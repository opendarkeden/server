/////////////////////////////////////////////////////////////////////////////
// Filename : PKTPowerPointHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_POWER_POINT_HANDLER_H__
#define __PKT_POWER_POINT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTPowerPointHandler
class PKTPowerPointHandler : public MPacketHandler
{
public:
	// 해당 패킷의 ID
	MPacketID_t getID() const;

	// 실행 함수
	void execute( MPlayer* pPlayer, MPacket* pPacket );
};

#endif

