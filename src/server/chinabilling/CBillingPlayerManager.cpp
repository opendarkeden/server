////////////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayerManager.cpp
//
////////////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPlayerManager.h"
#include "CBillingPlayer.h"
#include "Assert.h"
#include "Properties.h"

#include <unistd.h>
#include "DB.h"
#include "Timeval.h"

/*#define __BEGIN_TRY try {
#define __END_CATCH } catch ( Throwable& t ) {															\
								 cout << t.toString().c_str() << endl;											\
								 filelog( LOGFILE_CBILLING_PLAYER, "%s", t.toString().c_str() );				\
								 try {																			\
									 SAFE_DELETE( m_pCBillingPlayer );											\
								 } catch (Throwable & t ) {														\
									 filelog( LOGFILE_CBILLING_PLAYER, "(delete)%s", t.toString().c_str() );	\
								 }																				\
								 throw t;																		\
							 }
*/
// constructor
CBillingPlayerManager::CBillingPlayerManager()
	throw ( Error )
{
	__BEGIN_TRY

	m_pCBillingPlayer = NULL;

	m_Mutex.setName( "CBillingPlayerManager" );
	m_SendMutex.setName( "CBillingPlayerManager" );

	m_bForceDisconnect = false;

	__END_CATCH
}

// destructor
CBillingPlayerManager::~CBillingPlayerManager()
	throw ( Error )
{
	__BEGIN_TRY

	SAFE_DELETE( m_pCBillingPlayer );

	__END_CATCH
}

// stop thread. unsupport
void CBillingPlayerManager::stop()
	throw ( Error )
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}

// main method
void CBillingPlayerManager::run()
	throw ()
{
	__BEGIN_TRY

	try
	{
		// Player DB 에 Connection 을 하나 연결시켜 둔다.
		string host		= g_pConfig->getProperty( "UI_DB_HOST" );
		string db		= "DARKEDEN";
		string user		= g_pConfig->getProperty( "UI_DB_USER" );
		string password	= g_pConfig->getProperty( "UI_DB_PASSWORD" );

		Connection* pDistConnection = new Connection( host, db, user, password );
		g_pDatabaseManager->addDistConnection( ( (int)Thread::self() ), pDistConnection );
		cout << "***************************************************************" << endl;
		cout << " THREAD CONNECT Player DB - for China Billing System" << endl;
		cout << " TID Number = " << (int)Thread::self() << endl;
		cout << "***************************************************************" << endl;

#ifdef __GAME_SERVER__
		// CBilling Log DB에 Connection 을 하나 연결시켜 둔다.
		string cbhost		= g_pConfig->getProperty( "CBILLING_DB_HOST" );
		string cbdb			= g_pConfig->getProperty( "CBILLING_DB_DB" );
		string cbuser		= g_pConfig->getProperty( "CBILLING_DB_USER" );
		string cbpassword	= g_pConfig->getProperty( "CBILLING_DB_PASSWORD" );

		Connection* pCBillingConnection = new Connection( cbhost, cbdb, cbuser, cbpassword );
		g_pDatabaseManager->addCBillingConnection( ( (int)Thread::self() ), pCBillingConnection );
		cout << "***************************************************************" << endl;
		cout << " THREAD CONNECT China Billing Log DB - for China Billing System" << endl;
		cout << " TID Number = " << (int)Thread::self() << endl;
		cout << "***************************************************************" << endl;
#endif

		Timeval dummyQueryTime;
		getCurrentTime( dummyQueryTime );

		const string&	CBillingServerIP	= g_pConfig->getProperty( "ChinaBillingServerIP");
		uint			CBillingServerPort	= g_pConfig->getPropertyInt( "ChinaBillingServerPort" );

		while ( true )
		{
			usleep( 100 );

			// 연결 되어 있지 않다면 연결을 시도한다.
			if ( m_pCBillingPlayer == NULL )
			{
				Socket* pSocket = NULL;

				try
				{
					// create socket
					pSocket = new Socket( CBillingServerIP, CBillingServerPort );

					// connect
					pSocket->connect();

					// make nonblocking socket
					pSocket->setNonBlocking();

					// make no-linger socket
					pSocket->setLinger( 0 );

					__ENTER_CRITICAL_SECTION( m_Mutex )
					m_pCBillingPlayer = new CBillingPlayer( pSocket );
					__LEAVE_CRITICAL_SECTION( m_Mutex )

					pSocket = NULL;

					cout << "connection to china billing server established - "
						 << CBillingServerIP.c_str() << ":" << CBillingServerPort << endl;
					filelog( LOGFILE_CBILLING_PLAYER, "----- connection established(%s:%d) -----", CBillingServerIP.c_str(), CBillingServerPort );

#ifdef __GAME_SERVER__
					// interval validation packet 을 보낸다.
					sendIntervalValidation();
#endif
				}
				catch ( Throwable& t )
				{
					cout << "connect to china billing server fail - "
						 << CBillingServerIP.c_str() << ":" << CBillingServerPort << endl;
					filelog( LOGFILE_CBILLING_PLAYER, "connect failed(%s:%d)", CBillingServerIP.c_str(), CBillingServerPort );

					try
					{
						SAFE_DELETE( pSocket );
					}
					catch ( Throwable& t )
					{
						filelog( LOGFILE_CBILLING_PLAYER, "[socket release error]%s", t.toString().c_str() );
					}

					__ENTER_CRITICAL_SECTION( m_Mutex )
					try
					{
						SAFE_DELETE( m_pCBillingPlayer );
					}
					catch ( Throwable& t )
					{
						filelog( LOGFILE_CBILLING_PLAYER, "[CBillingPlayer release error]%s", t.toString().c_str() );
					}
					__LEAVE_CRITICAL_SECTION( m_Mutex )

					// 다음 접속 시도 시간
					usleep( 1000000 );		// 1초
				}
			}

			// 소켓이 연결되어 있다면 입출력을 처리한다.
			__ENTER_CRITICAL_SECTION( m_Mutex )


			if ( m_pCBillingPlayer != NULL )
			{
				__BEGIN_TRY

				if ( m_pCBillingPlayer->getSocket()->getSockError() )
				{
					filelog( LOGFILE_CBILLING_ERROR, "CBillingPlayer socket error" );

					try
					{
						SAFE_DELETE( m_pCBillingPlayer );
					}
					catch ( Throwable& t )
					{
						filelog( LOGFILE_CBILLING_PLAYER, "[CBillingPlayer release error]%s", t.toString().c_str() );
					}
				}
				else
				{
					try
					{
						m_pCBillingPlayer->processInput();
						
						// lock send mutex. m_Mutex cause deadlock with LoginPlayerManager lock
						__ENTER_CRITICAL_SECTION( m_SendMutex )
						m_pCBillingPlayer->processOutput();
						__LEAVE_CRITICAL_SECTION( m_SendMutex )

						m_pCBillingPlayer->processCommand();
					}
					catch ( Throwable& t )
					{
						filelog( LOGFILE_CBILLING_ERROR, "CBillingPlayer process error: %s", t.toString().c_str() );

						// delete player
						try
						{
							SAFE_DELETE( m_pCBillingPlayer );
						}
						catch ( Throwable& t )
						{
							filelog( LOGFILE_CBILLING_PLAYER, "[CBillingPlayer release error]%s", t.toString().c_str() );
						}
					}
				}

				__END_CATCH
			}

			__LEAVE_CRITICAL_SECTION( m_Mutex )

			// dummy query
			Timeval currentTime;
			getCurrentTime( currentTime );

			if ( dummyQueryTime < currentTime )
			{
				g_pDatabaseManager->executeDummyQuery( pDistConnection );

#ifdef __GAME_SERVER__
				g_pDatabaseManager->executeDummyQuery( pCBillingConnection );
#endif

				// 1시간 ~ 1시간 30분 사이에서 dummy query 시간을 설정한다.
				// timeout 이 되지 않게 하기 위해서이다.
				dummyQueryTime.tv_sec += (60+rand()%30) * 60;
			}

			if ( m_pCBillingPlayer != NULL && m_bForceDisconnect )
			{
				m_bForceDisconnect = false;
				filelog( LOGFILE_CBILLING_PLAYER, "Disconnect Force" );

				try
				{
					__ENTER_CRITICAL_SECTION( m_Mutex )

					SAFE_DELETE( m_pCBillingPlayer );

					__LEAVE_CRITICAL_SECTION( m_Mutex )
				}
				catch ( Throwable& t )
				{
					filelog( LOGFILE_CBILLING_PLAYER, "(delete)%s", t.toString().c_str() );
				}
			}
		}
	}
	catch ( Throwable& t )
	{
		filelog( "cbillingPlayerManager.log", "CBillingPlayerManager::run() : %s", t.toString().c_str() );

		cerr << t.toString().c_str() << endl;
	}

	__END_CATCH
}

#ifdef __LOGIN_SERVER__

void CBillingPlayerManager::sendLogin( LoginPlayer* pLoginPlayer )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_SendMutex )

	if ( m_pCBillingPlayer != NULL )
	{
		m_pCBillingPlayer->sendLogin( pLoginPlayer );
	}

	__LEAVE_CRITICAL_SECTION( m_SendMutex )
	__END_CATCH
}

#elif defined(__GAME_SERVER__)

void CBillingPlayerManager::sendIntervalValidation()
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex )

	if ( m_pCBillingPlayer != NULL )
	{
		m_pCBillingPlayer->sendIntervalValidation();

		// 바로 보내버린다.
		m_pCBillingPlayer->processOutput();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	__END_CATCH
}

bool CBillingPlayerManager::sendLogin( GamePlayer* pGamePlayer )
	throw ( ProtocolException, Error )
{
	bool ret = true;

	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex )


	if ( m_pCBillingPlayer != NULL )
	{
		m_pCBillingPlayer->sendLogin( pGamePlayer );
	}
	else
	{
		ret = false;
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	__END_CATCH

	return ret;
}

bool CBillingPlayerManager::sendMinusPoint( GamePlayer* pGamePlayer )
	throw ( ProtocolException, Error )
{
	bool ret = true;

	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex )


	if ( m_pCBillingPlayer != NULL )
	{
		m_pCBillingPlayer->sendMinusPoint( pGamePlayer );
		m_pCBillingPlayer->processOutput();
	}
	else
	{
		ret = false;
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	__END_CATCH

	return ret;
}

void CBillingPlayerManager::sendMinusMinute( GamePlayer* pGamePlayer )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex )

	if ( m_pCBillingPlayer != NULL )
	{
		m_pCBillingPlayer->sendMinusMinute( pGamePlayer );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	__END_CATCH
}

void CBillingPlayerManager::sendLogout( GamePlayer* pGamePlayer )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex )

	if ( m_pCBillingPlayer != NULL )
	{
		m_pCBillingPlayer->sendLogout( pGamePlayer );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	__END_CATCH
}

#endif

int CBillingPlayerManager::getVersionNumber() const
	throw ()
{
	__BEGIN_TRY

	int version_no = g_pConfig->getPropertyInt( "ChinaBillingVersionNo" );

	return version_no;

	__END_CATCH
}

int CBillingPlayerManager::getMinusIntervalInt() const
	throw ()
{
	__BEGIN_TRY

	static int interval = g_pConfig->getPropertyInt( "ChinaBillingMinusInterval" );

	return interval;

	__END_CATCH
}

string CBillingPlayerManager::getMinusInterval() const
	throw ()
{
	__BEGIN_TRY

	static string interval = g_pConfig->getProperty( "ChinaBillingMinusInterval" );

	return interval;

	__END_CATCH
}

// global variable definition
CBillingPlayerManager* g_pCBillingPlayerManager = NULL;

