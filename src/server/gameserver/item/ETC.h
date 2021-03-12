//////////////////////////////////////////////////////////////////////////////
// Filename    : ETC.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ETC_H__
#define __ETC_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ETC;
//////////////////////////////////////////////////////////////////////////////

class ETC : public Item 
{
public:
	ETC() ;
	ETC(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_ETC; }
	virtual string getObjectTableName() const  { return "ETCObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }


private:
	ItemType_t m_ItemType;
	ItemNum_t m_Num;				// 겹쳐있는 포션의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class ETCInfo
//////////////////////////////////////////////////////////////////////////////

class ETCInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_ETC; }
	virtual string toString() const ;

private:
	// bomb material 
	// required ability

};


//////////////////////////////////////////////////////////////////////////////
// class ETCInfoManager;
//////////////////////////////////////////////////////////////////////////////

class ETCInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_ETC; }
	
	virtual void load() ;

};

extern ETCInfoManager* g_pETCInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class ETCFactory
//////////////////////////////////////////////////////////////////////////////
class ETCFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_ETC; }

	// get item classname
	virtual string getItemClassName() const  { return "ETC"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new ETC(ItemType,OptionType,1); }

};


//////////////////////////////////////////////////////////////////////////////
// class ETCLoader;
//////////////////////////////////////////////////////////////////////////////

class ETCLoader : public ItemLoader 
{

public:

	// get item class
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_ETC; }

	// get item class name
	virtual string getItemClassName() const  { return "ETC"; }

public:

	// load to creature
	virtual void load(Creature* pCreature) ;

	// load to zone
	virtual void load(Zone* pZone) ;

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern ETCLoader* g_pETCLoader;

#endif
