
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBombCrashWalkToEnemy.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectBombCrashWalkToEnemy.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBombCrashWalkToEnemy::EffectBombCrashWalkToEnemy(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalkToEnemy::affect()
	
{
	__BEGIN_TRY

	//cout << "EffectBombCrashWalkToEnemy " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectBombCrashWalkToEnemy " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalkToEnemy::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectBombCrashWalkToEnemy " << "begin" << endl;
	//cout << "EffectBombCrashWalkToEnemy " << "end" << endl;
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		&& !pCreature->isDead()
		&& !pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
		// 公利惑怕 眉农. by sigi. 2002.9.5
		&& canAttack( pAttacker, pCreature )
	   )
	{
		GCModifyInformation gcMI, gcAttackerMI;
		setDamage( pCreature, m_Point, pAttacker, SKILL_DIVINE_GUIDANCE, &gcMI, &gcAttackerMI );
		if ( pCreature->isPC() ) pCreature->getPlayer()->sendPacket( &gcMI );

		if (pAttacker!=NULL) 
		{
			computeAlignmentChange( pCreature, m_Point, pAttacker, &gcMI, &gcAttackerMI );
			if ( pAttacker->isPC() )
			{ 
				if ( pAttacker->isSlayer() && !pCreature->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pAttacker);

					if ( pSlayer != NULL )
					{
						//GCModifyInformation gcMI;
						//shareAttrExp( pSlayer, m_Point, 1, 1, 8, gcAttackerMI );
					}
				}

				if ( pAttacker->isPC() ) pAttacker->getPlayer()->sendPacket( &gcAttackerMI );
			}
		}

	}
	// 如果角色死亡 去除效果
	if (pCreature->isDead())
	{
		setDeadline( 0 );
		setNextTime( 0 );
	}
	setNextTime( m_Tick );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalkToEnemy::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect );

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalkToEnemy::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBombCrashWalkToEnemy::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectBombCrashWalkToEnemy("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

