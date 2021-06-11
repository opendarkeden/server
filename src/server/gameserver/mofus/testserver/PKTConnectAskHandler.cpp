/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAskHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTConnectAskHandler.h"
#include "PKTConnectAccept.h"
#include "GameServerPlayer.h"


// 실행 함수
void PKTConnectAskHandler::execute( GameServerPlayer* pPlayer, MPacket* pPacket )
{
	cout << "RECV ConnectAsk" << endl;

	PKTConnectAccept pkt;

	pPlayer->sendPacket( &pkt );

	cout << "SEND ConnectAccept" << endl;
}

