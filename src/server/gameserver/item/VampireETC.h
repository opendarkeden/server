//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireETC.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VampireETC_H__
#define __VampireETC_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class VampireETC;
//////////////////////////////////////////////////////////////////////////////

class VampireETC : public Item 
{
public:
	VampireETC() ;
	VampireETC(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_ETC; }
	virtual string getObjectTableName() const  { return "VampireETCObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }

private:
	ItemType_t m_ItemType; // ...
	ItemNum_t  m_Num;      // 겹쳐있는 아이템의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class VampireETCInfo
//////////////////////////////////////////////////////////////////////////////

class VampireETCInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_ETC; }
	virtual string toString() const ;
};


//////////////////////////////////////////////////////////////////////////////
// class VampireETCInfoManager;
//////////////////////////////////////////////////////////////////////////////

class VampireETCInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_ETC; }
	virtual void load() ;
};

// global variable declaration
extern VampireETCInfoManager* g_pVampireETCInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class VampireETCFactory
//////////////////////////////////////////////////////////////////////////////
class VampireETCFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_ETC; }
	virtual string getItemClassName() const  { return "VampireETC"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new VampireETC(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampireETCLoader;
//////////////////////////////////////////////////////////////////////////////

class VampireETCLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_ETC; }
	virtual string getItemClassName() const  { return "VampireETC"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern VampireETCLoader* g_pVampireETCLoader;

#endif
