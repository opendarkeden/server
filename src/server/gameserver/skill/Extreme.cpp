//////////////////////////////////////////////////////////////////////////////
// Filename    : Extreme.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Extreme.h"
#include "EffectExtreme.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCAddEffect.h"
#include "HitRoll.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void Extreme::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerself)" << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// Knowledge of Innate 가 있다면 hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);
		bool bEffected   = pVampire->isFlag(Effect::EFFECT_CLASS_EXTREME);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);

			// 스킬 레벨에 따라 데미지 보너스가 달라진다.
			SkillInput input( pVampire );
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			EffectExtreme* pEffect = new EffectExtreme(pVampire);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamageBonus(output.Damage);
			pVampire->addEffect(pEffect);
			pVampire->setFlag(Effect::EFFECT_CLASS_EXTREME);

			// 이로 인하여 바뀌는 능력치를 보낸다.
			VAMPIRE_RECORD prev;
			pVampire->getVampireRecord(prev);
			pVampire->initAllStat();
			pVampire->sendRealWearingInfo();
			pVampire->sendModifyInfo(prev);

			// 패킷을 만들어 보낸다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCSkillToSelfOK2, pVampire);

			// 이펙트가 붙었다고 알려준다.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pVampire->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_EXTREME);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcAddEffect);

			// set Next Run Time
			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerself)" << endl;

	__END_CATCH
}

void Extreme::execute(Vampire* pVampire, ObjectID_t TargetObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerself)" << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);


	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;

		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_EXTREME);

		ZoneCoord_t myX = pVampire->getX();
		ZoneCoord_t myY = pVampire->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && pTargetCreature->isVampire() )
		{
			Vampire* pTargetVampire= dynamic_cast<Vampire*>(pTargetCreature);

			ZoneCoord_t X   = pTargetVampire->getX();
			ZoneCoord_t Y   = pTargetVampire->getY();

			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

			// 스킬 레벨에 따라 데미지 보너스가 달라진다.
			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			EffectExtreme* pEffect = new EffectExtreme(pTargetVampire);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamageBonus(output.Damage);
			pTargetVampire->addEffect(pEffect);
			pTargetVampire->setFlag(Effect::EFFECT_CLASS_EXTREME);

			// 이로 인하여 바뀌는 능력치를 보낸다.
			VAMPIRE_RECORD prev;
			pTargetVampire->getVampireRecord(prev);
			pTargetVampire->initAllStat();
			pTargetVampire->sendRealWearingInfo();
			pTargetVampire->sendModifyInfo(prev);

			// 패킷을 만들어 보낸다.
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);
		

			_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
		    _GCSkillToObjectOK3.setSkillType(SkillType);
		    _GCSkillToObjectOK3.setTargetXY (X, Y);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC())
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
	
				_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
				_GCSkillToObjectOK2.setSkillType(SkillType);
				_GCSkillToObjectOK2.setDuration(output.Duration);
		
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}
			else
			{
				Assert(false);
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);

			// 이펙트가 붙었다고 알려준다.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pTargetVampire->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_EXTREME);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pTargetVampire->getX(), pTargetVampire->getY(), &gcAddEffect);

			// set Next Run Time
			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerself)" << endl;

	__END_CATCH
}

void Extreme::execute(Vampire* pVampire)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerself)" << endl;

	Assert(pVampire != NULL);

	if( !pVampire->hasSkill(SKILL_EXTREME) ) return;

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);


		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		//GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;

		ZoneCoord_t myX = pVampire->getX();
		ZoneCoord_t myY = pVampire->getY();

		int oX, oY;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		for(oX = -4; oX <= 4; oX++)
		for(oY = -4; oY <= 4; oY++)
		{
			int tileX = myX+oX;
			int tileY = myY+oY;
			if (!rect.ptInRect(tileX, tileY)) continue;

			// 타일 위에! 뱀파이어가 있는지 본다!
			Tile& tile = pZone->getTile(tileX, tileY);
			Creature * pTargetCreature = NULL;
			if(tile.hasCreature(Creature::MOVE_MODE_WALKING)) pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

			if( pTargetCreature != NULL && pTargetCreature != pVampire && pTargetCreature->isVampire() ) {

				bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_EXTREME);

				if( bEffected ) continue;

				Vampire* pTargetVampire= dynamic_cast<Vampire*>(pTargetCreature);

				// 스킬 레벨에 따라 데미지 보너스가 달라진다.
				SkillInput input(pVampire);
				SkillOutput output;
				computeOutput(input, output);

				// 이펙트 클래스를 만들어 붙인다.
				EffectExtreme* pEffect = new EffectExtreme(pTargetVampire);
				pEffect->setDeadline(output.Duration);
				pEffect->setDamageBonus(output.Damage);
				pTargetVampire->addEffect(pEffect);
				pTargetVampire->setFlag(Effect::EFFECT_CLASS_EXTREME);

				// 이로 인하여 바뀌는 능력치를 보낸다.
				VAMPIRE_RECORD prev;
				pTargetVampire->getVampireRecord(prev);
				pTargetVampire->initAllStat();
				pTargetVampire->sendRealWearingInfo();
				pTargetVampire->sendModifyInfo(prev);

				/*
				if (pTargetCreature->isPC())
				{
					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);

					_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
					_GCSkillToObjectOK2.setSkillType(getSkillType());
					_GCSkillToObjectOK2.setDuration(output.Duration);

					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				}
				else
				{
					Assert(false);
				}
				*/

				// 이펙트가 붙었다고 알려준다.
				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID(pTargetVampire->getObjectID());
				gcAddEffect.setEffectID(Effect::EFFECT_CLASS_EXTREME);
				gcAddEffect.setDuration(output.Duration);
				pZone->broadcastPacket(pTargetVampire->getX(), pTargetVampire->getY(), &gcAddEffect);
			}
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerself)" << endl;

	__END_CATCH
}


Extreme g_Extreme;
