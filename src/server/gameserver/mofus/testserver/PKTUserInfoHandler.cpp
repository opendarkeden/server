/////////////////////////////////////////////////////////////////////////////
// Filename : PKTUserInfoHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTUserInfoHandler.h"
#include "PKTUserInfo.h"
#include "GameServerPlayer.h"
#include "PKTPowerPoint.h"


// 실행 함수
void PKTUserInfoHandler::execute( GameServerPlayer* pPlayer, MPacket* pPacket )
{
	cout << "--------------------------------------------------" << endl;
	cout << "RECV UserInfo" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV UserInfo" );
	filelog( MOFUS_PACKET_FILE, "RECV : %s", pPacket->toString().c_str() );

	PKTPowerPoint pkt;
	strcpy( pkt.sCharName, "슬11" );
	pkt.nPowerPoint = 300;
	pkt.nContinue = rand() % 2;
	pkt.nOnGameCode = 1;
	cout << "sending PowerPoint : " << endl << pkt.toString() << endl;
	pPlayer->sendPacket( &pkt );
}

