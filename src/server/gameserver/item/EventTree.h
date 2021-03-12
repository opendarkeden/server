//////////////////////////////////////////////////////////////////////////////
// Filename    : EventTree.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_TREE_H__
#define __EVENT_TREE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventTree;
//////////////////////////////////////////////////////////////////////////////

class EventTree : public Item 
{
public:
	EventTree() ;
	EventTree(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_TREE; }
	virtual string getObjectTableName() const  { return "EventTreeObject"; }

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
// class EventTreeInfo
//////////////////////////////////////////////////////////////////////////////

class EventTreeInfo : public ItemInfo 
{
public:
	enum ITEM_FUNCTION
	{
		FUNCTION_NULL = 0,
		FUNCTION_ENCHANT_OPTION = 0x01,	// 옵션을 더 좋게 바꾼다.
		FUNCTION_ADD_OPTION = 0x02,		// 옵션을 추가한다.
		FUNCTION_ENCHANT_RARE_OPTION = 0x04,	// 레어 아이템의 옵션을 업~한다.
	};

public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_TREE; }
	virtual string toString() const ;

};

//////////////////////////////////////////////////////////////////////////////
// class EventTreeInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventTreeInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_TREE; }
	virtual void load() ;
};

extern EventTreeInfoManager* g_pEventTreeInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventTreeFactory
//////////////////////////////////////////////////////////////////////////////

class EventTreeFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_TREE; }
	virtual string getItemClassName() const  { return "EventTree"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new EventTree(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventTreeLoader;
//////////////////////////////////////////////////////////////////////////////

class EventTreeLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_EVENT_TREE; }
	virtual string getItemClassName() const  { return "EventTree"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern EventTreeLoader* g_pEventTreeLoader;

#endif
