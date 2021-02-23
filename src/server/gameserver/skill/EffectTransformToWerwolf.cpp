//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransformToWerwolf.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectTransformToWerwolf.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GCAddVampireFromTransformation.h"
#include "Gpackets/GCAddMonsterFromTransformation.h"
#include "ZoneUtil.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTransformToWerwolf::EffectTransformToWerwolf(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWerwolf::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWerwolf::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWerwolf::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	//cout << "EffectTransfromToWerwolf " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	Assert(pCreature != NULL);

	if (pCreature->isSlayer())
	{
		//cout << "EffectTransfromToWerwolf::unaffect() : Slayer cannot transfrom to wolf!" << endl;
		throw Error("EffectTransfromToWerwolf::unaffect() : Slayer cannot transfrom to wolf!");
	}

	unaffect(pCreature);

	//cout << "EffectTransfromToWerwolf " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWerwolf::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectTransfromToWerwolf " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 원래 모습으로 되돌리고, 플래그를 제거한다.
	addUntransformCreature(pZone, pCreature, false);
	pCreature->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF);

	// 능력치를 원래대로 되돌린다.
	if (pCreature->isVampire())
	{
		Vampire* pTargetVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;

		pTargetVampire->getVampireRecord(prev);
		pTargetVampire->initAllStat();
		pTargetVampire->sendRealWearingInfo();
		pTargetVampire->sendModifyInfo(prev);
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		pMonster->initAllStat();
	}
	else
	{
		Assert(false);
	}

	//cout << "EffectTransfromToWerwolf " << "unaffect END" << endl;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWerwolf::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTransformToWerwolf::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTransformToWerwolf("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
