//////////////////////////////////////////////////////////////////////////////
// Filename    : Potion.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Potion;
//////////////////////////////////////////////////////////////////////////////

class Potion : public ConcreteItem<Item::ITEM_CLASS_POTION, Stackable, NoDurability, NoOption, NoGrade, NoAttacking, NoEnchantLevel>
{
public:
	Potion() ;
	Potion(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	bool destroy() ;

	// get debug string
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
//	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_POTION; }
//	virtual string getObjectTableName() const  { return "PotionObject"; }

/*	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }*/

	// 회복양
	int getHPAmount(void) const ;
	int getMPAmount(void) const ;

	int getHPDelay(void) const ;
	int getMPDelay(void) const ;

	int getHPQuantity(void) const ;
	int getMPQuantity(void) const ;

	int getHPRecoveryUnit(void) const ;
	int getMPRecoveryUnit(void) const ;

private:

//	ItemType_t m_ItemType;			// 아이템 타입
//	ItemNum_t m_Num;				// 겹쳐있는 포션의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//--------------------------------------------------------------------------------
// 
// class PotionInfo
// 
//--------------------------------------------------------------------------------

class PotionInfo : public ItemInfo 
{
public:

	// get item class
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_POTION; }

	int getHPAmount(void) const  { return m_HPAmount; }
	int getMPAmount(void) const  { return m_MPAmount; }

	int getHPDelay(void) const  { return m_HPDelay; }
	int getMPDelay(void) const  { return m_MPDelay; }

	int getHPQuantity(void) const  { return m_HPRecoveryUnit; }
	int getMPQuantity(void) const  { return m_MPRecoveryUnit; }

	int getHPRecoveryUnit(void) const  { return m_HPRecoveryUnit; }
	int getMPRecoveryUnit(void) const  { return m_MPRecoveryUnit; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	void parseEffect(const string& effect) ;

	// toString
	virtual string toString() const ;

private:
	int  m_HPAmount;
	int  m_MPAmount;
	int  m_HPDelay;
	int  m_MPDelay;
	int  m_HPRecoveryUnit;
	int  m_MPRecoveryUnit;
	uint m_ItemLevel;

};


//--------------------------------------------------------------------------------
//
// class PotionInfoManager;
//
//--------------------------------------------------------------------------------
class PotionInfoManager : public InfoClassManager {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_POTION; }
	
	// load from DB
	virtual void load() ;

};

// global variable declaration
extern PotionInfoManager* g_pPotionInfoManager;


//--------------------------------------------------------------------------------
//
// class PotionFactory
//
//--------------------------------------------------------------------------------
class PotionFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_POTION; }

	// get item classname
	virtual string getItemClassName() const  { return "Potion"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Potion(ItemType,OptionType,1); }

};


//--------------------------------------------------------------------------------
//
// class PotionLoader;
//
//--------------------------------------------------------------------------------

class PotionLoader : public ItemLoader {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_POTION; }

	// get item class name
	virtual string getItemClassName() const  { return "Potion"; }

public:

	// load to creature
	virtual void load(Creature* pCreature) ;

	// load to zone
	virtual void load(Zone* pZone) ;

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern PotionLoader* g_pPotionLoader;
#endif
