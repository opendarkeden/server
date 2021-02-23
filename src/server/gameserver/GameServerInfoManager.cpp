//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServerInfoManager.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GameServerInfoManager.h"
#include "database/DB.h"

//////////////////////////////////////////////////////////////////////////////
// class GameServerInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

GameServerInfoManager::GameServerInfoManager () 
	throw ()
{
	m_MaxWorldID = 0;
	m_MaxServerGroupID = 0;
}


GameServerInfoManager::~GameServerInfoManager () 
	throw ()
{
	clear();
}


void GameServerInfoManager::clear()
	throw (Error)
{
	// hashmap 안의 각 pair 의 second, 즉 GameServerInfo 객체만을 삭제하고
	// pair 자체는 그대로 둔다. (GameServerInfo가 힙에 생성되어 있다는 것에
	// 유의하라. 즉 필살삭제를 해야 한다. 하긴, GSIM이 destruct 된다는 것은
	// 로그인 서버가 셧다운된다는 것을 의미하니깐.. - -;)
	for( int j = 1; j < m_MaxWorldID; j++ ) {
		for (int i=0; i < m_MaxServerGroupID; i++) 
		{
			HashMapGameServerInfo::iterator itr = m_pGameServerInfos[j][i].begin();
			for (; itr != m_pGameServerInfos[j][i].end(); itr++) 
			{
				SAFE_DELETE(itr->second);
			}

			// 이제 해쉬맵안에 있는 모든 pair 들을 삭제한다.
			m_pGameServerInfos[j][i].clear();
		}
	}

	if (m_pGameServerInfos != NULL) 
	{
		for (int i=1 ; i < m_MaxWorldID; i++) SAFE_DELETE_ARRAY(m_pGameServerInfos[i]);
		SAFE_DELETE_ARRAY(m_pGameServerInfos);
	}	
}


void GameServerInfoManager::init ()
	throw (Error)
{
	__BEGIN_TRY

	// just load data from GameServerInfo table
	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

void GameServerInfoManager::load ()
	throw (Error)
{
	__BEGIN_TRY

	// clear GameServerInfos
	clear();

	Statement* pStmt = NULL;

	// 먼저 MAX SERVER GROUP ID를 읽어들여야 한다.
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT MAX(GroupID) FROM GameServerInfo"
		);

		if (pResult->getRowCount() == 0)
		{
			cerr << "GameServerInfo TABLE does not exist!" << endl;
			throw Error("GameServerInfo TABLE does not exist!");
		}

		pResult->next();
		m_MaxServerGroupID = pResult->getInt(1) + 1;

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT MAX(WorldID) FROM GameServerInfo"
		);

		if (pResult->getRowCount() == 0)
		{
			cerr << "GameServerInfo TABLE does not exist!" << endl;
			throw Error("GameServerInfo TABLE does not exist!");
		}

		pResult->next();
		m_MaxWorldID = pResult->getInt(1) + 2;

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

		/*
	m_pTiles = new Tile* [ m_Width ];
	for (uint i = 0 ; i < m_Width ; i++) m_pTiles[i] = new Tile [m_Height];
	*/

	m_pGameServerInfos = new HashMapGameServerInfo* [m_MaxWorldID];

	for( int i = 1; i < m_MaxWorldID; i++ ) m_pGameServerInfos[i] = new HashMapGameServerInfo[m_MaxServerGroupID];

	cout << "MAX SERVER GROUP = " << m_MaxServerGroupID << endl;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT ServerID, Nickname , IP , TCPPort , UDPPort, WorldID, GroupID, Stat FROM GameServerInfo"
		);

		while (pResult->next()) 
		{
			GameServerInfo* pGameServerInfo = new GameServerInfo();

			pGameServerInfo->setServerID(pResult->getInt(1));
			pGameServerInfo->setNickname(pResult->getString(2));
			pGameServerInfo->setIP(pResult->getString(3));
			pGameServerInfo->setTCPPort(pResult->getInt(4));
			pGameServerInfo->setUDPPort(pResult->getInt(5));

			WorldID_t WorldID = pResult->getInt(6);
			pGameServerInfo->setWorldID(WorldID);

			ServerGroupID_t ServerGroupID = pResult->getInt(7);
			pGameServerInfo->setGroupID(ServerGroupID);

			pGameServerInfo->setServerStat((ServerStatus)pResult->getInt(8));
			addGameServerInfo(pGameServerInfo, ServerGroupID, WorldID);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	///////////////////////////////////////////////////////////////////////////////
	// PK Server 세팅하기
	// DB의 PKServerList 테이블에서 읽어서 세팅한다.
	// PKServerList 는 플레이어(login) DB 에 있다.
	///////////////////////////////////////////////////////////////////////////////
	BEGIN_DB
	{
		// PKServerList 는 플레이어(login) DB 에 있다.
		pStmt = g_pDatabaseManager->getDistConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT WorldID, ServerGroupID FROM NonPKServerList"
		);

		while (pResult->next()) 
		{
			WorldID_t worldID = pResult->getInt( 1 );
			ServerGroupID_t serverGroupID = pResult->getInt( 2 );

			GameServerInfo* pGameServerInfo = getGameServerInfo( 1, serverGroupID, worldID );

			pGameServerInfo->setNonPKServer();

			cout << "WorldID:" << (int)worldID << " ServerGroupID:" << (int)serverGroupID << " NonPK set" << endl;
		}

		SAFE_DELETE(pStmt);

	}
	END_DB(pStmt)

	///////////////////////////////////////////////////////////////////////////////
	// Castle Stat 로딩
	// 이 서버에서 어떤 서버의 전쟁 결과에 따라 바뀌는지
	///////////////////////////////////////////////////////////////////////////////
	BEGIN_DB
	{
		// 플레이어(login) DB 에 있다.
		pStmt = g_pDatabaseManager->getDistConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT WorldID, ServerGroupID, FollowServerID FROM CastleStatInfo"
		);

		while (pResult->next()) 
		{
			WorldID_t		worldID = pResult->getInt(1);
			ServerGroupID_t serverGroupID = pResult->getInt( 2 );
			ServerGroupID_t followServerID = pResult->getInt( 3 );

			GameServerInfo* pGameServerInfo = getGameServerInfo( 1, serverGroupID, worldID );

			pGameServerInfo->setCastleFollowingServerID( followServerID );

			cout << "WorldID:" << (int)worldID << " ServerGroupID:" << (int)serverGroupID << " follows" << (int)followServerID << endl;
		}

		SAFE_DELETE(pStmt);

	}
	END_DB(pStmt)


	__END_CATCH
}

void GameServerInfoManager::addGameServerInfo(GameServerInfo * pGameServerInfo, const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) 
	throw (DuplicatedException)
{
	__BEGIN_TRY

	if (ServerGroupID >= m_MaxServerGroupID)
	{
		throw DuplicatedException("ServerGroupID over Bounce");
	}

	if (WorldID >= m_MaxWorldID )
	{
		throw DuplicatedException("WorldID over Bounce");
	}

	HashMapGameServerInfo::iterator itr = m_pGameServerInfos[WorldID][ServerGroupID].find(pGameServerInfo->getServerID());
	
	if (itr != m_pGameServerInfos[WorldID][ServerGroupID].end())
	{
		throw DuplicatedException("duplicated game-server ServerID");
	}

	m_pGameServerInfos[WorldID][ServerGroupID][ pGameServerInfo->getServerID() ] = pGameServerInfo;

	__END_CATCH
}
	
void GameServerInfoManager::deleteGameServerInfo (const ServerID_t ServerID, const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY

	if (ServerGroupID >= m_MaxServerGroupID)
	{
		throw DuplicatedException("ServerGroupID over Bounce");
	}
	if (WorldID >= m_MaxWorldID)
	{
		throw DuplicatedException("WorldID over Bounce");
	}
	HashMapGameServerInfo::iterator itr = m_pGameServerInfos[WorldID][ServerGroupID].find(ServerID);
	
	if (itr != m_pGameServerInfos[WorldID][ServerGroupID].end()) 
	{
		// GameServerInfo 를 삭제한다.
		delete itr->second;

		// pair를 삭제한다.
		m_pGameServerInfos[WorldID][ServerGroupID].erase(itr);
	} 
	else 
	{
		// 그런 게임서버인포 객체를 찾을 수 없을 때
		throw NoSuchElementException();
	}

	__END_CATCH
}
	
/*
//----------------------------------------------------------------------
// get info
//----------------------------------------------------------------------
GameServerInfo * GameServerInfoManager::getGameServerInfo (const string & nickname) const
	throw (NoSuchElementException)
{
	__BEGIN_TRY
		
	GameServerInfo * pGameServerInfo = NULL;

	HashMapGameServerInfo::const_iterator itr = m_pGameServerInfos.find(nickname);
	
	if (itr != m_pGameServerInfos.end()) {

		pGameServerInfo = itr->second;

	} else {

		// 그런 게임서버인포 객체를 찾을 수 없었을 때
		throw NoSuchElementException(nickname);

	}

	return pGameServerInfo;

	__END_CATCH
}
*/

GameServerInfo * GameServerInfoManager::getGameServerInfo (const ServerID_t ServerID, const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) const
	throw (NoSuchElementException)
{
	__BEGIN_TRY
		
	GameServerInfo * pGameServerInfo = NULL;

	if( WorldID >= m_MaxWorldID || ServerGroupID >= m_MaxServerGroupID ) {
		// 그런 게임서버인포 객체를 찾을 수 없었을 때
		throw NoSuchElementException();
	}

	HashMapGameServerInfo::const_iterator itr = m_pGameServerInfos[WorldID][ServerGroupID].find(ServerID);
	
	if (itr != m_pGameServerInfos[WorldID][ServerGroupID].end()) 
	{
		pGameServerInfo = itr->second;
	} 
	else 
	{
		// 그런 게임서버인포 객체를 찾을 수 없었을 때
		throw NoSuchElementException();
	}

	return pGameServerInfo;

	__END_CATCH
}

string GameServerInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GameServerInfoManager(\n";

	for( int j = 1; j < m_MaxWorldID; j++ ) {

		for (int i = 0; i < m_MaxServerGroupID; i++) 
		{
			if (m_pGameServerInfos[j][i].empty()) 
			{
				msg << "EMPTY";
			} 
			else 
			{
				HashMapGameServerInfo::const_iterator itr = m_pGameServerInfos[j][i].begin();
				for (; itr != m_pGameServerInfos[j][i].end(); itr++)
				{
					msg << itr->second->toString() << '\n';
				}
			}

			msg << ")";
		}
	}

	return msg.toString();

	__END_CATCH
}

// global variable definition
GameServerInfoManager * g_pGameServerInfoManager = NULL;
