//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGroundAttack.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectGroundAttack.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectGroundAttack::EffectGroundAttack(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_DamagePercent = 0;
//	m_CasterName = "";
	m_UserObjectID = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGroundAttack::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectGroundAttack" << "affect BEGIN" << endl;

	//setNextTime(m_Delay);

	//cout << "EffectGroundAttack" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGroundAttack::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGroundAttack::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGroundAttack::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectGroundAttack" << "unaffect BEGIN" << endl;
	Assert(m_pZone != NULL);

	// 시전자를 가져온다.
	// !! 이미 존을 나갔을 수 있으므로 NULL이 될 수 잇다.
	// by bezz. 2003.1.4
	Creature* pCastCreature = m_pZone->getCreature( m_UserObjectID );

	int Damage;
	int DamageLimit = 0xFFFF; //500;

	HP_t MaxHP = 0;

	VSRect rect(0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1);

	// 현재 이펙트가 붙어있는 타일을 받아온다.
	// 중심타일 + 스플래쉬 타일
	for (int x=-1; x<=1; x++)
	{
		for (int y=-1; y<=1; y++)
		{
			int X = m_X + x;
			int Y = m_Y + y;

			if (!rect.ptInRect(X, Y)) continue;
			Tile& tile = m_pZone->getTile(X, Y);

			// 가운데는 100%
			// 주위에는 50% damage
			bool bCenterEffect = (x==0 && y==0);
			int	DamagePercent = (bCenterEffect? m_DamagePercent : (m_DamagePercent>>1));

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
					if ( !canAttack( pCastCreature, pCreature ) )
					{
						continue;
					}

					if (pCreature->isSlayer()) 
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

						MaxHP = pSlayer->getHP(ATTR_MAX);
						Damage = min(DamageLimit, MaxHP*DamagePercent/100);

						GCModifyInformation gcMI;
						::setDamage( pSlayer, Damage, pCastCreature, SKILL_GROUND_ATTACK, &gcMI );

						Player* pPlayer = pSlayer->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);
					} 
					else if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

						MaxHP = pVampire->getHP(ATTR_MAX);
						Damage = min(DamageLimit, MaxHP*DamagePercent/100);

						GCModifyInformation gcMI;
						::setDamage( pVampire, Damage, pCastCreature, SKILL_GROUND_ATTACK, &gcMI );

						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);
					}
					else if (pCreature->isOusters())
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

						MaxHP = pOusters->getHP(ATTR_MAX);
						Damage = min(DamageLimit, MaxHP*DamagePercent/100);

						GCModifyInformation gcMI;
						::setDamage( pOusters, Damage, pCastCreature, SKILL_GROUND_ATTACK, &gcMI );

						Player* pPlayer = pOusters->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);
					}
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);

						MaxHP = pMonster->getHP(ATTR_MAX);
						Damage = min(DamageLimit, MaxHP*DamagePercent/100);

						::setDamage( pMonster, Damage, pCastCreature, SKILL_GROUND_ATTACK );
					}

					// user한테는 맞는 모습을 보여준다.
					if (pCreature->isPC())
					{
						GCSkillToObjectOK2 gcSkillToObjectOK2;
						gcSkillToObjectOK2.setObjectID( 1 );	// 의미 없다.
						gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK2.setDuration(0);
						pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);
					}

					GCSkillToObjectOK4 gcSkillToObjectOK4;
					gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
					gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
					gcSkillToObjectOK4.setDuration(0);
					m_pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcSkillToObjectOK4, pCreature);

					// m_CasterName이 pCreature를 죽인 경우의 KillCount 처리
					// by sigi. 2002.8.31
/*					if (pCreature->isDead())
					{
						Creature* pAttacker = m_pZone->getCreature( m_CasterName );

						if (pAttacker!=NULL)
						{ 
							affectKillCount(pAttacker, pCreature);
						}
					}*/
				}
			}
		}
	}

	Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectGroundAttack" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectGroundAttack::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectGroundAttack("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

EffectGroundAttackLoader* g_pEffectGroundAttackLoader = NULL;
