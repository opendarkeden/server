//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDissectionCorpse.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DISSECTION_CORPSE_H__
#define __CG_DISSECTION_CORPSE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGDissectionCorpse;
//
//////////////////////////////////////////////////////////////////////

class CGDissectionCorpse : public Packet {

public:
	
	// constructor
	CGDissectionCorpse() throw();
	
	// destructor
	~CGDissectionCorpse() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_DISSECTION_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord + szCoord + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "CGDissectionCorpse"; }

	// get/set Corpse's X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	// get/set Corpse's Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }

	// get/set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	BYTE isPet() const { return m_IsPet; }
	void setPet(BYTE isPet) { m_IsPet = isPet; }

	// get packet's debug string
	string toString() const throw();

private :

	ObjectID_t m_ObjectID;

	Coord_t m_X;
	Coord_t m_Y;

	BYTE	m_IsPet;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGDissectionCorpseFactory;
//
// Factory for CGDissectionCorpse
//
//////////////////////////////////////////////////////////////////////

class CGDissectionCorpseFactory : public PacketFactory {

public:
	
	// constructor
	CGDissectionCorpseFactory() throw() {}
	
	// destructor
	virtual ~CGDissectionCorpseFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGDissectionCorpse(); }

	// get packet name
	string getPacketName() const throw() { return "CGDissectionCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_DISSECTION_CORPSE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord + szCoord + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGDissectionCorpseHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDissectionCorpseHandler {

public:

	// execute packet's handler
	static void execute(CGDissectionCorpse* pCGDissectionCorpse, Player* pPlayer) throw(Error);
};

#endif
