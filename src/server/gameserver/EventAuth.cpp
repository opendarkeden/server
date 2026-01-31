//////////////////////////////////////////////////////////////////////////////
// Filename    : EventAuth.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EventAuth.h"

#include "Creature.h"
#include "EventKick.h"
#include "GCAuthKey.h"
#include "GCSystemMessage.h"
#include "GamePlayer.h"
#include "Item.h"
#include "Ousters.h"
#include "Slayer.h"
#include "Vampire.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::EventAuth(GamePlayer* pGamePlayer)

    : Event(pGamePlayer) {
    // 1분
    setDeadline(600);
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventAuth::~EventAuth()

{}

//////////////////////////////////////////////////////////////////////////////
// activate
//////////////////////////////////////////////////////////////////////////////
void EventAuth::activate()

{
    __BEGIN_TRY

    if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) {
        Assert(m_pGamePlayer != NULL);

        // if ( !m_pGamePlayer->getCSAuth().IsAuth() )
        if (true) {
            filelog("CSAuth.log", "[%s] 인증 시간 제한을 초과했습니다.", m_pGamePlayer->getID().c_str());

            GCSystemMessage gcSystemMessage;
            gcSystemMessage.setMessage("nProtect GameGuard 훰聯呵겨.獵契匡숭댄轎샀GameGuard匡숭愆뻐.");
            m_pGamePlayer->sendPacket(&gcSystemMessage);

            EventKick* pKick = new EventKick(m_pGamePlayer);
            pKick->setDeadline(100);
            //			pKick->setMessage("GameGuard 인증 제한 시간이 초과했습니다.. 10초 뒤에 접속이 종료됩니다.");
            pKick->sendMessage();

            m_pGamePlayer->addEvent(pKick);
        } else {
            // DWORD key = m_pGamePlayer->getCSAuth().GetAuthDword();
            // GCAuthKey gcKey;
            // gcKey.setKey(key);
            // m_pGamePlayer->sendPacket(&gcKey);
        }
    }

    // 5분에 한번
    Timeval delay;
    delay.tv_sec = 300;
    delay.tv_usec = 0;

    m_Deadline = m_Deadline + delay;

    __END_CATCH
}
