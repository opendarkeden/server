//////////////////////////////////////////////////////////////////////////////
// Filename    : SMG.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SMG_H__
#define __SMG_H__

//#include "Gun.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class SMG;
//////////////////////////////////////////////////////////////////////////////

class SMG : public ConcreteItem<Item::ITEM_CLASS_SMG, NoStack, HasDurability, HasOption, WeaponGrade, SlayerGun> 
{
public:
	SMG() throw();
	SMG(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	~SMG() throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw(Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw(Error);
	virtual void saveBullet() throw(Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SMG; }
//	virtual string getObjectTableName() const throw() { return "SMGObject"; }

/*	bool isSilverWeapon() const throw() { return true; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual Damage_t getMinDamage() const throw(Error);
	virtual Damage_t getMaxDamage() const throw(Error);

	virtual Range_t getRange() const throw(Error);

	virtual ToHit_t getToHitBonus() const throw(Error);

	virtual int getCriticalBonus(void) const throw();
*/
	void makePCItemInfo(PCItemInfo& result) const;

private:

	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class SMGInfo
//////////////////////////////////////////////////////////////////////////////

class SMGInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SMG; }

	virtual Durability_t getDurability() const throw() { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	virtual Damage_t getMinDamage() const throw() { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage) throw() { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage() const throw() { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage) throw() { m_MaxDamage = maxDamage; }

	Range_t getRange() const throw() { return m_Range; }
	void setRange(Range_t range) throw() { m_Range = range; }

	ToHit_t getToHitBonus() const throw() { return m_ToHitBonus; }
	void setToHitBonus(ToHit_t tohit) throw() { m_ToHitBonus = tohit; }

	virtual Speed_t getSpeed(void) const throw() { return m_Speed; }
	virtual void setSpeed(Speed_t speed) throw() { m_Speed = speed; }

	virtual uint getItemLevel(void) const throw() { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual int getCriticalBonus(void) const throw() { return m_CriticalBonus; }
	virtual void setCriticalBonus(int bonus) throw() { m_CriticalBonus = bonus; }

	virtual string toString() const throw();

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
// class SMGInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SMGInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SMG; }
	virtual void load() throw(Error);

};

// global variable declaration
extern SMGInfoManager* g_pSMGInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SMGFactory
//////////////////////////////////////////////////////////////////////////////

class SMGFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SMG; }
	virtual string getItemClassName() const throw() { return "SMG"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new SMG(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SMGLoader;
//////////////////////////////////////////////////////////////////////////////

class SMGLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SMG; }
	virtual string getItemClassName() const throw() { return "SMG"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern SMGLoader* g_pSMGLoader;

#endif
