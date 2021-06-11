//////////////////////////////////////////////////////////////////////////////
// Filename    : EventItem.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_ITEM_H__
#define __EVENT_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventItem;
//////////////////////////////////////////////////////////////////////////////

class EventItem : public Item 
{
public:
	EventItem() ;
	EventItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

	void whenPCTake( PlayerCreature* pPC );

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string getObjectTableName() const  { return "EventItemObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

public:
	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class EventItemInfo
//////////////////////////////////////////////////////////////////////////////

class EventItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class EventItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual void load() ;
};

extern EventItemInfoManager* g_pEventItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventItemFactory
//////////////////////////////////////////////////////////////////////////////

class EventItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string getItemClassName() const  { return "EventItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new EventItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventItemLoader;
//////////////////////////////////////////////////////////////////////////////

class EventItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string getItemClassName() const  { return "EventItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern EventItemLoader* g_pEventItemLoader;

#endif
