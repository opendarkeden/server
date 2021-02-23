//////////////////////////////////////////////////////////////////////////////
// Filename    : ExtraSlotInfo.h
// Written By  : elca
// Description :
// 플레이어의 마우스에 달려있는 아이템에 대한 정보를 가지고 전송되는
// 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EXTRA_SLOT_INFO_H__
#define __EXTRA_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class ExtraSlotInfo
//////////////////////////////////////////////////////////////////////////////

class ExtraSlotInfo : public PCItemInfo 
{
public:
	ExtraSlotInfo();
	virtual ~ExtraSlotInfo();

public:
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	string toString () const throw ();
};

#endif
