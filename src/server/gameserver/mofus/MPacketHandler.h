/////////////////////////////////////////////////////////////////////////////
// Filename : MPacketHandler.h
// Desc		: 占쏙옙占쌜쏙옙 占쏙옙 占쏙옙킷 占쌘들러
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_HANDLER_H__
#define __MPACKET_HANDLER_H__

// include files
#include "MPacket.h"

// forward declaration
class MPlayer;

// class MPacketHandler
class MPacketHandler
{
public:
	virtual ~MPacketHandler() = default;

	virtual MPacketID_t getID() const = 0;

	virtual void execute( MPlayer* pPlayer, MPacket* pPacket ) = 0;
};

#endif

