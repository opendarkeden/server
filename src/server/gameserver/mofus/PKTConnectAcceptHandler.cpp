/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAcceptHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTConnectAcceptHandler.h"
#include "MPlayer.h"
#include "MJob.h"


// 실행 함수
void PKTConnectAcceptHandler::execute( MPlayer* pPlayer, MPacket* pPacket )
{
	cout << "--------------------------------------------------" << endl;
	cout << "RECV [" << pPlayer->getJob()->getName() << "] ConnectAccept" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV [%s] ConnectAccept", pPlayer->getJob()->getName().c_str() );
	filelog( MOFUS_PACKET_FILE, "RECV : [%s] %s", pPlayer->getJob()->getName().c_str(), pPacket->toString().c_str() );

	// 유저 인포를 요청. 파워포인트 가져오기
	pPlayer->sendUserInfo();
}

