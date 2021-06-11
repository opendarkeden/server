//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAcceptUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ACCEPT_UNION_H__
#define __CG_ACCEPT_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGAcceptUnion;
//
//////////////////////////////////////////////////////////////////////

class CGAcceptUnion : public Packet
{
public:
	CGAcceptUnion() {};
    ~CGAcceptUnion() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_ACCEPT_UNION; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szGuildID; }

	// get packet name
	string getPacketName() const  { return "CGAcceptUnion"; }

	// get packet's debug string
	string toString() const ;

	// get/set GuildID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t GuildID )  { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGAcceptUnionFactory;
//
// Factory for CGAcceptUnion
//
//////////////////////////////////////////////////////////////////////

class CGAcceptUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGAcceptUnionFactory()  {}
	
	// destructor
	virtual ~CGAcceptUnionFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGAcceptUnion(); }

	// get packet name
	string getPacketName() const  { return "CGAcceptUnion"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_ACCEPT_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGAcceptUnionHandler;
//
//////////////////////////////////////////////////////////////////////

class CGAcceptUnionHandler {

public:

	// execute packet's handler
	static void execute(CGAcceptUnion* pCGAcceptUnion, Player* pPlayer) ;

};

#endif
