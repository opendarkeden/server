//////////////////////////////////////////////////////////////////////////////
// Filename    : EventETC.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_ETC_H__
#define __EVENT_ETC_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventETC;
//////////////////////////////////////////////////////////////////////////////

class EventETC : public Item 
{
public:
	EventETC() throw();
	EventETC(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getObjectTableName() const throw() { return "EventETCObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool	isStackable() const throw() { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class EventETCInfo
//////////////////////////////////////////////////////////////////////////////

class EventETCInfo : public ItemInfo 
{
public:
/*	enum ITEM_FUNCTION
	{
		FUNCTION_NULL = 0,
		FUNCTION_ENCHANT_OPTION = 0x01,	// 옵션을 더 좋게 바꾼다.
		FUNCTION_ADD_OPTION = 0x02,		// 옵션을 추가한다.
		FUNCTION_ENCHANT_RARE_OPTION = 0x04,	// 레어 아이템의 옵션을 업~한다.
	};*/

public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string toString() const throw();

	uint getFunction() const { return m_Function; }
	void setFunction( uint func ) { m_Function = func; }

private:
	uint m_Function;
};

//////////////////////////////////////////////////////////////////////////////
// class EventETCInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventETCInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual void load() throw(Error);
};

extern EventETCInfoManager* g_pEventETCInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventETCFactory
//////////////////////////////////////////////////////////////////////////////

class EventETCFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getItemClassName() const throw() { return "EventETC"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EventETC(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventETCLoader;
//////////////////////////////////////////////////////////////////////////////

class EventETCLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getItemClassName() const throw() { return "EventETC"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern EventETCLoader* g_pEventETCLoader;

#endif
