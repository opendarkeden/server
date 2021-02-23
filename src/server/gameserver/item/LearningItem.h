//////////////////////////////////////////////////////////////////////////////
// Filename    : LearningItem.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __LEARNINGITEM_H__
#define __LEARNINGITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class LearningItem;
//////////////////////////////////////////////////////////////////////////////

class LearningItem : public Item 
{
public:
	LearningItem() throw();
	LearningItem(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_LEARNINGITEM; }
	virtual string getObjectTableName() const throw() { return "LearningItemObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

private:
	ItemType_t			m_ItemType;		// 아이템 타입
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class LearningItemInfo
//////////////////////////////////////////////////////////////////////////////

class LearningItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_LEARNINGITEM; }

	virtual string toString() const throw();

public:
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t skillType) throw() { m_SkillType = skillType; }

private:
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////////////
// class LearningItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class LearningItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_LEARNINGITEM; }
	virtual void load() throw(Error);
};

// global variable declaration
extern LearningItemInfoManager* g_pLearningItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class LearningItemFactory
//////////////////////////////////////////////////////////////////////////////

class LearningItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_LEARNINGITEM; }
	virtual string getItemClassName() const throw() { return "LearningItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new LearningItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class LearningItemLoader;
//////////////////////////////////////////////////////////////////////////////

class LearningItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_LEARNINGITEM; }
	virtual string getItemClassName() const throw() { return "LearningItem"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern LearningItemLoader* g_pLearningItemLoader;


#endif
