////////////////////////////////////////////////////////////////////////////////
// Filename : ItemMap.h
// Written by : 김성민
// Description : 
// 클라이언트에서 가져온 소트된 아이템의 맵이다.
////////////////////////////////////////////////////////////////////////////////

#include "ItemMap.h"
#include "Inventory.h"
#include "Item.h"

#define TWO_BY_TWO_PACKING_SIZE 12

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
ItemMap::ItemMap() 
	
{
	__BEGIN_TRY

	m_Num2x2     = 0;
	m_Num2x2Temp = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 아이템 객체 자체를 지우기를 원하지 않는다면,
// 반드시 clearAll()를 호출한 후에 부를 것.
////////////////////////////////////////////////////////////
ItemMap::~ItemMap()
	
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 향상된 정렬을 위해 사용하는 2x2 아이템의 갯수 세팅
////////////////////////////////////////////////////////////
void ItemMap::set2x2(int n) 
	
{
	__BEGIN_TRY

	// 2x2 아이템이 3개가 있을 경우, 
	// 우선 순위가 제일 높다. 그래서 3개 단위로
	// 변수 값을 세팅해준다.
	m_Num2x2 = n;
	m_Num2x2Temp = (n/3)*3;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// 아이템을 맵에다 더한다.
////////////////////////////////////////////////////////////
bool ItemMap::addItem(Item* pItem)
	
{
	__BEGIN_TRY

	ulonglong key = getKey(pItem);

	ITEM_MAP::const_iterator itr = find(key);
	
	if (itr == end()) // 없으면 추가한다.
	{
		insert(ITEM_MAP::value_type(key, pItem));
		return true;
	}

	return false;

	__END_CATCH
}


////////////////////////////////////////////////////////////
// 아이템을 정렬하기 위한 키를 만든다.
//
// key는 8 byte이고 상위byte부터..
//
// 4 Byte : gridWidth* gridHeight
// 4 Byte : ObjectID
//
// 로 표현된다.
////////////////////////////////////////////////////////////
ulonglong ItemMap::getKey(Item* pItem)
	
{
	__BEGIN_TRY

	ObjectID_t objectID   = pItem->getObjectID();
	int        gridWidth  = pItem->getVolumeWidth();
	int        gridHeight = pItem->getVolumeHeight();
	int        gridSize   = gridWidth* gridHeight;

	// 2x2 아이템을 땜빵으로 우선순위를 제일 높게 해준다.
	if (gridSize == 4)
	{
		if (m_Num2x2Temp > 0)
		{
			m_Num2x2Temp--;
			gridSize = TWO_BY_TWO_PACKING_SIZE;
		}
	}

	gridSize = 0xFF - gridSize;

	ulonglong  key = gridSize;
	key = (key << 32) | objectID;

	return key;

	__END_CATCH
}

