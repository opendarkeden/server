//--------------------------------------------------------------------------------
// 
// Filename    : ItemNameInfo.h 
// Written By  : 
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __ITEM_NAME_H__
#define __ITEM_NAME_H__

// include files
#include "Types.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "Exception.h"

//--------------------------------------------------------------------------------
//
// class ItemNameInfo;
//
//--------------------------------------------------------------------------------

class ItemNameInfo {

public :
	ItemNameInfo() {}
	ItemNameInfo(ObjectID_t objectID, string name)
	{
		m_ObjectID = objectID;
		m_Name = name;
	}
	virtual ~ItemNameInfo() {}
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    virtual void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    virtual void write(SocketOutputStream & oStream) const ;

	virtual PacketSize_t getSize() const ;

	static PacketSize_t getMaxSize() 
	{
		return (szObjectID + szBYTE + (szBYTE * 20));
	}

	// get packet's debug string
	string toString() const ;

public:
	void setObjectID( ObjectID_t objectID )  { m_ObjectID = objectID; }
	ObjectID_t getObjectID() const  { return m_ObjectID; }

	void setName( string name )  { m_Name = name; }
	string getName() const  { return m_Name; }

protected :
	ObjectID_t		m_ObjectID;
	string			m_Name;
};

#endif
