//////////////////////////////////////////////////////////////////////////////
// Filename    : Invisibility.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Invisibility.h"
#include "EffectFadeOut.h"
#include "Monster.h"
#include "RankBonus.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 셀프
//////////////////////////////////////////////////////////////////////////////
void Invisibility::execute(Vampire* pVampire, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pVampire->getX();
		ZoneCoord_t y = pVampire->getY();

		// Knowledge of Innate 가 있다면 hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		Tile& rTile = pZone->getTile( pVampire->getX(), pVampire->getY() );

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot, HitBonus);
		bool bEffected   = pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) || 
				            pVampire->isFlag(Effect::EFFECT_CLASS_FADE_OUT) || 
							pVampire->hasRelicItem() ||
							pVampire->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) ||
							pVampire->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) ||
							rTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION) != NULL;
		
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);
		
			// 점점 사라지는 이펙트를 생성해서 붙인다.
			// 실제로 사라지는 것은 이 이펙트 내부에서다.
			// (한번에 '팍'하고 사라지는 게 아니라서 붙이는 이펙트다.)
			EffectFadeOut* pEffect= new EffectFadeOut(pVampire);
			pEffect->setDuration(output.Duration);
			pEffect->setDeadline(40);
			pEffect->setInvisibility();
			pVampire->addEffect(pEffect);
			pVampire->setFlag(Effect::EFFECT_CLASS_FADE_OUT);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);

			_GCSkillToSelfOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pVampire);

			pSkillSlot->setRunTime(output.Delay);
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

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void Invisibility::execute(Monster* pMonster)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();

		Assert(pZone != NULL);

		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;
			return;
		}

		SkillType_t SkillType  = SKILL_INVISIBILITY;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck = checkZoneLevelToUseSkill(pMonster);
		bool bHitRoll    = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		bool bEffected   = (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) || 
				            pMonster->isFlag(Effect::EFFECT_CLASS_FADE_OUT));

		if (bRangeCheck && bHitRoll && !bEffected)
		{
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			// 점점 사라지는 이펙트를 생성해서 붙인다.
			// 실제로 사라지는 것은 이 이펙트 내부에서다.
			// (한번에 '팍'하고 사라지는 게 아니라서 붙이는 이펙트다.)
			EffectFadeOut* pEffect= new EffectFadeOut(pMonster);
			pEffect->setDuration(output.Duration);
			pEffect->setDeadline(40);	
			pEffect->setInvisibility();	
			pMonster->addEffect(pEffect);
			pMonster->setFlag(Effect::EFFECT_CLASS_FADE_OUT);

			_GCSkillToSelfOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToSelfOK2.setDuration(0);
			_GCSkillToSelfOK2.setSkillType(SkillType);

			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2);
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

Invisibility g_Invisibility;
