////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSearchMotorcycle.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSearchMotorcycle.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "item/Key.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSearchMotorcycleOK.h"
#include "Gpackets/GCSearchMotorcycleFail.h"
#include "ParkingCenter.h"
#include "DB.h"
#include "Belt.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionSearchMotorcycle::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionSearchMotorcycle::execute (Creature * pCreature1 , Creature* pCreature2) 
	
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
		Inventory* pInventory  = pSlayer->getInventory();
		uint       InvenWidth  = pInventory->getWidth();
		uint       InvenHeight = pInventory->getHeight();
		Item*      pItem       = NULL;
		uint       motorZoneID = 0;
		uint       motorX      = 0;
		uint       motorY      = 0;
	
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
					if (search(pItem, motorZoneID, motorX, motorY))
					{
						GCSearchMotorcycleOK okpkt;
						okpkt.setZoneID(motorZoneID);
						okpkt.setX(motorX);
						okpkt.setY(motorY);
						pPlayer->sendPacket(&okpkt);
						return;
					}
				}
			}
		}
		
		if(pBelt != NULL)
		{
			// 인벤토리를 검색한다.
			for (uint y=0; y<BeltInvenHeight; y++)
			{
				for (uint x=0; x<BeltInvenWidth; x++)
				{
					// x, y에 아이템이 있다면...
					if (pBeltInventory->hasItem(x, y))
					{
						pItem = pBeltInventory->getItem(x, y);
						if (search(pItem, motorZoneID, motorX, motorY))
						{
							GCSearchMotorcycleOK okpkt;
							okpkt.setZoneID(motorZoneID);
							okpkt.setX(motorX);
							okpkt.setY(motorY);
							pPlayer->sendPacket(&okpkt);
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

	GCSearchMotorcycleFail failpkt;
	pPlayer->sendPacket(&failpkt);

	__END_CATCH
}

bool ActionSearchMotorcycle::search(Item* pItem, uint& zoneid, uint& x, uint& y) const
	
{
	__BEGIN_TRY

	bool bFound = false;

	// 단서가 되는 아이템이 키가 아니라면 false를 리턴.
	if (pItem->getItemClass() != Item::ITEM_CLASS_KEY) return false;

	// 키가 맞다면 키의 타겟이 되는 아이템의 아이템 ID를 얻어낸다.
	DWORD targetID = dynamic_cast<Key*>(pItem)->getTarget();

	// 해당하는 오토바이가 존재하는지 체크를 한다.
	if (g_pParkingCenter->hasMotorcycleBox(targetID))
	{
		MotorcycleBox* pBox = g_pParkingCenter->getMotorcycleBox(targetID);
		Assert(pBox != NULL);

		zoneid = pBox->getZone()->getZoneID();
		x      = pBox->getX();
		y      = pBox->getY();

		bFound = true;
	}

	return bFound;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSearchMotorcycle::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSearchMotorcycle(" << ")";
	return msg.toString();

	__END_CATCH
}
