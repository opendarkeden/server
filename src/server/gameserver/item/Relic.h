//////////////////////////////////////////////////////////////////////////////
// Filename    : Relic.h
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __RELIC_H__
#define __RELIC_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Relic;
//////////////////////////////////////////////////////////////////////////////

class Relic : public Item 
{
public:
	Relic() ;
	Relic(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_RELIC; }
	virtual string getObjectTableName() const  { return "RelicObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

public:
	virtual Durability_t getDurability() const  { return m_Durability; }
	void setDurability(Durability_t durability)  { m_Durability = durability; }

	virtual Defense_t getDefenseBonus() const ;
	virtual Protection_t getProtectionBonus() const ;

	virtual EnchantLevel_t getEnchantLevel() const  { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	Durability_t		m_Durability;		// 내구성
	EnchantLevel_t		m_EnchantLevel; 
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class RelicInfo
//////////////////////////////////////////////////////////////////////////////

const int maxRelic = 2;

// Relic Type, 성물의 본래 소유
enum RelicType
{
	RELIC_TYPE_SLAYER,
	RELIC_TYPE_VAMPIRE
};

extern const string RelicType2String[maxRelic];


class RelicInfo : public ItemInfo 
{
public:
	void setRelicType( const string& str ) 
	{
		if ( str == RelicType2String[RELIC_TYPE_SLAYER] ) relicType = RELIC_TYPE_SLAYER;
		else if ( str == RelicType2String[RELIC_TYPE_VAMPIRE] ) relicType = RELIC_TYPE_VAMPIRE;
		else throw InvalidProtocolException( "Invalid Relic Type value" );
	}

public:
	RelicType       relicType;
	int             zoneID;
	ZoneCoord_t     x, y;
	int             monsterType;

public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RELIC; }

	virtual Durability_t getDurability() const  { return m_Durability; }
	virtual void setDurability(Durability_t durability)  { m_Durability = durability; }

	Defense_t getDefenseBonus() const  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual string toString() const ;

private:
	Durability_t		m_Durability;		// 내구성
	Defense_t			m_DefenseBonus;		// 명중률 보너스
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class RelicInfoManager;
//////////////////////////////////////////////////////////////////////////////

class RelicInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RELIC; }
	virtual void load() ;
};

// global variable declaration
extern RelicInfoManager* g_pRelicInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class RelicFactory
//////////////////////////////////////////////////////////////////////////////

class RelicFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RELIC; }
	virtual string getItemClassName() const  { return "Relic"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Relic(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class RelicLoader;
//////////////////////////////////////////////////////////////////////////////

class RelicLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RELIC; }
	virtual string getItemClassName() const  { return "Relic"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern RelicLoader* g_pRelicLoader;
#endif
