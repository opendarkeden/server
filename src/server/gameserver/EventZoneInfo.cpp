#include "EventZoneInfo.h"
#include "Zone.h"
#include "PCManager.h"
#include "ZoneUtil.h"
#include "DB.h"

EventZoneInfo::EventZoneInfo( WORD eventID, ZoneID_t zoneID )
	: m_EventID( eventID )
{
	m_pZone = getZoneByZoneID( zoneID );
	Assert( m_pZone != NULL );
}

ZoneID_t EventZoneInfo::getZoneID() const
{
	return m_pZone->getZoneID();
}

bool EventZoneInfo::canEnter() const
{
	if ( !isEventOn() ) return false;

	const PCManager* pPCManager = m_pZone->getPCManager();
	if ( pPCManager->getSize() >= m_PCLimit ) return false;

	return true;
}

EventZoneInfo* ZoneEventInfo::getEventZoneInfo( ZoneID_t zoneID ) const
{
	hash_map<ZoneID_t, EventZoneInfo*>::const_iterator itr = m_EventZoneInfos.find( zoneID );

	if ( itr == m_EventZoneInfos.end() ) return NULL;
	return itr->second;
}

void ZoneEventInfo::addEventZoneInfo( EventZoneInfo* pEventZoneInfo )
{
	m_EventZoneInfos[pEventZoneInfo->getZoneID()] = pEventZoneInfo;
}

EventZoneInfo* ZoneEventInfo::getCurrentEventZoneInfo() const
{
	hash_map<ZoneID_t, EventZoneInfo*>::const_iterator itr = m_EventZoneInfos.begin();
	hash_map<ZoneID_t, EventZoneInfo*>::const_iterator endItr = m_EventZoneInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second->isEventOn() ) return itr->second;
	}

	return NULL;
}

ZoneEventInfo* EventZoneInfoManager::getZoneEventInfo( WORD eventID ) const 
{
	hash_map<WORD, ZoneEventInfo*>::const_iterator itr = m_ZoneEventInfos.find( eventID );

	if ( itr == m_ZoneEventInfos.end() ) return NULL;
	return itr->second;
}

EventZoneInfo* EventZoneInfoManager::getEventZoneInfo( ZoneID_t zoneID ) const 
{
	hash_map<ZoneID_t, EventZoneInfo*>::const_iterator itr = m_EventZoneInfos.find( zoneID );

	if ( itr == m_EventZoneInfos.end() ) return NULL;
	return itr->second;
}

void EventZoneInfoManager::load() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT EventID, ZoneID, EnterX, EnterY, ResurrectX, ResurrectY, PCLimit FROM EventZoneInfo");

		while ( pResult->next() )
		{
			WORD		eventID		= pResult->getInt(1);
			ZoneID_t	zoneID		= pResult->getInt(2);
			EventZoneInfo*	pEventZoneInfo = new EventZoneInfo( eventID, zoneID );
			
			pEventZoneInfo->m_EnterX = pResult->getInt(3);
			pEventZoneInfo->m_EnterY = pResult->getInt(4);
			pEventZoneInfo->m_ResurrectX = pResult->getInt(5);
			pEventZoneInfo->m_ResurrectY = pResult->getInt(6);

			pEventZoneInfo->m_PCLimit = pResult->getInt(7);
			pEventZoneInfo->m_bEventOn = false;

			if ( m_ZoneEventInfos[eventID] == NULL )
			{
				m_ZoneEventInfos[eventID] = new ZoneEventInfo( eventID );
			}

			m_ZoneEventInfos[eventID]->addEventZoneInfo( pEventZoneInfo );
			m_EventZoneInfos[zoneID] = pEventZoneInfo;
		}
	}
	END_DB(pStmt)

	__END_CATCH
}

