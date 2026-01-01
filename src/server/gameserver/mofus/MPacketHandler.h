/////////////////////////////////////////////////////////////////////////////
// Filename : MPacketHandler.h
// Desc		: ���۽� �� ��Ŷ �ڵ鷯
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

