////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRedeemMotorcycle.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRedeemMotorcycle.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "ParkingCenter.h"
#include "Item.h"
#include "Zone.h"
#include "Belt.h"
#include "DB.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/Key.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionRedeemMotorcycle::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionRedeemMotorcycle::execute (Creature * pCreature1 , Creature* pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	// 일단 클라이언트를 위해 ok패킷을 하나 날려주고...
	GCNPCResponse answerOKpkt;
	pPlayer->sendPacket(&answerOKpkt);

	// 플레이어가 슬레이어인지 검사한다.
	if (pCreature2->isSlayer())
	{
		Slayer*    pSlayer     = dynamic_cast<Slayer*>(pCreature2);
		Zone*      pZone       = pSlayer->getZone();
		Inventory* pInventory  = pSlayer->getInventory();
		uint       InvenWidth  = pInventory->getWidth();
		uint       InvenHeight = pInventory->getHeight();
		Item*      pItem       = NULL;

		Inventory* pBeltInventory = NULL;
		uint		BeltInvenWidth = 0;
		uint		BeltInvenHeight = 0;
		Item*      pBelt          = NULL;
		
		pBelt	= pSlayer->getWearItem(Slayer::WEAR_BELT);
		if(pBelt != NULL)
		{
			pBeltInventory = ((Belt*)pBelt)->getInventory();

			BeltInvenWidth = pBeltInventory->getWidth();
			BeltInvenHeight = pBeltInventory->getHeight();
		}
							  
		// 인벤토리를 검색한다.
		for (uint y=0; y<InvenHeight; y++)
		{
			for (uint x=0; x<InvenWidth; x++)
			{
				// x, y에 아이템이 있다면...
				if (pInventory->hasItem(x, y))
				{
					pItem = pInventory->getItem(x, y);
					if (load(pItem, pSlayer, pZone, pSlayer->getX(), pSlayer->getY()))
					{
						return;
					}
				}
			}
		}

		if(pBelt != NULL)
		{
			// 벨트를 검색한다
			for (uint y = 0; y < BeltInvenHeight; y++)
			{
				for(uint x = 0; x < BeltInvenWidth; x++)
				{

					if(pBeltInventory->hasItem(x, y))
					{
						pItem= pBeltInventory->getItem(x, y);
						if (load(pItem, pSlayer, pZone, pSlayer->getX(), pSlayer->getY()))
						{
							return;
						}
					}

				}
			}
		}
	}
	else // 뱀파이어라면...오토바이를 찾아줄 이유가 있을까?
	{
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool ActionRedeemMotorcycle::load(Item* pItem, Slayer* pSlayer, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) const
	throw()
{
	bool bFound = false;

	__BEGIN_TRY

	// 단서가 되는 아이템이 키가 아니라면 false를 리턴.
	if (pItem->getItemClass() != Item::ITEM_CLASS_KEY) return false;

	Key* pKey = dynamic_cast<Key*>(pItem);
	ItemID_t   targetID = pKey->getTarget();

	try {

	// 키가 맞다면 키의 타겟이 되는 아이템의 아이템 ID를 얻어낸다.
	Statement* pStmt    = NULL;
	Result*    pResult  = NULL;

	// targetID가 0인 경우는.. targetID(motorcycleObject의 ItemID)가 설정이 안된 경우다.
	// 이 때는 임시로 targetID를 key의 ItemID와 같게 하면 된다...고 본다.
	// targetID가 motorcycle의 itemID로 들어가기 때문에..
	// broadcasting 등에서.. Assert()에 의해서 다운되었다...고 보여진다.  - -;
	// by sigi. 2002.12.25 x-mas T_T;
	if (targetID==0)
	{
		targetID = pKey->setNewMotorcycle(pSlayer);
/*		// (!) MotorcycleObject를 생성하고 MotorcycleItemID==Target를 받아야 한다.
		// 이 코드 제발 함수로 빼기를.. -_-; by sigi
		list<OptionType_t> optionNULL;
		Item* pMotorcycle = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MOTORCYCLE, 0, optionNULL);
		Assert(pMotorcycle != NULL);
		(pZone->getObjectRegistry()).registerObject(pMotorcycle);

		pMotorcycle->create(pSlayer->getName(), STORAGE_ZONE, pZone->getZoneID(), pSlayer->getX(), pSlayer->getY());
		pKey->setTarget(pMotorcycle->getItemID());

		targetID = pMotorcycle->getItemID();

		// targetID를 DB에도 update시켜야 한다.
		BEGIN_DB
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery(
						"UPDATE KeyObject SET Target=%d WHERE ItemID=%d", 
									targetID, pKey->getItemID());

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)

		// 밑에서 pMotorcycle을 사용해도 되겠지만, 기존 코드 안 건드릴려고 여기서 지운다. 
		SAFE_DELETE(pMotorcycle);*/
	}
	else
	{
		// 한번 모터사이클이랑 키랑 연결됐는데 모터사이클을 누가 자꾸 지우나보다.
		// 키에 연결된 모터사이클이 실제로 디비에 있는지 체크하고 없으면 새로 만들어서 넣어준다.
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery("SELECT ItemID FROM MotorcycleObject WHERE ItemID=%lu", targetID);

			if ( !pResult->next() )
			{
				Key* pKey = dynamic_cast<Key*>(pItem);
				Assert( pKey != NULL );

				targetID = pKey->setNewMotorcycle(pSlayer);
			}

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt);
	}

	
	// 필살 방어 코드 -_-;
	if (targetID==0)
	{
		filelog("errorLog.txt", "[ActionRedeemMotorcycle] itemID=%d, motorItemID=%d", (int)pItem->getItemID(), (int)targetID);
		return false;
	}

	// DB에 쿼리하기 전에 먼저 객체가 생성되어 있지는 않은지 체크한다.
	if (g_pParkingCenter->hasMotorcycleBox(targetID)) 
	{
		// 자꾸 다운되어서 혹시나 하고..
		// 일단 주석처리한다.  by sigi. 2002.11.16
		/*
		if (!pSlayer->hasRideMotorcycle()
			&& !pSlayer->isFlag(Effect::EFFECT_CLASS_COMA))
		{
			//return false;

			// by sigi. 2002.11.14
			MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox(targetID);

			// 있다면 소환한다.
			if (pMotorcycleBox!=NULL
				&& !pMotorcycleBox->isTransport())
			{
				Zone* pMotorZone = pMotorcycleBox->getZone();
				ZoneCoord_t motorX = pMotorcycleBox->getX();
				ZoneCoord_t motorY = pMotorcycleBox->getY();
				Motorcycle* pMotorcycle = pMotorcycleBox->getMotorcycle();

				// 같은 존에 있는 경우
				// 거리가 너무 가까우면 부르지 말자~
				if (pMotorZone!=pZone
					|| pSlayer->getDistance(motorX, motorY) > 15)
				{
					// 다른 zone으로 이동중이라고 표시한다.
					pMotorcycleBox->setTransport();

					// motorcycle을 slayer의 zone으로 옮긴다.
					pMotorZone->transportItem( motorX, motorY, pMotorcycle, 
												pZone, pSlayer->getX(), pSlayer->getY() );

					// Use OK 대용이다.
					// Use하면 아이템이 사라지던가 그렇지 싶다. - -;
					//GCCannotUse _GCCannotUse;
					//_GCCannotUse.setObjectID(pPacket->getObjectID());
					//pGamePlayer->sendPacket(&_GCCannotUse);

					// 한동안 delay를 줘야하는데..
				}
			}

			return true;
		}
		*/

		return false;
	}

	ItemID_t     itemID;
	ItemType_t   itemType;
	string 		 optionType;
	Durability_t durability;

	BEGIN_DB
	{
		StringStream sql;
		sql << "SELECT ItemID, ItemType, OptionType, Durability "
		    << "FROM MotorcycleObject where ItemID = " << targetID;
		
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(sql.toString());

		// by sigi. 2002.10.14
		// 결과물이 없다면 모터사이클이 없는 거쥐.
		if (pResult->getRowCount() <= 0) 
		{
			bFound = false;

			itemID     = targetID;
			itemType   = 0;
			optionType = "";
			durability = 300;
		}
		else 
		{
			bFound = true;

			pResult->next();

			itemID     = pResult->getInt(1);
			itemType   = pResult->getInt(2);
			optionType = pResult->getString(3);
			durability = pResult->getInt(4);
		}


			// 모터사이클 객체를 생성한다.
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionType);
			Motorcycle* pMotorcycle = new Motorcycle(itemType, optionTypes);

			Assert(pMotorcycle != NULL);

			pMotorcycle->setItemID(itemID);
			pMotorcycle->setDurability(durability);

			// 존에다 붙이기 전에 oid를 새로 할당받는다.
			(pZone->getObjectRegistry()).registerObject(pMotorcycle);
			
			// 생성한 모터사이클을 존에다 갖다붙인다.
			TPOINT pt = pZone->addItem(pMotorcycle, x, y, false);
			if (pt.x == -1)
			{
				// 오토바이를 존에다 더할 수 없었다. 씨바.
				filelog("motorError.txt", "ActionRedeemMotorcycle::load() : 모터사이클을 존에다 더할 수 없습니다. zoneID=%d, xy=(%d, %d)", (int)pZone->getZoneID(), (int)x, (int)y);	// by sigi. 2002.12.24
				throw Error("ActionRedeemMotorcycle::load() : 모터사이클을 존에다 더할 수 없습니다");
			}
			
			// by sigi. 2002.10.14
			if (!bFound)
			{
				pStmt->executeQuery(
				"INSERT IGNORE INTO MotorcycleObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Durability) Values (%d, %d, %d, '', %d, %d, %d, %d, '', %d)",
					itemID, pMotorcycle->getObjectID(), itemType, STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y, durability);
			}

			// 모터사이클을 뻑킹 센터에 등록해준다.
			MotorcycleBox* pBox = new MotorcycleBox(pMotorcycle, pZone, pt.x, pt.y);
			Assert(pBox != NULL);

			try {
				g_pParkingCenter->addMotorcycleBox(pBox);
			} catch (DuplicatedException& de) {	// by sigi. 2002.12.24
				filelog("motorError.txt", "%s - itemID=%d, motorid=%d", de.toString().c_str(), itemID, pMotorcycle->getObjectID());
			}

			bFound = true;
		//}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	} catch (Throwable& t) {	// by sigi. 2002.12.25
		filelog("motorError.txt", "%s - itemID=%d, motorItemID=%d", t.toString().c_str(), (int)pItem->getItemID(), (int)targetID);
		// 일단 다운은 막자.
		//throw;
	}

	__END_CATCH

	return bFound;
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRedeemMotorcycle::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRedeemMotorcycle(" << ")";
	return msg.toString();

	__END_CATCH
}
