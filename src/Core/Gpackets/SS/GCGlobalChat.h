//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGlobalChat.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GLOBAL_CHAT_H__
#define __GC_GLOBAL_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChat;
//
// 게임 서버가 특정 플레이어의 GlobalChat 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 GlobalChat 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChat : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_GLOBAL_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szuint + szBYTE + m_Message.size() + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "GCGlobalChat"; }
	
	// get packet's debug string
	string toString() const throw();

	//get/set text color
	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }

	// get/set chatting message
	Race_t getRace() const throw() { return m_Race; }
	void setRace(Race_t race) throw() { m_Race = race; }
	

private :
	
	// chatting message
	string m_Message;

	// text color
	uint m_Color;

	// race
	Race_t m_Race;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChatFactory;
//
// Factory for GCGlobalChat
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChatFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCGlobalChat(); }

	// get packet name
	string getPacketName() const throw() { return "GCGlobalChat"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GLOBAL_CHAT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCGlobalChatPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szuint + szBYTE + 128 + szBYTE ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChatHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChatHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCGlobalChat* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
