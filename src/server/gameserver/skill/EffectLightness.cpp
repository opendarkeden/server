
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLightness.cpp
// Written by  : excel96
// Description : Lightness에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#include "EffectLightness.h"
#include "Creature.h"
#include "Zone.h"
#include "Player.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCModifyInformation.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectLightness::EffectLightness(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLightness::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLightness::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	pCreature->removeFlag(Effect::EFFECT_CLASS_LIGHTNESS);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_LIGHTNESS);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	Player* pPlayer = pCreature->getPlayer();
	if ( pPlayer != NULL )
	{
		GCModifyInformation gcMI;

		Sight_t oldSight = pCreature->getSight();
		Sight_t newSight = pCreature->getEffectedSight();

		if ( oldSight != newSight )
		{
			pCreature->setSight( newSight );
			pZone->updateScan(pCreature, oldSight, newSight);
			gcMI.addShortData(MODIFY_VISION, newSight);
			pPlayer->sendPacket( &gcMI );
		}

		GCChangeDarkLight gcChangeDarkLight;
		gcChangeDarkLight.setDarkLevel(pZone->getDarkLevel());
		gcChangeDarkLight.setLightLevel(pZone->getLightLevel());

		pPlayer->sendPacket(&gcChangeDarkLight);
	}


	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectLightness::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectLightness("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

