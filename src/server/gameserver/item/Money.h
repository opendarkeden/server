//////////////////////////////////////////////////////////////////////////////
// Filename    : Money.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONEY_H__
#define __MONEY_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Money;
//////////////////////////////////////////////////////////////////////////////

class Money : public Item 
{
public:
	Money() ;
	Money(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_MONEY; }
	virtual string getObjectTableName() const  { return "MoneyObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual string toString() const ;
// add by sonic 2006.10.30
	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }
// end 
public:
	DWORD getAmount() const  { return m_Amount; }
	void setAmount(DWORD amount)  { m_Amount = amount; }

public:
	virtual Durability_t getDurability() const  
	{ 
		WORD lowBits  = (m_Amount & 0x0000FFFF);
		return lowBits;
	}

	virtual Silver_t getSilver() const  
	{ 
		WORD highBits = m_Amount >> 16;
		return highBits;
	}

private:
	ItemType_t m_ItemType; // 아이템 타입
	DWORD      m_Amount;   // 액수
	//  add by sonci 2006.10.30
	ItemNum_t  m_Num;
	// end
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class MoneyInfo
//////////////////////////////////////////////////////////////////////////////

class MoneyInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MONEY; }
	virtual string toString() const ;
};


//////////////////////////////////////////////////////////////////////////////
// class MoneyInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MoneyInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MONEY; }
	virtual void load() ;
};

extern MoneyInfoManager* g_pMoneyInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MoneyFactory
//////////////////////////////////////////////////////////////////////////////

class MoneyFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MONEY; }
	virtual string getItemClassName() const  { return "Money"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Money(ItemType,OptionType,1); }
};


//////////////////////////////////////////////////////////////////////////////
// class MoneyLoader;
//////////////////////////////////////////////////////////////////////////////

class MoneyLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MONEY; }
	virtual string getItemClassName() const  { return "Money"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern MoneyLoader* g_pMoneyLoader;

#endif
