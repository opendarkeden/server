//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGuildChat.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GUILD_CHAT_H__
#define __CG_GUILD_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGuildChat;
//
//////////////////////////////////////////////////////////////////////

class CGGuildChat : public Packet {

public:
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_GUILD_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const 
	{
		return szBYTE +
			   szuint +				// text color
			   szBYTE +				// message size
			   m_Message.size();	// chatting message
	}

	// get packet name
	string getPacketName() const  { return "CGGuildChat"; }
	
	// get packet's debug string
	string toString() const ;

	BYTE getType() const  { return m_Type; }
	void setType(BYTE type )  { m_Type = type; }

	// get/set text color
	uint getColor() const  { return m_Color; }
	void setColor(uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	

private :

	BYTE m_Type;
	// text color
	uint m_Color;

	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGGuildChatFactory;
//
// Factory for CGGuildChat
//
//////////////////////////////////////////////////////////////////////

class CGGuildChatFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGGuildChat(); }

	// get packet name
	string getPacketName() const  { return "CGGuildChat"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_GUILD_CHAT; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const 
	{
		return szBYTE +
			   szuint +			// text color
			   szBYTE +			// message size
			   128;				// chatting message
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CGGuildChatHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGuildChatHandler {

public:

	// execute packet's handler
	static void execute(CGGuildChat* pPacket, Player* pPlayer) ;

};

#endif
