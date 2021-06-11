/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAcceptHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ACCEPT_HANDLER_H__
#define __PKT_CONNECT_ACCEPT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTConnectAcceptHandler
class PKTConnectAcceptHandler : public MPacketHandler
{
public:
	// 해당 패킷의 ID
	MPacketID_t getID() const;

	// 실행 함수
	void execute( MPlayer* pPlayer, MPacket* pPacket );
};

#endif

