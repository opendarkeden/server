//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestSellHandler.cpp
// Written By  : 김성민
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

	#include "Gpackets/GCShopSellOK.h"
	#include "Gpackets/GCShopSellFail.h"
	#include "Gpackets/GCShopBought.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCCreateItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 플레이어가 팔려고 하는 아이템을 가지고 있는지 확인한 다음에,
// 일반 아이템과 모터 사이클 처리 부분으로 분기한다.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::execute (CGShopRequestSell* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
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
		// 플레이어가 팔려고 하는 아이템을 가지고 있는지 검사
		Inventory* pInventory = pPC->getInventory();
		if (pInventory->hasItem(ITEMOID) == false) 
			throw ProtocolException("CGShopRequestSellHandler::execute() : No such item to sell!");

		Item* pItem = pInventory->getItemWithObjectID(ITEMOID);
		if (pItem == NULL) return sendFailPacket(pPacket, pPlayer);
		if ( pPC->getStore()->hasItem( pItem ) ) return sendFailPacket(pPacket, pPlayer);

		//ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
		//Assert(pItemInfo!=NULL);

		// 유니크 아이템은 못판다.
		// 특정 아이템 클래스는 팔 수 없다. by sigi. 2002.8.29
		// 선물 상자는 팔 수 있다. by bezz. 2002.12.13
		// 커플링은 팔 수 없다. by Sequoia. 2003. 3. 3
		// ItemUtil 안에 canSell 로 Extract 2003. 3. 3
		if ( !canSell( pItem ) )
		{
			return sendFailPacket(pPacket, pPlayer);
		}
		// 唐珂쇌掘齡돨膠틔꼇횻놔簡
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
// 일반 아이템을 처리한다.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::executeNormal (CGShopRequestSell* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
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

	// NoSuch제거. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 

	if (pNPCBase == NULL || !pNPCBase->isNPC()) return sendFailPacket(pPacket, pPlayer);

	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);
	
	// 플레이어가 팔려고 하는 아이템을 가지고 있는지 검사
	Inventory* pInventory  = pPC->getInventory();
	//Gold_t     playerMoney = pPC->getGold(); 
	Item*      pItem       = pInventory->getItemWithObjectID(ITEMOID);
	ItemNum_t  itemNumber  = pItem->getNum();
	Price_t    itemPrice   = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC) * itemNumber;

	// 플레이어의 인벤토리에 아이템을 제거한다.
	pInventory->deleteItem(ITEMOID);
	pItem->whenPCLost(pPC);

	if (!pItem->destroy())
	{
		filelog("shopDBBug.txt", "NoSuchItemInDB-destroy: %s", pItem->toString().c_str());

		throw DisconnectException("아이템 지울려는데 DB에 없다.");
	}

	// 만약 벨트라면 안에 있는 포션을 삭제해준다.
	// DB에서 지우는 것은 Belt::destroy()를 부르는 것만으로 포션까지 삭제된다.
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

	// Skull 일 경우 Variable Manager 에서 머리값 배수 값으로 가격을 새로 계산한다
	if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
	{
		itemPrice = itemPrice * (g_pVariableManager->getHeadPriceBonus() / 100);
	}

	// ItemTrace Log 를 남겨야 한다면 남긴다
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature->getName() , pNPC->getName(), ITEM_LOG_DELETE, DETAIL_SHOPSELL);
	}

	// 플레이어에게 물건값을 지불한다.
	// pPC->setGoldEx(playerMoney+itemPrice);
	// by sigi. 2002.9.4
	pPC->increaseGoldEx(itemPrice);

	// 플레이어가 물건 팔 때 처리할 것들을 처리한다.
	pPC->sellItem( pItem );

	if ( pItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 4 )
	{
		addOlympicStat( pPC, 4, (uint)(itemNumber) );
	}

	// NPC에게 자리가 충분하다면 플레이어가 판 아이템을 보관한다.
	// 운영자 명령어로 만든 아이템은 바로 없앤다.
	// 단 스페셜 아이템만을 보관한다. 노말 아이템은 그냥 버림.
	// 퀘스트 아이템은 보관하지 않고 버린다.
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
			// 아이템을 추가한다.
			pNPC->insertShopItem(SHOP_RACK_SPECIAL, index, pItem);

			// 스페셜 아이템을 NPC가 진열장에 추가했으므로, 상점 버전이 올라간다.
			pNPC->increaseShopVersion(SHOP_RACK_SPECIAL);

			////////////////////////////////////////////////////////////////////////////
			// 근처의 플레이어들에게는 GCShopBought를...
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
						// 바운드를 넘어가지 않는가를 체크
						if (!isValidZoneCoord(pZone, zx, zy)) continue;

						Tile & tile = pZone->getTile(zx, zy);

						// 걸어다니는 크리쳐를 검색	
						if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
						{
							pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
							if (pNearCreature == NULL) continue;

							// 방금 물건을 판 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer == NULL) continue;
								pNearPlayer->sendPacket(&boughtpkt);
							}
						}
						// 날아다니는 크리쳐를 검색
						if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
						{
							pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
							if (pNearCreature == NULL) continue;
							
							// 방금 물건을 판 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;

							// 만약 플레이어라면 패킷을 보내준다.
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

	// 물건을 산 플레이어에게 GCShopSellOK를...보낸다.
	GCShopSellOK okpkt;
	okpkt.setObjectID(NPCID);
	if (bSpecialItem) okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_SPECIAL));
	else              okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_NORMAL));
	okpkt.setItemObjectID(ITEMOID);
	//okpkt.setPrice(playerMoney+itemPrice);
	// playerMoney + itemPrice 가 MAX_MONEY를 넘어갈 수 있다.
	// 2003.1.8 by bezz
	okpkt.setPrice(pPC->getGold());
	pPlayer->sendPacket(&okpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//
// 모터 사이클을 처리한다.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::executeMotorcycle (CGShopRequestSell* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 패킷 정보를 뽑아낸다.
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

	// NoSuch제거. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 

	if (pNPCBase == NULL || !pNPCBase->isNPC()) return sendFailPacket(pPacket, pPlayer);

	NPC*        pNPC    = dynamic_cast<NPC*>(pNPCBase);
	int         CenterX = pNPC->getX();
	int         CenterY = pNPC->getY();
	
	// 플레이어가 팔려고 하는 아이템을 가지고 있는지 검사
	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();
	Item*      pItem       = pInventory->getItemWithObjectID(ITEMOID);
	if (pItem == NULL) return sendFailPacket(pPacket, pPlayer);

	// 주위 일정 범위를 검색해서, 모터 사이클이 있는지 확인한다.
	try
	{
		for (int zx=CenterX-5; zx<=CenterX+5; zx++)
		{
			for (int zy=CenterY-5; zy<=CenterY+5; zy++)
			{
				// 바운드를 넘어가지 않는가를 체크
				if (!isValidZoneCoord(pZone, zx, zy)) continue;

				Tile & tile = pZone->getTile(zx, zy);
				if (tile.hasItem())
				{
					Item* pItemOnTile = tile.getItem();
					if (pItemOnTile == NULL) continue;

					// 만일 아이템이 타일 위에 있을 경우, 모터 사이클인지 확인한다.
					if (pItemOnTile->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE)
					{
						DWORD    targetID     = dynamic_cast<Key*>(pItem)->getTarget();
						ItemID_t motorcycleID = pItemOnTile->getItemID();

						if (targetID == motorcycleID)
						{
							// 모터사이클을 DB에서 삭제한다.
							pItemOnTile->destroy();

							// 플레이어의 인벤토리에서 열쇠를 제거한다.
							pInventory->deleteItem(ITEMOID);
							pItem->destroy();
							SAFE_DELETE(pItem);
							
							// 열쇠 값이 아니라, 오토바이 값을 줘야 한다.
							Price_t itemPrice = g_pPriceManager->getPrice(pItemOnTile, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC);

							// 플레이어의 돈을 늘린다.
							//pPC->setGoldEx(playerMoney+itemPrice);
							// by sigi. 2002.9.4
							pPC->increaseGoldEx(itemPrice);

							// 물건을 판 플레이어에게 GCShopSellOK를...보낸다.
							GCShopSellOK okpkt;
							okpkt.setObjectID(NPCID);
							if (!pItemOnTile->getOptionTypeList().empty()) okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_SPECIAL));
							else                                   okpkt.setShopVersion(pNPC->getShopVersion(SHOP_RACK_NORMAL));
							okpkt.setItemObjectID(ITEMOID);
							okpkt.setPrice(playerMoney+itemPrice);
							pPlayer->sendPacket(&okpkt);

							// 뻑킹 센터에서 박스를 삭제해 준다.
							if (g_pParkingCenter->hasMotorcycleBox(motorcycleID)) 
								g_pParkingCenter->deleteMotorcycleBox(motorcycleID);

							// NPC에게 자리가 충분하다면 플레이어가 판 아이템을 보관한다.
							// 단 스페셜 아이템만을 보관한다. 노말 아이템은 그냥 버림.
							//if (pItemOnTile->getOptionType() != 0)
							//{
							//	index = pNPC->getFirstEmptySlot(SHOP_RACK_SPECIAL);
							//	if (index < SHOP_RACK_INDEX_MAX)
							//	{
							//		pNPC->insertShopItem(SHOP_RACK_SPECIAL, index, pItemOnTile);
							//		// 스페셜 아이템을 NPC가 진열장에 추가했으므로, 상점 버전이 올라간다.
							//		pNPC->increaseShopVersion(SHOP_RACK_SPECIAL);
							//	}
							//}
							//else
							//{
							//	SAFE_DELETE(pItemOnTile);
							//}

							// 모터 사이클을 찾았으므로, 할 일이 끝났다. 
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

	// FOR 루프를 다 돌고, 이까지 왔다는 것은 근처에 오토바이가 없다는 말이당...
	// 그러므로 모터 사이클 팔기가 실패했다는 것을 알린다.
	GCShopSellFail failpkt;
	failpkt.setObjectID(NPCID);
	pPlayer->sendPacket(&failpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 
// 해골 한꺼번에 팔기를 실행한다.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::executeOpAllSkull (CGShopRequestSell* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
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

	// NoSuch제거. by sigi. 2002.5.2
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

			// 아이템이 존재하고, 해골이라면...
			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
			{
				// 아이템 가격을 계산해서 플레이어의 돈에다 더한다.
				//itemPrice = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC) * pItem->getNum();
				//playerMoney += itemPrice;

				// by sigi. 2002.9.4
				itemPrice += g_pPriceManager->getPrice(pItem, pNPC->getMarketCondBuy(), SHOP_RACK_NORMAL, pPC) * pItem->getNum();
				
				// 인벤토리 및 DB에서 아이템을 삭제한다.
				pInventory->deleteItem(x, y);
				pItem->destroy();
				SAFE_DELETE(pItem);
			}
		}
	}

	itemPrice = itemPrice * (g_pVariableManager->getHeadPriceBonus() / 100);

	// 플레이어에게 물건값을 지불한다.
	//pPC->setGoldEx(playerMoney);
	// by sigi. 2002.9.4
	pPC->increaseGoldEx(itemPrice);

	// 물건을 산 플레이어에게 GCShopSellOK를...보낸다.
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
	throw(ProtocolException, Error)
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

		throw DisconnectException("아이템 지울려는데 DB에 없다.");
	}

	pZone->registerObject( pNewItem );

	GCShopSellOK okpkt;
	okpkt.setObjectID(NPCID);
	okpkt.setShopVersion(-1);
	okpkt.setItemObjectID(ITEMOID);
	okpkt.setPrice(0);
	pGamePlayer->sendPacket(&okpkt);

	// ItemTrace Log 를 남겨야 한다면 남긴다
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
// 물건 팔기가 실패했다는 정보를 날려준댜.
//
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestSellHandler::sendFailPacket (CGShopRequestSell* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GCShopSellFail failpkt;
	failpkt.setObjectID(pPacket->getObjectID());
	pPlayer->sendPacket(&failpkt);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

