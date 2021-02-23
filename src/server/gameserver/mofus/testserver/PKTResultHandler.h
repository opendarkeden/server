/////////////////////////////////////////////////////////////////////////////
// Filename : PKTResultHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_RESULT_HANDLER_H__
#define __PKT_RESULT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTResultHandler
class PKTResultHandler : public MPacketHandler
{
public:
	// 해당 패킷의 ID
	MPacketID_t getID() const;

	// 실행 함수
	void execute( GameServerPlayer* pPlayer, MPacket* pPacket );
};

#endif

