//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromBlood.cpp
// Written by  : excel96
// Description : ProtectionFromBlood에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#include "EffectProtectionFromBlood.h"
#include "Creature.h"
#include "Slayer.h"
#include "DB.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectProtectionFromBlood::EffectProtectionFromBlood(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromBlood::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Resist_t resist = pCreature->getResist(MAGIC_DOMAIN_BLOOD);
	resist = min(MAX_RESIST,(int)(resist + m_Resist));
	pCreature->setResist(MAGIC_DOMAIN_BLOOD, resist);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromBlood::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromBlood::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromBlood::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	pCreature->removeFlag(Effect::EFFECT_CLASS_PROTECTION_FROM_BLOOD);

	Resist_t resist = pCreature->getResist(MAGIC_DOMAIN_BLOOD);
	resist = max(0,(int)(resist - m_Resist));
	pCreature->setResist(MAGIC_DOMAIN_BLOOD, resist);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PROTECTION_FROM_BLOOD);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromBlood::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectProtectionFromBlood::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectProtectionFromBlood("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromBloodLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

EffectProtectionFromBloodLoader* g_pEffectProtectionFromBloodLoader = NULL;
