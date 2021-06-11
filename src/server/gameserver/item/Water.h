//////////////////////////////////////////////////////////////////////////////
// Filename    : Water.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __WATER_H__
#define __WATER_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Water;
//////////////////////////////////////////////////////////////////////////////

class Water : public Item 
{
public:
	Water() ;
	Water(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;

	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_WATER; }
	virtual string getObjectTableName() const  { return "WaterObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }

private:
	ItemType_t m_ItemType;			// 아이템 타입
	ItemNum_t m_Num; 
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class WaterInfo
//////////////////////////////////////////////////////////////////////////////

class WaterInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_WATER; }
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class WaterInfoManager;
//////////////////////////////////////////////////////////////////////////////

class WaterInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_WATER; }
	virtual void load() ;
};

// global variable declaration
extern WaterInfoManager* g_pWaterInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class WaterFactory
//////////////////////////////////////////////////////////////////////////////

class WaterFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_WATER; }
	virtual string getItemClassName() const  { return "Water"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Water(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class WaterLoader;
//////////////////////////////////////////////////////////////////////////////

class WaterLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_WATER; }
	virtual string getItemClassName() const  { return "Water"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern WaterLoader* g_pWaterLoader;

#endif
