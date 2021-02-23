//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSilverCoatingHandler.cpp
// Written By  : 김성민
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSilverCoating.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "PriceManager.h"
	#include "LogClient.h"

	#include "Gpackets/GCNPCResponse.h"
	#include <stdio.h>

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSilverCoatingHandler::execute (CGSilverCoating* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	ObjectID_t    ITEMOID      = pPacket->getObjectID();
	Creature*     pPC          = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	bool          bSlayer      = true;
	Gold_t        playerMoney  = 0;
	Price_t       coatingPrice = 0;
	Item*         pItem        = NULL;
	Slayer*       pSlayer      = NULL;
	Vampire*      pVampire     = NULL;
	int           storage      = 0;
	int           X            = 0;
	int           Y            = 0;
	GCNPCResponse response;

	// 플레이어가 슬레이어인지 뱀파이어인지 구분.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bSlayer = false;

	// 플레이어가 코팅하려고 하는 아이템을 가지고 있는지 검사
	if (bSlayer)
	{
		pSlayer     = dynamic_cast<Slayer*>(pPC);
		playerMoney = pSlayer->getGold();
		pItem       = pSlayer->findItemOID(ITEMOID, storage, X, Y);
	}
	else
	{
		pVampire    = dynamic_cast<Vampire*>(pPC);
		playerMoney = pVampire->getGold();
		pItem       = pVampire->findItemOID(ITEMOID, storage, X, Y);
	}

	// 아이템이 없다면 당연히 코팅할 수 없다.
	if (pItem == NULL)
	{
		response.setCode(NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_NOT_EXIST);
		pPlayer->sendPacket(&response);
		return;
	}

	// 코팅하려는 아이템이 코팅될 수 없는 아이템이라면...
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			break;
		default:
			response.setCode(NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_TYPE);
			pPlayer->sendPacket(&response);
			return;
	}

	coatingPrice = g_pPriceManager->getSilverCoatingPrice(pItem);
	if (coatingPrice > playerMoney)
	{
		response.setCode(NPC_RESPONSE_SILVER_COATING_FAIL_MONEY);
		pPlayer->sendPacket(&response);
		return;
	}

	// 최대 은 도금량을 얻어와서... 도금한다.
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	pItem->setSilver(pItemInfo->getMaxSilver());

	// 돈을 줄인다.
	if (bSlayer)
	{
		//pSlayer->setGoldEx(playerMoney - coatingPrice);

		// by sigi. 2002.9.4
		pSlayer->decreaseGoldEx(coatingPrice);
		//log(LOG_REPAIR_ITEM, pSlayer->getName(), "", pItem->toString());
	}
	else
	{
		//pVampire->setGoldEx(playerMoney - coatingPrice);

		// by sigi. 2002.9.4
		pVampire->decreaseGoldEx(coatingPrice);
		//log(LOG_REPAIR_ITEM, pVampire->getName(), "", pItem->toString());
	}

	// silver만 저장하면 된다.
	// 아이템 저장 최적화. by sigi. 2002.5.13
	char pField[80];
	sprintf(pField, "Silver=%d", pItem->getSilver());
	pItem->tinysave(pField);

	// 아이템을 은으로 코팅했다는 정보를 DB에다가 저장해준다.
	// 단 분명히 STORAGE_STASH가 돌아올 수 있지만, 
	// 보관함에 있는 것을 수리한다는 것은 말이 안 되므로,
	// 저장하지 않는다.
	/*
	switch (storage)
	{
		case STORAGE_INVENTORY:
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, X, Y);
			break;
		case STORAGE_GEAR:
			if (bSlayer) pItem->save(pSlayer->getName(),  STORAGE_GEAR, 0, X, 0);
			else         pItem->save(pVampire->getName(), STORAGE_GEAR, 0, X, 0);
			break;
		default:
			break;
	}
	*/

	// OK 패킷을 날려준다.
	response.setCode(NPC_RESPONSE_SILVER_COATING_OK);
	response.setParameter(playerMoney-coatingPrice);
	pPlayer->sendPacket(&response);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

