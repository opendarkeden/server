//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBible.h
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BLOOD_BIBLE_H__
#define __BLOOD_BIBLE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodBible;
//////////////////////////////////////////////////////////////////////////////

class BloodBible : public Item 
{
public:
	BloodBible() ;
	BloodBible(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual string getObjectTableName() const  { return "BloodBibleObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

public:
	virtual Durability_t getDurability() const  { return m_Durability; }
	void setDurability(Durability_t durability)  { m_Durability = durability; }

	virtual Defense_t getDefenseBonus() const ;
	virtual Protection_t getProtectionBonus() const ;

	virtual EnchantLevel_t getEnchantLevel() const  { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	Durability_t		m_Durability;		// 내구성
	EnchantLevel_t		m_EnchantLevel; 
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class BloodBibleInfo;
//////////////////////////////////////////////////////////////////////////////
class BloodBibleInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BLOOD_BIBLE; }

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
	Durability_t		m_Durability;		// 내구성
	Defense_t			m_DefenseBonus;		// 명중률 보너스
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class BloodBibleInfoManager;
//////////////////////////////////////////////////////////////////////////////

class BloodBibleInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual void load() ;
};

// global variable declaration
extern BloodBibleInfoManager* g_pBloodBibleInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class BloodBibleFactory
//////////////////////////////////////////////////////////////////////////////

class BloodBibleFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual string getItemClassName() const  { return "BloodBible"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new BloodBible(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class BloodBibleLoader;
//////////////////////////////////////////////////////////////////////////////

class BloodBibleLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual string getItemClassName() const  { return "BloodBible"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern BloodBibleLoader* g_pBloodBibleLoader;
#endif
