//////////////////////////////////////////////////////////////////////////////
// Filename    : SubInventory.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SUB_INVENTORY_H__
#define __SUB_INVENTORY_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

class Inventory;

//////////////////////////////////////////////////////////////////////////////
// class SubInventory;
//////////////////////////////////////////////////////////////////////////////

class SubInventory : public Item 
{
public:
	SubInventory() ;
	SubInventory(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	~SubInventory();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getObjectTableName() const  { return "SubInventoryObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	Inventory* getInventory() const { return m_pInventory; }
	void setInventory(Inventory* pInventory) { m_pInventory = pInventory; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	void makePCItemInfo(PCItemInfo& result) const;

private:
	ItemType_t m_ItemType;
	Inventory* m_pInventory;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class SubInventoryInfo
//////////////////////////////////////////////////////////////////////////////

class SubInventoryInfo : public ItemInfo 
{
private:
	CoordInven_t m_Width, m_Height;
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string toString() const ;

	CoordInven_t getWidth() const { return m_Width; }
	void setWidth(CoordInven_t Width) { m_Width = Width; }

	CoordInven_t getHeight() const { return m_Height; }
	void setHeight(CoordInven_t Height) { m_Height = Height; }

};

//////////////////////////////////////////////////////////////////////////////
// class SubInventoryInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SubInventoryInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual void load() ;
};

extern SubInventoryInfoManager* g_pSubInventoryInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class SubInventoryFactory
//////////////////////////////////////////////////////////////////////////////

class SubInventoryFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getItemClassName() const  { return "SubInventory"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new SubInventory(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class SubInventoryLoader;
//////////////////////////////////////////////////////////////////////////////

class SubInventoryLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getItemClassName() const  { return "SubInventory"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern SubInventoryLoader* g_pSubInventoryLoader;

#endif
