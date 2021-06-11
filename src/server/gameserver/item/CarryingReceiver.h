//////////////////////////////////////////////////////////////////////////////
// Filename    : CarryingReceiver.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CARRYING_RECEIVER_H__
#define __CARRYING_RECEIVER_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class CarryingReceiver;
//////////////////////////////////////////////////////////////////////////////

class CarryingReceiver : public ConcreteItem<Item::ITEM_CLASS_CARRYING_RECEIVER, NoStack, NoDurability, HasOption, AccessoryGrade, NoAttacking>
{
public:
	CarryingReceiver() ;
	CarryingReceiver(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

private:
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class CarryingReceiverInfo
//////////////////////////////////////////////////////////////////////////////

class CarryingReceiverInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CARRYING_RECEIVER; }

	Defense_t getDefenseBonus() const  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual string toString() const ;

private:
	Defense_t			m_DefenseBonus;		// 명중률 보너스
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class CarryingReceiverInfoManager;
//////////////////////////////////////////////////////////////////////////////

class CarryingReceiverInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CARRYING_RECEIVER; }
	virtual void load() ;
};

// global variable declaration
extern CarryingReceiverInfoManager* g_pCarryingReceiverInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CarryingReceiverFactory
//////////////////////////////////////////////////////////////////////////////

class CarryingReceiverFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CARRYING_RECEIVER; }
	virtual string getItemClassName() const  { return "CarryingReceiver"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new CarryingReceiver(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CarryingReceiverLoader;
//////////////////////////////////////////////////////////////////////////////

class CarryingReceiverLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CARRYING_RECEIVER; }
	virtual string getItemClassName() const  { return "CarryingReceiver"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern CarryingReceiverLoader* g_pCarryingReceiverLoader;
#endif
