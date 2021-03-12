//////////////////////////////////////////////////////////////////////////////
// Filename    : VampirePortalItem.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_PORTAL_ITEM_H__
#define __VAMPIRE_PORTAL_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItem;
//////////////////////////////////////////////////////////////////////////////

class EffectVampirePortal;

class VampirePortalItem : public Item 
{
public:
	VampirePortalItem() ;
	VampirePortalItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	~VampirePortalItem() ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string& field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char*field) const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string getObjectTableName() const  { return "VampirePortalItemObject"; }

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

	ZoneID_t getZoneID(void) const { return m_ZoneID; }
	void setZoneID(ZoneID_t id) { m_ZoneID = id; }

	ZoneCoord_t getX(void) const { return m_X; }
	void setX(ZoneCoord_t X) { m_X = X; }

	ZoneCoord_t getY(void) const { return m_Y; }
	void setY(ZoneCoord_t Y) { m_Y = Y; }

public:
	virtual Durability_t getDurability() const ;
	virtual Silver_t getSilver() const ;
	virtual EnchantLevel_t getEnchantLevel() const ;

private:
	ItemType_t  m_ItemType; // 아이템 타입
	int         m_Charge;   // 포탈을 열 수 있는 횟수
	ZoneID_t    m_ZoneID;   // 목표 존 ID
	ZoneCoord_t m_X;        // 목표 존 좌표 
	ZoneCoord_t m_Y;        // 목표 존 좌표 
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemInfo
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string toString() const ;

public:
	int getMaxCharge(void) const { return m_MaxCharge; }
	void setMaxCharge(int charge) { m_MaxCharge = charge; }

private:
	int m_MaxCharge;
};


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual void load() ;
};

extern VampirePortalItemInfoManager* g_pVampirePortalItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemFactory
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string getItemClassName() const  { return "VampirePortalItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new VampirePortalItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemLoader;
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string getItemClassName() const  { return "VampirePortalItem"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;

};

extern VampirePortalItemLoader* g_pVampirePortalItemLoader;

#endif
