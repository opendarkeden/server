////////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterManager.h 
// Written By  : Reiot
// Revised by  : ±è¼º¹Î
// Description : 
////////////////////////////////////////////////////////////////////////////////


#include "MonsterManager.h"
#include <stdlib.h>			// atoi()
#include "Assert.h"
#include "LogClient.h"
#include "MonsterInfo.h"
#include "ItemInfoManager.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "MonsterCorpse.h"
#include "Tile.h"
#include "Zone.h"
#include "Player.h"
#include "Monster.h"
#include "OptionInfo.h"
#include "Skull.h"
#include "DB.h"
#include "Treasure.h"
#include "Thread.h"
#include "ItemFactoryManager.h"
#include "ZoneUtil.h"
#include "CreatureUtil.h"
#include "VariableManager.h"
#include "MonsterNameManager.h"
#include "MasterLairInfoManager.h"
#include "LuckInfo.h"
#include "ItemUtil.h"
#include "EventItemUtil.h"
#include "WarSystem.h"
#include "Properties.h"
#include "CastleInfoManager.h"
#include "SweeperBonusManager.h"
#include "skill/SummonGroundElemental.h"
#include "skill/EffectHarpoonBomb.h"
#include "EffectPacketSend.h"
#include "ItemGradeManager.h"
#include "StringPool.h"

#include <fstream>

#include "GCCreatureDied.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"
#include "GCDeleteObject.h"
#include "GCSay.h"

#include "Profile.h"
#include "GDRLairManager.h"
#include "DynamicZone.h"
#include "DynamicZoneGateOfAlter.h"

#define __MONSTER_FIGHTING__
extern bool isPotentialEnemy(Monster* pMonster, Creature* pCreature);
extern void countResurrectItem();

//#define __PROFILE_MONSTER__

#ifdef __PROFILE_MONSTER__
	#define __BEGIN_PROFILE_MONSTER(name)	beginProfileEx(name);
	#define __END_PROFILE_MONSTER(name)		endProfileEx(name);
#else
	#define __BEGIN_PROFILE_MONSTER(name)	((void)0);
	#define __END_PROFILE_MONSTER(name)		((void)0);
#endif

////////////////////////////////////////////////////////////////////////////////
// À¯·áÈ­Á¸ ¾ÆÀÌÅÛ ·çÆÃÈ®·ü º¸³Ê½º ÆÛ¼¾Æ®
////////////////////////////////////////////////////////////////////////////////
//const uint g_pVariableManager->getPremiumItemProbePercent() = 220;

bool isLottoWinning();

////////////////////////////////////////////////////////////////////////////////
//
// constructor
//
////////////////////////////////////////////////////////////////////////////////
MonsterManager::MonsterManager (Zone* pZone) 
	
{
	__BEGIN_TRY
		
	Assert(pZone != NULL);
	m_pZone = pZone;

	Assert(g_pCastleInfoManager!=NULL);
	m_CastleZoneID = 0;
	g_pCastleInfoManager->getCastleZoneID( m_pZone->getZoneID(), m_CastleZoneID );

	m_nEventMonster = 0;
	m_pEventMonsterInfo = NULL;

	getCurrentTime(m_RegenTime);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// destructor
//
////////////////////////////////////////////////////////////////////////////////
MonsterManager::~MonsterManager () 
	
{
	__BEGIN_TRY

	SAFE_DELETE(m_pEventMonsterInfo);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// load from database
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::load ()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*    pResult = NULL;
	string     text, eventText;

	m_RICE_CAKE_PROB_RATIO[0] = 100;
	m_RICE_CAKE_PROB_RATIO[1] = 33;
	m_RICE_CAKE_PROB_RATIO[2] = 33;
	m_RICE_CAKE_PROB_RATIO[3] = 33;
	m_RICE_CAKE_PROB_RATIO[4] = 1;
	m_SumOfCakeRatio = 0;

	for (int i=0; i<5; i++)
		m_SumOfCakeRatio += m_RICE_CAKE_PROB_RATIO[i];

	// ÀÌ¹Ì ÀÖ´Ù¸é ±âÁ¸ÀÇ MonsterCounterµéÀ» ¸ðµÎ Áö¿î´Ù.
	bool bReload = false;
	unordered_map< SpriteType_t, MonsterCounter* >::iterator iMC = m_Monsters.begin();
	while (iMC!=m_Monsters.end())
	{
		MonsterCounter* pMC = iMC->second;
		SAFE_DELETE(pMC);

		iMC ++;

		// m_Monsters°¡ ÀÌ¹Ì ÀÖ¾ú´Ù¸é reloadÇÑ °ÍÀÌ´Ù..¶ó°í º»´Ù. by sigi. 2002.9.19
		bReload = true;
	}

	BEGIN_DB
	{
		// DynamicZone À» À§ÇÑ Ã³¸®
		ZoneID_t zoneID = m_pZone->getZoneID();
		if ( m_pZone->isDynamicZone() )
		{
			DynamicZone* pDynamicZone = m_pZone->getDynamicZone();
			Assert( pDynamicZone != NULL );

			zoneID = pDynamicZone->getTemplateZoneID();
		}

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
		"SELECT MonsterList, EventMonsterList from ZoneInfo WHERE ZoneID=%d", zoneID );

		if (pResult->getRowCount() <= 0) 
		{
			SAFE_DELETE(pStmt);
//			throw Error("MonsterManager::load() : Á¸ÀÌ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
			return;
		}

		pResult->next();
		text = pResult->getString(1);
		eventText = pResult->getString(2);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)


	parseMonsterList( text, bReload );
	parseEventMonsterList( eventText, bReload );

	__END_CATCH
}

void MonsterManager::parseMonsterList(const string& text, bool bReload)
	
{
	if (text.size() <= 0) return;

	//--------------------------------------------------------------------------------
	//
	// text ÆÄ¶ó¹ÌÅÍ´Â ZoneInfo Å×ÀÌºíÀÇ Monsters (TEXT) ÄÃ·³°ªÀ» ³ªÅ¸³½´Ù.
	// Æ÷¸ËÀº ´ÙÀ½°ú °°´Ù.
	//
	// (MonsterType1,#Monster1) (MonsterType2,#Monter2)(..,..)
	// i            j         k i            j        k    
	//
	//--------------------------------------------------------------------------------
	
	size_t i = 0 , j = 0 , k = 0;

	do 
	{
		// parse string
		i = text.find_first_of('(',k);
		j = text.find_first_of(',',i+1);
		k = text.find_first_of(')',j+1);

		if (i==string::npos || j==string::npos || k==string::npos
			|| i > j || j > k) break;

		// ¸ó½ºÅÍ Å¸ÀÔ°ú ÃÖ´ë °³¼ö¸¦ ±¸ÇÑ´Ù. ¸ó½ºÅÍ Å¸ÀÔ°ú ÃÖ´ë °³¼ö¸¦ ±¸ÇÑ´Ù.
		uint monsterType = atoi(text.substr(i+1,j-i-1).c_str());
		uint maxMonsters = atoi(text.substr(j+1,k-j-1).c_str());

		Assert(maxMonsters > 0);

		// ¸ó½ºÅÍ ÀÎÆ÷·Î ºÎÅÍ Monster Sprite TypeÀ» ¹Þ¾Æ¿Â´Ù.
		const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(monsterType);
		SpriteType_t spriteType = pMonsterInfo->getSpriteType();

		// ÀÌ¹Ì Á¸ÀçÇÏ´ÂÁöÀÇ ¿©ºÎ¸¦ Ã¼Å©ÇÑ´Ù.
		unordered_map< SpriteType_t , MonsterCounter* >::iterator itr = m_Monsters.find(spriteType);

		if (itr != m_Monsters.end()) 
		{
			WORD CurrentMaxCount = itr->second->getMaxMonsters();
			WORD NewMaxCount = CurrentMaxCount + maxMonsters;
			itr->second->setMaxMonsters(NewMaxCount);
		} 
		else 
		{
			// ¸ó½ºÅÍÄ«¿îÅÍ °´Ã¼¸¦ »ý¼º, unordered_map ¿¡ µî·ÏÇÑ´Ù.
			MonsterCounter* pMonsterCounter = new MonsterCounter(monsterType , maxMonsters, 0);

			// Á¸ÀçÇÏÁö ¾Ê´Â °æ¿ì, Ãß°¡ÇÑ´Ù.
			m_Monsters[spriteType] = pMonsterCounter;
		}

		//--------------------------------------------------------------------------------
		// ÇØ´çÇÏ´Â Å¸ÀÔÀÇ ¸ó½ºÅÍ¸¦ Á¸¿¡ Ãß°¡ÇÑ´Ù.
		//--------------------------------------------------------------------------------
		if (!bReload) // reload°¡ ¾Æ´Ï¸é..
		{
			for (uint m = 0 ; m < maxMonsters ; m ++) 
			{
				// Á¸ÀÇ ºó ÁÂÇ¥¸¦ Ã£¾Æ³½´Ù.
				ZoneCoord_t x, y;
				if (!findPosition(monsterType, x, y))
				{
					Assert(false);
					return;
				}

				// ¸ó½ºÅÍ °´Ã¼¸¦ »ý¼ºÇÏ°í ´É·ÂÄ¡ µîÀ» ÃÊ±âÈ­ÇÑ´Ù.
				Monster* pMonster = new Monster(monsterType);

				////////////////////////////////////////////////////////////////////////////////
				// ¿ùµåÄÅ ÀÌº¥Æ® °ü·Ã(7¿ù 1ÀÏºÎÅÍ´Â ¾ø¾îÁü)
				/*
				if(rand()%g_pVariableManager->getEventRatio() == 0 &&
						g_pVariableManager->getEventActivate() == 1)
				{
				  pMonster->setEventMonsterFlag(true);
				  string MonsterName =  g_pMonsterNameManager->getRandomName(pMonster, true);
				  pMonster->setName(MonsterName);
				  //cout << "ÀÌº¥Æ® ¸ó½ºÅÍ ÀÌ¸§: " << pMonster->getName();
				}
				*/
				///////////////////////////////////////////////////////////////////////////
				Assert(pMonster != NULL);

				try
				{
					m_pZone->addCreature(pMonster , x , y , Directions(rand() & 0x07));
				}
				catch (EmptyTileNotExistException&)
				{
					//cerr << "MonsterManager::load() : ÀÚ¸®°¡ ¾ø³×?" << endl;
					SAFE_DELETE(pMonster);
				}

			}
		}
	} while (k < text.size() - 1);
}

void MonsterManager::parseEventMonsterList(const string& text, bool bReload)
	
{
	if (text.size() <= 0) return;

	//--------------------------------------------------------------------------------
	//
	// text ÆÄ¶ó¹ÌÅÍ´Â ZoneInfo Å×ÀÌºíÀÇ Monsters (TEXT) ÄÃ·³°ªÀ» ³ªÅ¸³½´Ù.
	// Æ÷¸ËÀº ´ÙÀ½°ú °°´Ù.
	//
	// (MonsterType1,#Monster1,RegenDelay) (MonsterType2,#Monter2,RegenDelay)(..,..)
	// i            j         k          l i            j        k          l
	//
	//--------------------------------------------------------------------------------
	
	size_t i = 0 , j = 0 , k = 0, l = 0, m = 0, n = 0;

	do 
	{
		// parse string
		i = text.find_first_of('(',l);
		j = text.find_first_of(',',i+1);
		k = text.find_first_of(',',j+1);
		l = text.find_first_of(')',k+1);
		m = text.find_first_of(',',k+1);
		n = text.find_first_of(',',m+1);

		if (i==string::npos || j==string::npos || k==string::npos || l==string::npos
			|| i > j || j > k || k > l) break;

		int tx = -1;
		int ty = -1;
		if ( m != string::npos && n != string::npos && k < m && m < n && n < l )
		{
			tx = atoi(text.substr(m+1, n-m-1).c_str());
			ty = atoi(text.substr(n+1, l-n-1).c_str());
			cout << "x : " << tx << endl;
			cout << "y : " << ty << endl;
			l = m;
		}

		// ¸ó½ºÅÍ Å¸ÀÔ°ú ÃÖ´ë °³¼ö¸¦ ±¸ÇÑ´Ù. ¸ó½ºÅÍ Å¸ÀÔ°ú ÃÖ´ë °³¼ö¸¦ ±¸ÇÑ´Ù.
		uint monsterType = atoi(text.substr(i+1,j-i-1).c_str());
		uint maxMonsters = atoi(text.substr(j+1,k-j-1).c_str());
		uint regenDelay  = atoi(text.substr(k+1,l-k-1).c_str());

		Assert(maxMonsters > 0);

		//--------------------------------------------------------------------------------
		// ÇØ´çÇÏ´Â Å¸ÀÔÀÇ ¸ó½ºÅÍ¸¦ Á¸¿¡ Ãß°¡ÇÑ´Ù.
		//--------------------------------------------------------------------------------
		if (!bReload) // reload°¡ ¾Æ´Ï¸é..
		{
			//cout << "[MM] load EventMonsterList: [" << m_pZone->getZoneID() << "] mtype=" << monsterType
			//	<< ", maxMonsters=" << maxMonsters
			//	<< ", regenDelay=" << regenDelay << endl;
			if (m_pEventMonsterInfo==NULL)
			{
				m_pEventMonsterInfo = new vector<EventMonsterInfo>;
				//m_pEventMonsterInfo->resize( maxMonsters );
			}

			/*
			if (m_pEventMonsterInfo->size() + maxMonsters < m_pEventMonsterInfo->capacity())
			{
				m_pEventMonsterInfo->resize( m_pEventMonsterInfo->size() + maxMonsters );
			}
			*/

			for (uint m = 0 ; m < maxMonsters ; m ++) 
			{
				if (g_pVariableManager->isActiveChiefMonster())
				{
					// Á¸ÀÇ ºó ÁÂÇ¥¸¦ Ã£¾Æ³½´Ù.
					ZoneCoord_t x, y;
					if ( tx != -1 )
					{
						x = tx; y = ty;
					}
					else if (!findPosition(monsterType, x, y))
					{
						Assert(false);
						return;
					}

					// ¸ó½ºÅÍ °´Ã¼¸¦ »ý¼ºÇÏ°í ´É·ÂÄ¡ µîÀ» ÃÊ±âÈ­ÇÑ´Ù.
					Monster* pMonster = new Monster(monsterType);
					Assert(pMonster != NULL);

					pMonster->setEventMonsterIndex( m_nEventMonster++ );

					EventMonsterInfo info;
					info.monsterType = monsterType;
					info.regenDelay = regenDelay;
					info.bExist = true;
					info.x = tx;
					info.y = ty;

					m_pEventMonsterInfo->push_back( info );

					try
					{
						m_pZone->addCreature(pMonster , x , y , Directions(rand() & 0x07));

						// ±×·¹ÀÌÆ® ·¯ÇÇ¾ð
/*						if ( monsterType == 764 )
						{
							static TPOINT pos[] = {
								{ 41, 52 },
								{ 72, 114 },
								{ 104, 35 } };
							// ¸®Ä¡Á© 20¸¶¸®
							for ( int j=0; j<3; ++j )
							for ( int i=0; i<20; ++i )
							{
								pMonster = new Monster( 493 + (i%10) );
								m_pZone->addCreature(pMonster , pos[j].x , pos[j].y , Directions(rand()%8));
							}
						}*/
					}
					catch (EmptyTileNotExistException&)
					{
						//cerr << "MonsterManager::load() : ÀÚ¸®°¡ ¾ø³×?" << endl;
						SAFE_DELETE(pMonster);
					}
				}
				else
				{
					m_nEventMonster++;

					EventMonsterInfo info;
					info.monsterType = monsterType;
					info.regenDelay = regenDelay;
					getCurrentTime( info.regenTime );
					info.bExist = false;

					m_pEventMonsterInfo->push_back( info );
				}

			}
		}
	} while (l < text.size() - 1);


}

////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addCreature (Creature* pCreature)
	
{
	__BEGIN_TRY

	Monster* pMonster = dynamic_cast<Monster*>(pCreature);

	// Å©¸®Ã³ ÇØ½¬¸Ê¿¡ Ãß°¡ÇÑ´Ù.
	CreatureManager::addCreature(pMonster);

	// event monster´Â MonsterCounter¿¡ µé¾î°¡Áö ¾Ê°Ô ÇÑ´Ù. by sigi. 2002.10.14
	if (m_pEventMonsterInfo!=NULL 
		&& pMonster->isEventMonster())
	{
		uint index = pMonster->getEventMonsterIndex();

		if (index < m_pEventMonsterInfo->size())
		{
			EventMonsterInfo& info = (*m_pEventMonsterInfo)[index];

			getCurrentTime( info.regenTime );
			info.regenTime.tv_sec += info.regenDelay;

			info.bExist = true;
		}

		//cout << "[MM] add EventMonster: [" << pMonster->getEventMonsterIndex()
		//	<< "] = " << info.monsterType << ", delay = " << info.regenDelay << endl;
		return;
	}

	// ±×·± ¸ó½ºÅÍ Å¸ÀÔÀÌ Á¸¿¡ Á¸ÀçÇÒ ¼ö ÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù.
	unordered_map< SpriteType_t , MonsterCounter* >::iterator itr = m_Monsters.find(pMonster->getSpriteType());

	if (itr == m_Monsters.end()) 
	{
		StringStream msg;
		msg << "ÇöÀç Á¸¿¡ Á¸ÀçÇÒ ¼ö ¾ø´Â Å¸ÀÔÀÇ ¸ó½ºÅÍ°¡ Ãß°¡µÇ¾ú½À´Ï´Ù.\n" 
			<< "ÇöÀç Á¸Àº [" << m_pZone->getZoneID() << "]ÀÔ´Ï´Ù.\n"
			<< "Ãß°¡ÇÏ·Á°í ÇÑ ¸ó½ºÅÍÀÇ Å¸ÀÔÀº [" << pMonster->getMonsterType() << "]ÀÔ´Ï´Ù.\n";
		//throw Error(msg.toString());
	}
	else
	{ 
		// ¸ó½ºÅÍ Ä«¿îÅÍ¸¦ Áõ°¡½ÃÅ²´Ù.
		itr->second->addMonster();
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::deleteCreature (ObjectID_t creatureID)
	//NoSuchElementException , Error)
{
	__BEGIN_TRY

	// Å©¸®Ã³ ÇØ½¬¸Ê¿¡ ±×·± OID ¸¦ °¡Áø ¸ó½ºÅÍ°¡ Á¸ÀçÇÏ´ÂÁö Ã¼Å©ÇÑ´Ù.
	unordered_map<ObjectID_t , Creature* >::iterator itr = m_Creatures.find(creatureID);

	if (itr == m_Creatures.end()) 
	{
		cerr << "MonsterManager::deleteCreature() : NoSuchElementException" << endl;
		
		// ÀÌ°Íµµ ¿ÜºÎ¿¡¼­ Á¦´ë·Î Ã³¸® ¾ÈµÇ°í ÀÖ´Â°Å °°´Ù.
		// by sigi. 2002.5.9
		//throw NoSuchElementException("±×·± ObjectID¸¦ °¡Áø ¸ó½ºÅÍ´Â Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
		
		return;
	}

	Monster* pMonster = dynamic_cast<Monster*>(itr->second);

	// Å©¸®Ã³ ÇØ½¬¸ÊÀÇ ÇØ´ç ³ëµå¸¦ »èÁ¦ÇÑ´Ù.
	// ÇÔ¼ö ³¡¿¡ ÀÖ´ø°É ¿©±â·Î ¿Ã·È´Ù. by sigi
	// ¹Ùº¸¾ß~ itr ÂüÁ¶´Â ³¡³»°í ³ëµå¸¦ Áö¿ö¾ßÂ¡~. 2002.10.12 by bezz
	m_Creatures.erase(itr);


	// event monster´Â MonsterCounter¶û °ü°è¾ø´Ù. by sigi .2002.10.14
	if (m_pEventMonsterInfo!=NULL
		&& pMonster->isEventMonster()
		&& pMonster->getMonsterType() != 764)
	{
		uint index = pMonster->getEventMonsterIndex();

		if (index < m_pEventMonsterInfo->size())
		{
			EventMonsterInfo& info = (*m_pEventMonsterInfo)[index];
			info.bExist = false;
			//cout << "[MM] delete EventMonster: [" << pMonster->getEventMonsterIndex()
			//	<< "] = " << info.monsterType << endl;
		}

		return;
	}

	// ¸ó½ºÅÍ Ä«¿îÅÍ¿¡ ±×·± ¸ó½ºÅÍ Å¸ÀÔÀÌ Á¸ÀçÇÏ´ÂÁö Ã¼Å©ÇÑ´Ù.
	unordered_map< SpriteType_t , MonsterCounter *>::iterator itr2 = m_Monsters.find(pMonster->getSpriteType());

	if (itr2 == m_Monsters.end()) 
	{
		cerr << "MonsterManager::deleteCreature() : NoSuchElementException" << endl;
		//throw NoSuchElementException("±×·± SpriteTypeÀ» °¡Áø ¸ó½ºÅÍ´Â Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
	}
	else 
	{
		// ¸ó½ºÅÍÀÇ ¼ýÀÚ¸¦ ÁÙÀÎ´Ù.
		itr2->second->deleteMonster();
	}


	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// ÀüÃ¼ÀÇ ÀáÀçÀûÀÎ ÀûÀ¸·Î ÀÎ½ÄÇÑ´Ù. 2002.7.22 by sigi
// pAttackedMonster¸¦ pCreature°¡ °ø°ÝÇÑ °æ¿ì¿¡
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addPotentialEnemy(Monster* pAttackedMonster, Creature* pCreature) 
	
{
	__BEGIN_TRY

	//cout << "MonsterManager::addPotentialEnemy()" << endl;
		
	unordered_map< ObjectID_t , Creature* >::const_iterator itr = m_Creatures.begin();

	for (; itr!=m_Creatures.end(); itr++) 
	{
		Creature* pMonsterCreature = itr->second;

		// ¶§¸° ³ðÀ» º¼¼ö ÀÖ´Â °Å¸®¿©¾ß ÇÑ´Ù.
		Distance_t dist = pMonsterCreature->getDistance(pCreature->getX(), pCreature->getY());

		if (dist <= pMonsterCreature->getSight() 
			// ÀÚ½ÅÀº ´Ù¸¥ ÄÚµå¿¡¼­ Ã¼Å©ÇÑ´Ù.
			&& pMonsterCreature!=pAttackedMonster)
		{
			Monster* pMonster = dynamic_cast<Monster*>(pMonsterCreature);
			//cout << "addPotentialEnemy: " << pMonster->getName().c_str() << endl;
			pMonster->addPotentialEnemy( pCreature );
		}
	}
		

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// ÀüÃ¼ÀÇ ÀûÀ¸·Î ÀÎ½ÄÇÑ´Ù. 2002.7.22 by sigi
// pAttackedMonster¸¦ pCreature°¡ °ø°ÝÇÑ °æ¿ì¿¡
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addEnemy(Monster* pAttackedMonster, Creature* pCreature) 
	
{
	__BEGIN_TRY
		
	//cout << "MonsterManager::addEnemy()" << endl;

	unordered_map< ObjectID_t , Creature* >::const_iterator itr = m_Creatures.begin();

	for (; itr!=m_Creatures.end(); itr++) 
	{
		Creature* pMonsterCreature = itr->second;

		// ¶§¸° ³ðÀ» º¼¼ö ÀÖ´Â °Å¸®¿©¾ß ÇÑ´Ù.
		Distance_t dist = pMonsterCreature->getDistance(pCreature->getX(), pCreature->getY());

		if (dist <= pMonsterCreature->getSight() 
			// ÀÚ½ÅÀº ´Ù¸¥ ÄÚµå¿¡¼­ Ã¼Å©ÇÑ´Ù.
			&& pMonsterCreature!=pAttackedMonster)
		{
			Monster* pMonster = dynamic_cast<Monster*>(pMonsterCreature);
			//cout << "addEnemy: " << pMonster->getName().c_str() << endl;
			pMonster->addEnemy( pCreature );
		}
	}
		

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// Å©¸®Ã³ ¸Å´ÏÀú¿¡ Á¾¼ÓµÈ ¸ó½ºÅÍµéÀÇ AI¿¡ ÀÇÇÑ ¾×¼ÇÀ» ½ÇÇàÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::processCreatures ()
	
{
	__BEGIN_TRY

//	__BEGIN_PROFILE_MONSTER("MM_PROCESS_CREATURES");

	Timeval currentTime;
	getCurrentTime(currentTime);

	try
	{
		unordered_map< ObjectID_t , Creature* >::iterator before = m_Creatures.end();
		unordered_map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

		while (current != m_Creatures.end()) 
		{
			Creature* pCreature = current->second;

			Assert(pCreature != NULL);

			__BEGIN_PROFILE_MONSTER("MM_EFFECTMANAGER");

			pCreature->getEffectManager()->heartbeat(currentTime);

			__END_PROFILE_MONSTER("MM_EFFECTMANAGER");

			if (pCreature->isAlive()) 
			{
				/*
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);

				if (pMonster->isEnemyLimit())
				{
					Zone* 		pZone 	= pMonster->getZone();
					ZoneCoord_t cx 		= pMonster->getX();
					ZoneCoord_t cy 		= pMonster->getY();
					ObjectID_t 	monsterID = pMonster->getObjectID();

					unordered_map< SpriteType_t , MonsterCounter *>::iterator itr = m_Monsters.find(pMonster->getSpriteType());

					if (itr == m_Monsters.end()) 
					{
						//cerr << "MonsterManager::processCreatures() : NoSuchElementException" << endl;
						//throw NoSuchElementException("±×·± SpriteTypeÀ» °¡Áø ¸ó½ºÅÍ´Â Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
					}
					else
					{
						// ¸ó½ºÅÍÀÇ ¼ýÀÚ¸¦ ÁÙÀÎ´Ù.
						itr->second->deleteMonster();
					}


					// Å¸ÀÏ°ú ¸ó½ºÅÍ ¸Å´ÏÀú¿¡¼­ Å©¸®Ã³¸¦ »èÁ¦ÇÑ´Ù.
					Tile & tile = pZone->getTile(cx , cy);
					tile.deleteCreature(monsterID);

					SAFE_DELETE(pMonster);

					if (before == m_Creatures.end()) 
					{
						m_Creatures.erase(current);
						current = m_Creatures.begin();
					} 
					else 
					{
						m_Creatures.erase(current);
						current = before;
						current ++;
					}

					GCDeleteObject gcDeleteObject;
					gcDeleteObject.setObjectID(monsterID);

					pZone->broadcastPacket(cx, cy , &gcDeleteObject);
				}
			*/
				__BEGIN_PROFILE_MONSTER("MM_CREATURE_ACT");
				pCreature->act(currentTime);
				before = current ++;
				__END_PROFILE_MONSTER("MM_CREATURE_ACT");
			} 
			else
			{

				Monster* pMonster = dynamic_cast<Monster*>(pCreature);
				Assert(pMonster != NULL);

				/*if ( pMonster->getMonsterType() == 371 ||
				     pMonster->getMonsterType() == 372 ||
				     pMonster->getMonsterType() == 373 ||
				     pMonster->getMonsterType() == 374 ||
				     pMonster->getMonsterType() == 375 ||
				     pMonster->getMonsterType() == 376)
					return;
				else
				{*/

					if (pMonster->isEventMonster())		// by sigi. 2002.10.14
					{
						if (m_pEventMonsterInfo!=NULL)
						{
							uint index = pMonster->getEventMonsterIndex();

							if (index < m_pEventMonsterInfo->size())
							{
								EventMonsterInfo& info = (*m_pEventMonsterInfo)[index];
								info.bExist = false;

								//cout << "[MM] dead EventMonster: [" << pMonster->getEventMonsterIndex()
								//	<< "] = " << info.monsterType << endl;
							}
						}
					}
					else
					{
						// ¸ó½ºÅÍ Ä«¿îÅÍ¸¦ ÇÏ³ª ÁÙÀÎ´Ù.
						unordered_map< SpriteType_t , MonsterCounter *>::iterator itr = m_Monsters.find(pMonster->getSpriteType());

						if (itr == m_Monsters.end()) 
						{
							//cerr << "MonsterManager::processCreatures() : NoSuchElementException" << endl;
							//throw NoSuchElementException("±×·± SpriteTypeÀ» °¡Áø ¸ó½ºÅÍ´Â Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
						}
						else
						{
							// ¸ó½ºÅÍÀÇ ¼ýÀÚ¸¦ ÁÙÀÎ´Ù.
							itr->second->deleteMonster();
						}
					}

				__BEGIN_PROFILE_MONSTER("MM_CREATURE_DEADACTION");
					// ¸ÕÀú ¸ó½ºÅÍ¸¦ Á×ÀÌ±â Àü¿¡ ¸¶Áö¸· ¾×¼ÇÀ» ÃëÇÏ°Ô ÇÑ´Ù.
					pMonster->actDeadAction();
				__END_PROFILE_MONSTER("MM_CREATURE_DEADACTION");

				__BEGIN_PROFILE_MONSTER("MM_KILL_CREATURE");
					// ¸ó½ºÅÍ¸¦ Á¸¿¡¼­ Á¦°ÅÇÏ°í, ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
					killCreature(pMonster);
				__END_PROFILE_MONSTER("MM_KILL_CREATURE");

					// ¸ó½ºÅÍ¿¡ ´ëÇÑ Å©¸®Ã³ÀÇ ÇØ½¬¸ÊÀÇ ³ëµå¸¦ »èÁ¦ÇÑ´Ù.
					// Àß¸ø »èÁ¦ÇÒ °æ¿ì, ¿¬°áÀÌ ±úÁú ¿ì·Á°¡ ÀÖÀ¸´Ï ÁÖÀÇÇÒ °Í.
					if (before == m_Creatures.end()) 
					{
						m_Creatures.erase(current);
						current = m_Creatures.begin();
					} 
					else 
					{
						m_Creatures.erase(current);
						current = before;
						current ++;
					}
				//}

			}
		}

		// ¸ó½ºÅÍ Àç»ý ÄÚµå¿¡ findPositionÀÌ¶ó´Â ¹«ÇÑ ·çÇÁ ÇÔ¼ö°¡ ÇÏ³ª ÀÖ´Ù.
		// 30ÃÊ µ¿¾È ¿©·¯ ¸¶¸®ÀÇ ¸ó½ºÅÍ°¡ Á×¾úÀ» ¶§, ÀÌ ¸ó½ºÅÍµéÀ» ¸®Á¨ÇÒ ÀÚ¸®¸¦ Ã£´Âµ¥ 
		// °É¸®´Â ½Ã°£ÀÌ ±æ¾îÁú ¼ö°¡ ÀÖ´Ù. ±×¸®°í ÀÌ ½Ã°£ÀÌ ±æ¾îÁö¸é ·¢ÀÌ
		// ¹ß»ýÇÑ´Ù. Æò±ÕÀûÀ¸·Î´Â Á» ´À·ÁÁö´õ¶óµµ, ·ºÀ» ÁÙÀÌ±â À§ÇØ¼­ 
		// ¸®Á¨¿¡ ´ëÇÑ °Ë»ç¸¦ ¸ÅÅÏ ÇÏµµ·Ï º¯°æÇÑ´Ù. -- ±è¼º¹Î
		// ÀÏÁ¤ ÁÖ±â¸¶´Ù ¸ó½ºÅÍ ¼ýÀÚ¸¦ È®ÀÎÇØ¼­ ¸®Á¨½ÃÄÑÁØ´Ù.
		if (m_RegenTime < currentTime)
		{
			__BEGIN_PROFILE_MONSTER("MM_REGENERATE_CREATURES");

			regenerateCreatures();

			m_RegenTime.tv_sec  = currentTime.tv_sec + 5;	// 5ÃÊ ÈÄ ¸®Á¨
			m_RegenTime.tv_usec = currentTime.tv_usec;

			__END_PROFILE_MONSTER("MM_REGENERATE_CREATURES");
		}

		// ÀÌ°Å ¿Ö ÁÖ¼®Ã³¸® ¾ÈµÇ¾îÀÖ¾úÁö.. by sigi. 2002.5.3
		//regenerateCreatures();
	}
	catch (Throwable & t)
	{
		filelog("MonsterManagerBug.log", "ProcessCreatureBug : %s", t.toString().c_str());
		//cerr << t.toString() << endl;
	}

//	__END_PROFILE_MONSTER("MM_PROCESS_CREATURES");

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// ¸ó½ºÅÍÀÇ ¼ýÀÚ°¡ ÁÙ¾îµé¸é ¸ó½ºÅÍ¸¦ Àç»ý¼ºÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::regenerateCreatures ()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// ÀüÀï Áß¿¡ ¸ó½ºÅÍ ¸®Á¨ ¾ÈµÇ°Ô..
	if (m_pZone->isHolyLand()) 
	{
		// Á¾Á· ÀüÀï Áß
		if (g_pWarSystem->hasActiveRaceWar())
			return;

		// ±æµå ÀüÀï Áß..
		if (m_CastleZoneID!=0 && g_pWarSystem->hasCastleActiveWar(m_CastleZoneID))
		{
			CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
			if (pCastleInfo!=NULL)
			{
				GuildID_t OwnerGuildID = pCastleInfo->getGuildID();

				// °ø¿ë¼ºÀÌ ¾Æ´Ñ °æ¿ì´Â ¸®Á¨ ¾ÈÇÑ´Ù.==°ø¿ë¼ºÀº ¸®Á¨ ÇÑ´Ù.
				if (OwnerGuildID!=SlayerCommon
					&& OwnerGuildID!=VampireCommon
					&& OwnerGuildID!=OustersCommon
					)
				{
					return;
				}
			}
		}
	}

	// ·¹º§º° ÀüÀïÀ» ÇÏ´Â ÁßÀÌ¶ó¸é -_-;; 
	ZoneID_t zoneID = m_pZone->getZoneID(); 
	if (zoneID == 1131 || zoneID == 1132 || zoneID == 1133 || zoneID == 1134)
	{
		if (!g_pSweeperBonusManager->isAble( zoneID ) )
			return;
	}

	unordered_map<SpriteType_t, MonsterCounter*>::iterator itr = m_Monsters.begin();
	for (; itr != m_Monsters.end() ; itr ++) 
	{
		MonsterCounter* pCounter = itr->second;

		// ¸ó½ºÅÍ°¡ ÁÙ¾îµé¾úÀ» °æ¿ì...
		while (pCounter->getCurrentMonsters() < pCounter->getMaxMonsters()) 
		{
			SpriteType_t  SpriteType  = itr->first;
			MonsterType_t monsterType = 0;

			vector<MonsterType_t> RegenVector = g_pMonsterInfoManager->getMonsterTypeBySprite(SpriteType);
			Assert(RegenVector.size() > 0);

			monsterType = RegenVector[rand()%RegenVector.size()];

			// Á¸ÀÇ ºó ÁÂÇ¥¸¦ Ã£¾Æ³½´Ù.
			ZoneCoord_t x, y;
			if (!findPosition(monsterType, x, y))
			{
				Assert(false);
				return;
			}

			// ¸ó½ºÅÍ °´Ã¼¸¦ »ý¼ºÇÏ°í ´É·ÂÄ¡ µîÀ» ÃÊ±âÈ­ÇÑ´Ù.
			Monster* pMonster = new Monster(monsterType);
			Assert(pMonster != NULL);

			/////////////////////////////////////////////////////////////////////
			// ¸ó½ºÅÍ¸¦ Ãß°¡ÇÏ´Â ½ÃÁ¡¿¡¼­ ÀÌº¥Æ® ¸ó½ºÅÍÀÎÁö °Ë»ç¸¦ ÇÑ´Ù.
			///  7¿ù 1ÀÏÀÚ·Î »èÁ¦ (¿ùµåÄÅ ÀÌº¥Æ® ³¡)
			/*
			if(rand()%g_pVariableManager->getEventRatio()==0 && 
					g_pVariableManager->getEventActivate() == 1 )
			{		
				pMonster->setEventMonsterFlag(true);
				string MonsterName = g_pMonsterNameManager->getRandomName(pMonster, true);
				pMonster->setName(MonsterName);

				//cout << "ÀÌº¥Æ® ¸ó½ºÅÍ ÀÌ¸§: " << MonsterName;
			}
			*/
			/////////////////////////////////////////////////////////////////////

			try
			{
				m_pZone->addCreature(pMonster , x , y , Directions(rand()%8));
			}
			catch (EmptyTileNotExistException&)
			{
				//cerr << "MonsterManager::processCreatures() : ÀÚ¸®°¡ ¾ø³×?" << endl;
				SAFE_DELETE(pMonster);
			}
		}
	}

	if (g_pVariableManager->isActiveChiefMonster()
		&& m_pEventMonsterInfo!=NULL)
	{
		Timeval currentTime;
		getCurrentTime( currentTime );

		//cout << "regenCheck [" << m_pZone->getZoneID() <<"] EventMonsterNum = "
		//	<< m_pEventMonsterInfo->size() << " : "; 

		for (uint i=0; i<m_pEventMonsterInfo->size(); i++)
		{
			EventMonsterInfo& info = (*m_pEventMonsterInfo)[i];

			if (!info.bExist
				&& currentTime >= info.regenTime)
			{
				//cout << i << " ";
				MonsterType_t monsterType = info.monsterType;

				// Á¸ÀÇ ºó ÁÂÇ¥¸¦ Ã£¾Æ³½´Ù.
				ZoneCoord_t x, y;
				if ( info.x != -1 )
				{
					x = info.x;
					y = info.y;
				}
				else if (!findPosition(monsterType, x, y))
				{
					Assert(false);
					return;
				}

				// ¸ó½ºÅÍ °´Ã¼¸¦ »ý¼ºÇÏ°í ´É·ÂÄ¡ µîÀ» ÃÊ±âÈ­ÇÑ´Ù.
				Monster* pMonster = new Monster(monsterType);
				Assert(pMonster != NULL);

				pMonster->setEventMonsterIndex( i );

				try
				{
					m_pZone->addCreature(pMonster , x , y , Directions(rand()%8));

					// ±×·¹ÀÌÆ® ·¯ÇÇ¾ð
/*					if ( monsterType == 764 )
					{
						static TPOINT pos[] = {
							{ 41, 52 },
							{ 72, 114 },
							{ 104, 35 } };
						// ¸®Ä¡Á© 20¸¶¸®
						for ( int j=0; j<3; ++j )
						for ( int i=0; i<20; ++i )
						{
							pMonster = new Monster( 493 + (i%10) );
							m_pZone->addCreature(pMonster , pos[j].x , pos[j].y , Directions(rand()%8));
						}
					}*/
				}
				catch (EmptyTileNotExistException&)
				{
					//cerr << "MonsterManager::processCreatures() : ÀÚ¸®°¡ ¾ø³×?" << endl;
					SAFE_DELETE(pMonster);
				}
			}

			/*
			else
			{
				if (!info.bExist)
					cout << "f ";
				else
					cout << "t ";
			}
			*/
		}

		//cout << endl;
	}

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool MonsterManager::findPosition(MonsterType_t monsterType, ZoneCoord_t& RX, ZoneCoord_t& RY) const
	
{
	__BEGIN_TRY

	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(monsterType);

	int count = 0;

/*	if ( monsterType == 722 )
	{
		// Áúµå·¹ ¼®»ó -_-;;
		RX = 94;
		RY = 172;
		return true;
	}*/

	// ¹«ÇÑ ·çÇÁÀÎµ¥... È¤½Ã¶óµµ ¹®Á¦°¡ ÀÖÀ»±î?
	while (true)
	{
		const BPOINT& pt = m_pZone->getRandomMonsterRegenPosition();

		Tile& rTile = m_pZone->getTile(pt.x,pt.y);

		// 1. Å¸ÀÏÀÌ ºí·ÏµÇ¾î ÀÖÁö ¾Ê°í
		// 2. Å¸ÀÏ¿¡ Æ÷Å»ÀÌ Á¸ÀçÇÏÁö ¾ÊÀ¸¸ç,
		// 3. ¾ÈÀüÁö´ë°¡ ¾Æ´Ï¶ó¸é
		if (!rTile.isBlocked(pMonsterInfo->getMoveMode()) && 
			!rTile.hasPortal() && 
			!(m_pZone->getZoneLevel(pt.x, pt.y) & SAFE_ZONE))
		{
			RX = pt.x;
			RY = pt.y;
			return true;
		}

		if (++count >= 300)
		{
			cerr << "MonsterManager::findPosition() : Max Count Exceeded" << endl;
			throw ("MonsterManager::findPosition() : Max Count Exceeded");
		}
	}

	// À§¿¡¼­ ¹«ÇÑ ·çÇÁ´Ï±î, ¿©±â±îÁö ¸ø ¿À°ÚÁö?
	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// Á×Àº Å©¸®Ã³¸¦ Ã³¸®ÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::killCreature (Creature* pDeadCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pDeadCreature->isDead());

	Zone* pZone = pDeadCreature->getZone();
	Assert(m_pZone == pZone);

	Monster* pDeadMonster = dynamic_cast<Monster*>(pDeadCreature);
	ZoneCoord_t cx = pDeadMonster->getX();
	ZoneCoord_t cy = pDeadMonster->getY();

	// Á×¾úÀ¸´Ï±î ¿ì¼±±ÇÀ» °è»êÇØÁØ´Ù.
	PrecedenceTable* pTable = pDeadMonster->getPrecedenceTable();
	
	pTable->compute();

	if ( pTable->getHostName() == "" )
	{
		// ¾Æ¹«µµ ¶§¸° ³ÑÀÌ ¾ø´Ù¸é ¾ÆÀÌÅÛÀ» ¾È ³Ö´Â´Ù.
		pDeadMonster->setTreasure( false );
	}
	else
	{
		pDeadMonster->setHostName(pTable->getHostName());
		pDeadMonster->setHostPartyID(pTable->getHostPartyID());
	}

	// ¸ÕÀú ¹Ù´Ú¿¡ ¾²·¯¶ß¸®¶ó°í, ÀÌÆåÆ®¸¦ »Ñ¸°´Ù.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pDeadCreature->getObjectID());
	gcAddEffect.setEffectID(Effect::EFFECT_CLASS_COMA);
	gcAddEffect.setDuration(0);
	pZone->broadcastPacket(cx, cy, &gcAddEffect);

	// ¸ó½ºÅÍ Á¦°Å
	Tile & tile = m_pZone->getTile(cx , cy);
	tile.deleteCreature(pDeadMonster->getObjectID());

	// DynamicZone ÀÏ°æ¿ìÀÇ Ã³¸®
	if ( m_pZone->isDynamicZone() )
	{
		DynamicZone* pDynamicZone = m_pZone->getDynamicZone();
		Assert( pDynamicZone != NULL );

		if ( pDynamicZone->getTemplateZoneID() == 4001 )
		{
			// Á¦´ÜÀÇ ÀÔ±¸ÀÇ °æ¿ì Ã³¸®
			DynamicZoneGateOfAlter* pGateOfAlter = dynamic_cast<DynamicZoneGateOfAlter*>(pDynamicZone);
			Assert( pGateOfAlter != NULL );

			pGateOfAlter->removeEffect( cx, cy );
		}
	}

	// ±×¶ó¿îµå ¿¤¸®¸àÅ»Àº ½ÃÃ¼µµ ¾øÁö·Õ
	if ( pDeadMonster->getMonsterType() == GROUND_ELEMENTAL_TYPE )
	{
		GCDeleteObject* pGCDO = new GCDeleteObject;
		pGCDO->setObjectID( pDeadMonster->getObjectID() );

		EffectPacketSend* pEffectPacketSend = new EffectPacketSend( pDeadMonster->getZone(), pDeadMonster->getX(), pDeadMonster->getY() );
		pEffectPacketSend->setPacket( pGCDO );
		// 1ÃÊ µÚ¿¡ ÆÐÅ¶ º¸³»¾ßÁã~
		pEffectPacketSend->setDeadline(10);
		pDeadMonster->getZone()->registerObject( pEffectPacketSend );
		pDeadMonster->getZone()->addEffect( pEffectPacketSend );

		SAFE_DELETE( pDeadMonster );
		return;
	}
	else if ( pDeadMonster->getMonsterType() == 764 )
	{
		// ±×·¹ÀÌÆ® ·¯ÇÇ¾ð
		GCDeleteObject* pGCDO = new GCDeleteObject;
		pGCDO->setObjectID( pDeadMonster->getObjectID() );

		EffectPacketSend* pEffectPacketSend = new EffectPacketSend( pDeadMonster->getZone(), pDeadMonster->getX(), pDeadMonster->getY() );
		pEffectPacketSend->setPacket( pGCDO );
		// 1ÃÊ µÚ¿¡ ÆÐÅ¶ º¸³»¾ßÁã~
		pEffectPacketSend->setDeadline(10);
		pDeadMonster->getZone()->registerObject( pEffectPacketSend );
		pDeadMonster->getZone()->addEffect( pEffectPacketSend );

		Monster* pNewMonster = new Monster(765);
		pNewMonster->setClanType( pDeadMonster->getClanType() );
		pNewMonster->setEventMonsterIndex( pDeadMonster->getEventMonsterIndex() );
		pNewMonster->setName(pDeadMonster->getName());
		pDeadMonster->getZone()->addCreature(pNewMonster, pDeadMonster->getX(), pDeadMonster->getY(), pDeadMonster->getDir());

		SAFE_DELETE( pDeadMonster );
		return;
	}
	else if ( pDeadMonster->getMonsterType() == 793
			|| pDeadMonster->getMonsterType() == 794
			|| pDeadMonster->getMonsterType() == 795 )
	{
		// ½½·¹ÀÌ¾î, ¹ìÆÄÀÌ¾î, ¾Æ¿ì½ºÅÍÁî Á¦¹°µµ ½ÃÃ¼ ¾ö²¿
		// ¹Ù·Î ¾ø¾Ö ¹ö¸°´Ù.
		GCDeleteObject gcDO;
		gcDO.setObjectID( pDeadMonster->getObjectID() );
		pDeadMonster->getZone()->broadcastPacket( pDeadMonster->getX(), pDeadMonster->getY(), &gcDO );

		SAFE_DELETE( pDeadMonster );
		return;
	}

	// ½ÃÃ¼ °´Ã¼¸¦ »ý¼ºÇÏ°í, OID ¸¦ ÇÒ´ç¹Þ´Â´Ù.
	MonsterCorpse* pMonsterCorpse = new MonsterCorpse(pDeadMonster);
	pMonsterCorpse->setHostName(pDeadMonster->getHostName());
	pMonsterCorpse->setHostPartyID(pDeadMonster->getHostPartyID());
	pMonsterCorpse->setQuestHostName( pTable->getQuestHostName() );
	pMonsterCorpse->setLevel( (int)(pDeadMonster->getLevel()) );
	pMonsterCorpse->setExp( (Exp_t)computeCreatureExp(pDeadMonster, 100) );
	pMonsterCorpse->setLastKiller( pDeadMonster->getLastKiller() );

	// Á×Àº ¸ó½ºÅÍ Á¾·ù¿¡ µû¶ó¼­ ½ÃÃ¼¿¡ ¾ÆÀÌÅÛÀ» Ãß°¡ÇØµÐ´Ù.
	addItem(pDeadMonster, pMonsterCorpse);

	// by sigi. 2002.12.12
	addCorpseToZone( pMonsterCorpse, m_pZone, cx, cy );

	if ( pDeadMonster->isFlag( Effect::EFFECT_CLASS_HARPOON_BOMB ) )
	{
		EffectHarpoonBomb* pEffect = dynamic_cast<EffectHarpoonBomb*>(pDeadMonster->findEffect( Effect::EFFECT_CLASS_HARPOON_BOMB ));
		if ( pEffect != NULL )
		{
			EffectHarpoonBomb* pZoneEffect = new EffectHarpoonBomb( m_pZone, pMonsterCorpse->getX(), pMonsterCorpse->getY() );
			pZoneEffect->setDamage( pEffect->getDamage() );
			pZoneEffect->setUserObjectID( pEffect->getUserObjectID() );
			pZoneEffect->setNextTime( pEffect->getNextTime() );
			pZoneEffect->setDeadline( pEffect->getRemainDuration() );
//			pDeadMonster->deleteEffect( Effect::EFFECT_CLASS_HARPOON_BOMB );
			pEffect->setDeadline(0);
			m_pZone->registerObject( pZoneEffect );
			m_pZone->getTile( pMonsterCorpse->getX(), pMonsterCorpse->getY() ).addEffect( pZoneEffect );
			m_pZone->addEffect( pZoneEffect );
		}
	}

	// Å©¸®Ã³°¡ Á×¾ú´Ù°í ÁÖº¯¿¡ ¾Ë·ÁÁØ´Ù.
	GCCreatureDied gcCreatureDied;
	gcCreatureDied.setObjectID(pDeadMonster->getObjectID());
	m_pZone->broadcastPacket(cx , cy , &gcCreatureDied);

	// ¸¶½ºÅÍÀÎ °æ¿ì¿¡ Á×À¸¸é¼­ ÇÑ ¸¶µð ÇÏ´Â°Å.. by sigi. 2002.9.13
	if (pDeadMonster->isMaster())
	{
		//MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pDeadMonster->getMonsterType() );
		MasterLairInfo* pMasterLairInfo = g_pMasterLairInfoManager->getMasterLairInfo( pZone->getZoneID() );

		if (pMasterLairInfo!=NULL
			&& pMasterLairInfo->getMasterMonsterType()==pDeadMonster->getMonsterType())
		{
			GCSay gcSay;
			gcSay.setObjectID( pDeadMonster->getObjectID() );
			gcSay.setColor( MASTER_SAY_COLOR );

			if (pDeadMonster->getLastHitCreatureClass() == Creature::CREATURE_CLASS_SLAYER)
			{
				gcSay.setMessage( pMasterLairInfo->getRandomMasterDeadSlayerSay() );
			}
			else
			{
				gcSay.setMessage( pMasterLairInfo->getRandomMasterDeadVampireSay() );
			}

			if (!gcSay.getMessage().empty())
				pZone->broadcastPacket(cx, cy, &gcSay);
		}
	}

	if ( pDeadMonster->getMonsterType() == 717 )
	{
		GCSay gcSay;
		gcSay.setObjectID( pDeadMonster->getObjectID() );
		gcSay.setColor( MASTER_SAY_COLOR );

		gcSay.setMessage( g_pStringPool->getString(345) );
		cout << gcSay.getMessage() << endl;
		pZone->broadcastPacket(cx, cy, &gcSay);
	}
	else if ( pDeadMonster->getMonsterType() == 723 )
	{
		GCSay gcSay;
		gcSay.setObjectID( pDeadMonster->getObjectID() );
		gcSay.setColor( MASTER_SAY_COLOR );

		gcSay.setMessage( g_pStringPool->getString(360) );
		cout << gcSay.getMessage() << endl;
		pZone->broadcastPacket(cx, cy, &gcSay);
	}

	// Å©¸®ÃÄ¸¦ »èÁ¦ÇÑ´Ù.
	SAFE_DELETE(pDeadMonster);

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// addCreature
//
// (x, y) ±ÙÃ³¿¡ 
// monsterTypeÀÇ Monster¸¦ num¸¶¸® Ãß°¡ÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
void
MonsterManager::addMonsters(ZoneCoord_t x, ZoneCoord_t y, MonsterType_t monsterType, int num, const SUMMON_INFO& summonInfo, list<Monster*>* pSummonedMonsters)
{
	TPOINT pt;

	ClanType_t clanType = CLAN_VAMPIRE_MONSTER;	// default

	// group ÀüÃ¼°¡ °°Àº clan
	if (summonInfo.clanType==SUMMON_INFO::CLAN_TYPE_RANDOM_GROUP
		|| summonInfo.clanType==SUMMON_INFO::CLAN_TYPE_GROUP)
	{
		clanType = summonInfo.clanID;//rand()%90+2;
	}

	// Á¸ÀÇ ºó ÁÂÇ¥¸¦ Ã£¾Æ³½´Ù.
	for (int i=0; i<num; i++)
	{
		pt = findSuitablePosition(m_pZone, x, y, Creature::MOVE_MODE_WALKING);

		// À§Ä¡¸¦ Ã£Áö ¸øÇß°Å³ª, ¾ÈÀüÁö´ë¶ó¸é Ãß°¡ÇÒ ¼ö ¾ø´Ù.
		if (pt.x == -1 || (m_pZone->getZoneLevel(pt.x, pt.y) & SAFE_ZONE))
		{
			return;
		}

		Monster* pMonster = NULL;

		// ¸ó½ºÅÍ °´Ã¼¸¦ »ý¼ºÇÏ°í ´É·ÂÄ¡ µîÀ» ÃÊ±âÈ­ÇÑ´Ù.
		try {

			pMonster = new Monster(monsterType);
			//cout << "¸ó½ºÅÍ Ãß°¡" << endl;

			// ¼ÒÈ¯µÈ ¸ó½ºÅÍ°¡ ¾ÆÀÌÅÛÀ» °¡Áö´Â°¡?
			pMonster->setTreasure( summonInfo.hasItem );

			////////////////////////////////////////////////////////////////////////////////
			// ¸ó½ºÅÍ¸¦ Ãß°¡ÇÏ´Â ½ÃÁ¡¿¡¼­ ÀÌº¥Æ® ¸ó½ºÅÍÀÎÁö °Ë»ç¸¦ ÇÑ´Ù.
			//  7¿ù 1ÀÏ ÀÌº¥Æ® ³¡À¸·Î Ãà±¸°ø ³ª¿ÀÁö ¾ÊÀ½
			/*
			if(rand()%g_pVariableManager->getEventRatio()==0 && 
					g_pVariableManager->getEventActivate() == 1 )
			{		
				pMonster->setEventMonsterFlag(true);
				string MonsterName = g_pMonsterNameManager->getRandomName(pMonster, true);
				pMonster->setName(MonsterName);

				//cout << "ÀÌº¥Æ® ¸ó½ºÅÍ ÀÌ¸§: " << MonsterName;
			}
			*/
			///////////////////////////////////////////////////////////////////////////

			Assert(pMonster != NULL);

			if (summonInfo.regenType==REGENTYPE_PORTAL)
			{
				// È¤½Ã ÀÌ¹Ì ¼³Á¤µÅÀÖÀ»Áöµµ ¸ð¸£´Â °ÍµéÀ» Á¦°ÅÇØÁØ´Ù.
				pMonster->removeFlag( Effect::EFFECT_CLASS_HIDE );
				pMonster->removeFlag( Effect::EFFECT_CLASS_INVISIBILITY );
				pMonster->removeFlag( Effect::EFFECT_CLASS_TRANSFORM_TO_BAT );

				pMonster->setFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);
				pMonster->setMoveMode( Creature::MOVE_MODE_WALKING );
			}

			if (summonInfo.initHPPercent!=0)
			{
				int currentHP = pMonster->getHP(ATTR_CURRENT);
				int MaxHP = currentHP * 100 / summonInfo.initHPPercent;
				pMonster->setHP(MaxHP, ATTR_MAX);
			}

		} catch (OutOfBoundException& t) {
			filelog("MonsterManagerBug.log", "addMonsters : %s", t.toString().c_str());
			SAFE_DELETE(pMonster);
			return;
		} catch (NoSuchElementException& t) {
			filelog("MonsterManagerBug.log", "addMonsters : %s", t.toString().c_str());
			SAFE_DELETE(pMonster);
			return;
		}


		try
		{
			m_pZone->addCreature(pMonster , pt.x , pt.y , Directions(rand()%8));


			// SUMMON_INFO
			if (summonInfo.clanType==SUMMON_INFO::CLAN_TYPE_RANDOM_EACH)
			{
				pMonster->setClanType( rand()%90+2 );
			}
			else
			{
				pMonster->setClanType( clanType );
			}

			//cout << "clanType=" << (int)pMonster->getClanType() << endl;

			// 
			if (summonInfo.canScanEnemy)
			{
				pMonster->setScanEnemy();

				m_pZone->monsterScan(pMonster, pt.x, pt.y, pMonster->getDir());
			}
			else if (summonInfo.scanEnemy)
			{
				m_pZone->monsterScan(pMonster, pt.x, pt.y, pMonster->getDir());
			}

			if (pSummonedMonsters!=NULL)
			{
				pSummonedMonsters->push_back( pMonster );
			}
	
		}
		catch (EmptyTileNotExistException&)
		{
			//cerr << "MonsterManager::processCreatures() : ÀÚ¸®°¡ ¾ø³×?" << endl;
			SAFE_DELETE(pMonster);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
// Á×Àº ¸ó½ºÅÍ¿¡°Ô¼­ ¾ÆÀÌÅÛÀ» »ý¼ºÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addItem(Monster* pDeadMonster, MonsterCorpse* pMonsterCorpse)
	
{
	__BEGIN_TRY

	if ( pDeadMonster->getMonsterType() == 734 )
	{
		if ( pDeadMonster->getZoneID() >= 1500 && pDeadMonster->getZoneID() <= 1506 )
		{
			ItemType_t iType = pDeadMonster->getZoneID() - min((int)pDeadMonster->getZoneID(), 1501);
			Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_CASTLE_SYMBOL, iType, list<OptionType_t>() );
			pMonsterCorpse->setZone( pDeadMonster->getZone() );
			pMonsterCorpse->addTreasure( pItem );
		}
	}

	// Äù½ºÆ® ¾ÆÀÌÅÛ Ãß°¡
	if ( pDeadMonster->getQuestItem() != NULL )
	{
		pMonsterCorpse->addTreasure( pDeadMonster->getQuestItem() );
		pDeadMonster->setQuestItem( NULL );
	}

	if ( g_pVariableManager->getVariable( PREMIUM_TRIAL_EVENT ) != 0 && pDeadMonster->getMonsterType() == 705 )
	{
		if ( rand()%100 < 30 )
		{
			int Num = 5 + (rand()%5); // 5~9
			for ( int i=0; i<Num; ++i )
			{
				Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_LUCKY_BAG, 3, list<OptionType_t>() );
				pMonsterCorpse->addTreasure( pItem );
			}
		}
	}

	// ¾ÆÀÌÅÛÀÌ ¾È ³ª¿À´Â ¸ó½ºÅÍ Ã¼Å©(==¸¶½ºÅÍ ¼ÒÈ¯ ¸ó½ºÅÍ)
	// by sigi. 2002.9.2
	if (!pDeadMonster->hasTreasure())
		return;

	MonsterType_t MonsterType = pDeadMonster->getMonsterType();
	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(MonsterType);
	TreasureList* pTreasureList = NULL;

	//----------------------------------------------------------------------
	// 2002³â Ãß¼® ÀÌº¥Æ® ¾ÆÀÌÅÛ
	// ¼ÛÆíÀÌ ÀÏÁ¤ È®·ü·Î ³ª¿Â µÚ¿¡´Â ´Ù¸¥ ¾ÆÀÌÅÛÀº ³ª¿ÀÁö ¾Ê¾Æ¾ß ÇÑ´Ù. 
	//----------------------------------------------------------------------
	bool isHarvestFestivalItemAppeared = false;
	int  PartialSumOfCakeRatio = 0;
	int  itemBonusPercent = 0;

	if (g_pVariableManager->getHarvestFestivalItemRatio() > 0 &&  rand() % g_pVariableManager->getHarvestFestivalItemRatio() == 0) 
	{
		// ¾ÆÀÌÅÛÀº 5°¡Áö Áß¿¡¼­ ³ª¿Ã ¼ö ÀÖ´Ù.
		ITEM_TEMPLATE ricecake_template;
		ricecake_template.NextOptionRatio = 0;

		bool bOK = false;
		int EventSelector = rand() % m_SumOfCakeRatio;

		for (int i=0; i<5; i++)
		{
			PartialSumOfCakeRatio += m_RICE_CAKE_PROB_RATIO[i];

			// ¸¸¾à Dice ¹æ½ÄÀ¸·Î Àû¿ëµÈ´Ù¸é
			if ( EventSelector < PartialSumOfCakeRatio)
			{
				if ( i == 0 )
				{
					if (pDeadMonster->getLastHitCreatureClass() == Creature::CREATURE_CLASS_SLAYER)
					{
						ricecake_template.ItemClass = Item::ITEM_CLASS_POTION;
						ricecake_template.ItemType  = 11;
					}
					else
					{
						ricecake_template.ItemClass = Item::ITEM_CLASS_SERUM;
						ricecake_template.ItemType  = 5;
					}
				}
				else
				{
					// º°
					ricecake_template.ItemClass = Item::ITEM_CLASS_EVENT_STAR;
					ricecake_template.ItemType = i + 7;
				}
				bOK = true;
				break;
			}
		}

		//cout << "ÀÌº¥Æ® ¾ÆÀÌÅÛ »ý¼º"  << "[" << i >> "," << EventSelector << "]" << m_SumOfCakeRatio << endl 
			 //<< "(" << ricecake_template.ItemClass << " " << ricecake_template.ItemType << ")" << endl;

		if (bOK)
		{
			Item* pItem = g_pItemFactoryManager->createItem(ricecake_template.ItemClass,ricecake_template.ItemType, ricecake_template.OptionType);

			Assert(pItem != NULL);

			pMonsterCorpse->addTreasure(pItem);

			isHarvestFestivalItemAppeared = true;
		}
	}

	//----------------------------------------------------------------------
	// Å©¸®½º¸¶½º ÆøÁ× Ãß°¡
	//----------------------------------------------------------------------
	int fireCrackerRatio = g_pVariableManager->getVariable( CHRISTMAS_FIRE_CRACKER_RATIO );
	if ( fireCrackerRatio > 0 )
	{
		int value = rand() % 10000;
		if ( value < fireCrackerRatio )
		{
			// ¼¼ °¡Áö Á¾·ùÀÇ ÆøÁ×ÀÌ ³ª¿Â´Ù.
			ItemType_t fireCrackerType = value % 3;

			// ¾ÆÀÌÅÛÀ» »ý¼ºÇÑ´Ù.
			list<OptionType_t> optionType;
			Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_ETC, fireCrackerType, optionType );

			// ¸ó½ºÅÍ ½ÃÃ¼¿¡ ³Ö´Â´Ù.
			pMonsterCorpse->addTreasure( pItem );
		}
	}
	
	//----------------------------------------------------------------------
	// Å©¸®½º¸¶½º Æ®¸® Á¶°¢ Ãß°¡
	//----------------------------------------------------------------------
	int treePartRatio = g_pVariableManager->getVariable( CHRISTMAS_TREE_PART_RATIO );
	if ( treePartRatio > 0 )
	{
		int value = rand() % 10000;
		if ( value < treePartRatio )
		{
			// 12°³ÀÇ Æ®¸® Á¶°¢ÀÌ ÀÖ´Ù.
			ItemType_t treeItemType = rand() % 12;

			// ¾ÆÀÌÅÛÀ» »ý¼ºÇÑ´Ù.
			list<OptionType_t> optionType;
			Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, treeItemType, optionType );

			// ¸ó½ºÅÍ ½ÃÃ¼¿¡ ³Ö´Â´Ù.
			pMonsterCorpse->addTreasure( pItem );
		}
	}
	int value=0;
	int PayZonecheckIn=0;
	ItemType_t treeItemType = 3;
	if ( pDeadMonster->getMonsterType() == 765 )
	{
		treeItemType = 6;
		if (pDeadMonster->getZoneID() >= 1402)
		{
			value = rand() % 250;
			PayZonecheckIn = 50;
			if ( value < PayZonecheckIn )
			{
				list<OptionType_t> optionType;
				Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, treeItemType, optionType );
				pMonsterCorpse->addTreasure( pItem );
			}
		}
		treeItemType = 3;
			for (int l=0;l<3;l++)
			{
				value = rand() % 10000;
				PayZonecheckIn = 3000;
				if ( value < PayZonecheckIn )
				{
					list<OptionType_t> optionType;
					Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MOON_CARD, treeItemType, optionType );
					pMonsterCorpse->addTreasure( pItem );
				}
			}
	}
	// end 
		
	//----------------------------------------------------------------------
	// ³ì»ö ¼±¹° »óÀÚ Ãß°¡
	//----------------------------------------------------------------------
	int giftBoxRatio = g_pVariableManager->getVariable( CHRISTMAS_GIFT_BOX_RATIO );
	if ( giftBoxRatio > 0 )
	{
		int value = rand() % 10000;
		if ( value < giftBoxRatio )
		{
			// ³ì»ö ¼±¹° »óÀÚ¸¦ »ý¼ºÇÑ´Ù.
			list<OptionType_t> optionType;
			Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 0, optionType );

			// ¸ó½ºÅÍ ½ÃÃ¼¿¡ ³Ö´Â´Ù.
			pMonsterCorpse->addTreasure( pItem );
		}
	}

	//----------------------------------------------------------------------
	// ¼±¹° »óÀÚ Ãß°¡
	//----------------------------------------------------------------------
	// º¹ÁÖ¸Ó´Ï´Â affectKillCount ¿©±â¼­ Ã³¸®ÇÏÁö¸¸
	// ¼±¹° »óÀÚ´Â Monster ÀÇ m_pQuestItem ¿¡ ³ÖÀ» °ÍÀÌ ¾Æ´Ï¹Ç·Î ¿©±â¼­ Ã³¸®ÇÑ´Ù
	// (»ç½Ç º¹ÁÖ¸Ó´Ïµµ m_pQuestItem ¿¡ ³ÖÀ» ÇÊ¿ä°¡ ¾ø±äÇÏ´Ù¸¸ ;;)
	//----------------------------------------------------------------------
	if ( g_pVariableManager->isEventGiftBox() )
	{
		if ( m_pZone != NULL )
		{
			Creature* pCreature = m_pZone->getCreature( pDeadMonster->getLastKiller() );

			if ( pCreature != NULL && pCreature->isPC() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

				if ( pPC != NULL )
				{
					Item* pItem = getGiftBoxItem( getGiftBoxKind( pPC, pDeadMonster ) );

					// GiftBox ¾ÆÀÌÅÛÀ» Ãß°¡ÇØ¾ß µÈ´Ù¸é Ãß°¡ÇÑ´Ù.
					if ( pItem != NULL )
						pMonsterCorpse->addTreasure( pItem );
				}
			}
		}
	}
	

	// ¾ÆÀÌÅÛ ¸Ô¾î¾ßÇÒ Ä³¸¯ÅÍÀÇ Á¾Á·À» µû¸¥´Ù.
	// ÇöÀç Á¸¿¡ ±× Ä³¸¯ÅÍ°¡ ¾ø´Ù¸é, 
	// ±× Ä³¸¯ÅÍÀÇ party¿¡ µû¸£°í.. ÆÄÆ¼µµ ¾ø´Ù¸é
	// LastHit¸¦ µû¸¥´Ù.
	// by sigi. 2002.10.14
	// ¸¶Áö¸·À¸·Î ÀÌ ¸ó½ºÅÍ¸¦ ¶§¸° Å©¸®ÃÄ°¡ ½½·¹ÀÌ¾î¶ó¸é ½½·¹ÀÌ¾î ¾ÆÀÌÅÛÀ» »ý¼ºÇÏ°í,
	// ¾Æ´Ï¶ó¸é µðÆúÆ®·Î ¹ìÆÄÀÌ¾î ¾ÆÀÌÅÛÀ» »ý¼ºÇÑ´Ù.
	Creature* pItemOwnerCreature = m_pZone->getPCManager()->getCreature( pDeadMonster->getHostName() );

	Creature::CreatureClass ownerCreatureClass;
	
	int luckLevel = 0;
	if (pItemOwnerCreature!=NULL)
	{
		ownerCreatureClass = pItemOwnerCreature->getCreatureClass();
		luckLevel = pItemOwnerCreature->getLuck();

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pItemOwnerCreature->getPlayer());

		if ( pGamePlayer != NULL)
			itemBonusPercent = pGamePlayer->getItemRatioBonusPoint();
	}
	else if (pDeadMonster->getHostPartyID()!=0)
	{
		Party* pParty = m_pZone->getLocalPartyManager()->getParty( pDeadMonster->getHostPartyID() );

		if (pParty!=NULL)
		{
			ownerCreatureClass = pParty->getCreatureClass();
		}
		else
		{
			ownerCreatureClass = pDeadMonster->getLastHitCreatureClass();
		}
	}
	else 
	{
		ownerCreatureClass = pDeadMonster->getLastHitCreatureClass();
	}

	// ¾ÆÀÌÅÛ ¼ÒÀ¯ÀÚÀÇ Á¾Á·¿¡ µû¶ó¼­ ¾ÆÀÌÅÛÀÇ Á¾Á· °áÁ¤ 
	if (ownerCreatureClass == Creature::CREATURE_CLASS_SLAYER)
	{
		pTreasureList = pMonsterInfo->getSlayerTreasureList();
	}
	else if (ownerCreatureClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		pTreasureList = pMonsterInfo->getVampireTreasureList();
	}
	else if (ownerCreatureClass == Creature::CREATURE_CLASS_OUSTERS)
	{
		pTreasureList = pMonsterInfo->getOustersTreasureList();
	}

	// ÀÌ ¸ó½ºÅÍ°¡ chief monsterÀÎ°¡?  by sigi. 2002.10.23
	bool bChiefMonsterBonus = pDeadMonster->isChief()
								&& g_pVariableManager->isActiveChiefMonster();


	if ( pTreasureList != NULL )
	{
		const list<Treasure*>& treasures = pTreasureList->getTreasures();

		list<Treasure*>::const_iterator itr = treasures.begin();
		for (; itr != treasures.end(); itr++)
		{
			Treasure* pTreasure = (*itr);
			ITEM_TEMPLATE it;

			it.ItemClass  = Item::ITEM_CLASS_MAX;
			it.ItemType   = 0;
			//it.OptionType = 0;

			int itemRatioBonus = 0;

			if (bChiefMonsterBonus)
			{
				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				itemRatioBonus     = g_pVariableManager->getPremiumItemProbePercent();
			}
			else
			{
				it.NextOptionRatio = 0;
			}

			Item* pItem = NULL;

			// À¯·áÈ­ Á¸¿¡¼­´Â ¾ÆÀÌÅÛ È®·üÀÌ µÎ ¹è´Ù.
			Zone* pZone = pDeadMonster->getZone();

			// ´ë¹ÚÀÌº¥Æ®°¡ Àû¿ëµÇ´Â Á¸. by sigi. 2003.1.17
			static bool isNetMarble = g_pConfig->getPropertyInt("IsNetMarble")!=0;
			bool isLottoZone = pZone->isPayPlay() || isNetMarble;

			if ( pZone->isPayPlay() 
				|| pZone->isPremiumZone())
			{
				//cout << "»ý¼ºÈ®·ü!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
			// add by sonic Ôö¼ÓÈýÊôÐÔµô±¦µØÍ¼ 2006.10.27
				if(pDeadMonster->getZoneID() == 1013)//Èç¹ûµ±Ç°µØÍ¼ÎªÉè¶¨µÄµô±¦µØÍ¼
				{
					pTreasure->setRndItemOptionMax( 3 );
				}
				else
					pTreasure->setRndItemOptionMax(2);
			// end by Sonic ÐÞ¸ÄÍê±Ï 2006.10.27
				if (pTreasure->getRandomItem(&it, itemRatioBonus + g_pVariableManager->getPremiumItemProbePercent() + itemBonusPercent ) )
				{
					// by sigi. 2002.10.21
					int upgradeLevel = upgradeItemTypeByLuck(luckLevel, ownerCreatureClass, it);
					if ( upgradeLevel != 0 )
					{
						GCAddEffectToTile gcAE;

						if ( upgradeLevel > 0 ) gcAE.setEffectID( Effect::EFFECT_CLASS_LUCKY );
						else gcAE.setEffectID( Effect::EFFECT_CLASS_MISFORTUNE );

						gcAE.setObjectID( 0 );
						gcAE.setDuration( 0 );
						gcAE.setXY( pDeadMonster->getX(), pDeadMonster->getY() );

						PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pItemOwnerCreature);
						if ( pPC != NULL )
						{
							if ( canGiveEventItem( pPC, pDeadMonster ) && !GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
							{
								if ( upgradeLevel > 0 )
									addOlympicStat( pPC, 5 );
								else
									addOlympicStat( pPC, 6 );
							}
						}

	//					cout << "ºê·ÎµåÄ³½ºÆÃ : " << pDeadMonster->getX() << ", " << pDeadMonster->getY() << endl;
						
						pZone->broadcastPacket( pDeadMonster->getX(), pDeadMonster->getY(), &gcAE );
					}

					if ( !it.OptionType.empty() )
					{
						upgradeOptionByLuck( luckLevel, ownerCreatureClass, it );
					}

					// Ä¡ÇÁ ¸ó½ºÅÍ´Â ¾ÆÀÌÅÛ 1´Ü°è +
					// by sigi. 2002.10.23
					if (bChiefMonsterBonus
						// ÀÏ´Ü rare È®·ü°ú °°°Ô °¡´Âµ¥..
						// ³ªÁß¿¡ ÀÌ°Íµµ ´Ù¸¥ variable·Î ºÐ¸®ÇØ¾ßµÉ °ÍÀÌ´Ù.	 by sigi. 2002.10.23
						&& rand()%100 < g_pVariableManager->getChiefMonsterRareItemPercent()
						&& isPossibleUpgradeItemType(it.ItemClass))
					{
						// ItemType 1´Ü°è upgrade
						int upgradeCount = 1;
			
						it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, upgradeCount);
					}

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
					it.ItemType = getItemTypeByItemLimit( it.ItemClass, it.OptionType);
#endif

					pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					Assert(pItem != NULL);
					if ( pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();

					if ( pItem->isUnique() ) pItem->setGrade(6);
					else
						pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
	//				cout << "·çÆÃ ¾ÆÀÌÅÛ µî±Þ : " << pItem->getGrade() << endl;

					pItem->setDurability( computeMaxDurability(pItem) );

					if (!isHarvestFestivalItemAppeared ||
							(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
						pMonsterCorpse->addTreasure(pItem);

					// ´ë¹ÚÀÌº¥Æ®: ÇØ°ñ 8°³ ´õ Ãß°¡
					if ( isLottoZone 
						&& pItem->getItemClass() == Item::ITEM_CLASS_SKULL )
					{
						int lottoSkullRatio = g_pVariableManager->getVariable( LOTTO_SKULL_RATIO );
						if ( lottoSkullRatio > 0 )
						{
							int value = rand() % 10000;
							if ( value < lottoSkullRatio )
							{
								// ÇØ°É 8°³ ´õ ¸¸µé¾î ³Ö´Â´Ù.
								for ( int i = 0; i < 8; i++ )
								{
									pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
									pMonsterCorpse->addTreasure( pItem );
									if ( pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();
								}
							}
						}
					}
				}
			}
			else
			{
				//cout << "»ý¼ºÈ®·ü!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
				if (pTreasure->getRandomItem(&it, g_pVariableManager->getItemProbRatio() + itemBonusPercent ))
				{
					// by sigi. 2002.10.21
					//upgradeItemTypeByLuck(luckLevel, it);
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)

					it.ItemType = getItemTypeByItemLimit( it.ItemClass, it.ItemType );
#endif
					pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					Assert(pItem != NULL);
					if ( pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();

					if ( pItem->isUnique() ) pItem->setGrade(6);
					else
						pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
	//				pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
	//				cout << "·çÆÃ ¾ÆÀÌÅÛ µî±Þ : " << pItem->getGrade() << endl;

					pItem->setDurability( computeMaxDurability(pItem) );
		
					if (!isHarvestFestivalItemAppeared ||
							(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
						pMonsterCorpse->addTreasure(pItem);

				}
			}


			/////////////////////////////////////////////////////////////////////////
			// ¾ÆÀÌÅÛ(ÇØ°ñ»©°í) ³ª¿À°í ´ë¹Ú È®·üÀÌ ÅÍÁ³´Ù¸é ¾ÆÀÌÅÛÀ» ¸î°³ ´õ ³Ö´Â´Ù. À¯·áÁ¸¸¸.
			// Ä¡ÇÁ ¸ó½ºÅÍ¿¡ Ãß°¡ ¾ÆÀÌÅÛÀÌ ¼³Á¤µÇ¾î ÀÖ´Ù¸é ±× ¼öÄ¡¸¸Å­ ¾ÆÀÌÅÛÀ» ´õ ³Ö´Â´Ù.
			int nBonusItem = 0;

			if ( pItem != NULL
				&& pItem->getItemClass() != Item::ITEM_CLASS_SKULL
				)	
			{
				if ( bChiefMonsterBonus )
					nBonusItem = g_pVariableManager->getVariable( CHIEF_ITEM_BONUS_NUM );

				if ( isLottoZone && isLottoWinning() )
					nBonusItem = g_pVariableManager->getVariable( LOTTO_ITEM_BONUS_NUM );

				if ( pDeadMonster->getMonsterType() == 765 )
					nBonusItem = 8;
				//add by sonic 2006.10.30
				if ( pDeadMonster->getZoneID() == 1013 && 
					pDeadMonster->getMonsterType() != 765 &&
					nBonusItem ==0) 
					nBonusItem =2;
				// end by sonic 2006.10.31
			}

			if ( nBonusItem > 0 )
			{
				int i = 0;
				int j = 0;
				static int MaxTry = 30;
				while ( i < nBonusItem && j < MaxTry )
				{
					Treasure* pTreasure = (*itr);
					ITEM_TEMPLATE it;

					it.ItemClass  = Item::ITEM_CLASS_MAX;
					it.ItemType   = 0;
					//it.OptionType = 0;

					int itemRatioBonus = 0;

					if (bChiefMonsterBonus || pDeadMonster->getMonsterType() == 765
						|| pDeadMonster->getZoneID() == 1013) //  add by sonic 2006.101.
					{
						it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
						itemRatioBonus     = g_pVariableManager->getPremiumItemProbePercent();
					}
					else
					{
						it.NextOptionRatio = 0;
					}

					Item* pItem = NULL;

					// À¯·áÈ­ Á¸¿¡¼­´Â ¾ÆÀÌÅÛ È®·üÀÌ µÎ ¹è´Ù.
					Zone* pZone = pDeadMonster->getZone();
					if ( pZone->isPayPlay() 
						|| pZone->isPremiumZone())
					{
						//cout << "»ý¼ºÈ®·ü!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
						if (pTreasure->getRandomItem(&it, itemRatioBonus + g_pVariableManager->getPremiumItemProbePercent() + itemBonusPercent ) )
						{
							// by sigi. 2002.10.21
							int upgradeLevel = upgradeItemTypeByLuck(luckLevel, ownerCreatureClass, it);

							if ( upgradeLevel != 0 )
							{
								GCAddEffectToTile gcAE;

								if ( upgradeLevel > 0 ) gcAE.setEffectID( Effect::EFFECT_CLASS_LUCKY );
								else gcAE.setEffectID( Effect::EFFECT_CLASS_MISFORTUNE );

								gcAE.setObjectID( 0 );
								gcAE.setDuration( 0 );
								gcAE.setXY( pDeadMonster->getX(), pDeadMonster->getY() );

								PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pItemOwnerCreature);
								if ( pPC != NULL )
								{
									if ( canGiveEventItem( pPC, pDeadMonster ) && !GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
									{
										if ( upgradeLevel > 0 )
											addOlympicStat( pPC, 5 );
										else
											addOlympicStat( pPC, 6 );
									}
								}

	//							cout << "ºê·ÎµåÄ³½ºÆÃ : " << pDeadMonster->getX() << ", " << pDeadMonster->getY() << endl;
								
								pZone->broadcastPacket( pDeadMonster->getX(), pDeadMonster->getY(), &gcAE );
							}

							// Ä¡ÇÁ ¸ó½ºÅÍ´Â ¾ÆÀÌÅÛ 1´Ü°è +
							// by sigi. 2002.10.23
							if (bChiefMonsterBonus
								// ÀÏ´Ü rare È®·ü°ú °°°Ô °¡´Âµ¥..
								// ³ªÁß¿¡ ÀÌ°Íµµ ´Ù¸¥ variable·Î ºÐ¸®ÇØ¾ßµÉ °ÍÀÌ´Ù.	 by sigi. 2002.10.23
								&& rand()%100 < g_pVariableManager->getChiefMonsterRareItemPercent()
								&& isPossibleUpgradeItemType(it.ItemClass))
							{
								// ItemType 1´Ü°è upgrade
								int upgradeCount = 1;
					
								it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, upgradeCount);
							}

							if ( !it.OptionType.empty() )
							{
								// add by sonic 2006.10.31
								if ( pDeadMonster->getZoneID() == 1013 && pDeadMonster->getMonsterType()!= 765)
									{
										upgradeOptionByLuck( 1, ownerCreatureClass, it );
									}
								else
									{
										upgradeOptionByLuck( luckLevel, ownerCreatureClass, it );
									}
								// end
								
							}

#if defined(__THAILAND_SERVER__) || defined(__CHAINA_SERVER__)
							it.ItemType	= getItemTypeByItemLimit( it.ItemClass , it.ItemType );
#endif

							pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
							Assert(pItem != NULL);
							if ( pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();
							
							if ( pItem->isUnique() ) pItem->setGrade(6);
							else
								pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
							//pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
							//cout << "·çÆÃ ¾ÆÀÌÅÛ µî±Þ : " << pItem->getGrade() << endl;

							pItem->setDurability( computeMaxDurability(pItem) );
				
							if (!isHarvestFestivalItemAppeared ||
									(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
								pMonsterCorpse->addTreasure(pItem);
						}
					}
					else
					{
						//cout << "»ý¼ºÈ®·ü!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
						if (pTreasure->getRandomItem(&it, g_pVariableManager->getItemProbRatio() + itemBonusPercent ))
						{
							// by sigi. 2002.10.21
							//upgradeItemTypeByLuck(luckLevel, it);
#if defined(__CHAINA_SERVER__) || defined(__THAILAND_SERVER__)
							it.ItemType = getItemTypeByItemLimit ( it.ItemClass, it.ItemType );
#endif
							pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
							Assert(pItem != NULL);
							if ( pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();

							if ( pItem->isUnique() ) pItem->setGrade(6);
							else
								pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
							//pItem->setGrade( ItemGradeManager::Instance().getRandomGrade() );
	//						cout << "·çÆÃ ¾ÆÀÌÅÛ µî±Þ : " << pItem->getGrade() << endl;

							pItem->setDurability( computeMaxDurability(pItem) );
				
							if (!isHarvestFestivalItemAppeared ||
									(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
								pMonsterCorpse->addTreasure(pItem);
						}
					}

					if ( pItem != NULL )
						i++;

					j++;
				}
			}
			/////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////
		}
	}

	// ÇØ°ñ ³Ö¾îÁà¾ß µÇ´Â ¸ó½ºÅ¸
	if ( pMonsterInfo->getSkullType() != 0 )
	{
		Item* pSkull = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_SKULL, pMonsterInfo->getSkullType(), list<OptionType_t>() );
		if ( pSkull != NULL )
		{
			pMonsterCorpse->addTreasure( pSkull );
		}
	}

	//////////////////////////////////////////////////////////////////////
	// 2002³â 6¿ù ¿ùµåÄÅ ÀÌº¥Æ®
	//  ÀÌº¥Æ® ¸ó½ºÅÍ·Î ¼¼ÆÃÀÌ µÈ ¸ó½ºÅÍ¿¡°Ô¼­´Â Ãà±¸°ø ¾ÆÀÌÅÛÀÌ ³ª¿Â´Ù.
	//  Ãà±¸°øÀº º°µµÀÇ ITEM_TYPEÀ» °¡ÁöÁö ¾Ê°í
	//  EVENT_STARÀÇ Type7¹øÀ¸·Î ÀÛµ¿ÇÑ´Ù.
	//  Â÷ÈÄ EventStarInfo, EventStarObject´Â EventItemInfo, EventItemObject
	//  ·Î º¯°æµÇ¾î¾ß ÇÒ °ÍÀÌ´Ù.
	/////////////////////////////////////////////////////////////////////
	/*
	if(pDeadMonster->getEventMonsterFlag() == true)
	{
		ITEM_TEMPLATE ball_template;
		ball_template.ItemClass = Item::ITEM_CLASS_EVENT_STAR;
		ball_template.ItemType = 6;
		ball_template.OptionType=0;

		//if(g_pVariable->getDebugMode() == "COUT")
			//cout << "Ãà±¸°ø ¾ÆÀÌÅÛ »ý¼º" << endl;

		Item *pItem = g_pItemFactoryManager->createItem(ball_template.ItemClass, ball_template.ItemType, ball_template.OptionType);
		Assert(pItem != NULL);
		pMonsterCorpse->addTreasure(pItem);
	}
	*/
	

	//////////////////////////////////////////////////////////////////////
	//   2002³â 5¿ù °¡Á¤ÀÇ ´Þ ÀÌº¥Æ®/
	//   ¸ðµç ¸ó½ºÅÍ¿¡°Ô¼­ º°ÀÌ ³ª¿Ã ¼ö ÀÖÀ¸¹Ç·Î, ¿©±â¿¡ ÇÏµåÄÚµùÇÏ¿´´Ù.
	//   1/1500 ÀÇ È®·ü·Î º° ¾ÆÀÌÅÛÀ» Ãß°¡·Î »ý¼ºÇÑ´Ù.(°É¸®´Â ³ðÀº Àç¼ö´Ù)
	//////////////////////////////////////////////////////////////////////
	//cout << "Monster Manager: star -> " << g_pVariable->getStar() << endl;
	//int star_percentage = g_pVariable->getStar();
    /*
	if(rand()%500 == 0) {
		ITEM_TEMPLATE star_template;
		star_template.ItemClass = Item::ITEM_CLASS_EVENT_STAR;

		// ¸ÕÀú 1/10ÀÇ È®·ü·Î »ìÆìº» ´ÙÀ½, °É¸®¸é 1/6ÀÇ È®·ü·Î °¢ º°À» ³ª¿À°Ô ÇÑ´Ù.
		// 9/10ÀÇ È®·ü·Î´Â °ËÀºº°À» Á¦¿ÜÇÑ º°¸¸ ³ª¿À°Ô ÇÑ´Ù.
		if(rand() % 1500 == 0)
			star_template.ItemType = rand() % 6;
		else
			star_template.ItemType = (rand() % 5) + 1;
		star_template.OptionType = 0;

		cout << "ÀÌº¥Æ® ¾ÆÀÌÅÛ »ý¼º" << star_template.ItemType << endl;
		Item* pItem = g_pItemFactoryManager->createItem(star_template.ItemClass,star_template.ItemType, star_template.OptionType);
		Assert(pItem != NULL);
		pMonsterCorpse->addTreasure(pItem);
	}
	*/
	__END_CATCH
}

int MonsterManager::upgradeItemTypeByLuck(int luckLevel, Creature::CreatureClass ownerCreatureClass, ITEM_TEMPLATE& it)
	
{
	__BEGIN_TRY

	if (luckLevel==0
		|| !isPossibleUpgradeItemType(it.ItemClass))
		return 0;

	luckLevel = luckLevel + (rand()%20) - 10;
	luckLevel = min(MAX_LUCK_LEVEL, luckLevel);
//	cout << "Apply luck : " << luckLevel << endl;

	int ratio;

	switch ( ownerCreatureClass )
	{
		case Creature::CREATURE_CLASS_SLAYER:
			{
				if ( luckLevel >= 0 )
				{
					ratio = (int)(( (float)luckLevel / (4.254 + (1.0 + it.ItemType)/5.0) ) * 100);
				}
				else
				{
					ratio = (int)(( (float)luckLevel / (2.5 - (1.0 + it.ItemType)/20.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_VAMPIRE:
			{
				if ( luckLevel >= 0 )
				{
					ratio = (int)(( (float)luckLevel / (6.03 + (1.0 + it.ItemType)/5.0) ) * 100);
				}
				else
				{
					ratio = (int)(( (float)luckLevel / (4.14 - (1.0 + it.ItemType)/20.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_OUSTERS:
			{
				if ( luckLevel >= 0 )
				{
					ratio = (int)(( (float)luckLevel / (4.936 + (1.0 + it.ItemType)/5.0) ) * 100);
				}
				else
				{
					ratio = (int)(( (float)luckLevel / (3.05 - (1.0 + it.ItemType)/20.0) ) * 100);
				}
			}
			break;
		default:
			return 0;
	}

	int value = rand()%10000;
//	int value = 0;//rand()%10000;

//	cout << "ratio : " << ratio << endl;
//	cout << "value : " << value << endl;

/*	const LuckInfo& luckInfo = g_pLuckInfoManager->getLuckInfo(luckLevel);

	int upgradeCount = luckInfo.getUpgradeItemTypeCount();

	if (upgradeCount==0)
		return;*/

//	cout << "before : " << it.ItemClass << "/" << (int)it.ItemType << endl;
	if ( ratio > 0 && value < ratio )
	{
		it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, 1);
//		cout << "after : " << it.ItemClass << "/" << (int)it.ItemType << endl;
		return 1;
	}
	else if ( ratio < 0 && value < (-ratio) )
	{
		it.ItemType = getDowngradeItemType(it.ItemClass, it.ItemType);
//		cout << "after : " << it.ItemClass << "/" << (int)it.ItemType << endl;
		return -1;
	}

	return 0;

	__END_CATCH
}

int MonsterManager::upgradeOptionByLuck(int luckLevel, Creature::CreatureClass ownerCreatureClass, ITEM_TEMPLATE& it) 
{
	__BEGIN_TRY

	if ( it.OptionType.empty() ) return 0;

	OptionType_t optionType = it.OptionType.front();
	OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
	if ( pOptionInfo == NULL ) return 0;

	luckLevel = luckLevel + (rand()%20) - 10;
	luckLevel = min(MAX_LUCK_LEVEL, luckLevel);
//	cout << "Apply luck to option : " << luckLevel << endl;

	int grade = pOptionInfo->getGrade() + 1;
//	cout << "Option Grade : " << grade << endl;

	int ratio;

	switch ( ownerCreatureClass )
	{
		case Creature::CREATURE_CLASS_SLAYER:
			{
				if ( luckLevel >= 0 )
				{
					ratio = (int)(( (float)luckLevel / (grade*25.0 - 15.2) ) * 100);
				}
				else
				{
					ratio = (int)(( (float)luckLevel / (7.5 - grade/2.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_VAMPIRE:
			{
				if ( luckLevel >= 0 )
				{
					ratio = (int)(( (float)luckLevel / (grade*25.0 - 11.3) ) * 100);
				}
				else
				{
					ratio = (int)(( (float)luckLevel / (10.3 - grade/2.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_OUSTERS:
			{
				if ( luckLevel >= 0 )
				{
					ratio = (int)(( (float)luckLevel / (grade/25.0 - 13.7) ) * 100);
				}
				else
				{
					ratio = (int)(( (float)luckLevel / (7.9 - grade/2.0) ) * 100);
				}
			}
			break;
		default:
			return 0;
	}

	int value = rand()%10000;
//	int value = 0;//rand()%10000;

//	cout << "ratio : " << ratio << endl;
//	cout << "value : " << value << endl;

//	cout << "before : " << pOptionInfo->getHName() << endl;

	if ( ratio > 0 && value < ratio && pOptionInfo->getUpgradeType() != optionType && pOptionInfo->isUpgradePossible() )
	{
		(*it.OptionType.begin()) = pOptionInfo->getUpgradeType();
//		cout << "after : " << g_pOptionInfoManager->getOptionInfo( it.OptionType.front() )->getHName() << endl;
		return 1;
	}
	else if ( ratio < 0 && value < (-ratio) && pOptionInfo->getPreviousType() != optionType )
	{
		if ( pOptionInfo->getPreviousType() != 0 )
			(*it.OptionType.begin()) = pOptionInfo->getPreviousType();
		else
			it.OptionType.pop_front();
//		if ( it.OptionType.front() == 0 ) it.OptionType.pop_front();
//		cout << "after : " << g_pOptionInfoManager->getOptionInfo( it.OptionType.front() )->getHName() << endl;
		return -1;
	}

	return 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// ¸ðµç Å©¸®Ã³¸¦ Á¦°ÅÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::deleteAllMonsters (bool bDeleteFromZone)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	unordered_map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

	while (current != m_Creatures.end()) 
	{
		Creature* pCreature = current->second;

		Assert(pCreature != NULL);

		if (bDeleteFromZone)
		{
			try {
				Zone* pZone = pCreature->getZone();
				Assert(m_pZone == pZone);

				//Monster* pMonster = dynamic_cast<Monster*>(pCreature);

				ZoneCoord_t cx = pCreature->getX();
				ZoneCoord_t cy = pCreature->getY();

				// Å¸ÀÏ¿¡¼­ Á¦°Å
				Tile & tile = m_pZone->getTile(cx , cy);
				tile.deleteCreature(pCreature->getObjectID());

				// ÁÖº¯ÀÇ PCµé¿¡°Ô Å©¸®Ã³°¡ »ç¶óÁ³´Ù´Â »ç½ÇÀ» ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
				GCDeleteObject gcDeleteObject(pCreature->getObjectID());
				pZone->broadcastPacket(cx, cy, &gcDeleteObject, pCreature);

			} catch (Throwable& t) {
				filelog("MonsterManagerBug.txt", "deleteAllCreatures: %s", t.toString().c_str());
			}
		}

		// Å©¸®ÃÄ¸¦ »èÁ¦ÇÑ´Ù.
		SAFE_DELETE(pCreature);

		current ++;
	}

	// ´Ù Á¦°ÅÇÑ´Ù.
	m_Creatures.clear();
	m_Monsters.clear();



	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// ¸ðµç Å©¸®Ã³¸¦ Á×ÀÎ´Ù.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::killAllMonsters (const unordered_map<ObjectID_t, ObjectID_t>& exceptCreatures)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	unordered_map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

	while (current != m_Creatures.end()) 
	{
		Creature* pCreature = current->second;

		Assert(pCreature != NULL);

		if (pCreature->isAlive())
		{
			if (pCreature->isMonster())
			{
				unordered_map<ObjectID_t, ObjectID_t>::const_iterator itr = exceptCreatures.find( pCreature->getObjectID() );

				if (itr==exceptCreatures.end())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);
					pMonster->setHP(0, ATTR_CURRENT);
				}
			}
			else Assert(false);
		}
	}

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string MonsterManager::toString () const
       
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterManager(" << CreatureManager::toString();

	unordered_map< SpriteType_t , MonsterCounter* >::const_iterator itr = m_Monsters.begin();
	for (; itr != m_Monsters.end() ; itr ++) msg << itr->second->toString();

	msg << ")" ;
	return msg.toString();

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// È²±Ý ÇØ°ñ ÁÝ±â ÀÌº¥Æ®¿¡ ¾²¿´´ø ÄÚµåÀÇ ÀÏºÎºÐÀÌ´Ù.
// ÀÏ´ÜÀº º¸±â ½È¾î¼­ »©³õ´Âµ¥, ³ªÁß¿¡¶óµµ È¤½Ã ´Ù½Ã ¾²¿©Áú±î ÇØ¼­
// ÆÄÀÏ ¸Ç ³¡À¸·Î ¿Å°Ü³õ´Â´Ù.
//////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////
// ÀÌº¥Æ® °ü·Ã ÄÚµå ½ÃÀÛ
////////////////////////////////////////////////////////////
SpriteType_t SpriteType = pMonsterInfo->getSpriteType();
uint         event_ratio = rand()%100;
uint         skull_ratio = rand()%100;

switch (SpriteType)
{
	case 5: // µ¥µå¹Ùµð
		if (event_ratio < 3) ItemType = 12;
		break;
	case 8: // ÅÍ´×µ¥µå
		if (event_ratio < 3) ItemType = 12;
		break;
	case 7: // ÅÍ´×¼Ò¿ï
		if (event_ratio < 3)
		{
			if (skull_ratio < 98) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 6: // Å°µå
		if (event_ratio < 3)
		{
			if (skull_ratio < 97) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 4: // ¼ÖÁ®
		if (event_ratio < 3)
		{
			if (skull_ratio < 96) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 9: // Ä¸Æ¾
		if (event_ratio < 3)
		{
			if (skull_ratio < 94) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 42: // ¾ËÄ­
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 43: // ·¹µå¾ÆÀÌ
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 60: // ¹ÂÅÏÆ®
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 64: // ¸ðµ¥¶ó½º
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 41: // ´õÆ¼½ºÆ®¶óÀÌ´õ
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 62: // ¿¡½ºÆ®·ÎÀÌ´õ
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 61: // À§µµ¿ìÁî
		if (event_ratio < 4)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 48: // È£ºí
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 < skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 27: // ºí·¯µå¿ö·Ï
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 40: // °ñ·¹¸Ó
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 57: // ½¦µµ¿ìÀ®
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 47: // Ä«¿À½º°¡µð¾ð
		if (event_ratio < 6)
		{
			if (skull_ratio < 89) ItemType = 12;
			else if (89 <= skull_ratio && skull_ratio < 97) ItemType = 15;
			else ItemType = 14;
		}
		break;
	default:
		break;
}
////////////////////////////////////////////////////////////
// ÀÌº¥Æ® °ü·Ã ÄÚµå ³¡
////////////////////////////////////////////////////////////
*/

bool isLottoWinning()
{
	int lottoItemRatio = g_pVariableManager->getVariable( LOTTO_ITEM_RATIO );
	if ( lottoItemRatio > 0 )
	{
		int value = rand() % 10000;
		if ( value < lottoItemRatio )
		{
			return true;
		}
	}

	return false;
}
