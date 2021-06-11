//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLChangeServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_CHANGE_SERVER_H__
#define __CL_CHANGE_SERVER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLChangeServer;
//
//////////////////////////////////////////////////////////////////////

class CLChangeServer : public Packet {

public:
	CLChangeServer() {};
    virtual ~CLChangeServer() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CL_CHANGE_SERVER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szServerGroupID; }

	// get packet name
	string getPacketName() const  { return "CLChangeServer"; }

	// get / set ServerGroupID
	ServerGroupID_t getServerGroupID() const  { return m_ServerGroupID; }
	void setServerGroupID(ServerGroupID_t ServerGroupID)  { m_ServerGroupID = ServerGroupID; }
	
	// get packet's debug string
	string toString() const  { return "CLChangeServer"; }

private :

	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class CLChangeServerFactory;
//
// Factory for CLChangeServer
//
//////////////////////////////////////////////////////////////////////

class CLChangeServerFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLChangeServer(); }

	// get packet name
	string getPacketName() const  { return "CLChangeServer"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_CHANGE_SERVER; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szServerGroupID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLChangeServerHandler;
//
//////////////////////////////////////////////////////////////////////

class CLChangeServerHandler {

public:

	// execute packet's handler
	static void execute(CLChangeServer* pPacket, Player* player) ;

};

#endif
