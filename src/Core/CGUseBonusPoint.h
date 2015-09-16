//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUseBonusPoint.h 
// Written By  : crazydog
// Description : vampire가 bonus point를 사용한다.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_BONUS_POINT_H__
#define __CG_USE_BONUS_POINT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


#define INC_INT		0
#define INC_STR		1
#define INC_DEX		2


//////////////////////////////////////////////////////////////////////
//
// class CGUseBonusPoint;
//
//////////////////////////////////////////////////////////////////////

class CGUseBonusPoint : public Packet {

public:
	
	// constructor
	CGUseBonusPoint() throw();
	
	// destructor
	~CGUseBonusPoint() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_USE_BONUS_POINT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "CGUseBonusPoint"; }

	// get/set which 
	BYTE getWhich() const throw() { return m_Which;}
	void setWhich(BYTE w) throw() { m_Which = w;}

	// get packet's debug string
	string toString() const throw();

private :

	// which
	BYTE m_Which;

};


//////////////////////////////////////////////////////////////////////
//
// class CGUseBonusPointFactory;
//
// Factory for CGUseBonusPoint
//
//////////////////////////////////////////////////////////////////////

class CGUseBonusPointFactory : public PacketFactory {

public:
	
	// constructor
	CGUseBonusPointFactory() throw() {}
	
	// destructor
	virtual ~CGUseBonusPointFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGUseBonusPoint(); }

	// get packet name
	string getPacketName() const throw() { return "CGUseBonusPoint"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_USE_BONUS_POINT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGUseBonusPointHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUseBonusPointHandler {

public:

	// execute packet's handler
	static void execute(CGUseBonusPoint* pCGUseBonusPoint, Player* pPlayer) throw(Error);

};

#endif
