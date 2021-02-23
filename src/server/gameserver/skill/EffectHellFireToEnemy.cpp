//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHellFireToEnemy.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHellFireToEnemy.h"
#include "Ousters.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHellFireToEnemy::EffectHellFireToEnemy(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	//Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

void EffectHellFireToEnemy::affect()
	throw(Error)
{
	__BEGIN_TRY

	if ( m_pTarget == NULL || m_pTarget->getObjectClass() != OBJECT_CLASS_CREATURE )
	{
		setDeadline(0);
		return;
	}

	affect( dynamic_cast<Creature*>(m_pTarget) );
	
	__END_CATCH
}

void EffectHellFireToEnemy::affect(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY
		
	Assert( pCreature != NULL );

	if ( pCreature->isDead() )
	{
		setDeadline(0);
		return;
	}

	Creature* pAttacker = pCreature->getZone()->getCreature( m_CasterOID );
	Damage_t damage = m_Damage;

	GCModifyInformation gcMI, gcAttackerMI;

	::setDamage( pCreature, damage, pAttacker, SKILL_HELLFIRE, &gcMI, &gcAttackerMI, true, false );

	if ( pCreature->isDead() && pAttacker != NULL && pAttacker->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pAttacker);
//		Exp_t exp = computeCreatureExp( pCreature, KILL_EXP );
		Exp_t exp = computeCreatureExp( pCreature, 70, pOusters );
		shareOustersExp( pOusters, exp, gcAttackerMI );
		increaseAlignment( pAttacker, pCreature, gcAttackerMI );
	}
	
	if ( pAttacker != NULL && pAttacker->isPC() )
	{
		computeAlignmentChange(pCreature, damage, pAttacker, &gcMI, &gcAttackerMI);
		pAttacker->getPlayer()->sendPacket( &gcAttackerMI );
	}

	if ( pCreature->isPC() )
	{
		pCreature->getPlayer()->sendPacket( &gcMI );
	}

	setNextTime(10);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHellFireToEnemy::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectHellFireToEnemy" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
//	Assert(pCreature->isOusters());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_HELLFIRE_TO_ENEMY);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

//	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
//	Assert( pTargetOusters != NULL );

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HELLFIRE_TO_ENEMY);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectHellFireToEnemy" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHellFireToEnemy::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHellFireToEnemy::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHellFireToEnemy("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

