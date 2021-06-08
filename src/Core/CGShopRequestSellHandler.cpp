//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestSellHandler.cpp
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestSell.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "PriceManager.h"
	#include "ParkingCenter.h"
	#include "ZoneUtil.h"
	#include "RelicUtil.h"
	#include "ItemUtil.h"
	#include "PacketUtil.h"

	#include "VariableManager.h"
	#include "Store.h"
	#include "FlagSet.h"

	#include "item/Key.h"
	#include "item/Potion.h"
	#include "item/Magazine.h"
	#include "item/Belt.h"

	#include "GCShopSellOK.h"
	#include "GCShopSellFail.h"
	#include "GCShopBought.h"
	#include "GCDeleteObject.h"
	#include "GCCreateItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// �÷��̾ �ȷ��� �ϴ� �������� ������ �ִ��� Ȯ���� ������,
// �Ϲ� �����۰� ���� ����Ŭ ó�� �κ����� �б��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::execute (CGShopRequestSell* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	ObjectID_t      ITEMOID     = pPacket->getItemObjectID();
	BYTE            OPCODE      = pPacket->getOpCode();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

	if (OPCODE == SHOP_REQUEST_SELL_NORMAL)
	{
		// �÷��̾ �ȷ��� �ϴ� �������� ������ �ִ��� �˻�
		Inventory* pInventory = pPC->getInventory();
		if (pInventory->hasItem(ITEMOID) == false) 
			throw ProtocolException("CGShopRequestSellHandler::execute() : No such item to sell!");

		Item* pItem = pInventory->getItemWithObjectID(ITEMOID);
		if (pItem == NULL) return sendFailPacket(pPacket, pPlayer);
		if ( pPC->getStore()->hasItem( pItem ) ) return sendFailPacket(pPacket, pPlayer);

		//ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
		//Assert(pItemInfo!=NULL);

		// ����ũ �������� ���Ǵ�.
		// Ư�� ������ Ŭ������ �� �� ����. by sigi. 2002.8.29
		// ���� ���ڴ� �� �� �ִ�. by bezz. 2002.12.13
		// Ŀ�ø��� �� �� ����. by Sequoia. 2003. 3. 3
		// ItemUtil �ȿ� canSell �� Extract 2003. 3. 3
		if ( !canSell( pItem ) )
		{
			return sendFailPacket(pPacket, pPlayer);
		}
		// ��ʱ�����Ƶ���Ʒ���ó���
		// add by Coffee 2007-8-5
		if (pItem->isTimeLimitItem())
		{
			return sendFailPacket(pPacket, pPlayer);
		}
		
		else if (pItem->getItemClass() == Item::ITEM_CLASS_KEY && pItem->getItemType() == 2) 
		{
			executeMotorcycle(pPacket, pPlayer);
		}
		else 
		{
			executeNormal(pPacket, pPlayer);
		}
	}
	else if (OPCODE == SHOP_REQUEST_SELL_ALL_SKULL)
	{
		executeOpAllSkull(pPacket, pPlayer);
	}
	else if (OPCODE == SHOP_REQUEST_SWAP_ADVANCEMENT_ITEM)
	{
		executeOpSwapAdvancementItem(pPacket, pPlayer);
	}
	else
	{
		throw ProtocolException("CGShopRequestSellHandler::execute() : unknown op code");
	}
	
#endif

	__END_DEBUG_EX __END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// 
// �Ϲ� �������� ó���Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::executeNormal (CGShopRequestSell* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	ObjectID_t      NPCID        = pPacket->getObjectID();
	ObjectID_t      ITEMOID      = pPacket->getItemObjectID();
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	BYTE            index        = 0;
	bool            bSpecialItem = false;

	Zone* pZone = pPC->getZone();
	if (pZone == NULL) return sendFailPacket(pPacket, pPlayer);

	Creature* pNPCBase = NULL;
	/*
	try 
	{ 
		pNPCBase = pZone->getCreature(NPCID); 
	}
	catch (NoSuchElementException & nsee) 
	{ 
		pNPCBase = NULL; 
	}
	*/

	// NoSuch����. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 

	if (pNPCBase == NULL || !pNPCBase->isNPC()) return sendFailPacket(pPacket, pPlayer);

	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);
	
	// �÷��̾ �ȷ��� �ϴ� �������� ������ �ִ��� �˻�
	Inventory* pInventory  = pPC->getInventory();
	//Gold_t     playerMoney = pPC->getGold(); 
	Item*      pItem       = pInventory->getItemWithObjectID(ITEMOID);
	ItemNum_t  itemNumber  = pItem->getNum();
	Price_t    itemPrice   = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC) * itemNumber;

	// �÷��̾��� �κ��丮�� �������� �����Ѵ�.
	pInventory->deleteItem(ITEMOID);
	pItem->whenPCLost(pPC);

	if (!pItem->destroy())
	{
		filelog("shopDBBug.txt", "NoSuchItemInDB-destroy: %s", pItem->toString().c_str());

		throw DisconnectException("������ ������µ� DB�� ����.");
	}

	// ���� ��Ʈ��� �ȿ� �ִ� ������ �������ش�.
	// DB���� ����� ���� Belt::destroy()�� �θ��� �͸����� ���Ǳ��� �����ȴ�.
	if (pItem->getItemClass() == Item::ITEM_CLASS_BELT)
	{
		Inventory* pBeltInventory = dynamic_cast<Belt*>(pItem)->getInventory();
		for (int y=0; y<pBeltInventory->getHeight(); y++)
		{
			for (int x=0; x<pBeltInventory->getWidth(); x++)
			{
				Item* pBeltItem = pBeltInventory->getItem(x, y);
				if (pBeltItem != NULL)
				{
					pBeltInventory->deleteItem(x, y);
					SAFE_DELETE(pBeltItem);
				}
			}
		}
	}

	// Skull �� ��� Variable Manager ���� �Ӹ��� ��� ������ ������ ���� ����Ѵ�
	if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
	{
		itemPrice = itemPrice * (g_pVariableManager->getHeadPriceBonus() / 100);
	}

	// ItemTrace Log �� ���ܾ� �Ѵٸ� �����
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature->getName() , pNPC->getName(), ITEM_LOG_DELETE, DETAIL_SHOPSELL);
	}

	// �÷��̾�� ���ǰ��� �����Ѵ�.
	// pPC->setGoldEx(playerMoney+itemPrice);
	// by sigi. 2002.9.4
	pPC->increaseGoldEx(itemPrice);

	// �÷��̾ ���� �� �� ó���� �͵��� ó���Ѵ�.
	pPC->sellItem( pItem );

	if ( pItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 4 )
	{
		addOlympicStat( pPC, 4, (uint)(itemNumber) );
	}

	// NPC���� �ڸ��� ����ϴٸ� �÷��̾ �� �������� �����Ѵ�.
	// ��� ��ɾ�� ���� �������� �ٷ� ���ش�.
	// �� ����� �����۸��� �����Ѵ�. �븻 �������� �׳� ����.
	// ����Ʈ �������� �������� �ʰ� ������.
	if (pNPC->getShopType()==SHOPTYPE_NORMAL
		&& pItem->getCreateType()!=Item::CREATE_TYPE_CREATE
		&& !pItem->getOptionTypeList().empty()
		&& !pItem->isTimeLimitItem()
	)
	{
		bSpecialItem = true;
		index        = pNPC->getFirstEmptySlot(SHOP_RACK_SPECIAL);

		if (index < SHOP_RACK_INDEX_MAX)
		{
			// �������� �߰��Ѵ�.
			pNPC->insertShopItem(SHOP_RACK_SPECIAL, index, pItem);

			// ����� �������� NPC�� �����忡 �߰������Ƿ�, ���� ������ �ö󰣴�.
			pNPC->increaseShopVersion(SHOP_RACK_SPECIAL);

			////////////////////////////////////////////////////////////////////////////
			// ��ó�� �÷��̾�鿡�Դ� GCShopBought��...
			////////////////////////////////////////////////////////////////////////////

			int         CenterX       = pNPC->getX();
			int         CenterY       = pNPC->getY();
			Creature*   pNearCreature = NULL;
			Player*     pNearPlayer   = NULL;

			GCShopBought boughtpkt;
			boughtpkt.setObjectID(NPCID);
			if (!pItem->getOptionTypeList().empty())
			{
				boughtpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_SPECIAL));
				boughtpkt.setShopType(SHOP_RACK_SPECIAL);
			}
			else
			{
				boughtpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_NORMAL));
				boughtpkt.setShopType(SHOP_RACK_NORMAL);
			}
			boughtpkt.setShopIndex(index);
			boughtpkt.setItemObjectID(ITEMOID);
			boughtpkt.setItemClass(pItem->getItemClass());
			boughtpkt.setItemType(pItem->getItemType());
			boughtpkt.setOptionType(pItem->getOptionTypeList());
			boughtpkt.setDurability(pItem->getDurability());
			boughtpkt.setSilver(pItem->getSilver());
			boughtpkt.setGrade(pItem->getGrade());
			boughtpkt.setEnchantLevel(pItem->getEnchantLevel());

			//pZone->broadcastPacket(pNPC->getX(), pNPC->getY(), &boughtpkt, pPC);

			try
			{
				for (int zx=CenterX-5; zx<=CenterX+5; zx++)
				{
					for (int zy=CenterY-5; zy<=CenterY+5; zy++)
					{
						// �ٿ�带 �Ѿ�� �ʴ°��� üũ
						if (!isValidZoneCoord(pZone, zx, zy)) continue;

						Tile & tile = pZone->getTile(zx, zy);

						// �ɾ�ٴϴ� ũ���ĸ� �˻�	
						if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
						{
							pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
							if (pNearCreature == NULL) continue;

							// ��� ������ �� �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer == NULL) continue;
								pNearPlayer->sendPacket(&boughtpkt);
							}
						}
						// ���ƴٴϴ� ũ���ĸ� �˻�
						if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
						{
							pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
							if (pNearCreature == NULL) continue;
							
							// ��� ������ �� �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;

							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer == NULL) continue;
								pNearPlayer->sendPacket(&boughtpkt);
							}
						}

					} // end of for (ZoneCoord_t zy=CenterY-5; zy<=CenterY+5; zy++)
				} // end of for (ZoneCoord_t zx=CenterX-5; zx<=CenterX+5; zx++)
			}
			catch (Throwable & t)
			{
				filelog("shopbug_packet.log", "%s", t.toString().c_str());
			}

		} // if (index < SHOP_RACK_INDEX_MAX)
		else
		{
			SAFE_DELETE(pItem);
		}
	} // if (pItem->getOptionType() != 0)
	else
	{
		bSpecialItem = false;
		SAFE_DELETE(pItem);
	}

	// ������ �� �÷��̾�� GCShopSellOK��...������.
	GCShopSellOK okpkt;
	okpkt.setObjectID(NPCID);
	if (bSpecialItem) okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_SPECIAL));
	else              okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_NORMAL));
	okpkt.setItemObjectID(ITEMOID);
	//okpkt.setPrice(playerMoney+itemPrice);
	// playerMoney + itemPrice �� MAX_MONEY�� �Ѿ �� �ִ�.
	// 2003.1.8 by bezz
	okpkt.setPrice(pPC->getGold());
	pPlayer->sendPacket(&okpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//
// ���� ����Ŭ�� ó���Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::executeMotorcycle (CGShopRequestSell* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ��Ŷ ������ �̾Ƴ���.
	ObjectID_t      NPCID       = pPacket->getObjectID();
	ObjectID_t      ITEMOID     = pPacket->getItemObjectID();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

	Zone* pZone = pPC->getZone();
	if (pZone == NULL) return sendFailPacket(pPacket, pPlayer);

	Creature* pNPCBase = NULL;
	/*
	try 
	{ 
		pNPCBase = pZone->getCreature(NPCID); 
	} 
	catch (NoSuchElementException & nsee) 
	{ 
		pNPCBase = NULL; 
	}
	*/

	// NoSuch����. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 

	if (pNPCBase == NULL || !pNPCBase->isNPC()) return sendFailPacket(pPacket, pPlayer);

	NPC*        pNPC    = dynamic_cast<NPC*>(pNPCBase);
	int         CenterX = pNPC->getX();
	int         CenterY = pNPC->getY();
	
	// �÷��̾ �ȷ��� �ϴ� �������� ������ �ִ��� �˻�
	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();
	Item*      pItem       = pInventory->getItemWithObjectID(ITEMOID);
	if (pItem == NULL) return sendFailPacket(pPacket, pPlayer);

	// ���� ���� ������ �˻��ؼ�, ���� ����Ŭ�� �ִ��� Ȯ���Ѵ�.
	try
	{
		for (int zx=CenterX-5; zx<=CenterX+5; zx++)
		{
			for (int zy=CenterY-5; zy<=CenterY+5; zy++)
			{
				// �ٿ�带 �Ѿ�� �ʴ°��� üũ
				if (!isValidZoneCoord(pZone, zx, zy)) continue;

				Tile & tile = pZone->getTile(zx, zy);
				if (tile.hasItem())
				{
					Item* pItemOnTile = tile.getItem();
					if (pItemOnTile == NULL) continue;

					// ���� �������� Ÿ�� ���� ���� ���, ���� ����Ŭ���� Ȯ���Ѵ�.
					if (pItemOnTile->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE)
					{
						DWORD    targetID     = dynamic_cast<Key*>(pItem)->getTarget();
						ItemID_t motorcycleID = pItemOnTile->getItemID();

						if (targetID == motorcycleID)
						{
							// ���ͻ���Ŭ�� DB���� �����Ѵ�.
							pItemOnTile->destroy();

							// �÷��̾��� �κ��丮���� ���踦 �����Ѵ�.
							pInventory->deleteItem(ITEMOID);
							pItem->destroy();
							SAFE_DELETE(pItem);
							
							// ���� ���� �ƴ϶�, ������� ���� ��� �Ѵ�.
							Price_t itemPrice = g_pPriceManager->getPrice(pItemOnTile, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC);

							// �÷��̾��� ���� �ø���.
							//pPC->setGoldEx(playerMoney+itemPrice);
							// by sigi. 2002.9.4
							pPC->increaseGoldEx(itemPrice);

							// ������ �� �÷��̾�� GCShopSellOK��...������.
							GCShopSellOK okpkt;
							okpkt.setObjectID(NPCID);
							if (!pItemOnTile->getOptionTypeList().empty()) okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_SPECIAL));
							else                                   okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_NORMAL));
							okpkt.setItemObjectID(ITEMOID);
							okpkt.setPrice(playerMoney+itemPrice);
							pPlayer->sendPacket(&okpkt);

							// ��ŷ ���Ϳ��� �ڽ��� ������ �ش�.
							if (g_pParkingCenter->hasMotorcycleBox(motorcycleID)) 
								g_pParkingCenter->deleteMotorcycleBox(motorcycleID);

							// NPC���� �ڸ��� ����ϴٸ� �÷��̾ �� �������� �����Ѵ�.
							// �� ����� �����۸��� �����Ѵ�. �븻 �������� �׳� ����.
							//if (pItemOnTile->getOptionType() != 0)
							//{
							//	index = pNPC->getFirstEmptySlot(SHOP_RACK_SPECIAL);
							//	if (index < SHOP_RACK_INDEX_MAX)
							//	{
							//		pNPC->insertShopItem(SHOP_RACK_SPECIAL, index, pItemOnTile);
							//		// ����� �������� NPC�� �����忡 �߰������Ƿ�, ���� ������ �ö󰣴�.
							//		pNPC->increaseShopVersion(SHOP_RACK_SPECIAL);
							//	}
							//}
							//else
							//{
							//	SAFE_DELETE(pItemOnTile);
							//}

							// ���� ����Ŭ�� ã�����Ƿ�, �� ���� ������. 
							return;
						}
					}
				}
			} // end of for (ZoneCoord_t zy=CenterY-5; zy<=CenterY+5; zy++)
		} // end of for (ZoneCoord_t zx=CenterX-5; zx<=CenterX+5; zx++)
	}
	catch (Throwable & t)
	{
		filelog("shopbug_packet.log", "%s", t.toString().c_str());
	}

	// FOR ������ �� ����, �̱��� �Դٴ� ���� ��ó�� ������̰� ���ٴ� ���̴�...
	// �׷��Ƿ� ���� ����Ŭ �ȱⰡ �����ߴٴ� ���� �˸���.
	GCShopSellFail failpkt;
	failpkt.setObjectID(NPCID);
	pPlayer->sendPacket(&failpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 
// �ذ� �Ѳ����� �ȱ⸦ �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::executeOpAllSkull (CGShopRequestSell* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	ObjectID_t      NPCID        = pPacket->getObjectID();
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);

	Zone* pZone = pPC->getZone();
	if (pZone == NULL) return sendFailPacket(pPacket, pPlayer);

	Creature* pNPCBase = NULL;
	/*
	try 
	{ 
		pNPCBase = pZone->getCreature(NPCID); 
	}
	catch (NoSuchElementException & nsee) 
	{ 
		pNPCBase = NULL; 
	}
	*/

	// NoSuch����. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 
	
	if (pNPCBase == NULL || !pNPCBase->isNPC()) return sendFailPacket(pPacket, pPlayer);

	NPC*       pNPC        = dynamic_cast<NPC*>(pNPCBase);
	Inventory* pInventory  = pPC->getInventory();
	// by sigi. 2002.9.4
	//Gold_t     playerMoney = pPC->getGold(); 
	Price_t    itemPrice   = 0;
	Item*      pItem       = NULL;

	for (uint y=0; y<pInventory->getHeight(); y++)
	{
		for (uint x=0; x<pInventory->getWidth(); x++)
		{
			pItem = pInventory->getItem(x, y);

			// �������� �����ϰ�, �ذ��̶��...
			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
			{
				// ������ ������ ����ؼ� �÷��̾��� ������ ���Ѵ�.
				//itemPrice = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC) * pItem->getNum();
				//playerMoney += itemPrice;

				// by sigi. 2002.9.4
				itemPrice += g_pPriceManager->getPrice(pItem, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC) * pItem->getNum();
				
				// �κ��丮 �� DB���� �������� �����Ѵ�.
				pInventory->deleteItem(x, y);
				pItem->destroy();
				SAFE_DELETE(pItem);
			}
		}
	}

	itemPrice = itemPrice * (g_pVariableManager->getHeadPriceBonus() / 100);

	// �÷��̾�� ���ǰ��� �����Ѵ�.
	//pPC->setGoldEx(playerMoney);
	// by sigi. 2002.9.4
	pPC->increaseGoldEx(itemPrice);

	// ������ �� �÷��̾�� GCShopSellOK��...������.
	GCShopSellOK okpkt;
	okpkt.setObjectID(NPCID);
	okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_NORMAL));
	okpkt.setItemObjectID(0);
	okpkt.setPrice(pPC->getGold());
	pPlayer->sendPacket(&okpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

void CGShopRequestSellHandler::executeOpSwapAdvancementItem(CGShopRequestSell* pPacket, Player* pPlayer)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	ObjectID_t      NPCID        = pPacket->getObjectID();
	ObjectID_t      ITEMOID      = pPacket->getItemObjectID();
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);

	if ( !pPC->isAdvanced() )
	{
		return sendFailPacket(pPacket, pPlayer);
	}

	Zone* pZone = pPC->getZone();
	if (pZone == NULL) return sendFailPacket(pPacket, pPlayer);

	Creature*		pNPCBase = pZone->getCreature(NPCID); 
	if (pNPCBase == NULL || !pNPCBase->isNPC()) return sendFailPacket(pPacket, pPlayer);
	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);
	
	Inventory* pInventory  = pPC->getInventory();
	Item*      pItem       = pInventory->getItemWithObjectID(ITEMOID);

	if ( pItem == NULL || pItem->isTimeLimitItem() )
	{
		return sendFailPacket(pPacket, pPlayer);
	}

	Item::ItemClass iClass = Item::ITEM_CLASS_MAX;
	ItemType_t		iType = 0;
	Grade_t			iGrade = 0;
	FlagSetType		fType = FLAGSET_MAX;

	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
	Assert(pItemInfo!=NULL);

	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
			{
				switch ( pItem->getItemType() )
				{
					case 9:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 2;
							break;
						}
					case 11:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 4;
							break;
						}
					case 12:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 6;
							break;
						}
					case 13:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 8;
							break;
						}
					default:
						break;
				}
				if ( iClass == Item::ITEM_CLASS_SG ) iClass = Item::ITEM_CLASS_SR;
				if ( iClass == Item::ITEM_CLASS_SMG ) iClass = Item::ITEM_CLASS_AR;
				break;
			}
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			{
				switch ( pItem->getItemType() )
				{
					case 7:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 2;
							break;
						}
					case 9:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 4;
							break;
						}
					case 10:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 6;
							break;
						}
					case 11:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 8;
							break;
						}
					default:
						break;
				}
				break;
			}

		case Item::ITEM_CLASS_COAT:
		case Item::ITEM_CLASS_TROUSER:
			{
				switch ( pItem->getItemType() )
				{
					case 14:
					case 15:
						{
							iClass = pItem->getItemClass();
							iType = 24 + (pItem->getItemType()%2);
							iGrade = 2;
							break;
						}
					case 18:
					case 19:
					case 20:
					case 21:
					case 22:
					case 23:
						{
							iClass = pItem->getItemClass();
							iType = 24 + (pItem->getItemType()%2);
							iGrade = 4 + (((pItem->getItemType()-18)/2)*2);
							break;
						}
					default:
						break;
				}
				break;
			}
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
			{
				switch ( pItem->getItemType() )
				{
					case 14:
						{
							iClass = pItem->getItemClass();
							iType = 19;
							iGrade = 2;
							break;
						}
					case 16:
						{
							iClass = pItem->getItemClass();
							iType = 19;
							iGrade = 4;
							break;
						}
					case 17:
						{
							iClass = pItem->getItemClass();
							iType = 19;
							iGrade = 6;
							break;
						}
					case 18:
						{
							iClass = pItem->getItemClass();
							iType = 19;
							iGrade = 8;
							break;
						}
					default:
						break;
				}
				break;
			}
		case Item::ITEM_CLASS_VAMPIRE_COAT:
			{
				switch ( pItem->getItemType() )
				{
					case 10:
					case 11:
						{
							iClass = pItem->getItemClass();
							iType = 20 + (pItem->getItemType()%2);
							iGrade = 2;
							break;
						}
					case 14:
					case 15:
					case 16:
					case 17:
					case 18:
					case 19:
						{
							iClass = pItem->getItemClass();
							iType = 20 + (pItem->getItemType()%2);
							iGrade = 4 + (((pItem->getItemType()-14)/2)*2);
							break;
						}
					default:
						break;
				}
				break;
			}
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
			{
				switch ( pItem->getItemType() )
				{
					case 9:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 2;
							break;
						}
					case 10:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 4;
							break;
						}
					case 11:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 6;
							break;
						}
					case 13:
						{
							iClass = pItem->getItemClass();
							iType = 14;
							iGrade = 8;
							break;
						}
					default:
						break;
				}
				break;
			}
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			{
				switch ( pItem->getItemType() )
				{
					case 9:
					case 30:
					case 31:
					case 39:
						{
							iClass = pItem->getItemClass();
							iType = 42;
							iGrade = pItemInfo->getItemLevel() * 2 - 16;
							break;
						}
					case 19:
					case 32:
					case 33:
					case 40:
						{
							iClass = pItem->getItemClass();
							iType = 43;
							iGrade = pItemInfo->getItemLevel() * 2 - 16;
							break;
						}
					case 29:
					case 34:
					case 35:
					case 41:
						{
							iClass = pItem->getItemClass();
							iType = 44;
							iGrade = pItemInfo->getItemLevel() * 2 - 16;
							break;
						}
					default:
						break;
				}
				break;
			}
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
			{
				switch ( pItem->getItemType() )
				{
					case 7:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 2;
							break;
						}
					case 8:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 4;
							break;
						}
					case 9:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 6;
							break;
						}
					case 11:
						{
							iClass = pItem->getItemClass();
							iType = 12;
							iGrade = 8;
							break;
						}
					default:
						break;
				}
				break;
			}
		default:
			break;
	}

	switch ( iClass )
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			fType = FLAGSET_SWAP_WEAPON;
			break;
		case Item::ITEM_CLASS_COAT:
		case Item::ITEM_CLASS_VAMPIRE_COAT:
		case Item::ITEM_CLASS_OUSTERS_COAT:
			fType = FLAGSET_SWAP_COAT;
			break;
		case Item::ITEM_CLASS_TROUSER:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
			fType = FLAGSET_SWAP_TROUSER;
			break;
		default:
			break;
	}

	if ( iClass == Item::ITEM_CLASS_MAX || fType == FLAGSET_MAX )
	{
		sendFailPacket( pPacket, pPlayer );
		return;
	}

	FlagSet* pFlagSet = pPC->getFlagSet();
	if ( pFlagSet->isOn(fType) )
	{
		sendFailPacket( pPacket, pPlayer );
		return;
	}

	Item* pNewItem = g_pItemFactoryManager->createItem( iClass, iType, pItem->getOptionTypeList() );
	if ( pNewItem == NULL )
	{
		sendFailPacket( pPacket, pPlayer );
		return;
	}
	pNewItem->setGrade(iGrade);

	_TPOINT tp;
	if ( !pInventory->getEmptySlot(pNewItem, tp) )
	{
		SAFE_DELETE( pNewItem );
		sendFailPacket( pPacket, pPlayer );
		return;
	}

	filelog("ItemSwap.log", "[%s:%s] %s <-> %s",
			pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->toString().c_str(), pNewItem->toString().c_str() );

	pNewItem->setTraceItem( bTraceLog( pNewItem ) );

	pInventory->deleteItem(ITEMOID);
	pItem->whenPCLost(pPC);

	if (!pItem->destroy())
	{
		filelog("shopDBBug.txt", "NoSuchItemInDB-destroy: %s", pItem->toString().c_str());

		throw DisconnectException("������ ������µ� DB�� ����.");
	}

	pZone->registerObject( pNewItem );

	GCShopSellOK okpkt;
	okpkt.setObjectID(NPCID);
	okpkt.setShopVersion(-1);
	okpkt.setItemObjectID(ITEMOID);
	okpkt.setPrice(0);
	pGamePlayer->sendPacket(&okpkt);

	// ItemTrace Log �� ���ܾ� �Ѵٸ� �����
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature->getName() , pNPC->getName(), ITEM_LOG_DELETE, DETAIL_SHOPSELL);
	}

	if ( pNewItem->isTraceItem() )
	{
		remainTraceLog( pNewItem, pNPC->getName() , pCreature->getName(), ITEM_LOG_CREATE, DETAIL_SHOPBUY);
	}

	Assert( pInventory->addItem( pNewItem, tp ) );

	pNewItem->create(pPC->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y );

	pFlagSet->turnOn(fType);
	pFlagSet->save( pPC->getName() );

	GCCreateItem gcCI;
	makeGCCreateItem( &gcCI, pNewItem, tp.x, tp.y );

	pGamePlayer->sendPacket( &gcCI );

#endif

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//
// ���� �ȱⰡ �����ߴٴ� ������ �����ش�.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::sendFailPacket (CGShopRequestSell* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GCShopSellFail failpkt;
	failpkt.setObjectID(pPacket->getObjectID());
	pPlayer->sendPacket(&failpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

