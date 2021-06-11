//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPickupMoney.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PICKUP_MONEY_H__
#define __CG_PICKUP_MONEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoney;
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoney : public Packet {
public:

	// constructor
	CGPickupMoney() ;

	// destructor
	~CGPickupMoney() ;

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_PICKUP_MONEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGPickupMoneyPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord + szCoord; }

	// get packet name
	string getPacketName() const  { return "CGPickupMoney"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get/set X Coordicate
	Coord_t getZoneX() const  { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX)  { m_ZoneX = ZoneX; }

	// get/set Y Coordicate
	Coord_t getZoneY() const  { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY)  { m_ZoneY = ZoneY; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// 아이템이 있는 Zone의  X, Y 좌표.
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoneyFactory;
//
// Factory for CGPickupMoney
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoneyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGPickupMoney(); }

	// get packet name
	string getPacketName() const  { return "CGPickupMoney"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_PICKUP_MONEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGPickupMoneyPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord + szCoord; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoneyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoneyHandler {
	
public:

	// execute packet's handler
	static void execute(CGPickupMoney* pPacket, Player* player) ;
};

#endif
