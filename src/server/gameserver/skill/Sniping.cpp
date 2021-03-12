//////////////////////////////////////////////////////////////////////////////
// Filename    : Sniping.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Sniping.h"
#include "ItemUtil.h"
#include "ZoneUtil.h"
#include "EffectFadeOut.h"
#include "EffectSnipingMode.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void Sniping::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 무장하고 있는 무기가 널이거나, 총이 아니라면 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL 
			|| isArmsWeapon(pItem) == false
			|| pSlayer->hasRelicItem()
			)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t x = pSlayer->getX();
		ZoneCoord_t y = pSlayer->getY();

		Tile& rTile = pZone->getTile( pSlayer->getX(), pSlayer->getY() );
		int  RequiredMP  = pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || 
			                pSlayer->isFlag(Effect::EFFECT_CLASS_FADE_OUT) ||
							pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) ||
							pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) ||
							rTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION)!=NULL;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			// 능력치 재계산은 EffectFadeOut이 unaffect되면서,
			// 즉 EffectSnipingMode가 붙으면서 이루어진다.
			EffectFadeOut* pEffect= new EffectFadeOut(pSlayer);
			pEffect->setDuration(output.Duration);
			pEffect->setDeadline(40);
			pEffect->setSniping();
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_FADE_OUT);

			// 경험치를 올린다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);
			shareAttrExp(pSlayer, ExpUp, 1, 8, 1, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			// 패킷을 보낸다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);

			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

void Sniping::checkRevealRatio(Creature* pCreature, int base, int divisor)
{
	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());
	Assert(pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE));
	
	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	Assert(pSlayer != NULL);

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	SkillSlot* pSkillSlot = pSlayer->getSkill(SKILL_SNIPING);
	Assert(pSkillSlot != NULL);

	EffectSnipingMode* pEffectSM = dynamic_cast<EffectSnipingMode*>(pCreature->findEffect(Effect::EFFECT_CLASS_SNIPING_MODE));
	Assert(pEffectSM != NULL);

	int penalty = base - (pSkillSlot->getExpLevel()/divisor);
	pEffectSM->setRevealRatio(pEffectSM->getRevealRatio() + penalty);

	if (rand()%100 < pEffectSM->getRevealRatio())
	{
		//addUnSnipingModeCreature(pZone, pCreature, true);
		// 이펙트가 꺼지도록 한다.
		// 2003. 1. 17 by bezz
		pEffectSM->setDeadline(0);
	}
}

Sniping g_Sniping;
