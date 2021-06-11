////////////////////////////////////////////////////////////////////////////////
//
// filename		: SBillingPlayerManager.cpp
//
////////////////////////////////////////////////////////////////////////////////

// include files
#include "SBillingPlayerManager.h"
#include "SBillingPlayer.h"
#include "SProfile.h"
#include "Assert.h"
#include "Properties.h"

#include <unistd.h>
#include "Timeval.h"

// constructor
SBillingPlayerManager::SBillingPlayerManager()
	throw ( Error )
{
	__BEGIN_TRY

	m_pSBillingPlayer = NULL;

	int connections = g_pConfig->getPropertyInt( "Connections" );
	Assert( connections > 0 && connections <= 15 );

	m_SBillingPlayers = connections;

	m_pSBillingPlayer = new (SBillingPlayer*)[m_SBillingPlayers];

	for ( int i = 0; i < m_SBillingPlayers; ++i )
	{
		m_pSBillingPlayer[i] = NULL;
	}

	m_Mutex = new Mutex[ m_SBillingPlayers ];

	for ( int i = 0; i < m_SBillingPlayers; ++i )
	{
		m_Mutex[i].setName( "SBillingPlayerManager" );
	}

	__END_CATCH
}

// destructor
SBillingPlayerManager::~SBillingPlayerManager()
	throw ( Error )
{
	__BEGIN_TRY

	for ( int i = 0; i < m_SBillingPlayers; ++i )
	{
		SAFE_DELETE( m_pSBillingPlayer[i] );
	}

	SAFE_DELETE_ARRAY( m_pSBillingPlayer );

	__END_CATCH
}

// stop thread. unsupport
void SBillingPlayerManager::stop()
	throw ( Error )
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}

// main method
void SBillingPlayerManager::run()
	throw ()
{
	__BEGIN_TRY

	try
	{
		const string&	SBillingServerIP	= g_pConfig->getProperty( "ChinaBillingServerIP");
		uint			SBillingServerPort	= g_pConfig->getPropertyInt( "ChinaBillingServerPort" );

		Timeval pfTime;
		getCurrentTime( pfTime );

		while ( true )
		{
			usleep( 100 );

			for ( int i = 0; i < m_SBillingPlayers; ++i )
			{

				// 연결 되어 있지 않다면 연결을 시도한다.
				if ( m_pSBillingPlayer[i] == NULL )
				{
					Socket* pSocket = NULL;

					try
					{
						// create socket
						pSocket = new Socket( SBillingServerIP, SBillingServerPort );

						// connect
						pSocket->connect();

						// make nonblocking socket
						pSocket->setNonBlocking();

						// make no-linger socket
						pSocket->setLinger( 0 );

						__ENTER_CRITICAL_SECTION( m_Mutex[i] )
						m_pSBillingPlayer[i] = new SBillingPlayer( pSocket );
						__LEAVE_CRITICAL_SECTION( m_Mutex[i] )

						pSocket = NULL;

						cout << "connection to china billing server established - "
							 << SBillingServerIP.c_str() << ":" << SBillingServerPort << endl;
						filelog( LOGFILE_CBILLING_PLAYER, "----- connection established(%s:%d) -----", SBillingServerIP.c_str(), SBillingServerPort );

						// interval validation packet 을 보낸다.
						sendIntervalValidation( i );
					}
					catch ( Throwable& t )
					{
						cout << "connect to china billing server fail - "
							 << SBillingServerIP.c_str() << ":" << SBillingServerPort << endl;
						filelog( LOGFILE_CBILLING_PLAYER, "connect failed(%s:%d)", SBillingServerIP.c_str(), SBillingServerPort );

						try
						{
							SAFE_DELETE( pSocket );
						}
						catch ( Throwable& t )
						{
							filelog( LOGFILE_CBILLING_PLAYER, "[socket release error]%s", t.toString().c_str() );
						}

						__ENTER_CRITICAL_SECTION( m_Mutex[i] )
						try
						{
							SAFE_DELETE( m_pSBillingPlayer[i] );
						}
						catch ( Throwable& t )
						{
							filelog( LOGFILE_CBILLING_PLAYER, "[SBillingPlayer release error]%s", t.toString().c_str() );
						}
						__LEAVE_CRITICAL_SECTION( m_Mutex[i] )

						// 다음 접속 시도 시간
						usleep( 1000000 );		// 1초
					}
				}

				// 소켓이 연결되어 있다면 입출력을 처리한다.
				__ENTER_CRITICAL_SECTION( m_Mutex[i] )

				if ( m_pSBillingPlayer[i] != NULL )
				{
					__BEGIN_TRY

					if ( m_pSBillingPlayer[i]->getSocket()->getSockError() )
					{
						try
						{
							SAFE_DELETE( m_pSBillingPlayer[i] );
						}
						catch ( Throwable& t )
						{
							filelog( LOGFILE_CBILLING_PLAYER, "[SBillingPlayer release error]%s", t.toString().c_str() );
						}
					}
					else
					{
						try
						{
							m_pSBillingPlayer[i]->processInput();
							m_pSBillingPlayer[i]->processOutput();
							m_pSBillingPlayer[i]->processCommand();
						}
						catch ( Throwable& t )
						{
							filelog( LOGFILE_CBILLING_ERROR, "SBillingPlayer process error: %s", t.toString().c_str() );

							// delete player
							try
							{
								SAFE_DELETE( m_pSBillingPlayer[i] );
							}
							catch ( Throwable& t )
							{
								filelog( LOGFILE_CBILLING_PLAYER, "[SBillingPlayer release error]%s", t.toString().c_str() );
							}
						}
					}

					__END_CATCH
				}

				__LEAVE_CRITICAL_SECTION( m_Mutex[i] )
			}

			Timeval currentTime;
			getCurrentTime( currentTime );

			if ( pfTime < currentTime )
			{
				g_pSProfile->print();

				pfTime.tv_sec += 10;
			}
		}
	}
	catch ( Throwable& t )
	{
		filelog( "cbillingPlayerManager.log", "SBillingPlayerManager::run() : %s", t.toString().c_str() );

		cerr << t.toString().c_str() << endl;
	}

	__END_CATCH
}

void SBillingPlayerManager::sendIntervalValidation( int i )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex[i] )

	if ( m_pSBillingPlayer[i] != NULL )
	{
		m_pSBillingPlayer[i]->sendIntervalValidation();

		// 바로 보내버린다.
		m_pSBillingPlayer[i]->processOutput();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex[i] )
	__END_CATCH
}

bool SBillingPlayerManager::sendLogin( PayUser* pPayUser, int i )
	throw ( ProtocolException, Error )
{
	bool ret = true;

	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex[i] )


	if ( m_pSBillingPlayer[i] != NULL )
	{
		m_pSBillingPlayer[i]->sendLogin( pPayUser );
	}
	else
	{
		ret = false;
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex[i] )
	__END_CATCH

	return ret;
}

bool SBillingPlayerManager::sendMinusPoint( PayUser* pPayUser, int i )
	throw ( ProtocolException, Error )
{
	bool ret = true;

	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex[i] )


	if ( m_pSBillingPlayer[i] != NULL )
	{
		m_pSBillingPlayer[i]->sendMinusPoint( pPayUser );
	}
	else
	{
		ret = false;
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex[i] )
	__END_CATCH

	return ret;
}

void SBillingPlayerManager::sendMinusMinute( PayUser* pPayUser, int i )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex[i] )

	if ( m_pSBillingPlayer[i] != NULL )
	{
		m_pSBillingPlayer[i]->sendMinusMinute( pPayUser );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex[i] )
	__END_CATCH
}

void SBillingPlayerManager::sendLogout( PayUser* pPayUser, int i )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	__ENTER_CRITICAL_SECTION( m_Mutex[i] )

	if ( m_pSBillingPlayer[i] != NULL )
	{
		m_pSBillingPlayer[i]->sendLogout( pPayUser );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex[i] )
	__END_CATCH
}

int SBillingPlayerManager::getVersionNumber() const
	throw ()
{
	__BEGIN_TRY

	int version_no = g_pConfig->getPropertyInt( "ChinaBillingVersionNo" );

	return version_no;

	__END_CATCH
}

int SBillingPlayerManager::getMinusIntervalInt() const
	throw ()
{
	__BEGIN_TRY

	static int interval = g_pConfig->getPropertyInt( "ChinaBillingMinusInterval" );

	return interval;

	__END_CATCH
}

string SBillingPlayerManager::getMinusInterval() const
	throw ()
{
	__BEGIN_TRY

	static string interval = g_pConfig->getProperty( "ChinaBillingMinusInterval" );

	return interval;

	__END_CATCH
}

// global variable definition
SBillingPlayerManager* g_pSBillingPlayerManager = NULL;

