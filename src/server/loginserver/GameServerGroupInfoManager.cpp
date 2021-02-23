//----------------------------------------------------------------------
//
// Filename    : GameServerGroupInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GameServerGroupInfoManager.h"

#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"
#include "database/DB.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
GameServerGroupInfoManager::GameServerGroupInfoManager () 
	throw ()
{
	m_MaxWorldID = 0;
}
	
//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
GameServerGroupInfoManager::~GameServerGroupInfoManager () 
	throw ()
{
	clear();
}

//----------------------------------------------------------------------
// clear GameServerGroupInfos
//----------------------------------------------------------------------
void GameServerGroupInfoManager::clear()
	throw ( Error )
{
	__BEGIN_TRY

	// hashmap 안의 각 pair 의 second, 즉 GameServerGroupInfo 객체만을 삭제하고
	// pair 자체는 그대로 둔다. (GameServerGroupInfo가 힙에 생성되어 있다는 것에
	// 유의하라. 즉 필살삭제를 해야 한다. 하긴, GSIM이 destruct 된다는 것은
	// 로그인 서버가 셧다운된다는 것을 의미하니깐.. - -; )
	for( int i = 1 ; i < m_MaxWorldID; i++ ) {
		for ( HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[i].begin() ; 
			  itr != m_GameServerGroupInfos[i].end() ; 
			  itr ++ ) {
			SAFE_DELETE(itr->second);
		}

		// 이제 해쉬맵안에 있는 모든 pair 들을 삭제한다.
		m_GameServerGroupInfos[i].clear();

	}

	SAFE_DELETE_ARRAY(m_GameServerGroupInfos);

	__END_CATCH
}
	

//----------------------------------------------------------------------
// initialize GSIM
//----------------------------------------------------------------------
void GameServerGroupInfoManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	// just load data from GameServerGroupInfo table
	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// load data from database
//----------------------------------------------------------------------
void GameServerGroupInfoManager::load ()
	throw ( Error )
{
	__BEGIN_TRY

	clear();

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT MAX(WorldID) FROM GameServerGroupInfo"
		);

		if (pResult->getRowCount() == 0)
		{
			throw Error("GameServerGroupInfo TABLE does not exist!");
		}

		pResult->next();
		m_MaxWorldID = pResult->getInt(1) + 2;

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	m_GameServerGroupInfos = new HashMapGameServerGroupInfo[m_MaxWorldID];

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result * pResult = pStmt->executeQuery(
			"SELECT WorldID, GroupID, GroupName, Stat FROM GameServerGroupInfo"
		);

		while ( pResult->next() ) {
			GameServerGroupInfo * pGameServerGroupInfo = new GameServerGroupInfo();
			WorldID_t WorldID = pResult->getInt(1);
			pGameServerGroupInfo->setWorldID( WorldID );
			pGameServerGroupInfo->setGroupID( pResult->getInt(2) );
			pGameServerGroupInfo->setGroupName( pResult->getString(3) );
			pGameServerGroupInfo->setStat( pResult->getInt(4) );
			addGameServerGroupInfo( pGameServerGroupInfo, WorldID );
		}

		// 필살 삭제!
		SAFE_DELETE( pStmt );

	} catch ( SQLQueryException & sqe ) {

		// 필살 삭제!
		SAFE_DELETE( pStmt );

		throw Error(sqe.toString());

	} catch ( Throwable & t ) {
		SAFE_DELETE( pStmt );
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// add info 
//----------------------------------------------------------------------
void GameServerGroupInfoManager::addGameServerGroupInfo ( GameServerGroupInfo * pGameServerGroupInfo, WorldID_t WorldID ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	int GroupID = pGameServerGroupInfo->getGroupID();
	HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[WorldID].find( GroupID );
	
	if ( itr != m_GameServerGroupInfos[WorldID].end() )
		throw DuplicatedException("duplicated game-server nickname");

	cout << "addGameServerGroupInfo: " << (int)WorldID << ", " << GroupID 
		<< " : " << pGameServerGroupInfo->getGroupName().c_str() << endl;

	m_GameServerGroupInfos[WorldID][GroupID] = pGameServerGroupInfo;

	__END_CATCH
}
	
//----------------------------------------------------------------------
// delete info
//----------------------------------------------------------------------
void GameServerGroupInfoManager::deleteGameServerGroupInfo ( const ServerGroupID_t GroupID, WorldID_t WorldID ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[WorldID].find( GroupID );
	
	if ( itr != m_GameServerGroupInfos[WorldID].end() ) {

		// GameServerGroupInfo 를 삭제한다.
		delete itr->second;

		// pair를 삭제한다.
		m_GameServerGroupInfos[WorldID].erase( itr );

	} else {

		// 그런 게임서버인포 객체를 찾을 수 없을 때
		throw NoSuchElementException();

	}

	__END_CATCH
}
	
//----------------------------------------------------------------------
// get GameServerGroupinfo by ServerGroupID
//----------------------------------------------------------------------
GameServerGroupInfo * GameServerGroupInfoManager::getGameServerGroupInfo ( const ServerGroupID_t GroupID, WorldID_t WorldID ) const
	throw ( NoSuchElementException )
{
	__BEGIN_TRY

	if( WorldID >= m_MaxWorldID ) {
		// 그런 게임서버인포 객체를 찾을 수 없었을 때
		throw NoSuchElementException();
	}
		
	GameServerGroupInfo * pGameServerGroupInfo = NULL;

	HashMapGameServerGroupInfo::const_iterator itr = m_GameServerGroupInfos[WorldID].find( GroupID );
	
	if ( itr != m_GameServerGroupInfos[WorldID].end() ) {
		pGameServerGroupInfo = itr->second;
	} else {
		// 그런 게임서버인포 객체를 찾을 수 없었을 때
		throw NoSuchElementException();
	}

	return pGameServerGroupInfo;

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string GameServerGroupInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GameServerGroupInfoManager(\n";

	for ( int i = 1; i < m_MaxWorldID ; i++ ) {

		if ( m_GameServerGroupInfos[i].empty() ) {

			msg << "EMPTY";

		} else {

			//--------------------------------------------------
			// *OPTIMIZATION*
			//
			// for_each()를 사용할 것
			//--------------------------------------------------
			for ( HashMapGameServerGroupInfo::const_iterator itr = m_GameServerGroupInfos[i].begin() ; 
				  itr != m_GameServerGroupInfos[i].end() ; 
				  itr ++ )
				msg << itr->second->toString() << '\n';
		}

	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
GameServerGroupInfoManager * g_pGameServerGroupInfoManager = NULL;
