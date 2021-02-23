//////////////////////////////////////////////////////////////////////////////
// Filename    : RideMotorcycleInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 타고 있는 모터사이클에 대한 정보를 가지고 있는 패킷이다.
// 모터 사이클 자체에 관한 정보 외에도, 모터 사이클 내부에 있는
// 인벤토리에 대한 정보도 같이 가지고 있다. 인벤토리 정보에 대한 것은
// RideMotorcycleSlotInfo와 InventorySlotInfo를 참조하라.
//////////////////////////////////////////////////////////////////////////////

#ifndef __RIDE_MOTORCYCLE_INFO_H__
#define __RIDE_MOTORCYCLE_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "RideMotorcycleSlotInfo.h"
#include "Packet.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class RideMotorcycleInfo;
//////////////////////////////////////////////////////////////////////////////

class RideMotorcycleInfo 
{
public:
	RideMotorcycleInfo () throw ();
	~RideMotorcycleInfo () throw ();
	
public:
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	PacketSize_t getSize() throw ();

	static uint getMaxSize() throw() 
	{
		return szObjectID +  // motorcycle object id
			szItemType +  // motorcycle type
			szBYTE + 255 + // motorcycle option type
			szBYTE + // number of item in motorcycle inventory
			RideMotorcycleSlotInfo::getMaxSize()* 60;
	}

	string toString () const throw ();

public:
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }

	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }
	ItemType_t getItemType() const throw() { return m_ItemType; }

	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }
	int getOptionTypeSize() const throw()	{ return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
        OptionType_t optionType = m_OptionType.front();
        m_OptionType.pop_front();
	    return optionType;
	}

public:
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	void addListElement(RideMotorcycleSlotInfo* pRideMotorcycleSlotInfo) throw() { m_RideMotorcycleSlotInfoList.push_back(pRideMotorcycleSlotInfo); }

	void clearList() throw() { m_RideMotorcycleSlotInfoList.clear(); m_ListNum = 0; }

	RideMotorcycleSlotInfo* popFrontListElement() throw() 
	{ 
		RideMotorcycleSlotInfo* TempRideMotorcycleSlotInfo = m_RideMotorcycleSlotInfoList.front(); m_RideMotorcycleSlotInfoList.pop_front(); return TempRideMotorcycleSlotInfo; 
	}

private:
	ObjectID_t   		m_ObjectID;   // motorcycle object id
	ItemType_t   		m_ItemType;   // motorcycle item type
	list<OptionType_t> 	m_OptionType; // motorcycle option type
	BYTE         		m_ListNum;    // number of item in motorcycle inventory

	// actual item info in motorcycle inventory
	list<RideMotorcycleSlotInfo*> m_RideMotorcycleSlotInfoList;

};

#endif
