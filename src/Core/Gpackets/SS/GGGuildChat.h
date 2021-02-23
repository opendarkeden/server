//----------------------------------------------------------------------
// 
// Filename    : GGGuildChat.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GG_GUILD_CHAT_H__
#define __GG_GUILD_CHAT_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GGGuildChat;
//
//----------------------------------------------------------------------

class GGGuildChat : public DatagramPacket {

public :
	
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GG_GUILD_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE +
			   szGuildID +						// GuildID
			   szBYTE + m_Sender.size() +		// Sender
			   szuint +							// Color
			   szBYTE + m_Message.size();		// Message
	}

	// get packet name
	string getPacketName() const throw() { return "GGGuildChat"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	BYTE getType() const throw() { return m_Type; }
	void setType( BYTE type ) throw() { m_Type = type; }

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set Sender
	const string& getSender() const throw() { return m_Sender; }
	void setSender( const string& sender ) throw() { m_Sender = sender; }

	// get/set text color
	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set message
	const string& getMessage() const throw() { return m_Message; }
	void setMessage( const string& message ) throw() { m_Message = message; }

private :

	BYTE m_Type;
	// Guild ID
	GuildID_t m_GuildID;

	// Sender
	string m_Sender;

	// text color
	uint m_Color;

	// message
	string m_Message;

};


//////////////////////////////////////////////////////////////////////
//
// class GGGuildChatFactory;
//
// Factory for GGGuildChat
//
//////////////////////////////////////////////////////////////////////

class GGGuildChatFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GGGuildChat(); }

	// get packet name
	string getPacketName() const throw() { return "GGGuildChat"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GG_GUILD_CHAT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GGGuildChatPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE +
			   szGuildID +						// GuildID
			   szBYTE + 10 +					// Sender
			   szuint +							// Color
			   szBYTE + 128;					// Message
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GGGuildChatHandler;
//
//////////////////////////////////////////////////////////////////////

class GGGuildChatHandler {
	
public :

	// execute packet's handler
	static void execute(GGGuildChat* pPacket) throw(ProtocolException, Error);

};

#endif
