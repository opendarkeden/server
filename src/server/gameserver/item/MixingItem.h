//////////////////////////////////////////////////////////////////////////////
// Filename    : MixingItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MIXING_ITEM_H__
#define __MIXING_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class MixingItem;
//////////////////////////////////////////////////////////////////////////////

class MixingItem : public Item 
{
public:
	MixingItem() ;
	MixingItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_MIXING_ITEM; }
	virtual string getObjectTableName() const  { return "MixingItemObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }

public:

private:
	ItemType_t m_ItemType;
	ItemNum_t m_Num;				// 겹쳐있는 포션의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class MixingItemInfo
//////////////////////////////////////////////////////////////////////////////

class MixingItemInfo : public ItemInfo 
{
public:
	enum Target
	{
		MIXING_WEAPON,
		MIXING_ARMOR,
		MIXING_ACCESSORY,
		MIXING_ALL
	};

	enum Type
	{
		TYPE_MIX,
		TYPE_DETACH,
		TYPE_CLEAR
	};
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MIXING_ITEM; }
	virtual string toString() const ;

public:
	Target	getTarget() const { return m_Target; }
	void	setTarget( Target target ) { m_Target = target; }

	Type	getType() const { return m_Type; }
	void	setType( Type type ) { m_Type = type; }

	ItemType_t	getVampireLevel() const { return m_VampireLevel; }
	ItemType_t	getSlayerLevel() const { return m_SlayerLevel; }
	ItemType_t	getOustersLevel() const { return m_OustersLevel; }

	void		setVampireLevel( ItemType_t level ) { m_VampireLevel = level; }
	void		setSlayerLevel( ItemType_t level ) { m_SlayerLevel = level; }
	void		setOustersLevel( ItemType_t level ) { m_OustersLevel = level; }

private:
	Target	m_Target;
	Type	m_Type;
	ItemType_t	m_SlayerLevel;
	ItemType_t	m_VampireLevel;
	ItemType_t	m_OustersLevel;
};

//////////////////////////////////////////////////////////////////////////////
// class MixingItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MixingItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MIXING_ITEM; }
	virtual void load() ;
};

extern MixingItemInfoManager* g_pMixingItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class MixingItemFactory
//////////////////////////////////////////////////////////////////////////////

class MixingItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MIXING_ITEM; }
	virtual string getItemClassName() const  { return "MixingItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new MixingItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class MixingItemLoader;
//////////////////////////////////////////////////////////////////////////////

class MixingItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MIXING_ITEM; }
	virtual string getItemClassName() const  { return "MixingItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern MixingItemLoader* g_pMixingItemLoader;

#endif
