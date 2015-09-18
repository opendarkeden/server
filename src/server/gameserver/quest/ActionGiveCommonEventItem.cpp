////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveCommonEventItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionGiveCommonEventItem.h"
#include "Item.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"
#include "OptionInfo.h"
#include "Zone.h"
#include "VariableManager.h"
#include "DB.h"

#include "GCCreateItem.h"
#include "GCNPCResponse.h"

#include <list>


struct EVENT_ITEM_TEMPLATE
{
	Item::ItemClass		ItemClass;
	ItemType_t			ItemType;
	Grade_t				ItemGrade;
	string				ItemOption;
	uint				Ratio;
	string				ItemName;
};

const int EVENT_ITEM_200505_SLAYER_MAX = 24;
const EVENT_ITEM_TEMPLATE Event200505SlayerTemplate[EVENT_ITEM_200505_SLAYER_MAX] =
{
	{ Item::ITEM_CLASS_COAT,				10,		4,		"DUR+5",		80,		"컴뱃 메일(M)" },
	{ Item::ITEM_CLASS_TROUSER,				10,		4,		"DUR+5",		80,		"컴뱃 게이터(M)" },
	{ Item::ITEM_CLASS_COAT,				11,		4,		"VIS+3",		80,		"컴뱃 메일(W)" },
	{ Item::ITEM_CLASS_TROUSER,				11,		4,		"VIS+3",		80,		"컴뱃 게이터(W)" },
	{ Item::ITEM_CLASS_GLOVE,				5,		4,		"DEF+5",		80,		"틴 플레이트 건틀렛" },
	{ Item::ITEM_CLASS_SHOES,				5,		4,		"ASPD+5",		80,		"사란 부츠" },
	{ Item::ITEM_CLASS_BELT,				2,		4,		"RES+5",		80,		"미디엄 벨트" },
	{ Item::ITEM_CLASS_SHIELD,				5,		4,		"DAM+4",		80,		"드래곤 쉴드" },
	{ Item::ITEM_CLASS_BLADE,				3,		4,		"BLRES+3",		80,		"세버드 블레이드" },
	{ Item::ITEM_CLASS_SG,					3,		4,		"TOHIT+3",		80,		"AM-99 맘모스" },
	{ Item::ITEM_CLASS_SMG,					3,		4,		"INT+5",		80,		"B-INTER" },
	{ Item::ITEM_CLASS_AR,					3,		4,		"ACRES+3",		80,		"MK-2 G2" },
	{ Item::ITEM_CLASS_SR,					3,		4,		"ATTR+3",		80,		"X-45T 토마호크" },
	{ Item::ITEM_CLASS_NECKLACE,			4,		4,		"TOHIT+4",		80,		"크레센트 네크리스" },
	{ Item::ITEM_CLASS_BRACELET,			4,		4,		"DEF+4",		80,		"오러스 브레이슬릿" },
	{ Item::ITEM_CLASS_NECKLACE,			5,		4,		"CURES+2",		80,		"블루 센스" },
	{ Item::ITEM_CLASS_BRACELET,			5,		4,		"HP+5",			80,		"오러스 브레이슬릿" },
	{ Item::ITEM_CLASS_RING,				5,		4,		"VIS+3",		80,		"행운의 반지" },
	{ Item::ITEM_CLASS_CARRYING_RECEIVER,	0,		4,		"",				20,		"캐링 리시버 1단" },
	{ Item::ITEM_CLASS_RESURRECT_ITEM,		0,		0,		"",				200,	"부활 스크롤" },
	{ Item::ITEM_CLASS_RESURRECT_ITEM,		1,		0,		"",				100,	"엘릭서 스크롤" },
	{ Item::ITEM_CLASS_EVENT_ETC,			13,		0,		"",				3000,	"스톰 폭죽" },
	{ Item::ITEM_CLASS_EVENT_ETC,			3,		0,		"",				4740,	"드래곤 폭죽" },
	{ Item::ITEM_CLASS_EVENT_TREE,			27,		0,		"",				500,	"12시간 알림판" }
};

const int EVENT_ITEM_200505_VAMPIRE_MAX = 19;
const EVENT_ITEM_TEMPLATE Event200505VampireTemplate[EVENT_ITEM_200505_VAMPIRE_MAX] =
{
	{ Item::ITEM_CLASS_VAMPIRE_COAT,		6,		4,		"CRI+9",		110,	"하이딩 로브" },
	{ Item::ITEM_CLASS_VAMPIRE_COAT,		8,		4,		"VIS+3",		110,	"안티-썬 폴" },
	{ Item::ITEM_CLASS_VAMPIRE_COAT,		7,		4,		"DUR+5",		110,	"레버테이트 클록" },
	{ Item::ITEM_CLASS_VAMPIRE_COAT,		9,		4,		"VIS+3",		110,	"안티-썬 코프" },
	{ Item::ITEM_CLASS_VAMPIRE_NECKLACE,	3,		4,		"TOHIT+5",		110,	"젯 네크리스" },
	{ Item::ITEM_CLASS_VAMPIRE_BRACELET,	2,		4,		"DEF+5",		110,	"쥬얼 브레이슬릿" },
	{ Item::ITEM_CLASS_VAMPIRE_RING,		3,		4,		"CURES+3",		110,	"길트 링" },
	{ Item::ITEM_CLASS_VAMPIRE_EARRING,		3,		4,		"HP+5",			110,	"골드 이어링" },
	{ Item::ITEM_CLASS_VAMPIRE_AMULET,		2,		4,		"PORES+3",		110,	"제라" },
	{ Item::ITEM_CLASS_VAMPIRE_WEAPON,		3,		4,		"RES+5",		110,	"제미널링 너클" },
	{ Item::ITEM_CLASS_VAMPIRE_WEAPON,		4,		4,		"ATTR+3",		110,	"예티 크로우" },
	{ Item::ITEM_CLASS_VAMPIRE_WEAPON,		5,		4,		"INT+5",		110,	"캣츠 크로우" },
	{ Item::ITEM_CLASS_VAMPIRE_WEAPON,		6,		4,		"DAM+4",		110,	"피스트 너클" },
	{ Item::ITEM_CLASS_PERSONA,				0,		4,		"",				20,		"페르소나 1단" },
	{ Item::ITEM_CLASS_RESURRECT_ITEM,		0,		0,		"",				200,	"부활 스크롤" },
	{ Item::ITEM_CLASS_RESURRECT_ITEM,		1,		0,		"",				100,	"엘릭서 스크롤" },
	{ Item::ITEM_CLASS_EVENT_ETC,			13,		0,		"",				3000,	"스톰 폭죽" },
	{ Item::ITEM_CLASS_EVENT_ETC,			3,		0,		"",				4750,	"드래곤 폭죽" },
	{ Item::ITEM_CLASS_EVENT_TREE,			27,		0,		"",				500,	"12시간 알림판" }
};

const int EVENT_ITEM_200505_OUSTERS_MAX = 19;
const EVENT_ITEM_TEMPLATE Event200505OustersTemplate[EVENT_ITEM_200505_OUSTERS_MAX] =
{
	{ Item::ITEM_CLASS_OUSTERS_COAT,		4,		4,		"DUR+5",		110,	"레프리컨 코트" },
	{ Item::ITEM_CLASS_OUSTERS_BOOTS,		4,		4,		"ASPD+5",		110,	"레프리컨 부츠" },
	{ Item::ITEM_CLASS_OUSTERS_BOOTS,		4,		4,		"VIS+3",		110,	"레프리컨 부츠" },
	{ Item::ITEM_CLASS_OUSTERS_ARMSBAND,	4,		4,		"CURES+3",		110,	"블라즘 암스밴드" },
	{ Item::ITEM_CLASS_OUSTERS_CIRCLET,		3,		4,		"HP+5",			110,	"실바나 서클릿" },
	{ Item::ITEM_CLASS_OUSTERS_PENDENT,		3,		4,		"TOHIT+4",		110,	"이져실 펜던트" },
	{ Item::ITEM_CLASS_OUSTERS_RING,		3,		4,		"CURES+2",		110,	"위스퍼 오브 엘프 링" },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		10,		4,		"VIS+3",		110,	"대지의 정령석1" },
	{ Item::ITEM_CLASS_OUSTERS_STONE,		6,		4,		"MP+5",			110,	"물의 정령석2" },
	{ Item::ITEM_CLASS_OUSTERS_WRISTLET,	4,		4,		"ASPD+5",		110,	"불의 닉스플로즈 리스틀릿" },
	{ Item::ITEM_CLASS_OUSTERS_WRISTLET,	15,		4,		"HP+5",			110,	"물의 라크리마 리스틀릿" },
	{ Item::ITEM_CLASS_OUSTERS_CHAKRAM,		3,		4,		"DAM+5",		110,	"뉴보 챠크람" },
	{ Item::ITEM_CLASS_OUSTERS_CHAKRAM,		4,		4,		"ACRES+3",		110,	"아니마 챠크람" },
	{ Item::ITEM_CLASS_FASCIA,				0,		4,		"",				20,		"페이샤 1단" },
	{ Item::ITEM_CLASS_RESURRECT_ITEM,		0,		0,		"",				200,	"부활 스크롤" },
	{ Item::ITEM_CLASS_RESURRECT_ITEM,		1,		0,		"",				100,	"엘릭서 스크롤" },
	{ Item::ITEM_CLASS_EVENT_ETC,			13,		0,		"",				3000,	"스톰 폭죽" },
	{ Item::ITEM_CLASS_EVENT_ETC,			3,		0,		"",				4750,	"드래곤 폭죽" },
	{ Item::ITEM_CLASS_EVENT_TREE,			27,		0,		"",				500,	"12시간 알림판" }
};

////////////////////////////////////////////////////////////////////////////////
// ActionGiveCommonEventItem
////////////////////////////////////////////////////////////////////////////////
ActionGiveCommonEventItem::ActionGiveCommonEventItem()
{
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ActionGiveCommonEventItem::~ActionGiveCommonEventItem()
{
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveCommonEventItem::read(PropertyBuffer & propertyBuffer)
    throw(Error)
{
    __BEGIN_TRY

	try
	{
		// read script id
		m_Type = propertyBuffer.getProperty("Type");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveCommonEventItem::execute(Creature * pCreature1 , Creature * pCreature2) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	Inventory* pInventory = pPC->getInventory();
	Assert (pInventory != NULL);

	Zone* pZone = pPC->getZone();
	Assert (pZone != NULL);

	// 이벤트 기간이 아닌 경우
	if (g_pVariableManager->getVariable(FAMILY_COIN_EVENT ) == 0 )
	{
		GCNPCResponse response;
		response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&response);

		return;
	}

	// 인벤토리 공간 체크
	_TPOINT pt;
	if (!pInventory->getEmptySlot(2, 3, pt ) )
	{
		GCNPCResponse response;
		response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&response);

		return;
	}


	// 패밀리 코인 체크
	if (!pInventory->hasEnoughNumItem(Item::ITEM_CLASS_EVENT_ETC, 18, 9 ) )
	{
		GCNPCResponse response;
		response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&response);

		return;
	}

	// 아이템 랜덤 생석
	int ratio = rand() % 10000 + 1;

	Item::ItemClass itemClass;
	ItemType_t itemType;
	Grade_t itemGrade;
	string itemOption;

	int sum = 0;
	bool bFind = false;
	
	int itemIndex = 0;
	if (pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert(pSlayer != NULL);

		for (int i = 0; i < EVENT_ITEM_200505_SLAYER_MAX; ++i )
		{
			sum += Event200505SlayerTemplate[i].Ratio;
			if (sum >= ratio )
			{
				bFind = true;
				itemIndex = i;

				itemClass = Event200505SlayerTemplate[i].ItemClass;
				itemType = Event200505SlayerTemplate[i].ItemType;
				itemGrade = Event200505SlayerTemplate[i].ItemGrade;
				itemOption = Event200505SlayerTemplate[i].ItemOption;

				break;
			}
		}
	}
	else if (pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert(pVampire != NULL);

		for (int i = 0; i < EVENT_ITEM_200505_VAMPIRE_MAX; ++i )
		{
			sum += Event200505VampireTemplate[i].Ratio;
			if (sum >= ratio )
			{
				bFind = true;
				itemIndex = i;

				itemClass = Event200505VampireTemplate[i].ItemClass;
				itemType = Event200505VampireTemplate[i].ItemType;
				itemGrade = Event200505VampireTemplate[i].ItemGrade;
				itemOption = Event200505VampireTemplate[i].ItemOption;

				break;
			}
		}
	}
	else if (pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert(pOusters != NULL);

		for (int i = 0; i < EVENT_ITEM_200505_OUSTERS_MAX; ++i )
		{
			sum += Event200505OustersTemplate[i].Ratio;
			if (sum >= ratio )
			{
				bFind = true;
				itemIndex = i;

				itemClass = Event200505OustersTemplate[i].ItemClass;
				itemType = Event200505OustersTemplate[i].ItemType;
				itemGrade = Event200505OustersTemplate[i].ItemGrade;
				itemOption = Event200505OustersTemplate[i].ItemOption;

				break;
			}
		}
	}

	if (bFind )
	{
		// 아이템 생성 및 추가
		list<OptionType_t> options;

		// 아이템 옵션 체크
		if (itemOption != "" )
		{
			options.push_back(g_pOptionInfoManager->getOptionType(itemOption ));
		}

		Item* pItem = g_pItemFactoryManager->createItem(itemClass, itemType, options);
		Assert(pItem != NULL);

		// 아이템 급수 체크
		if (itemGrade != 0 )
		{
			pItem->setGrade(itemGrade);
		}

		pZone->registerObject(pItem);

		if (pInventory->addItem(pItem, pt ) )
		{
			// 패밀리 코인을 없앤다.
			pInventory->decreaseNumItem(Item::ITEM_CLASS_EVENT_ETC, 18, 9, pPlayer);

			// DB 에 아이템 생성
			pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

			// itemTraceLog 를 남긴다.
			remainTraceLog(pItem, "Event200505", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);

			// 결과를 클라이언트에 알리기
			GCCreateItem gcCreateItem;
			gcCreateItem.setObjectID(pItem->getObjectID());
			gcCreateItem.setItemClass(pItem->getItemClass());
			gcCreateItem.setItemType(pItem->getItemType());
			gcCreateItem.setGrade(pItem->getGrade());
			gcCreateItem.setOptionType(pItem->getOptionTypeList());
			gcCreateItem.setDurability(pItem->getDurability());
			gcCreateItem.setItemNum(pItem->getNum());
			gcCreateItem.setInvenX(pt.x);
			gcCreateItem.setInvenY(pt.y);

			pPlayer->sendPacket(&gcCreateItem);
		}

		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("UPDATE EventItemCount2 SET Count = Count + 1 WHERE Race = %d AND ItemIndex = %d",
									pPC->getRace(), itemIndex);
		}
		END_DB(pStmt )
	}

	// 대화창 닫기
	GCNPCResponse response;
	response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	pPlayer->sendPacket(&response);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveCommonEventItem::toString () const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveCommonEventItem("
		<< "Type:" << m_Type
	    << ")";
	return msg.toString();

	__END_CATCH
}

