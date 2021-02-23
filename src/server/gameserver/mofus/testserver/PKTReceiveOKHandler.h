/////////////////////////////////////////////////////////////////////////////
// Filename : PKTReceiveOKHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_RECEIVE_OK_HANDLER_H__
#define __PKT_RECEIVE_OK_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTReceiveOKHandler
class PKTReceiveOKHandler : public MPacketHandler
{
public:
	// 해당 패킷의 ID
	MPacketID_t getID() const;

	// 실행 함수
	void execute( GameServerPlayer* pPlayer, MPacket* pPacket );
};

#endif

