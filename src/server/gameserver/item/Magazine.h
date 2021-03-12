//////////////////////////////////////////////////////////////////////////////
// Filename    : Magazine.h
// Written By  : Elca
//////////////////////////////////////////////////////////////////////////////

#ifndef __MAGAZINE_H__
#define __MAGAZINE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Magazine;
//////////////////////////////////////////////////////////////////////////////

class Magazine : public Item 
{
public:
	Magazine() ;
	Magazine(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string getObjectTableName() const  { return "MagazineObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

public:
	ItemNum_t getNum() const  { return m_Num; }
	void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }

private:
	ItemType_t			m_ItemType;		// 아이템 타입
	ItemNum_t			m_Num;			// 겹쳐있는 탄창의 수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class MagazineInfo
//////////////////////////////////////////////////////////////////////////////

class MagazineInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string toString() const ;

	enum GunType
	{
		AR=0, SMG, SG, SR
	};

public:
	uint getMaxBullets() const  { return m_MaxBullets; }
	void setMaxBullets(uint maxBullets)  { m_MaxBullets = maxBullets; }

	Silver_t getMaxSilver(void) const  { return m_MaxSilver; }
	void setMaxSilver(Silver_t silver)  { m_MaxSilver = silver; }

	virtual uint getItemLevel(void) const  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	bool isVivid() const { return m_bVivid; }
	void setVivid( bool vivid=true ) { m_bVivid = vivid; }

	GunType getGunType() const { return m_GunType; }
	void setGunType( GunType type ) { m_GunType = type; }

private:
	uint     m_MaxBullets;
	Silver_t m_MaxSilver;
	uint     m_ItemLevel;
	bool	 m_bVivid;
	GunType	 m_GunType;
};


//////////////////////////////////////////////////////////////////////////////
// class MagazineInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MagazineInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual void load() ;
};

// global variable declaration
extern MagazineInfoManager* g_pMagazineInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MagazineFactory
//////////////////////////////////////////////////////////////////////////////

class MagazineFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string getItemClassName() const  { return "Magazine"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Magazine(ItemType,OptionType,1); }
};


//////////////////////////////////////////////////////////////////////////////
// class MagazineLoader;
//////////////////////////////////////////////////////////////////////////////

class MagazineLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string getItemClassName() const  { return "Magazine"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern MagazineLoader* g_pMagazineLoader;

#endif
