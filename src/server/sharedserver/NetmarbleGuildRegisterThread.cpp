/////////////////////////////////////////////////////////////////////
// Filename		: NetmarbleGuildRegisterThread.cpp
// Written by	: bezz@darkeden.com
// Description	:
/////////////////////////////////////////////////////////////////////

// include files
#include "NetmarbleGuildRegisterThread.h"
#include "Properties.h"
#include "Timeval.h"
#include "DB.h"
#include "Python.h"

// constructor
NetmarbleGuildRegisterThread::NetmarbleGuildRegisterThread()
	throw ( Error )
{
	__BEGIN_TRY

	m_Mutex.setName( "NetmarbleGuildRegisterThread" );

	__END_CATCH
}

// destructor
NetmarbleGuildRegisterThread::~NetmarbleGuildRegisterThread()
	throw ( Error )
{
}

// initialize
void NetmarbleGuildRegisterThread::init()
	throw ( Error )
{
}

// thread main loop
void NetmarbleGuildRegisterThread::run()
	throw ( Error )
{
	__BEGIN_DEBUG

	// create GAME Database Connection
	string host		= g_pConfig->getProperty( "DB_HOST" );
	string db		= g_pConfig->getProperty( "DB_DB" );
	string user		= g_pConfig->getProperty( "DB_USER" );
	string password	= g_pConfig->getProperty( "DB_PASSWORD" );

	Connection* pConnection = new Connection( host, db, user, password );
	g_pDatabaseManager->addConnection( (int)Thread::self(), pConnection );
    cout << "******************************************************" << endl;
    cout << " THREAD CONNECT DB " << endl;
    cout << "******************************************************" << endl;

	// create PLAYER Database Connection
    string dist_host     = g_pConfig->getProperty("UI_DB_HOST");
    string dist_db       = "DARKEDEN";
    string dist_user     = g_pConfig->getProperty("UI_DB_USER");
    string dist_password = g_pConfig->getProperty("UI_DB_PASSWORD");

    Connection* pDistConnection = new Connection(dist_host, dist_db, dist_user, dist_password);
    g_pDatabaseManager->addDistConnection(((int)Thread::self()), pDistConnection);
    cout << "******************************************************" << endl;
    cout << " THREAD CONNECT UIIRIBUTION DB " << endl;
    cout << " TID Number = " << (int)Thread::self()<< endl;
    cout << "******************************************************" << endl;


	////////////////////////////////////////////////////////////////////////////
	// initialize PYTHON
	////////////////////////////////////////////////////////////////////////////
	// py init
	Py_Initialize();

	// import py module
	PyRun_SimpleString( "import httdlib, urllib" );
	////////////////////////////////////////////////////////////////////////////

	try
	{
		Timeval dummyQueryTime;
		getCurrentTime( dummyQueryTime );

		while ( true )
		{
			// 길드 등록
			registerGuild();

			// for context switch
			usleep( 100 );
		}
	}
	catch ( Throwable& t )
	{
		filelog( "NetmarbleGuildRegisterThread.log", "%s", t.toString().c_str() );
		throw;
	}

	////////////////////////////////////////////////////////////////////////////
	// finalize PYTHON
	////////////////////////////////////////////////////////////////////////////
	// py finalize
	Py_Finalize();
	////////////////////////////////////////////////////////////////////////////

	__END_DEBUG
}

// 넷마블에 등록할 길드 아이디를 쌓는다.
void NetmarbleGuildRegisterThread::pushGuildID( GuildID_t guildID )
{
	__ENTER_CRITICAL_SECTION( m_Mutex )

	m_GuildIDs.push( guildID );

	__LEAVE_CRITICAL_SECTION( m_Mutex )
}

// 길드 정보를 넷마블 쪽으로 등록한다.
void NetmarbleGuildRegisterThread::registerGuild()
{
	GuildID_t guildID;

	if ( m_GuildIDs.empty() )
		return;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	guildID = m_GuildIDs.front();
	m_GuildIDs.pop();

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	////////////////////////////////////////////////////////////////////////////
	// get guild data from database
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	// register guild data to Netmarble
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

}

// external variable definition
NetmarbleGuildRegisterThread* g_pNetmarbleGuildRegisterThread = NULL;

