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
#include "Assert.h"
#include "DB.h"

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

	__END_CATCH
}

void DatabaseManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	try 
	{
		cout << "--------------------------------------------------" << endl;
		cout << "            Init DatabaseManager " << endl;
		cout << "--------------------------------------------------" << endl;

		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_NAME");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");

		printf("Connect information : %s - %s - %s - %s\n", host.c_str(), db.c_str(), user.c_str(), password.c_str());
		
		m_pDefaultConnection = new Connection(host, db, user, password);
		Assert(m_pDefaultConnection!=NULL);

		Statement * pStmt = NULL;
		pStmt = m_pDefaultConnection->createStatement();
		Result * pResult = NULL;

		// 시간 체크
		// 데이터 베이스와 서버간에 시간차이가 1시간 이상이면 안뜬다.
		pResult = pStmt->executeQuery( "SELECT now()" );
		if ( pResult->next() )
		{
			// 0123456789012345678
			// 2003-08-25 18:25:11
			string sDBTime = pResult->getString( 1 );
			tm tDBTime;
			cout << sDBTime << endl;

			tDBTime.tm_year	= atoi( sDBTime.substr( 0,4).c_str() ) - 1900;
			tDBTime.tm_mon	= atoi( sDBTime.substr( 5,2).c_str() );
			tDBTime.tm_mday	= atoi( sDBTime.substr( 8,2).c_str() );
			tDBTime.tm_hour	= atoi( sDBTime.substr(11,2).c_str() );
			tDBTime.tm_min	= atoi( sDBTime.substr(14,2).c_str() );
			tDBTime.tm_sec	= atoi( sDBTime.substr(17,2).c_str() );

			time_t tSYSTime = time(0);

			double dbDiff = difftime( tSYSTime, mktime(&tDBTime) );

			if ( (int)dbDiff > 3600 )
			{
				// 데이터 베이스와 서버간에 시간차이가 1시간 이상이다.
				cout << "======================================================" << endl;
				cout << "!!! Time Check Error !!!" << endl;
				cout << "!!! Please check DB server and service server time !!!" << endl;
				cout << "======================================================" << endl;

				throw Error("Time Check Error");
			}
		}

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

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "Adding TID connection END" << endl;

	__END_CATCH
}

Connection * DatabaseManager::getConnection ( const string& connName ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	Connection * pTempConnection = NULL;

	hash_map<int, Connection*>::iterator itr;

	// connName에 대해서 각기 다른 DB Server로 분기하도록 한다.
	//if(connName == "DIST_DARKEDEN")
	//{
	//	itr = m_DistConnections.find(Thread::self());

	//	if(itr == m_DistConnections.end())
	//		pTempConnection = m_pDistConnection;
	//	else
	//		pTempConnection = itr->second;
	//}
	//else
	//{
		itr = m_Connections.find(Thread::self());

		if(itr == m_Connections.end())
			pTempConnection = m_pDefaultConnection;
		else
			pTempConnection = itr->second;
	//}

	//Assert(pTempConnection!=NULL);
	return pTempConnection;

	__END_CATCH
}

void DatabaseManager::executeDummyQuery(Connection* pConnection)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	BEGIN_DB
	{
		pStmt = pConnection->createStatement();
		pStmt->executeQuery("SELECT 1");

		SAFE_DELETE(pStmt);
	} END_DB(pStmt) {
		 SAFE_DELETE(pStmt);
	} 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// global variable definition
//////////////////////////////////////////////////////////////////////////////
DatabaseManager * g_pDatabaseManager = NULL;
