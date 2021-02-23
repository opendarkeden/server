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
	EventItem() throw();
	EventItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

	void whenPCTake( PlayerCreature* pPC );

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string getObjectTableName() const throw() { return "EventItemObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

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
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class EventItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual void load() throw(Error);
};

extern EventItemInfoManager* g_pEventItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventItemFactory
//////////////////////////////////////////////////////////////////////////////

class EventItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string getItemClassName() const throw() { return "EventItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EventItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventItemLoader;
//////////////////////////////////////////////////////////////////////////////

class EventItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ITEM; }
	virtual string getItemClassName() const throw() { return "EventItem"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern EventItemLoader* g_pEventItemLoader;

#endif
