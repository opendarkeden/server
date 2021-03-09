//////////////////////////////////////////////////////////////////////////////
// Filename    : GearInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// 입고 있는 기어 아이템들의 정보 리스트이다.
// 각각의 기어 아이템에 대한 정보는 GearSlotInfo를 참조하면 된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GEAR_INFO_H__
#define __GEAR_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "GearSlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
// class GearInfo;
//////////////////////////////////////////////////////////////////////////////

class GearInfo 
{
public:
	GearInfo () ;
	~GearInfo () ;
	
public:
    void read (SocketInputStream & iStream) ;
    void write (SocketOutputStream & oStream) const ;

	PacketSize_t getSize () ;

	static uint getMaxSize ()  
	{
		return szBYTE + (GearSlotInfo::getMaxSize()* 13);
	}

	string toString () const ;

public:
	BYTE getListNum() const  { return m_ListNum; }
	void setListNum(BYTE ListNum)  { m_ListNum = ListNum; }

	void addListElement(GearSlotInfo* pGearSlotInfo)  { m_GearSlotInfoList.push_back(pGearSlotInfo); }

	void clearList()  { m_GearSlotInfoList.clear(); m_ListNum = 0; }

	GearSlotInfo* popFrontListElement()  
	{ 
		GearSlotInfo* TempGearSlotInfo = m_GearSlotInfoList.front(); m_GearSlotInfoList.pop_front(); return TempGearSlotInfo; 
	}

private:
	BYTE m_ListNum; // number of gear
	list<GearSlotInfo*> m_GearSlotInfoList; // actual gear info

};

#endif
