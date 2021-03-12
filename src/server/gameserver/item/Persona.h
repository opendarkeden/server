//////////////////////////////////////////////////////////////////////////////
// Filename    : Persona.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PERSONA_H__
#define __PERSONA_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Persona;
//////////////////////////////////////////////////////////////////////////////

class Persona : public ConcreteItem<Item::ITEM_CLASS_PERSONA, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking>
{
public:
	Persona() ;
	Persona(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
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
// class PersonaInfo
//////////////////////////////////////////////////////////////////////////////

class PersonaInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_PERSONA; }

	virtual Durability_t getDurability() const  { return m_Durability; }
	virtual void setDurability(Durability_t durability)  { m_Durability = durability; }

	Defense_t getDefenseBonus() const  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual string toString() const ;

private:
	Durability_t	m_Durability;		// 내구성
	Defense_t		m_DefenseBonus;		// 명중률 보너스
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class PersonaInfoManager;
//////////////////////////////////////////////////////////////////////////////

class PersonaInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_PERSONA; }
	virtual void load() ;
};

// global variable declaration
extern PersonaInfoManager* g_pPersonaInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class PersonaFactory
//////////////////////////////////////////////////////////////////////////////

class PersonaFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_PERSONA; }
	virtual string getItemClassName() const  { return "Persona"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Persona(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class PersonaLoader;
//////////////////////////////////////////////////////////////////////////////

class PersonaLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_PERSONA; }
	virtual string getItemClassName() const  { return "Persona"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern PersonaLoader* g_pPersonaLoader;

#endif
