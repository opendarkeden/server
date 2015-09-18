//////////////////////////////////////////////////////////////////////////////
// Filename    : EventStar.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_STAR_H__
#define __EVENT_STAR_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventStar;
//////////////////////////////////////////////////////////////////////////////

class EventStar : public Item 
{
public:
	EventStar() throw();
	EventStar(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw(Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw(Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string getObjectTableName() const throw() { return "EventStarObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable() const throw() { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class EventStarInfo
//////////////////////////////////////////////////////////////////////////////

class EventStarInfo : public ItemInfo 
{
public:
	enum ITEM_FUNCTION
	{
		FUNCTION_NULL = 0,
		FUNCTION_ENCHANT_OPTION = 0x01,	// 옵션을 더 좋게 바꾼다.
		FUNCTION_ADD_OPTION = 0x02,		// 옵션을 추가한다.
		FUNCTION_ENCHANT_RARE_OPTION = 0x04,	// 레어 아이템의 옵션을 업~한다.
		FUNCTION_TRANS_KIT = 0x08,		// 아템 성별을 바꾼다.
		FUNCTION_UP_GRADE = 0x10,		// 아이템 급수를 올린다.
	};

public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string toString() const throw();

public :
	virtual BYTE getFunctionFlag() const throw() { return m_fFunction; }
	virtual BYTE isFunctionEnchantOption() const { return m_fFunction & FUNCTION_ENCHANT_OPTION; }	// 옵션을 더 좋게 바꾼다.
	virtual BYTE isFunctionAddOption() const { return m_fFunction & FUNCTION_ADD_OPTION; }	// 옵션을 추가한다.
	virtual BYTE isFunctionEnchantRareOption() const { return m_fFunction & FUNCTION_ENCHANT_RARE_OPTION; }	// 옵션을 더 좋게 바꾼다.
	virtual BYTE isFunctionTransKit() const { return m_fFunction & FUNCTION_TRANS_KIT; }
	virtual void setFunctionFlag(BYTE flag) throw() { m_fFunction = flag; }

	virtual int getFunctionValue() const throw() { return m_FunctionValue; }
	virtual void setFunctionValue(int value) throw() { m_FunctionValue = value; }


	BYTE	   m_fFunction;		// 기능
	int        m_FunctionValue;	// 기능과 관련된 값
};

//////////////////////////////////////////////////////////////////////////////
// class EventStarInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventStarInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual void load() throw(Error);
};

extern EventStarInfoManager* g_pEventStarInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventStarFactory
//////////////////////////////////////////////////////////////////////////////

class EventStarFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string getItemClassName() const throw() { return "EventStar"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EventStar(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventStarLoader;
//////////////////////////////////////////////////////////////////////////////

class EventStarLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string getItemClassName() const throw() { return "EventStar"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern EventStarLoader* g_pEventStarLoader;

#endif
