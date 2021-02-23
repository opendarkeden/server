//////////////////////////////////////////////////////////////////////////////
// Filename    : PetFood.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PET_FOOD_H__
#define __PET_FOOD_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"
#include "types/PetTypes.h"

//////////////////////////////////////////////////////////////////////////////
// class PetFood;
//////////////////////////////////////////////////////////////////////////////

class PetFood : public Item 
{
public:
	PetFood() throw();
	PetFood(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_FOOD; }
	virtual string getObjectTableName() const throw() { return "PetFoodObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable() const throw() { return true; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

private:
	ItemType_t m_ItemType;
	ItemNum_t m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class PetFoodInfo
//////////////////////////////////////////////////////////////////////////////

class PetFoodInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_FOOD; }
	virtual string toString() const throw();

	PetHP_t getPetHP() const { return m_PetHP; }
	void setPetHP( PetHP_t PetHP ) { m_PetHP = PetHP; }

	int getTameRatio() const { return m_TameRatio; }
	void setTameRatio( int ratio ) { m_TameRatio = ratio; }

	int getTarget() const { return m_Target; }
	void setTarget( int Target ) { m_Target = Target; }

private :
	PetHP_t m_PetHP;
	int m_TameRatio;
	int m_Target;
};

//////////////////////////////////////////////////////////////////////////////
// class PetFoodInfoManager;
//////////////////////////////////////////////////////////////////////////////

class PetFoodInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_FOOD; }
	virtual void load() throw(Error);
};

extern PetFoodInfoManager* g_pPetFoodInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class PetFoodFactory
//////////////////////////////////////////////////////////////////////////////

class PetFoodFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_FOOD; }
	virtual string getItemClassName() const throw() { return "PetFood"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new PetFood(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class PetFoodLoader;
//////////////////////////////////////////////////////////////////////////////

class PetFoodLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_FOOD; }
	virtual string getItemClassName() const throw() { return "PetFood"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern PetFoodLoader* g_pPetFoodLoader;

#endif
