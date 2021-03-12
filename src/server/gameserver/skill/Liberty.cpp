//////////////////////////////////////////////////////////////////////////////
// Filename    : Liberty.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Liberty.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"

#include "EffectParalyze.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Liberty::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType());
			return;
		}

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !pTargetCreature->isOusters())
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() +  pOustersSkillSlot->getExpLevel()/3;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange()) && canHit( pOusters, pTargetCreature, SkillType, pOustersSkillSlot->getExpLevel() );
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bSatisfyRequire	= pOusters->satisfySkillRequire( pSkillInfo );
		bool bHPCheck	= pTargetOusters->isFlag( Effect::EFFECT_CLASS_PARALYZE );

		int Ratio = 0;
		EffectParalyze* pEffect = dynamic_cast<EffectParalyze*>(pTargetOusters->findEffect( Effect::EFFECT_CLASS_PARALYZE ));
		if ( pEffect != NULL )
		{
			if ( pOustersSkillSlot->getExpLevel() <= 15 )
			{
				Ratio = ( pOusters->getLevel() + ( pOustersSkillSlot->getExpLevel() * 8.0 / 3.0 ) ) - pEffect->getLevel();
			}
			else
			{
				Ratio = ( pOusters->getLevel() + 20 + ( pOustersSkillSlot->getExpLevel() * 4.0 / 3.0 ) ) - pEffect->getLevel();
				if ( pOustersSkillSlot->getExpLevel() == 30 ) Ratio *= 1.1;
			}
		}

		bool bHitRoll2 = (rand()%100) < Ratio;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bSatisfyRequire && bHPCheck)
		{
			// 마나를 줄인다.
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

			// 이펙트의 효과와 지속시간을 계산한다.
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			input.TargetType = SkillInput::TARGET_OTHER;
			computeOutput(input, output);

			pEffect->setDeadline(0);

			// 패킷을 준비해서 보낸다.
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pOusters != pTargetCreature && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);
		
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToObjectOK5 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

Liberty g_Liberty;
