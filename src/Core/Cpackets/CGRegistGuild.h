//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRegistGuild.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REGIST_GUILD_H__
#define __CG_REGIST_GUILD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRegistGuild;
//
//////////////////////////////////////////////////////////////////////

class CGRegistGuild : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_REGIST_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_GuildName.size() + szBYTE + m_GuildIntro.size(); }

	// get packet name
	string getPacketName() const throw() { return "CGRegistGuild"; }

	// get packet's debug string
	string toString() const throw();

	// get/set GuildName
	string getGuildName() const throw() { return m_GuildName; }
	void setGuildName( const string& guildName ) throw() { m_GuildName = guildName; }

	// get/set GuildIntro
	string getGuildIntro() const throw() { return m_GuildIntro; }
	void setGuildIntro( const string& guildIntro ) throw() { m_GuildIntro = guildIntro; }


private :

	// Guild Name
	string m_GuildName;

	// Guild Intro
	string m_GuildIntro;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGRegistGuildFactory;
//
// Factory for CGRegistGuild
//
//////////////////////////////////////////////////////////////////////

class CGRegistGuildFactory : public PacketFactory {

public:
	
	// constructor
	CGRegistGuildFactory() throw() {}
	
	// destructor
	virtual ~CGRegistGuildFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRegistGuild(); }

	// get packet name
	string getPacketName() const throw() { return "CGRegistGuild"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_REGIST_GUILD; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 30 + szBYTE + 256; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRegistGuildHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRegistGuildHandler {

public:

	// execute packet's handler
	static void execute(CGRegistGuild* pCGRegistGuild, Player* pPlayer) throw(Error);

};

#endif
