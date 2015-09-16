//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemLoaderManager.h
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_LOADER_MANAGER_H__
#define __ITEM_LOADER_MANAGER_H__

#include "Types.h"
#include "Item.h"
#include "ItemLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class ItemLoaderManager;
//////////////////////////////////////////////////////////////////////////////

class Slayer;
class Vampire;
class Ousters;
class Zone;

class ItemLoaderManager 
{
public:
	ItemLoaderManager() throw();
	~ItemLoaderManager() throw();

public:
	void init() throw(Error);

	void load(Slayer* pSlayer) throw(Error);
	void load(Vampire* pVampire) throw(Error);
	void load(Ousters* pOusters) throw(Error);
	void load(Zone* pZone) throw(Error);

	string toString() const throw();

private:
	ItemLoader* m_pItemLoaders[Item::ITEM_CLASS_MAX];

};

extern ItemLoaderManager* g_pItemLoaderManager;

#endif
