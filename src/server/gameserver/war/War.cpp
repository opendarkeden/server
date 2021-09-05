///////////////////////////////////////////////////////////////////
// ���￡ ���� �������� ���� �� ���� ���� �� ����� ó����ƾ ����
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "War.h"
#include "Mutex.h"
#include "WarSystem.h"
#include "Properties.h"
#include "DB.h"
#include "Assert.h"
#include "ZoneGroupManager.h"
#include "HolyLandRaceBonus.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneUtil.h"
#include "CastleInfoManager.h"
#include "ShrineInfoManager.h"
#include "ZoneInfoManager.h"
#include "PCManager.h"

#include "StringStream.h"
#include "StringPool.h"

#include "GCSystemMessage.h"
#include "GCNoticeEvent.h"

//--------------------------------------------------------------------------------
// static members
//--------------------------------------------------------------------------------
Mutex	War::m_Mutex;
WarID_t	War::m_WarIDRegistry = 0;

//--------------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------------
War::War( WarState warState, WarID_t warID )
: m_State( warState )
{
	if (warID==0)
	{
		m_WarIDRegistry += g_pWarSystem->getWarIDSuccessor();
		m_WarID = m_WarIDRegistry;
	}
	else
	{
		m_WarID = warID;
	}
}

War::~War()
{
}

//--------------------------------------------------------------------------------
//
// init WarID Registry
//
//--------------------------------------------------------------------------------
void War::initWarIDRegistry()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL; 
	m_WarIDRegistry = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pCountResult = pStmt->executeQueryString("SELECT COUNT(*) from WarScheduleInfo");
		pCountResult->next();
		int count = pCountResult->getDWORD(1);
		SAFE_DELETE(pStmt);

		if (count != 0)
		{
			//pStmt = g_pDatabaseManager->getConnection("DIST_DARKEDEN")->createStatement();
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			Result* pResult = pStmt->executeQueryString("SELECT MAX(WarID) FROM WarScheduleInfo");
			pResult->next();
			m_WarIDRegistry = pResult->getDWORD(1);
			SAFE_DELETE(pStmt);
		}

		static WarID_t WarIDBase 		= g_pConfig->getPropertyInt("ServerID");
		static WarID_t WarIDSuccessor 	= g_pConfig->getPropertyInt("ServerCount");
		m_WarIDRegistry += (WarIDSuccessor - (m_WarIDRegistry % WarIDSuccessor)) + WarIDBase;
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	cout << "War::WarIDRegistry:" << m_WarIDRegistry << endl;

	__END_CATCH
}

const string& War::getState2DBString() const
{
	Assert(m_State < MAX_WAR_STATE);

	static string WarState[] =
	{
		"WAIT",
		"START",
		"END",
		"CANCEL"
	};

	return WarState[m_State];
}

//--------------------------------------------------------------------------------
//
// execute
//
//--------------------------------------------------------------------------------
void War::execute()
	
{
	__BEGIN_TRY

	switch ( m_State )
	{
		case WAR_STATE_WAIT:
			executeStart();
			m_State = WAR_STATE_CURRENT;
			break;

		case WAR_STATE_CURRENT:
			executeEnd();
			m_State = WAR_STATE_END;
			break;

		case WAR_STATE_END:
			Assert(false);
			break;

		default:
			Assert(false);
	}

	// execute()�Ŀ��� WarSchedule�� heartbeat()���� DB�� Status�� �����ϰ� �ȴ�.

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// send Message
//
//--------------------------------------------------------------------------------
// ���� ������ ��
//--------------------------------------------------------------------------------
void War::sendWarStartMessage() const
	
{
	__BEGIN_TRY
		
	GCSystemMessage gcSystemMessage;
	char str[80];
	//sprintf(str, "%s�� ���۵Ǿ����ϴ�.", getWarName().c_str());
	sprintf(str, g_pStringPool->c_str( STRID_WAR_START ), getWarName().c_str());

	gcSystemMessage.setMessage( str );
	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	filelog( "WarLog.txt", "[WarID=%u] %s", (int)m_WarID, str );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// ���� ���� ��
//--------------------------------------------------------------------------------
void War::sendWarEndMessage() const
	
{
	__BEGIN_TRY
		
	GCSystemMessage gcSystemMessage;
	char str[80];
//	sprintf(str, "%s�� �������ϴ�.", getWarName().c_str());
	sprintf(str, g_pStringPool->c_str( STRID_WAR_END ), getWarName().c_str());

	gcSystemMessage.setMessage( str );
	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	filelog( "WarLog.txt", "[WarID=%u] %s", (int)m_WarID, str );

	__END_CATCH
}

