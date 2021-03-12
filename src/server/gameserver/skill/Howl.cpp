//////////////////////////////////////////////////////////////////////////////
// Filename    : Howl.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Howl.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GCAddEffect.h"
#include "ZoneUtil.h"
#include "EffectHowl.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Howl::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);

	// 패킷 핸들러에서 직접 수행하는 기술 핸들러이기 때문에
	// 스킬 핸들러가 널이다.
	//Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillInput input( pVampire );
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP = 10;
		bool bManaCheck = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll    = (rand()%100)<output.Range;
		bool bEffected   = pVampire->isFlag(Effect::EFFECT_CLASS_HOWL);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);

			ZoneCoord_t x = pVampire->getX();
			ZoneCoord_t y = pVampire->getY();
		
			ObjectID_t objectID = pVampire->getObjectID();

			EffectHowl* pEffect = new EffectHowl( pVampire );
			pEffect->setDeadline( output.Duration );

			pVampire->setFlag(Effect::EFFECT_CLASS_HOWL);
			pVampire->addEffect( pEffect );

			VAMPIRE_RECORD prev;
			pVampire->getVampireRecord( prev );
			pVampire->initAllStat();
			pVampire->sendModifyInfo( prev );
			
			_GCSkillToSelfOK1.setSkillType(SKILL_HOWL);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);

			_GCSkillToSelfOK2.setObjectID(objectID);
			_GCSkillToSelfOK2.setSkillType(SKILL_HOWL);
			_GCSkillToSelfOK2.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pVampire);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID( pVampire->getObjectID() );
			gcAddEffect.setEffectID( Effect::EFFECT_CLASS_HOWL );
			gcAddEffect.setDuration( output.Duration );

			pPlayer->sendPacket(&gcAddEffect);
		}
		else
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Howl g_Howl;
