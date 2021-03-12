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
	CGDissectionCorpse() ;
	
	// destructor
	~CGDissectionCorpse() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_DISSECTION_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord + szCoord + szBYTE; }

	// get packet name
	string getPacketName() const  { return "CGDissectionCorpse"; }

	// get/set Corpse's X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	// get/set Corpse's Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }

	// get/set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	BYTE isPet() const { return m_IsPet; }
	void setPet(BYTE isPet) { m_IsPet = isPet; }

	// get packet's debug string
	string toString() const ;

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
	CGDissectionCorpseFactory()  {}
	
	// destructor
	virtual ~CGDissectionCorpseFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGDissectionCorpse(); }

	// get packet name
	string getPacketName() const  { return "CGDissectionCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_DISSECTION_CORPSE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord + szCoord + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGDissectionCorpseHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDissectionCorpseHandler {

public:

	// execute packet's handler
	static void execute(CGDissectionCorpse* pCGDissectionCorpse, Player* pPlayer) ;
};

#endif
