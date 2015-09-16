//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMap.h
// Written by  : 김성민
// Description : 
// 클라이언트에서 가져온 소트된 아이템의 맵이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_MAP__
#define __ITEM_MAP__

#include "Item.h"
#include <map>
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class ItemMap
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

class ItemMap : public std::map<ulonglong, Item*> 
{
// Inner type definition
public:
	typedef std::map<ulonglong, Item*> ITEM_MAP;
	typedef ITEM_MAP::iterator         iterator;
	typedef ITEM_MAP::const_iterator   const_iterator;

// Member methods
public:
	ItemMap() throw();
	~ItemMap() throw();

public:
	// 모든 자료들을 날린다.
	void clearAll(void) throw() { clear(); m_Num2x2 = 0; m_Num2x2Temp = 0;}

	// 아이템을 더한다.
	bool addItem(Item* pItem) throw();

	// 2x2 아이템의 갯수를 세팅해 준다.
	void set2x2(int n) throw();
	int  get2x2() const throw() { return m_Num2x2; }

protected:
	// 아이템을 맵에 넣기 위해 키를 구한다.
	ulonglong getKey(Item* pItem) throw();

// Member data
protected:
	int m_Num2x2;
	int m_Num2x2Temp; // 임시 - GetKey에서 필수

};




#endif
