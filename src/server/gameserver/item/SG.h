//////////////////////////////////////////////////////////////////////////////
// Filename    : SG.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SG_H__
#define __SG_H__

//#include "Gun.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class SG;
//////////////////////////////////////////////////////////////////////////////

class SG : public ConcreteItem<Item::ITEM_CLASS_SG, NoStack, HasDurability, HasOption, WeaponGrade, SlayerGun>
{
public:
	SG() ;
	SG(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	~SG() ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual void saveBullet() ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
//	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_SG; }
//	virtual string getObjectTableName() const  { return "SGObject"; }

/*	bool isSilverWeapon() const  { return true; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual Damage_t getMinDamage() const ;
	virtual Damage_t getMaxDamage() const ;

	virtual Range_t getRange() const ;

	virtual ToHit_t getToHitBonus() const ;

	virtual int getCriticalBonus(void) const ;
*/
	void makePCItemInfo(PCItemInfo& result) const;

private:

	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class SGInfo
//////////////////////////////////////////////////////////////////////////////

class SGInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SG; }

	virtual Durability_t getDurability() const  { return m_Durability; }
	virtual void setDurability(Durability_t durability)  { m_Durability = durability; }

	virtual Damage_t getMinDamage() const  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage)  { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage() const  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage)  { m_MaxDamage = maxDamage; }

	Range_t getRange() const  { return m_Range; }
	void setRange(Range_t range)  { m_Range = range; }

	ToHit_t getToHitBonus() const  { return m_ToHitBonus; }
	void setToHitBonus(ToHit_t tohit)  { m_ToHitBonus = tohit; }

	virtual Speed_t getSpeed(void) const  { return m_Speed; }
	virtual void setSpeed(Speed_t speed)  { m_Speed = speed; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual int getCriticalBonus(void) const  { return m_CriticalBonus; }
	virtual void setCriticalBonus(int bonus)  { m_CriticalBonus = bonus; }

	virtual string toString() const ;

private:
	Durability_t  m_Durability;
	Damage_t      m_MinDamage;
	Damage_t      m_MaxDamage;
	Range_t       m_Range;
	ToHit_t       m_ToHitBonus;
	Speed_t       m_Speed;
	uint          m_ItemLevel;
	int           m_CriticalBonus; // 아이템마다 다른 크리티컬 확률

};


//////////////////////////////////////////////////////////////////////////////
// class SGInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SGInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SG; }
	virtual void load() ;
};

// global variable declaration
extern SGInfoManager* g_pSGInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SGFactory
//////////////////////////////////////////////////////////////////////////////

class SGFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SG; }
	virtual string getItemClassName() const  { return "SG"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new SG(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SGLoader;
//////////////////////////////////////////////////////////////////////////////

class SGLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SG; }
	virtual string getItemClassName() const  { return "SG"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern SGLoader* g_pSGLoader;

#endif
