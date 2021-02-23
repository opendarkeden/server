//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodyWallBlocked.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectBloodyWallBlocked.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBloodyWallBlocked::EffectBloodyWallBlocked(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_CasterName ="";
	m_PartyID = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWallBlocked::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBloodyWallBlocked" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 현재 이펙트가 붙어있는 타일을 받아온다.
    Tile& tile = m_pZone->getTile(m_X, m_Y);

	HP_t CurrentHP = 0;
	HP_t RemainHP  = 0;

	// 타일 안에 존재하는 오브젝트들을 검색한다.
    const slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::const_iterator itr = oList.begin();
    for (; itr != oList.end(); itr++) 
	{
		Assert(*itr != NULL);

		Object* pObject = *itr;
		Assert(pObject != NULL);

    	if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature != NULL);

			// 무적상태 체크. by sigi. 2002.9.5
			// 산 면역. by sigi. 2002.9.13
			if ( !canAttack( NULL, pCreature )
				|| pCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN)
				|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
				|| pCreature->isDead())
			{
				continue;
			}

			int AcidDamage = computeMagicDamage(pCreature, m_Damage, SKILL_BLOODY_WALL);

			if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
			{
				if (pCreature->isSlayer()) 
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

					CurrentHP = pSlayer->getHP(ATTR_CURRENT);
					RemainHP  = max(0, CurrentHP -(int)AcidDamage);

					pSlayer->setHP(RemainHP, ATTR_CURRENT);

					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_HP, pSlayer->getHP(ATTR_CURRENT));

					Player* pPlayer = pSlayer->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					// 변한 HP를 브로드캐스팅해준다.
					GCStatusCurrentHP pkt;
					pkt.setObjectID(pSlayer->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &pkt);
				} 
/*				else if (pCreature->isVampire())
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

					CurrentHP = pVampire->getHP(ATTR_CURRENT);
					RemainHP  = max(0, CurrentHP -(int)AcidDamage);

					pVampire->setHP(RemainHP, ATTR_CURRENT);

					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_HP, pVampire->getHP(ATTR_CURRENT));

					Player* pPlayer = pVampire->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					// 변한 HP를 브로드캐스팅해준다.
					GCStatusCurrentHP pkt;
					pkt.setObjectID(pVampire->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &pkt);
				}
				*/
				else if (pCreature->isOusters())
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

					CurrentHP = pOusters->getHP(ATTR_CURRENT);
					RemainHP  = max(0, CurrentHP -(int)AcidDamage);

					pOusters->setHP(RemainHP, ATTR_CURRENT);

					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_HP, pOusters->getHP(ATTR_CURRENT));

					Player* pPlayer = pOusters->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					// 변한 HP를 브로드캐스팅해준다.
					GCStatusCurrentHP pkt;
					pkt.setObjectID(pOusters->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &pkt);
				}
				else if (pCreature->isMonster())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					CurrentHP = pMonster->getHP(ATTR_CURRENT);
					RemainHP  = max(0, CurrentHP -(int)AcidDamage);

					pMonster->setHP(RemainHP, ATTR_CURRENT);

					if( m_CasterName != "" ) {
						// 시전자의 데미지를 추가해 준다.
						// 맞는 놈이 몬스터이고, 공격자가 사람이라면,
						// 데미지에 따라서 변하는 우선권 테이블을 갱신해 주어야 한다.
						pMonster->addPrecedence(m_CasterName, m_PartyID, AcidDamage);
						pMonster->setLastHitCreatureClass(Creature::CREATURE_CLASS_VAMPIRE);
					}

					// 변한 HP를 브로드캐스팅해준다.
					GCStatusCurrentHP pkt;
					pkt.setObjectID(pMonster->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &pkt);
				}


				// m_CasterName이 pCreature를 죽인 경우의 KillCount 처리
				// by sigi. 2002.8.31
				if (pCreature->isDead())
				{
					Creature* pAttacker = m_pZone->getCreature( m_CasterName );

					if (pAttacker!=NULL)
					{ 
						affectKillCount(pAttacker, pCreature);
					}
				}
			}
		}
	}
	
	// 한번만..
	//setNextTime(m_Tick);

	//cout << "EffectBloodyWallBlocked" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWallBlocked::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWallBlocked::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWallBlocked::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWallBlocked::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBloodyWallBlocked" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectBloodyWallBlocked" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWallBlocked::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBloodyWallBlocked::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectBloodyWallBlocked("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

EffectBloodyWallBlockedLoader* g_pEffectBloodyWallBlockedLoader = NULL;
