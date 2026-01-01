//////////////////////////////////////////////////////////////////////////////
// Filename    : InventoryInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// �κ��丮 �ȿ� �ִ� �����۵��� ���� ����Ʈ�̴�.
// �κ��丮 ���� ������ �����۵鿡 ���� ������ InventorySlotInfo�� ����.
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
	InventoryInfo () ;
	~InventoryInfo () noexcept ;
	
public:
    void read (SocketInputStream & iStream) ;
    void write (SocketOutputStream & oStream) const ;

	PacketSize_t getSize () ;

	static uint getMaxSize()  
	{
		return szBYTE + (InventorySlotInfo::getMaxSize()* 60);
	}

	string toString () const ;

public:
	BYTE getListNum() const  { return m_ListNum; }
	void setListNum(BYTE ListNum)  { m_ListNum = ListNum; }

	void addListElement(InventorySlotInfo* pInventorySlotInfo)  { m_InventorySlotInfoList.push_back(pInventorySlotInfo); }

	void clearList()  { m_InventorySlotInfoList.clear(); m_ListNum = 0; }

	InventorySlotInfo* popFrontListElement()  
	{ 
		InventorySlotInfo* TempInventorySlotInfo = m_InventorySlotInfoList.front(); m_InventorySlotInfoList.pop_front(); return TempInventorySlotInfo; 
	}

private:
	BYTE m_ListNum; // number of item in inventory
	list<InventorySlotInfo*> m_InventorySlotInfoList; // actual item info

};

#endif
