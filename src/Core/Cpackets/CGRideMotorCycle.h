//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRideMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_RIDE_MOTORCYCLE_H__
#define __CG_RIDE_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRideMotorCycle;
//
//////////////////////////////////////////////////////////////////////

class CGRideMotorCycle : public Packet {

public:
	
	// constructor
	CGRideMotorCycle() throw();
	
	// destructor
	~CGRideMotorCycle() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_RIDE_MOTORCYCLE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord + szCoord ; }

	// get packet name
	string getPacketName() const throw() { return "CGRideMotorCycle"; }

	// get/set ObjectID
	ObjectID_t getObjectID() const throw()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	// get/set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }
	
	// get packet's debug string
	string toString() const throw();

private :

	// ObjectID
	ObjectID_t m_ObjectID;

	// Coord X
	Coord_t m_X;

	// Coord Y
	Coord_t m_Y;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGRideMotorCycleFactory;
//
// Factory for CGRideMotorCycle
//
//////////////////////////////////////////////////////////////////////

class CGRideMotorCycleFactory : public PacketFactory {

public:
	
	// constructor
	CGRideMotorCycleFactory() throw() {}
	
	// destructor
	virtual ~CGRideMotorCycleFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRideMotorCycle(); }

	// get packet name
	string getPacketName() const throw() { return "CGRideMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_RIDE_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord + szCoord; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGRideMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRideMotorCycleHandler {

public:

	// execute packet's handler
	static void execute(CGRideMotorCycle* pCGRideMotorCycle, Player* pPlayer) throw(Error);

};

#endif
