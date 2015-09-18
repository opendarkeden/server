//////////////////////////////////////////////////////////////////////////////
// Filename    : Mitten.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MITTEN_H__
#define __MITTEN_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Mitten;
//////////////////////////////////////////////////////////////////////////////

class Mitten : public ConcreteItem<Item::ITEM_CLASS_MITTEN, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking>
{
public:
	Mitten() throw();
	Mitten(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw(Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw(Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

private:
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class MittenInfo
//////////////////////////////////////////////////////////////////////////////

class MittenInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MITTEN; }

	virtual Durability_t getDurability() const throw() { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	Defense_t getDefenseBonus() const throw() { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const throw() { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const throw() { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() const throw();

private:
	Durability_t	m_Durability;		// 내구성
	Defense_t		m_DefenseBonus;
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class MittenInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MittenInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MITTEN; }
	virtual void load() throw(Error);
};

// global variable declaration
extern MittenInfoManager* g_pMittenInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MittenFactory
//////////////////////////////////////////////////////////////////////////////

class MittenFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MITTEN; }
	virtual string getItemClassName() const throw() { return "Mitten"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Mitten(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class MittenLoader;
//////////////////////////////////////////////////////////////////////////////

class MittenLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MITTEN; }
	virtual string getItemClassName() const throw() { return "Mitten"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern MittenLoader* g_pMittenLoader;

#endif
