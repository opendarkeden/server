//////////////////////////////////////////////////////////////////////
// Filename    : Stash.h
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////

#ifndef __STASH_H__
#define __STASH_H__

#include "Types.h"


//////////////////////////////////////////////////////////////////////
// class Stash
//////////////////////////////////////////////////////////////////////

class Item;
class ItemRack;

class Stash
{

///// Member methods /////

public: // constructor & destructor
	Stash() throw();
	virtual ~Stash() throw();

public: // public methods
	bool  isExist(BYTE rack, BYTE index) const throw();
	void  insert(BYTE rack, BYTE index, Item* pItem) throw();
	void  remove(BYTE rack, BYTE index) throw();
	Item* get(BYTE rack, BYTE index) throw();
	void  clear(void) throw();

	BYTE getFirstEmptySlot(BYTE rack) const throw();
	BYTE getLastEmptySlot(BYTE rack) const throw();

///// Member data /////

protected:
	int       m_nSize;
	ItemRack* m_pRack;

};

#endif

