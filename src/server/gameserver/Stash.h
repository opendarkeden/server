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
	Stash() ;
	virtual ~Stash() ;

public: // public methods
	bool  isExist(BYTE rack, BYTE index) const ;
	void  insert(BYTE rack, BYTE index, Item* pItem) ;
	void  remove(BYTE rack, BYTE index) ;
	Item* get(BYTE rack, BYTE index) ;
	void  clear(void) ;

	BYTE getFirstEmptySlot(BYTE rack) const ;
	BYTE getLastEmptySlot(BYTE rack) const ;

///// Member data /////

protected:
	int       m_nSize;
	ItemRack* m_pRack;

};

#endif

