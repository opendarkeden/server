//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAcidEruption.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectAcidEruption.h"
#include "Slayer.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectAcidEruption::EffectAcidEruption(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectAcidEruption::affect() 
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

void EffectAcidEruption::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert( pCreature != NULL );
	if ( pCreature->isDead() )
	{
		setDeadline(0);
		return;
	}

	Creature* pAttacker = pCreature->getZone()->getCreature( m_CasterOID );
	Damage_t damage = m_Damage / m_TotalTimes;
	if ( m_Times == m_TotalTimes ) damage += m_Damage % m_TotalTimes;

	GCModifyInformation gcMI, gcAttackerMI;

	::setDamage( pCreature, damage, pAttacker, SKILL_ACID_ERUPTION, &gcMI, &gcAttackerMI );

	if ( pCreature->isDead() && pAttacker != NULL && pAttacker->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pAttacker);
		Exp_t exp = computeCreatureExp( pCreature, KILL_EXP );
		shareVampExp( pVampire, exp, gcAttackerMI );
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

	--m_Times;

	if ( m_Times == 0 ) 
		setDeadline(0);
	else 
		setNextTime( m_Tick );

	__END_CATCH
}

void EffectAcidEruption::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectAcidEruption " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectAcidEruption " << "unaffect END" << endl;

    __END_CATCH
}

void EffectAcidEruption::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectAcidEruption " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_ACID_ERUPTION);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_ACID_ERUPTION);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectAcidEruption " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectAcidEruption::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectAcidEruption("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
