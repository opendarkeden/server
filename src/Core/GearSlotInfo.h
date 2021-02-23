//////////////////////////////////////////////////////////////////////////////
// Filename    : GearSlotInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GEAR_SLOT_INFO_H__
#define __GEAR_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// Inventory 정보를 담고 있는 객체.
//////////////////////////////////////////////////////////////////////////////

class GearSlotInfo : public PCItemInfo 
{
public:
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	uint getSize () throw ()
	{ 
		return PCItemInfo::getSize() + szSlotID;
	}

	static uint getMaxSize () throw ()
	{ 
		return PCItemInfo::getMaxSize() + szSlotID;
	}

	string toString () const throw ();

public:
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }
	SlotID_t getSlotID() const throw() { return m_SlotID; }

private:
	SlotID_t m_SlotID;
};

#endif
