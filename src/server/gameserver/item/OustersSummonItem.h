//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersSummonItem.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_SUMMON_ITEM_H__
#define __OUSTERS_SUMMON_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItem;
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItem : public Item 
{
public:
	OustersSummonItem() ;
	OustersSummonItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string getObjectTableName() const  { return "OustersSummonItemObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual string toString() const ;

public:
	int getCharge(void) const { return m_Charge; }
	void setCharge(int charge) { m_Charge = charge; }

	int getMaxCharge(void) const ;

public:
	virtual EnchantLevel_t getEnchantLevel() const  { return m_Charge; }

private:
	ItemType_t m_ItemType; // 아이템 타입
	int        m_Charge;   // 포탈을 열 수 있는 횟수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemInfo
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string toString() const ;

public:
	int getMaxCharge(void) const { return m_MaxCharge; }
	void setMaxCharge(int charge) { m_MaxCharge = charge; }

	EffectID_t getEffectID(void) const { return m_EffectID; }
	void setEffectID(int effectID) { m_EffectID = effectID; }

private:
	int m_MaxCharge;
	EffectID_t m_EffectID;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual void load() ;
};

extern OustersSummonItemInfoManager* g_pOustersSummonItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemFactory
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string getItemClassName() const  { return "OustersSummonItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new OustersSummonItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string getItemClassName() const  { return "OustersSummonItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern OustersSummonItemLoader* g_pOustersSummonItemLoader;

#endif
