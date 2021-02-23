//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMephisto.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectMephisto.h"
#include "Creature.h"
#include "Vampire.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectMephisto::EffectMephisto(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectMephisto::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMephisto::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

	//cout << "EffectMephisto" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectMephisto" << "unaffect END" << endl;

    __END_CATCH
}

void EffectMephisto::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectMephisto" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isVampire());

	pCreature->removeFlag(Effect::EFFECT_CLASS_MEPHISTO);

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
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_MEPHISTO);
	pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcRemoveEffect);

	//cout << "EffectMephisto" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectMephisto::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMephisto("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
