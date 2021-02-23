//////////////////////////////////////////////////////////////////////////////
// Filename    : Regeneration.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RegenerationSkill.h"
#include "EffectRegeneration.h"
#include "Vampire.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCSkillFailed1.h"
#include "Gpackets/GCSkillFailed2.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////
//
// RegenerationSkill::execute()
//
//////////////////////////////////////////////////////////////////////
void RegenerationSkill::execute(Slayer* pSlayer, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;
		/*

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		// Player를 받아온다.
		Player * pPlayer = pSlayer->getPlayer();
		
		// Zone을 받아온다.
		Zone * pZone = pSlayer->getZone();
		Assert(pZone);
		Assert(pSkillSlot);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;
		GCSkillFailed1 _GCSkillFailed1;
		GCSkillFailed2 _GCSkillFailed2;

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Assert(pSkillInfo);
		
		SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

		// 명중률을 받아온다.
		ToHit_t ToHit = pSlayer->getINT(ATTR_CURRENT);
		
		bool bTargetEffected = false;
		if (pSlayer->isFlag(Effect::EFFECT_CLASS_REGENERATION))
			bTargetEffected = true;	

		int RemainMP = (int)pSlayer->getMP(ATTR_CURRENT) - (int)pSkillInfo->getConsumeMP();
		bool bModifyMP = false;
		if (RemainMP >= 0 && verifyRunTime(pSkillSlot) && 
			pZone->getZoneLevel(pSlayer->getX(), pSlayer->getY()) != 0
			&& bTargetEffected == false
			)
		{
			pSlayer->setMP(RemainMP , ATTR_CURRENT);
			bModifyMP = true;
		}

		// 기술성공률 검증.
		if (bModifyMP && (ToHit + SkillLevel > Random(0, 100))) 
		{

			// Effect Object를 생성한다.
			EffectRegeneration * pEffectRegeneration = new EffectRegeneration (pSlayer);

			HP_t generationHP = computeSkillDamage(pSkillSlot, pSkillInfo);	// 재생되는 HP의 총 양.
			Duration_t Duration = max(1, (int)10);
			pEffectRegeneration->setDelay(REGENERATION_DELAY);  
			pEffectRegeneration->setDeadline(Duration * 10);
			pEffectRegeneration->setPoint(generationHP / (Duration*10 / REGENERATION_DELAY));
			pEffectRegeneration->affect(pSlayer);

			// Creature에 Effect Flag를 On 시킨다.
			pSlayer->setFlag(Effect::EFFECT_CLASS_REGENERATION);

			// Creature의 effectManager에 이 Effect를 추가시킨다.
			pSlayer->addEffect(pEffectRegeneration);

			_GCSkillToSelfOK1.addShortData(MODIFY_CURRENT_MP , RemainMP);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(Duration * 10);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(Duration * 10);
		
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToSelfOK2, pSlayer);
			pSkillSlot->setRunTime();

		} else {

			_GCSkillFailed1.setSkillType(getSkillType());
			if (bModifyMP)
				_GCSkillFailed1.addShortData(MODIFY_CURRENT_MP, RemainMP);
			pPlayer->sendPacket(&_GCSkillFailed1);

			_GCSkillFailed2.setObjectID(pSlayer->getObjectID());
	//		_GCSkillFailed2.setTargetObjectID(pSlayer->getObjectID());
			_GCSkillFailed2.setSkillType(SkillType);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillFailed2, pSlayer);

		}
	} 
	catch(Throwable & t) 
	{
		GCSkillFailed1 _GCSkillFailed1;
		_GCSkillFailed1.setSkillType(getSkillType());
		pSlayer->getPlayer()->sendPacket(&_GCSkillFailed1);
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
	*/

	__END_CATCH
}

RegenerationSkill g_RegenerationSkill;
