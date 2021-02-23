//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSystemMessage.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SYSTEM_MESSAGE_H__
#define __GC_SYSTEM_MESSAGE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


enum SystemMessageType
{
	SYSTEM_MESSAGE_NORMAL = 0,
	SYSTEM_MESSAGE_OPERATOR,	// 운영자 말씀
	SYSTEM_MESSAGE_MASTER_LAIR,	// 마스터 레어 관련
	SYSTEM_MESSAGE_COMBAT,		// 전쟁 관련
	SYSTEM_MESSAGE_INFO, 		// 특정한 정보 관련
	SYSTEM_MESSAGE_HOLY_LAND, 	// 아담의 성지 관련
	SYSTEM_MESSAGE_RANGER_SAY, 	// Ranger Say, DragonEye 를 가진 Ranger의 메시지
	SYSTEM_MESSAGE_PLAYER,      // 鯤소홍혐랙箇斤口
	SYSTEM_MESSAGE_MAX
};

//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessage;
//
// 게임 서버가 특정 플레이어의 SystemMessage 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 SystemMessage 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessage : public Packet {

public :
	GCSystemMessage() 
	: m_Color(0x006040E8), m_Type(SYSTEM_MESSAGE_NORMAL)
	{
	}
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SYSTEM_MESSAGE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Message.size() + szuint + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "GCSystemMessage"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set chatting message
	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }

	// get/set text color
	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	SystemMessageType getType() const throw() { return m_Type; }
	void setType( SystemMessageType Type ) throw() { m_Type = Type; }

	// get/set race
	Race_t getRace() const { return m_Race; }
	void setRace( Race_t race ) { m_Race = race; }

private :
	
	// chatting message
	string m_Message;

	// text color
	uint m_Color;
	
	SystemMessageType m_Type;

	// race
	Race_t m_Race;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessageFactory;
//
// Factory for GCSystemMessage
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessageFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSystemMessage(); }

	// get packet name
	string getPacketName() const throw() { return "GCSystemMessage"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SYSTEM_MESSAGE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 256 + szuint + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessageHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessageHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSystemMessage* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
