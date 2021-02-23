//////////////////////////////////////////////////////////////////////////////
// Filename    : EventAuth.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventAuth.h"
#include "GamePlayer.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Item.h"

#include "Gpackets/GCAuthKey.h"
#include "Gpackets/GCSystemMessage.h"
#include "EventKick.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::EventAuth (GamePlayer* pGamePlayer) 
	throw (Error)
: Event(pGamePlayer)
{
	// 1ºÐ
	setDeadline(600);
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::~EventAuth () 
	throw ()
{
}

//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventAuth::activate () 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Assert(m_pGamePlayer != NULL);

		if ( !m_pGamePlayer->getCSAuth().IsAuth() )
		{
			filelog("CSAuth.log", "[%s] ÀÎÁõ ½Ã°£ Á¦ÇÑÀ» ÃÊ°úÇß½À´Ï´Ù.", m_pGamePlayer->getID().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage("nProtect GameGuard ÈÏÖ¤Ê§°Ü.Ö´ÐÐÎÄ¼þ´íÎó»òGameGuardÎÄ¼þËð»µ.");
			m_pGamePlayer->sendPacket( &gcSystemMessage );

			EventKick* pKick = new EventKick( m_pGamePlayer );
			pKick->setDeadline(100);
//			pKick->setMessage("GameGuard ÀÎÁõ Á¦ÇÑ ½Ã°£ÀÌ ÃÊ°úÇß½À´Ï´Ù.. 10ÃÊ µÚ¿¡ Á¢¼ÓÀÌ Á¾·áµË´Ï´Ù.");
			pKick->sendMessage();

			m_pGamePlayer->addEvent( pKick );
		}
		else
		{
			DWORD key = m_pGamePlayer->getCSAuth().GetAuthDword();
			GCAuthKey gcKey;
			gcKey.setKey(key);
			m_pGamePlayer->sendPacket(&gcKey);
		}
	}

	// 5ºÐ¿¡ ÇÑ¹ø
	Timeval delay;
	delay.tv_sec = 300;
	delay.tv_usec = 0;

	m_Deadline = m_Deadline + delay;
	
	__END_CATCH
}
