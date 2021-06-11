//////////////////////////////////////////////////////////////////////////////
// Filename    : Cross.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CROSS_H__
#define __CROSS_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Cross;
//////////////////////////////////////////////////////////////////////////////

class Cross : public ConcreteItem<Item::ITEM_CLASS_CROSS, NoStack, HasDurability, HasOption, WeaponGrade, SlayerWeapon> 
{
public:
	Cross() ;
	Cross(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
//	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_CROSS; }
//	virtual string getObjectTableName() const  { return "CrossObject"; }

/*	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	bool isSilverWeapon() const  { return true; }

	virtual bool hasOptionType() const  { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize() const  { return m_OptionType.size(); }
	virtual int getRandomOptionType() const  { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList() const  { return m_OptionType; }
	virtual OptionType_t getFirstOptionType() const  { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType)  { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType)  { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType)  { m_OptionType = OptionType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual Durability_t getDurability() const  { return m_Durability; }
	void setDurability(Durability_t durability)  { m_Durability = durability; }

	virtual Damage_t getMinDamage() const ;
	virtual Damage_t getMaxDamage() const ;

	Damage_t getBonusDamage() const  { return m_BonusDamage;}
	void setBonusDamage(Damage_t damage)  { m_BonusDamage = damage;}
*/
	virtual MP_t getMPBonus() const ;

/*	virtual Silver_t getSilver() const  { return m_Silver; }
	virtual void setSilver(Silver_t amount)  { m_Silver = amount; }
*/
//	virtual int getCriticalBonus(void) const ;

private:
//	ItemType_t    m_ItemType;
//	list<OptionType_t>  m_OptionType;
//	Durability_t  m_Durability;
//	BYTE          m_BonusDamage;
//	Silver_t      m_Silver;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class CrossInfo
//////////////////////////////////////////////////////////////////////////////

class CrossInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CROSS; }

	virtual Durability_t getDurability() const  { return m_Durability; }
	virtual void setDurability(Durability_t durability)  { m_Durability = durability; }

	virtual Damage_t getMinDamage() const  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage)  { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage() const  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage)  { m_MaxDamage = maxDamage; }

	virtual MP_t getMPBonus() const  { return m_MPBonus; }
	void setMPBonus(MP_t mpBonus)  { m_MPBonus = mpBonus; }

	virtual Silver_t getMaxSilver() const  { return m_MaxSilver; }
	virtual void setMaxSilver(Silver_t amount)  { m_MaxSilver = amount; }

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
	MP_t          m_MPBonus;
	Silver_t      m_MaxSilver;
	Speed_t       m_Speed;
	uint          m_ItemLevel;
	int           m_CriticalBonus; // 아이템마다 다른 크리티컬 확률

};


//////////////////////////////////////////////////////////////////////////////
// class CrossInfoManager;
//////////////////////////////////////////////////////////////////////////////

class CrossInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CROSS; }
	virtual void load() ;
};

extern CrossInfoManager* g_pCrossInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CrossFactory
//////////////////////////////////////////////////////////////////////////////

class CrossFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CROSS; }
	virtual string getItemClassName() const  { return "Cross"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Cross(ItemType,OptionType); }

};


//////////////////////////////////////////////////////////////////////////////
// class CrossLoader;
//////////////////////////////////////////////////////////////////////////////

class CrossLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CROSS; }
	virtual string getItemClassName() const  { return "Cross"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern CrossLoader* g_pCrossLoader;

#endif
