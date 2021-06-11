/////////////////////////////////////////////////////////////////////////////
// Filename : PKTLogoutHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTLogoutHandler.h"


// 실행 함수
void PKTLogoutHandler::execute( GameServerPlayer* pPlayer, MPacket* pPacket )
{
	cout << "--------------------------------------------------" << endl;
	cout << "RECV Logout" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV Logout" );
	filelog( MOFUS_PACKET_FILE, "RECV : %s", pPacket->toString().c_str() );
}

