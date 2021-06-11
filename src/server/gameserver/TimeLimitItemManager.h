#ifndef __TIME_LIMIT_ITEM_MANAGER_H__
#define __TIME_LIMIT_ITEM_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "VSDateTime.h"
#include "Item.h"

#include <string>
#include <unordered_map>
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
	typedef unordered_map<ObjectID_t,VSDateTime> ItemTimeLimitMap;

public:
	TimeLimitItemManager( PlayerCreature* pOwner ) { m_pOwnerPC = pOwner; m_ItemTimeLimits.clear(); m_TableRecords.clear(); }
	~TimeLimitItemManager();

public:
	void		load() ;

	bool		makeTimeLimitItemInfo( GCTimeLimitItemInfo& gcTimeLimitItemInfo ) const ;
	bool		registerItem( Item* pItem ) ;
	bool		checkTimeLimit( Item* pItem ) ;
	bool		wasteIfTimeOver( Item* pItem ) ;
	bool		itemSold( Item* pItem )  { return changeStatus( pItem, SOLD ); }
	bool		deleteItemByMorph( Item* pItem )  { return changeStatus( pItem, MORPH ); }
	bool		updateItemTimeLimit( Item* pItem, DWORD time ) ;

	void		clear()  { m_ItemTimeLimits.clear(); }

	void		addTimeLimitItem( Item* pItem, DWORD time ) ;

protected:
	bool		changeStatus( Item* pItem, TimeLimitStatus status ) ;

private:
	PlayerCreature*		m_pOwnerPC;

	ItemTimeLimitMap	m_ItemTimeLimits;
	TableRecordList		m_TableRecords;

	bool	m_loaded;
};

#endif// __TIME_LIMIT_ITEM_MANAGER_H__
