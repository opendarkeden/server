//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGlobalChat.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GLOBAL_CHAT_H__
#define __CG_GLOBAL_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChat;
//
// 클라이언트가 서버에게 보내는 GlobalChat 패킷이다.
// 내부에 GlobalChat String 만을 데이타 필드로 가진다.
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChat : public Packet {

public:
	CGGlobalChat() {};
    ~CGGlobalChat() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_GLOBAL_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szuint + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "CGGlobalChat"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set text color
	uint getColor() const  { return m_Color; }
	void setColor(uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	

private :
	
	// text color
	uint m_Color;

	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChatFactory;
//
// Factory for CGGlobalChat
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChatFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGGlobalChat(); }

	// get packet name
	string getPacketName() const  { return "CGGlobalChat"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_GLOBAL_CHAT; }

	// get packet's max body size
	// message 의 최대 크기에 대한 설정이 필요하다.
	PacketSize_t getPacketMaxSize() const  { return szuint + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChatHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChatHandler {

public:

	// execute packet's handler
	static void execute(CGGlobalChat* pPacket, Player* pPlayer) ;

};

#endif
