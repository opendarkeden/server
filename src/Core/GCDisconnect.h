//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDisconnect.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DISCONNECT_H__
#define __GC_DISCONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCDisconnect;
//
//////////////////////////////////////////////////////////////////////

class GCDisconnect : public Packet {

public :
	GCDisconnect() {};
    ~GCDisconnect() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_DISCONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "GCDisconnect"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }

private :
	
	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCDisconnectFactory;
//
// Factory for GCDisconnect
//
//////////////////////////////////////////////////////////////////////

class GCDisconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCDisconnect(); }

	// get packet name
	string getPacketName() const  { return "GCDisconnect"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_DISCONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCDisconnectPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDisconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDisconnectHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCDisconnect* pPacket, Player* pPlayer) ;

};

#endif
