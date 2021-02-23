//////////////////////////////////////////////////////////////////////////////
// Filename    : Motorcycle.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MOTORCYCLE_H__
#define __MOTORCYCLE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Motorcycle;
//////////////////////////////////////////////////////////////////////////////

class Motorcycle : public Item 
{
public:
	Motorcycle() throw();
	Motorcycle(ItemType_t itemType, const list<OptionType_t>& optionType) throw(Error);
	~Motorcycle() throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual string getObjectTableName() const throw() { return "MotorcycleObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual bool hasOptionType() const throw() { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	virtual int getRandomOptionType() const throw() { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList() const throw() { return m_OptionType; }
	virtual OptionType_t getFirstOptionType() const throw() { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	Inventory* getInventory() throw() { return m_pInventory; }

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	list<OptionType_t>		m_OptionType;		// 옵션 타입
	Durability_t		m_Durability;		// 내구성
	Inventory*			m_pInventory;		// 인벤토리
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleInfo
//////////////////////////////////////////////////////////////////////////////

class MotorcycleInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MOTORCYCLE; }

	virtual Durability_t getDurability() const throw() { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	virtual string toString() const throw();

private:
	Durability_t m_Durability;	// 내구성
};


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MotorcycleInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual void load() throw(Error);
};

// global variable declaration
extern MotorcycleInfoManager* g_pMotorcycleInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleFactory
//////////////////////////////////////////////////////////////////////////////

class MotorcycleFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual string getItemClassName() const throw() { return "Motorcycle"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Motorcycle(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleLoader;
//////////////////////////////////////////////////////////////////////////////

class MotorcycleLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual string getItemClassName() const throw() { return "Motorcycle"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern MotorcycleLoader* g_pMotorcycleLoader;

#endif
