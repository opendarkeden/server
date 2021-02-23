//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectExtreme.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectExtreme.h"
#include "Creature.h"
#include "Vampire.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectExtreme::EffectExtreme(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectExtreme::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectExtreme::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

	//cout << "EffectExtreme" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectExtreme" << "unaffect END" << endl;

    __END_CATCH
}

void EffectExtreme::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectExtreme" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isVampire());

	pCreature->removeFlag(Effect::EFFECT_CLASS_EXTREME);

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

	VAMPIRE_RECORD prev;
	pVampire->getVampireRecord(prev);
	pVampire->initAllStat();
	pVampire->sendRealWearingInfo();
	pVampire->sendModifyInfo(prev);

	Zone* pZone = pVampire->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pVampire->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_EXTREME);
	pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcRemoveEffect);

	//cout << "EffectExtreme" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectExtreme::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectExtreme("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
