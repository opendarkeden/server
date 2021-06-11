//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerPortalItem.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_PORTAL_ITEM_H__
#define __SLAYER_PORTAL_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItem;
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItem : public Item 
{
public:
	SlayerPortalItem() ;
	SlayerPortalItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string getObjectTableName() const  { return "SlayerPortalItemObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	virtual string toString() const ;

public:
	int getCharge(void) const { return m_Charge; }
	void setCharge(int charge) { m_Charge = charge; }

	int getMaxCharge(void) const ;

public:
	virtual EnchantLevel_t getEnchantLevel() const  { return m_Charge; }

private:
	ItemType_t m_ItemType; // 아이템 타입
	int        m_Charge;   // 포탈을 열 수 있는 횟수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemInfo
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string toString() const ;

public:
	int getMaxCharge(void) const { return m_MaxCharge; }
	void setMaxCharge(int charge) { m_MaxCharge = charge; }

private:
	int m_MaxCharge;
};


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual void load() ;
};

extern SlayerPortalItemInfoManager* g_pSlayerPortalItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemFactory
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string getItemClassName() const  { return "SlayerPortalItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new SlayerPortalItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemLoader;
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string getItemClassName() const  { return "SlayerPortalItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern SlayerPortalItemLoader* g_pSlayerPortalItemLoader;

#endif
