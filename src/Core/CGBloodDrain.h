//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGBloodDrain 
// Written By  : crazydog
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_BLOOD_DRAIN_H__
#define __CG_BLOOD_DRAIN_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#ifdef __LINUX__
//#include "GCGlobalHandler.h"
#endif // __LINUX__


//////////////////////////////////////////////////////////////////////
//
// class CGBloodDrain;
//
//////////////////////////////////////////////////////////////////////

class CGBloodDrain : public Packet {

public:
	
	// constructor
	CGBloodDrain() throw();
	
	// destructor
	~CGBloodDrain() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_BLOOD_DRAIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

	// get packet name
	string getPacketName() const throw() { return "CGBloodDrain"; }
	
	// get packet's debug string
	string toString() const throw();
/*	
	// get/set X Coordicate
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }

	// get/set Y Coordicate
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	// get/set Direction
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }
*/	
	// get/set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	
private :
	
	ObjectID_t m_ObjectID;  // ObjectID
/*	
	Coord_t m_X;			// X 좌표
	Coord_t m_Y;			// Y 좌표
	Dir_t m_Dir;			// 방향
*/
};


//////////////////////////////////////////////////////////////////////
//
// class CGBloodDrainFactory;
//
// Factory for CGBloodDrain
//
//////////////////////////////////////////////////////////////////////

class CGBloodDrainFactory : public PacketFactory {

public:
	
	// constructor
	CGBloodDrainFactory() throw() {}
	
	// destructor
	virtual ~CGBloodDrainFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGBloodDrain(); }

	// get packet name
	string getPacketName() const throw() { return "CGBloodDrain"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_BLOOD_DRAIN; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGBloodDrainHandler;
//
//////////////////////////////////////////////////////////////////////

class CGBloodDrainHandler {
	
public:

	// execute packet's handler
	static void execute(CGBloodDrain* pCGBloodDrain, Player* player) throw(Error);
};

#endif
