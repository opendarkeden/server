//////////////////////////////////////////////////////////////////////////////
// Filename    : ShoulderArmor.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHOULDER_ARMOR_H__
#define __SHOULDER_ARMOR_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmor;
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmor : public ConcreteItem<Item::ITEM_CLASS_SHOULDER_ARMOR, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking>
{
public:
	ShoulderArmor() throw();
	ShoulderArmor(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
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
// class ShoulderArmorInfo
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SHOULDER_ARMOR; }

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
	Durability_t  m_Durability;
	Defense_t     m_DefenseBonus;
	Protection_t  m_ProtectionBonus;
	uint          m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorInfoManager;
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SHOULDER_ARMOR; }
	virtual void load() throw(Error);
};

extern ShoulderArmorInfoManager* g_pShoulderArmorInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorFactory
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SHOULDER_ARMOR; }
	virtual string getItemClassName() const throw() { return "ShoulderArmor"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new ShoulderArmor(ItemType,OptionType); }

};


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorLoader;
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SHOULDER_ARMOR; }
	virtual string getItemClassName() const throw() { return "ShoulderArmor"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);

};

extern ShoulderArmorLoader* g_pShoulderArmorLoader;

#endif
