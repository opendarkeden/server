//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemRack.h
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEMRACK_H__
#define __ITEMRACK_H__

#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class ItemRack
//////////////////////////////////////////////////////////////////////////////

class Item;

class ItemRack
{
public: 
	ItemRack();
	ItemRack(int size);
	virtual ~ItemRack();

public:
	void  init(int size);
	bool  isEmpty(void) const;
	bool  isFull(void) const;

	bool  isExist(BYTE index) const;
	void  insert(BYTE index, Item* pItem);
	void  remove(BYTE index);
	Item* get(BYTE index);
	void  clear(void);

	BYTE  getFirstEmptySlot(void) const;
	BYTE  getLastEmptySlot(void) const;

	bool  verifyIndex(BYTE index) const;

protected:
	int    m_nSize;
	Item** m_ppItem;
};

#endif


