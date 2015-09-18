////////////////////////////////////////////////////////////////////////////////
// Filename    : Inventory.cpp
// Written By  : elca@ewestsoft.com
// Revised By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "Inventory.h"
#include "Assert1.h"
#include "ItemInfoManager.h"
#include "VolumeInfo.h"
#include "ParkingCenter.h"
#include "ObjectRegistry.h"
#include "ItemUtil.h"
#include "EffectSchedule.h"
#include "Zone.h"
#include "Store.h"
#include "InventoryInfo.h"
#include "Player.h"
#include <map>
#include <stdio.h>

#include "Key.h"
#include "Belt.h"

#include "EffectVampirePortal.h"

#include "GCDeleteInventoryItem.h"
#include "GCCreateItem.h"

////////////////////////////////////////////////////////////////////////////////
//
// CONSTRUCTOR & DESTRUCTOR
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// 기본 생성자
////////////////////////////////////////////////////////////
Inventory::Inventory(CoordInven_t Width, CoordInven_t Height, bool bDeleteAll)
	throw()
{
	__BEGIN_TRY

	m_Owner          = "";
	m_Width          = Width;
	m_Height         = Height;
	m_TotalNum       = 0;
	m_TotalWeight    = 0;
	m_bDeleteAll     = bDeleteAll;
	m_pInventorySlot = NULL;

	m_pInventorySlot = new InventorySlot*[m_Width];
	for (int i=0; i < m_Width ; i ++) 
	{
		m_pInventorySlot[i] = new InventorySlot[m_Height];
	}


	__END_CATCH
}

////////////////////////////////////////////////////////////
// 복사 생성자
////////////////////////////////////////////////////////////
Inventory::Inventory(const Inventory* pInventory)
	throw()
{
	__BEGIN_TRY

	m_Width          = pInventory->getWidth();
	m_Height         = pInventory->getHeight();
	m_TotalNum       = pInventory->getItemNum();
	m_TotalWeight    = pInventory->getWeight();
	m_bDeleteAll     = pInventory->getDeleteAllFlag();
	m_pInventorySlot = NULL;

	m_pInventorySlot = new InventorySlot*[m_Width];
	for (int i=0; i < m_Width ; i ++) 
	{
		m_pInventorySlot[i] = new InventorySlot[m_Height];
	}

	for (int x=0; x<m_Width; x++)
	{
		for (int y=0; y<m_Height; y++)
		{
			Item* pItem = pInventory->getInventorySlot(x, y).getItem();
			if (pItem != NULL) m_pInventorySlot[x][y].addItem(pItem);
		}
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 소멸자
////////////////////////////////////////////////////////////
Inventory::~Inventory()
	throw()
{
	__BEGIN_TRY

	int i, j, k;

	try 
	{
		if (m_pInventorySlot != NULL)
		{
			// 인벤토리에 존재하는 모든 아이템들을 삭제한다.
			// 아이템 크기를 사용하면 좀더 최적화할 수 있을 것이다.
			for (j = 0 ; j < m_Height ; j++) 
			{
				for (i = 0 ; i < m_Width ; i++) 
				{
					Item* pItem = m_pInventorySlot[i][j].getItem();
					if (pItem != NULL) 
					{
						// 인벤토리 슬랏을 NULL 로 지정한다.

						deleteItem(i,j);

						if (m_bDeleteAll)
						{
							// 열쇠일 경우에 ParkingCenter에서 오토바이 정보를 빼낸다음.
							// Zone에서 오토바이를 삭제해주고, ParkingCenter에 오토바이를 삭제한다.
							// 원래 깔끔하게 하기 위해선 GamePlayer 내지는 Creature의 destructor에서
							// 해야하나, 검색 시간의 단축을 위해서 꽁수로 여기서 하도록 한다.
							// 이거 없애믄, 개 된다.
							if (pItem->getItemClass() == Item::ITEM_CLASS_KEY) 
							{
								Key* pKey = dynamic_cast<Key*>(pItem);
								// 걍 간단하게 이안에서 알아서 존에서 지워 주도록 하자.
								if (g_pParkingCenter->hasMotorcycleBox(pKey->getTarget())) 
								{
									g_pParkingCenter->deleteMotorcycleBox(pKey->getTarget());
								}
							}

							SAFE_DELETE(pItem);
						} // end of if (m_bDeleteAll)
					} // end of if (pItem != NULL)
				} // end of for
			} // end of for

			//Assert(m_TotalNum == 0);
			//Assert(m_TotalWeight == 0);
			// 임시로 넣어둔 코드.. 그냥 숫자나 보고 싶어서 - -; by sigi. 2002.5.15
			if (m_TotalNum != 0)
			{
				filelog("inventoryBug.txt", "TotalNum=%d", m_TotalNum);
			}

			Assert(m_TotalNum == 0);

			for (k = 0; k < m_Width; k++) 
			{
				if (m_pInventorySlot[k] != NULL)
				{
					SAFE_DELETE_ARRAY(m_pInventorySlot[k]);
				}
			}

			SAFE_DELETE_ARRAY(m_pInventorySlot);
		}
	} 
	catch (Throwable & t) 
	{ 
		//cerr << t.toString() << endl; 
	}
	
	__END_CATCH
}
 




////////////////////////////////////////////////////////////////////////////////
//
// CHECK METHODS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// 지정된 위치에 아이템이 있는가?
////////////////////////////////////////////////////////////
bool Inventory::hasItem(CoordInven_t X, CoordInven_t Y) const
	throw()
{
	__BEGIN_TRY

	if (X < m_Width && Y < m_Height) 
	{
		InventorySlot& slot = getInventorySlot(X, Y);
		return (slot.getItem() != NULL) ? true : false;
	}
	return false;
	
	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템이 있는가?
////////////////////////////////////////////////////////////
bool Inventory::hasItem(ObjectID_t ObjectID) const
	throw()
{
	__BEGIN_TRY

	CoordInven_t x, y;
	if (findItemOID(ObjectID, x, y) != NULL) return true;
	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템이 있는가?
////////////////////////////////////////////////////////////
bool Inventory::hasItemWithItemID(ItemID_t ItemID) const
	throw()
{
	__BEGIN_TRY

	CoordInven_t x, y;
	if (findItemIID(ItemID, x, y) != NULL) return true;
	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 클래스의 아이템이 있는가?
////////////////////////////////////////////////////////////
bool Inventory::hasItemWithItemClass(Item::ItemClass ItemClass ) const
{
	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getItemClass() == ItemClass )
			{
				return true;
			}
		}
	}

	return false;
}

////////////////////////////////////////////////////////////
// 지정된 타겟을 타겟으로 하는 열쇠를 가지고 있는가?
////////////////////////////////////////////////////////////
bool Inventory::hasKey(ItemID_t TargetItemID) const
	throw()
{
	__BEGIN_TRY

	for (int x = 0; x < m_Width; x++) 
	{
		for (int y = 0; y < m_Height; y++) 
		{
			Item* pSlotItem = m_pInventorySlot[x][y].getItem();

			if (pSlotItem != NULL && pSlotItem->getItemClass() == Item::ITEM_CLASS_KEY) 
			{
				Key* pKey = dynamic_cast<Key*>(pSlotItem);
				if (pKey->getTarget() == TargetItemID) return true;
			}
		}
	}

	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 주어진 위치에 아이템을 더할 수 있는가? 
// 이 함수는 하나는 마우스에 붙일 수 있다고 가정하고 
// 결과를 리턴한다.
////////////////////////////////////////////////////////////
bool Inventory::canAdding(CoordInven_t X, CoordInven_t Y, Item* pItem)
	throw()
{
	__BEGIN_TRY

	// get Volume's Size Width, Height
	VolumeWidth_t  ItemWidth  = pItem->getVolumeWidth();
	VolumeHeight_t ItemHeight = pItem->getVolumeHeight();
	int            ItemCount = 0;
	ObjectID_t     ItemObjectID;

	if ((X+ItemWidth > m_Width) || (Y+ItemHeight > m_Height)) return false;

	for (int x = X; x < X + ItemWidth ; x++) 
	{
		for (int y = Y; y < Y + ItemHeight ; y++) 
		{
			if (hasItem(x, y)) 
			{
				Item*      pTempItem    = m_pInventorySlot[x][y].getItem();
				ObjectID_t TempObjectID = pTempItem->getObjectID();

				if (ItemCount == 0) 
				{
					ItemObjectID = TempObjectID;  
					ItemCount++;
				}
				if (ItemObjectID != TempObjectID) 
				{
					ItemCount++;
				}
			}
		}
	}

	if (ItemCount > 1) return false;

	// if not false return true
	return true;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 주어진 위치에 아이템을 붙일 수 있는가? 
// 이 함수는 마우스에 아이템을 붙일 수 있다고 
// 가정하지 ***않는다.***
////////////////////////////////////////////////////////////
bool Inventory::canAddingEx(CoordInven_t X, CoordInven_t Y, Item* pItem)
	throw()
{
	__BEGIN_TRY

	VolumeWidth_t   ItemWidth     = pItem->getVolumeWidth();
	VolumeHeight_t  ItemHeight    = pItem->getVolumeHeight();
	list<Item*>     prevItemList;

	if ((X+ItemWidth > m_Width) || (Y+ItemHeight > m_Height)) return false;

	// 인벤토리를 검색하면서, 그 자리에 아이템이 있다면,
	// 리스트에 그 아이템이 없는지 검사한 후, 리스트에다 아이템을 집어넣는다.
	for (int x=X; x<X+ItemWidth; x++)
	{
		for (int y=Y; y<Y+ItemHeight; y++)
		{
			Item* pInvenItem = m_pInventorySlot[x][y].getItem();

			// 그 자리에 아이템이 있다면...
			if (pInvenItem != NULL)
			{
				bool bAdd = true;

				// 리스트에 존재하는지 검사
				list<Item*>::iterator itr = prevItemList.begin();
				for (; itr != prevItemList.end(); itr++)
				{
					if (*itr == pInvenItem)
					{
						bAdd = false;
						break;
					}
				}

				// 리스트에다가 아이템을 더한다.
				if (bAdd) prevItemList.push_back(pInvenItem);
			}
		} 
	} 

	// 아이템을 넣으려고 하는 곳에 두 가지 이상의 아이템이 있다면,
	// 아이템을 넣을 수 없다.
	if (prevItemList.size() > 1) return false;

	// 아이템이 하나 있다면 그 아이템은 쌓이는 아이템이어야 하고,
	// 쌓으려는 아이템과 클래스와 타입이 같아야 한다.
	if (prevItemList.size() == 1)
	{
		Item::ItemClass IClass      = pItem->getItemClass();
		ItemType_t      IType       = pItem->getItemType();

		Item*           pInvenItem  = prevItemList.front();
		Item::ItemClass InvenIClass = pInvenItem->getItemClass();
		ItemType_t      InvenIType  = pInvenItem->getItemType();

		// 아이템이 종류가 다른 것이라면 당연히 false닷.
		if (IClass != InvenIClass || IType != InvenIType) return false;
		
		// 쌓일 수 있는 아이템이 아니었다면 당연히 false닷.
		if (!isStackable(pItem)) return false;

		// 갯수를 넘어도 당연히 false닷.
		uint MaxStack = ItemMaxStack[IClass];
		if ((pItem->getNum() + pInvenItem->getNum()) > (int)(MaxStack)) return false;
	}

	prevItemList.clear();

	return true;

	__END_CATCH
}






////////////////////////////////////////////////////////////////////////////////
//
// ADDITION & DELETION RELATED METHODS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// 지정된 위치에 아이템을 더한다.
////////////////////////////////////////////////////////////
bool Inventory::addItem(CoordInven_t X, CoordInven_t Y, Item* pItem)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	if (pItem == NULL)
	{
		//cerr << "Inventory::addItem() : 아이템 포인터가 널입니다." << endl;
		return false;
	}
	
    VolumeWidth_t  ItemWidth  = pItem->getVolumeWidth();
    VolumeHeight_t ItemHeight = pItem->getVolumeHeight();
	Weight_t       ItemWeight = pItem->getWeight();
			
	// 아이템을 더하기 전에 확인을 한다.
	for (int x = X; x < X + ItemWidth ; x++) 
		for (int y = Y; y < Y + ItemHeight ; y++) 
			if (getInventorySlot(x, y).getItem() != NULL) return false;

	// Add Item to Inventory
	for (int x = X; x < X + ItemWidth ; x++) 
	{
		for (int y = Y; y < Y + ItemHeight ; y++) 
		{
			InventorySlot& slot = getInventorySlot(x, y);
			slot.addItem(pItem);
		}
	}
	
	// 아이템 갯수만큼 무게를 더하고, 갯수도 더한다.
	m_TotalWeight += (ItemWeight* pItem->getNum());	
	m_TotalNum    += pItem->getNum();

	return true;

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 위치에 아이템을 더한다.
////////////////////////////////////////////////////////////
Item* Inventory::addItemEx(CoordInven_t X, CoordInven_t Y, Item* pItem)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	if (!canAddingEx(X, Y, pItem)) 
	{
		//cerr << "Inventory::addItemEx() : canAddingExCheck failed!!!" << endl;
		//cerr << toString() << endl;
		throw Error("Inventory::addItemEx() : 아이템을 더할 수 없습니다!");
	}

	VolumeWidth_t   ItemWidth  = pItem->getVolumeWidth();
	VolumeHeight_t  ItemHeight = pItem->getVolumeHeight();
	Item*           pInvenItem = m_pInventorySlot[X][Y].getItem();

	// 아이템이 존재한다면 쌓일 수 있는 아이템이기
	// 때문에, 숫자를 증가시켜 준다.
	if (pInvenItem != NULL)
	{
		pInvenItem->setNum(pItem->getNum()+pInvenItem->getNum());

		// 포인터를 삭제하기에 앞서, 무게와 아이템 숫자를 증가시켜준다.
		m_TotalWeight += (pItem->getWeight()* pItem->getNum());
		m_TotalNum    += pItem->getNum();

		// 인벤토리 아이템의 카운트를 증가시켰으니까, 
		// 더하라고 온 아이템은 삭제해준다.
		// *** 원래는 삭제를 했었는데, 
		// 아무래도 이상해서, 일단은 그냥 놔둔다. ***
		//SAFE_DELETE(pItem);
		//pItem = NULL;
		return pInvenItem;
	}

	for (int x=X; x<X+ItemWidth; x++)
	{
		for (int y=Y; y<Y+ItemHeight; y++)
		{
			// 아이템이 없다면...모든 슬롯에다가 같은 포인터를 할당해 준다.
			m_pInventorySlot[x][y].addItem(pItem);
		}
	}

	m_TotalWeight += (pItem->getWeight()* pItem->getNum());
	m_TotalNum    += pItem->getNum();

	return pItem;

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////
// 아이템을 알아서 더한다.
////////////////////////////////////////////////////////////
bool Inventory::addItem(Item* pItem)
	throw(InventoryFullException , Error)
{
	__BEGIN_TRY

	Assert (pItem != NULL);

	_TPOINT pt;

	if (getEmptySlot(pItem, pt))
	{
		addItem(pt.x, pt.y, pItem);
		return true;
	}

	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 아이템을 알아서 더한다.
////////////////////////////////////////////////////////////
bool Inventory::addItem(Item* pItem, TPOINT& rpt)
	throw(InventoryFullException , Error)
{
	__BEGIN_TRY

	Assert (pItem != NULL);

	_TPOINT pt;

	if (getEmptySlot(pItem, pt))
	{
		rpt.x = pt.x;
		rpt.y = pt.y;
		addItem(pt.x, pt.y, pItem);
		return true;
	}

	rpt.x = 255;
	rpt.y = 255;

	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 아이템을 넣을 수 있는 빈 자리를 찾는다.
////////////////////////////////////////////////////////////
bool Inventory::getEmptySlot(VolumeWidth_t ItemWidth, VolumeHeight_t ItemHeight, _TPOINT& p)
	throw()
{
	__BEGIN_TRY

	int x, y;
	int i, j;

	//---------------------------------------------------------
	// grid의 모든(x,y)에 pItem을 추가할 수 있는지 검사해본다.
	//---------------------------------------------------------
	int yLimit = m_Height - ItemHeight;
	int xLimit = m_Width  - ItemWidth;

	int yPlusHeight, xPlusWidth;

	for (x = 0; x <= xLimit; x++)
	{
		xPlusWidth = x + ItemWidth;

		for (y = 0; y <= yLimit; y++)
		{           
			yPlusHeight = y + ItemHeight;

			//---------------------------------------------------------
			// (x,y)에 넣을 수 있는지 체크..
			//---------------------------------------------------------
			bool bPlace = true;

			for (i = y; bPlace && i < yPlusHeight; i++)
			{
				for (j = x; bPlace && j < xPlusWidth; j++)
				{
					//---------------------------------------------------------
					// 이미 다른 Item이 있는 grid가 하나라도 있다면 추가할 수 없다.
					//---------------------------------------------------------
					Item* pItem = m_pInventorySlot[j][i].getItem();
					if (pItem != NULL)
					{
						bPlace = false;

						// 다음에 체크할 것...
				//		y = i + pItem->getVolumeHeight() - 1;

						break;
					}
				}
			}

			//---------------------------------------------------------
			// (x,y)에 넣을 수 있는 경우
			//---------------------------------------------------------
			if (bPlace)
			{
				p.x = x; 
				p.y = y;

				return true;
			}
		}
	}

	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템을 찾아서 지운다.
////////////////////////////////////////////////////////////
void Inventory::deleteItem(ObjectID_t ObjectID)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Item*        pTargetItem = NULL;
	CoordInven_t x           = 0;
	CoordInven_t y           = 0;

	pTargetItem = findItemOID(ObjectID, x, y);

	if (pTargetItem != NULL)
	{
		deleteItem(x, y);
	}
	else Assert(false);

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 위치에서 아이템을 지운다.
// *** 주의 *** 
// 1x1 아이템이 아닐 경우, 좌측 상단의 좌표를 지정해주지
// 않으면 끔찍한 결과가 발생할 수 있다.
////////////////////////////////////////////////////////////
void Inventory::deleteItem(CoordInven_t X, CoordInven_t Y)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	if (X < m_Width && Y < m_Height)
	{
		Item* pItem = m_pInventorySlot[X][Y].getItem();
		//Assert(pItem != NULL);

		if (pItem != NULL)
		{
			// get Volume's Size Width, Height
			VolumeWidth_t  ItemWidth  = pItem->getVolumeWidth();
			VolumeHeight_t ItemHeight = pItem->getVolumeHeight();

			if (pItem->isOnStore() )
			{
				Store* pStore = pItem->getStore();
				if (pStore != NULL && pStore->hasItem(pItem))
				{
					BYTE index = pStore->getItemIndex(pItem);
					pStore->removeStoreItem(index);
				}
			}

			Assert(ItemWidth != 0);
			Assert(ItemHeight != 0);

			for (int x = X; x < X + ItemWidth ; x++) 
			{
				for (int y = Y; y < Y + ItemHeight ; y++) 
				{
					InventorySlot& slot = getInventorySlot(x, y);

					//if (slot.getItem()==pItem)
					{
						slot.deleteItem();
					}
					/*
					// 다른 문제였다. - -;
					// Restore에서 뱀파이어 아이템 양손 무기를 하나 체크를 안해서 그렇다.
					// by sigi. 2002.8.29 밤
					else
					{
						// 인벤토리에 뭔가 이상한 현상이 있다고 보여지므로
						// 일단 다운 현상을 막기 위해서..
						// 전체를 검색해서 아이템을 지운다.
						// by sigi. 2002.8.29
						filelog("inventoryDeleteBug.txt", "deleteItem(%d, %d): class=%d, type=%d, volume(%d, %d), Wrong Item. (%d, %d) ",
								(int)X, (int)Y, (int)pItem->getItemClass(), (int)pItem->getItemType(), (int)ItemWidth, (int)ItemHeight, (int)x, (int)y);

						// 전체 검색해서 pItem을 지운다.
						for (int a=0; a<m_Width; a++)
						{
							for (int b=0; b<m_Height; b++)
							{
								InventorySlot& tempSlot = getInventorySlot(a, b);

								if (tempSlot.getItem()==pItem)
								{
									slot.deleteItem();

									filelog("inventoryDeleteBug.txt", 
											"delete another position(%d, %d)",
											a, b);
								}
							}
						}
					}
					*/
				}
			}

			m_TotalWeight -= (pItem->getWeight()* pItem->getNum());
			m_TotalNum    -= pItem->getNum();
		}
		else
		{
		}
	}

	__END_DEBUG
	__END_CATCH
}






////////////////////////////////////////////////////////////////////////////////
//
// FIND METHODS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// X, Y로부터 아이템의 크기만큼의 슬랏을 검사하여,
// 존재하는 아이템이 있으면 그 포인터를 리턴한다.
////////////////////////////////////////////////////////////
Item* Inventory::searchItem(CoordInven_t X, CoordInven_t Y, Item* pItem, TPOINT & pt)
	throw()
{
	__BEGIN_TRY

	// get Volume's Size Width, Height
	VolumeWidth_t  ItemWidth  = pItem->getVolumeWidth();
	VolumeHeight_t ItemHeight = pItem->getVolumeHeight();

	if ((X + ItemWidth <= m_Width) && (Y + ItemHeight <= m_Height)) 
	{
		for (int x = X; x < (X + ItemWidth); x++) 
		{
			for (int y = Y; y < (Y + ItemHeight); y++) 
			{
				if (hasItem(x, y)) 
				{
					pt.x = x;
					pt.y = y;
					return m_pInventorySlot[x][y].getItem();
				}
			}
		}
	}

	return NULL;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템을 찾아서 포인터를 리턴한다.
////////////////////////////////////////////////////////////
Item* Inventory::getItemWithItemID (ItemID_t itemID)
	throw(Error)
{
	__BEGIN_TRY

	CoordInven_t x, y;	
	return findItemIID(itemID, x, y);

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 벨트를 찾아서 포인터를 리턴한다.
////////////////////////////////////////////////////////////
Item* Inventory::getBeltWithItemID(ItemID_t itemID)
	throw(Error)
{
	__BEGIN_TRY

	CoordInven_t x, y;
	return findItemIID(itemID, Item::ITEM_CLASS_BELT, x, y);

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템을 찾아서 포인터를 리턴한다.
////////////////////////////////////////////////////////////
Item* Inventory::getItemWithObjectID(ObjectID_t objectID)
	throw(Error)
{
	__BEGIN_TRY

	CoordInven_t x, y;
	return findItemOID(objectID, x, y);

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템을 찾아서 포인터를 리턴한다.
// 이와 함께 그 아이템의 좌측 상단 좌표도 같이 보내준다.
////////////////////////////////////////////////////////////
Item* Inventory::findItemOID(ObjectID_t id, CoordInven_t& X, CoordInven_t& Y) const
	throw()
{
	__BEGIN_TRY

	for (int j=0; j<m_Height; j++)
	{
		for (int i=0; i<m_Width; i++)
		{
			InventorySlot& slot  = getInventorySlot(i, j);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getObjectID() == id)
			{
				X = i;
				Y = j;
				return pItem;
			}
		}
	}
	
	return NULL;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 아이템을 찾아서 포인터를 리턴한다.
// 이와 함께 그 아이템의 좌측 상단 좌표도 같이 보내준다.
////////////////////////////////////////////////////////////
Item* Inventory::findItemIID(ItemID_t id, CoordInven_t& X, CoordInven_t& Y) const
	throw()
{
	__BEGIN_TRY

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getItemID() == id)
			{
				X = x;
				Y = y;
				return pItem;
			}
		}
	}
	
	return NULL;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 id와 클래스로 아이템을 찾아서 포인터를 리턴한다.
// 이와 함께 그 아이템의 좌측 상단 좌표도 같이 보내준다.
////////////////////////////////////////////////////////////
Item* Inventory::findItemOID(ObjectID_t id, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) const
	throw()
{
	__BEGIN_TRY

	for (int j=0; j<m_Height; j++)
	{
		for (int i=0; i<m_Width; i++)
		{
			InventorySlot& slot  = getInventorySlot(i, j);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && 
				pItem->getItemClass() == IClass && pItem->getObjectID() == id)
			{
				X = i;
				Y = j;
				return pItem;
			}
		}
	}
	
	return NULL;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 id와 클래스로 아이템을 찾아서 포인터를 리턴한다.
// 이와 함께 그 아이템의 좌측 상단 좌표도 같이 보내준다.
////////////////////////////////////////////////////////////
Item* Inventory::findItemIID(ItemID_t id, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) const
	throw()
{
	__BEGIN_TRY

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && 
				pItem->getItemClass() == IClass && pItem->getItemID() == id)
			{
				X = x;
				Y = y;
				return pItem;
			}
		}
	}
	
	return NULL;

	__END_CATCH
}

/////////////////////////////////////////////////////////////////////////////////////
// findItem
//    : ItemClass
//  Desctiption: 해당 인벤토리에 특정 Item Class의 아이템이 존재하는 가 체크한다.
//               레어 마스터를 죽였을 경우 나타나는 아이템을 교환하기 위해서 
//               이 사람이 가지고 있는 특정 Item Class의 아이템을 반환한다.
//
//  2002.09.04 장홍창 
/////////////////////////////////////////////////////////////////////////////////////

Item* Inventory::findItem(Item::ItemClass IClass, ItemType_t itemType) const//, CoordInven_t& X, CoordInven_t& Y)
	throw()
{
	__BEGIN_TRY

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && 
				pItem->getItemClass() == IClass 
				&& (itemType==0xFFFF || pItem->getItemType() == itemType))
			{
				//X = x;
				//Y = y;
				return pItem;
			}
		}
	}
	
	return NULL;

	__END_CATCH
}

Item* Inventory::findItem(Item::ItemClass IClass, ItemType_t itemType, CoordInven_t& X, CoordInven_t& Y) const
	throw()
{
	__BEGIN_TRY

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && 
				pItem->getItemClass() == IClass 
				&& (itemType==0xFFFF || pItem->getItemType() == itemType))
			{
				X = x;
				Y = y;
				return pItem;
			}
		}
	}
	
//	X = -1;
//	Y = -1;
	return NULL;

	__END_CATCH
}



////////////////////////////////////////////////////////////////////////////////
//
// ITEM MANIPULATION RELATED METHODS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// 지정된 위치의 아이템 포인터를 리턴한다.
////////////////////////////////////////////////////////////
Item* Inventory::getItem(CoordInven_t X, CoordInven_t Y) const 
	throw()
{
	__BEGIN_TRY

	InventorySlot& slot = getInventorySlot(X, Y);
	return slot.getItem();

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 지정된 위치에 아이템 포인터를 세팅해준다.
////////////////////////////////////////////////////////////
void Inventory::setItem(CoordInven_t X, CoordInven_t Y, Item* pItem)
	throw()
{
	__BEGIN_TRY

	InventorySlot& slot = getInventorySlot(X, Y);
	slot.addItem(pItem);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 
// PACKING RELATED METHODS
// 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// 인벤토리에서 아이템 포인터 모두를 제거한다.
// 실제로 아이템 객체를 지우지는 않는다.
////////////////////////////////////////////////////////////
void Inventory::clear()
	throw()
{
	__BEGIN_TRY

	// 인벤토리 전체를 쭈욱 검색하면서...
	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot = getInventorySlot(x, y);
			slot.deleteItem();
		}
	}

	m_TotalNum    = 0;
	m_TotalWeight = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 인벤토리에 들어있는 아이템을 리스트로 만들어서 리턴한다.
////////////////////////////////////////////////////////////
list<Item*> Inventory::getList() const
	throw()
{
	__BEGIN_TRY

	list<Item*> itemList;

	for (int x=0; x<m_Width; x++)
	{
		for (int y=0; y<m_Height;y++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();
			bool           bAdd  = true;

			// 아이템이 있다면 아이템 리스트에 
			// 이미 들어가 있지는 않은지 체크를 해야 한다.
			if (pItem != NULL)
			{
				// 리스트에 같은 놈이 있는지 체크를 한다.
				list<Item*>::iterator itr = itemList.begin();
				for (; itr != itemList.end(); itr++)
				{
					if (*itr == pItem) 
					{
						bAdd = false;
						break;
					}
				}

				// 리스트에 똑같은 아이템이 없었다면 리스트에다가 더한다.
				if (bAdd)
				{
					itemList.push_back(pItem);
					y += pItem->getVolumeHeight() - 1;
					continue;
				}
			}
		}
	}

	return itemList;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 인벤토리 안에 들어 있는 2x2 아이템의 갯수를 리턴한다.
////////////////////////////////////////////////////////////
int Inventory::calc2x2Item(void) const
	throw()
{
	__BEGIN_TRY

	int rValue = 0;
	list<Item*> itemList = getList();

	list<Item*>::const_iterator itr = itemList.begin();
	for (; itr != itemList.end(); itr++)
	{
		Item* pItem = (*itr);
		if (pItem->getVolumeWidth()  == 2 && 
			pItem->getVolumeHeight() == 2) rValue += 1;
	}

	return rValue;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// MISC METHODS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void Inventory::save(const string& owner) 
	throw()
{
	__BEGIN_TRY

	list<Item*> itemList;

	for (int x=0; x<m_Width; x++)
	{
		for (int y=0; y<m_Height;y++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();
			bool           bAdd  = true;

			// 아이템이 있다면 아이템 리스트에 
			// 이미 들어가 있지는 않은지 체크를 해야 한다.
			if (pItem != NULL)
			{
				// 리스트에 같은 놈이 있는지 체크를 한다.
				list<Item*>::iterator itr = itemList.begin();
				for (; itr != itemList.end(); itr++)
				{
					if (*itr == pItem) 
					{
						bAdd = false;
						break;
					}
				}

				// 리스트에 똑같은 아이템이 없었다면 리스트에다가 더한다.
				// 벨트일 경우에는 Belt::save에서 안에 들어있는 아이템까지
				// 저장하니까, 걱정할 필요없다.
				if (bAdd)
				{
					pItem->save(owner, STORAGE_INVENTORY, 0, x, y);
					itemList.push_back(pItem);
					//y += pItem->getVolumeHeight() - 1;
				}
			}
		}
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
string Inventory::toString () const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "Inventory(" << "\n" << "Owner:" << m_Owner << "\n";

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL)
			{
				msg << pItem->getNum();
			}
		}

		msg << "\n";
	}

	msg << "\n)";

	return msg.toString();

	__END_CATCH
}


///////////////////////////////////////////////////////////////////////////
// XMAS 이벤트를 위해서 만든 색깔별 이벤트 별 숫자 코드이다.
// 2002년 어린이날에 이 코드를 그대로 사용하기 위해서 
// 주석을 해제하고 사용하였다. 
// 단 같은 이벤트가 계속해서 발생할 수 있기 때문에,
// EVENT CODE의 이름을 XMAS가 아니라 STAR_EVENT_CODE로 바꾸는 것을 고려해야
// 할 것이다.
// 
// 2002.5.2 장홍창(changaya@metrotech.co.kr
//
//////////////////////////////////////////////////////////////////////////
//#ifdef __XMAS_EVENT_CODE__
// 인벤토리를 검색하면서 색깔별로 이벤트 별 숫자를 헤아린다.
bool Inventory::hasEnoughStar(const XMAS_STAR& star)
	throw(Error)
{
	__BEGIN_TRY

	int amount[STAR_COLOR_MAX];
	memset(amount, 0, sizeof(int)*STAR_COLOR_MAX);

	for (int i=0; i<STAR_COLOR_MAX; i++)
		amount[i] = 0;

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_STAR)
			{
				int ItemNum =  pItem->getNum();

				switch (pItem->getItemType())
				{
					case 0: amount[STAR_COLOR_BLACK] += ItemNum; break;
					case 1: amount[STAR_COLOR_RED]   += ItemNum; break;
					case 2: amount[STAR_COLOR_BLUE]  += ItemNum; break;
					case 3: amount[STAR_COLOR_GREEN] += ItemNum; break;
					case 4: amount[STAR_COLOR_CYAN]  += ItemNum; break;
					case 5: amount[STAR_COLOR_WHITE] += ItemNum; break;
					case 6: amount[STAR_COLOR_PINK]  += ItemNum; break;
					default: Assert(false); break;
				}
			}
		}
	}

	if (amount[star.color] >= star.amount) return true;

	return false;

	__END_CATCH
}
//#endif

//#ifdef __XMAS_EVENT_CODE__
void Inventory::decreaseStar(const XMAS_STAR& star)
	throw(Error)
{
	__BEGIN_TRY

	// 줄여야 할 양을 기억해 둔다.
	int  amount = star.amount;

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_STAR) {
				ItemType_t IType = pItem->getItemType();

				if ((IType == 0 && star.color == STAR_COLOR_BLACK) ||
					(IType == 1 && star.color == STAR_COLOR_RED)   ||
					(IType == 2 && star.color == STAR_COLOR_BLUE)  ||
					(IType == 3 && star.color == STAR_COLOR_GREEN) ||
					(IType == 4 && star.color == STAR_COLOR_CYAN)  ||
					(IType == 5 && star.color == STAR_COLOR_WHITE) ||
					(IType == 6 && star.color == STAR_COLOR_PINK)) {
					int ItemNum = pItem->getNum();

					// 아이템의 스택 숫자가 줄여야 할 양보다 작거나 같다면,
					// 아이템을 삭제해야 한다.
					if (ItemNum <= amount) {
						m_TotalWeight -= (pItem->getWeight() * ItemNum);
						m_TotalNum -= ItemNum;

						// 아이템이 삭제된만큼 지워야 할 양도 줄여줘야 한다. 
						amount = amount - ItemNum;

						// 아이템을 삭제해준다.
						deleteItem(x, y);
						pItem->destroy();
						SAFE_DELETE(pItem);
					}
					else
					{
						m_TotalWeight -= (pItem->getWeight() * amount);
						m_TotalNum -= amount;

						pItem->setNum(ItemNum - amount);
						pItem->save(m_Owner, STORAGE_INVENTORY, 0, x, y);

						// 아이템이 삭제된만큼 지워야 할 양도 줄여줘야 한다. 
						amount = 0;
					}

					// 줄여야 할 양이 0이 되었다면 리턴한다.
					if (amount == 0) return;
				}
			}
		}
	}

	// 정상적인 처리 순서라면 이 곳까지 오면 안 된다.
	Assert(false);

	__END_CATCH
}
//#endif


///*
//#ifdef __XMAS_EVENT_CODE__
bool Inventory::hasRedGiftBox(void) 
	throw(Error)
{
	__BEGIN_TRY

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() == 1)
			{
				return true;

				// 선물 상자의 크기가 2x2이기 때문에,
				// x를 하나 더 더해준다.
				x += 1;
			}
		}
	}

	return false;

	__END_CATCH
}
//#endif
//*/

///*
//#ifdef __XMAS_EVENT_CODE__
bool Inventory::hasGreenGiftBox(void) 
	throw(Error)
{
	__BEGIN_TRY

	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX && pItem->getItemType() == 0)
			{
				return true;

				// 선물 상자의 크기가 2x2이기 때문에,
				// x를 하나 더 더해준다.
				x += 1;
			}
		}
	}

	return false;

	__END_CATCH
}
//#endif
//*/
bool Inventory::hasEnoughNumItem(Item::ItemClass itemClass, ItemType_t itemType, int num )
{
	int amount = 0;
	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL
				&& pItem->getItemClass() == itemClass
				&& pItem->getItemType() == itemType
			   )
			{
				amount +=  pItem->getNum();
			}
		}
	}

	if (amount >= num )
		return true;

	return false;
}

void Inventory::decreaseNumItem(Item::ItemClass itemClass, ItemType_t itemType, int num, Player* pPlayer )
{
	int amount = num;
	for (int y=0; y<m_Height; y++)
	{
		for (int x=0; x<m_Width; x++)
		{
			InventorySlot& slot  = getInventorySlot(x, y);
			Item*          pItem = slot.getItem();

			if (pItem != NULL
				&& pItem->getItemClass() == itemClass
				&& pItem->getItemType() == itemType
			   )
			{
				int itemNum =  pItem->getNum();

				if (itemNum <= amount )
				{
					// 아이템을 지운다.
					deleteItem(pItem->getObjectID());

					// 클라이언트에 알린다.
					GCDeleteInventoryItem gcDeleteInventoryItem;
					gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
					pPlayer->sendPacket(&gcDeleteInventoryItem);

					// 메모리및 DB 에서 삭제
					pItem->destroy();
					SAFE_DELETE(pItem);

					amount -= itemNum;
				}
				else
				{
					// 아이템 갯수를 줄인다.
					pItem->setNum(itemNum - amount);
					decreaseItemNum(amount);
					decreaseWeight(pItem->getWeight() * amount);

					// 클라이언트에 알린다.
					GCDeleteInventoryItem gcDeleteInventoryItem;
					gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
					pPlayer->sendPacket(&gcDeleteInventoryItem);

					GCCreateItem gcCreateItem;
					gcCreateItem.setObjectID(pItem->getObjectID());
					gcCreateItem.setItemClass(pItem->getItemClass());
					gcCreateItem.setItemType(pItem->getItemType());
					gcCreateItem.setItemNum(pItem->getNum());
					gcCreateItem.setInvenX((CoordInven_t)x);
					gcCreateItem.setInvenY((CoordInven_t)y);
					pPlayer->sendPacket(&gcCreateItem);

					// DB에 저장
					char pField[80];
					sprintf(pField, "Num=%d", pItem->getNum());
					pItem->tinysave(pField);

					amount = 0;
				}

				if (amount == 0 )
				{
					return;
				}
			}
		}
	}

	Assert(false);
}

void Inventory::clearQuestItem(list<Item*>& iList) throw(Error)
{
	{
		list<Item*> ItemList;
		int height = getHeight();
		int width  = getWidth();

		for (int j=0; j<height; j++)
		{
			for (int i=0; i<width; i++)
			{
				Item* pItem = getItem(i, j);
				if (pItem != NULL)
				{
					// 체크된 아이템의 리스트에서 현재 아이템을 찾는다.
					list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

					if (itr == ItemList.end())
					{
						i += pItem->getVolumeWidth() - 1;

						if (pItem->isQuestItem() )
						{
							deleteItem(pItem->getObjectID());
							iList.push_back(pItem);
						}
						else
						{
							// 리스트에 아이템이 없으면
							// 같은 아이템을 두번 체크하지 않기 위해서
							// 리스트에다가 아이템을 집어넣는다.
							ItemList.push_back(pItem);
						}
					}
				}
			}
		}
	}
}

InventoryInfo* Inventory::getInventoryInfo() const
{
	__BEGIN_TRY

	BYTE ItemCount = 0;

	InventoryInfo* pInventoryInfo = new InventoryInfo();
	list<Item*> ItemList;

	for (int j = 0; j < m_Height; j++) 
	{
		for (int i = 0 ; i < m_Width ; i++) 
		{
			if (hasItem(i, j)) 
			{
				Item* pItem = getItem(i , j);
				VolumeWidth_t ItemWidth = pItem->getVolumeWidth();
//				Item::ItemClass IClass = pItem->getItemClass();

				list<Item*>::iterator itr = find(ItemList.begin() , ItemList.end() , pItem);

				if (itr == ItemList.end()) 
				{
					// map 에 Item을 등록시켜 놓음,
					// 다음 비교때 같은 아이템인지 확인하기 위하여.
					ItemList.push_back(pItem);

					InventorySlotInfo* pInventorySlotInfo = new InventorySlotInfo();
					pItem->makePCItemInfo(*pInventorySlotInfo);
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);

					pInventoryInfo->addListElement(pInventorySlotInfo);
					ItemCount++;
					i = i + ItemWidth - 1;
				}
			}
		}
	}

	pInventoryInfo->setListNum(ItemCount);
	pInventoryInfo->setWidth(m_Width);
	pInventoryInfo->setHeight(m_Height);

	return pInventoryInfo;

	__END_CATCH
}
