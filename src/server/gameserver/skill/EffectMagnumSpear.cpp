//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMagnumSpear.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectMagnumSpear.h"
#include "Slayer.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectMagnumSpear::EffectMagnumSpear(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectMagnumSpear::affect() 
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

void EffectMagnumSpear::affect(Creature* pCreature)
	
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

	::setDamage( pCreature, damage, pAttacker, SKILL_MAGNUM_SPEAR, &gcMI, &gcAttackerMI );

	if ( pCreature->isDead() && pAttacker != NULL && pAttacker->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pAttacker);
		Exp_t exp = computeCreatureExp( pCreature, KILL_EXP );
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

	--m_Times;

	if ( m_Times == 0 ) 
		setDeadline(0);
	else 
		setNextTime( m_Tick );

	__END_CATCH
}

void EffectMagnumSpear::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectMagnumSpear " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectMagnumSpear " << "unaffect END" << endl;

    __END_CATCH
}

void EffectMagnumSpear::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectMagnumSpear " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_MAGNUM_SPEAR);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_MAGNUM_SPEAR);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectMagnumSpear " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectMagnumSpear::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMagnumSpear("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
