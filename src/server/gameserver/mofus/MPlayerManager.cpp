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
#include "Gpackets/GCRequestPowerPointResult.h"
#include "DB.h"

#include <unistd.h>

// constructor
MPlayerManager::MPlayerManager()
	throw(Error)
{
	__BEGIN_TRY

	m_Mutex.setName( "MPlayerManager" );
	m_pCurrentJob = NULL;

	__END_CATCH
}

// destructor
MPlayerManager::~MPlayerManager()
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

// stop thread. unsupport
void MPlayerManager::stop()
	throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}

// main method
void MPlayerManager::run()
	throw()
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

		// 현재 진행중인 Job 확인
		if ( m_pCurrentJob == NULL )
		{
			m_pCurrentJob = popJob();
		}

		// 현재 진행중인 Job 이 있다면
		if ( m_pCurrentJob != NULL )
		{
			// Mofus 와 연결해서 작업을 할 새 Player를 생성
			MPlayer* pPlayer = new MPlayer( m_pCurrentJob );

			// 파워포인트 가져오기 작업 진행
			pPlayer->process();

			// 결과처리
			processResult();

			// Player/Job 삭제
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
	// 새 job 객체를 생성
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
	// 사용자 찾기
	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	Creature* pCreature = g_pPCFinder->getCreature_LOCKED( m_pCurrentJob->getName() );

	if ( pCreature != NULL )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		// 파워포인트를 플레이어에 세팅
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

		// 클라이언트에 알리기
		pPC->getPlayer()->sendPacket( &gcRequestPowerPointResult );
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )
}

// global variable
MPlayerManager* g_pMPlayerManager = NULL;

