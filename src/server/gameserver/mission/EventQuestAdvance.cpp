
#include "EventQuestAdvance.h"

#include "DB.h"
#include "PlayerCreature.h"

#include <algorithm>

void EventQuestAdvance::save(const string& name) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"UPDATE EventQuestAdvance SET Status=%u WHERE OwnerID='%s' AND QuestLevel=%u",
				(uint)getStatus(), name.c_str(), (uint)getLevel()
				);

		if ( pStmt->getAffectedRowCount() == 0 )
		{
			pStmt->executeQuery(
				"INSERT IGNORE INTO EventQuestAdvance (QuestLevel, OwnerID, Status) VALUES (%u, '%s', %u)",
				(uint)getLevel(), name.c_str(), (uint)getStatus()
				);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EventQuestAdvanceManager::EventQuestAdvanceManager( PlayerCreature* pPC )
{
	m_Advances.reserve(EVENT_QUEST_LEVEL_MAX);
	m_Advances.clear();
	for ( int i=0; i<EVENT_QUEST_LEVEL_MAX; ++i ) m_Advances[i] = NULL;

	m_pOwner = pPC;
}

template<typename T>
inline void SafeDelete( T* pT ) { SAFE_DELETE(pT); }

EventQuestAdvanceManager::~EventQuestAdvanceManager()
{
	clear();
}

void EventQuestAdvanceManager::clear()
{
	for_each( m_Advances.begin(), m_Advances.end(), SafeDelete<EventQuestAdvance> );
	m_Advances.clear();
}

bool EventQuestAdvanceManager::start( int questLevel )
{
	Assert( questLevel >= 0 );
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );
	if ( m_Advances[questLevel] == NULL )
		m_Advances[questLevel] = new EventQuestAdvance( questLevel );
	return m_Advances[questLevel]->start();
}

bool EventQuestAdvanceManager::success( int questLevel )
{
	Assert( questLevel >= 0 );
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );
	if ( m_Advances[questLevel] != NULL ) return m_Advances[questLevel]->success();
	return false;
}

bool EventQuestAdvanceManager::rewarded( int questLevel )
{
	Assert( questLevel >= 0 );
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );
/*	if ( m_Advances[questLevel] != NULL )
	{
		for ( int i=0; i<=questLevel; ++i ) m_Advances[i]->reset();
		return true;
	}*/

	for ( int i=0; i<EVENT_QUEST_LEVEL_MAX; ++i )
	{
		if ( m_Advances[i] != NULL ) m_Advances[i]->reset();
	}
	return true;
}

bool EventQuestAdvanceManager::advanced( int questLevel )
{
	Assert( questLevel >= 0 );
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );
	if ( m_Advances[questLevel] != NULL ) return m_Advances[questLevel]->advanced();
	return false;
}

EventQuestAdvance::Status EventQuestAdvanceManager::getStatus( int questLevel )
{
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );
	
	// 퀘스트 레벨이 음수값이면 모든 사람이 이미 끝낸 퀘스트다. -_-;
	if ( questLevel < 0 ) return EventQuestAdvance::EVENT_QUEST_ADVANCED;
	if ( m_Advances[questLevel] == NULL ) return EventQuestAdvance::EVENT_QUEST_INIT;
	return m_Advances[questLevel]->getStatus();
}

void EventQuestAdvanceManager::save() throw(Error)
{
	__BEGIN_TRY

	for ( int i=0; i<EVENT_QUEST_LEVEL_MAX; ++i )
	{
		if ( m_Advances[i] != NULL ) m_Advances[i]->save( m_pOwner->getName() );
	}

	__END_CATCH
}

void EventQuestAdvanceManager::save( int questLevel ) throw(Error)
{
	__BEGIN_TRY

	Assert( questLevel >= 0 );
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );
	if ( m_Advances[questLevel] != NULL ) m_Advances[questLevel]->save( m_pOwner->getName() );

	__END_CATCH
}

void EventQuestAdvanceManager::load() throw(Error)
{
	__BEGIN_TRY

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT QuestLevel, Status FROM EventQuestAdvance WHERE OwnerID='%s'",
				m_pOwner->getName().c_str() );

		while (pResult->next()) 
		{
			int 						qLevel	= pResult->getInt(1);
			EventQuestAdvance::Status 	status	= (EventQuestAdvance::Status)pResult->getInt(2);

			m_Advances[qLevel] = new EventQuestAdvance( qLevel, status );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

bool EventQuestAdvanceManager::canExecute( int questLevel )
{
	Assert( questLevel >= 0 );
	Assert( questLevel < EVENT_QUEST_LEVEL_MAX );

	EventQuestAdvance::Status stat = getStatus(questLevel);

	if ( stat == EventQuestAdvance::EVENT_QUEST_ADVANCED || stat == EventQuestAdvance::EVENT_QUEST_REWARDED ) return false;

	for ( int i=0 ; i<questLevel; ++i )
	{
		if ( getStatus(i) != EventQuestAdvance::EVENT_QUEST_ADVANCED ) return false;
	}

	for ( int i = questLevel + 1; i < EVENT_QUEST_LEVEL_MAX ; ++i )
	{
		if ( getStatus(i) != EventQuestAdvance::EVENT_QUEST_INIT ) return false;
	}

	return true;
}

int	EventQuestAdvanceManager::getQuestLevel()
{
	for ( int i=0; i<EVENT_QUEST_LEVEL_MAX; ++i )
	{
		EventQuestAdvance::Status stat = getStatus(i);
		if ( stat != EventQuestAdvance::EVENT_QUEST_ADVANCED )
		{
			if ( stat == EventQuestAdvance::EVENT_QUEST_REWARDED ) return 0;
			return i;
		}
	}

	return -1;
}
