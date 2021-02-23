#ifndef __TIME_LIMIT_ITEM_MANAGER_H__
#define __TIME_LIMIT_ITEM_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "VSDateTime.h"
#include "Item.h"

#include <string>
#include <hash_map>
#include <list>

class GCTimeLimitItemInfo;
class PlayerCreature;

class TimeLimitItemManager
{
private:
	class TableRecord
	{
	public:
		Item::ItemClass	m_ItemClass;
		ItemID_t		m_ItemID;
		VSDateTime		m_TimeLimit;
	};
	typedef list<TableRecord*> TableRecordList;

	enum TimeLimitStatus
	{
		VALID = 0,
		EXPIRED,
		SOLD,
		MORPH,
		EXTENDED
	};

public:
	typedef hash_map<ObjectID_t,VSDateTime> ItemTimeLimitMap;

public:
	TimeLimitItemManager( PlayerCreature* pOwner ) { m_pOwnerPC = pOwner; m_ItemTimeLimits.clear(); m_TableRecords.clear(); }
	~TimeLimitItemManager();

public:
	void		load() throw(Error);

	bool		makeTimeLimitItemInfo( GCTimeLimitItemInfo& gcTimeLimitItemInfo ) const throw(Error);
	bool		registerItem( Item* pItem ) throw(Error);
	bool		checkTimeLimit( Item* pItem ) throw(Error);
	bool		wasteIfTimeOver( Item* pItem ) throw(Error);
	bool		itemSold( Item* pItem ) throw(Error) { return changeStatus( pItem, SOLD ); }
	bool		deleteItemByMorph( Item* pItem ) throw(Error) { return changeStatus( pItem, MORPH ); }
	bool		updateItemTimeLimit( Item* pItem, DWORD time ) throw(Error);

	void		clear() throw(Error) { m_ItemTimeLimits.clear(); }

	void		addTimeLimitItem( Item* pItem, DWORD time ) throw(Error);

protected:
	bool		changeStatus( Item* pItem, TimeLimitStatus status ) throw(Error);

private:
	PlayerCreature*		m_pOwnerPC;

	ItemTimeLimitMap	m_ItemTimeLimits;
	TableRecordList		m_TableRecords;

	bool	m_loaded;
};

#endif// __TIME_LIMIT_ITEM_MANAGER_H__
