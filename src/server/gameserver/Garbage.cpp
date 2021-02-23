//////////////////////////////////////////////////////////////////////////////
// Filename    : Garbage.cpp
// Written by  : excel96
// Description :
// 서버 DB 오류 같은 것으로 인해, 유저의 아이템이 사라질 위기에 처했을 
// 경우에 들어가게 되는 storage의 하나다.
//////////////////////////////////////////////////////////////////////////////

#include "Garbage.h"
#include "Item.h"
#include "DB.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class Garbage member methods
//////////////////////////////////////////////////////////////////////////////

Garbage::Garbage()
{
}

Garbage::~Garbage()
{
	list<Item*>::iterator itr = m_Items.begin();
	for (; itr != m_Items.end(); itr++)
	{
		Item* pItem = *itr;
		SAFE_DELETE(pItem);
	}

	m_Items.clear();
}

void Garbage::addItem(Item* pItem)
{
	m_Items.push_back(pItem);
}

void Garbage::addItemEx(Item* pItem, const string& OwnerID)
{
	m_Items.push_back(pItem);
	pItem->save(OwnerID, STORAGE_GARBAGE, 0, 0, 0);
}

Item* Garbage::popItem(void)
{
	if (!m_Items.empty())
	{
		Item* pItem = m_Items.front();
		m_Items.pop_front();
		return pItem;
	}

	return NULL;
}

void Garbage::save(const string& OwnerID)
{
	list<Item*>::iterator itr = m_Items.begin();
	for (; itr != m_Items.end(); itr++)
	{
		Item* pItem = *itr;
		pItem->save(OwnerID, STORAGE_GARBAGE, 0, 0, 0);
	}
}

void Garbage::registerObject(ObjectRegistry& OR)
{
	list<Item*>::iterator itr = m_Items.begin();
	for (; itr != m_Items.end(); itr++)
	{
		Item* pItem = *itr;
		OR.registerObject_NOLOCKED(pItem);
	}
}
