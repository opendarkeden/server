/////////////////////////////////////////////////////////////////////////////
// Filename : PKTResultHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTResultHandler.h"


// 실행 함수
void PKTResultHandler::execute( GameServerPlayer* pPlayer, MPacket* pPacket )
{
	cout << "--------------------------------------------------" << endl;
	cout << "RECV Result" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV Result" );
	filelog( MOFUS_PACKET_FILE, "RECV : %s", pPacket->toString().c_str() );

	throw ConnectException("process complete. close connection");
}

