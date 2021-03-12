//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyTunnel.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyTunnel.h"
#include "ZoneUtil.h"
#include "EffectSchedule.h"
#include "EffectVampirePortal.h"

#include "item/VampirePortalItem.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToSelfOK3.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 인벤토리 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyTunnel::execute(Vampire* pVampire, ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pSkillSlot)
	
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
		Assert(pZone != NULL);
		Assert(pInventory!= NULL);

		// 전쟁 존이라면 BloodyTunnel를 사용할 수 없다.
		// 일단은 ZoneID로 가는데.. ZoneInfo에 넣도록 해야한다.
		///*
		//if (pZone->getZoneID()==1122 || pZone->getZoneID()==1123)
		// 이벤트 경기장/OX 막기. by sigi. 2002.8.31
		//int zoneID = pZone->getZoneID();
		//if (zoneID==1005 || zoneID==1006)
		if (pZone->isNoPortalZone()
			|| pZone->isMasterLair()
			|| pZone->isCastle()
			|| pZone->isHolyLand())
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		//*/


		Item* pItem = pInventory->getItem(X, Y);
		// 아이템이 없거나, 뱀파이어 포탈 아이템이 아니거나, OID가 틀리다면 기술 사용 불가
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM || pItem->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pItem);
		Assert(pVampirePortalItem != NULL);

		// 뱀파이어 포탈 아이템에 기록된 위치가 없을 경우에는 실패다.
		ZoneID_t    zoneid = pVampirePortalItem->getZoneID();
		ZoneCoord_t tx     = pVampirePortalItem->getX();
		ZoneCoord_t ty     = pVampirePortalItem->getY();
		if (zoneid == 0)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// 얻어온 목표 존과 좌표를 검증한다.
		Zone* pTargetZone = getZoneByZoneID(zoneid);

		// 아담의 성지와 다른 존과는 연결되지 않는다.
		if (pZone->isHolyLand() != pTargetZone->isHolyLand())
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}

		//cout << "타겟 존 포인터 획득 성공" << endl;

		VSRect* pRect = pTargetZone->getOuterRect();

		if (!pRect->ptInRect(tx, ty))
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		//cout << "좌표 검증 성공" << endl;
		
		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);
		//bool bHitRoll       = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot);
		bool bHitRoll       = true;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// 각각의 존에다가 포탈을 더한다.
			ZONE_COORD s_coord;
			ZONE_COORD t_coord;

			s_coord.id = pZone->getZoneID();
			s_coord.x  = pVampire->getX();
			s_coord.y  = pVampire->getY();

			t_coord.id = pTargetZone->getZoneID();
			t_coord.x  = tx;
			t_coord.y  = ty;

			pZone->addVampirePortal(s_coord.x, s_coord.y, pVampire, t_coord);
			pTargetZone->addVampirePortal(t_coord.x, t_coord.y, pVampire, s_coord);

			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setObjectID(InvenObjectID);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			// 차지 수를 줄인다.
			pVampirePortalItem->setCharge(pVampirePortalItem->getCharge()-1);

			if (pVampirePortalItem->getCharge() > 0)
			{
				// 아직 차지가 남았다면 살려둔다.
				pVampirePortalItem->save(pVampire->getName(), STORAGE_INVENTORY, 0, X, Y);
			}
			else
			{
				// 포탈 아이템의 차지가 다 소모되었다면 삭제시킨다.
				pInventory->deleteItem(X, Y);
				pVampirePortalItem->destroy();

				// 아이템 포인터 자체가 지워지고, NULL이 되면,
				// 이펙트 내부에서의 아이템 포인터도 NULL이 되겠지...
				SAFE_DELETE(pVampirePortalItem);
			}

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

BloodyTunnel g_BloodyTunnel;
