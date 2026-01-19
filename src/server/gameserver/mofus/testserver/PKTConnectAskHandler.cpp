/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAskHandler.cpp
// Desc		:
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTConnectAskHandler.h"

#include "GameServerPlayer.h"
#include "Mofus.h"
#include "PKTConnectAccept.h"


// 실행 함수
void PKTConnectAskHandler::execute(GameServerPlayer* pPlayer, MPacket* pPacket) {
    cout << "RECV ConnectAsk" << endl;

    PKTConnectAccept pkt;

    pPlayer->sendPacket(&pkt);

    cout << "SEND ConnectAccept" << endl;
}
