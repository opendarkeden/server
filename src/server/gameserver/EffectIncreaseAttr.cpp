//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIncreaseAttr.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectIncreaseAttr.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "PacketUtil.h"

#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"
#include "GCOtherModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectIncreaseAttr::EffectIncreaseAttr(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIncreaseAttr::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIncreaseAttr::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIncreaseAttr::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIncreaseAttr::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	if(pCreature->isSlayer())
	{
		pCreature->removeFlag(Effect::EFFECT_CLASS_INCRASE_ATTR);

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		SLAYER_RECORD prev;
		pSlayer->getSlayerRecord(prev);
		pSlayer->initAllStat();
		pSlayer->sendRealWearingInfo();
		pSlayer->sendModifyInfo(prev);

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pCreature->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_INCRASE_ATTR);
		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);
	}
	else if (pCreature->isVampire() )
	{
		pCreature->removeFlag(Effect::EFFECT_CLASS_INCRASE_ATTR);

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		VAMPIRE_RECORD prev;
		pVampire->getVampireRecord(prev);
		pVampire->initAllStat();
		pVampire->sendRealWearingInfo();
		pVampire->sendModifyInfo(prev);

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pCreature->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_INCRASE_ATTR);
		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, pVampire, &prev);
		pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcOtherModifyInfo, pVampire);
	}
	else if (pCreature->isOusters() )
	{
		pCreature->removeFlag(Effect::EFFECT_CLASS_INCRASE_ATTR);

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		OUSTERS_RECORD prev;
		pOusters->getOustersRecord(prev);
		pOusters->initAllStat();
		pOusters->sendRealWearingInfo();
		pOusters->sendModifyInfo(prev);

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pCreature->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_INCRASE_ATTR);
		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, pOusters, &prev);
		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcOtherModifyInfo, pOusters);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIncreaseAttr::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectIncreaseAttr::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectIncreaseAttr("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
