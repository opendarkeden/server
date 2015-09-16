//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemUtil.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEMUTIL_H__
#define __ITEMUTIL_H__

#include "Item.h"
#include <list>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;
class Inventory;
class PlayerCreature;
class Slayer;
class Ousters;
class Corpse;

struct ITEM_TEMPLATE;

enum ItemTraceLogType
{
	ITEM_LOG_CREATE = 0,		// 아이템 생성에 대한 로그
	ITEM_LOG_TRADE,				// 아이템 TRADE 에 대한 로그
	ITEM_LOG_MOVE,				// 아이템 이동에 대한 로그
	ITEM_LOG_DELETE,			// 아이템 삭제에 대한 로그
             
	ITEM_LOG_MAX
};

enum ItemTraceDetailType
{
	DETAIL_COMMAND = 0,		// command 명령어로 생성						: ITEM_LOG_CREATE
	DETAIL_SHOPBUY,			// 상점에서 산 경우								: ITEM_LOG_CREATE
	DETAIL_PICKUP,			// 바닥에서 물건 주웠을 경우					: ITEM_LOG_MOVE
	DETAIL_DROP,			// 바닥에 버린 경우								: ITEM_LOG_MOVE
	DETAIL_EVENTNPC,		// 이벤트로 생긴 아이템							: ITEM_LOG_CREATE
	DETAIL_SHOPSELL,		// 상점에 물건 판 경우							: ITEM_LOG_DELETE
	DETAIL_TIMEOUT,			// 바닥에 떨어진 후 timeout 으로 사라진 경우	: ITEM_LOG_DELETE
	DETAIL_ENCHANT,			// 인첸트로 변경된 경우							: ITEM_LOG_DELETE
	DETAIL_OPCLEAR,			// commnad 로 삭제								: ITEM_LOG_DELETE
	DETAIL_TRADE,			// 아이템 TRADE									: ITEM_LOG_TRADE
	DETAIL_MALLBUY,			// 웹에서 산 아이템								: ITEM_LOG_CREATE

	DETAIL_MAX				
};

enum ITLType
{
	ITL_GET = 0,			// 아이템 GET
	ITL_DROP,				// 아이템 DROP
	ITL_ETC,				// 아이템 ETC
             
	ITL_MAX	
};

enum ITLDType
{
	ITLD_PICKUP = 0, 		// 아이템 PICKUP		GET
	ITLD_TRADE,				// 아이템 TRADE			GET/DROP
	ITLD_EVENTNPC,			// 이벤트를 clear하고 NPC에게 받는 아이템 		GET
	ITLD_PETITEM,			// GET
	ITLD_ENCHANT,			// GET/DROP
	ITLD_MIXING,			// GET/DROP
	ITLD_OPTION,			// GET/DROP/ETC

	ITLD_NPCSHOP,			// NPC샵에서 거래	GET/DROP
	ITLD_WEBSHOP,			// 웹마켓에서의 거래 GET
	ITLD_PRIVATESHOP,		// 개인상점에서 GET/DROP

	ITLD_GM,				// 게임마스터의 ACTION GET/DROP/MOVE/ETC
	ITLD_TIMEOUT,			// Time아웃	DROP
	ITLD_DELETE,			// Delete		// ETC+DELETE 의 경우는 없을테다.
	ITLD_MOVE,				// Mode 		GET/DROP/ETC

	ITLD_MAX
};

const string ItemTraceLogType2String[] =
{
	"CREATE",       // 0
	"TRADE",        // 1
	"MOVE",         // 2
	"DELETE",       // 3
};

const string ItemTraceLogDetailType2String[] =
{
	"COMMAND",      // 0
	"SHOPBUY",      // 1
	"PICKUP",       // 2
	"DROP",         // 3
	"EVENTNPC",     // 4
	"SHOPSELL",     // 5
	"TIMEOUT",      // 6
	"ENCHANT",      // 7
	"OPCLEAR",      // 8
	"TRADE",        // 9
	"MALLBUY",      // 10
};

const string ITLType2String[] =
{
	"GET",       // 0
	"DROP",        // 1
	"MOVE",         // 2
	"ETC",       // 3
};

const string ITLDType2String[] =
{
	"PICKUP",     // 0
	"TRADE",      // 1
	"EVENTNPC",   // 2
	"PETITEM",    // 3
	"ENCHANT",    // 4
	"MIXING",     // 5
	"OPTION",     // 6

	"NPCSHOP",    // 7
	"WEBSHOP",    // 8
	"PRIVATESHOP",// 9

	"GM",  		  // 10
	"TIMEOUT",	  // 11
	"DELETE",	  // 12
	"MOVE"        // 13
};

//////////////////////////////////////////////////////////////////////////////
// 쌓일 수 있는 아이템인가? 
//////////////////////////////////////////////////////////////////////////////
bool isStackable(Item::ItemClass IClass);
bool isStackable(const Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// 같은 클래스, 타입의 아이템인가?
//////////////////////////////////////////////////////////////////////////////
bool isSameItem(Item::ItemClass IClass1, Item::ItemClass IClass2, ItemType_t type1, ItemType_t type2);
bool isSameItem(const Item* pItem1, const Item* pItem2);

//////////////////////////////////////////////////////////////////////////////
// 두 아이템을 쌓을 수 있는가?
//////////////////////////////////////////////////////////////////////////////
bool canStack(const Item* pItem1, const Item* pItem2);

//////////////////////////////////////////////////////////////////////////////
// 두 손 무기인가?
// 접근전 무기인가?
// 전사,군인, 성직자 무기인가?
//////////////////////////////////////////////////////////////////////////////
bool isTwohandWeapon(const Item* pItem);
bool isMeleeWeapon(const Item* pItem);
bool isFighterWeapon(const Item* pItem);
bool isArmsWeapon(const Item* pItem);
bool isClericWeapon(const Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// 총에 맞는 탄창인가?
//////////////////////////////////////////////////////////////////////////////
bool isSuitableMagazine(const Item* pGun, const Item* pMagazine, bool hasVivid);

//////////////////////////////////////////////////////////////////////////////
// 슬레이어용 무기인가?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerWeapon(Item::ItemClass IClass);
bool isAdvancedSlayerWeapon(Item::ItemClass IClass);
bool isVampireWeapon(Item::ItemClass IClass);
bool isOustersWeapon(Item::ItemClass IClass);

//////////////////////////////////////////////////////////////////////////////
// 슬레이어용 방어구인가?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerArmor(Item::ItemClass IClass);
bool isVampireArmor(Item::ItemClass IClass);
bool isOustersArmor(Item::ItemClass IClass);

//////////////////////////////////////////////////////////////////////////////
// 슬레이어용 악세사리인가?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerAccessory(Item::ItemClass IClass);
bool isVampireAccessory(Item::ItemClass IClass);
bool isOustersAccessory(Item::ItemClass IClass);

//////////////////////////////////////////////////////////////////////////////
// 수리할 수 있는 아이템인가?
//////////////////////////////////////////////////////////////////////////////
bool isRepairableItem(const Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// 아이템을 수리한다.
//////////////////////////////////////////////////////////////////////////////
void repairItem(Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// 아이템의 최대 내구도를 얻어낸다.
//////////////////////////////////////////////////////////////////////////////
Durability_t computeMaxDurability(Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// 탄창을 갈아끼워준다.
//////////////////////////////////////////////////////////////////////////////
Bullet_t reloadArmsItem(Item* pWeapon, Item* pMagazine);

//////////////////////////////////////////////////////////////////////////////
// 총알을 빼준다.
//////////////////////////////////////////////////////////////////////////////
Bullet_t decreaseBullet(Item* pWeapon) throw();

//////////////////////////////////////////////////////////////////////////////
// 남은 총알의 갯수를 리턴
//////////////////////////////////////////////////////////////////////////////
Bullet_t getRemainBullet(Item* pWeapon) throw();

//////////////////////////////////////////////////////////////////////////////
// 주을 수 있는 아이템인가?
//////////////////////////////////////////////////////////////////////////////
bool isPortableItem(Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// 사용할 수 있는 아이템인가?
// 여기서의 사용이란, 사용해서 사라지는 소모성 아이템을 말한다.
//////////////////////////////////////////////////////////////////////////////
bool isUsableItem(Item* pItem, Creature* pUser);

//////////////////////////////////////////////////////////////////////////////
// 아이템의 숫자를 줄인다.
//////////////////////////////////////////////////////////////////////////////
ItemNum_t decreaseItemNum(Item* pItem, Inventory* pInventory, 
	const string& OwnerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);

//////////////////////////////////////////////////////////////////////////////
// 아이템이 겹치는 버그를 로그하는 함수다.
//////////////////////////////////////////////////////////////////////////////
void processItemBug(Creature* pCreature, Item* pItem);
void processItemBugEx(Creature* pCreature, Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// Mysterious item 생성
//////////////////////////////////////////////////////////////////////////////
Item* getRandomMysteriousItem(Creature* pCreature, Item::ItemClass itemClass, int maxLevel=0)
	    throw(Error);

//////////////////////////////////////////////////////////////////////////////
// Option에 관련된 ㅎ마수들
//////////////////////////////////////////////////////////////////////////////
// 특정한 OptionType이 붙어있는가?
bool hasOptionType(const list<OptionType_t>& optionTypes, OptionType_t optionType);

// 특정한 OptionClass(STR, DEX...)가 붙어있는가?
bool hasOptionClass(const list<OptionType_t>& optionTypes, OptionType_t optionType);

// DB에서 읽어올때
void setOptionTypeFromField(list<OptionType_t>& optionTypes, const string& optionField);

// DB에 저장할 때
void setOptionTypeToField(const list<OptionType_t>& optionTypes, string& optionField);

// cout에 사용
string getOptionTypeToString(const list<OptionType_t>& optionTypes);

//////////////////////////////////////////////////////////////////////////////
// 다음 옵션이 붙을 확률 체크 : 레어 아이템 생성 여부
//////////////////////////////////////////////////////////////////////////////
bool isPossibleNextOption(ITEM_TEMPLATE* pTemplate);

ItemType_t getUpgradeItemType(Item::ItemClass IClass, ItemType_t itemType, ItemType_t upgradeCount);
ItemType_t getDowngradeItemType(Item::ItemClass IClass, ItemType_t itemType);
bool isPossibleUpgradeItemType(Item::ItemClass IClass);

//////////////////////////////////////////////////////////////////////////////
// 크리스마스 트리 이벤트용
//////////////////////////////////////////////////////////////////////////////
// 트리 조각을 검색
//TPOINT checkEventTree(PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY);
//TPOINT checkEventDocument(PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY);
//TPOINT checkEventDoll(PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY);
TPOINT checkEventPuzzle(PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY, int start);

// 인벤토리의 (X0, Y0) - (X1, y1) 범위의 아이템을 지운다.
void deleteInventoryItem(Inventory* pInventory, CoordInven_t invenX0, CoordInven_t invenY0, CoordInven_t invenX1, CoordInven_t invenY1);

// 인벤토리에 초보자용 아이템을 넣어준다.
bool addNewbieItemToInventory(Slayer* pSlayer, bool sendPacket = false ) throw(Error);
bool addNewbieGoldToInventory(Slayer* pSlayer, bool sendPacket = false ) throw(Error);
bool addNewbieItemToGear(Slayer* pSlayer, bool sendPacket = false ) throw(Error);

bool addNewbieItemToInventory(Ousters* pOusters, bool sendPacket = false ) throw(Error);
bool addNewbieGoldToInventory(Ousters* pOusters, bool sendPacket = false ) throw(Error);
bool addNewbieItemToGear(Ousters* pOusters, bool sendPacket = false ) throw(Error);

Item::ItemClass getBestNewbieWeaponClass(Slayer* pSlayer) throw(Error);

// 옵션 string으로부터 옵션 list를 만든다.
void makeOptionList(const string& options, list<OptionType_t>& optionList) throw(Error);

void saveDissectionItem(Creature* pCreature, Item* pTreasure, int x, int y) throw(Error);

bool canDecreaseDurability(Item* pItem ) throw(Error);

bool canSell(Item* pItem);
bool canPutInStash(Item* pItem);
bool canTrade(Item* pItem);
bool canTradeInventoryItem(Item* pItem);
bool isCoupleRing(Item* pItem);

bool suitableItemClass(Item::ItemClass iClass, SkillDomainType_t domainType);

// 아이템을 성별에 맞는 동급의 아이템으로 바꿔준다. 아이템 타입이 남자용 다음에 바로 같은 급의 여자용이 온다고 가정
// 이걸 불러준 뒤엔 반드시 아이템 타입을 세이브해주던가 pItem->save() 를 불러줘야 된다.
void setItemGender(Item* pItem, GenderRestriction gender);

// Item Trace Log 를 남길 아이템인가?
bool bTraceLog(Item* pItem);

// Item Trace Log 남기는 함수 
void remainTraceLog (Item* pItem, const string& preOwner, const string& owner, ItemTraceLogType logType, ItemTraceDetailType detailType ) throw(Error);
void remainTraceLogNew (Item* pItem, const string& owner, ITLType logType, ITLDType detailType, ZoneID_t zid=0, int x=0, int y=0 ) throw(Error);

// Meney Trace Log 남기는 함수
void remainMoneyTraceLog (const string& preOwner, const string& owner, ItemTraceLogType logType, ItemTraceDetailType detailType, int amount ) throw(Error);

// Web 에서 산 아이템을 만드는 함수
Item* createItemByGoodsID(DWORD goodsID);

// 복권당첨에 관련 된 함수 (특별히 둘 곳이 없어서 여기 둔다 --;) 2003.04.29 by DEW
bool bWinPrize(DWORD rewardID, DWORD questLevel);

void deleteFlagEffect(Corpse* pFlagPole, Item* pFlag);

Item* fitToPC(Item* pItem, PlayerCreature* pPC);

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)

ItemType_t getItemTypeByItemLimit(Item::ItemClass itemClass, ItemType_t itemType);

#endif	// __THAILAND_SERVER__

void increaseEventItemCount(Item* pItem, int num = 1);

#endif
