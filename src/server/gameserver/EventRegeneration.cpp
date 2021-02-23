//////////////////////////////////////////////////////////////////////////////
// Filename    : EventRegeneration.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventRegeneration.h"
#include "GamePlayer.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Item.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventRegeneration::EventRegeneration (GamePlayer* pGamePlayer) 
	throw (Error)
: Event(pGamePlayer)
{
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventRegeneration::~EventRegeneration () 
	throw ()
{
}

			
//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventRegeneration::activate () 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Assert(m_pGamePlayer != NULL);

		Creature* pCreature = m_pGamePlayer->getCreature();
		Assert(pCreature != NULL);
		Assert(pCreature->isPC());

		Zone* pZone = pCreature->getZone();

		if (pCreature->isAlive())
		{
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

				HP_t oldHP   = pSlayer->getHP(ATTR_CURRENT); // 현재 HP
				MP_t oldMP   = pSlayer->getMP(ATTR_CURRENT); // 현재 MP

				HP_t maxHP   = pSlayer->getHP(ATTR_MAX); // 현재 맥스 HP
				MP_t maxMP   = pSlayer->getMP(ATTR_MAX); // 현재 맥스 MP

				// 리젠율에 따라 회복시킬 HP와 MP의 양을 계산한다.
				//HP_t regenHP = getPercentValue(maxHP, pSlayer->getHPRegen()); 
				//MP_t regenMP = getPercentValue(maxMP, pSlayer->getMPRegen());
				HP_t regenHP = pSlayer->getHPRegen() * 2;
				MP_t regenMP = pSlayer->getMPRegen() * 2;

				// MAX를 넘어가면 곤란하다.
				HP_t newHP   = min((int)(oldHP + regenHP), (int)maxHP); 
				MP_t newMP   = min((int)(oldMP + regenMP), (int)maxMP);

				pSlayer->setHP(newHP, ATTR_CURRENT);
				pSlayer->setMP(newMP, ATTR_CURRENT);

				GCModifyInformation GCMI;

				// HP가 변경되었으니 브로드캐스팅해준다.
				if (oldHP != newHP)
				{
					GCMI.addShortData(MODIFY_CURRENT_HP, newHP); 

					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pSlayer->getObjectID());
					gcStatusCurrentHP.setCurrentHP(newHP);
					pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcStatusCurrentHP, pSlayer);
				}

				if (oldMP != newMP)
				{
					GCMI.addShortData(MODIFY_CURRENT_MP, newMP); 
				}

				// HP나 MP가 변경되었다면, 변경되었다는 사실을 본인에게 알려준다.
				if (GCMI.getShortCount() != 0 || GCMI.getLongCount() != 0)
					m_pGamePlayer->sendPacket(&GCMI);
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				HP_t     oldHP    = pVampire->getHP(ATTR_CURRENT);
				HP_t     maxHP    = pVampire->getHP(ATTR_MAX) - pVampire->getSilverDamage();
				HP_t     regenHP  = 0;
				HP_t     newHP    = 0;
 
				/*
				if (pVampire->isFlag(Effect::EFFECT_CLASS_HIDE))
				{
					// 하이드하고 있을 때는 평상시보다 HP가 빨리 차게 된다.
					regenHP = getPercentValue(maxHP, 15 + pVampire->getHPRegen() + pVampire->getINT(ATTR_CURRENT)/60);
					newHP   = min((int)(oldHP + regenHP), (int)maxHP);
				}
				else
				{
					// 평상시에는...
					regenHP = getPercentValue(maxHP, 10 + pVampire->getHPRegen() + pVampire->getINT(ATTR_CURRENT)/60);
					newHP   = min((int)(oldHP + regenHP), (int)maxHP);
				}
				*/

				// 박쥐 상태인가 아닌가만을 검사한다.
				// 하이드나 관에 들어가 있는 상태 검사가 없는 이유는,
				// 이들 상태에 의한 HP 회복 루틴은 Vampire::heartbeat()에 들어가 있기 때문이다.
				if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
				{
					// 박쥐 상태에서는 HP가 회복되지 않는다.
					regenHP = 0;
				}
				else
				{
					// 평상시에는...
					regenHP = pVampire->getHPRegen() * 2;
				}

				newHP = min((int)(oldHP + regenHP), (int)maxHP);

				pVampire->setHP(newHP, ATTR_CURRENT);

				GCModifyInformation GCMI;

				// HP가 변경되었으니 브로드캐스팅해준다.
				if (oldHP != newHP)
				{
					GCMI.addShortData(MODIFY_CURRENT_HP, newHP); 

					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
					gcStatusCurrentHP.setCurrentHP(newHP);
					pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);
				}

				// HP가 변경되었다는 사실을 본인에게 알려준다.
				if (GCMI.getShortCount() != 0 || GCMI.getLongCount() != 0) m_pGamePlayer->sendPacket(&GCMI);
			}
			else if (pCreature->isOusters())
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		
				HP_t oldHP   = pOusters->getHP(ATTR_CURRENT); // 현재 HP
				MP_t oldMP   = pOusters->getMP(ATTR_CURRENT); // 현재 MP

				HP_t maxHP   = pOusters->getHP(ATTR_MAX); // 현재 맥스 HP
				MP_t maxMP   = pOusters->getMP(ATTR_MAX); // 현재 맥스 MP

				// 리젠율에 따라 회복시킬 HP와 MP의 양을 계산한다.
				//HP_t regenHP = getPercentValue(maxHP, pOusters->getHPRegen()); 
				//MP_t regenMP = getPercentValue(maxMP, pOusters->getMPRegen());
				HP_t regenHP = pOusters->getHPRegen() * 2;
				MP_t regenMP = pOusters->getMPRegen() * 2;

				// MAX를 넘어가면 곤란하다.
				HP_t newHP   = min((int)(oldHP + regenHP), (int)maxHP); 
				MP_t newMP   = min((int)(oldMP + regenMP), (int)maxMP);

				pOusters->setHP(newHP, ATTR_CURRENT);

				if ( oldMP < newMP ) pOusters->setMP(newMP, ATTR_CURRENT);
				newMP = pOusters->getMP(ATTR_CURRENT);

				GCModifyInformation GCMI;

				// HP가 변경되었으니 브로드캐스팅해준다.
				if (oldHP != newHP)
				{
					GCMI.addShortData(MODIFY_CURRENT_HP, newHP); 

					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pOusters->getObjectID());
					gcStatusCurrentHP.setCurrentHP(newHP);
					pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcStatusCurrentHP, pOusters);
				}

				if (oldMP != newMP)
				{
					GCMI.addShortData(MODIFY_CURRENT_MP, newMP); 
				}

				// HP나 MP가 변경되었다면, 변경되었다는 사실을 본인에게 알려준다.
				if (GCMI.getShortCount() != 0 || GCMI.getLongCount() != 0)
					m_pGamePlayer->sendPacket(&GCMI);
			}
		}

		// 10 초마다 회복시켜 주기 위해서는 deadline 을 증가시켜 줘야 한다.
		Timeval delay;
		delay.tv_sec = 10;
		delay.tv_usec = 0;
	
		m_Deadline = m_Deadline + delay;
	}
	else
	{
		Timeval delay;
		delay.tv_sec = 10;
		delay.tv_usec = 0;
	
		m_Deadline = m_Deadline + delay;
	}
	
	__END_CATCH
}
