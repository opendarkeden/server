//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonCasket.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SummonCasket.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK3.h"
#include "GCDeleteObject.h"
#include "GCAddEffect.h"
#include "ZoneUtil.h"
#include "RankBonus.h"

#include "EffectSummonCasket.h"
#include "EffectFlare.h"
#include "EffectDoom.h"
#include "EffectSeduction.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void SummonCasket::execute(Vampire* pVampire, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	//cout << "SummonCasket try.." << endl;

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		if (!pVampire->isVampire()
			&& !pVampire->isMonster())
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
			return;
		}


		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK3 _GCSkillToSelfOK3;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pVampire->getX();
		ZoneCoord_t y = pVampire->getY();

		// Knowledge of Summon �� �ִٸ� hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_SUMMON ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_SUMMON );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll       = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot, HitBonus);
		bool bTileCheck     = canBurrow(pZone, x, y);
		bool bMoveModeCheck = pVampire->isWalking();
		bool bEffected      = pVampire->isFlag(Effect::EFFECT_CLASS_CASKET);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck && bMoveModeCheck && !bEffected)
		{
			//cout << "SummonCasket Success" << endl;

			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			
			// �����̾ �� ������ �����ϱ� ������ ��� ��Ŷ���� ������.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK3.setXY(x, y);
			_GCSkillToSelfOK3.setSkillType(SkillType);
			_GCSkillToSelfOK3.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK3, pVampire);

			//---------------------------------------------------------------
			// ������ ���� ���� ȿ���� �����Ѵ�.
			//---------------------------------------------------------------
			EffectManager* pEffectManager = pVampire->getEffectManager();
			Assert(pEffectManager!=NULL);

			Effect* pCheckEffect = NULL;

			// ������� level�� ���Ѵ�.
			int userLevel = pVampire->getLevel();

			Effect::EffectClass effectClass;

			// EFFECT_CLASS_FLARE
			effectClass = Effect::EFFECT_CLASS_FLARE;
			pCheckEffect = pEffectManager->findEffect(effectClass);
			if (pCheckEffect!=NULL)
			{
				int level =	(dynamic_cast<EffectFlare*>(pCheckEffect))->getLevel();

				if (level < userLevel)
				{
					pEffectManager->deleteEffect( effectClass );
					pVampire->removeFlag( effectClass );
				}
			}

			// EFFECT_CLASS_DOOM
			effectClass = Effect::EFFECT_CLASS_DOOM;
			pCheckEffect = pEffectManager->findEffect(effectClass);
			if (pCheckEffect!=NULL)
			{
				int level =	(dynamic_cast<EffectDoom*>(pCheckEffect))->getLevel();

				if (level < userLevel)
				{
					pEffectManager->deleteEffect( effectClass );
					pVampire->removeFlag( effectClass );
				}
			}

			// EFFECT_CLASS_SEDUCTION
			effectClass = Effect::EFFECT_CLASS_SEDUCTION;
			pCheckEffect = pEffectManager->findEffect(effectClass);
			if (pCheckEffect!=NULL)
			{
				int level =	(dynamic_cast<EffectSeduction*>(pCheckEffect))->getLevel();

				if (level < userLevel) {
					pEffectManager->deleteEffect( effectClass );
					pVampire->removeFlag( effectClass );
				}
			}


			//---------------------------------------------------------------
			// ����Ʈ ������Ʈ�� ������ ���δ�.
			//---------------------------------------------------------------
			EffectSummonCasket* pEffect = new EffectSummonCasket(pVampire);
			pEffect->setDeadline(99999999);
			pEffect->setType(0);
			pVampire->addEffect(pEffect);
			pVampire->setFlag(Effect::EFFECT_CLASS_CASKET);

			// SUMMON CASKET �� ���� ���ϴ� �ɷ�ġ�� ���Ѵ�.. 2002.12.13  by bezz.
			VAMPIRE_RECORD prev;

			pVampire->getVampireRecord(prev);
			pVampire->initAllStat();
			pVampire->sendRealWearingInfo();
			pVampire->sendModifyInfo(prev);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pVampire->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_CASKET);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcAddEffect, pVampire);
						
			pSkillSlot->setRunTime();
		} 
		else 
		{
			//cout << "SummonCasket Failed" << endl;
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		//cout << "SummonCasket Failed2" << endl;
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
// ���� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void SummonCasket::execute(Monster* pMonster)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;
	/*
	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_CASKET))
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		GCSkillToSelfOK3 _GCSkillToSelfOK3;

		SkillType_t SkillType  = SKILL_SUMMON_CASKET;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);
		bool bHitRoll       = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		bool bTileCheck     = canBurrow(pZone, x, y);
		bool bMoveModeCheck = pMonster->isWalking();
		bool bEffected      = pMonster->isFlag(Effect::EFFECT_CLASS_CASKET);

		if (bRangeCheck && bHitRoll && bTileCheck && bMoveModeCheck && !bEffected)
		{
			// ���͸� �� ������ �����ϱ� ������ ��� ��Ŷ���� ������.
			_GCSkillToSelfOK3.setXY(x, y);
			_GCSkillToSelfOK3.setDuration(0);
			_GCSkillToSelfOK3.setSkillType(SkillType);
		
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK3);

			// �� ���� �����ִ� ���� �����϶�� �˸���.
			GCDeleteObject gcDO;
			gcDO.setObjectID(pMonster->getObjectID());
			pZone->broadcastPacket(x, y, &gcDO);

			// �� �ӿ��ٰ� ���͸� �߰��Ѵ�.
			addBurrowingCreature(pZone, pMonster, x, y);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
	*/

	__END_CATCH

}

SummonCasket g_SummonCasket;
