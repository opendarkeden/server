//////////////////////////////////////////////////////////////////////////////
// Filename    : Serum.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __Serum_H__
#define __Serum_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Serum;
//////////////////////////////////////////////////////////////////////////////

class Serum : public Item 
{
public:
	Serum() throw();
	Serum(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SERUM; }
	virtual string getObjectTableName() const throw() { return "SerumObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	int getHPAmount(void) const throw();
	int getPeriod(void) const throw();
	int getCount(void) const throw();

	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable() const throw() { return true; }

private:
	ItemType_t m_ItemType; // 아이템 타입
	ItemNum_t  m_Num;      // 겹쳐있는 혈청의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class SerumInfo
//////////////////////////////////////////////////////////////////////////////

class SerumInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SERUM; }

	int getHPAmount(void) const { return m_HPAmount; }
	void setHPAmount(int amount) { m_HPAmount = amount; }

	int getPeriod(void) const { return m_Period; }
	void setPeriod(int period) { m_Period = period; }

	int getCount(void) const { return m_Count; }
	void setCount(int count) { m_Count = count; }

	void parseEffect(const string& effect) throw();

	virtual string toString() const throw();

private:
	int m_HPAmount; // 단위 시간당 HP 회복량
	int m_Period;   // 단위 시간(초 단위)
	int m_Count;    // 단위 시간을 몇 번 반복할 것인가?



};


//////////////////////////////////////////////////////////////////////////////
// class SerumInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SerumInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SERUM; }
	virtual void load() throw(Error);
};

extern SerumInfoManager* g_pSerumInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SerumFactory
//////////////////////////////////////////////////////////////////////////////

class SerumFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SERUM; }
	virtual string getItemClassName() const throw() { return "Serum"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Serum(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SerumLoader;
//////////////////////////////////////////////////////////////////////////////

class SerumLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SERUM; }
	virtual string getItemClassName() const throw() { return "Serum"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);

};

extern SerumLoader* g_pSerumLoader;

#endif
