//////////////////////////////////////////////////////////////////////////////
// Filename    : InventorySlotInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_SLOT_INFO_H__
#define __INVENTORY_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// Inventory 정보를 담고 있는 객체.
//////////////////////////////////////////////////////////////////////////////

class InventorySlotInfo : public PCItemInfo 
{
public:
	void read (SocketInputStream & iStream) ;
	void write (SocketOutputStream & oStream) const ;

	uint getSize () 
	{ 
		return PCItemInfo::getSize() + szCoordInven* 2;
	}

	static uint getMaxSize () 
	{ 
		return PCItemInfo::getMaxSize() + szCoordInven* 2;
	}

	string toString () const ;

public:
	void setInvenX(CoordInven_t InvenX)  { m_InvenX = InvenX; }
	CoordInven_t getInvenX() const  { return m_InvenX; }

	void setInvenY(CoordInven_t InvenY)  { m_InvenY = InvenY; }
	CoordInven_t getInvenY() const  { return m_InvenY; }

private:
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};

#endif
