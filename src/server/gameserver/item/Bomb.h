//////////////////////////////////////////////////////////////////////////////
// Filename    : Bomb.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BOMB_H__
#define __BOMB_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Bomb;
//////////////////////////////////////////////////////////////////////////////

class Bomb : public Item 
{
public:
	Bomb() ;
	Bomb(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const ;
	virtual string toString() const ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass() const  { return Item::ITEM_CLASS_BOMB; }
	virtual string getObjectTableName() const  { return "BombObject"; }

	virtual ItemType_t getItemType() const  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const ;
	virtual VolumeHeight_t getVolumeHeight() const ;
	virtual Weight_t getWeight() const ;

	Damage_t getDamage() const  { return m_Damage;}
	void setDamage(Damage_t D)  { m_Damage = D;}

	//Dir_t getDir() const  { return m_Dir;}
	//void setDir(Dir_t R)  { m_Dir = R;}

	virtual Damage_t getMinDamage() const ;
	virtual Damage_t getMaxDamage() const ;

	virtual ItemNum_t getNum() const  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable() const  { return true; }

private:
	ItemType_t m_ItemType;			// 아이템 타입
	Damage_t   m_Damage;
	ItemNum_t  m_Num;
	//	Dir_t m_Dir;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class BombInfo
//////////////////////////////////////////////////////////////////////////////

class BombInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BOMB; }
	virtual string toString() const ;

	virtual Damage_t getMinDamage() const  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage)  { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage() const  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage)  { m_MaxDamage = maxDamage; }

private:
	Damage_t m_MinDamage;     // 최소 데미지
	Damage_t m_MaxDamage;     // 최대 데미지
};


//////////////////////////////////////////////////////////////////////////////
// class BombInfoManager;
//////////////////////////////////////////////////////////////////////////////

class BombInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BOMB; }
	virtual void load() ;
};

extern BombInfoManager* g_pBombInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class BombFactory
//////////////////////////////////////////////////////////////////////////////

class BombFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BOMB; }
	virtual string getItemClassName() const  { return "Bomb"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Bomb(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class BombLoader;
//////////////////////////////////////////////////////////////////////////////

class BombLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_BOMB; }
	virtual string getItemClassName() const  { return "Bomb"; }

public:
	virtual void load(Creature* pCreature) ;
	virtual void load(Zone* pZone) ;
	virtual void load(StorageID_t storageID, Inventory* pInventory) ;
};

extern BombLoader* g_pBombLoader;

#endif
