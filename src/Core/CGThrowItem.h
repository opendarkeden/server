//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGThrowItem.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_THROW_ITEM_H__
#define __CG_THROW_ITEM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGThrowItem;
//
//////////////////////////////////////////////////////////////////////

class CGThrowItem : public Packet {

public:
	
	// constructor
	CGThrowItem() ;
	
	// destructor
	~CGThrowItem() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_THROW_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName() const  { return "CGThrowItem"; }

	// get/set ItemObjectID
	ObjectID_t getObjectID() const   { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID() const   { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID)  { m_TargetObjectID = TargetObjectID; }

	// get/set InvenX
	CoordInven_t getX() const  { return m_InvenX; }
	void setX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	// get/set InvenY
	CoordInven_t getY() const  { return m_InvenY; }
	void setY(CoordInven_t InvenY)  { m_InvenY = InvenY; }

	// get packet's debug string
	string toString() const ;

private :

	// Item Object ID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

	// InvenX / Y
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGThrowItemFactory;
//
// Factory for CGThrowItem
//
//////////////////////////////////////////////////////////////////////

class CGThrowItemFactory : public PacketFactory {

public:
	
	// constructor
	CGThrowItemFactory()  {}
	
	// destructor
	virtual ~CGThrowItemFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGThrowItem(); }

	// get packet name
	string getPacketName() const  { return "CGThrowItem"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_THROW_ITEM; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGThrowItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGThrowItemHandler {

public:

	// execute packet's handler
	static void execute(CGThrowItem* pCGThrowItem, Player* pPlayer) ;

};

#endif
