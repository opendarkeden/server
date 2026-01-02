/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayerManager.cpp
// Desc		:
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "MPlayerManager.h"
#include "MPlayer.h"
#include "Assert.h"
#include "Properties.h"
#include "PlayerCreature.h"
#include "PCFinder.h"

#include "PKTError.h"
#include "GCRequestPowerPointResult.h"
#include "DB.h"

#include <unistd.h>

// constructor
MPlayerManager::MPlayerManager()
	
{
	__BEGIN_TRY

	m_Mutex.setName( "MPlayerManager" );
	m_pCurrentJob = NULL;

	__END_CATCH
}

// destructor
MPlayerManager::~MPlayerManager() noexcept
	
{
	// no owning members to clean; keep noexcept
}

// stop thread. unsupport
void MPlayerManager::stop()
	
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}

// main method
void MPlayerManager::run()
{
	__BEGIN_TRY

	string host     = g_pConfig->getProperty("DB_HOST");
	string db       = g_pConfig->getProperty("DB_DB");
	string user     = g_pConfig->getProperty("DB_USER");
	string password = g_pConfig->getProperty("DB_PASSWORD");
	uint port		= 0;
	if ( g_pConfig->hasKey("DB_PORT") )
		port = g_pConfig->getPropertyInt("DB_PORT");

	Connection* pConnection = new Connection(host, db, user, password, port);
	g_pDatabaseManager->addConnection((int)Thread::self(), pConnection);
	cout << "******************************************************" << endl;
	cout << " Mofus THREAD CONNECT DB " << endl;
	cout << "******************************************************" << endl;

	Timeval dummyQueryTime;
	getCurrentTime( dummyQueryTime );

	while ( 1 )
	{
		usleep( 100 );

		// Fetch a job if none is currently running.
		if ( m_pCurrentJob == NULL )
		{
			m_pCurrentJob = popJob();
		}

		// If a job is available, process it.
		if ( m_pCurrentJob != NULL )
		{
			// Spin up an MPlayer to handle the job.
			MPlayer* pPlayer = new MPlayer( m_pCurrentJob );

			// Run the player.
			pPlayer->process();

			// Persist any job results.
			processResult();

			// Clean up player and job objects.
			SAFE_DELETE( pPlayer );
			SAFE_DELETE( m_pCurrentJob );
		}

		Timeval currentTime;
		getCurrentTime( currentTime );

		if ( dummyQueryTime < currentTime )
		{
			g_pDatabaseManager->executeDummyQuery( pConnection );

			dummyQueryTime.tv_sec += ( 60 + rand() % 30 ) * 60;
		}
	}

	__END_CATCH
}

void MPlayerManager::addJob( const string& userID, const string& name, const string& cellnum )
{
	// Allocate and enqueue a new job.
	MJob* pJob = new MJob( userID, name, cellnum );

	__ENTER_CRITICAL_SECTION( m_Mutex )

	m_Jobs.push_back( pJob );

	__LEAVE_CRITICAL_SECTION( m_Mutex )

}

MJob* MPlayerManager::popJob()
{
	MJob* pJob = NULL;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	if ( !m_Jobs.empty() )
	{
		pJob = m_Jobs.front();
		m_Jobs.pop_front();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	return pJob;
}

void MPlayerManager::processResult()
{
	// Locate the target player creature.
	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	Creature* pCreature = g_pPCFinder->getCreature_LOCKED( m_pCurrentJob->getName() );

	if ( pCreature != NULL )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		// Refresh the player's PowerPoint from the database value.
		pPC->setPowerPoint( loadPowerPoint( pPC->getName() ) );

		GCRequestPowerPointResult gcRequestPowerPointResult;

		gcRequestPowerPointResult.setSumPowerPoint( pPC->getPowerPoint() );
		gcRequestPowerPointResult.setRequestPowerPoint( m_pCurrentJob->getPowerPoint() );

		if ( m_pCurrentJob->getErrorCode() == 0 )
		{
			gcRequestPowerPointResult.setErrorCode( 0 );
		}
		else
		{
			switch ( m_pCurrentJob->getErrorCode() )
			{
				case MERR_SERVER :
					gcRequestPowerPointResult.setErrorCode( GCRequestPowerPointResult::SERVER_ERROR );
					break;

				case MERR_CONFIRM:
				case MERR_PACKET:
					gcRequestPowerPointResult.setErrorCode( GCRequestPowerPointResult::CONNECT_ERROR );
					break;

				case MERR_PROCESS:
					gcRequestPowerPointResult.setErrorCode( GCRequestPowerPointResult::PROCESS_ERROR );
					break;

				case MERR_SEARCH :
					gcRequestPowerPointResult.setErrorCode( GCRequestPowerPointResult::NO_MEMBER );
					break;
					
				case MERR_NULLPOINT :
					gcRequestPowerPointResult.setErrorCode( GCRequestPowerPointResult::NO_POINT );
					break;

				case MERR_MATCHING :
					gcRequestPowerPointResult.setErrorCode( GCRequestPowerPointResult::NO_MATCHING );
					break;

				default:
					filelog( MOFUS_ERROR_FILE, "INVALID ERROR CODE:%d", m_pCurrentJob->getErrorCode() );
					return;
			}
		}

		// Send the result back to the client.
		pPC->getPlayer()->sendPacket( &gcRequestPowerPointResult );
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )
}

// global variable
MPlayerManager* g_pMPlayerManager = NULL;

