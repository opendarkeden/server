//////////////////////////////////////////////////////////////////////
//
// Filename    : SharedServerManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "SharedServerManager.h"
#include "SharedServerClient.h"
#include "Properties.h"
#include "LogClient.h"
#include "Assert.h"

#include "ThreadManager.h"
#include "ThreadPool.h"

#include <unistd.h>
#include "DB.h"
#include "Timeval.h"

#include "Gpackets/GSRequestGuildInfo.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SharedServerManager::SharedServerManager () 
	throw (Error)
{
	__BEGIN_TRY

	m_pSharedServerClient = NULL;

	m_Mutex.setName( "SharedServerManager" );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SharedServerManager::~SharedServerManager () 
	throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pSharedServerClient);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// stop thread
//////////////////////////////////////////////////////////////////////
void SharedServerManager::stop () 
	throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// main method
//////////////////////////////////////////////////////////////////////
void SharedServerManager::run () 
	throw ()
{
	try {

		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_DB");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");
		uint port		= 0;
		if ( g_pConfig->hasKey("DB_PORT") )
			port = g_pConfig->getPropertyInt("DB_PORT");

		Connection* pConnection = new Connection(host, db, user, password, port);
		g_pDatabaseManager->addConnection((int)Thread::self(), pConnection);
		cout << "************************************************************************" << endl;
		cout << "OPEN LOGIN DB" << endl;
		cout << "************************************************************************" << endl;

		Timeval dummyQueryTime;
		getCurrentTime( dummyQueryTime );

		while ( true )
		{
			usleep( 100 );

			// 연결되어 있지 않다면 연결을 시도한다.
			if ( m_pSharedServerClient == NULL )
			{
				Socket* pSocket = NULL;

				try
				{
					string SharedServerIP = g_pConfig->getProperty( "SharedServerIP" );
					uint SharedServerPort = g_pConfig->getPropertyInt( "SharedServerPort" );

					// create socket
					pSocket = new Socket( SharedServerIP, SharedServerPort );

					// connect
					pSocket->connect();

					// make nonblocking socket
					pSocket->setNonBlocking();

					// make no-linger socket
					pSocket->setLinger(0);

					__ENTER_CRITICAL_SECTION(m_Mutex)
					m_pSharedServerClient = new SharedServerClient( pSocket );
					__LEAVE_CRITICAL_SECTION(m_Mutex)

					pSocket = NULL;

					cout << "connection to sharedserver established" << endl;

					// 길드 정보를 가져오도록 요청한다.
					GSRequestGuildInfo gsRequestGuildInfo;
					m_pSharedServerClient->sendPacket( &gsRequestGuildInfo );
				} 
				catch ( Throwable& t )
				{
					cout << "connect to sharedserver fail" << endl;

					try {
						SAFE_DELETE( pSocket );
					} catch (Throwable& t) {
						filelog("sharedServerClient.txt", "[0]%s", t.toString().c_str());
					}

					__ENTER_CRITICAL_SECTION(m_Mutex)
					
					try {
							SAFE_DELETE( m_pSharedServerClient ); 
					} catch (Throwable& t) {
						filelog("sharedServerClient.txt", "[1]%s", t.toString().c_str());
					}
					__LEAVE_CRITICAL_SECTION(m_Mutex)

					// 다음 접속시도시간
					usleep( 500000 );
				}
			}

			// 소켓이 연결되어 있다면 입출력을 처리한다.
			__ENTER_CRITICAL_SECTION(m_Mutex)

			if ( m_pSharedServerClient != NULL )
			{
				try
				{
					m_pSharedServerClient->processInput();
					m_pSharedServerClient->processOutput();
					m_pSharedServerClient->processCommand();
				}
				catch ( Throwable& t )
				{
					cout << t.toString().c_str() << endl;

					try {
						SAFE_DELETE( m_pSharedServerClient );
					} catch (Throwable& t) {
						filelog("sharedServerClient.txt", "[2]%s", t.toString().c_str());
					}
				}
			}

			__LEAVE_CRITICAL_SECTION(m_Mutex)

			// dummy query
			Timeval currentTime;
			getCurrentTime(currentTime);

			if (dummyQueryTime < currentTime)
			{
				g_pDatabaseManager->executeDummyQuery( pConnection );

				// 1시간 ~ 1시간 30분 사이에서 dummy query 시간을 설정한다.
				// timeout이 되지 않게 하기 위해서이다.
				dummyQueryTime.tv_sec += (60+rand()%30) * 60;
			}
		}

	}
	catch (Throwable & t)
	{
		filelog("SHAREDSERVERMANAGER.log", "SharedServerManager::run() 4 : %s", t.toString().c_str());

		cerr << t.toString() << endl;
	}
}

//////////////////////////////////////////////////////////////////////
// send packet to shared server
//////////////////////////////////////////////////////////////////////
void SharedServerManager::sendPacket ( Packet* pPacket )
	throw (ProtocolException , Error)
{
	__ENTER_CRITICAL_SECTION(m_Mutex)
		
	if ( m_pSharedServerClient != NULL )
	{
		m_pSharedServerClient->sendPacket( pPacket );
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}


// global variable definition
SharedServerManager* g_pSharedServerManager = NULL;
