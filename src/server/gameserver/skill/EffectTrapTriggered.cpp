//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTrapTriggered.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectTrapTriggered.h"
#include "Slayer.h"
#include "Player.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectTrapTriggered::EffectTrapTriggered(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectTrapTriggered::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectTrapTriggered::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectTrapTriggered " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectTrapTriggered " << "unaffect END" << endl;

    __END_CATCH
}

void EffectTrapTriggered::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectTrapTriggered " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	//Assert(pCreature->isSlayer());

	pCreature->removeFlag(Effect::EFFECT_CLASS_TRAPPED);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_TRAPPED);
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_TRAP_TRIGGERED);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectTrapTriggered " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectTrapTriggered::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTrapTriggered("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
