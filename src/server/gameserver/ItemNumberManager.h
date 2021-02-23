//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemNumberManager.h
// Written By  : ½­
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_NUMBER_MANAGER_H__
#define __ITEM_NUMBER_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class NUMBER_INFO
//////////////////////////////////////////////////////////////////////////////
class NUMBER_INFO
{
public :
	NUMBER_INFO() : m_bLimitNumber(false), m_MaxNumber(0xFFFFFFFF), m_CurrentNumber(0)
	{
	}

	void		setCurrent(DWORD currentNumber)	{ m_CurrentNumber = currentNumber; }
	void		setLimit(DWORD maxNumber)		{ m_bLimitNumber = true; m_MaxNumber = maxNumber; }
	void		removeLimit() 					{ m_bLimitNumber = false; m_MaxNumber = 0xFFFFFFFF; m_CurrentNumber = 0; }

	bool		hasLimit() const	{ return m_bLimitNumber; }	
	DWORD		getCurrent() const	{ return m_CurrentNumber; }	
	DWORD		getLimit() const	{ return m_MaxNumber; }	

private :
	bool 		m_bLimitNumber;
	DWORD		m_MaxNumber;	
	DWORD		m_CurrentNumber;	
};

//////////////////////////////////////////////////////////////////////////////
// Class ItemNumberManager
//////////////////////////////////////////////////////////////////////////////

class ItemNumberManager 
{
public:
	ItemNumberManager() throw();
	~ItemNumberManager() throw();

public:
	void 	init() throw(Error);
	NUMBER_INFO* getItemNumber(Item::ItemClass Class, ItemType_t ItemType) const throw();
	{
		return m_ItemNumberInfos[Class][ItemType];
	}

	string toString() const throw();

private:
	vector<NUMBER_INFO*> 	m_ItemNumberInfos[Item::ITEM_CLASS_MAX];
};

extern ItemNumberManager* g_pItemNumberManager;

#endif

ItemNumberManager::ItemNumberManager() 
	throw()
{
}

ItemNumberManager::~ItemNumberManager() 
	throw()
{
}

void ItemNumberManager::init() 
	throw(Error)
{
	for (int i=0; i<Item::ITEM_CLASS_MAX; i++)
	{
		m_ItemNumberInfos[i] 
	}

}
int 	getItemNumber(Item::ItemClass Class, ItemType_t ItemType) const throw(Error);

string toString() const throw();

bool			m_bLimitNumber[Item::ITEM_CLASS_MAX];
vector<int> 	m_ItemNumber[Item::ITEM_CLASS_MAX];

