////////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterManager.h 
// Written By  : Reiot
// Revised by  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////


#include "MonsterManager.h"
#include <stdlib.h>			// atoi()
#include "Assert1.h"
//#include "LogClient.h"
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

#include <map>

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
// 유료화존 아이템 루팅확률 보너스 퍼센트
////////////////////////////////////////////////////////////////////////////////
//const uint g_pVariableManager->getPremiumItemProbePercent() = 220;

bool isLottoWinning();

////////////////////////////////////////////////////////////////////////////////
//
// constructor
//
////////////////////////////////////////////////////////////////////////////////
MonsterManager::MonsterManager (Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY
		
	Assert(pZone != NULL);
	m_pZone = pZone;

	Assert(g_pCastleInfoManager!=NULL);
	m_CastleZoneID = 0;
	g_pCastleInfoManager->getCastleZoneID(m_pZone->getZoneID(), m_CastleZoneID);

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
	throw()
{
	__BEGIN_TRY

	SAFE_DELETE(m_pEventMonsterInfo);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// load from database
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::load ()
	throw(Error)
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

	// 이미 있다면 기존의 MonsterCounter들을 모두 지운다.
	bool bReload = false;
	map< SpriteType_t, MonsterCounter* >::iterator iMC = m_Monsters.begin();
	while (iMC!=m_Monsters.end())
	{
		MonsterCounter* pMC = iMC->second;
		SAFE_DELETE(pMC);

		iMC ++;

		// m_Monsters가 이미 있었다면 reload한 것이다..라고 본다. by sigi. 2002.9.19
		bReload = true;
	}

	BEGIN_DB
	{
		// DynamicZone 을 위한 처리
		ZoneID_t zoneID = m_pZone->getZoneID();
		if (m_pZone->isDynamicZone() )
		{
			DynamicZone* pDynamicZone = m_pZone->getDynamicZone();
			Assert(pDynamicZone != NULL);

			zoneID = pDynamicZone->getTemplateZoneID();
		}

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
		"SELECT MonsterList, EventMonsterList from ZoneInfo WHERE ZoneID=%d", zoneID);

		if (pResult->getRowCount() <= 0) 
		{
			SAFE_DELETE(pStmt);
//			throw Error("MonsterManager::load() : 존이 존재하지 않습니다.");
			return;
		}

		pResult->next();
		text = pResult->getString(1);
		eventText = pResult->getString(2);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)


	parseMonsterList(text, bReload);
	parseEventMonsterList(eventText, bReload);

	__END_CATCH
}

void MonsterManager::parseMonsterList(const string& text, bool bReload)
	throw(Error)
{
	if (text.size() <= 0) return;

	//--------------------------------------------------------------------------------
	//
	// text 파라미터는 ZoneInfo 테이블의 Monsters (TEXT) 컬럼값을 나타낸다.
	// 포맷은 다음과 같다.
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

		// 몬스터 타입과 최대 개수를 구한다. 몬스터 타입과 최대 개수를 구한다.
		uint monsterType = atoi(text.substr(i+1,j-i-1).c_str());
		uint maxMonsters = atoi(text.substr(j+1,k-j-1).c_str());

		Assert(maxMonsters > 0);

		// 몬스터 인포로 부터 Monster Sprite Type을 받아온다.
		const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(monsterType);
		SpriteType_t spriteType = pMonsterInfo->getSpriteType();

		// 이미 존재하는지의 여부를 체크한다.
		map< SpriteType_t , MonsterCounter* >::iterator itr = m_Monsters.find(spriteType);

		if (itr != m_Monsters.end()) 
		{
			WORD CurrentMaxCount = itr->second->getMaxMonsters();
			WORD NewMaxCount = CurrentMaxCount + maxMonsters;
			itr->second->setMaxMonsters(NewMaxCount);
		} 
		else 
		{
			// 몬스터카운터 객체를 생성, map 에 등록한다.
			MonsterCounter* pMonsterCounter = new MonsterCounter(monsterType , maxMonsters, 0);

			// 존재하지 않는 경우, 추가한다.
			m_Monsters[spriteType] = pMonsterCounter;
		}

		//--------------------------------------------------------------------------------
		// 해당하는 타입의 몬스터를 존에 추가한다.
		//--------------------------------------------------------------------------------
		if (!bReload) // reload가 아니면..
		{
			for (uint m = 0 ; m < maxMonsters ; m ++) 
			{
				// 존의 빈 좌표를 찾아낸다.
				ZoneCoord_t x, y;
				if (!findPosition(monsterType, x, y))
				{
					Assert(false);
					return;
				}

				// 몬스터 객체를 생성하고 능력치 등을 초기화한다.
				Monster* pMonster = new Monster(monsterType);

				////////////////////////////////////////////////////////////////////////////////
				// 월드컵 이벤트 관련(7월 1일부터는 없어짐)
				/*
				if(rand()%g_pVariableManager->getEventRatio() == 0 &&
						g_pVariableManager->getEventActivate() == 1)
				{
				  pMonster->setEventMonsterFlag(true);
				  string MonsterName =  g_pMonsterNameManager->getRandomName(pMonster, true);
				  pMonster->setName(MonsterName);
				  //cout << "이벤트 몬스터 이름: " << pMonster->getName();
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
					//cerr << "MonsterManager::load() : 자리가 없네?" << endl;
					SAFE_DELETE(pMonster);
				}

			}
		}
	} while (k < text.size() - 1);
}

void MonsterManager::parseEventMonsterList(const string& text, bool bReload)
	throw(Error)
{
	if (text.size() <= 0) return;

	//--------------------------------------------------------------------------------
	//
	// text 파라미터는 ZoneInfo 테이블의 Monsters (TEXT) 컬럼값을 나타낸다.
	// 포맷은 다음과 같다.
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
		if (m != string::npos && n != string::npos && k < m && m < n && n < l )
		{
			tx = atoi(text.substr(m+1, n-m-1).c_str());
			ty = atoi(text.substr(n+1, l-n-1).c_str());
			//cout << "x : " << tx << endl;
			//cout << "y : " << ty << endl;
			l = m;
		}

		// 몬스터 타입과 최대 개수를 구한다. 몬스터 타입과 최대 개수를 구한다.
		uint monsterType = atoi(text.substr(i+1,j-i-1).c_str());
		uint maxMonsters = atoi(text.substr(j+1,k-j-1).c_str());
		uint regenDelay  = atoi(text.substr(k+1,l-k-1).c_str());

		Assert(maxMonsters > 0);

		//--------------------------------------------------------------------------------
		// 해당하는 타입의 몬스터를 존에 추가한다.
		//--------------------------------------------------------------------------------
		if (!bReload) // reload가 아니면..
		{
			//cout << "[MM] load EventMonsterList: [" << m_pZone->getZoneID() << "] mtype=" << monsterType
			//	<< ", maxMonsters=" << maxMonsters
			//	<< ", regenDelay=" << regenDelay << endl;
			if (m_pEventMonsterInfo==NULL)
			{
				m_pEventMonsterInfo = new vector<EventMonsterInfo>;
				//m_pEventMonsterInfo->resize(maxMonsters);
			}

			/*
			if (m_pEventMonsterInfo->size() + maxMonsters < m_pEventMonsterInfo->capacity())
			{
				m_pEventMonsterInfo->resize(m_pEventMonsterInfo->size() + maxMonsters);
			}
			*/

			for (uint m = 0 ; m < maxMonsters ; m ++) 
			{
				if (g_pVariableManager->isActiveChiefMonster())
				{
					// 존의 빈 좌표를 찾아낸다.
					ZoneCoord_t x, y;
					if (tx != -1 )
					{
						x = tx; y = ty;
					}
					else if (!findPosition(monsterType, x, y))
					{
						Assert(false);
						return;
					}

					// 몬스터 객체를 생성하고 능력치 등을 초기화한다.
					Monster* pMonster = new Monster(monsterType);
					Assert(pMonster != NULL);

					pMonster->setEventMonsterIndex(m_nEventMonster++);

					EventMonsterInfo info;
					info.monsterType = monsterType;
					info.regenDelay = regenDelay;
					info.bExist = true;
					info.x = tx;
					info.y = ty;

					m_pEventMonsterInfo->push_back(info);

					try
					{
						m_pZone->addCreature(pMonster , x , y , Directions(rand() & 0x07));

						// 그레이트 러피언
/*						if (monsterType == 764 )
						{
							static TPOINT pos[] = {
								{ 41, 52 },
								{ 72, 114 },
								{ 104, 35 } };
							// 리치젤 20마리
							for (int j=0; j<3; ++j )
							for (int i=0; i<20; ++i )
							{
								pMonster = new Monster(493 + (i%10));
								m_pZone->addCreature(pMonster , pos[j].x , pos[j].y , Directions(rand()%8));
							}
						}*/
					}
					catch (EmptyTileNotExistException&)
					{
						//cerr << "MonsterManager::load() : 자리가 없네?" << endl;
						SAFE_DELETE(pMonster);
					}
				}
				else
				{
					m_nEventMonster++;

					EventMonsterInfo info;
					info.monsterType = monsterType;
					info.regenDelay = regenDelay;
					getCurrentTime(info.regenTime);
					info.bExist = false;

					m_pEventMonsterInfo->push_back(info);
				}

			}
		}
	} while (l < text.size() - 1);


}

////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addCreature (Creature* pCreature)
	throw(DuplicatedException , Error)
{
	__BEGIN_TRY

	Monster* pMonster = dynamic_cast<Monster*>(pCreature);

	// 크리처 해쉬맵에 추가한다.
	CreatureManager::addCreature(pMonster);

	// event monster는 MonsterCounter에 들어가지 않게 한다. by sigi. 2002.10.14
	if (m_pEventMonsterInfo!=NULL 
		&& pMonster->isEventMonster())
	{
		uint index = pMonster->getEventMonsterIndex();

		if (index < m_pEventMonsterInfo->size())
		{
			EventMonsterInfo& info = (*m_pEventMonsterInfo)[index];

			getCurrentTime(info.regenTime);
			info.regenTime.tv_sec += info.regenDelay;

			info.bExist = true;
		}

		//cout << "[MM] add EventMonster: [" << pMonster->getEventMonsterIndex()
		//	<< "] = " << info.monsterType << ", delay = " << info.regenDelay << endl;
		return;
	}

	// 그런 몬스터 타입이 존에 존재할 수 있는지 체크한다.
	map< SpriteType_t , MonsterCounter* >::iterator itr = m_Monsters.find(pMonster->getSpriteType());

	if (itr == m_Monsters.end()) 
	{
		StringStream msg;
		msg << "현재 존에 존재할 수 없는 타입의 몬스터가 추가되었습니다.\n" 
			<< "현재 존은 [" << m_pZone->getZoneID() << "]입니다.\n"
			<< "추가하려고 한 몬스터의 타입은 [" << pMonster->getMonsterType() << "]입니다.\n";
		//throw Error(msg.toString());
	}
	else
	{ 
		// 몬스터 카운터를 증가시킨다.
		itr->second->addMonster();
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::deleteCreature (ObjectID_t creatureID)
	throw()//NoSuchElementException , Error)
{
	__BEGIN_TRY

	// 크리처 해쉬맵에 그런 OID 를 가진 몬스터가 존재하는지 체크한다.
	map<ObjectID_t , Creature* >::iterator itr = m_Creatures.find(creatureID);

	if (itr == m_Creatures.end()) 
	{
		cerr << "MonsterManager::deleteCreature() : NoSuchElementException" << endl;
		
		// 이것도 외부에서 제대로 처리 안되고 있는거 같다.
		// by sigi. 2002.5.9
		//throw NoSuchElementException("그런 ObjectID를 가진 몬스터는 존재하지 않습니다.");
		
		return;
	}

	Monster* pMonster = dynamic_cast<Monster*>(itr->second);

	// 크리처 해쉬맵의 해당 노드를 삭제한다.
	// 함수 끝에 있던걸 여기로 올렸다. by sigi
	// 바보야~ itr 참조는 끝내고 노드를 지워야징~. 2002.10.12 by bezz
	m_Creatures.erase(itr);


	// event monster는 MonsterCounter랑 관계없다. by sigi .2002.10.14
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

	// 몬스터 카운터에 그런 몬스터 타입이 존재하는지 체크한다.
	map< SpriteType_t , MonsterCounter *>::iterator itr2 = m_Monsters.find(pMonster->getSpriteType());

	if (itr2 == m_Monsters.end()) 
	{
		cerr << "MonsterManager::deleteCreature() : NoSuchElementException" << endl;
		//throw NoSuchElementException("그런 SpriteType을 가진 몬스터는 존재하지 않습니다.");
	}
	else 
	{
		// 몬스터의 숫자를 줄인다.
		itr2->second->deleteMonster();
	}


	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 전체의 잠재적인 적으로 인식한다. 2002.7.22 by sigi
// pAttackedMonster를 pCreature가 공격한 경우에
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addPotentialEnemy(Monster* pAttackedMonster, Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	//cout << "MonsterManager::addPotentialEnemy()" << endl;
		
	map< ObjectID_t , Creature* >::const_iterator itr = m_Creatures.begin();

	for (; itr!=m_Creatures.end(); itr++) 
	{
		Creature* pMonsterCreature = itr->second;

		// 때린 놈을 볼수 있는 거리여야 한다.
		Distance_t dist = pMonsterCreature->getDistance(pCreature->getX(), pCreature->getY());

		if (dist <= pMonsterCreature->getSight() 
			// 자신은 다른 코드에서 체크한다.
			&& pMonsterCreature!=pAttackedMonster)
		{
			Monster* pMonster = dynamic_cast<Monster*>(pMonsterCreature);
			//cout << "addPotentialEnemy: " << pMonster->getName().c_str() << endl;
			pMonster->addPotentialEnemy(pCreature);
		}
	}
		

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 전체의 적으로 인식한다. 2002.7.22 by sigi
// pAttackedMonster를 pCreature가 공격한 경우에
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addEnemy(Monster* pAttackedMonster, Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY
		
	//cout << "MonsterManager::addEnemy()" << endl;

	map< ObjectID_t , Creature* >::const_iterator itr = m_Creatures.begin();

	for (; itr!=m_Creatures.end(); itr++) 
	{
		Creature* pMonsterCreature = itr->second;

		// 때린 놈을 볼수 있는 거리여야 한다.
		Distance_t dist = pMonsterCreature->getDistance(pCreature->getX(), pCreature->getY());

		if (dist <= pMonsterCreature->getSight() 
			// 자신은 다른 코드에서 체크한다.
			&& pMonsterCreature!=pAttackedMonster)
		{
			Monster* pMonster = dynamic_cast<Monster*>(pMonsterCreature);
			//cout << "addEnemy: " << pMonster->getName().c_str() << endl;
			pMonster->addEnemy(pCreature);
		}
	}
		

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 크리처 매니저에 종속된 몬스터들의 AI에 의한 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::processCreatures ()
	throw(Error)
{
	__BEGIN_TRY

//	__BEGIN_PROFILE_MONSTER("MM_PROCESS_CREATURES");

	Timeval currentTime;
	getCurrentTime(currentTime);

	try
	{
		map< ObjectID_t , Creature* >::iterator before = m_Creatures.end();
		map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

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

					map< SpriteType_t , MonsterCounter *>::iterator itr = m_Monsters.find(pMonster->getSpriteType());

					if (itr == m_Monsters.end()) 
					{
						//cerr << "MonsterManager::processCreatures() : NoSuchElementException" << endl;
						//throw NoSuchElementException("그런 SpriteType을 가진 몬스터는 존재하지 않습니다.");
					}
					else
					{
						// 몬스터의 숫자를 줄인다.
						itr->second->deleteMonster();
					}


					// 타일과 몬스터 매니저에서 크리처를 삭제한다.
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

				/*if (pMonster->getMonsterType() == 371 ||
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
						// 몬스터 카운터를 하나 줄인다.
						map< SpriteType_t , MonsterCounter *>::iterator itr = m_Monsters.find(pMonster->getSpriteType());

						if (itr == m_Monsters.end()) 
						{
							//cerr << "MonsterManager::processCreatures() : NoSuchElementException" << endl;
							//throw NoSuchElementException("그런 SpriteType을 가진 몬스터는 존재하지 않습니다.");
						}
						else
						{
							// 몬스터의 숫자를 줄인다.
							itr->second->deleteMonster();
						}
					}

				__BEGIN_PROFILE_MONSTER("MM_CREATURE_DEADACTION");
					// 먼저 몬스터를 죽이기 전에 마지막 액션을 취하게 한다.
					pMonster->actDeadAction();
				__END_PROFILE_MONSTER("MM_CREATURE_DEADACTION");

				__BEGIN_PROFILE_MONSTER("MM_KILL_CREATURE");
					// 몬스터를 존에서 제거하고, 브로드캐스트한다.
                    killCreature(pMonster);
				__END_PROFILE_MONSTER("MM_KILL_CREATURE");

					// 몬스터에 대한 크리처의 해쉬맵의 노드를 삭제한다.
					// 잘못 삭제할 경우, 연결이 깨질 우려가 있으니 주의할 것.
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

		// 몬스터 재생 코드에 findPosition이라는 무한 루프 함수가 하나 있다.
		// 30초 동안 여러 마리의 몬스터가 죽었을 때, 이 몬스터들을 리젠할 자리를 찾는데 
		// 걸리는 시간이 길어질 수가 있다. 그리고 이 시간이 길어지면 랙이
		// 발생한다. 평균적으로는 좀 느려지더라도, 렉을 줄이기 위해서 
		// 리젠에 대한 검사를 매턴 하도록 변경한다. -- 김성민
		// 일정 주기마다 몬스터 숫자를 확인해서 리젠시켜준다.
		if (m_RegenTime < currentTime)
		{
			__BEGIN_PROFILE_MONSTER("MM_REGENERATE_CREATURES");

			regenerateCreatures();

			m_RegenTime.tv_sec  = currentTime.tv_sec + 5;	// 5초 후 리젠
			m_RegenTime.tv_usec = currentTime.tv_usec;

			__END_PROFILE_MONSTER("MM_REGENERATE_CREATURES");
		}

		// 이거 왜 주석처리 안되어있었지.. by sigi. 2002.5.3
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
// 몬스터의 숫자가 줄어들면 몬스터를 재생성한다.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::regenerateCreatures ()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// 전쟁 중에 몬스터 리젠 안되게..
	if (m_pZone->isHolyLand()) 
	{
		// 종족 전쟁 중
		if (g_pWarSystem->hasActiveRaceWar())
			return;

		// 길드 전쟁 중..
		if (m_CastleZoneID!=0 && g_pWarSystem->hasCastleActiveWar(m_CastleZoneID))
		{
			CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo(m_CastleZoneID);
			if (pCastleInfo!=NULL)
			{
				GuildID_t OwnerGuildID = pCastleInfo->getGuildID();

				// 공용성이 아닌 경우는 리젠 안한다.==공용성은 리젠 한다.
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

	// 레벨별 전쟁을 하는 중이라면 -_-;; 
	ZoneID_t zoneID = m_pZone->getZoneID(); 
	if (zoneID == 1131 || zoneID == 1132 || zoneID == 1133 || zoneID == 1134)
	{
		if (!g_pSweeperBonusManager->isAble(zoneID ) )
			return;
	}

	map<SpriteType_t, MonsterCounter*>::iterator itr = m_Monsters.begin();
	for (; itr != m_Monsters.end() ; itr ++) 
	{
		MonsterCounter* pCounter = itr->second;

		// 몬스터가 줄어들었을 경우...
		while (pCounter->getCurrentMonsters() < pCounter->getMaxMonsters()) 
		{
			SpriteType_t  SpriteType  = itr->first;
			MonsterType_t monsterType = 0;

			vector<MonsterType_t> RegenVector = g_pMonsterInfoManager->getMonsterTypeBySprite(SpriteType);
			Assert(RegenVector.size() > 0);

			monsterType = RegenVector[rand()%RegenVector.size()];

			// 존의 빈 좌표를 찾아낸다.
			ZoneCoord_t x, y;
			if (!findPosition(monsterType, x, y))
			{
				Assert(false);
				return;
			}

			// 몬스터 객체를 생성하고 능력치 등을 초기화한다.
			Monster* pMonster = new Monster(monsterType);
			Assert(pMonster != NULL);

			/////////////////////////////////////////////////////////////////////
			// 몬스터를 추가하는 시점에서 이벤트 몬스터인지 검사를 한다.
			///  7월 1일자로 삭제 (월드컵 이벤트 끝)
			/*
			if(rand()%g_pVariableManager->getEventRatio()==0 && 
					g_pVariableManager->getEventActivate() == 1 )
			{		
				pMonster->setEventMonsterFlag(true);
				string MonsterName = g_pMonsterNameManager->getRandomName(pMonster, true);
				pMonster->setName(MonsterName);

				//cout << "이벤트 몬스터 이름: " << MonsterName;
			}
			*/
			/////////////////////////////////////////////////////////////////////

			try
			{
				m_pZone->addCreature(pMonster , x , y , Directions(rand()%8));
			}
			catch (EmptyTileNotExistException&)
			{
				//cerr << "MonsterManager::processCreatures() : 자리가 없네?" << endl;
				SAFE_DELETE(pMonster);
			}
		}
	}

	if (g_pVariableManager->isActiveChiefMonster()
		&& m_pEventMonsterInfo!=NULL)
	{
		Timeval currentTime;
		getCurrentTime(currentTime);

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

				// 존의 빈 좌표를 찾아낸다.
				ZoneCoord_t x, y;
				if (info.x != -1 )
				{
					x = info.x;
					y = info.y;
				}
				else if (!findPosition(monsterType, x, y))
				{
					Assert(false);
					return;
				}

				// 몬스터 객체를 생성하고 능력치 등을 초기화한다.
				Monster* pMonster = new Monster(monsterType);
				Assert(pMonster != NULL);

				pMonster->setEventMonsterIndex(i);

				try
				{
					m_pZone->addCreature(pMonster , x , y , Directions(rand()%8));

					// 그레이트 러피언
/*					if (monsterType == 764 )
					{
						static TPOINT pos[] = {
							{ 41, 52 },
							{ 72, 114 },
							{ 104, 35 } };
						// 리치젤 20마리
						for (int j=0; j<3; ++j )
						for (int i=0; i<20; ++i )
						{
							pMonster = new Monster(493 + (i%10));
							m_pZone->addCreature(pMonster , pos[j].x , pos[j].y , Directions(rand()%8));
						}
					}*/
				}
				catch (EmptyTileNotExistException&)
				{
					//cerr << "MonsterManager::processCreatures() : 자리가 없네?" << endl;
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
	throw()
{
	__BEGIN_TRY

	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(monsterType);

	int count = 0;

/*	if (monsterType == 722 )
	{
		// 질드레 석상 -_-;;
		RX = 94;
		RY = 172;
		return true;
	}*/

	// 무한 루프인데... 혹시라도 문제가 있을까?
	while (true)
	{
		const BPOINT& pt = m_pZone->getRandomMonsterRegenPosition();

		Tile& rTile = m_pZone->getTile(pt.x,pt.y);

		// 1. 타일이 블록되어 있지 않고
		// 2. 타일에 포탈이 존재하지 않으며,
		// 3. 안전지대가 아니라면
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
			throw("MonsterManager::findPosition() : Max Count Exceeded");
		}
	}

	// 위에서 무한 루프니까, 여기까지 못 오겠지?
	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 죽은 크리처를 처리한다.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::killCreature (Creature* pDeadCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pDeadCreature->isDead());

	Zone* pZone = pDeadCreature->getZone();
	Assert(m_pZone == pZone);

	Monster* pDeadMonster = dynamic_cast<Monster*>(pDeadCreature);
	ZoneCoord_t cx = pDeadMonster->getX();
	ZoneCoord_t cy = pDeadMonster->getY();

	// 죽었으니까 우선권을 계산해준다.
	PrecedenceTable* pTable = pDeadMonster->getPrecedenceTable();
	
	pTable->compute();

	if (pTable->getHostName() == "" )
	{
		// 아무도 때린 넘이 없다면 아이템을 안 넣는다.
		pDeadMonster->setTreasure(false);
	}
	else
	{
		pDeadMonster->setHostName(pTable->getHostName());
		pDeadMonster->setHostPartyID(pTable->getHostPartyID());
	}

	// 먼저 바닥에 쓰러뜨리라고, 이펙트를 뿌린다.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pDeadCreature->getObjectID());
	gcAddEffect.setEffectID(Effect::EFFECT_CLASS_COMA);
	gcAddEffect.setDuration(0);
	pZone->broadcastPacket(cx, cy, &gcAddEffect);

	// 몬스터 제거
	Tile & tile = m_pZone->getTile(cx , cy);
	tile.deleteCreature(pDeadMonster->getObjectID());

	// DynamicZone 일경우의 처리
	if (m_pZone->isDynamicZone() )
	{
		DynamicZone* pDynamicZone = m_pZone->getDynamicZone();
		Assert(pDynamicZone != NULL);

		if (pDynamicZone->getTemplateZoneID() == 4001 )
		{
			// 제단의 입구의 경우 처리
			DynamicZoneGateOfAlter* pGateOfAlter = dynamic_cast<DynamicZoneGateOfAlter*>(pDynamicZone);
			Assert(pGateOfAlter != NULL);

			pGateOfAlter->removeEffect(cx, cy);
		}
	}

	// 그라운드 엘리멘탈은 시체도 없지롱
	if (pDeadMonster->getMonsterType() == GROUND_ELEMENTAL_TYPE )
	{
		GCDeleteObject* pGCDO = new GCDeleteObject;
		pGCDO->setObjectID(pDeadMonster->getObjectID());

		EffectPacketSend* pEffectPacketSend = new EffectPacketSend(pDeadMonster->getZone(), pDeadMonster->getX(), pDeadMonster->getY());
		pEffectPacketSend->setPacket(pGCDO);
		// 1초 뒤에 패킷 보내야쥐~
		pEffectPacketSend->setDeadline(10);
		pDeadMonster->getZone()->registerObject(pEffectPacketSend);
		pDeadMonster->getZone()->addEffect(pEffectPacketSend);

		SAFE_DELETE(pDeadMonster);
		return;
	}
	else if (pDeadMonster->getMonsterType() == 764 )
	{
		// 그레이트 러피언
		GCDeleteObject* pGCDO = new GCDeleteObject;
		pGCDO->setObjectID(pDeadMonster->getObjectID());

		EffectPacketSend* pEffectPacketSend = new EffectPacketSend(pDeadMonster->getZone(), pDeadMonster->getX(), pDeadMonster->getY());
		pEffectPacketSend->setPacket(pGCDO);
		// 1초 뒤에 패킷 보내야쥐~
		pEffectPacketSend->setDeadline(10);
		pDeadMonster->getZone()->registerObject(pEffectPacketSend);
		pDeadMonster->getZone()->addEffect(pEffectPacketSend);

		Monster* pNewMonster = new Monster(765);
		pNewMonster->setClanType(pDeadMonster->getClanType());
		pNewMonster->setEventMonsterIndex(pDeadMonster->getEventMonsterIndex());
		pNewMonster->setName(pDeadMonster->getName());
		pDeadMonster->getZone()->addCreature(pNewMonster, pDeadMonster->getX(), pDeadMonster->getY(), pDeadMonster->getDir());

		SAFE_DELETE(pDeadMonster);
		return;
	}
	else if (pDeadMonster->getMonsterType() == 793
			|| pDeadMonster->getMonsterType() == 794
			|| pDeadMonster->getMonsterType() == 795 )
	{
		// 슬레이어, 뱀파이어, 아우스터즈 제물도 시체 엄꼬
		// 바로 없애 버린다.
		GCDeleteObject gcDO;
		gcDO.setObjectID(pDeadMonster->getObjectID());
		pDeadMonster->getZone()->broadcastPacket(pDeadMonster->getX(), pDeadMonster->getY(), &gcDO);

		SAFE_DELETE(pDeadMonster);
		return;
	}

	// 시체 객체를 생성하고, OID 를 할당받는다.
	MonsterCorpse* pMonsterCorpse = new MonsterCorpse(pDeadMonster);
	pMonsterCorpse->setHostName(pDeadMonster->getHostName());
	pMonsterCorpse->setHostPartyID(pDeadMonster->getHostPartyID());
	pMonsterCorpse->setQuestHostName(pTable->getQuestHostName());
	pMonsterCorpse->setLevel((int)(pDeadMonster->getLevel()));
	pMonsterCorpse->setExp((Exp_t)computeCreatureExp(pDeadMonster, 100));
	pMonsterCorpse->setLastKiller(pDeadMonster->getLastKiller());

	// 죽은 몬스터 종류에 따라서 시체에 아이템을 추가해둔다.
	addItem(pDeadMonster, pMonsterCorpse);

	// by sigi. 2002.12.12
	addCorpseToZone(pMonsterCorpse, m_pZone, cx, cy);

	if (pDeadMonster->isFlag(Effect::EFFECT_CLASS_HARPOON_BOMB ) )
	{
		EffectHarpoonBomb* pEffect = dynamic_cast<EffectHarpoonBomb*>(pDeadMonster->findEffect(Effect::EFFECT_CLASS_HARPOON_BOMB ));
		if (pEffect != NULL )
		{
			EffectHarpoonBomb* pZoneEffect = new EffectHarpoonBomb(m_pZone, pMonsterCorpse->getX(), pMonsterCorpse->getY());
			pZoneEffect->setDamage(pEffect->getDamage());
			pZoneEffect->setUserObjectID(pEffect->getUserObjectID());
			pZoneEffect->setNextTime(pEffect->getNextTime());
			pZoneEffect->setDeadline(pEffect->getRemainDuration());
//			pDeadMonster->deleteEffect(Effect::EFFECT_CLASS_HARPOON_BOMB);
			pEffect->setDeadline(0);
			m_pZone->registerObject(pZoneEffect);
			m_pZone->getTile(pMonsterCorpse->getX(), pMonsterCorpse->getY() ).addEffect(pZoneEffect);
			m_pZone->addEffect(pZoneEffect);
		}
	}

	// 크리처가 죽었다고 주변에 알려준다.
	GCCreatureDied gcCreatureDied;
	gcCreatureDied.setObjectID(pDeadMonster->getObjectID());
	m_pZone->broadcastPacket(cx , cy , &gcCreatureDied);

	// 마스터인 경우에 죽으면서 한 마디 하는거.. by sigi. 2002.9.13
	if (pDeadMonster->isMaster())
	{
		//MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(pDeadMonster->getMonsterType());
		MasterLairInfo* pMasterLairInfo = g_pMasterLairInfoManager->getMasterLairInfo(pZone->getZoneID());

		if (pMasterLairInfo!=NULL
			&& pMasterLairInfo->getMasterMonsterType()==pDeadMonster->getMonsterType())
		{
			GCSay gcSay;
			gcSay.setObjectID(pDeadMonster->getObjectID());
			gcSay.setColor(MASTER_SAY_COLOR);

			if (pDeadMonster->getLastHitCreatureClass() == Creature::CREATURE_CLASS_SLAYER)
			{
				gcSay.setMessage(pMasterLairInfo->getRandomMasterDeadSlayerSay());
			}
			else
			{
				gcSay.setMessage(pMasterLairInfo->getRandomMasterDeadVampireSay());
			}

			if (!gcSay.getMessage().empty())
				pZone->broadcastPacket(cx, cy, &gcSay);
		}
	}

	if (pDeadMonster->getMonsterType() == 717 )
	{
		GCSay gcSay;
		gcSay.setObjectID(pDeadMonster->getObjectID());
		gcSay.setColor(MASTER_SAY_COLOR);

		gcSay.setMessage(g_pStringPool->getString(345));
		//cout << gcSay.getMessage() << endl;
		pZone->broadcastPacket(cx, cy, &gcSay);
	}
	else if (pDeadMonster->getMonsterType() == 723 )
	{
		GCSay gcSay;
		gcSay.setObjectID(pDeadMonster->getObjectID());
		gcSay.setColor(MASTER_SAY_COLOR);

		gcSay.setMessage(g_pStringPool->getString(360));
		//cout << gcSay.getMessage() << endl;
		pZone->broadcastPacket(cx, cy, &gcSay);
	}

	// 크리쳐를 삭제한다.
	SAFE_DELETE(pDeadMonster);

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// addCreature
//
// (x, y) 근처에 
// monsterType의 Monster를 num마리 추가한다.
////////////////////////////////////////////////////////////////////////////////
void
MonsterManager::addMonsters(ZoneCoord_t x, ZoneCoord_t y, MonsterType_t monsterType, int num, const SUMMON_INFO& summonInfo, list<Monster*>* pSummonedMonsters)
{
	TPOINT pt;

	ClanType_t clanType = CLAN_VAMPIRE_MONSTER;	// default

	// group 전체가 같은 clan
	if (summonInfo.clanType==SUMMON_INFO::CLAN_TYPE_RANDOM_GROUP
		|| summonInfo.clanType==SUMMON_INFO::CLAN_TYPE_GROUP)
	{
		clanType = summonInfo.clanID;//rand()%90+2;
	}

	// 존의 빈 좌표를 찾아낸다.
	for (int i=0; i<num; i++)
	{
		pt = findSuitablePosition(m_pZone, x, y, Creature::MOVE_MODE_WALKING);

		// 위치를 찾지 못했거나, 안전지대라면 추가할 수 없다.
		if (pt.x == -1 || (m_pZone->getZoneLevel(pt.x, pt.y) & SAFE_ZONE))
		{
			return;
		}

		Monster* pMonster = NULL;

		// 몬스터 객체를 생성하고 능력치 등을 초기화한다.
		try {

			pMonster = new Monster(monsterType);
			//cout << "몬스터 추가" << endl;

			// 소환된 몬스터가 아이템을 가지는가?
			pMonster->setTreasure(summonInfo.hasItem);

			////////////////////////////////////////////////////////////////////////////////
			// 몬스터를 추가하는 시점에서 이벤트 몬스터인지 검사를 한다.
			//  7월 1일 이벤트 끝으로 축구공 나오지 않음
			/*
			if(rand()%g_pVariableManager->getEventRatio()==0 && 
					g_pVariableManager->getEventActivate() == 1 )
			{		
				pMonster->setEventMonsterFlag(true);
				string MonsterName = g_pMonsterNameManager->getRandomName(pMonster, true);
				pMonster->setName(MonsterName);

				//cout << "이벤트 몬스터 이름: " << MonsterName;
			}
			*/
			///////////////////////////////////////////////////////////////////////////

			Assert(pMonster != NULL);

			if (summonInfo.regenType==REGENTYPE_PORTAL)
			{
				// 혹시 이미 설정돼있을지도 모르는 것들을 제거해준다.
				pMonster->removeFlag(Effect::EFFECT_CLASS_HIDE);
				pMonster->removeFlag(Effect::EFFECT_CLASS_INVISIBILITY);
				pMonster->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);

				pMonster->setFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);
				pMonster->setMoveMode(Creature::MOVE_MODE_WALKING);
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
				pMonster->setClanType(rand()%90+2);
			}
			else
			{
				pMonster->setClanType(clanType);
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
				pSummonedMonsters->push_back(pMonster);
			}
	
		}
		catch (EmptyTileNotExistException&)
		{
			//cerr << "MonsterManager::processCreatures() : 자리가 없네?" << endl;
			SAFE_DELETE(pMonster);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
// 죽은 몬스터에게서 아이템을 생성한다.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::addItem(Monster* pDeadMonster, MonsterCorpse* pMonsterCorpse)
	throw(Error)
{
	__BEGIN_TRY

	if (pDeadMonster->getMonsterType() == 734 )
	{
		if (pDeadMonster->getZoneID() >= 1500 && pDeadMonster->getZoneID() <= 1506 )
		{
			ItemType_t iType = pDeadMonster->getZoneID() - min((int)pDeadMonster->getZoneID(), 1501);
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_CASTLE_SYMBOL, iType, list<OptionType_t>());
			pMonsterCorpse->setZone(pDeadMonster->getZone());
			pMonsterCorpse->addTreasure(pItem);
		}
	}

	// 퀘스트 아이템 추가
	if (pDeadMonster->getQuestItem() != NULL )
	{
		pMonsterCorpse->addTreasure(pDeadMonster->getQuestItem());
		pDeadMonster->setQuestItem(NULL);
	}

	if (g_pVariableManager->getVariable(PREMIUM_TRIAL_EVENT ) != 0 && pDeadMonster->getMonsterType() == 705 )
	{
		if (rand()%100 < 30 )
		{
			int Num = 5 + (rand()%5); // 5~9
			for (int i=0; i<Num; ++i )
			{
				Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_LUCKY_BAG, 3, list<OptionType_t>());
				pMonsterCorpse->addTreasure(pItem);
			}
		}
	}

	// 아이템이 안 나오는 몬스터 체크(==마스터 소환 몬스터)
	// by sigi. 2002.9.2
	if (!pDeadMonster->hasTreasure())
		return;

	MonsterType_t MonsterType = pDeadMonster->getMonsterType();
	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(MonsterType);
	TreasureList* pTreasureList = NULL;

	//----------------------------------------------------------------------
	// 2002년 추석 이벤트 아이템
	// 송편이 일정 확률로 나온 뒤에는 다른 아이템은 나오지 않아야 한다. 
	//----------------------------------------------------------------------
	bool isHarvestFestivalItemAppeared = false;
	int  PartialSumOfCakeRatio = 0;
	int  itemBonusPercent = 0;

	if (g_pVariableManager->getHarvestFestivalItemRatio() > 0 &&  rand() % g_pVariableManager->getHarvestFestivalItemRatio() == 0) 
	{
		// 아이템은 5가지 중에서 나올 수 있다.
		ITEM_TEMPLATE ricecake_template;
		ricecake_template.NextOptionRatio = 0;

		bool bOK = false;
		int EventSelector = rand() % m_SumOfCakeRatio;

		for (int i=0; i<5; i++)
		{
			PartialSumOfCakeRatio += m_RICE_CAKE_PROB_RATIO[i];

			// 만약 Dice 방식으로 적용된다면
			if (EventSelector < PartialSumOfCakeRatio)
			{
				if (i == 0 )
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
					// 별
					ricecake_template.ItemClass = Item::ITEM_CLASS_EVENT_STAR;
					ricecake_template.ItemType = i + 7;
				}
				bOK = true;
				break;
			}
		}

		//cout << "이벤트 아이템 생성"  << "[" << i >> "," << EventSelector << "]" << m_SumOfCakeRatio << endl 
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
	// 크리스마스 폭죽 추가
	//----------------------------------------------------------------------
	int fireCrackerRatio = g_pVariableManager->getVariable(CHRISTMAS_FIRE_CRACKER_RATIO);
	if (fireCrackerRatio > 0 )
	{
		int value = rand() % 10000;
		if (value < fireCrackerRatio )
		{
			// 세 가지 종류의 폭죽이 나온다.
			ItemType_t fireCrackerType = value % 3;

			// 아이템을 생성한다.
			list<OptionType_t> optionType;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ETC, fireCrackerType, optionType);

			// 몬스터 시체에 넣는다.
			pMonsterCorpse->addTreasure(pItem);
		}
	}
	
	//----------------------------------------------------------------------
	// 크리스마스 트리 조각 추가
	//----------------------------------------------------------------------
	int treePartRatio = g_pVariableManager->getVariable(CHRISTMAS_TREE_PART_RATIO);
	if (treePartRatio > 0 )
	{
		int value = rand() % 10000;
		if (value < treePartRatio )
		{
			// 12개의 트리 조각이 있다.
			ItemType_t treeItemType = rand() % 12;

			// 아이템을 생성한다.
			list<OptionType_t> optionType;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_TREE, treeItemType, optionType);

			// 몬스터 시체에 넣는다.
			pMonsterCorpse->addTreasure(pItem);
		}
	}
		
	//----------------------------------------------------------------------
	// 녹색 선물 상자 추가
	//----------------------------------------------------------------------
	int giftBoxRatio = g_pVariableManager->getVariable(CHRISTMAS_GIFT_BOX_RATIO);
	if (giftBoxRatio > 0 )
	{
		int value = rand() % 10000;
		if (value < giftBoxRatio )
		{
			// 녹색 선물 상자를 생성한다.
			list<OptionType_t> optionType;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_GIFT_BOX, 0, optionType);

			// 몬스터 시체에 넣는다.
			pMonsterCorpse->addTreasure(pItem);
		}
	}

	//----------------------------------------------------------------------
	// 선물 상자 추가
	//----------------------------------------------------------------------
	// 복주머니는 affectKillCount 여기서 처리하지만
	// 선물 상자는 Monster 의 m_pQuestItem 에 넣을 것이 아니므로 여기서 처리한다
	// (사실 복주머니도 m_pQuestItem 에 넣을 필요가 없긴하다만 ;;)
	//----------------------------------------------------------------------
	if (g_pVariableManager->isEventGiftBox() )
	{
		if (m_pZone != NULL )
		{
			Creature* pCreature = m_pZone->getCreature(pDeadMonster->getLastKiller());

			if (pCreature != NULL && pCreature->isPC() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

				if (pPC != NULL )
				{
					Item* pItem = getGiftBoxItem(getGiftBoxKind(pPC, pDeadMonster ));

					// GiftBox 아이템을 추가해야 된다면 추가한다.
					if (pItem != NULL )
						pMonsterCorpse->addTreasure(pItem);
				}
			}
		}
	}
	

	// 아이템 먹어야할 캐릭터의 종족을 따른다.
	// 현재 존에 그 캐릭터가 없다면, 
	// 그 캐릭터의 party에 따르고.. 파티도 없다면
	// LastHit를 따른다.
	// by sigi. 2002.10.14
	// 마지막으로 이 몬스터를 때린 크리쳐가 슬레이어라면 슬레이어 아이템을 생성하고,
	// 아니라면 디폴트로 뱀파이어 아이템을 생성한다.
	Creature* pItemOwnerCreature = m_pZone->getPCManager()->getCreature(pDeadMonster->getHostName());

	Creature::CreatureClass ownerCreatureClass;
	
	int luckLevel = 0;
	if (pItemOwnerCreature!=NULL)
	{
		ownerCreatureClass = pItemOwnerCreature->getCreatureClass();
		luckLevel = pItemOwnerCreature->getLuck();

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pItemOwnerCreature->getPlayer());

		if (pGamePlayer != NULL)
			itemBonusPercent = pGamePlayer->getItemRatioBonusPoint();
	}
	else if (pDeadMonster->getHostPartyID()!=0)
	{
		Party* pParty = m_pZone->getLocalPartyManager()->getParty(pDeadMonster->getHostPartyID());

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

	// 아이템 소유자의 종족에 따라서 아이템의 종족 결정 
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

	// 이 몬스터가 chief monster인가?  by sigi. 2002.10.23
	bool bChiefMonsterBonus = pDeadMonster->isChief()
								&& g_pVariableManager->isActiveChiefMonster();


	if (pTreasureList != NULL )
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

			// 유료화 존에서는 아이템 확률이 두 배다.
			Zone* pZone = pDeadMonster->getZone();

			// 대박이벤트가 적용되는 존. by sigi. 2003.1.17
			static bool isNetMarble = g_pConfig->getPropertyInt("IsNetMarble")!=0;
			bool isLottoZone = pZone->isPayPlay() || isNetMarble;

			if (pZone->isPayPlay() 
				|| pZone->isPremiumZone())
			{
				//cout << "생성확률!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
				if (pTreasure->getRandomItem(&it, itemRatioBonus + g_pVariableManager->getPremiumItemProbePercent() + itemBonusPercent ) )
				{
					// by sigi. 2002.10.21
					int upgradeLevel = upgradeItemTypeByLuck(luckLevel, ownerCreatureClass, it);
					if (upgradeLevel != 0 )
					{
						GCAddEffectToTile gcAE;

						if (upgradeLevel > 0 ) gcAE.setEffectID(Effect::EFFECT_CLASS_LUCKY);
						else gcAE.setEffectID(Effect::EFFECT_CLASS_MISFORTUNE);

						gcAE.setObjectID(0);
						gcAE.setDuration(0);
						gcAE.setXY(pDeadMonster->getX(), pDeadMonster->getY());

						PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pItemOwnerCreature);
						if (pPC != NULL )
						{
							if (canGiveEventItem(pPC, pDeadMonster ) && !GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
							{
								if (upgradeLevel > 0 )
									addOlympicStat(pPC, 5);
								else
									addOlympicStat(pPC, 6);
							}
						}

	//					cout << "브로드캐스팅 : " << pDeadMonster->getX() << ", " << pDeadMonster->getY() << endl;
						
						pZone->broadcastPacket(pDeadMonster->getX(), pDeadMonster->getY(), &gcAE);
					}

					if (!it.OptionType.empty() )
					{
						upgradeOptionByLuck(luckLevel, ownerCreatureClass, it);
					}

					// 치프 몬스터는 아이템 1단계 +
					// by sigi. 2002.10.23
					if (bChiefMonsterBonus
						// 일단 rare 확률과 같게 가는데..
						// 나중에 이것도 다른 variable로 분리해야될 것이다.	 by sigi. 2002.10.23
						&& rand()%100 < g_pVariableManager->getChiefMonsterRareItemPercent()
						&& isPossibleUpgradeItemType(it.ItemClass))
					{
						// ItemType 1단계 upgrade
						int upgradeCount = 1;
			
						it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, upgradeCount);
					}
/*
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
					it.ItemType = getItemTypeByItemLimit(it.ItemClass, it.OptionType);
#endif
*/
					pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					Assert(pItem != NULL);
					if (pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();

					if (pItem->isUnique() ) pItem->setGrade(6);
					else
						pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
	//				cout << "루팅 아이템 등급 : " << pItem->getGrade() << endl;

					pItem->setDurability(computeMaxDurability(pItem));

					if (!isHarvestFestivalItemAppeared ||
							(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
						pMonsterCorpse->addTreasure(pItem);

					// 대박이벤트: 해골 8개 더 추가
					if (isLottoZone 
						&& pItem->getItemClass() == Item::ITEM_CLASS_SKULL )
					{
						int lottoSkullRatio = g_pVariableManager->getVariable(LOTTO_SKULL_RATIO);
						if (lottoSkullRatio > 0 )
						{
							int value = rand() % 10000;
							if (value < lottoSkullRatio )
							{
								// 해걸 8개 더 만들어 넣는다.
								for (int i = 0; i < 8; i++ )
								{
									pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
									pMonsterCorpse->addTreasure(pItem);
									if (pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();
								}
							}
						}
					}
				}
			}
			else
			{
				//cout << "생성확률!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
				if (pTreasure->getRandomItem(&it, g_pVariableManager->getItemProbRatio() + itemBonusPercent ))
				{
					// by sigi. 2002.10.21
					//upgradeItemTypeByLuck(luckLevel, it);
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)

					it.ItemType = getItemTypeByItemLimit(it.ItemClass, it.ItemType);
#endif
					pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					Assert(pItem != NULL);
					if (pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();

					if (pItem->isUnique() ) pItem->setGrade(6);
					else
						pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
	//				pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
	//				cout << "루팅 아이템 등급 : " << pItem->getGrade() << endl;

					pItem->setDurability(computeMaxDurability(pItem));
		
					if (!isHarvestFestivalItemAppeared ||
							(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
						pMonsterCorpse->addTreasure(pItem);

				}
			}


			/////////////////////////////////////////////////////////////////////////
			// 아이템(해골빼고) 나오고 대박 확률이 터졌다면 아이템을 몇개 더 넣는다. 유료존만.
			// 치프 몬스터에 추가 아이템이 설정되어 있다면 그 수치만큼 아이템을 더 넣는다.
			int nBonusItem = 0;

			if (pItem != NULL
				&& pItem->getItemClass() != Item::ITEM_CLASS_SKULL
				)	
			{
				if (bChiefMonsterBonus )
					nBonusItem = g_pVariableManager->getVariable(CHIEF_ITEM_BONUS_NUM);

				if (isLottoZone && isLottoWinning() )
					nBonusItem = g_pVariableManager->getVariable(LOTTO_ITEM_BONUS_NUM);

				if (pDeadMonster->getMonsterType() == 765 )
					nBonusItem = 8;
			}

			if (nBonusItem > 0 )
			{
				int i = 0;
				int j = 0;
				static int MaxTry = 30;
				while (i < nBonusItem && j < MaxTry )
				{
					Treasure* pTreasure = (*itr);
					ITEM_TEMPLATE it;

					it.ItemClass  = Item::ITEM_CLASS_MAX;
					it.ItemType   = 0;
					//it.OptionType = 0;

					int itemRatioBonus = 0;

					if (bChiefMonsterBonus || pDeadMonster->getMonsterType() == 765)
					{
						it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
						itemRatioBonus     = g_pVariableManager->getPremiumItemProbePercent();
					}
					else
					{
						it.NextOptionRatio = 0;
					}

					Item* pItem = NULL;

					// 유료화 존에서는 아이템 확률이 두 배다.
					Zone* pZone = pDeadMonster->getZone();
					if (pZone->isPayPlay() 
						|| pZone->isPremiumZone())
					{
						//cout << "생성확률!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
						if (pTreasure->getRandomItem(&it, itemRatioBonus + g_pVariableManager->getPremiumItemProbePercent() + itemBonusPercent ) )
						{
							// by sigi. 2002.10.21
							int upgradeLevel = upgradeItemTypeByLuck(luckLevel, ownerCreatureClass, it);

							if (upgradeLevel != 0 )
							{
								GCAddEffectToTile gcAE;

								if (upgradeLevel > 0 ) gcAE.setEffectID(Effect::EFFECT_CLASS_LUCKY);
								else gcAE.setEffectID(Effect::EFFECT_CLASS_MISFORTUNE);

								gcAE.setObjectID(0);
								gcAE.setDuration(0);
								gcAE.setXY(pDeadMonster->getX(), pDeadMonster->getY());

								PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pItemOwnerCreature);
								if (pPC != NULL )
								{
									if (canGiveEventItem(pPC, pDeadMonster ) && !GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
									{
										if (upgradeLevel > 0 )
											addOlympicStat(pPC, 5);
										else
											addOlympicStat(pPC, 6);
									}
								}

	//							cout << "브로드캐스팅 : " << pDeadMonster->getX() << ", " << pDeadMonster->getY() << endl;
								
								pZone->broadcastPacket(pDeadMonster->getX(), pDeadMonster->getY(), &gcAE);
							}

							// 치프 몬스터는 아이템 1단계 +
							// by sigi. 2002.10.23
							if (bChiefMonsterBonus
								// 일단 rare 확률과 같게 가는데..
								// 나중에 이것도 다른 variable로 분리해야될 것이다.	 by sigi. 2002.10.23
								&& rand()%100 < g_pVariableManager->getChiefMonsterRareItemPercent()
								&& isPossibleUpgradeItemType(it.ItemClass))
							{
								// ItemType 1단계 upgrade
								int upgradeCount = 1;
					
								it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, upgradeCount);
							}

							if (!it.OptionType.empty() )
							{
								upgradeOptionByLuck(luckLevel, ownerCreatureClass, it);
							}

#if defined(__THAILAND_SERVER__) || defined(__CHAINA_SERVER__)
							it.ItemType	= getItemTypeByItemLimit(it.ItemClass , it.ItemType);
#endif

							pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
							Assert(pItem != NULL);
							if (pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();
							
							if (pItem->isUnique() ) pItem->setGrade(6);
							else
								pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
							//pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
							//cout << "루팅 아이템 등급 : " << pItem->getGrade() << endl;

							pItem->setDurability(computeMaxDurability(pItem));
				
							if (!isHarvestFestivalItemAppeared ||
									(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
								pMonsterCorpse->addTreasure(pItem);
						}
					}
					else
					{
						//cout << "생성확률!!!! : " << g_pVariableManager->getPremiumItemProbePercent() << endl;
						if (pTreasure->getRandomItem(&it, g_pVariableManager->getItemProbRatio() + itemBonusPercent ))
						{
							// by sigi. 2002.10.21
							//upgradeItemTypeByLuck(luckLevel, it);
#if defined(__CHAINA_SERVER__) || defined(__THAILAND_SERVER__)
							it.ItemType = getItemTypeByItemLimit (it.ItemClass, it.ItemType);
#endif
							pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
							Assert(pItem != NULL);
							if (pItem->getItemClass() == Item::ITEM_CLASS_RESURRECT_ITEM ) countResurrectItem();

							if (pItem->isUnique() ) pItem->setGrade(6);
							else
								pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
							//pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
	//						cout << "루팅 아이템 등급 : " << pItem->getGrade() << endl;

							pItem->setDurability(computeMaxDurability(pItem));
				
							if (!isHarvestFestivalItemAppeared ||
									(isHarvestFestivalItemAppeared && pItem->getItemClass() == Item::ITEM_CLASS_SKULL))
								pMonsterCorpse->addTreasure(pItem);
						}
					}

					if (pItem != NULL )
						i++;

					j++;
				}
			}
			/////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////
		}
	}

	// 해골 넣어줘야 되는 몬스타
	if (pMonsterInfo->getSkullType() != 0 )
	{
		Item* pSkull = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_SKULL, pMonsterInfo->getSkullType(), list<OptionType_t>());
		if (pSkull != NULL )
		{
			pMonsterCorpse->addTreasure(pSkull);
		}
	}

	//////////////////////////////////////////////////////////////////////
	// 2002년 6월 월드컵 이벤트
	//  이벤트 몬스터로 세팅이 된 몬스터에게서는 축구공 아이템이 나온다.
	//  축구공은 별도의 ITEM_TYPE을 가지지 않고
	//  EVENT_STAR의 Type7번으로 작동한다.
	//  차후 EventStarInfo, EventStarObject는 EventItemInfo, EventItemObject
	//  로 변경되어야 할 것이다.
	/////////////////////////////////////////////////////////////////////
	/*
	if(pDeadMonster->getEventMonsterFlag() == true)
	{
		ITEM_TEMPLATE ball_template;
		ball_template.ItemClass = Item::ITEM_CLASS_EVENT_STAR;
		ball_template.ItemType = 6;
		ball_template.OptionType=0;

		//if(g_pVariable->getDebugMode() == "COUT")
			//cout << "축구공 아이템 생성" << endl;

		Item *pItem = g_pItemFactoryManager->createItem(ball_template.ItemClass, ball_template.ItemType, ball_template.OptionType);
		Assert(pItem != NULL);
		pMonsterCorpse->addTreasure(pItem);
	}
	*/
	

	//////////////////////////////////////////////////////////////////////
	//   2002년 5월 가정의 달 이벤트/
	//   모든 몬스터에게서 별이 나올 수 있으므로, 여기에 하드코딩하였다.
	//   1/1500 의 확률로 별 아이템을 추가로 생성한다.(걸리는 놈은 재수다)
	//////////////////////////////////////////////////////////////////////
	//cout << "Monster Manager: star -> " << g_pVariable->getStar() << endl;
	//int star_percentage = g_pVariable->getStar();
    /*
	if(rand()%500 == 0) {
		ITEM_TEMPLATE star_template;
		star_template.ItemClass = Item::ITEM_CLASS_EVENT_STAR;

		// 먼저 1/10의 확률로 살펴본 다음, 걸리면 1/6의 확률로 각 별을 나오게 한다.
		// 9/10의 확률로는 검은별을 제외한 별만 나오게 한다.
		if(rand() % 1500 == 0)
			star_template.ItemType = rand() % 6;
		else
			star_template.ItemType = (rand() % 5) + 1;
		star_template.OptionType = 0;

		cout << "이벤트 아이템 생성" << star_template.ItemType << endl;
		Item* pItem = g_pItemFactoryManager->createItem(star_template.ItemClass,star_template.ItemType, star_template.OptionType);
		Assert(pItem != NULL);
		pMonsterCorpse->addTreasure(pItem);
	}
	*/
	__END_CATCH
}

int MonsterManager::upgradeItemTypeByLuck(int luckLevel, Creature::CreatureClass ownerCreatureClass, ITEM_TEMPLATE& it)
	throw(Error)
{
	__BEGIN_TRY

	if (luckLevel==0
		|| !isPossibleUpgradeItemType(it.ItemClass))
		return 0;

	luckLevel = luckLevel + (rand()%20) - 10;
	luckLevel = min(MAX_LUCK_LEVEL, luckLevel);
//	cout << "Apply luck : " << luckLevel << endl;

	int ratio;

	switch (ownerCreatureClass )
	{
		case Creature::CREATURE_CLASS_SLAYER:
			{
				if (luckLevel >= 0 )
				{
					ratio = (int)(((float)luckLevel / (4.254 + (1.0 + it.ItemType)/5.0) ) * 100);
				}
				else
				{
					ratio = (int)(((float)luckLevel / (2.5 - (1.0 + it.ItemType)/20.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_VAMPIRE:
			{
				if (luckLevel >= 0 )
				{
					ratio = (int)(((float)luckLevel / (6.03 + (1.0 + it.ItemType)/5.0) ) * 100);
				}
				else
				{
					ratio = (int)(((float)luckLevel / (4.14 - (1.0 + it.ItemType)/20.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_OUSTERS:
			{
				if (luckLevel >= 0 )
				{
					ratio = (int)(((float)luckLevel / (4.936 + (1.0 + it.ItemType)/5.0) ) * 100);
				}
				else
				{
					ratio = (int)(((float)luckLevel / (3.05 - (1.0 + it.ItemType)/20.0) ) * 100);
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
	if (ratio > 0 && value < ratio )
	{
		it.ItemType = getUpgradeItemType(it.ItemClass, it.ItemType, 1);
//		cout << "after : " << it.ItemClass << "/" << (int)it.ItemType << endl;
		return 1;
	}
	else if (ratio < 0 && value < (-ratio) )
	{
		it.ItemType = getDowngradeItemType(it.ItemClass, it.ItemType);
//		cout << "after : " << it.ItemClass << "/" << (int)it.ItemType << endl;
		return -1;
	}

	return 0;

	__END_CATCH
}

int MonsterManager::upgradeOptionByLuck(int luckLevel, Creature::CreatureClass ownerCreatureClass, ITEM_TEMPLATE& it) throw(Error)
{
	__BEGIN_TRY

	if (it.OptionType.empty() ) return 0;

	OptionType_t optionType = it.OptionType.front();
	OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(optionType);
	if (pOptionInfo == NULL ) return 0;

	luckLevel = luckLevel + (rand()%20) - 10;
	luckLevel = min(MAX_LUCK_LEVEL, luckLevel);
//	cout << "Apply luck to option : " << luckLevel << endl;

	int grade = pOptionInfo->getGrade() + 1;
//	cout << "Option Grade : " << grade << endl;

	int ratio;

	switch (ownerCreatureClass )
	{
		case Creature::CREATURE_CLASS_SLAYER:
			{
				if (luckLevel >= 0 )
				{
					ratio = (int)(((float)luckLevel / (grade*25.0 - 15.2) ) * 100);
				}
				else
				{
					ratio = (int)(((float)luckLevel / (7.5 - grade/2.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_VAMPIRE:
			{
				if (luckLevel >= 0 )
				{
					ratio = (int)(((float)luckLevel / (grade*25.0 - 11.3) ) * 100);
				}
				else
				{
					ratio = (int)(((float)luckLevel / (10.3 - grade/2.0) ) * 100);
				}
			}
			break;
		case Creature::CREATURE_CLASS_OUSTERS:
			{
				if (luckLevel >= 0 )
				{
					ratio = (int)(((float)luckLevel / (grade/25.0 - 13.7) ) * 100);
				}
				else
				{
					ratio = (int)(((float)luckLevel / (7.9 - grade/2.0) ) * 100);
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

	if (ratio > 0 && value < ratio && pOptionInfo->getUpgradeType() != optionType && pOptionInfo->isUpgradePossible() )
	{
		(*it.OptionType.begin()) = pOptionInfo->getUpgradeType();
//		cout << "after : " << g_pOptionInfoManager->getOptionInfo(it.OptionType.front() )->getHName() << endl;
		return 1;
	}
	else if (ratio < 0 && value < (-ratio) && pOptionInfo->getPreviousType() != optionType )
	{
		if (pOptionInfo->getPreviousType() != 0 )
			(*it.OptionType.begin()) = pOptionInfo->getPreviousType();
		else
			it.OptionType.pop_front();
//		if (it.OptionType.front() == 0 ) it.OptionType.pop_front();
//		cout << "after : " << g_pOptionInfoManager->getOptionInfo(it.OptionType.front() )->getHName() << endl;
		return -1;
	}

	return 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 모든 크리처를 제거한다.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::deleteAllMonsters (bool bDeleteFromZone)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

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

				// 타일에서 제거
				Tile & tile = m_pZone->getTile(cx , cy);
				tile.deleteCreature(pCreature->getObjectID());

				// 주변의 PC들에게 크리처가 사라졌다는 사실을 브로드캐스트한다.
				GCDeleteObject gcDeleteObject(pCreature->getObjectID());
				pZone->broadcastPacket(cx, cy, &gcDeleteObject, pCreature);

			} catch (Throwable& t) {
				filelog("MonsterManagerBug.txt", "deleteAllCreatures: %s", t.toString().c_str());
			}
		}

		// 크리쳐를 삭제한다.
		SAFE_DELETE(pCreature);

		current ++;
	}

	// 다 제거한다.
	m_Creatures.clear();
	m_Monsters.clear();



	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 모든 크리처를 죽인다.
////////////////////////////////////////////////////////////////////////////////
void MonsterManager::killAllMonsters (const map<ObjectID_t, ObjectID_t>& exceptCreatures)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

	while (current != m_Creatures.end()) 
	{
		Creature* pCreature = current->second;

		Assert(pCreature != NULL);

		if (pCreature->isAlive())
		{
			if (pCreature->isMonster())
			{
				map<ObjectID_t, ObjectID_t>::const_iterator itr = exceptCreatures.find(pCreature->getObjectID());

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
       throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterManager(" << CreatureManager::toString();

	map< SpriteType_t , MonsterCounter* >::const_iterator itr = m_Monsters.begin();
	for (; itr != m_Monsters.end() ; itr ++) msg << itr->second->toString();

	msg << ")" ;
	return msg.toString();

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// 황금 해골 줍기 이벤트에 쓰였던 코드의 일부분이다.
// 일단은 보기 싫어서 빼놓는데, 나중에라도 혹시 다시 쓰여질까 해서
// 파일 맨 끝으로 옮겨놓는다.
//////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////
// 이벤트 관련 코드 시작
////////////////////////////////////////////////////////////
SpriteType_t SpriteType = pMonsterInfo->getSpriteType();
uint         event_ratio = rand()%100;
uint         skull_ratio = rand()%100;

switch (SpriteType)
{
	case 5: // 데드바디
		if (event_ratio < 3) ItemType = 12;
		break;
	case 8: // 터닝데드
		if (event_ratio < 3) ItemType = 12;
		break;
	case 7: // 터닝소울
		if (event_ratio < 3)
		{
			if (skull_ratio < 98) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 6: // 키드
		if (event_ratio < 3)
		{
			if (skull_ratio < 97) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 4: // 솔져
		if (event_ratio < 3)
		{
			if (skull_ratio < 96) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 9: // 캡틴
		if (event_ratio < 3)
		{
			if (skull_ratio < 94) ItemType = 12;
			else ItemType = 15;
		}
		break;
	case 42: // 알칸
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 43: // 레드아이
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 60: // 뮤턴트
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 64: // 모데라스
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 41: // 더티스트라이더
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 62: // 에스트로이더
		if (event_ratio < 4)
		{
			if (skull_ratio < 93) ItemType = 12;
			else if (93 <= skull_ratio && skull_ratio < 99) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 61: // 위도우즈
		if (event_ratio < 4)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 48: // 호블
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 < skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 27: // 블러드워록
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 40: // 골레머
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 57: // 쉐도우윙
		if (event_ratio < 5)
		{
			if (skull_ratio < 91) ItemType = 12;
			else if (91 <= skull_ratio && skull_ratio < 98) ItemType = 15;
			else ItemType = 14;
		}
		break;
	case 47: // 카오스가디언
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
// 이벤트 관련 코드 끝
////////////////////////////////////////////////////////////
*/

bool isLottoWinning()
{
	int lottoItemRatio = g_pVariableManager->getVariable(LOTTO_ITEM_RATIO);
	if (lottoItemRatio > 0 )
	{
		int value = rand() % 10000;
		if (value < lottoItemRatio )
		{
			return true;
		}
	}

	return false;
}
