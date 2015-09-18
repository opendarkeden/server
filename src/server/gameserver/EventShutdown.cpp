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

#include <map>

#include "DB.h"
//////////////////////////////////////////////////////////////////////////////
// class EventShutdown member methods
//////////////////////////////////////////////////////////////////////////////

EventShutdown::EventShutdown(GamePlayer* pGamePlayer )
	throw()
	:Event(pGamePlayer)
{
}

void EventShutdown::activate () 
	throw(Error)
{
	__BEGIN_TRY

	try
	{
		const map<ZoneGroupID_t, ZoneGroup*>& zoneGroups = g_pZoneGroupManager->getZoneGroups();
		map<ZoneGroupID_t, ZoneGroup*>::const_iterator itr = zoneGroups.begin();

		for (; itr != zoneGroups.end(); itr++ )
		{
			ZonePlayerManager* pZonePlayerManager = itr->second->getZonePlayerManager();

			pZonePlayerManager->clearPlayers();
		}

		g_pIncomingPlayerManager->clearPlayers();
	}
	catch (Throwable& t )
	{
		// ¹«½Ã
	}

#ifdef __CONNECT_BILLING_SYSTEM__
	// ¸ðµç ºô¸µ Á¤º¸¸¦ »èÁ¦ÇÑ´Ù.
	g_pBillingPlayerManager->sendPayInit();
#endif

	// ÇÁ·Î¼¼½º Á¾·á. ²¥²¥~ Á×¾î¶ó~~ ²¥²¥~
	if (g_pVariableManager->isKillDaemonCtl() == 1 )
	{
		kill(getppid(), 9);
	}
    __END_CATCH
}

string EventShutdown::toString () const 
	throw()
{
	StringStream msg;
	msg << "EventShutdown("
		<< ")";
	return msg.toString();
}
