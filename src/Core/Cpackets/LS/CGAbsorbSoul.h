//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAbsorbSoul 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ABSORB_SOUL_H__
#define __CG_ABSORB_SOUL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoul;
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoul : public Packet {

public:
	
	// constructor
	CGAbsorbSoul() throw();
	
	// destructor
	~CGAbsorbSoul() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_ABSORB_SOUL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szZoneCoord + szZoneCoord + szObjectID + szCoordInven + szCoordInven + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName() const throw() { return "CGAbsorbSoul"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	
	ZoneCoord_t getTargetZoneX() const throw() { return m_TargetZoneX; }
	void setTargetZoneX( ZoneCoord_t x ) throw() { m_TargetZoneX = x; }

	ZoneCoord_t getTargetZoneY() const throw() { return m_TargetZoneY; }
	void setTargetZoneY( ZoneCoord_t y ) throw() { m_TargetZoneY = y; }

	ObjectID_t getInvenObjectID() const throw() { return m_InvenObjectID; }
	void setInvenObjectID(ObjectID_t invenObjectID) throw() { m_InvenObjectID = invenObjectID; }

	Coord_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX( CoordInven_t x ) throw() { m_InvenX = x; }

	Coord_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY( CoordInven_t y ) throw() { m_InvenY = y; }

	Coord_t getTargetInvenX() const throw() { return m_TargetInvenX; }
	void setTargetInvenX( CoordInven_t x ) throw() { m_TargetInvenX = x; }

	Coord_t getTargetInvenY() const throw() { return m_TargetInvenY; }
	void setTargetInvenY( CoordInven_t y ) throw() { m_TargetInvenY = y; }

private :
	
	ObjectID_t m_ObjectID;  // ObjectID

	ZoneCoord_t	m_TargetZoneX;
	ZoneCoord_t	m_TargetZoneY;
	
	ObjectID_t m_InvenObjectID; // 라바의 ObjectID
	CoordInven_t m_InvenX;			// X 좌표
	CoordInven_t m_InvenY;			// Y 좌표
	CoordInven_t m_TargetInvenX;	// Target X 좌표
	CoordInven_t m_TargetInvenY;	// Target Y 좌표
};


//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoulFactory;
//
// Factory for CGAbsorbSoul
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoulFactory : public PacketFactory {

public:
	
	// constructor
	CGAbsorbSoulFactory() throw() {}
	
	// destructor
	virtual ~CGAbsorbSoulFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGAbsorbSoul(); }

	// get packet name
	string getPacketName() const throw() { return "CGAbsorbSoul"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ABSORB_SOUL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szZoneCoord + szZoneCoord + szObjectID + szCoordInven + szCoordInven + szCoordInven + szCoordInven; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGAbsorbSoulHandler;
//
//////////////////////////////////////////////////////////////////////

class CGAbsorbSoulHandler {
	
public:

	// execute packet's handler
	static void execute(CGAbsorbSoul* pCGAbsorbSoul, Player* player) throw(Error);
};

#endif
