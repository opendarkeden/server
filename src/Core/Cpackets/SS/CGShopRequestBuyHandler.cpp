//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestBuyHandler.cpp
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestBuy.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "PriceManager.h"
	#include "Tile.h"
	#include "ParkingCenter.h"
	#include "ItemUtil.h"
	#include "LogClient.h"
	#include "ZoneUtil.h"
	#include "CastleInfoManager.h"
	#include "Utility.h"

	#include "item/Key.h"
	#include "item/Potion.h"
	#include "item/Magazine.h"

	#include "Gpackets/GCShopBuyOK.h"
	#include "Gpackets/GCShopBuyFail.h"
	#include "Gpackets/GCShopSold.h"

	#include "SystemAvailabilitiesManager.h"
	#include "GuildManager.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
// 플레이어가 원하는 물건을 파는 NPC와 그 아이템이 있는지
// 확인하고, 일반 아이템과 모터 사이클 처리부분으로 분기한다.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::execute (CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 패킷 정보를 뽑아낸다.
	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ItemNum_t       itemNum     = pPacket->getItemNum();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pNPCBase    = NULL;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	if ( shopType == SHOP_RACK_MYSTERIOUS )
	{
		SYSTEM_ASSERT( SYSTEM_GAMBLE );
	}

	//try 
	//{ 

	// NoSuch제거. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 
	//}	
	if (pNPCBase==NULL)//catch (NoSuchElementException) 
	{ 
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NPC_NOT_EXIST);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	if (!pNPCBase->isNPC())
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_NPC);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);

	/*
	// 상점에 아이템 있는지 없는지 체크용
	for (int i=0; i<=2; i++)
	{
		for (int j=0; j<20; j++)
		{
			cout << (int)pNPC->isExistShopItem(i, j) << " ";
		}

		cout << endl;
	}
	*/

	if (pNPC->getShopType() == SHOPTYPE_NORMAL)
	{
		// 플레이어가 구입하고자 하는 아이템을 NPC가 가지고 있는지 검사
		if (pNPC->isExistShopItem(shopType, shopIndex) == false) 
		{
			GCShopBuyFail gcShopBuyFail;
			gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST);
			gcShopBuyFail.setAmount(0);
			pPlayer->sendPacket(&gcShopBuyFail);
			return;
		}

		Item* pItem = pNPC->getShopItem(shopType, shopIndex);

		if ( pItem->getItemClass() == Item::ITEM_CLASS_TRAP_ITEM )
		{
			if( !g_pGuildManager->isGuildMaster ( pPC->getGuildID(), pPC ) || !pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_DEFENDER ) )
			{
				GCShopBuyFail gcShopBuyFail;
				gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST);
				gcShopBuyFail.setAmount(0);
				pPlayer->sendPacket(&gcShopBuyFail);
				return;
			}
		}

		// 아이템 갯수가 정상적인지를 검사
		if (itemNum < 1 || itemNum > ItemMaxStack[pItem->getItemClass()])
		{
			throw ProtocolException("CGShopRequestBuyHandler::execute() : 아이템 갯수 오류!");
		}

		// 아이템 갯수가 2개 이상이라면 정상적인 아이템인지를 검사
		// 쌓일 수 있는 아이템이 아니라면 갯수를 1로 세팅해 준다.
		if (itemNum > 1 && !isStackable(pItem->getItemClass()))
			pPacket->setItemNum(1);

		if (pItem->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE) executeMotorcycle(pPacket, pPlayer);
		else executeNormal(pPacket, pPlayer);
	}

///////////////////////////////////////////////////////////////////////
// 2001년 크리스마스 이벤트를 위해서 사용된 함수이다.
// 2002년 어린이날 이벤트를 위해서 재사용됨. 
// XMAS_EVENT에서 STAR_EVENT로 수정되어야 할 것으로 예정
//  2002.5.2 장홍창(changaya@metrotech.co.kr)
//////////////////////////////////////////////////////////////////////
#ifdef __XMAS_EVENT_CODE__
	else if (pNPC->getShopType() == SHOPTYPE_EVENT)
	{
		// 플레이어가 구입하고자 하는 아이템을 NPC가 가지고 있는지 검사
		if (pNPC->isExistShopItem(shopType, shopIndex) == false) 
		{
			GCShopBuyFail gcShopBuyFail;
			gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST);
			gcShopBuyFail.setAmount(0);
			pPlayer->sendPacket(&gcShopBuyFail);
			return;
		}

		// 아이템 갯수가 정상적인지를 검사
		if (itemNum != 1) 
			throw ProtocolException("CGShopRequestBuyHandler::execute() : 아이템 갯수 오류!");

		executeEvent(pPacket, pPlayer);
	}
#endif

	//cout << "Buy ok" << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 일반 아이템의 구입을 처리한다.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::executeNormal (CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ItemNum_t       itemNum     = pPacket->getItemNum();
	Coord_t         x           = pPacket->getX();
	Coord_t         y           = pPacket->getY();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*           pZone       = pPC->getZone();
	NPC*            pNPC        = dynamic_cast<NPC*>(pZone->getCreature(NPCID));
	Gold_t			itemTax		= 0;

	// NoSuch제거. by sigi. 2002.5.2
	if (pNPC==NULL) return;

	Item*           pItem       = pNPC->getShopItem(shopType, shopIndex);
	Price_t         itemMoney;
	bool 			bMysteriousRack = (shopType==SHOP_RACK_MYSTERIOUS);

	// Mysterious item은 가격 계산이 다르다.
	if (bMysteriousRack)
	{
		//cout << pPacket->toString().c_str() << endl;
		itemMoney = g_pPriceManager->getMysteriousPrice(pItem->getItemClass(), pCreature);
		//cout << "CGShopRequestBuyHandler::MysteriousItem Price = " << itemMoney << endl;
	}
	else
	{
		itemMoney = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondSell(), shopType, pPC) * itemNum;
		//cout << "CGShopRequestBuyHandler::normalItem Price = " << itemMoney << endl;
	}

	if ( pNPC->getTaxingCastleZoneID() != 0 )
	{
		int itemTaxRatio = pNPC->getTaxRatio( pPC );
		if (itemTaxRatio > 100)
		{
//			int NewItemMoney = getPercentValue((int)itemMoney, itemTaxRatio);
			int NewItemMoney = (int)(itemMoney * (itemTaxRatio/100.0));
			itemTax = ( NewItemMoney - itemMoney );

			itemMoney = NewItemMoney;
		}
	}

	Item::ItemClass IClass     	 	= pItem->getItemClass();
	ItemType_t      IType   	    = pItem->getItemType();
	const list<OptionType_t>& OType = pItem->getOptionTypeList();

	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();

	if (playerMoney < itemMoney)
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);

		//cout << "Not Enough Money for Mysterious Item" << endl;

		return;
	}
	
	// mysterious item을 생성해버린다.
	if (bMysteriousRack)
	{
		if (pZone->isPremiumZone() || pZone->isPayPlay())
		{
			pItem = getRandomMysteriousItem( pCreature, IClass );
		}
		else
		{
			// premium zone이 아니면 gamble level을 30으로 제한한다.
			pItem = getRandomMysteriousItem( pCreature, IClass, 30 );
		}

		Assert(pItem!=NULL);
		(pZone->getObjectRegistry()).registerObject(pItem);
	}

	// 먼저 포션이나, 탄창 같은 경우에는 아이템 갯수를 세팅해 주고 나서...
	if (isStackable(pItem))
	{
		pItem->setNum(itemNum);
	}
	else
	{
		pItem->setNum(1);
	}

	if (!pInventory->canAddingEx(x, y, pItem))
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);

		// mysterious item은 위에서 getRandomMysteriousItem()을 통해서
		// 생성되었기 때문에 지워줘야 한다.
		if (bMysteriousRack) SAFE_DELETE(pItem);

		//cout << "Can't Add to Inventory" << endl;

		return;
	}

	if ( pItem != NULL ) pItem->whenPCTake( pPC );

	// 플레이어가 산 아이템이 스페셜 아이템이라면 상점 버전을 올린다.
	if (shopType == SHOP_RACK_SPECIAL)
	{
		pNPC->increaseShopVersion(shopType);
	}

	// 플레이어의 돈을 줄인다.
	//pPC->setGoldEx(playerMoney - itemMoney);

	// by sigi. 2002.9.4
	pPC->decreaseGoldEx(itemMoney);
	filelog("Tax.log", "%s 가 %s 에게 %u 만큼을 세금으로 냈습니다.", pPC->getName().c_str(), pNPC->getName().c_str(), itemTax);
	g_pCastleInfoManager->increaseTaxBalance( pNPC->getTaxingCastleZoneID(), itemTax );

	//cout << "addItemEx" << endl;

	Item* pReturnItem = pInventory->addItemEx(x, y, pItem);
	if (pReturnItem == pItem)
	{
		//cout << "add ok" << endl;
		// pReturnItem과 pItem이 같다는 말은 아이템이 쌓이는 아이템이 
		// 아니었다는 말이다.


		// 기존의 ItemID를 그대로 유지한다. 
		// ItemID가 0이면.. create()할때 다시 ItemID를 받는다.
		// by sigi. 2002.10.28
		pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, x, y, pItem->getItemID());
		// 단순히 create만 부르면 DB에는 포션의 갯수 같은 것을 1개로 만든다.
		// 그러므로 다시 세이브를 불러서 실제적인 갯수를 세팅해줘야 한다.
		//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);

		// 개수를 바로 저장하도록 create를 수정했다.
		// item저장 최적화. by sigi. 2002.5.13

		// OK 패킷을 보낸다.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pItem->getObjectID());
		OKPacket.setItemClass(pItem->getItemClass());
		OKPacket.setItemType(pItem->getItemType());
		OKPacket.setOptionType(pItem->getOptionTypeList());
		OKPacket.setDurability(pItem->getDurability());
		OKPacket.setItemNum(pItem->getNum());
		OKPacket.setSilver(pItem->getSilver());
		OKPacket.setGrade(pItem->getGrade());
		OKPacket.setEnchantLevel(pItem->getEnchantLevel());
		OKPacket.setPrice(playerMoney-itemMoney);
		pPlayer->sendPacket(&OKPacket);

		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());
	}
	else
	{
		//cout << "pile ok" << endl;
		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());

		// pReturnItem과 pItem이 다르다는 말은 아이템이 
		// 쌓이는 아이템이었다는 말이다. 그러므로 더하라고 보낸 pItem은 
		// 삭제해 줘야 한다.
		SAFE_DELETE(pItem);
		//pReturnItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);
		// item저장 최적화. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Num=%d", pReturnItem->getNum());
		pReturnItem->tinysave(pField);


		// OK 패킷을 보낸다.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pReturnItem->getObjectID());
		OKPacket.setItemClass(pReturnItem->getItemClass());
		OKPacket.setItemType(pReturnItem->getItemType());
		OKPacket.setOptionType(pReturnItem->getOptionTypeList());
		OKPacket.setDurability(pReturnItem->getDurability());
		OKPacket.setItemNum(pReturnItem->getNum());
		OKPacket.setSilver(pReturnItem->getSilver());
		OKPacket.setGrade(pReturnItem->getGrade());
		OKPacket.setEnchantLevel(pReturnItem->getEnchantLevel());
		OKPacket.setPrice(playerMoney-itemMoney);
		pPlayer->sendPacket(&OKPacket);
	}

	// ItemTrace 로그를 남긴다
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pNPC->getName(), pCreature->getName(), ITEM_LOG_CREATE, DETAIL_SHOPBUY);
	}
	//cout << "send OK" << endl;

	// mysterious item이 아닌 경우..
	if (!bMysteriousRack)
	{
		pNPC->removeShopItem(shopType, shopIndex);
	}

	if (shopType == SHOP_RACK_NORMAL)
	{
		// 팔린 아이템이 노멀 아이템이라면 같은 타입, 클래스의 아이템을 생성한다.
		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);
		(pZone->getObjectRegistry()).registerObject(pNewItem);
		pNPC->insertShopItem(shopType, shopIndex, pNewItem);
	}
	else if (bMysteriousRack)
	{
		// mysterious item인 경우는 상점은 그대로 두면 된다.
		//cout << "mysterious item" << endl;
	}
	else
	{
		// 팔린 아이템이 노멀 아이템이 아니라면,
		// 근처의 플레이어들에게 상점의 물건이 팔렸다는 사실을 알려줘야 한다.
		int CenterX = pNPC->getX();
		int CenterY = pNPC->getY();
		GCShopSold soldpkt;
		soldpkt.setObjectID(NPCID);
		soldpkt.setShopVersion(pNPC->getShopVersion(shopType));
		soldpkt.setShopType(shopType);
		soldpkt.setShopIndex(shopIndex);

		try
		{
			for (int zx=CenterX-5; zx<=CenterX+5; zx++)
			{
				for (int zy=CenterY-5; zy<=CenterY+5; zy++)
				{
					// 바운드를 넘어가지 않는가 체크
					if (!isValidZoneCoord(pZone, zx, zy)) continue;

					Tile & tile = pZone->getTile(zx, zy);

					// 걸어다니는 크리쳐를 검색
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						if (pNearCreature != NULL)
						{
							// 방금 아이템을 구입한 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
					// 날아다니는 크리쳐를 검색
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						if (pNearCreature != NULL)
						{
							// 방금 아이템을 구입한 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
				} // for (ZoneCoord_t zy...) 끝
			} // for (ZoneCoord_t zx...) 끝
		}
		catch (Throwable& t)
		{
			filelog("shopbug_packet.log", "%s", t.toString().c_str());
		}
	} 

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 모터 사이클의 구입을 처리한다.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::executeMotorcycle (CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 패킷 정보를 뽑아낸다.
	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ZoneCoord_t     x           = pPacket->getX();
	ZoneCoord_t     y           = pPacket->getY();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*           pZone       = pPC->getZone();
	NPC*            pNPC        = dynamic_cast<NPC*>(pZone->getCreature(NPCID));

	// NoSuch제거. by sigi. 2002.5.2
	if (pNPC==NULL) return;

	Item*           pItem       = pNPC->getShopItem(shopType, shopIndex);
	Price_t         itemMoney   = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondSell(), shopType, pPC);
	Item::ItemClass IClass;
	ItemType_t      IType;

	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();

	list<OptionType_t> optionNULL;
	Item* pTestKey = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_KEY, 0, optionNULL);
	Assert(pTestKey != NULL);

	if (playerMoney < itemMoney)
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		SAFE_DELETE(pTestKey);
		return;
	}

	if (!pInventory->canAddingEx(x, y, pTestKey))
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		SAFE_DELETE(pTestKey);
		return;
	}
	
	// 플레이어가 산 아이템이 스페셜 아이템이라면 상점 버전을 올린다.
	if (shopType == SHOP_RACK_SPECIAL) pNPC->increaseShopVersion(shopType);

	// 플레이어의 돈을 줄인다.
	//pPC->setGoldEx(playerMoney - itemMoney);
	// by sigi. 2002.9.4
	pPC->decreaseGoldEx(itemMoney);
	
	// 먼저 모터 사이클을 NPC의 진열장에서 꺼내어 존에다 붙인다.
	// 글고 DB에다가 모터 사이클이 팔렸다는 것을 쓴다.
	TPOINT pt = pZone->addItem(pItem, pPC->getX(), pPC->getY(), false);
	if (pt.x == -1)
	{
		// 서버 측의 NPC에게서 방금 팔린 모터 사이클을 지운다.
		//pNPC->removeShopItem(shopType, shopIndex);

		//SAFE_DELETE(pItem);
		// 오토바이를 존에다 더할 수가 없었다. 쉬트... 걍 리턴하자.
		cerr << "######################################################" << endl;
		cerr << "# CRITICAL ERROR!!! Cannot add MOTORCYCLE to ZONE!!! #" << endl;
		cerr << "######################################################" << endl;
		return;
	}
	pItem->create(pPC->getName(), STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
	ItemID_t MotorcycleID = pItem->getItemID();

	// 모터사이클을 뻑킹 센터에 등록해 준다.
	MotorcycleBox* pBox = new MotorcycleBox(dynamic_cast<Motorcycle*>(pItem), pZone, pt.x, pt.y);
	Assert(pBox != NULL);
	g_pParkingCenter->addMotorcycleBox(pBox);

	// 다음으로 방금 생성한 모터 사이클에 맞는 키를 생성한다.
	// 글고 DB에다가 모터 사이클 키가 플레이어에게 넘어갔다는 것을 쓴다.
	Item* pKey = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_KEY, 2, optionNULL);
	Assert(pKey != NULL);
	(pZone->getObjectRegistry()).registerObject(pKey);
	dynamic_cast<Key*>(pKey)->setTarget(MotorcycleID);
	pKey->create(pPC->getName(), STORAGE_INVENTORY, 0, x, y);

	// 모터 사이클 키를 플레이어의 인벤토리에 더한다.
	pInventory->addItemEx(x, y, pKey);

	// 서버 측의 NPC에게서 방금 팔린 모터 사이클을 지운다.
	pNPC->removeShopItem(shopType, shopIndex);

	// OK 패킷을 보낸다.
	GCShopBuyOK OKPacket;
	OKPacket.setObjectID(NPCID);
	OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
	OKPacket.setItemObjectID(pKey->getObjectID());
	OKPacket.setItemClass(pKey->getItemClass());
	OKPacket.setItemType(pKey->getItemType());
	OKPacket.setOptionType(pKey->getOptionTypeList());
	OKPacket.setDurability(pKey->getDurability());
	OKPacket.setItemNum(1);
	OKPacket.setSilver(pKey->getSilver());
	OKPacket.setGrade(pKey->getGrade());
	OKPacket.setEnchantLevel(pKey->getEnchantLevel());
	OKPacket.setPrice(playerMoney-itemMoney);
	pPlayer->sendPacket(&OKPacket);

	// 팔린 모터 사이클이 노멀 모터 사이클이라면...
	// 같은 타입, 클래스의 모터 사이클을 생성한다.
	if (shopType == SHOP_RACK_NORMAL)
	{
		IClass = Item::ITEM_CLASS_MOTORCYCLE;
		IType  = pItem->getItemType();
		const list<OptionType_t>& OType  = pItem->getOptionTypeList();
		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);
		(pZone->getObjectRegistry()).registerObject(pNewItem);
		pNPC->insertShopItem(shopType, shopIndex, pNewItem);
	}
	else if (shopType == SHOP_RACK_MYSTERIOUS)
	{
	}
	else
	{
		// 팔린 모터 사이클이 노멀 모터 사이클이 아니라면 근처의 플레이어들에게
		// 상점의 모터 사이클이 팔렸다는 사실을 알려줘야 한다.
		
		int         CenterX       = pNPC->getX();
		int         CenterY       = pNPC->getY();
		Creature*   pNearCreature = NULL;
		Player*     pNearPlayer   = NULL;
		GCShopSold  soldpkt;

		soldpkt.setObjectID(NPCID);
		soldpkt.setShopVersion(pNPC->getShopVersion(shopType));
		soldpkt.setShopType(shopType);
		soldpkt.setShopIndex(shopIndex);

		try
		{
			for (int zx=CenterX-5; zx<=CenterX+5; zx++)
			{
				for (int zy=CenterY-5; zy<=CenterY+5; zy++)
				{
					// 바운드를 넘어가지 않는가 체크
					if (!isValidZoneCoord(pZone, zx, zy)) continue;

					Tile & tile = pZone->getTile(zx, zy);

					if (tile.hasCreature(Creature::MOVE_MODE_WALKING)) 
					{
						// 걸어다니는 크리쳐를 검색
						pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						if (pNearCreature != NULL)
						{
							// 방금 아이템을 구입한 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING)) 
					{
						// 날아다니는 크리쳐를 검색
						pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						if (pNearCreature != NULL)
						{
							// 방금 아이템을 구입한 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
				} // for (ZoneCoord_t zy...) 끝
			} // for (ZoneCoord_t zx...) 끝
		}
		catch (Throwable& t)
		{
			filelog("shopbug_packet.log", "%s", t.toString().c_str());
		}
	} // if (shopType == SHOP_RACK_NORMAL) else 끝

	SAFE_DELETE(pTestKey);

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 이벤트 아이템의 구입을 처리한다.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::executeEvent(CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

#ifdef __XMAS_EVENT_CODE__

	//cout << "CGShopRequestBuy::executeChildrenEvent() : BEGIN" << endl;

	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ItemNum_t       itemNum     = pPacket->getItemNum();
	Coord_t         x           = pPacket->getX();
	Coord_t         y           = pPacket->getY();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*           pZone       = pPC->getZone();
	NPC*            pNPC        = dynamic_cast<NPC*>(pZone->getCreature(NPCID));

	// NoSuch제거. by sigi. 2002.5.2
	if (pNPC==NULL) return;

	Item*           pItem       = pNPC->getShopItem(shopType, shopIndex);
	Item::ItemClass IClass      = pItem->getItemClass();
	ItemType_t      IType       = pItem->getItemType();
	const list<OptionType_t>& OType  = pItem->getOptionTypeList();

	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();
	XMAS_STAR  star;

	// 이벤트용 아이템의 이벤트 가격을 구한다.
	g_pPriceManager->getStarPrice(pItem, star);

	//cout << "사려고 하는 아이템:" << endl << pItem->toString() << endl;
	//cout << "사려고 하는 아이템의 가격:" << endl
	//	<< "COLOR:" << star.color << ",AMOUNT:" << star.amount << endl;

	// 먼저 포션이나, 탄창 같은 경우에는 아이템 갯수를 세팅해 주고 나서...
	// 사실 이벤트 아이템에는 포션이나 탄창이 포함되어 있지 않지만...
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
			dynamic_cast<Potion*>(pItem)->setNum(itemNum);
			break;
		case Item::ITEM_CLASS_MAGAZINE:
			dynamic_cast<Magazine*>(pItem)->setNum(itemNum);
			break;
		default:
			break;
	}

	// 이 부분에서 해당하는 가격만큼의 별을 가지고 있는지를 체크한다.
	if (!pInventory->hasEnoughStar(star))
	{
		//cout << "플레이어는 해당하는 만큼의 별을 가지고 있지 못합니다." << endl;

		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	//cout << "플레이어는 해당하는 만큼 이상의 별을 가지고 있습니다." << endl;

	// 혹시라도 자리가 없다면...
	if (!pInventory->canAddingEx(x, y, pItem))
	{
		//cout << "인벤토리에 자리가 없습니다." << endl;

		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	// 플레이어가 산 아이템이 스페셜 아이템이라면 상점 버전을 올린다.
	if (shopType == SHOP_RACK_SPECIAL)
	{
		pNPC->increaseShopVersion(shopType);
	}

	// 이 부분에서 플레이어의 별을 줄인다.
	pInventory->decreaseStar(star);

	//cout << "플레이어의 별을 줄였습니다." << endl;

	Item* pReturnItem = pInventory->addItemEx(x, y, pItem);
	if (pReturnItem == pItem)
	{
		// pReturnItem과 pItem이 같다는 말은 아이템이 쌓이는 아이템이 
		// 아니었다는 말이다.
		pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, x, y);
		// 단순히 create만 부르면 DB에는 포션의 갯수 같은 것을 1개로 만든다.
		// 그러므로 다시 세이브를 불러서 실제적인 갯수를 세팅해줘야 한다.
		//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);

		// item의 create에서 개수를 저장하도록 바꿨다.
        // item저장 최적화. by sigi. 2002.5.13
		        
		// OK 패킷을 보낸다.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pItem->getObjectID());
		OKPacket.setItemClass(pItem->getItemClass());
		OKPacket.setItemType(pItem->getItemType());
		OKPacket.setOptionType(pItem->getOptionTypeList());
		OKPacket.setDurability(pItem->getDurability());
		OKPacket.setItemNum(pItem->getNum());
		OKPacket.setSilver(pItem->getSilver());
		OKPacket.setGrade(pItem->getGrade());
		OKPacket.setEnchantLevel(pItem->getEnchantLevel());
		OKPacket.setPrice(playerMoney);
		pPlayer->sendPacket(&OKPacket);

		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());
	}
	else
	{
		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());

		// pReturnItem과 pItem이 다르다는 말은 아이템이 
		// 쌓이는 아이템이었다는 말이다. 그러므로 더하라고 보낸 pItem은 
		// 삭제해 줘야 한다.
		SAFE_DELETE(pItem);
		//pReturnItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);
		// item저장 최적화. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Num=%d", pReturnItem->getNum());
		pReturnItem->tinysave(pField);


		// OK 패킷을 보낸다.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pReturnItem->getObjectID());
		OKPacket.setItemClass(pReturnItem->getItemClass());
		OKPacket.setItemType(pReturnItem->getItemType());
		OKPacket.setOptionType(pReturnItem->getOptionTypeList());
		OKPacket.setDurability(pReturnItem->getDurability());
		OKPacket.setItemNum(pReturnItem->getNum());
		OKPacket.setSilver(pReturnItem->getSilver());
		OKPacket.setGrade(pReturnItem->getGrade());
		OKPacket.setEnchantLevel(pReturnItem->getEnchantLevel());
		OKPacket.setPrice(playerMoney);
		pPlayer->sendPacket(&OKPacket);
	}

	pNPC->removeShopItem(shopType, shopIndex);

	if (shopType == SHOP_RACK_NORMAL)
	{
		// 팔린 아이템이 노멀 아이템이라면 같은 타입, 클래스의 아이템을 생성한다.
		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);
		(pZone->getObjectRegistry()).registerObject(pNewItem);
		pNPC->insertShopItem(shopType, shopIndex, pNewItem);
	}
	else if (shopType == SHOP_RACK_MYSTERIOUS)
	{
	}
	else
	{
		// 팔린 아이템이 노멀 아이템이 아니라면,
		// 근처의 플레이어들에게 상점의 물건이 팔렸다는 사실을 알려줘야 한다.
		int CenterX = pNPC->getX();
		int CenterY = pNPC->getY();
		GCShopSold soldpkt;
		soldpkt.setObjectID(NPCID);
		soldpkt.setShopVersion(pNPC->getShopVersion(shopType));
		soldpkt.setShopType(shopType);
		soldpkt.setShopIndex(shopIndex);

		//VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		try
		{
			for (int zx=CenterX-5; zx<=CenterX+5; zx++)
			{
				for (int zy=CenterY-5; zy<=CenterY+5; zy++)
				{
					// 바운드를 넘어가지 않는가 체크
					if (!isValidZoneCoord(pZone, zx, zy)) continue;

					Tile & tile = pZone->getTile(zx, zy);

					// 걸어다니는 크리쳐를 검색
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						if (pNearCreature != NULL)
						{
							// 방금 아이템을 구입한 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
					// 날아다니는 크리쳐를 검색
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						if (pNearCreature != NULL)
						{
							// 방금 아이템을 구입한 플레이어라면 생략
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// 만약 플레이어라면 패킷을 보내준다.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
				} // for (ZoneCoord_t zy...) 끝
			} // for (ZoneCoord_t zx...) 끝
		}
		catch (Throwable& t)
		{
			filelog("shopbug_packet.log", "%s", t.toString().c_str());
		}
	} 

	//cout << "CGShopRequestBuy::executeEvent() : END" << endl;

#endif
#endif

	__END_DEBUG_EX __END_CATCH
}

