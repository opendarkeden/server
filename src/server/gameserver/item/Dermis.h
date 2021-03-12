//////////////////////////////////////////////////////////////////////////////
// Filename    : Dermis.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __DERMIS_H__
#define __DERMIS_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Dermis;
//////////////////////////////////////////////////////////////////////////////

class Dermis : public ConcreteItem<Item::ITEM_CLASS_DERMIS, NoStack, NoDurability, HasOption, AccessoryGrade, NoAttacking>
{
public:
	Dermis() ;
	Dermis(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
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
// class DermisInfo
//////////////////////////////////////////////////////////////////////////////

class DermisInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_DERMIS; }

	Defense_t getDefenseBonus() const  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual string toString() const ;

private:
	Defense_t		m_DefenseBonus;		// 명중률 보너스
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class DermisInfoManager;
//////////////////////////////////////////////////////////////////////////////

class DermisInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_DERMIS; }
	virtual void load() ;
};

// global variable declaration
extern DermisInfoManager* g_pDermisInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class DermisFactory
//////////////////////////////////////////////////////////////////////////////

class DermisFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_DERMIS; }
	virtual string getItemClassName() const  { return "Dermis"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Dermis(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class DermisLoader;
//////////////////////////////////////////////////////////////////////////////

class DermisLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_DERMIS; }
	virtual string getItemClassName() const  { return "Dermis"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern DermisLoader* g_pDermisLoader;

#endif
