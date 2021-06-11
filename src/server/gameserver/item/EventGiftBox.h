//////////////////////////////////////////////////////////////////////////////
// Filename    : EventGiftBox.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_GIFT_BOX_H__
#define __EVENT_GIFT_BOX_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBox;
//////////////////////////////////////////////////////////////////////////////
class EventGiftBox : public Item 
{
public:
	EventGiftBox() ;
	EventGiftBox(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getObjectTableName() const  { return "EventGiftBoxObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

private:
	ItemType_t m_ItemType;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxInfo
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string toString() const ;

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxInfoManager;
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual void load() ;
};

extern EventGiftBoxInfoManager* g_pEventGiftBoxInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxFactory
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getItemClassName() const  { return "EventGiftBox"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new EventGiftBox(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxLoader;
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getItemClassName() const  { return "EventGiftBox"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern EventGiftBoxLoader* g_pEventGiftBoxLoader;

#endif
