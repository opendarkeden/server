//////////////////////////////////////////////////////////////////////////////
// Filename    : EventCBilling.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventCBilling.h"
#include "GamePlayer.h"
#include "chinabilling/CBillingPlayerManager.h"
#include "Assert.h"


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventCBilling::EventCBilling (GamePlayer* pGamePlayer) 
	
: Event(pGamePlayer),
  m_TrySendLoginCount(0)
{
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventCBilling::~EventCBilling () 
	
{
}

			
//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventCBilling::activate () 
	
{
	__BEGIN_TRY

	Assert(m_pGamePlayer != NULL);

	if ( !m_pGamePlayer->isCBillingVerified() )
	{
		// 아직 Login 패킷을 보내지 못했다면 다시 보낸다. ( 연결이 끊겨 있어서 보내지 못한 생태이다. )
		m_pGamePlayer->setCBillingVerified( g_pCBillingPlayerManager->sendLogin( m_pGamePlayer ) );
		m_TrySendLoginCount++;
	}

	// Login 패킷을 보냈다면 minus point packet 을 보내고, 아니라면 쌓아 둔다.
	if ( m_pGamePlayer->isCBillingVerified() )
	{
		// 빌링 패킷을 보낸다. minus point/minute
		if ( !g_pCBillingPlayerManager->sendMinusPoint( m_pGamePlayer ) )
		{
			m_pGamePlayer->increaseMissedMinusPointPacket();
		}

		// send missed minus point packet
		while ( m_pGamePlayer->hasMissedMinusPointPacket() )
		{
			if ( g_pCBillingPlayerManager->sendMinusPoint( m_pGamePlayer ) )
			{
				m_pGamePlayer->decreaseMissedMinusPointPacket();
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		// Login packet 을 보내지 못한 상태이다. minus packet 도 못보낸걸로 하고 쌓아둔다.
		m_pGamePlayer->increaseMissedMinusPointPacket();
	}

	// 다음에 보낼 시간 설정한다. 분 단위
	static int interval = g_pCBillingPlayerManager->getMinusIntervalInt();

	Timeval delay;
	delay.tv_sec = interval * 60;
	delay.tv_usec = 0;

	m_Deadline = m_Deadline + delay;
	
	__END_CATCH
}
