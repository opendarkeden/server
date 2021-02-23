//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeAddItemHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeAddItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "PetItem.h"
	#include "AR.h"
	#include "SR.h"
	#include "SG.h"
	#include "SMG.h"
	#include "Belt.h"
	#include "OustersArmsband.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"
	#include "FlagSet.h"
	#include "RelicUtil.h"
	#include "ItemUtil.h"
	#include "Store.h"

	#include "Gpackets/GCTradeAddItem.h"
	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::execute (CGTradeAddItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pPC = pGamePlayer->getCreature();
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);
	
	// 교환을 원하는 상대방을 존에서 찾아본다.
	Creature* pTargetPC = NULL;
	/*
	try 
	{ 
		pTargetPC = pZone->getCreature(TargetOID); 
	}
	catch (NoSuchElementException) 
	{ 
		pTargetPC = NULL; 
	}
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID); 

	// 교환 상대가 없다면 에러다.
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// 교환 상대가 사람이 아니거나, 같은 종족이 아니라면 에러다.
	if (!pTargetPC->isPC() || !isSameRace(pTargetPC, pPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

    // 둘 다 안전 지대에 있는지 체크를 한다.
	if (!isInSafeZone(pPC) || !isInSafeZone(pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// 오토바이를 타고 있다면 에러다.
	if (pPC->isSlayer() && pTargetPC->isSlayer())
	{
		Slayer* pSlayer1 = dynamic_cast<Slayer*>(pPC);
		Slayer* pSlayer2 = dynamic_cast<Slayer*>(pTargetPC);

		if (pSlayer1->hasRideMotorcycle() || pSlayer2->hasRideMotorcycle())
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	if (pPC->isOusters() && pTargetPC->isOusters())
	{
		Ousters* pOusters1 = dynamic_cast<Ousters*>(pPC);
		Ousters* pOusters2 = dynamic_cast<Ousters*>(pTargetPC);

		if ( pOusters1->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) 
			|| pOusters2->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) )
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	// 둘이서 교환을 하고 있는 상태가 아니라면 에러다.
	if (!pTradeManager->isTrading(pPC, pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
		return;
	}

	if (pPC->isSlayer()) executeSlayer(pPacket, pPlayer);
	else if (pPC->isVampire()) executeVampire(pPacket, pPlayer);
	else if (pPC->isOusters()) executeOusters(pPacket, pPlayer);
	else throw ProtocolException("CGTradeAddItemHandler::execute() : 알 수 없는 플레이어 크리쳐");

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeSlayer (CGTradeAddItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t   TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t   ItemOID     = pPacket->getItemObjectID();
	GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*    pPC         = pGamePlayer->getCreature();
	Zone*        pZone       = pPC->getZone();
	Creature*    pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*      pSender     = dynamic_cast<Slayer*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 대상에 추가할 아이템의 포인터를 얻어낸다.
	CoordInven_t X, Y;
	Inventory*   pInventory = pSender->getInventory();
	Item*        pItem      = pInventory->findItemOID(ItemOID, X, Y);

	// 추가할 아이템이 없다면 당연히 더 이상 처리가 불가능
	// 추가할 아이템이 Relic이면 추가할 수 없다.
	if (pItem == NULL
	|| !canTrade( pItem ) 
	|| pSender->getStore()->hasItem(pItem) )
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_ADD_ITEM);
		return;
	}

///*
//#ifdef __XMAS_EVENT_CODE__
	// 녹색 선물 상자인 경우에는, 상대방에게 적색 선물 상자가 없는지 검사한 후, 
	// 인증 패킷을 보내줘야 한다.
	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX)
	{
		PlayerCreature* pReceiver = dynamic_cast<PlayerCreature*>(pTargetPC);
		Item* pExtraSlotItem = pReceiver->getExtraInventorySlotItem();

		// 녹색 선물 상자
		if (pItem->getItemType() == 0)
		{
			// 교환 받을 사람이 이미 녹색 선물 상자를 받은 적이 있는지 체크한다. by sigi. 2002.12.16	
			FlagSet*   pFlagSet    = pReceiver->getFlagSet();
			if (pFlagSet->isOn(FLAGSET_RECEIVE_GREEN_GIFT_BOX)) 
			{
				// 적색 선물 상자는 교환 품목의 대상이 될 수 없다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}

			Inventory* pTargetInventory = pReceiver->getInventory();
			if (pTargetInventory->hasRedGiftBox())
			{
				// 적색 선물 상자를 가지고 있다면 더할 수 없다. 리턴시킨다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}
			else if (pExtraSlotItem != NULL)
			{
				if (pExtraSlotItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pExtraSlotItem->getItemType() == 1)
				{
					GCTradeVerify gcTradeVerify;
					gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
					pPlayer->sendPacket(&gcTradeVerify);
					return;
				}
			}
			else
			{
				// 적색 선물 상자를 가지고 있지 않다면, 걍 넘어간다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}
		}
		// 빨간 선물 상자
		else if (pItem->getItemType() == 1)	
		{
			// 적색 선물 상자는 교환 품목의 대상이 될 수 없다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
			pPlayer->sendPacket(&gcTradeVerify);
			return;
		}
	}
//#endif
//*/

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	list<Item*>      tradeList1  = pInfo1->getItemList();

	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() > 1 && pItem->getItemType() < 6)
	{
		for (list<Item*>::iterator itr = tradeList1.begin(); itr != tradeList1.end(); itr++)
		{
			Item* pTradeItem = (*itr);
			if ( pTradeItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pTradeItem->getItemType() > 1 && pTradeItem->getItemType() < 6)	
			{
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}
		}

		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() >= 6)
	{
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
		pPlayer->sendPacket(&gcTradeVerify);
	}


	// TradeManager에 교환 대상으로서 아이템을 더한다.
	//Assert(pInfo1->addItem(pItem));
	pInfo1->addItem(pItem);

	// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
        //cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH이므로, 인증 패킷을 보내준다." << endl;

		// 인증 패킷을 날려준다.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT);
		pPlayer->sendPacket(&gcTradeVerify);
	}
    else
    {
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH가 아니므로, 인증 패킷 날리지 않는다." << endl;
    }

	// 아이템을 더하거나 뺄 경우, 상태가 TRADE_FINISH라면 
	// TRADE_TRADING으로 바꿔줘야 한다.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// 상대방에게 날려줄 아이템 정보를 구성한다.
	GCTradeAddItem gcTradeAddItem;
	makeGCTradeAddItemPacket(&gcTradeAddItem, pSender->getObjectID(), pItem, X, Y);

	// 상대방에게 교환할 아이템 정보를 날려준다.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeAddItem);


#endif

	__END_DEBUG_EX __END_CATCH
}




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeVampire (CGTradeAddItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t   TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t   ItemOID     = pPacket->getItemObjectID();
	GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*    pPC         = pGamePlayer->getCreature();
	Zone*        pZone       = pPC->getZone();
	Creature*    pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*     pSender     = dynamic_cast<Vampire*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 대상에 추가할 아이템의 포인터를 얻어낸다.
	CoordInven_t X, Y;
	Inventory*   pInventory = pSender->getInventory();
	Item*        pItem      = pInventory->findItemOID(ItemOID, X, Y);

	// 추가할 아이템이 없다면 당연히 더 이상 처리가 불가능
	// Relic은 교환할 수 없다.
	if (pItem == NULL
	|| !canTrade( pItem )
	|| pSender->getStore()->hasItem(pItem) )
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_ADD_ITEM);
		return;
	}


//
//#ifdef __XMAS_EVENT_CODE__
	// 녹색 선물 상자인 경우에는, 상대방에게 적색 선물 상자가 없는지 검사한 후, 
	// 인증 패킷을 보내줘야 한다.
	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX)
	{
		PlayerCreature* pReceiver = dynamic_cast<PlayerCreature*>(pTargetPC);
		Item* pExtraSlotItem = pReceiver->getExtraInventorySlotItem();

		if (pItem->getItemType() == 0)
		{
			Inventory* pTargetInventory = pReceiver->getInventory();
			if (pTargetInventory->hasRedGiftBox())
			{
				// 적색 선물 상자를 가지고 있다면 더할 수 없다. 리턴시킨다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}
			else if (pExtraSlotItem != NULL)
			{
				if (pExtraSlotItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pExtraSlotItem->getItemType() == 1)
				{
					GCTradeVerify gcTradeVerify;
					gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
					pPlayer->sendPacket(&gcTradeVerify);
					return;
				}
			}
			else
			{
				// 적색 선물 상자를 가지고 있지 않다면, 걍 넘어간다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}
		}
		else if (pItem->getItemType() == 1)
		{
			// 적색 선물 상자는 교환 품목이 될 수 없다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
			pPlayer->sendPacket(&gcTradeVerify);
			return;
		}
	}
//#endif
//

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	list<Item*>      tradeList1  = pInfo1->getItemList();

	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() > 1 && pItem->getItemType() < 6)
	{
		for (list<Item*>::iterator itr = tradeList1.begin(); itr != tradeList1.end(); itr++)
		{
			Item* pTradeItem = (*itr);
			if ( pTradeItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pTradeItem->getItemType() > 1 && pTradeItem->getItemType() < 6)	
			{
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}
		}

		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() >= 6)
	{
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
		pPlayer->sendPacket(&gcTradeVerify);
	}



	// TradeManager에 교환 대상으로서 아이템을 더한다.
	//Assert(pInfo1->addItem(pItem));
	pInfo1->addItem(pItem);

	// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
        //cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH이므로, 인증 패킷을 보내준다." << endl;

		// 인증 패킷을 날려준다.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT);
		pPlayer->sendPacket(&gcTradeVerify);
	}
    else
    {
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH가 아니므로, 인증 패킷 날리지 않는다." << endl;
    }

	// 아이템을 더하거나 뺄 경우, 상태가 TRADE_FINISH라면 
	// TRADE_TRADING으로 바꿔줘야 한다.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// 상대방에게 날려줄 아이템 정보를 구성한다.
	GCTradeAddItem gcTradeAddItem;
	makeGCTradeAddItemPacket(&gcTradeAddItem, pSender->getObjectID(), pItem, X, Y);

	// 상대방에게 교환할 아이템 정보를 날려준다.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeAddItem);

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeOusters (CGTradeAddItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t   TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t   ItemOID     = pPacket->getItemObjectID();
	GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*    pPC         = pGamePlayer->getCreature();
	Zone*        pZone       = pPC->getZone();
	Creature*    pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*     pSender     = dynamic_cast<Ousters*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 대상에 추가할 아이템의 포인터를 얻어낸다.
	CoordInven_t X, Y;
	Inventory*   pInventory = pSender->getInventory();
	Item*        pItem      = pInventory->findItemOID(ItemOID, X, Y);

	// 추가할 아이템이 없다면 당연히 더 이상 처리가 불가능
	// Relic은 교환할 수 없다.
	if (pItem == NULL
	|| !canTrade( pItem )
	|| pSender->getStore()->hasItem(pItem) )
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_ADD_ITEM);
		return;
	}


//
//#ifdef __XMAS_EVENT_CODE__
	// 녹색 선물 상자인 경우에는, 상대방에게 적색 선물 상자가 없는지 검사한 후, 
	// 인증 패킷을 보내줘야 한다.
	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX)
	{
		PlayerCreature* pReceiver = dynamic_cast<PlayerCreature*>(pTargetPC);
		Item* pExtraSlotItem = pReceiver->getExtraInventorySlotItem();

		if (pItem->getItemType() == 0)
		{
			Inventory* pTargetInventory = pReceiver->getInventory();
			if (pTargetInventory->hasRedGiftBox())
			{
				// 적색 선물 상자를 가지고 있다면 더할 수 없다. 리턴시킨다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}
			else if (pExtraSlotItem != NULL)
			{
				if (pExtraSlotItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pExtraSlotItem->getItemType() == 1)
				{
					GCTradeVerify gcTradeVerify;
					gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
					pPlayer->sendPacket(&gcTradeVerify);
					return;
				}
			}
			else
			{
				// 적색 선물 상자를 가지고 있지 않다면, 걍 넘어간다.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}
		}
		else if (pItem->getItemType() == 1)
		{
			// 적색 선물 상자는 교환 품목이 될 수 없다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
			pPlayer->sendPacket(&gcTradeVerify);
			return;
		}
	}
//#endif
//

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	list<Item*>      tradeList1  = pInfo1->getItemList();

	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() > 1 && pItem->getItemType() < 6)
	{
		for (list<Item*>::iterator itr = tradeList1.begin(); itr != tradeList1.end(); itr++)
		{
			Item* pTradeItem = (*itr);
			if ( pTradeItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pTradeItem->getItemType() > 1 && pTradeItem->getItemType() < 6)	
			{
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}
		}

		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() >= 6)
	{
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
		pPlayer->sendPacket(&gcTradeVerify);
	}


	// TradeManager에 교환 대상으로서 아이템을 더한다.
	//Assert(pInfo1->addItem(pItem));
	pInfo1->addItem(pItem);

	// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
        //cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH이므로, 인증 패킷을 보내준다." << endl;

		// 인증 패킷을 날려준다.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT);
		pPlayer->sendPacket(&gcTradeVerify);
	}
    else
    {
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH가 아니므로, 인증 패킷 날리지 않는다." << endl;
    }

	// 아이템을 더하거나 뺄 경우, 상태가 TRADE_FINISH라면 
	// TRADE_TRADING으로 바꿔줘야 한다.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// 상대방에게 날려줄 아이템 정보를 구성한다.
	GCTradeAddItem gcTradeAddItem;
	makeGCTradeAddItemPacket(&gcTradeAddItem, pSender->getObjectID(), pItem, X, Y);

	// 상대방에게 교환할 아이템 정보를 날려준다.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeAddItem);

#endif

	__END_DEBUG_EX __END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::makeGCTradeAddItemPacket (GCTradeAddItem* pPacket, ObjectID_t Sender, Item* pItem, CoordInven_t X, CoordInven_t Y) 
	throw ()
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	// 상대방에게 날려줄 아이템 정보를 구성한다.
	pPacket->setTargetObjectID(Sender);
	pPacket->setItemObjectID(pItem->getObjectID());
	pPacket->setX(X);
	pPacket->setY(Y);
	pPacket->setItemClass(pItem->getItemClass());
	pPacket->setItemType(pItem->getItemType());
	pPacket->setOptionType(pItem->getOptionTypeList());
	pPacket->setDurability(pItem->getDurability());
	pPacket->setItemNum(pItem->getNum());
	pPacket->setSilver(pItem->getSilver());
	pPacket->setGrade(pItem->getGrade());
	pPacket->setEnchantLevel(pItem->getEnchantLevel());
	pPacket->clearList();

	// 어떤 아이템들을 정보를 보내주기 전에 추가적으로 가공을 해야한다.
	Item::ItemClass IClass = pItem->getItemClass();

	if (IClass == Item::ITEM_CLASS_PET_ITEM)
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);

		if ( pPetItem->getPetInfo() != NULL )
		{
			list<OptionType_t> olist;

			if ( pPetItem->getPetInfo()->getPetOption() != 0 )
				olist.push_back(pPetItem->getPetInfo()->getPetOption());

			pPacket->setOptionType( olist );
			pPacket->setDurability( pPetItem->getPetInfo()->getPetHP() );
			pPacket->setEnchantLevel( pPetItem->getPetInfo()->getPetAttr() );
			pPacket->setSilver( pPetItem->getPetInfo()->getPetAttrLevel() );
			pPacket->setGrade( (pPacket->getDurability() == 0 )?(pPetItem->getPetInfo()->getLastFeedTime().daysTo( VSDateTime::currentDateTime() )):(-1) );
			pPacket->setItemNum( pPetItem->getPetInfo()->getPetLevel() );
//			pPacket->setMainColor( 0xffff );
		}

	}
	// 총 종류는 아이템 숫자 대신에 총알의 숫자를 넣어준다.
	else if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pItem);
		pPacket->setItemNum(pAR->getBulletCount());
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pItem);
		pPacket->setItemNum(pSR->getBulletCount());
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pItem);
		pPacket->setItemNum(pSG->getBulletCount());
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pItem);
		pPacket->setItemNum(pSMG->getBulletCount());
	}
	// 벨트의 경우에는 벨트 안에 포함되어 있는 아이템 정보를
	// 같이 날려줘야 한다.
	else if (IClass == Item::ITEM_CLASS_BELT)
	{
		Belt*      pBelt          = dynamic_cast<Belt*>(pItem);
		Inventory* pBeltInventory = pBelt->getInventory();
		BYTE       SubItemCount   = 0;

		for (int i=0; i<pBelt->getPocketCount(); i++)
		{
			Item* pBeltItem = pBeltInventory->getItem(i, 0);
			if (pBeltItem != NULL)
			{
				SubItemInfo* pInfo = new SubItemInfo();
				pInfo->setObjectID(pBeltItem->getObjectID());
				pInfo->setItemClass(pBeltItem->getItemClass());
				pInfo->setItemType(pBeltItem->getItemType());
				pInfo->setItemNum(pBeltItem->getNum());
				pInfo->setSlotID(i);
				pPacket->addListElement(pInfo);

				SubItemCount += 1;
			}
		}

		pPacket->setListNum(SubItemCount);
	}
	// 암스밴드의 경우에는 안에 포함되어 있는 아이템 정보를
	// 같이 날려줘야 한다.
	else if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND)
	{
		OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
		Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
		BYTE SubItemCount = 0;

		for (int i=0; i<pOustersArmsband->getPocketCount(); i++)
		{
			Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
			if (pOustersArmsbandItem != NULL)
			{
				SubItemInfo* pInfo = new SubItemInfo();
				pInfo->setObjectID(pOustersArmsbandItem->getObjectID());
				pInfo->setItemClass(pOustersArmsbandItem->getItemClass());
				pInfo->setItemType(pOustersArmsbandItem->getItemType());
				pInfo->setItemNum(pOustersArmsbandItem->getNum());
				pInfo->setSlotID(i);
				pPacket->addListElement(pInfo);

				SubItemCount += 1;
			}
		}

		pPacket->setListNum(SubItemCount);
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeError(CGTradeAddItem* pPacket, Player* pPlayer, BYTE ErrorCode)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	GCTradeError gcTradeError;
	gcTradeError.setTargetObjectID(pPacket->getTargetObjectID());
	gcTradeError.setCode(ErrorCode);
	pPlayer->sendPacket(&gcTradeError);

#endif

	__END_DEBUG_EX __END_CATCH
}

