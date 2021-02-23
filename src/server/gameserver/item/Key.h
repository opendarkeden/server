//////////////////////////////////////////////////////////////////////////////
// Filename    : Key.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __KEY_H__
#define __KEY_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

class Slayer;

//////////////////////////////////////////////////////////////////////////////
// class Key;
//////////////////////////////////////////////////////////////////////////////

class Key : public Item 
{
public:
	Key() throw();
	Key(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_KEY; }
	virtual string getObjectTableName() const throw() { return "KeyObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	ItemID_t getTarget() const throw() { return m_Target; }
	void setTarget(ItemID_t target) throw() { m_Target = target; }

	ItemID_t setNewMotorcycle(Slayer* pSlayer) throw(Error);

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	ItemID_t			m_Target;			// 무엇을 열 것인가?	
	
	static Mutex		m_Mutex;			// 아이템 ID 관련 락
	static ItemID_t		m_ItemIDRegistry; 	// 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class KeyInfo
//////////////////////////////////////////////////////////////////////////////

class KeyInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_KEY; }
	virtual string toString() const throw();

	OptionType_t getOptionType() const throw() { return m_OptionType; }
	void setOptionType( OptionType_t optionType ) { m_OptionType = optionType; }

	ItemType_t getTargetType() const throw() { return m_TargetType; }
	void setTargetType( ItemType_t target ) { m_TargetType = target; }

private:
	OptionType_t m_OptionType;
	ItemType_t m_TargetType;
};


//////////////////////////////////////////////////////////////////////////////
// class KeyInfoManager;
//////////////////////////////////////////////////////////////////////////////

class KeyInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_KEY; }
	virtual void load() throw(Error);
};

// global variable declaration
extern KeyInfoManager* g_pKeyInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class KeyFactory
//////////////////////////////////////////////////////////////////////////////

class KeyFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_KEY; }
	virtual string getItemClassName() const throw() { return "Key"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Key(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class KeyLoader;
//////////////////////////////////////////////////////////////////////////////

class KeyLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_KEY; }
	virtual string getItemClassName() const throw() { return "Key"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern KeyLoader* g_pKeyLoader;


#endif
