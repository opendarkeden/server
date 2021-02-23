//////////////////////////////////////////////////////////////////////////////
// Filename    : PetItem.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PET_ITEM_H__
#define __PET_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

#include "PetInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class PetItem;
//////////////////////////////////////////////////////////////////////////////

class PetItem : public Item 
{
public:
	PetItem() throw();
	PetItem(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	~PetItem() { SAFE_DELETE( m_pPetInfo ); }
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	void savePetInfo() const;
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ITEM; }
	virtual string getObjectTableName() const throw() { return "PetItemObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	void		setPetInfo( PetInfo* pPetInfo ) { m_pPetInfo = pPetInfo; }
	PetInfo*	getPetInfo() const { return m_pPetInfo; }

	void makePCItemInfo(PCItemInfo& result) const;

	void whenPCTake( PlayerCreature* pPC );
	void whenPCLost( PlayerCreature* pPC );

private:
	ItemType_t m_ItemType;
	PetInfo*	m_pPetInfo;

	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class PetItemInfo
//////////////////////////////////////////////////////////////////////////////

class PetItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ITEM; }
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class PetItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class PetItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ITEM; }
	virtual void load() throw(Error);
};

extern PetItemInfoManager* g_pPetItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class PetItemFactory
//////////////////////////////////////////////////////////////////////////////

class PetItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ITEM; }
	virtual string getItemClassName() const throw() { return "PetItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new PetItem(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class PetItemLoader;
//////////////////////////////////////////////////////////////////////////////

class PetItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ITEM; }
	virtual string getItemClassName() const throw() { return "PetItem"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern PetItemLoader* g_pPetItemLoader;

#endif
