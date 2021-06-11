
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestUnionInfo.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUER_UNION_INFO_H__
#define __CG_REQUER_UNION_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionInfo;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionInfo : public Packet
{
public:
	CGRequestUnionInfo() {};
    virtual ~CGRequestUnionInfo() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_REQUEST_UNION_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return 0; }

	// get packet name
	string getPacketName() const  { return "CGRequestUnionInfo"; }

	// get packet's debug string
	string toString() const ;


};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionInfoFactory;
//
// Factory for CGRequestUnionInfo
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionInfoFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestUnionInfoFactory()  {}
	
	// destructor
	virtual ~CGRequestUnionInfoFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGRequestUnionInfo(); }

	// get packet name
	string getPacketName() const  { return "CGRequestUnionInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_REQUEST_UNION_INFO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return 0; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionInfoHandler {

public:
    CGRequestUnionInfoHandler() {};
    ~CGRequestUnionInfoHandler() {};
	// execute packet's handler
	static void execute(CGRequestUnionInfo* pCGRequestUnionInfo, Player* pPlayer) ;

};

#endif
