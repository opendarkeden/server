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

#include "GCAuthKey.h"
#include "GCSystemMessage.h"
#include "EventKick.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::EventAuth (GamePlayer* pGamePlayer) 
	throw(Error)
: Event(pGamePlayer)
{
	// 1분
	setDeadline(600);
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::~EventAuth () 
	throw()
{
}

//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventAuth::activate () 
	throw(Error)
{
	__BEGIN_TRY
/*
	if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Assert(m_pGamePlayer != NULL);

		if (!m_pGamePlayer->getCSAuth().IsAuth() )
		{
			filelog("CSAuth.log", "[%s] 인증 시간 제한을 초과했습니다.", m_pGamePlayer->getID().c_str());

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage("nProtect GameGuard 인증 제한 시간이 초과했습니다. 실행 파일이 변조되거나 GameGuard 파일이 손상되었습니다.");
			m_pGamePlayer->sendPacket(&gcSystemMessage);

			EventKick* pKick = new EventKick(m_pGamePlayer);
			pKick->setDeadline(100);
//			pKick->setMessage("GameGuard 인증 제한 시간이 초과했습니다.. 10초 뒤에 접속이 종료됩니다.");
			pKick->sendMessage();

			m_pGamePlayer->addEvent(pKick);
		}
		else
		{
			DWORD key = m_pGamePlayer->getCSAuth().GetAuthDword();
			GCAuthKey gcKey;
			gcKey.setKey(key);
			m_pGamePlayer->sendPacket(&gcKey);
        }
	}
*/
	// 5분에 한번
	Timeval delay;
	delay.tv_sec = 300;
	delay.tv_usec = 0;

	m_Deadline = m_Deadline + delay;
	
	__END_CATCH
}
