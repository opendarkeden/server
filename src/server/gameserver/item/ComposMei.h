//////////////////////////////////////////////////////////////////////////////
// Filename    : ComposMei.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __COMPOS_MEI_H__
#define __COMPOS_MEI_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ComposMei;
//////////////////////////////////////////////////////////////////////////////

class ComposMei : public ConcreteItem<Item::ITEM_CLASS_COMPOS_MEI, Stackable, NoDurability, NoOption, NoGrade, NoAttacking, NoEnchantLevel>
{
public:
	ComposMei() throw();
	ComposMei(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	bool destroy() throw(Error);

	// get debug string
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_COMPOS_MEI; }
//	virtual string getObjectTableName() const throw() { return "ComposMeiObject"; }

/*	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable() const throw() { return true; }*/

	// 회복양
	int getHPAmount(void) const throw();
	int getMPAmount(void) const throw();

	int getHPDelay(void) const throw();
	int getMPDelay(void) const throw();

	int getHPQuantity(void) const throw();
	int getMPQuantity(void) const throw();

	int getHPRecoveryUnit(void) const throw();
	int getMPRecoveryUnit(void) const throw();

private:

//	ItemType_t m_ItemType;			// 아이템 타입
//	ItemNum_t m_Num;				// 겹쳐있는 포션의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//--------------------------------------------------------------------------------
// 
// class ComposMeiInfo
// 
//--------------------------------------------------------------------------------

class ComposMeiInfo : public ItemInfo 
{
public:

	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_COMPOS_MEI; }

	int getHPAmount(void) const throw() { return m_HPAmount; }
	int getMPAmount(void) const throw() { return m_MPAmount; }

	int getHPDelay(void) const throw() { return m_HPDelay; }
	int getMPDelay(void) const throw() { return m_MPDelay; }

	int getHPQuantity(void) const throw() { return m_HPRecoveryUnit; }
	int getMPQuantity(void) const throw() { return m_MPRecoveryUnit; }

	int getHPRecoveryUnit(void) const throw() { return m_HPRecoveryUnit; }
	int getMPRecoveryUnit(void) const throw() { return m_MPRecoveryUnit; }

	void parseEffect(const string& effect) throw();

	// toString
	virtual string toString() const throw();

private:
	int  m_HPAmount;
	int  m_MPAmount;
	int  m_HPDelay;
	int  m_MPDelay;
	int  m_HPRecoveryUnit;
	int  m_MPRecoveryUnit;

};


//--------------------------------------------------------------------------------
//
// class ComposMeiInfoManager;
//
//--------------------------------------------------------------------------------
class ComposMeiInfoManager : public InfoClassManager {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_COMPOS_MEI; }
	
	// load from DB
	virtual void load() throw(Error);

};

// global variable declaration
extern ComposMeiInfoManager* g_pComposMeiInfoManager;


//--------------------------------------------------------------------------------
//
// class ComposMeiFactory
//
//--------------------------------------------------------------------------------
class ComposMeiFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_COMPOS_MEI; }

	// get item classname
	virtual string getItemClassName() const throw() { return "ComposMei"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new ComposMei(ItemType,OptionType,1); }

};


//--------------------------------------------------------------------------------
//
// class ComposMeiLoader;
//
//--------------------------------------------------------------------------------

class ComposMeiLoader : public ItemLoader {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_COMPOS_MEI; }

	// get item class name
	virtual string getItemClassName() const throw() { return "ComposMei"; }

public:

	// load to creature
	virtual void load(Creature* pCreature) throw(Error);

	// load to zone
	virtual void load(Zone* pZone) throw(Error);

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);

};

extern ComposMeiLoader* g_pComposMeiLoader;
#endif
