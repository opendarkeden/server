//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKickMessage.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_KICK_MESSAGE_H__
#define __GC_KICK_MESSAGE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


enum KickMessageType
{
	KICK_MESSAGE_PAY_TIMEOUT = 0,
	KICK_MESSAGE_EXPIRE_FREEPLAY,
#ifdef __THAILAND_SERVER__
	KICK_MESSAGE_CHILDGUARD,
#endif
	KICK_MESSAGE_MAX
};

//////////////////////////////////////////////////////////////////////
//
// class GCKickMessage;
//
// 게임 서버가 특정 플레이어의 KickMessage 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 KickMessage 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCKickMessage : public Packet {

public :
	GCKickMessage() 
	: m_Type(KICK_MESSAGE_PAY_TIMEOUT)
	{
	}
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_KICK_MESSAGE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + szuint; }

	// get packet name
	string getPacketName() const throw() { return "GCKickMessage"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set Kick Message Type
	BYTE getType() const throw() { return m_Type; }
	void setType( BYTE type ) throw() { m_Type = (KickMessageType)type; }

	// get/set seconds
	uint getSeconds() const throw() { return m_Seconds; }
	void setSeconds( uint seconds ) throw() { m_Seconds = seconds; }

private :
	
	KickMessageType m_Type;

	// seconds
	uint m_Seconds;
};


//////////////////////////////////////////////////////////////////////
//
// class GCKickMessageFactory;
//
// Factory for GCKickMessage
//
//////////////////////////////////////////////////////////////////////

class GCKickMessageFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCKickMessage(); }

	// get packet name
	string getPacketName() const throw() { return "GCKickMessage"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_KICK_MESSAGE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCKickMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szuint; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCKickMessageHandler;
//
//////////////////////////////////////////////////////////////////////

class GCKickMessageHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCKickMessage* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
