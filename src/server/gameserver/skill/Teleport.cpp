//////////////////////////////////////////////////////////////////////////////
// Filename    : Teleport.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Teleport.h"

#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK5.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러 
//////////////////////////////////////////////////////////////////////////////
void Teleport::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

/*		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType());
			return;
		}
*/
		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		// NPC는 공격할 수가 없다.
		//		bool bIncreaseDomainExp = pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (!rect.ptInRect(X, Y) )
		{
			executeSkillFailException(pOusters, getSkillType());
		}

		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/10;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, output.Range);
		bool bEffected	 = pOusters->hasRelicItem() 
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) 
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected )
		{
			// 빠르게 PC를 움직여준다.
			if (pZone->moveFastPC(pOusters, pOusters->getX(), pOusters->getY(), X, Y, getSkillType())) 
			{
				decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

				_GCSkillToTileOK1.setSkillType(SkillType);
				_GCSkillToTileOK1.setCEffectID(0);
				_GCSkillToTileOK1.setX(X);
				_GCSkillToTileOK1.setY(Y);
				_GCSkillToTileOK1.setRange(0);
				_GCSkillToTileOK1.setDuration(0);

				_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
				_GCSkillToTileOK5.setSkillType(SkillType);
				_GCSkillToTileOK5.setX(X);
				_GCSkillToTileOK5.setY(Y);
				_GCSkillToTileOK5.setRange(0);
				_GCSkillToTileOK5.setDuration(0);

				// 자신에게 바뀐 MP를 알려준다.
				pPlayer->sendPacket(&_GCSkillToTileOK1);
				pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &_GCSkillToTileOK5, pOusters);

				pOustersSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailException(pOusters, getSkillType());
			}
		} 
		else 
		{
			executeSkillFailException(pOusters, getSkillType());
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;


	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Teleport::execute(Ousters * pOusters, ObjectID_t TargetObjectID, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

//		bool bIncreaseDomainExp = pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND);

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
/*
		SkillInput input(pOusters);
		SkillOutput output;
		computeOutput(input, output);

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, output.Range);
		bool bEffected	 = pOusters->hasRelicItem();

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected )
		{

			// 빠르게 PC를 움직여준다.
			if (pZone->moveFastPC(pOusters, pOusters->getX(), pOusters->getY(), pTargetCreature->getX(), pTargetCreature->getY())) 
			{
				GCModifyInformation	gcMI;

				decreaseMana(pOusters, RequiredMP, gcMI);

				// 자신에게 바뀐 HP를 알려준다.
				pPlayer->sendPacket(&gcMI);

				// 주위에 HP가 바꼈다고 알린다.
				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pOusters->getObjectID());
				gcStatusCurrentHP.setCurrentHP(pOusters->getHP());
				pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcStatusCurrentHP, pOusters);

				pOustersSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
			}
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
		}
		*/
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Teleport g_Teleport;

