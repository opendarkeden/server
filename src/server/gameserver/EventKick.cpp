//////////////////////////////////////////////////////////////////////////////
// Filename    : EventKick.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventKick.h"
#include "GamePlayer.h"
#include "StringPool.h"
	
#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// class EventKick member methods
//////////////////////////////////////////////////////////////////////////////

EventKick::EventKick(GamePlayer* pGamePlayer) 
	
: Event(pGamePlayer)
{
//	m_pKickZone = NULL;
//	m_X = m_Y = 0;
}

EventKick::~EventKick() 
	
{
}

//----------------------------------------------------------------------
// affect
//----------------------------------------------------------------------
void EventKick::sendMessage()
	
{
	__BEGIN_TRY

	Assert(m_pGamePlayer != NULL);
	Creature * pCreature = m_pGamePlayer->getCreature();

	Timeval currentTime;
	getCurrentTime(currentTime);

	Turn_t       RemainTime = max(0, (int)(m_Deadline.tv_sec-currentTime.tv_sec));

    char msg[50];
    sprintf( msg, g_pStringPool->c_str( STRID_DISCONNECT_COUNT_DOWN ),
                    (int)RemainTime );

    string sMsg( msg );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(sMsg);
	pCreature->getPlayer()->sendPacket( &gcSystemMessage );

	__END_CATCH
}


void EventKick::activate () 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG


	Assert(m_pGamePlayer != NULL);

	m_pGamePlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
	m_pGamePlayer->setItemRatioBonusPoint(5);

	__END_DEBUG
	__END_CATCH
}

string EventKick::toString () const 
	
{
	StringStream msg;
	msg << "EventKick("
		<< ")";
	return msg.toString();
}
