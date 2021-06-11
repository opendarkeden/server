//////////////////////////////////////////////////////////////////////////////
// Filename    : MoonCard.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MOON_CARD_H__
#define __MOON_CARD_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class MoonCard;
//////////////////////////////////////////////////////////////////////////////

class MoonCard : public Item 
{
public:
	MoonCard() ;
	MoonCard(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_MOON_CARD; }
	virtual string getObjectTableName() const  { return "MoonCardObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

public:
	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class MoonCardInfo
//////////////////////////////////////////////////////////////////////////////

class MoonCardInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MOON_CARD; }
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class MoonCardInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MoonCardInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MOON_CARD; }
	virtual void load() ;
};

extern MoonCardInfoManager* g_pMoonCardInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class MoonCardFactory
//////////////////////////////////////////////////////////////////////////////

class MoonCardFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MOON_CARD; }
	virtual string getItemClassName() const  { return "MoonCard"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new MoonCard(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class MoonCardLoader;
//////////////////////////////////////////////////////////////////////////////

class MoonCardLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MOON_CARD; }
	virtual string getItemClassName() const  { return "MoonCard"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern MoonCardLoader* g_pMoonCardLoader;

#endif
