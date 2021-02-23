//////////////////////////////////////////////////////////////////////////////
// Filename    : CreatureManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CreatureManager.h"
#include <algorithm>		// find_if ()
#include "Assert.h"
#include "GamePlayer.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "IncomingPlayerManager.h"
#include "Player.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Tile.h"
#include "Zone.h"
#include "LogClient.h"
#include "LevelWarZoneInfoManager.h"
#include "SweeperBonusManager.h"

#include "Gpackets/GCCreatureDied.h"

class isSameNAME 
{
public:
	isSameNAME (const string& Name) : m_Name(Name) {}

	bool operator () (pair<const long unsigned int , Creature *> itr) throw ()
	{
		return (itr.second)->getName() == m_Name;
	}

private:
	string m_Name;

};

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
CreatureManager::CreatureManager () 
	throw ()
{
	__BEGIN_TRY

	m_Mutex.setName("CreatureManager");

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
CreatureManager::~CreatureManager () 
	throw ()
{
	__BEGIN_TRY

	hash_map<ObjectID_t, Creature*>::iterator itr = m_Creatures.begin();

	for (; itr != m_Creatures.end(); itr++)	
	{
		Creature* pCreature = itr->second;
		SAFE_DELETE(pCreature);
	}

	m_Creatures.clear();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 크리처 매니저에 새 크리처 객체를 등록한다.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::addCreature (Creature* pCreature) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	hash_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.find(pCreature->getObjectID());

	if (itr != m_Creatures.end())	
		throw DuplicatedException();

	m_Creatures[ pCreature->getObjectID() ] = pCreature;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// 크리처 매니저에 들어있는 특정 크리처 객체를 삭제한다.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::deleteCreature (ObjectID_t objectID) 
	 //throw (NoSuchElementException , Error)
	 throw ()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//try 
	{
		hash_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.find(objectID);

		if (itr == m_Creatures.end())
		{
			//throw NoSuchElementException();
			// 대충(-_-;) 살펴본 결과 외부에서 NoSuchElementException()에 대한
			// 특별한 처리를 하는게 없었다.
			// 오히려.. 처리가 안된게 있어서 문제가 되는 부분도 있었다.
			//  EventMorph에서 Zone::deletePC()에서 NoSuch..가 뜨는 경우가 있다면..
			// 암튼 속도 문제로 인해서 제거
			m_Mutex.unlock();
			return; // by sigi 2002.5.2
		}

		// 단지 hash_map 의 노드만을 삭제할 뿐, 크리처 자체는 삭제하지 않는다.
		m_Creatures.erase(itr);
	} 
	//catch (Throwable & t) 
	//{
		//cerr << t.toString() << endl;
	//}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// 크리처 매니저에 들어있는 특정 크리처 객체를 리턴한다.
//////////////////////////////////////////////////////////////////////////////
Creature* CreatureManager::getCreature (ObjectID_t objectID) const 
           //throw (NoSuchElementException , Error)
           throw ()
{
	__BEGIN_TRY
		
	hash_map< ObjectID_t , Creature* >::const_iterator itr = m_Creatures.find(objectID);

	if (itr == m_Creatures.end())
	{
		//throw NoSuchElementException();
		return NULL;	// by sigi 2002.5.2
	}

	return itr->second;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 크리처 매니저에 들어있는 특정 크리처 객체를 리턴한다.
//////////////////////////////////////////////////////////////////////////////
Creature* CreatureManager::getCreature (const string& Name) const 
           //throw (NoSuchElementException , Error)
           throw ()
{
	__BEGIN_TRY
		
	hash_map< ObjectID_t , Creature* >::const_iterator itr = find_if (m_Creatures.begin(), m_Creatures.end(), isSameNAME(Name));

	if (itr == m_Creatures.end())
	{
		//throw NoSuchElementException();
		return NULL;	// by sigi 2002.5.2
	}

	return itr->second;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 크리처 매니저에 종속된 몬스터/NPC 들의 AI에 의한 액션을 실행한다.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::processCreatures ()
	throw (Error)
{
	__BEGIN_TRY

	hash_map< ObjectID_t , Creature* >::iterator before = m_Creatures.end();
	hash_map< ObjectID_t , Creature* >::iterator current = m_Creatures.begin();

	Timeval currentTime;
	getCurrentTime(currentTime);

	while (current != m_Creatures.end()) 
	{
		Assert(current->second != NULL);

		if (current->second->isAlive()) 
		{
			current->second->act(currentTime);
			before = current ++;
		} 
		else 
		{
			killCreature(current->second);

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
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 죽은 크리처를 처리한다.
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::killCreature (Creature* pDeadCreature)
	throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// broadcast packet
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::broadcastPacket (Packet* pPacket , Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPacket != NULL);

	hash_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.begin ();

	for (; itr != m_Creatures.end() ; itr ++) 
	{
		Assert(itr->second != NULL);
		Assert(itr->second->isPC());

		if (itr->second != pCreature)
		{
			Creature* pCreature = itr->second;
			Assert(pCreature != NULL);

			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);

			pPlayer->sendPacket(pPacket);
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// broadcast DarkLight packet
//////////////////////////////////////////////////////////////////////////////
void CreatureManager::broadcastDarkLightPacket (Packet* pPacket1, Packet* pPacket2 , Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPacket1 != NULL);
	Assert(pPacket2 != NULL);

	Creature* pTargetCreature = NULL;

	hash_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.begin ();

	for (; itr != m_Creatures.end() ; itr ++) 
	{
		Assert(itr->second != NULL);
		Assert(itr->second->isPC());

		pTargetCreature = itr->second;
		Assert(pTargetCreature != NULL);

		Zone* pZone = pTargetCreature->getZone();
		Assert(pZone != NULL);

		//ZoneCoord_t X = pTargetCreature->getX();
		//ZoneCoord_t Y = pTargetCreature->getY();

		if (pTargetCreature != pCreature) 
		{
			if (pTargetCreature->isSlayer()) 
			{
				bool bYellowPoisonEffected = pTargetCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
				bool bLightnessEffected = pTargetCreature->isFlag(Effect::EFFECT_CLASS_LIGHTNESS);

				// 주석처리 by sigi
				//bool bDarknessEffected = (tile.getEffect(Effect::EFFECT_CLASS_DARKNESS) == NULL) ? false : true;

				if (!bYellowPoisonEffected && !bLightnessEffected)// && !bDarknessEffected)  // 주석처리 by sigi
				{
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(pPacket1);
				}
			} 
			else if ( pTargetCreature->isVampire() )
			{
				Player* pPlayer = pTargetCreature->getPlayer();
				pPlayer->sendPacket(pPacket2);
			}
		}
	}

	__END_CATCH
}

void CreatureManager::broadcastLevelWarBonusPacket (Packet* pPacket , Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPacket != NULL);

	hash_map< ObjectID_t , Creature* >::iterator itr = m_Creatures.begin ();

	for (; itr != m_Creatures.end() ; itr ++) 
	{
		Assert(itr->second != NULL);
		Assert(itr->second->isPC());

		if (itr->second != pCreature)
		{
			Creature* pCreature = itr->second;
			Assert(pCreature != NULL);

			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);

			if ( g_pLevelWarZoneInfoManager->isCreatureBonusZone( pCreature, pCreature->getZoneID() ) )
			{
				pPlayer->sendPacket(pPacket);
				pCreature->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
			}
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string CreatureManager::toString () const
	throw ()
{
	StringStream msg;
	msg << "CreatureManager(" << "Size:" << (int)m_Creatures.size();
	for (hash_map<ObjectID_t, Creature*>::const_iterator itr = m_Creatures.begin(); itr != m_Creatures.end(); itr++)
	{
		msg << itr->second->toString();
	}
	msg << ")" ;
	return msg.toString();
}
