//////////////////////////////////////////////////////////////////////////////
// Filename    : EventSystemMessage.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventSystemMessage.h"
#include "GamePlayer.h"
	
#include "Gpackets/GCSystemMessage.h"


//////////////////////////////////////////////////////////////////////////////
// class EventSystemMessage member methods
//////////////////////////////////////////////////////////////////////////////

EventSystemMessage::EventSystemMessage(GamePlayer* pGamePlayer) 
	throw()
: Event(pGamePlayer)
{
//	m_pSystemMessageZone = NULL;
//	m_X = m_Y = 0;
}

EventSystemMessage::~EventSystemMessage() 
	throw()
{
}

void EventSystemMessage::addMessage (const string& msg) 
	throw (Error)
{
	__BEGIN_TRY

	m_Messages.push_back( msg );

	__END_CATCH
}

//----------------------------------------------------------------------
// affect
//----------------------------------------------------------------------
void EventSystemMessage::activate () 
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pGamePlayer != NULL);
	Creature * pCreature = m_pGamePlayer->getCreature();

	GCSystemMessage gcSystemMessage;

	list<string>::const_iterator itr = m_Messages.begin();

	while (itr!=m_Messages.end())
	{
		gcSystemMessage.setMessage( *itr );
		pCreature->getPlayer()->sendPacket( &gcSystemMessage );

		itr++;
	}

	//setNextTime( m_MessageTick );

	__END_CATCH
}

string EventSystemMessage::toString () const 
	throw ()
{
	StringStream msg;
	msg << "EventSystemMessage("
		<< ")";
	return msg.toString();
}
