//////////////////////////////////////////////////////////////////////////////
// Filename    : Glove.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GLOVE_H__
#define __GLOVE_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Glove;
//////////////////////////////////////////////////////////////////////////////

class Glove : public ConcreteItem<Item::ITEM_CLASS_GLOVE, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking>
{
public:
	Glove() throw();
	Glove(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw(Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw(Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();


public:
//	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_GLOVE; }
//	virtual string getObjectTableName() const throw() { return "GloveObject"; }

/*	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	// get/set item option type
	virtual bool hasOptionType() const throw() { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	virtual int getRandomOptionType() const throw() { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList() const throw() { return m_OptionType; }
	virtual OptionType_t getFirstOptionType() const throw() { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }

	// get width
	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	
	// get height
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	
	// get weight
	virtual Weight_t getWeight() const throw(Error);

	// get/set item's durability
	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	// get/set armor's Defense Bonus
	virtual Defense_t getDefenseBonus() const throw(Error);
	virtual Protection_t getProtectionBonus() const throw(Error);
*/

private:

//	ItemType_t m_ItemType;			// 아이템 타입
//	list<OptionType_t> m_OptionType;		// 옵션 타입
//	Durability_t m_Durability;		// 내구성
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class GloveInfo
//////////////////////////////////////////////////////////////////////////////

class GloveInfo : public ItemInfo {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_GLOVE; }

	// get/set item's durability
	virtual Durability_t getDurability() const throw() { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	// get/set armor's Defense Bonus
	Defense_t getDefenseBonus() const throw() { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const throw() { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const throw() { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	// toString
	virtual string toString() const throw();

private:

	Durability_t m_Durability;		// 내구성
	Defense_t m_DefenseBonus;		// 명중률 보너스
	Protection_t m_ProtectionBonus;
	uint          m_ItemLevel;

};


//--------------------------------------------------------------------------------
//
// class GloveInfoManager;
//
//--------------------------------------------------------------------------------
class GloveInfoManager : public InfoClassManager {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_GLOVE; }
	
	// load from DB
	virtual void load() throw(Error);

};

// global variable declaration
extern GloveInfoManager* g_pGloveInfoManager;


//--------------------------------------------------------------------------------
//
// class GloveFactory
//
//--------------------------------------------------------------------------------
class GloveFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_GLOVE; }

	// get item classname
	virtual string getItemClassName() const throw() { return "Glove"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Glove(ItemType,OptionType); }

};


//--------------------------------------------------------------------------------
//
// class GloveLoader;
//
//--------------------------------------------------------------------------------

class GloveLoader : public ItemLoader {

public:

	// get item class
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_GLOVE; }

	// get item class name
	virtual string getItemClassName() const throw() { return "Glove"; }

public:

	// load to creature
	virtual void load(Creature* pCreature) throw(Error);

	// load to zone
	virtual void load(Zone* pZone) throw(Error);

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);

};

extern GloveLoader* g_pGloveLoader;

#endif
