//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneGroupThread.cc
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ZoneGroupThread.h"
#include "ZonePlayerManager.h"
#include "LogClient.h"
#include "DB.h"
#include "VSDateTime.h"
#include "Properties.h"
#include "Profile.h"
#include "Timeval.h"
#include "Gpackets/GMServerInfo.h"

//#define __FULL_PROFILE__

#ifndef __FULL_PROFILE__
#undef beginProfileEx
#define beginProfileEx(name) ((void)0)
#undef endProfileEx
#define endProfileEx(name) ((void)0)
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
ZoneGroupThread::ZoneGroupThread (ZoneGroup* pZoneGroup) 
	
: m_pZoneGroup(pZoneGroup)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
ZoneGroupThread::~ZoneGroupThread () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 쓰레드 메쏘드들은 최상위로 사용되므로 __BEGIN_TRY와 __END_CATCH
// 를 할 필요가 없다. 즉 모든 예외를 잡아서 처리해야 한다는 소리.
//////////////////////////////////////////////////////////////////////////////
void ZoneGroupThread::run () 
	
{
	__BEGIN_DEBUG

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
	cout << " THREAD CONNECT DB " << endl;
	cout << "******************************************************" << endl;

	string dist_host     = g_pConfig->getProperty("UI_DB_HOST");
	string dist_db       = "DARKEDEN";
	string dist_user     = g_pConfig->getProperty("UI_DB_USER");
	string dist_password = g_pConfig->getProperty("UI_DB_PASSWORD");
	uint dist_port		= 0;
	if ( g_pConfig->hasKey("UI_DB_PORT") )
		dist_port = g_pConfig->getPropertyInt("UI_DB_PORT");

	Connection* pDistConnection = new Connection(dist_host, dist_db, dist_user, dist_password, dist_port);
	g_pDatabaseManager->addDistConnection(((int)Thread::self()), pDistConnection);
	cout << "******************************************************" << endl;
	cout << " THREAD CONNECT UIIRIBUTION DB " << endl;
	cout << " TID Number = " << (int)Thread::self()<< endl;
	cout << "******************************************************" << endl;

	/*
	// Login DB 의 PCRoomDBInfo Table 읽어서 Connection 만들기
	Statement * pStmt = NULL;
	pStmt = pDistConnection->createStatement();
	Result * pResult = NULL;
	
	pResult = pStmt->executeQuery("SELECT ID, Host, DB, User, Password FROM PCRoomDBInfo");
	
	if (pResult->next())
	{
		WorldID_t ID = pResult->getInt(1);
		string host = pResult->getString(2);
		string db = pResult->getString(3);
		string user = pResult->getString(4);
		string password = pResult->getString(5);

		cout << "Connection: "
			 << "  ID=" << (int)ID
			 << ", HOST=" << host.c_str()
			 << ", DB=" << db.c_str()
			 << ", User=" << user.c_str() << endl;

		Connection * pConnection = new Connection(host, db, user, password);
		Assert(pConnection!=NULL);

		g_pDatabaseManager->addPCRoomConnection((int)(Thread::self()) , pConnection );
	}
	*/

	Timeval NextTime;
	getCurrentTime(NextTime);
	Timeval currentTime;

	NextTime.tv_sec += 2;

	Timeval dummyQueryTime;
	getCurrentTime(dummyQueryTime);

	try {

	while (true) 
	{

//		beginProfileEx("ZGT_MAIN");
		try {
		beginProfileExNoTry("ZGT_MAIN");

		usleep(100); // CPU 점유율을 줄이기 위해서 강제로 0.001 초동안 쉰다.

		__ENTER_CRITICAL_SECTION((*m_pZoneGroup))

		beginProfileEx("ZG_PP");
		m_pZoneGroup->processPlayers(); // process all players in ZonePlayerManager;
		endProfileEx("ZG_PP");

		beginProfileEx("ZG_HEARTBEAT");
		m_pZoneGroup->heartbeat(); // process all npc, monster, ... in Zones
		endProfileEx("ZG_HEARTBEAT");

		__LEAVE_CRITICAL_SECTION((*m_pZoneGroup))

		getCurrentTime(currentTime);

//		endProfileEx("ZGT_MAIN");
		endProfileExNoCatch("ZGT_MAIN");
		} catch (Throwable&) {
		endProfileExNoCatch("ZGT_MAIN");
		throw;
		}

		if (dummyQueryTime < currentTime)
		{
			g_pDatabaseManager->executeDummyQuery( pConnection );
			g_pDatabaseManager->executeDummyQuery( pDistConnection );

			// 1시간 ~ 1시간 30분 사이에서 dummy query 시간을 설정한다.
		    // timeout이 되지 않게 하기 위해서이다.
		    dummyQueryTime.tv_sec += (60+rand()%30) * 60;
		}


		if (NextTime < currentTime)
		{

			GMServerInfo gmServerInfo;
			m_pZoneGroup->makeZoneUserInfo(gmServerInfo); 

			//outputProfileEx(false, false);
			(g_ProfileSampleManager.getProfileSampleSet())->outputProfileToFile("Profile", false, false,
																				&gmServerInfo);

			
			NextTime.tv_sec = currentTime.tv_sec + 10;
			NextTime.tv_usec = currentTime.tv_usec;

			// 매턴마다 프로파일 데이터를 초기화해준다.
			// 누적 데이터보다는 시간대에 따른 시간을 측정하기 위해서...
			initProfileEx();
		}
	}

	} catch (Throwable& t){
		filelog("zoneGroupThreadError.log", "%s", t.toString().c_str());
		throw;
	}

	__END_DEBUG
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string ZoneGroupThread::toString () const 
	
{
	StringStream msg;
	msg << "ZoneGroupThread("
			<< m_pZoneGroup->toString()
			<< ")";
	return msg.toString();
}
