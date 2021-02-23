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
	m_pDistConnection = NULL;
    m_pWorldDefaultConnection = NULL;
	m_pUserInfoConnection = NULL;

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
		cout << "--------------------------------------------------" << endl;
		cout << "            Init DatabaseManager " << endl;
		cout << "--------------------------------------------------" << endl;

		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_DB");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");
		uint port		= 0;
		if ( g_pConfig->hasKey("DB_PORT") )
			port = g_pConfig->getPropertyInt("DB_PORT");

		m_pDefaultConnection = new Connection(host, db, user, password, port);
		Assert(m_pDefaultConnection!=NULL);

		string uihost     = g_pConfig->getProperty("UI_DB_HOST");
		string uidb       = g_pConfig->getProperty("UI_DB_DB");
		string uiuser     = g_pConfig->getProperty("UI_DB_USER");
		string uipassword = g_pConfig->getProperty("UI_DB_PASSWORD");
		uint uiport		= 0;
		if ( g_pConfig->hasKey("DB_PORT") )
			uiport = g_pConfig->getPropertyInt("DB_PORT");

		m_pUserInfoConnection = new Connection(uihost, uidb, uiuser, uipassword, uiport);
		Assert(m_pUserInfoConnection!=NULL);

		//string disthost     = g_pConfig->getProperty("DIST_DB_HOST");
		////string distdb       = g_pConfig->getProperty("DIST_DB_DB");
		//string distuser     = g_pConfig->getProperty("DIST_DB_USER");
		//string distpassword = g_pConfig->getProperty("DIST_DB_PASSWORD");

		//m_pDistConnection = new Connection(disthost, distdb, distuser, distpassword);
		//Assert(m_pDistConnection!=NULL);

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

		#ifdef __LOGIN_SERVER__
			pResult = pStmt->executeQuery( 
			"SELECT WorldID, Host, DB, User, Password, Port FROM WorldDBInfo");
			cout << "[LOGIN_SERVER] query WorldDBInfo" << endl;
		#else
			pResult = pStmt->executeQuery( 
			"SELECT WorldID, Host, DB, User, Password, Port FROM WorldDBInfo WHERE WorldID = 0");
		#endif
	
		while( pResult->next() ) {
			cout << "--------------------------------------------------" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "Connecting....... Another DB Server" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "--------------------------------------------------" << endl;

			WorldID_t WorldID = pResult->getInt(1);
			string whost = pResult->getString(2);
			string wdb = pResult->getString(3);
			string wuser = pResult->getString(4);
			string wpassword = pResult->getString(5);
			uint port = pResult->getInt(6);

			cout << "Connectiong: " 
				<< "WorldID=" << (int)WorldID
				<< ", HOST=" << whost.c_str()
				<< ", DB=" << wdb.c_str()
				<< ", User=" << wuser.c_str()
				<< ", Port=" << port << endl;

			Connection * pConnection = new Connection(whost, wdb, wuser, wpassword, port);
			Assert(pConnection!=NULL);

			#ifdef __LOGIN_SERVER__
				m_WorldConnections[ WorldID ] = pConnection;

				addConnection( WorldID , pConnection );

				cout << "WorldID=" << (int)WorldID << ", IP=" << whost.c_str() << endl;
			#else
				m_pWorldDefaultConnection = pConnection;
			#endif

		}

		/*
		#ifdef __LOGIN_SERVER__
			pResult = pStmt->executeQuery( 
			"SELECT ID, Host, DB, User, Password FROM PCRoomDBInfo");

			if ( pResult->next() ) {
				WorldID_t ID = pResult->getInt(1);
				string phost = pResult->getString(2);
				string pdb = pResult->getString(3);
				string puser = pResult->getString(4);
				string ppassword = pResult->getString(5);

				cout << "Connectiong: " 
					<< "ID=" << (int)ID
					<< ", HOST=" << phost.c_str()
					<< ", DB=" << pdb.c_str()
					<< ", User=" << puser.c_str() << endl;

				m_pPCRoomConnection = new Connection(phost, pdb, puser, ppassword);
			}

			Assert(m_pPCRoomConnection!=NULL);

		#endif
		*/

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

////////////////////////////////////////////////////////////////////////////
// Potion 측 Thread Connection을 위한 부분
////////////////////////////////////////////////////////////////////////////
void DatabaseManager::addDistConnection ( int TID,  Connection * pConnection ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	cout << "Adding TID connection BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< int , Connection * >::iterator itr = m_DistConnections.find( TID );
	
	if ( itr != m_DistConnections.end() )
	{
		cout << "duplicated connection info id" << endl;
		throw DuplicatedException("duplicated connection info id");
	}

	m_DistConnections[ TID ] = pConnection;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "Adding TID connection END" << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////
// China Billing log 저장을 위한 DB 연결 추가
////////////////////////////////////////////////////////////////////////////
void DatabaseManager::addCBillingConnection ( int TID,  Connection * pConnection ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	cout << "Adding TID connection BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< int , Connection * >::iterator itr = m_CBillingConnections.find( TID );
	
	if ( itr != m_CBillingConnections.end() )
	{
		cout << "duplicated connection info id" << endl;
		throw DuplicatedException("duplicated connection info id");
	}

	m_CBillingConnections[ TID ] = pConnection;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "Adding TID connection END" << endl;

	__END_CATCH
}

/*
////////////////////////////////////////////////////////////////////////////////
// PC 방 관련 Connection 저장
////////////////////////////////////////////////////////////////////////////////
void DatabaseManager::addPCRoomConnection ( int TID,  Connection * pConnection ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	cout << "Adding TID connection BEGIN" << endl;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< int , Connection * >::iterator itr = m_PCRoomConnections.find( TID );
	
	if ( itr != m_Connections.end() )
	{
		cout << "duplicated connection info id" << endl;
		throw DuplicatedException("duplicated connection info id");
	}

	m_PCRoomConnections[ TID ] = pConnection;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "Adding TID connection END" << endl;

	__END_CATCH
}
*/

Connection * DatabaseManager::getDistConnection ( const string& connName ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	Connection * pTempConnection = NULL;

	hash_map<int, Connection*>::iterator itr = m_DistConnections.find(Thread::self());

	if (itr == m_DistConnections.end())
	{
		//pTempConnection = m_pDistConnection;
#ifdef __LOGIN_SERVER__
		pTempConnection = m_pDefaultConnection;
#else
		pTempConnection = m_pWorldDefaultConnection;
#endif
	} 
	else 
	{
		pTempConnection = itr->second;
	}

	return pTempConnection;

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

Connection* DatabaseManager::getCBillingConnection( const string& connName ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	Connection * pTempConnection = NULL;

	hash_map<int, Connection*>::iterator itr;

	itr = m_CBillingConnections.find(Thread::self());

	if( itr != m_CBillingConnections.end() )
	{
		pTempConnection = itr->second;
	}
	else
	{
		throw NoSuchElementException( "No such element CBilling Connection error" );
	}

	//Assert(pTempConnection!=NULL);
	return pTempConnection;

	__END_CATCH
}
/*
////////////////////////////////////////////////////////////////////////////
// PC 방 통합용 Connection 가져오기
////////////////////////////////////////////////////////////////////////////
Connection * DatabaseManager::getPCRoomConnection ( const string& connName ) 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	Connection * pTempConnection = NULL;

	hash_map<int, Connection*>::iterator itr;

	itr = m_PCRoomConnections.find(Thread::self());

	#ifdef __LOGIN_SERVER__

		return m_pPCRoomConnection;

	#else

		Assert( itr != m_PCRoomConnections.end() );

		pTempConnection = itr->second;

		return pTempConnection;

	#endif

	__END_CATCH
}
*/
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
		
	if (m_WorldConnections.empty())	// by sigi. 2002.10.23
	{
		Assert( m_pWorldDefaultConnection );
		return m_pWorldDefaultConnection;
	}
	else	// by sigi. 2002.10.23
	{
		Connection * pTempConnection = NULL;

		hash_map<int, Connection*>::iterator itr = m_WorldConnections.find(TID);

		if (itr == m_WorldConnections.end())
		{
			pTempConnection = m_pWorldDefaultConnection;
		}
		else
		{
			pTempConnection = itr->second;
		}

		return pTempConnection;
	}

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
