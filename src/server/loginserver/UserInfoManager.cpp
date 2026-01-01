//----------------------------------------------------------------------
//
// Filename    : UserInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "UserInfoManager.h"
#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"
#include "database/DB.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
UserInfoManager::UserInfoManager () noexcept
{
}
	
//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
UserInfoManager::~UserInfoManager () noexcept
{
	try
	{
		// hashmap ���� �� pair �� second, �� UserInfo ��ü���� �����ϰ�
		// pair ��ü�� �״�� �д�. (UserInfo�� ���� �����Ǿ� �ִٴ� �Ϳ�
		// �����϶�. �� �ʻ������ �ؾ� �Ѵ�. �ϱ�, ZGIM�� destruct �ȴٴ� ����
		// �α��� ������ �˴ٿ�ȴٴ� ���� �ǹ��ϴϱ�.. - -; )
		for( int i = 1; i < m_MaxWorldID; i++ ) {
			for ( HashMapUserInfo::iterator itr = m_UserInfos[i].begin() ; 
				  itr != m_UserInfos[i].end() ; 
				  itr ++ ) {
				delete itr->second;
				itr->second = NULL;
			}

			// ���� �ؽ��ʾȿ� �ִ� ��� pair ���� �����Ѵ�.
			m_UserInfos[i].clear();
		}

		delete [] m_UserInfos;
	}
	catch (...)
	{
		// destructor must not throw
	}

}
	

//----------------------------------------------------------------------
// initialize GSIM
//----------------------------------------------------------------------
void UserInfoManager::init ()
	noexcept(false)
{
	__BEGIN_TRY

	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// load data from database
//----------------------------------------------------------------------
void UserInfoManager::load ()
	noexcept(false)
{
	__BEGIN_TRY

	Statement * pStmt;

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

	m_UserInfos= new HashMapUserInfo[m_MaxWorldID];


	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result * pResult = pStmt->executeQuery(
			"SELECT WorldID, GroupID FROM GameServerGroupInfo"
		);

		while ( pResult->next() ) {
			UserInfo * pUserInfo = new UserInfo();
			WorldID_t WorldID = pResult->getInt(1);
			pUserInfo->setWorldID( WorldID );
			pUserInfo->setServerGroupID( pResult->getInt(2) );
			pUserInfo->setUserNum( 0 );
			addUserInfo( pUserInfo );
		}

	} catch ( SQLQueryException & sqe ) {

		// �ʻ� ����!
		delete pStmt;

		throw Error(sqe.toString());
	}

	// �ʻ� ����!
	delete pStmt;

	__END_CATCH
}

//----------------------------------------------------------------------
// add info 
//----------------------------------------------------------------------
void UserInfoManager::addUserInfo ( UserInfo * pUserInfo ) 
	noexcept(false)
{
	__BEGIN_TRY

	HashMapUserInfo::iterator itr = m_UserInfos[pUserInfo->getWorldID()].find( pUserInfo->getServerGroupID() );
	
	if ( itr != m_UserInfos[pUserInfo->getWorldID()].end() )
		throw DuplicatedException("duplicated zone id");

	m_UserInfos[pUserInfo->getWorldID()][ pUserInfo->getServerGroupID() ] = pUserInfo;

	__END_CATCH
}
	
//----------------------------------------------------------------------
// delete info
//----------------------------------------------------------------------
void UserInfoManager::deleteUserInfo ( ZoneGroupID_t ServerGroupID, WorldID_t WorldID )
	noexcept(false)
{
	__BEGIN_TRY
		
	HashMapUserInfo::iterator itr = m_UserInfos[WorldID].find( ServerGroupID );
	
	if ( itr != m_UserInfos[WorldID].end() ) {

		// UserInfo �� �����Ѵ�.
		delete itr->second;

		// pair�� �����Ѵ�.
		m_UserInfos[WorldID].erase( itr );

	} else { // not found

		StringStream msg;
		msg << "ServerGroupID: " << ServerGroupID;
		throw NoSuchElementException(msg.toString());

	}

	__END_CATCH
}
	
//----------------------------------------------------------------------
// get info
//----------------------------------------------------------------------
UserInfo * UserInfoManager::getUserInfo ( ZoneGroupID_t ServerGroupID, WorldID_t WorldID ) const
	noexcept(false)
{
	__BEGIN_TRY
		
	UserInfo * pUserInfo = NULL;

	HashMapUserInfo::const_iterator itr = m_UserInfos[WorldID].find( ServerGroupID );
	
	if ( itr != m_UserInfos[WorldID].end() ) {

		pUserInfo = itr->second;

	} else { // not found

		StringStream msg;
		msg << "ServerGroupID : " << ServerGroupID;
		throw NoSuchElementException( msg.toString() );

	}

	return pUserInfo;

	__END_CATCH
}


//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string UserInfoManager::toString () const noexcept(false)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "UserInfoManager(";

	for( int i = 1; i < m_MaxWorldID; i++ ) {

		if ( m_UserInfos[i].empty() ) {

			msg << "EMPTY";

		} else {

			//--------------------------------------------------
			// *OPTIMIZATION*
			//
			// for_each()�� ����� ��
			//--------------------------------------------------
			for ( HashMapUserInfo::const_iterator itr = m_UserInfos[i].begin() ; 
				  itr != m_UserInfos[i].end() ; 
				  itr ++ )
				msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
UserInfoManager * g_pUserInfoManager = NULL;
