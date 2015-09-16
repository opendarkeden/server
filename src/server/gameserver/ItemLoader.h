//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemLoader.h
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_LOADER_H__
#define __ITEM_LOADER_H__

#include "Types.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ItemLoader;
//////////////////////////////////////////////////////////////////////////////

class Creature;
class Zone;
class Inventory;

class ItemLoader 
{
public:
	virtual ~ItemLoader() {}

public:
	// get item class
	virtual Item::ItemClass getItemClass() const throw() = 0;

	// get item class name
	virtual string getItemClassName() const throw() = 0;

	// load to creature
	virtual void load(Creature* pCreature) throw(Error) = 0;

	// load to zone
	virtual void load(Zone* pZone) throw(Error) = 0;

	// load to inventory
	virtual void load(DWORD StorageID, Inventory* pInventory) throw(Error) = 0;

};

#endif
