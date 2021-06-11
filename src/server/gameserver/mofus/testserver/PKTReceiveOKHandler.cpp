/////////////////////////////////////////////////////////////////////////////
// Filename : PKTReceiveOKHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTReceiveOKHandler.h"
#include "PKTPowerPoint.h"
#include "GameServerPlayer.h"


// 실행 함수
void PKTReceiveOKHandler::execute( GameServerPlayer* pPlayer, MPacket* pPacket )
{
	cout << "--------------------------------------------------" << endl;
	cout << "RECV ReceiveOK" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV ReceiveOK" );
	filelog( MOFUS_PACKET_FILE, "RECV : %s", pPacket->toString().c_str() );

	PKTPowerPoint pkt;
	strcpy( pkt.sCharName, "슬11" );
	pkt.nPowerPoint = 300;
	pkt.nContinue = rand() % 2;
	pPlayer->sendPacket( &pkt );
}

