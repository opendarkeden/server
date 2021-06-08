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

	#include "GCTradeAddItem.h"
	#include "GCTradeError.h"
	#include "GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::execute (CGTradeAddItem* pPacket , Player* pPlayer)
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
	
	// ��ȯ�� ���ϴ� ������ ������ ã�ƺ���.
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

	// NoSuch����. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID); 

	// ��ȯ ��밡 ���ٸ� ������.
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// ��ȯ ��밡 ����� �ƴϰų�, ���� ������ �ƴ϶�� ������.
	if (!pTargetPC->isPC() || !isSameRace(pTargetPC, pPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

    // �� �� ���� ���뿡 �ִ��� üũ�� �Ѵ�.
	if (!isInSafeZone(pPC) || !isInSafeZone(pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// ������̸� Ÿ�� �ִٸ� ������.
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

	// ���̼� ��ȯ�� �ϰ� �ִ� ���°� �ƴ϶�� ������.
	if (!pTradeManager->isTrading(pPC, pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
		return;
	}

	if (pPC->isSlayer()) executeSlayer(pPacket, pPlayer);
	else if (pPC->isVampire()) executeVampire(pPacket, pPlayer);
	else if (pPC->isOusters()) executeOusters(pPacket, pPlayer);
	else throw ProtocolException("CGTradeAddItemHandler::execute() : �� �� ���� �÷��̾� ũ����");

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeSlayer (CGTradeAddItem* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t   TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t   ItemOID     = pPacket->getItemObjectID();
	GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*    pPC         = pGamePlayer->getCreature();
	Zone*        pZone       = pPC->getZone();
	Creature*    pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*      pSender     = dynamic_cast<Slayer*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ��� �߰��� �������� �����͸� ����.
	CoordInven_t X, Y;
	Inventory*   pInventory = pSender->getInventory();
	Item*        pItem      = pInventory->findItemOID(ItemOID, X, Y);

	// �߰��� �������� ���ٸ� �翬�� �� �̻� ó���� �Ұ���
	// �߰��� �������� Relic�̸� �߰��� �� ����.
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
	// ��� ���� ������ ��쿡��, ���濡�� ���� ���� ���ڰ� ������ �˻��� ��, 
	// ���� ��Ŷ�� ������� �Ѵ�.
	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX)
	{
		PlayerCreature* pReceiver = dynamic_cast<PlayerCreature*>(pTargetPC);
		Item* pExtraSlotItem = pReceiver->getExtraInventorySlotItem();

		// ��� ���� ����
		if (pItem->getItemType() == 0)
		{
			// ��ȯ ���� ����� �̹� ��� ���� ���ڸ� ���� ���� �ִ��� üũ�Ѵ�. by sigi. 2002.12.16	
			FlagSet*   pFlagSet    = pReceiver->getFlagSet();
			if (pFlagSet->isOn(FLAGSET_RECEIVE_GREEN_GIFT_BOX)) 
			{
				// ���� ���� ���ڴ� ��ȯ ǰ���� ����� �� �� ����.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL);
				pPlayer->sendPacket(&gcTradeVerify);
				return;
			}

			Inventory* pTargetInventory = pReceiver->getInventory();
			if (pTargetInventory->hasRedGiftBox())
			{
				// ���� ���� ���ڸ� ������ �ִٸ� ���� �� ����. ���Ͻ�Ų��.
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
				// ���� ���� ���ڸ� ������ ���� �ʴٸ�, �� �Ѿ��.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}
		}
		// ���� ���� ����
		else if (pItem->getItemType() == 1)	
		{
			// ���� ���� ���ڴ� ��ȯ ǰ���� ����� �� �� ����.
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


	// TradeManager�� ��ȯ ������μ� �������� ���Ѵ�.
	//Assert(pInfo1->addItem(pItem));
	pInfo1->addItem(pItem);

	// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
        //cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�̹Ƿ�, ���� ��Ŷ�� �����ش�." << endl;

		// ���� ��Ŷ�� �����ش�.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT);
		pPlayer->sendPacket(&gcTradeVerify);
	}
    else
    {
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ƴϹǷ�, ���� ��Ŷ ������ �ʴ´�." << endl;
    }

	// �������� ���ϰų� �� ���, ���°� TRADE_FINISH��� 
	// TRADE_TRADING���� �ٲ���� �Ѵ�.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// ���濡�� ������ ������ ������ �����Ѵ�.
	GCTradeAddItem gcTradeAddItem;
	makeGCTradeAddItemPacket(&gcTradeAddItem, pSender->getObjectID(), pItem, X, Y);

	// ���濡�� ��ȯ�� ������ ������ �����ش�.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeAddItem);


#endif

	__END_DEBUG_EX __END_CATCH
}




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeVampire (CGTradeAddItem* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t   TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t   ItemOID     = pPacket->getItemObjectID();
	GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*    pPC         = pGamePlayer->getCreature();
	Zone*        pZone       = pPC->getZone();
	Creature*    pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*     pSender     = dynamic_cast<Vampire*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ��� �߰��� �������� �����͸� ����.
	CoordInven_t X, Y;
	Inventory*   pInventory = pSender->getInventory();
	Item*        pItem      = pInventory->findItemOID(ItemOID, X, Y);

	// �߰��� �������� ���ٸ� �翬�� �� �̻� ó���� �Ұ���
	// Relic�� ��ȯ�� �� ����.
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
	// ��� ���� ������ ��쿡��, ���濡�� ���� ���� ���ڰ� ������ �˻��� ��, 
	// ���� ��Ŷ�� ������� �Ѵ�.
	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX)
	{
		PlayerCreature* pReceiver = dynamic_cast<PlayerCreature*>(pTargetPC);
		Item* pExtraSlotItem = pReceiver->getExtraInventorySlotItem();

		if (pItem->getItemType() == 0)
		{
			Inventory* pTargetInventory = pReceiver->getInventory();
			if (pTargetInventory->hasRedGiftBox())
			{
				// ���� ���� ���ڸ� ������ �ִٸ� ���� �� ����. ���Ͻ�Ų��.
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
				// ���� ���� ���ڸ� ������ ���� �ʴٸ�, �� �Ѿ��.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}
		}
		else if (pItem->getItemType() == 1)
		{
			// ���� ���� ���ڴ� ��ȯ ǰ���� �� �� ����.
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



	// TradeManager�� ��ȯ ������μ� �������� ���Ѵ�.
	//Assert(pInfo1->addItem(pItem));
	pInfo1->addItem(pItem);

	// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
        //cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�̹Ƿ�, ���� ��Ŷ�� �����ش�." << endl;

		// ���� ��Ŷ�� �����ش�.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT);
		pPlayer->sendPacket(&gcTradeVerify);
	}
    else
    {
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ƴϹǷ�, ���� ��Ŷ ������ �ʴ´�." << endl;
    }

	// �������� ���ϰų� �� ���, ���°� TRADE_FINISH��� 
	// TRADE_TRADING���� �ٲ���� �Ѵ�.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// ���濡�� ������ ������ ������ �����Ѵ�.
	GCTradeAddItem gcTradeAddItem;
	makeGCTradeAddItemPacket(&gcTradeAddItem, pSender->getObjectID(), pItem, X, Y);

	// ���濡�� ��ȯ�� ������ ������ �����ش�.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeAddItem);

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::executeOusters (CGTradeAddItem* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t   TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t   ItemOID     = pPacket->getItemObjectID();
	GamePlayer*  pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*    pPC         = pGamePlayer->getCreature();
	Zone*        pZone       = pPC->getZone();
	Creature*    pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*     pSender     = dynamic_cast<Ousters*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ��� �߰��� �������� �����͸� ����.
	CoordInven_t X, Y;
	Inventory*   pInventory = pSender->getInventory();
	Item*        pItem      = pInventory->findItemOID(ItemOID, X, Y);

	// �߰��� �������� ���ٸ� �翬�� �� �̻� ó���� �Ұ���
	// Relic�� ��ȯ�� �� ����.
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
	// ��� ���� ������ ��쿡��, ���濡�� ���� ���� ���ڰ� ������ �˻��� ��, 
	// ���� ��Ŷ�� ������� �Ѵ�.
	if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX)
	{
		PlayerCreature* pReceiver = dynamic_cast<PlayerCreature*>(pTargetPC);
		Item* pExtraSlotItem = pReceiver->getExtraInventorySlotItem();

		if (pItem->getItemType() == 0)
		{
			Inventory* pTargetInventory = pReceiver->getInventory();
			if (pTargetInventory->hasRedGiftBox())
			{
				// ���� ���� ���ڸ� ������ �ִٸ� ���� �� ����. ���Ͻ�Ų��.
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
				// ���� ���� ���ڸ� ������ ���� �ʴٸ�, �� �Ѿ��.
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}
		}
		else if (pItem->getItemType() == 1)
		{
			// ���� ���� ���ڴ� ��ȯ ǰ���� �� �� ����.
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


	// TradeManager�� ��ȯ ������μ� �������� ���Ѵ�.
	//Assert(pInfo1->addItem(pItem));
	pInfo1->addItem(pItem);

	// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
        //cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�̹Ƿ�, ���� ��Ŷ�� �����ش�." << endl;

		// ���� ��Ŷ�� �����ش�.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT);
		pPlayer->sendPacket(&gcTradeVerify);
	}
    else
    {
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ƴϹǷ�, ���� ��Ŷ ������ �ʴ´�." << endl;
    }

	// �������� ���ϰų� �� ���, ���°� TRADE_FINISH��� 
	// TRADE_TRADING���� �ٲ���� �Ѵ�.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// ���濡�� ������ ������ ������ �����Ѵ�.
	GCTradeAddItem gcTradeAddItem;
	makeGCTradeAddItemPacket(&gcTradeAddItem, pSender->getObjectID(), pItem, X, Y);

	// ���濡�� ��ȯ�� ������ ������ �����ش�.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeAddItem);

#endif

	__END_DEBUG_EX __END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeAddItemHandler::makeGCTradeAddItemPacket (GCTradeAddItem* pPacket, ObjectID_t Sender, Item* pItem, CoordInven_t X, CoordInven_t Y) 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	// ���濡�� ������ ������ ������ �����Ѵ�.
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

	// � �����۵��� ������ �����ֱ� ���� �߰������� ������ �ؾ��Ѵ�.
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
	// �� ������ ������ ���� ��ſ� �Ѿ��� ���ڸ� �־��ش�.
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
	// ��Ʈ�� ��쿡�� ��Ʈ �ȿ� ���ԵǾ� �ִ� ������ ������
	// ���� ������� �Ѵ�.
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
	// �Ͻ������ ��쿡�� �ȿ� ���ԵǾ� �ִ� ������ ������
	// ���� ������� �Ѵ�.
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

