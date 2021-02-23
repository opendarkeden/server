//////////////////////////////////////////////////////////////////////////////
// Filename    : RideMotorcycleSlotInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __RIDE_MOTORCYCLE_SLOT_INFO_H__
#define __RIDE_MOTORCYCLE_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// RideMotorcycle 정보를 담고 있는 객체.
/////////////////////////////////////////////////////////////////////////////

class RideMotorcycleSlotInfo : public PCItemInfo 
{
public:
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	uint getSize () throw ()
	{ 
		return PCItemInfo::getSize() + szCoordInven*2;
	}

	static uint getMaxSize () throw ()
	{ 
		return PCItemInfo::getMaxSize() + szCoordInven*2;
	}

	string toString () const throw ();

public:
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }
	CoordInven_t getInvenX() const throw() { return m_InvenX; }

	void setInvenY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }
	CoordInven_t getInvenY() const throw() { return m_InvenY; }

private:
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};

#endif
