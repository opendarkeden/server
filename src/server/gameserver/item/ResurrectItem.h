//////////////////////////////////////////////////////////////////////////////
// Filename    : ResurrectItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __RESURRECT_ITEM_H__
#define __RESURRECT_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItem;
//////////////////////////////////////////////////////////////////////////////

class ResurrectItem : public Item 
{
public:
	ResurrectItem() ;
	ResurrectItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string getObjectTableName() const  { return "ResurrectItemObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

public:
	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool	isStackable() const  { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemInfo
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemInfo : public ItemInfo 
{
public:
	enum ResurrectType
	{
		HP_1,		// HP가 1인 상태로 부활
		HP_FULL		// HP가 꽉찬 상태로 부활
	};
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string toString() const ;

	ResurrectType	getResurrectType() const { return m_ResurrectType; }
	void			setResurrectType( ResurrectType type ) { m_ResurrectType = type; }

private:
	ResurrectType m_ResurrectType;
};

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual void load() ;
};

extern ResurrectItemInfoManager* g_pResurrectItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemFactory
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string getItemClassName() const  { return "ResurrectItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new ResurrectItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemLoader;
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string getItemClassName() const  { return "ResurrectItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern ResurrectItemLoader* g_pResurrectItemLoader;

#endif
