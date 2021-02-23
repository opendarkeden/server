#ifndef __GLOBAL_ITEM_POSITION_LOADER_H__
#define __GLOBAL_ITEM_POSITION_LOADER_H__

#include "Item.h"
#include "Types.h"
#include "GlobalItemPosition.h"

class GlobalItemPositionLoader
{
private:
	class GlobalDBItemPosition
	{
	public:
		string		OwnerID;
		Storage		ItemStorage;
		StorageID_t	StorageID;
		WORD		X;
		WORD		Y;
		ObjectID_t	ObjectID;
	};
public:
	GlobalItemPosition*		load( Item::ItemClass itemClass, ItemID_t itemID) throw(Error);
	GlobalItemPosition*		makeGlobalItemPosition( GlobalDBItemPosition& gip ) throw(Error);

	static GlobalItemPositionLoader* getInstance()
	{
		static GlobalItemPositionLoader globalItemPositionLoader;
		return &globalItemPositionLoader;
	}

private:
	GlobalItemPositionLoader() {}
};

#endif
