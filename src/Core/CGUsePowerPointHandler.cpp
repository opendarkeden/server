//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePowerPointHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGUsePowerPoint.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "ItemFactoryManager.h"
	#include "Inventory.h"
	#include "Assert1.h"

	#include "mofus/Mofus.h"
	#include "GCUsePowerPointResult.h"
	#include "GCCreateItem.h"

struct POWER_POINT_ITEM_TEMPLATE
{
	GCUsePowerPointResult::ITEM_CODE	ItemCode;
	Item::ItemClass						ItemClass;
	ItemType_t							ItemType;
	uint								Ratio;
	string								ItemName;
};

const POWER_POINT_ITEM_TEMPLATE PowerPointItemTemplate[7] =
{
	{ GCUsePowerPointResult::CANDY,					Item::ITEM_CLASS_EVENT_ETC,			14,	28,	"노란사탕" },
	{ GCUsePowerPointResult::RESURRECTION_SCROLL,	Item::ITEM_CLASS_RESURRECT_ITEM,	0,	20,	"부활 스크롤" },
	{ GCUsePowerPointResult::ELIXIR_SCROLL,			Item::ITEM_CLASS_RESURRECT_ITEM,	1,	20,	"엘릭서 스크롤" },
	{ GCUsePowerPointResult::MEGAPHONE,				Item::ITEM_CLASS_EFFECT_ITEM,		0,	10,	"확성기1(30분)" },
	{ GCUsePowerPointResult::NAMING_PEN,			Item::ITEM_CLASS_EVENT_GIFT_BOX,	22,	10,	"네이밍 펜" },
	{ GCUsePowerPointResult::SIGNPOST,				Item::ITEM_CLASS_EVENT_TREE,		26,	10,	"알림판1(6시간)" },
	{ GCUsePowerPointResult::BLACK_RICE_CAKE_SOUP,	Item::ITEM_CLASS_EVENT_STAR,		11, 2,	"검은떡국" }

};
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUsePowerPointHandler::execute (CGUsePowerPoint* pPacket , Player* pPlayer)
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);


    //cout << "--------------------------------------------------" << endl;
    //cout << "RECV UsePowerPoint (Name:" << pCreature->getName() << ")" << endl;
    //cout << "--------------------------------------------------" << endl;


#ifdef __MOFUS__

	GCUsePowerPointResult gcUsePowerPointResult;

	// 파워 포인트가 있는지 확인
	if (pPC->getPowerPoint() < 300 )
	{
		// 파워 포인트가 부족하다.
		gcUsePowerPointResult.setErrorCode(GCUsePowerPointResult::NOT_ENOUGH_POWER_POINT);

		pGamePlayer->sendPacket(&gcUsePowerPointResult);

		return;
	}

	// 인벤토리에 공간이 있는지 확인한다.
	_TPOINT pt;
	if (!pPC->getInventory()->getEmptySlot(1, 2, pt ) )
	{
		// 인벤토리에 공간이 부족하다.
		gcUsePowerPointResult.setErrorCode(GCUsePowerPointResult::NOT_ENOUGH_INVENTORY_SPACE);

		pGamePlayer->sendPacket(&gcUsePowerPointResult);

		return;
	}

	// 아이템 랜덤 생성
	int ratio = rand() % 100 + 1;
	
	GCUsePowerPointResult::ITEM_CODE itemCode;
	Item::ItemClass itemClass;
	ItemType_t itemType;
	string itemName;

	int sum = 0;
	bool bFind = false;
	for (int i = 0; i < 7; ++i )
	{
		sum += PowerPointItemTemplate[i].Ratio;
		if (sum >= ratio )
		{
			bFind = true;
			itemCode = PowerPointItemTemplate[i].ItemCode;
			itemClass = PowerPointItemTemplate[i].ItemClass;
			itemType = PowerPointItemTemplate[i].ItemType;
			itemName = PowerPointItemTemplate[i].ItemName;
			break;
		}
	}

	if (bFind )
	{
		// 아이템 생성 및 추가
		list<OptionType_t> nullOption;
		Item* pItem = g_pItemFactoryManager->createItem(itemClass, itemType, nullOption);

		pPC->getZone()->registerObject(pItem);

		if (pPC->getInventory()->addItem(pItem, pt ) )
		{
			// DB 에 아이템 생성
			pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

			// ItemTraceLog 를 만긴다.
			remainTraceLog(pItem, "Mofus", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);

			// 결과를 클라이언트에 알리기	
            GCCreateItem gcCreateItem;
            gcCreateItem.setObjectID(pItem->getObjectID());
            gcCreateItem.setItemClass(pItem->getItemClass());
            gcCreateItem.setItemType(pItem->getItemType());
            gcCreateItem.setOptionType(pItem->getOptionTypeList());
            gcCreateItem.setDurability(pItem->getDurability());
            gcCreateItem.setItemNum(pItem->getNum());
            gcCreateItem.setInvenX(pt.x);
            gcCreateItem.setInvenY(pt.y);

            pPlayer->sendPacket(&gcCreateItem);

			// 아이템 생성에 필요한 파워짱 포인트
			static int RequirePowerPoint = -300;

			// 파워짱 포인트 저장
			pPC->setPowerPoint(savePowerPoint(pPC->getName(), RequirePowerPoint ));

			// 결과를 클라이언트에 알리기
			gcUsePowerPointResult.setErrorCode(GCUsePowerPointResult::NO_ERROR);
			gcUsePowerPointResult.setItemCode(itemCode);
			gcUsePowerPointResult.setPowerPoint(pPC->getPowerPoint());

			pGamePlayer->sendPacket(&gcUsePowerPointResult);

			//cout << "--------------------------------------------------" << endl;
			//cout << "CREATE ITEM (name:" << pPC->getName() << ",usepowerpoint:" << RequirePowerPoint << ",createditem:" << itemName << ")" << endl;
			//cout << "--------------------------------------------------" << endl;

			filelog(MOFUS_LOG_FILE, "CREATE ITEM (name:%s,usepowerpoint:%d,createditem:%s",
										pPC->getName().c_str(),
										RequirePowerPoint,
										itemName.c_str());
		}
		else
		{
			//cout << "인벤토리에 넣기 실패" << endl;
		}
	}
	else
	{
		//cout << "랜덤 굴리기 실패 ratio : " << ratio << endl;
	}

#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}

