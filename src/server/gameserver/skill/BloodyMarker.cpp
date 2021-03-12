//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyMarker.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyMarker.h"
#include "ZoneUtil.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToSelfOK3.h"
#include "Gpackets/GCDeleteObject.h"

#include "item/VampirePortalItem.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 인벤토리 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyMarker::execute(Vampire* pVampire, ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pSkillSlot)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Inventory* pInventory = pVampire->getInventory();

		Assert(pPlayer != NULL);
		Assert(pInventory != NULL);
		Assert(pZone != NULL);

		// 전쟁 존이라면 BloodyMark를 사용할 수 없다.
		// 일단은 ZoneID로 가는데.. ZoneInfo에 넣도록 해야한다.
		///*
		//int zoneID = pZone->getZoneID();
		//if (pZone->getZoneID()==1122 || pZone->getZoneID()==1123)

		// 이벤트 경기장/OX 막기. by sigi. 2002.8.31
        //if (zoneID==1005 || zoneID==1006)
		if (pZone->isNoPortalZone()
			|| pZone->isMasterLair()
		// 성 안으로도 막기. by bezz, Sequoia 2003. 1.20.
			|| pZone->isCastle()
			|| pZone->isHolyLand()
		)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		//*/

		Item* pItem = pInventory->getItem(X, Y);
		// 아이템이 널이거나, 포탈 아이템이 아니거나, 오브젝트ID가 틀리다면...
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM || pItem->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pItem);
		Assert(pVampirePortalItem != NULL);

		// 뱀파이어 포탈 아이템에 이미 임의의 위치가 기록되어 있을 경우에도...
		if (pVampirePortalItem->getZoneID() != 0 || pVampirePortalItem->getX() != 0 || pVampirePortalItem->getY() != 0)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);

		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// 마나를 줄이고...
			decreaseMana(pVampire, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// 아이템에다가 현재의 위치를 기록하고, 세이브한다.
			pVampirePortalItem->setZoneID(pZone->getZoneID());
			pVampirePortalItem->setX(pVampire->getX());
			pVampirePortalItem->setY(pVampire->getY());
			pVampirePortalItem->save(pVampire->getName(), STORAGE_INVENTORY, 0, X, Y);

			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setObjectID(InvenObjectID);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToInventoryOK1);
			
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
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

BloodyMarker g_BloodyMarker;
