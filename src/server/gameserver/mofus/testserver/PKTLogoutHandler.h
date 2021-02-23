/////////////////////////////////////////////////////////////////////////////
// Filename : PKTLogoutHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_LOGOUT_HANDLER_H__
#define __PKT_LOGOUT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTLogoutHandler
class PKTLogoutHandler : public MPacketHandler
{
public:
	// 해당 패킷의 ID
	MPacketID_t getID() const;

	// 실행 함수
	void execute( GameServerPlayer* pPlayer, MPacket* pPacket );
};

#endif

