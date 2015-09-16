//////////////////////////////////////////////////////////////////////////////
// Filename    : Item.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_H__
#define __ITEM_H__

#include "Object.h"
#include "Effect.h"
#include "EffectManager.h"
#include <bitset>
#include <vector>
#include <algorithm>
#include <list>

//////////////////////////////////////////////////////////////////////////////
// ItemClass String
//////////////////////////////////////////////////////////////////////////////

const string ItemClass2String[] = 
{
	"ITEM_CLASS_MOTORCYCLE",           // 0
	"ITEM_CLASS_POTION",               // 1
	"ITEM_CLASS_WATER",                // 2
	"ITEM_CLASS_HOLYWATER",            // 3
	"ITEM_CLASS_MAGAZINE",             // 4
	"ITEM_CLASS_BOMB_MATERIAL",        // 5
	"ITEM_CLASS_ETC",                  // 6
	"ITEM_CLASS_KEY",                  // 7
	"ITEM_CLASS_RING",                 // 8
	"ITEM_CLASS_BRACELET",             // 9
	"ITEM_CLASS_NECKLACE",             // 10
	"ITEM_CLASS_COAT",                 // 11
	"ITEM_CLASS_TROUSER",              // 12
	"ITEM_CLASS_SHOES",                // 13
	"ITEM_CLASS_SWORD",                // 14
	"ITEM_CLASS_BLADE",                // 15
	"ITEM_CLASS_SHIELD",               // 16
	"ITEM_CLASS_CROSS",                // 17
	"ITEM_CLASS_GLOVE",                // 18
	"ITEM_CLASS_HELM",                 // 19
	"ITEM_CLASS_SG",                   // 20
	"ITEM_CLASS_SMG",                  // 21
	"ITEM_CLASS_AR",                   // 22
	"ITEM_CLASS_SR",                   // 23
	"ITEM_CLASS_BOMB",                 // 24
	"ITEM_CLASS_MINE",                 // 25
	"ITEM_CLASS_BELT",                 // 26
	"ITEM_CLASS_LEARNINGITEM",         // 27
	"ITEM_CLASS_MONEY",                // 28
	"ITEM_CLASS_CORPSE",               // 29
	"ITEM_CLASS_VAMPIRE_RING",         // 30
	"ITEM_CLASS_VAMPIRE_BRACELET",     // 31
	"ITEM_CLASS_VAMPIRE_NECKLACE",     // 32
	"ITEM_CLASS_VAMPIRE_COAT",         // 33
	"ITEM_CLASS_SKULL",                // 34
	"ITEM_CLASS_MACE",                 // 35
	"ITEM_CLASS_SERUM",                // 36
	"ITEM_CLASS_VAMPIRE_ETC",          // 37
	"ITEM_CLASS_SLAYER_PORTAL_ITEM",   // 38
	"ITEM_CLASS_VAMPIRE_PORTAL_ITEM",  // 39
	"ITEM_CLASS_EVENT_GIFT_BOX",       // 40
	"ITEM_CLASS_EVENT_STAR",           // 41
	"ITEM_CLASS_VAMPIRE_EARRING",      // 42
	"ITEM_CLASS_RELIC",                // 43
	"ITEM_CLASS_VAMPIRE_WEAPON",       // 44
	"ITEM_CLASS_VAMPIRE_AMULET",       // 45
	"ITEM_CLASS_QUEST_ITEM",           // 46
	"ITEM_CLASS_EVENT_TREE",           // 47
	"ITEM_CLASS_EVENT_ETC",            // 48
	"ITEM_CLASS_BLOOD_BIBLE",		   // 49
	"ITEM_CLASS_CASTLE_SYMBOL",		   // 50
	"ITEM_CLASS_COUPLE_RING",		   // 51
	"ITEM_CLASS_VAMPIRE_COUPLE_RING",  // 52
	"ITEM_CLASS_EVENT_ITEM",  		   // 53
	"ITEM_CLASS_DYE_POTION",  		   // 54
	"ITEM_CLASS_RESURRECT_ITEM",	   // 55
	"ITEM_CLASS_MIXING_ITEM",	   	   // 56
	"ITEM_CLASS_OUSTERS_ARMSBAND",	   // 57
	"ITEM_CLASS_OUSTERS_BOOTS",	   	   // 58
	"ITEM_CLASS_OUSTERS_CHAKRAM",	   // 59
	"ITEM_CLASS_OUSTERS_CIRCLET",  	   // 60
	"ITEM_CLASS_OUSTERS_COAT",	   	   // 61
	"ITEM_CLASS_OUSTERS_PENDENT",  	   // 62
	"ITEM_CLASS_OUSTERS_RING",	   	   // 63
	"ITEM_CLASS_OUSTERS_STONE",	   	   // 64
	"ITEM_CLASS_OUSTERS_WRISTLET", 	   // 65
	"ITEM_CLASS_LARVA", 			   // 66
	"ITEM_CLASS_PUPA", 			 	   // 67
	"ITEM_CLASS_COMPOS_MEI",	 	   // 68
	"ITEM_CLASS_OUSTERS_SUMMON_ITEM",  // 69
	"ITEM_CLASS_EFFECT_ITEM",  		   // 70
	"ITEM_CLASS_CODE_SHEET",  		   // 71
	"ITEM_CLASS_MOON_CARD",			   // 72
	"ITEM_CLASS_SWEEPER",			   // 73
	"ITEM_CLASS_PET_ITEM",			   // 74
	"ITEM_CLASS_PET_FOOD",			   // 75
	"ITEM_CLASS_PET_ENCHANT_ITEM",	   // 76
	"ITEM_CLASS_LUCKY_BAG",            // 77
	"ITEM_CLASS_SMS_ITEM",             // 78
	"ITEM_CLASS_CORE_ZAP",				// 79
	"ITEM_CLASS_GQUEST_ITEM",			// 80
	"ITEM_CLASS_TRAP_ITEM",				// 81
	"ITEM_CLASS_BLOOD_BIBLE_SIGN",		// 82
	"ITEM_CLASS_WAR_ITEM",				// 83
	"ITEM_CLASS_CARRYING_RECEIVER",		// 84
	"ITEM_CLASS_SHOULDER_ARMOR",		// 85
	"ITEM_CLASS_DERMIS",				// 86
	"ITEM_CLASS_PERSONA",				// 87
	"ITEM_CLASS_FASCIA",				// 88
	"ITEM_CLASS_MITTEN",				// 89
	"ITEM_CLASS_SUB_INVENTORY",			// 90
};

const string ItemClass2ShortString[] = 
{
	"MOTORCYCLE",           // 0
	"POTION",               // 1
	"WATER",                // 2
	"HOLYWATER",            // 3
	"MAGAZINE",             // 4
	"BOMB_MATERIAL",        // 5
	"ETC",                  // 6
	"KEY",                  // 7
	"RING",                 // 8
	"BRACELET",             // 9
	"NECKLACE",             // 10
	"COAT",                 // 11
	"TROUSER",              // 12
	"SHOES",                // 13
	"SWORD",                // 14
	"BLADE",                // 15
	"SHIELD",               // 16
	"CROSS",                // 17
	"GLOVE",                // 18
	"HELM",                 // 19
	"SG",                   // 20
	"SMG",                  // 21
	"AR",                   // 22
	"SR",                   // 23
	"BOMB",                 // 24
	"MINE",                 // 25
	"BELT",                 // 26
	"LEARNINGITEM",         // 27
	"MONEY",                // 28
	"CORPSE",               // 29
	"VAMPIRE_RING",         // 30
	"VAMPIRE_BRACELET",     // 31
	"VAMPIRE_NECKLACE",     // 32
	"VAMPIRE_COAT",         // 33
	"SKULL",                // 34
	"MACE",                 // 35
	"SERUM",                // 36
	"VAMPIRE_ETC",          // 37
	"SLAYER_PORTAL_ITEM",   // 38
	"VAMPIRE_PORTAL_ITEM",  // 39
	"EVENT_GIFT_BOX",       // 40
	"EVENT_STAR",           // 41
	"VAMPIRE_EARRING",      // 42
	"RELIC",                // 43 
	"VAMPIRE_WEAPON",       // 44
	"VAMPIRE_AMULET",       // 45
	"QUEST_ITEM",       	// 46
	"EVENT_TREE",           // 47
	"EVENT_ETC",            // 48
	"BLOOD_BIBLE",		   	// 49
	"CASTLE_SYMBOL",		// 50
	"COUPLE_RING",			// 51
	"VAMPIRE_COUPLE_RING",	// 52
	"EVENT_ITEM",			// 53
	"DYE_POTION",			// 54
	"RESURRECT_ITEM",		// 55
	"MIXING_ITEM",	   	  	// 56
	"OUSTERS_ARMSBAND",		// 57
	"OUSTERS_BOOTS",		// 58
	"OUSTERS_CHAKRAM",		// 59
	"OUSTERS_CIRCLET",		// 60
	"OUSTERS_COAT",			// 61
	"OUSTERS_PENDENT",		// 62
	"OUSTERS_RING",			// 63
	"OUSTERS_STONE",		// 64
	"OUSTERS_WRISTLET",		// 65
	"LARVA", 			    // 66
	"PUPA", 			    // 67
	"COMPOS_MEI",	 	    // 68
	"OUSTERS_SUMMON_ITEM",  // 69
	"EFFECT_ITEM",  		// 70
	"CODE_SHEET",			// 71
	"MOON_CARD",			// 72
	"SWEEPER",			    // 73
	"PET_ITEM",			    // 74
	"PET_FOOD",			    // 75
	"PET_ENCHANT_ITEM",		// 76
	"LUCKY_BAG",            // 77
	"SMS_ITEM",             // 78
	"CORE_ZAP",				// 79
	"GQUEST_ITEM",			// 80
	"TRAP_ITEM",			// 81
	"BLOOD_BIBLE_SIGN",		// 82
	"WAR_ITEM",				// 83
	"CARRYING_RECEIVER",		// 84
	"SHOULDER_ARMOR",		// 85
	"DERMIS",				// 86
	"PERSONA",				// 87
	"FASCIA",				// 88
	"MITTEN",				// 89
	"SUB_INVENTORY",		// 90
};

const string ItemObjectTableName[] = 
{
	"MotorcycleObject",				  // 0
	"PotionObject",					  // 1
	"WaterObject",					  // 2
	"HolyWaterObject",				  // 3
	"MagazineObject",				  // 4
	"BombMaterialObject",			  // 5
	"ETCObject",					  // 6
	"KeyObject",					  // 7
	"RingObject",					  // 8
	"BraceletObject",				  // 9
	"NecklaceObject",				  // 10
	"CoatObject",					  // 11
	"TrouserObject",				  // 12
	"ShoesObject",					  // 13
	"SwordObject",					  // 14
	"BladeObject",					  // 15
	"ShieldObject",					  // 16
	"CrossObject",					  // 17
	"GloveObject",					  // 18
	"HelmObject",					  // 19
	"SGObject",						  // 20
	"SMGObject",					  // 21
	"ARObject",						  // 22
	"SRObject",						  // 23
	"BombObject",					  // 24
	"MineObject",					  // 25
	"BeltObject",					  // 26
	"LearningItemObject",			  // 27
	"MoneyObject",					  // 28
	"",							      // 29 Corpse
	"VampireRingObject",			  // 30
	"VampireBraceletObject",		  // 31
	"VampireNecklaceObject",		  // 32
	"VampireCoatObject",			  // 33
	"SkullObject",					  // 34
	"MaceObject",					  // 35
	"SerumObject",					  // 36
	"VampireETCObject",				  // 37
	"SlayerPortalItemObject",		  // 38
	"VampirePortalItemObject",		  // 39
	"EventGiftBoxObject",			  // 40
	"EventStarObject",				  // 41
	"VampireEarringObject",			  // 42
	"RelicObject",					  // 43 
	"VampireWeaponObject",			  // 44
	"VampireAmuletObject",			  // 45
	"QuestItemObject",				  // 46
	"EventTreeObject",				  // 47
	"EventETCObject",				  // 48
	"BloodBibleObject",				  // 49
	"CastleSymbolObject",			  // 50
	"CoupleRingObject",				  // 51
	"VampireCoupleRingObject",		  // 52
	"EventItemObject",		  		  // 53
	"DyePotionObject",		  		  // 54
	"ResurrectItemObject",			  // 55
	"MixingItemObject",				  // 56
	"OustersArmsbandObject",	  	  // 57
	"OustersBootsObject",			  // 58
	"OustersChakramObject",			  // 59
	"OustersCircletObject",			  // 60
	"OustersCoatObject",			  // 61
	"OustersPendentObject",			  // 62
	"OustersRingObject",			  // 63
	"OustersStoneObject",			  // 64
	"OustersWristletObject",		  // 65
	"LarvaObject",		  			  // 66
	"PupaObject",		  			  // 67
	"ComposMeiObject",				  // 68
	"OustersSummonItemObject",		  // 69
	"EffectItemObject",				  // 70
	"CodeSheetObject",				  // 71
	"MoonCardObject",				  // 72
	"SweeperObject",				  // 73
	"PetItemObject",				  // 74
	"PetFoodObject",				  // 75
	"PetEnchantItemObject",			  // 76
	"LuckyBagObject",	              // 77
	"SMSItemObject",	              // 78
	"CoreZapObject",	              // 79
	"GQuestItemObject",               // 80
	"TrapItemObject",				  // 81
	"",							   	  // 82
	"WarItemObject",			   	  // 83
	"CarryingReceiverObject",		// 84
	"ShoulderArmorObject",		// 85
	"DermisObject",				// 86
	"PersonaObject",				// 87
	"FasciaObject",				// 88
	"MittenObject",				// 89
	"SubInventoryObject",		// 90
};



const int ItemMaxStack[] = 
{
	 1, //MOTORCYCLE           // 0
	30, //POTION               // 1
	50, //WATER                // 2
	50, //HOLYWATER            // 3
//#else
//	 9, //POTION               // 1
//	20, //WATER                // 2
//	20, //HOLYWATER            // 3
//#endif
	20, //MAGAZINE             // 4
	20, //BOMB_MATERIAL        // 5
	 9, //ETC                  // 6
	 1, //KEY                  // 7
	 1, //RING                 // 8
	 1, //BRACELET             // 9
	 1, //NECKLACE             // 10
	 1, //COAT                 // 11
	 1, //TROUSER              // 12
	 1, //SHOES                // 13
	 1, //SWORD                // 14
	 1, //BLADE                // 15
	 1, //SHIELD               // 16
	 1, //CROSS                // 17
	 1, //GLOVE                // 18
	 1, //HELM                 // 19
	 1, //SG                   // 20
	 1, //SMG                  // 21
	 1, //AR                   // 22
	 1, //SR                   // 23
	20, //BOMB                 // 24
	20, //MINE                 // 25
	 1, //BELT                 // 26
	 1, //LEARNINGITEM         // 27
	 1, //MONEY                // 28
	 1, //CORPSE               // 29
	 1, //VAMPIRE_RING         // 30
	 1, //VAMPIRE_BRACELET     // 31
	 1, //VAMPIRE_NECKLACE     // 32
	 1, //VAMPIRE_COAT         // 33
	 9, //SKULL                // 34
	 1, //MACE                 // 35
	 30, //SERUM                // 36
	 20, //VAMPIRE_ETC          // 37
//#else
//	 9, //SERUM                // 36
//	 9, //VAMPIRE_ETC          // 37
//#endif
	 1, //SLAYER_PORTAL_ITEM   // 38
	 1, //VAMPIRE_PORTAL_ITEM  // 39
	 1, //EVENT_GIFT_BOX       // 40
	50, //EVENT_STAR           // 41
 	 1, //VAMPIRE_EARRING      // 42
 	 1, //RELIC                // 43
 	 1, //VAMPIRE_WEAPON       // 44
 	 1, //VAMPIRE_AMULET       // 45
 	 1, //QUEST_ITEM       	   // 46
	 1, //EVENT_TREE           // 47
	 9, //EVENT_ETC            // 48
	 1, //BLOOD_BIBLE          // 49
	 1, //CASTLE_SYMBOL		   // 50 
	 1, //COUPLE_RING		   // 51
	 1, //VAMPIRE_COUPLE_RING  // 52
	 1, //EVENT_ITEM  		   // 53
	 1, //DYE_POTION		   // 54
	 9, //RESURRECT_ITEM	   // 55
	 9, //MIXING_ITEM		   // 56
	 1, //OUSTERS_ARMSBAND	   // 57
	 1, //OUSTERS_BOOTS		   // 58
	 1, //OUSTERS_CHAKRAM	   // 59
	 1, //OUSTERS_CIRCLET	   // 60
	 1, //OUSTERS_COAT		   // 61
	 1, //OUSTERS_PENDENT	   // 62
	 1, //OUSTERS_RING		   // 63
	 1, //OUSTERS_STONE		   // 64
	 1, //OUSTERS_WRISTLET	   // 65
	 30, //LARVA 			   // 66
	 30, //PUPA 				   // 67
	 30, //COMPOS_MEI 		   // 68
//#else
//	 9, //LARVA 			   // 66
//	 9, //PUPA 				   // 67
//	 9, //COMPOS_MEI 		   // 68
//#endif
	 1,	//OUSTERS_SUMMON_ITEM  // 69
	20, //EFFECT_ITEM          // 70
	 1, //CODE_SHEET		   // 71
	99, //MOON_CARD			   // 72
	 1, //SWEEPER			   // 73
	 1, //PET_ITEM			   // 74
	 9, //PET_FOOD			   // 75
	50, //PET_ENCHANT_ITEM	   // 76
	50, //LUCKY_BAG            // 77
	 1, //SMS_ITEM             // 78
	 1, //CORE_ZAP             // 79
	 1, //GQUEST_ITEM          // 80
	 1, //TRAP_ITEM			   // 81
	 1, //BLOOD_BIBLE_SIGN	   // 82
	 1, //WAR_ITEM			   // 83
	 1, //CARRYING_RECEIVER		// 84
	 1, //SHOULDER_ARMOR		// 85
	 1, //DERMIS				// 86
	 1, //PERSONA				// 87
	 1, //FASCIA				// 88
	 1, //MITTEN				// 89
	 1, //SUB_INVENTORY			// 90
};

class PCItemInfo;
class PlayerCreature;
class Store;

//////////////////////////////////////////////////////////////////////////////
// class Item
// 땅에 떨어져 있거나, 크리처에게 소유되는 수동적인 아이템들을 나타낸다.
//////////////////////////////////////////////////////////////////////////////

class Item : public Object 
{
public:
	// Item 의 하위 분류를 나타낸다. Item 클래스를 
	// 직접 상속받은 클래스를 아래 리스트에 추가하기 
	// 바란다. 또한 이 클래스들은 getItemClass() 를
	// 재정의해줘야 한다.
	enum ItemClass 
	{
		ITEM_CLASS_MOTORCYCLE,           // 0
		ITEM_CLASS_POTION,               // 1
		ITEM_CLASS_WATER,                // 2
		ITEM_CLASS_HOLYWATER,            // 3
		ITEM_CLASS_MAGAZINE,             // 4
		ITEM_CLASS_BOMB_MATERIAL,        // 5
		ITEM_CLASS_ETC,                  // 6
		ITEM_CLASS_KEY,                  // 7
		ITEM_CLASS_RING,                 // 8
		ITEM_CLASS_BRACELET,             // 9
		ITEM_CLASS_NECKLACE,             // 10
		ITEM_CLASS_COAT,                 // 11
		ITEM_CLASS_TROUSER,              // 12
		ITEM_CLASS_SHOES,                // 13
		ITEM_CLASS_SWORD,                // 14
		ITEM_CLASS_BLADE,                // 15
		ITEM_CLASS_SHIELD,               // 16
		ITEM_CLASS_CROSS,                // 17
		ITEM_CLASS_GLOVE,                // 18
		ITEM_CLASS_HELM,                 // 19
		ITEM_CLASS_SG,                   // 20
		ITEM_CLASS_SMG,                  // 21
		ITEM_CLASS_AR,                   // 22
		ITEM_CLASS_SR,                   // 23
		ITEM_CLASS_BOMB,                 // 24
		ITEM_CLASS_MINE,                 // 25
		ITEM_CLASS_BELT,                 // 26
		ITEM_CLASS_LEARNINGITEM,         // 27
		ITEM_CLASS_MONEY,                // 28
		ITEM_CLASS_CORPSE,               // 29
		ITEM_CLASS_VAMPIRE_RING,         // 30
		ITEM_CLASS_VAMPIRE_BRACELET,     // 31
		ITEM_CLASS_VAMPIRE_NECKLACE,     // 32
		ITEM_CLASS_VAMPIRE_COAT,         // 33
		ITEM_CLASS_SKULL,                // 34
		ITEM_CLASS_MACE,                 // 35
		ITEM_CLASS_SERUM,                // 36
		ITEM_CLASS_VAMPIRE_ETC,          // 37
		ITEM_CLASS_SLAYER_PORTAL_ITEM,   // 38
		ITEM_CLASS_VAMPIRE_PORTAL_ITEM,  // 39
		ITEM_CLASS_EVENT_GIFT_BOX,       // 40
		ITEM_CLASS_EVENT_STAR,           // 41
		ITEM_CLASS_VAMPIRE_EARRING,      // 42
		ITEM_CLASS_RELIC,                // 43
		ITEM_CLASS_VAMPIRE_WEAPON,       // 44
		ITEM_CLASS_VAMPIRE_AMULET,       // 45
		ITEM_CLASS_QUEST_ITEM,       	 // 46
		ITEM_CLASS_EVENT_TREE,           // 47
		ITEM_CLASS_EVENT_ETC,            // 48
		ITEM_CLASS_BLOOD_BIBLE,          // 49
		ITEM_CLASS_CASTLE_SYMBOL,        // 50
		ITEM_CLASS_COUPLE_RING,			 // 51
		ITEM_CLASS_VAMPIRE_COUPLE_RING,	 // 52
		ITEM_CLASS_EVENT_ITEM,	 		 // 53
		ITEM_CLASS_DYE_POTION,	 		 // 54
		ITEM_CLASS_RESURRECT_ITEM,		 // 55
		ITEM_CLASS_MIXING_ITEM,			 // 56
		ITEM_CLASS_OUSTERS_ARMSBAND,	 // 57
		ITEM_CLASS_OUSTERS_BOOTS,		 // 58
		ITEM_CLASS_OUSTERS_CHAKRAM,		 // 59
		ITEM_CLASS_OUSTERS_CIRCLET,		 // 60
		ITEM_CLASS_OUSTERS_COAT,		 // 61
		ITEM_CLASS_OUSTERS_PENDENT,		 // 62
		ITEM_CLASS_OUSTERS_RING,		 // 63
		ITEM_CLASS_OUSTERS_STONE,		 // 64
		ITEM_CLASS_OUSTERS_WRISTLET,	 // 65
		ITEM_CLASS_LARVA, 				 // 66
		ITEM_CLASS_PUPA, 				 // 67
		ITEM_CLASS_COMPOS_MEI, 			 // 68
		ITEM_CLASS_OUSTERS_SUMMON_ITEM,	 // 69
		ITEM_CLASS_EFFECT_ITEM,	 	  	 // 70
		ITEM_CLASS_CODE_SHEET,	 	  	 // 71
		ITEM_CLASS_MOON_CARD,			 // 72
		ITEM_CLASS_SWEEPER,			 	 // 73
		ITEM_CLASS_PET_ITEM,		 	 // 74
		ITEM_CLASS_PET_FOOD,		 	 // 75
		ITEM_CLASS_PET_ENCHANT_ITEM, 	 // 76
		ITEM_CLASS_LUCKY_BAG,            // 77
		ITEM_CLASS_SMS_ITEM,             // 78
		ITEM_CLASS_CORE_ZAP,             // 79
		ITEM_CLASS_GQUEST_ITEM,          // 80
		ITEM_CLASS_TRAP_ITEM,			// 81
		ITEM_CLASS_BLOOD_BIBLE_SIGN,	// 82
		ITEM_CLASS_WAR_ITEM,			// 83
		ITEM_CLASS_CARRYING_RECEIVER,		// 84
		ITEM_CLASS_SHOULDER_ARMOR,		// 85
		ITEM_CLASS_DERMIS,				// 86
		ITEM_CLASS_PERSONA,				// 87
		ITEM_CLASS_FASCIA,				// 88
		ITEM_CLASS_MITTEN,				// 89
		ITEM_CLASS_SUB_INVENTORY,		// 90

		ITEM_CLASS_MAX                   // 91
	};

	enum CreateType 
	{
		CREATE_TYPE_NORMAL,		// 일반적인 아이템 생성				// 0
		CREATE_TYPE_MONSTER,	// 몬스터에 의해서 생성				// 1
		CREATE_TYPE_SHOP,		// 상점에서 생성					// 2
		CREATE_TYPE_GAMBLE,		// 갬블을 통해서 생성				// 3
		CREATE_TYPE_ENCHANT,	// 인챈트를 통해서 생성				// 4
		CREATE_TYPE_GAME,		// 다른 게임 시스템에 의해서 생성	// 5
		CREATE_TYPE_CREATE,		// 운영자 명령어로 생성				// 6
		CREATE_TYPE_MALL,		// 웹의 샵 몰에서 구매한 아이템		// 7
		CREATE_TYPE_PRIZE,		// 기타 이벤트로 준 아이템			// 8
		CREATE_TYPE_MIXING,		// Mixing Forge 로 만든 아이템		// 9
		CREATE_TYPE_SPECIAL,	// 사장님 아이템 -_-;				// 10
		CREATE_TYPE_TIME_EXTENSION,	// 신규 유저 이벤트시 제한시간 늘려줘야 되는 아이템	// 11

		CREATE_TYPE_MAX
	};

// constructor/destructor
public:
	Item() throw();
	virtual ~Item();


// methods from Object
public:
	virtual ObjectClass getObjectClass() const throw() { return OBJECT_CLASS_ITEM; }
	virtual ObjectPriority getObjectPriority() const throw(Error) { return OBJECT_PRIORITY_ITEM; }
	virtual string toString() const throw() = 0;


// DB methods
public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error) = 0;	// itemID=0 <-- 특정 ItemID로 생성. by sigi. 2002.10.28
	virtual bool destroy() throw(Error);
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y) throw(Error) = 0;
	virtual void tinysave(const string & field) const throw(Error) = 0;
	void waste(Storage storage = STORAGE_GARBAGE ) const throw(Error);

// own methods
// *CAUTION*
// ItemType은 Item 의 하위 클래스에서 정의된다. 
// 이유는 역시 메모리 정렬 문제로 인한 낭비를 
// 막기 위해서이다.
public:
	virtual ItemClass getItemClass() const throw() = 0;
	string getItemClassName() const throw() { return ItemClass2String[getItemClass()]; }
	virtual string getObjectTableName() const throw() = 0;

	virtual bool isSilverWeapon() const throw() { return false; }
	virtual bool isGun() const throw() { return false; }

//	virtual Item* getTreasure() const throw() { return NULL; };

	virtual ItemType_t getItemType() const throw() = 0;
	virtual void setItemType(ItemType_t itemType) throw() = 0;

	virtual bool hasOptionType() const throw() { return false; }
	virtual int getOptionTypeSize() const throw() { return 0; }
	virtual int getRandomOptionType() const throw() { return 0; }
	virtual const list<OptionType_t>& getOptionTypeList() const throw() { static list<OptionType_t> nullList; return nullList; }
	virtual OptionType_t getFirstOptionType() const throw() { return 0; }
	virtual void removeOptionType(OptionType_t OptionType) throw() {}
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() {}
	virtual void addOptionType(OptionType_t OptionType) throw() {}
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() {}

	ItemID_t getItemID() const throw() { return m_ItemID; }
	void setItemID(ItemID_t itemID) throw() { m_ItemID = itemID; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error) = 0;
	virtual VolumeHeight_t getVolumeHeight() const throw(Error) = 0;
	virtual Weight_t getWeight() const throw(Error) = 0;

	virtual Durability_t getDurability() const throw(Error) { return 1; }
	virtual void setDurability(Durability_t durability) throw(Error) {}

	virtual Durability_t getMaxDurability() const { return 1; }

	virtual Damage_t getMinDamage() const throw(Error) { return 0; }
	virtual Damage_t getMaxDamage() const throw(Error) { return 0; }

	virtual Range_t getRange() const throw(Error) { return 0; }

	virtual ToHit_t getToHitBonus() const throw(Error) { return 0; }

	virtual Defense_t getDefenseBonus() const throw(Error) { return 0; }
	virtual Protection_t getProtectionBonus() const throw(Error) { return 0; }

    virtual MP_t getMPBonus() const throw(Error) { return 0; }

	virtual ItemNum_t getNum() const throw() { return 1; }
	virtual void setNum(ItemNum_t Num) throw() {}

	virtual bool isStackable() const throw() { return false; }

	virtual BYTE getBulletCount() const throw() { return 0; } 
	virtual void setBulletCount(BYTE bulletCount) throw() {}

	virtual Silver_t getSilver() const throw() { return 0; }
	virtual void setSilver(Silver_t amount) throw() { }

	virtual EnchantLevel_t getEnchantLevel() const throw() { return 0;}
	virtual void setEnchantLevel(EnchantLevel_t level) throw() { }

	virtual Damage_t getBonusDamage() const throw() { return 0; }
	virtual void setBonusDamage(Damage_t BonusDamage) throw() {}

	virtual int getCriticalBonus(void) const throw() { return 0; }

	virtual Grade_t getGrade() const { return -1; }
	virtual void setGrade(Grade_t Grade ) { } 

	virtual Luck_t getLuck() const { return 0; }

	EffectManager& getEffectManager() throw() { return m_EffectManager;}

    // set/remove/check flag
    void setFlag(Effect::EffectClass Flag) throw() { m_Flag.set(Flag); }
    void removeFlag(Effect::EffectClass Flag) throw() { m_Flag.reset(Flag); }
    bool isFlag(Effect::EffectClass Flag) throw() { return m_Flag.test(Flag); }

	virtual const list<OptionType_t>& getDefaultOptions(void) const throw();

	CreateType	getCreateType() const			 { return m_CreateType; }
	void	setCreateType(CreateType createType) { m_CreateType = createType; }

	bool	isUnique() const				{ return m_bUnique; }
	void	setUnique(bool bUnique=true)	{ m_bUnique = bUnique; }

	bool	isQuestItem() const;
	void	setQuestItem(bool bQuest=true)	{ m_bQuest = bQuest; }

	bool	isFlagItem() const { return getItemClass() == ITEM_CLASS_EVENT_ITEM && getItemType() == 27; }
	bool	isSweeper() const { return getItemClass() == ITEM_CLASS_SWEEPER; }

	bool	isTraceItem() const				{ return m_bTrace; }
	void	setTraceItem(bool bTrace=false)	{ m_bTrace = bTrace; }

	bool	isTimeLimitItem() const				{ return m_bTimeLimit; }
	void	setTimeLimitItem(bool bTimeLimit=true) { m_bTimeLimit = bTimeLimit; }

	int		getHour() const					{ return m_Hour; }
	void	setHour(int hour)				{ m_Hour = hour; }

	virtual void makePCItemInfo(PCItemInfo& pResult ) const;
	virtual void whenPCTake(PlayerCreature* pPC) {};
	virtual void whenPCLost(PlayerCreature* pPC);

	bool	isOnStore() const { return m_bOnStore; }

	void	displayItem(Store* pStore) { m_bOnStore = true; setStore(pStore); }
	void	undisplayItem() { m_bOnStore = false; setStore(NULL); }

	Store* 			getStore() const { return m_pStore; }
	void			setStore(Store* pStore ) { m_pStore = pStore; }

// member data
protected:
	ItemID_t                         m_ItemID;        // DB-unique ID 
	EffectManager                    m_EffectManager; // EffectManager
	bitset<Effect::EFFECT_CLASS_MAX> m_Flag;          // Effect flag

	CreateType                   	m_CreateType;	  // 아이템 생성 종류
	bool							m_bUnique;        // 유니크 아이템인가?
	bool							m_bQuest;		  // 퀘스트 아이템인가..
	bool							m_bTrace;		  // Trace Log 를 남길 아이템인가?

	bool							m_bTimeLimit;     // 시간제한 아이템인가?
	int								m_Hour;			  // 제한시간

	bool							m_bOnStore;			// 개인상점에 진열되어있는가
	Store*							m_pStore;
};

#endif
