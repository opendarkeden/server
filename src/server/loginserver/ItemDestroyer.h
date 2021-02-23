//--------------------------------------------------------------------------------
// 
// Filename   : ItemDestroyer.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __ITEM_DESTROYER_H__
#define __ITEM_DESTROYER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "database/DB.h"

class ItemDestroyer {

public :

	// constructor
	ItemDestroyer () throw ();

	// destroy all item whose owner is ...
	void destroyAll ( const string & ownerID ) throw ( Error );

};

// global variable declaration
extern ItemDestroyer * g_pItemDestroyer;

#endif
