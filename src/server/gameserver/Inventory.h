//////////////////////////////////////////////////////////////////////////////
// Filename    : Inventory.h
// Written By  : elca@ewestsoft.com
// Revised By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Types.h"
#include "Item.h"
#include "VolumeInfo.h"
#include "InventorySlot.h"
#include <list>

class PetItem;
class InventoryInfo;
class Player;

#define MAX_INVEN_WIDTH		10
#define MAX_INVEN_HEIGHT	6

//////////////////////////////////////////////////////////////////////////////
// Class Inventory
//////////////////////////////////////////////////////////////////////////////

class Inventory 
{
// constructor & destructor
public:
	Inventory(CoordInven_t X,CoordInven_t Y, bool bDeleteAll=true) throw();
	Inventory(const Inventory* pInventory) throw();
	~Inventory() throw();

// identity methods
public:
	string getOwner(void) const throw() { return m_Owner; }
	void setOwner(const string& owner) throw() { m_Owner = owner; }

	CoordInven_t getWidth() const throw() { return m_Width; }
	CoordInven_t getHeight() const throw() { return m_Height; }

	ItemNum_t getItemNum() const throw() { return m_TotalNum; }
	void increaseNum() throw() { m_TotalNum++; }
	void increaseNum(ItemNum_t ItemNum) throw() { m_TotalNum += ItemNum; }
	void decreaseItemNum() throw() { m_TotalNum--; }
	void decreaseItemNum(ItemNum_t ItemNum) throw() { m_TotalNum -= ItemNum; }
	void setItemNum(ItemNum_t ItemNum) throw() { m_TotalNum = ItemNum; }

	Weight_t getWeight() const throw() { return m_TotalWeight; }
	void increaseWeight(Weight_t Weight) throw() { m_TotalWeight += Weight; }
	void decreaseWeight(Weight_t Weight) throw() { m_TotalWeight -= Weight; }

	bool getDeleteAllFlag(void) const throw() { return m_bDeleteAll; }
	void setDeleteAllFlag(bool value) throw() { m_bDeleteAll = value; }

// check methods
public: 
	bool hasItem(CoordInven_t X, CoordInven_t Y) const throw();
	bool hasItem(ObjectID_t ObjectID) const throw();
	bool hasItemWithItemID(ItemID_t ItemID) const throw();
	bool hasItemWithItemClass(Item::ItemClass ItemClass ) const;
	bool hasKey(ItemID_t TargetItemID) const throw();

	bool canAdding(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();
	bool canAddingEx(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();

// addition & deletion related methods
public:
	bool  addItem(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();
	Item* addItemEx(CoordInven_t X, CoordInven_t Y, Item* pItem) throw(Error);
	bool  addItem(Item* pItem) throw(InventoryFullException,Error);
	bool  addItem(Item* pItem, TPOINT& pt) throw(InventoryFullException,Error);
	bool  getEmptySlot(Item* pItem, _TPOINT& p) throw()
	{
		Assert (pItem != NULL);
		return getEmptySlot(pItem->getVolumeWidth(), pItem->getVolumeHeight(), p);
	}
	bool  getEmptySlot(VolumeWidth_t ItemWidth, VolumeHeight_t ItemHeight, _TPOINT& p) throw();
	void  deleteItem(ObjectID_t ObjectID) throw(Error);
	void  deleteItem(CoordInven_t X, CoordInven_t Y) throw(Error);

// find methods
public:
	Item* searchItem(CoordInven_t X, CoordInven_t Y, Item* pItem, TPOINT & pt) throw();

	Item* getItemWithItemID(ItemID_t itemID) throw(Error);
	Item* getBeltWithItemID(ItemID_t itemID) throw(Error);
	Item* getItemWithObjectID(ObjectID_t objectID) throw(Error);

	Item* findItemOID(ObjectID_t objectID, CoordInven_t& X, CoordInven_t& Y) const throw();
	Item* findItemIID(ItemID_t ItemID, CoordInven_t& X, CoordInven_t& Y) const throw();

	Item* findItemOID(ObjectID_t objectID, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) const throw();
	Item* findItemIID(ItemID_t ItemID, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) const throw();

	Item* findItem(Item::ItemClass IClass, ItemType_t itemType=0xFFFF) const throw();
	Item* findItem(Item::ItemClass IClass, ItemType_t itemType, CoordInven_t& X, CoordInven_t& Y) const throw();

// item manipulation related methods
public:
	Item* getItem(CoordInven_t X, CoordInven_t Y) const throw();

	InventorySlot& getInventorySlot(CoordInven_t X, CoordInven_t Y) const throw() { return m_pInventorySlot[X][Y]; }

protected:
	void  setItem(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();

// packing related methods
public:
	void clear() throw(); 
	list<Item*> getList() const throw();
	int  calc2x2Item(void) const throw();

// misc methods
public:
	void   save(const string& owner) throw();
	string toString() const throw();


//#ifdef __XMAS_EVENT_CODE__
/////////////////////////////////////////////////////////////////////////
// 2001년 크리스마스 이벤트 관련 함수들.
// 2002년 어린이날 스타 이벤트를 위해서 재사용(GiftBox는 사용하지 않음)
// 이벤트 재사용을 위해서 XMAS_STAR를 STAR_EVENT로 바꾸는 것을 고려해야 함
public:
	bool hasEnoughStar(const XMAS_STAR& star) throw(Error);
	void decreaseStar(const XMAS_STAR& star) throw(Error);
	bool hasRedGiftBox(void) throw(Error);
	bool hasGreenGiftBox(void) throw(Error);

	bool hasEnoughNumItem(Item::ItemClass itemClass, ItemType_t itemType, int num);
	void decreaseNumItem(Item::ItemClass itemClass, ItemType_t itemType, int num, Player* pPlayer);
//#endif

public:
	void clearQuestItem(list<Item*>& iList) throw(Error);

public:
	InventoryInfo* getInventoryInfo() const;

////////////////////////////////////////
// member data
////////////////////////////////////////
private:
	string          m_Owner;          // 인벤토리 소유주
	CoordInven_t    m_Width;          // Inventory Width
	CoordInven_t    m_Height;         // Inventory Height 
	ItemNum_t       m_TotalNum;       // Total Count
	Weight_t        m_TotalWeight;    // Total Weight
	InventorySlot** m_pInventorySlot; // InventorySlot의 이차원 배열.
	bool            m_bDeleteAll;     // 객체가 삭제될 때 아이템까지 삭제한다.
};

#endif	// __INVENTORY_H__
