/////////////////////////////////////////////////////////////////////////////
// Filename : PKTErrorHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_ERROR_HANDLER_H__
#define __PKT_ERROR_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTErrorHandler
class PKTErrorHandler : public MPacketHandler
{
public:
	// 해당 패킷의 ID
	MPacketID_t getID() const;

	// 실행 함수
	void execute( MPlayer* pPlayer, MPacket* pPacket );
};

#endif

