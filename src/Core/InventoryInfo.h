//////////////////////////////////////////////////////////////////////////////
// Filename    : InventoryInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// 인벤토리 안에 있는 아이템들의 정보 리스트이다.
// 인벤토리 안의 각각의 아이템들에 대한 정보는 InventorySlotInfo를 참조.
//////////////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_INFO_H__
#define __INVENTORY_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "InventorySlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
// class InventoryInfo;
//////////////////////////////////////////////////////////////////////////////

class InventoryInfo 
{
public:
	InventoryInfo () throw();
	~InventoryInfo () throw();
	
public:
    void read (SocketInputStream & iStream) throw(ProtocolException, Error);
    void write (SocketOutputStream & oStream) const throw(ProtocolException, Error);

	PacketSize_t getSize () throw();

	static uint getMaxSize() throw() 
	{
		//return szBYTE + szBYTE + szBYTE + (InventorySlotInfo::getMaxSize() * 60);
		return szBYTE + (InventorySlotInfo::getMaxSize() * 60);
	}

	string toString () const throw();

public:
	CoordInven_t getWidth() const { return m_Width; }
	void setWidth(CoordInven_t Width ) { m_Width = Width; }

	CoordInven_t getHeight() const { return m_Height; }
	void setHeight(CoordInven_t Height ) { m_Height = Height; }

	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	void addListElement(InventorySlotInfo* pInventorySlotInfo) throw() { m_InventorySlotInfoList.push_back(pInventorySlotInfo); }

	void clearList() throw() { m_InventorySlotInfoList.clear(); m_ListNum = 0; }

	InventorySlotInfo* popFrontListElement() throw() 
	{ 
		InventorySlotInfo* TempInventorySlotInfo = m_InventorySlotInfoList.front(); m_InventorySlotInfoList.pop_front(); return TempInventorySlotInfo; 
	}

private:
	CoordInven_t	m_Width, m_Height;

	BYTE m_ListNum; // number of item in inventory
	list<InventorySlotInfo*> m_InventorySlotInfoList; // actual item info
};

#endif
