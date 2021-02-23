//////////////////////////////////////////////////////////////////////////////
// Filename    : DatabaseManager.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "DatabaseManager.h"
#include "Properties.h"
#include "Utility.h"
#include "Thread.h"
#include "Timeval.h"
#include "Result.h"
#include "Statement.h"
#include "Properties.h"

DatabaseManager::DatabaseManager () 
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName("DatabaseManager");

	m_pDefaultConnection = NULL;

	__END_CATCH
}

DatabaseManager::~DatabaseManager () 
	throw ()
{
	__BEGIN_TRY
	
	// 모든 Connection 를 삭제해야 한다.
	hash_map<int, Connection*>::iterator itr = m_Connections.begin();
	for (; itr != m_Connections.end(); itr++)
		SAFE_DELETE(itr->second);

	// 해쉬맵안에 있는 모든 pair 들을 삭제한다.
	m_Connections.clear();

	SAFE_DELETE(m_pDefaultConnection);
	SAFE_DELETE(m_pUserInfoConnection);

	__END_CATCH
}

void DatabaseManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	try 
	{

		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_DB");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");

		m_pDefaultConnection = new Connection(host, db, user, password);

		string uihost     = g_pConfig->getProperty("UI_DB_HOST");
		string uidb       = g_pConfig->getProperty("UI_DB_DB");
		string uiuser     = g_pConfig->getProperty("UI_DB_USER");
		string uipassword = g_pConfig->getProperty("UI_DB_PASSWORD");

		m_pUserInfoConnection = new Connection(uihost, uidb, uiuser, uipassword);


		Statement * pStmt = NULL;
		pStmt = m_pDefaultConnection->createStatement();
		Result * pResult = NULL;

		pResult = pStmt->executeQuery( "SELECT WorldID, Host, DB, User, Password FROM WorldDBInfo WHERE WorldID = 0" );
		while( pResult->next() ) {
			cout << "Connecting....... Another DB Server" << endl;

			WorldID_t WorldID = pResult->getInt(1);
			string whost = pResult->getString(2);
			string wdb = pResult->getString(3);
			string wuser = pResult->getString(4);
			string wpassword = pResult->getString(5);

			Connection * pConnection = new Connection(whost, wdb, wuser, wpassword);
			m_pWorldDefaultConnection = pConnection;
		}


#ifdef __LOGIN_SERVER__

		pResult = pStmt->executeQuery( "SELECT WorldID, Host, DB, User, Password FROM WorldDBInfo" );
		while( pResult->next() ) {
			cout << "Connecting....... Another DB Server" << endl;

			WorldID_t WorldID = pResult->getInt(1);
			string whost = pResult->getString(2);
			string wdb = pResult->getString(3);
			string wuser = pResult->getString(4);
			string wpassword = pResult->getString(5);

			Connection * pConnection = new Connection(whost, wdb, wuser, wpassword);
			addConnection( WorldID , pConnection );

		}
#endif

		SAFE_DELETE(pStmt);

	} 
	catch ( SQLConnectException & sce ) 
	{
		throw Error( sce.toString() );
	}

	__END_CATCH
}

void DatabaseManager::addConnection ( int TID,  Connection * pConnection ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	cout << "Adding TID connection BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< int , Connection * >::iterator itr = m_Connections.find( TID );
	
	if ( itr != m_Connections.end() )
	{
		cout << "duplicated connection info id" << endl;
		throw DuplicatedException("duplicated connection info id");
	}

	m_Connections[ TID ] = pConnection;

#ifdef __GAME_SERVER

	// 게임 서버일 경우 각 쓰레드 별로 World DB Connection이 있는 경우가 좋다.
	Statement * pStmt = NULL;
	pStmt = m_pDefaultConnection->createStatement();
	Result * pResult = NULL;

	pResult = pStmt->executeQuery( "SELECT WorldID, Host, DB, User, Password FROM WorldDBInfo WHERE WorldID = 0" );
	while( pResult->next() ) {
		cout << "Connecting....... Another DB Server" << endl;

		WorldID_t WorldID = pResult->getInt(1);
		string whost = pResult->getString(2);
		string wdb = pResult->getString(3);
		string wuser = pResult->getString(4);
		string wpassword = pResult->getString(5);

		Connection * pConnection = new Connection(whost, wdb, wuser, wpassword);
		m_WorldConnections[ TID ] = pConnection;
	}

#endif

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "Adding TID connection END" << endl;

	__END_CATCH
}
	
Connection * DatabaseManager::getConnection ( string connName ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	Connection * pTempConnection = NULL;

	hash_map<int, Connection*>::iterator itr = m_Connections.find(Thread::self());

	if (itr == m_Connections.end())
	{
		pTempConnection = m_pDefaultConnection;
	} 
	else 
	{
		pTempConnection = itr->second;
	}

	return pTempConnection;

	__END_CATCH
}

/*
void DatabaseManager::addConnection ( WorldID_t WorldID,  Connection * pConnection ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	cout << "Adding World connection BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< WorldID_t , Connection * >::iterator itr = m_WorldConnections.find( WorldID );
	
	if ( itr != m_WorldConnections.end() )
	{
		cout << "duplicated connection info id" << endl;
		throw DuplicatedException("duplicated connection info id");
	}

	m_WorldConnections[ WorldID ] = pConnection;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "Adding World connection END" << endl;

	__END_CATCH
}
*/
	
Connection * DatabaseManager::getConnection ( int TID ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	Connection * pTempConnection = NULL;
#ifdef __GAME_SERVER__
	pTempConnection = m_pWorldDefaultConnection;

#elif __LOGIN_SERVER__
	hash_map<int, Connection*>::iterator itr = m_WorldConnections.find(TID);

	if (itr == m_WorldConnections.end())
	{
		pTempConnection = m_pWorldDefaultConnection;
	} 
	else 
	{
		pTempConnection = itr->second;
	}

#endif
	return pTempConnection;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// global variable definition
//////////////////////////////////////////////////////////////////////////////
DatabaseManager * g_pDatabaseManager = NULL;
