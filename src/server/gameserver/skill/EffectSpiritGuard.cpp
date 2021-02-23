//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSpiritGuard.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectSpiritGuard.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCStatusCurrentHP.h"

#include "SkillInfo.h"
#include "SkillSlot.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSpiritGuard::EffectSpiritGuard(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSpiritGuard::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	if ( pCreature != NULL )
	{
		affect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSpiritGuard::affect(Creature* pCastCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCastCreature != NULL);

	if ( !pCastCreature->isSlayer() )
		return;

	Player* pPlayer = dynamic_cast<Player*>(pCastCreature->getPlayer());
	Assert( pPlayer != NULL );

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCastCreature);
	Assert( pSlayer != NULL );

	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_SPIRIT_GUARD );
	if ( pSkillInfo == NULL )
	{
		return;
	}

	GCModifyInformation gcAttackerMI;

	Zone* pZone = pCastCreature->getZone();
	Assert( pZone != NULL );

	VSRect rect( 0, 0, pZone->getWidth()-1, pZone->getHeight()-1 );

	ZoneCoord_t Cx = pCastCreature->getX();
	ZoneCoord_t Cy = pCastCreature->getY();

	bool isHit = false;

	Level_t maxEnemyLevel = 0;
	uint EnemyNum = 0;

	for ( int x=-1; x<=1; x++ )
	{
		for ( int y=-1; y<=1; y++ )
		{
			if ( x == 0 && y == 0 ) continue;

			int X = Cx + x;
			int Y = Cy + y;

			if ( !rect.ptInRect( X, Y ) ) continue;

			// 타일안에 존재하는 오브젝트를 가져온다.
			Tile& tile = pZone->getTile( X, Y );

			if( tile.hasCreature(Creature::MOVE_MODE_WALKING) )
			{
				Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
				Assert( pCreature != NULL );

				// 자신은 맞지 않는다. 무적도 안 맞는다. 슬레이어도 안 맞느다.
				// 안전지대 체크
				// 2003.1.10 by bezz, Sequoia
				if ( pCreature == m_pTarget
				  || !canAttack( pCastCreature, pCreature )
				  || pCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				  || pCreature->isSlayer() 
				  || pCreature->isNPC()
				  || !checkZoneLevelToHitTarget(pCreature)
				)
				{
					continue;
				}

				isHit = true;

				if ( maxEnemyLevel < pCreature->getLevel() ) maxEnemyLevel = pCreature->getLevel();
				EnemyNum++;

				if ( pCreature->isVampire() || pCreature->isOusters() )
				{
//					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

					GCModifyInformation gcMI;
					::setDamage( pCreature, m_Damage, pCastCreature, SKILL_SPIRIT_GUARD, &gcMI, &gcAttackerMI );

					pCreature->getPlayer()->sendPacket( &gcMI );

					// 맞는 동작을 보여준다.
					GCSkillToObjectOK2 gcSkillToObjectOK2;
					gcSkillToObjectOK2.setObjectID( 1 );    // 의미 없다.
					gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
					gcSkillToObjectOK2.setDuration(0);
					pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);

				}
				else if ( pCreature->isMonster() )
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, m_Damage, pCastCreature, SKILL_SPIRIT_GUARD, NULL, &gcAttackerMI );

					pMonster->addEnemy( pCastCreature );
				}
				else Assert(false);

				GCSkillToObjectOK4 gcSkillToObjectOK4;
				gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
				gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
				gcSkillToObjectOK4.setDuration(0);

				pZone->broadcastPacket( X, Y, &gcSkillToObjectOK4, pCreature );
			}
		}
	}

	if ( isHit )
	{
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillSlot* pSkillSlot = pSlayer->getSkill( SKILL_SPIRIT_GUARD );

		if ( pSkillSlot != NULL )
		{
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), gcAttackerMI, maxEnemyLevel, EnemyNum);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, gcAttackerMI);
		}
	}

	setNextTime( m_Delay );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSpiritGuard::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	
	// cout << "EffectSpiritGuard " << "unaffect BEGIN" << endl;
	Assert(pCreature != NULL);

	if ( !pCreature->isSlayer() )
		return;

	Player* pPlayer = dynamic_cast<Player*>(pCreature->getPlayer());
	Assert( pPlayer != NULL );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	// Effect를 없애고 알린다.
	pCreature->removeFlag( Effect::EFFECT_CLASS_SPIRIT_GUARD_1 );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( m_EffectClass );

	pPlayer->sendPacket( &gcRemoveEffect );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect, pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSpiritGuard::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	if ( pCreature != NULL )
	{
		unaffect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSpiritGuard::setLevel(SkillLevel_t Level)
{
	if( Level <= GRADE_ADEPT_LIMIT_LEVEL ) m_EffectClass = EFFECT_CLASS_SPIRIT_GUARD_1;
	else if( Level <= GRADE_EXPERT_LIMIT_LEVEL ) m_EffectClass = EFFECT_CLASS_SPIRIT_GUARD_2;
	else if( Level <= GRADE_MASTER_LIMIT_LEVEL ) m_EffectClass = EFFECT_CLASS_SPIRIT_GUARD_3;
	else m_EffectClass = EFFECT_CLASS_SPIRIT_GUARD_4;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSpiritGuard::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSpiritGuard("
		<< "Damage:" << (int)m_Damage
		<< ", EffectClass:" << (int)m_EffectClass
		<< ")";
	return msg.toString();

	__END_CATCH
}

