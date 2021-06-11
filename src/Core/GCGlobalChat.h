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
	GCGlobalChat() {};
    ~GCGlobalChat() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_GLOBAL_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szuint + szBYTE + m_Message.size() + szBYTE; }

	// get packet name
	string getPacketName() const  { return "GCGlobalChat"; }
	
	// get packet's debug string
	string toString() const ;

	//get/set text color
	uint getColor() const  { return m_Color; }
	void setColor(uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }

	// get/set chatting message
	Race_t getRace() const  { return m_Race; }
	void setRace(Race_t race)  { m_Race = race; }
	

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
	Packet* createPacket()  { return new GCGlobalChat(); }

	// get packet name
	string getPacketName() const  { return "GCGlobalChat"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_GLOBAL_CHAT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCGlobalChatPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szuint + szBYTE + 128 + szBYTE ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGlobalChatHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGlobalChatHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCGlobalChat* pPacket, Player* pPlayer) ;

};

#endif
