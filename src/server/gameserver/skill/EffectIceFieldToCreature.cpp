//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceFieldToCreature.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectIceFieldToCreature.h"
#include "Ousters.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectIceFieldToCreature::EffectIceFieldToCreature(Creature* pCreature, bool bFrozenArmor)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	//Assert(pCreature->isOusters());

	setTarget(pCreature);
	m_bFrozenArmor = bFrozenArmor;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceFieldToCreature::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectIceFieldToCreature" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
//	Assert(pCreature->isOusters());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

//	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
//	Assert( pTargetOusters != NULL );

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectIceFieldToCreature" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceFieldToCreature::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectIceFieldToCreature::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectIceFieldToCreature("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

