#include "TimeLimitItemManager.h"
#include "DB.h"
#include "Item.h"
#include "PlayerCreature.h"

#include "Gpackets/GCTimeLimitItemInfo.h"

TimeLimitItemManager::~TimeLimitItemManager()
{
	TableRecordList::iterator itr = m_TableRecords.begin();

	for ( ; itr != m_TableRecords.end() ; ++itr )
	{
		SAFE_DELETE( *itr );
	}

	m_TableRecords.clear();
	m_ItemTimeLimits.clear();
	m_loaded = false;
}

void TimeLimitItemManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT ItemClass, ItemID, LimitDateTime from TimeLimitItems where OwnerID='%s' and Status=%u",
				m_pOwnerPC->getName().c_str(), (uint)VALID );

		while( pResult->next() )
		{
			TableRecord* pTableRecord = new TableRecord;

			pTableRecord->m_ItemClass	= (Item::ItemClass)pResult->getInt(1);
			pTableRecord->m_ItemID		= pResult->getInt(2);

			const string limitDateTime	= pResult->getString(3);
			pTableRecord->m_TimeLimit	= VSDateTime( limitDateTime );

			m_TableRecords.push_back( pTableRecord );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	m_loaded = true;

	__END_CATCH
}

// 아이템을 테이블과 비교해서 오브젝트 아이디를 등록해준다.
// true 가 리턴될 경우 오브젝트 아이디가 등록된다.
// false 가 리턴될 경우 오브젝트가 아이디가 등록되지 않으므로 m_ItemTimeLimits[pItem->ObjectID()] 는
// 예외가 발생한다.
bool TimeLimitItemManager::registerItem( Item* pItem )
	throw(Error)
{
	__BEGIN_TRY

	if ( m_ItemTimeLimits.find( pItem->getObjectID() ) != m_ItemTimeLimits.end() ) return false;

	TableRecordList::iterator itr = m_TableRecords.begin();
	TableRecordList::iterator endItr = m_TableRecords.end();

	for ( ; itr != endItr ; ++itr )
	{
		TableRecord* pTableRecord = *itr;
		if ( pTableRecord != NULL )
		{
			if ( pTableRecord->m_ItemClass == pItem->getItemClass()
			&&	pTableRecord->m_ItemID == pItem->getItemID() )
			{
				m_ItemTimeLimits[ pItem->getObjectID() ] = pTableRecord->m_TimeLimit;
				pItem->setTimeLimitItem();
				return true;
			}
		}
	}

	return false;

	__END_CATCH
}

bool TimeLimitItemManager::checkTimeLimit( Item* pItem )
	throw(Error)
{
	__BEGIN_TRY

	Assert( m_loaded );

	ObjectID_t	objectID = pItem->getObjectID();

	ItemTimeLimitMap::iterator itr = m_ItemTimeLimits.find( objectID );

	if ( itr == m_ItemTimeLimits.end() )
	{
		if ( !registerItem( pItem ) )
		{
			// 시간제한 아이템이 아니다.
			// 즉 시간제한 무제한이다. ㅎㅎ
			return true;
		}
	}

	VSDateTime currentTime = VSDateTime::currentDateTime();
	if ( currentTime > m_ItemTimeLimits[ objectID ] )
	{
		cout << pItem->toString() << " 시간제한 초과 : " << currentTime.toString() << " > " << m_ItemTimeLimits[ objectID ].toString() << endl;
		// 시간 제한이 지났다.
		return false;
	}

	return true;

	__END_CATCH
}

bool TimeLimitItemManager::wasteIfTimeOver( Item* pItem )
	throw(Error)
{
	__BEGIN_TRY

	if ( checkTimeLimit( pItem ) ) return false;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"UPDATE TimeLimitItems SET Status=%u where OwnerID='%s' and ItemClass=%u and ItemID=%u",
				(uint)EXPIRED, m_pOwnerPC->getName().c_str(), (uint)pItem->getItemClass(), (uint)pItem->getItemID() );

		if ( pStmt->getAffectedRowCount() == 0 ) 
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return true;

	__END_CATCH
}

bool TimeLimitItemManager::makeTimeLimitItemInfo( GCTimeLimitItemInfo& gcTLII ) const
	throw(Error)
{
	__BEGIN_TRY

	Assert( m_loaded );

	if ( m_ItemTimeLimits.empty() ) return false;

//	gcTLII.clear();

	VSDateTime currentTime = VSDateTime::currentDateTime();
	ItemTimeLimitMap::const_iterator itr = m_ItemTimeLimits.begin();
	ItemTimeLimitMap::const_iterator endItr = m_ItemTimeLimits.end();
	
	for ( ; itr != endItr ; ++itr )
	{
		int diffSecs = currentTime.secsTo( itr->second );

		if ( diffSecs < 0 ) diffSecs = 0;

		gcTLII.addTimeLimit( itr->first, diffSecs );
	}
	
	return true;

	__END_CATCH
}

bool TimeLimitItemManager::updateItemTimeLimit( Item* pItem, DWORD time ) throw(Error)
{
	__BEGIN_TRY

	if ( pItem->getCreateType() != Item::CREATE_TYPE_TIME_EXTENSION ) return false;
	if ( !changeStatus( pItem, EXTENDED ) ) return false;
	addTimeLimitItem( pItem, time );
	return true;

	__END_CATCH
}

// 반드시 존에 아이템을 등록한 후에 호출해야 한다.
void TimeLimitItemManager::addTimeLimitItem( Item* pItem, DWORD time )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pItem != NULL );
	Assert( time != 0 );

	VSDateTime timeLimit = VSDateTime::currentDateTime().addSecs(time);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"INSERT INTO TimeLimitItems (OwnerID, ItemClass, ItemID, LimitDateTime) VALUES ('%s',%u,%u,'%s')",
				m_pOwnerPC->getName().c_str(), (uint)pItem->getItemClass(), (uint)pItem->getItemID(), timeLimit.toDateTime().c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	TableRecord* pTableRecord = new TableRecord;

	pTableRecord->m_ItemClass = pItem->getItemClass();
	pTableRecord->m_ItemID = pItem->getItemID();
	pTableRecord->m_TimeLimit = timeLimit;

	m_TableRecords.push_back( pTableRecord );

	registerItem( pItem );

	__END_CATCH
}

// 메모리에 있는 애는 일단 아직 시간이 남은 넘이다.
bool TimeLimitItemManager::changeStatus( Item* pItem, TimeLimitStatus status ) throw(Error)
{
	__BEGIN_TRY

	Assert( status != VALID );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"UPDATE TimeLimitItems SET Status=%u where OwnerID='%s' and ItemClass=%u and ItemID=%u",
				(uint)status, m_pOwnerPC->getName().c_str(), (uint)pItem->getItemClass(), (uint)pItem->getItemID() );

		if ( pStmt->getAffectedRowCount() == 0 ) 
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	TableRecordList::iterator itr = m_TableRecords.begin();
	TableRecordList::iterator endItr = m_TableRecords.end();

	bool erased = false;

	for ( ; itr != endItr ; ++itr )
	{
		if ( (*itr)->m_ItemClass == pItem->getItemClass() && (*itr)->m_ItemID == pItem->getItemID() )
		{
			m_TableRecords.erase( itr );
			erased = true;
			break;
		}
	}

	if ( !erased ) 
		filelog( "QuestItem.log", "[%u,%u] : 시간제한 아이템을 테이블에서 지웠는데 메모리에 없습니다.",
			(uint)pItem->getItemClass(), (uint)pItem->getItemID() );

	// 위험 -_- ObjectID..... 0이면 뻑난다. 아이템 팔 때는 존 안에 있을때만 부르니까 일단 0일 리가 없다.
	ItemTimeLimitMap::iterator itr2 = m_ItemTimeLimits.find( pItem->getObjectID() );
	
	if ( itr2 != m_ItemTimeLimits.end() )
	{
		m_ItemTimeLimits.erase( itr2 );
	}
	else
	{
		filelog( "QuestItem.log", "[%u,%u] : Item Time Limit Map 에도 없습니다.", 
			(uint)pItem->getItemClass(), (uint)pItem->getItemID() );
	}

	return true;

	__END_CATCH
}

