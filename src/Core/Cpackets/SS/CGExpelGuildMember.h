//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGExpelGuildMember.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_EXPEL_GUILD_MEMBER_H__
#define __CG_EXPEL_GUILD_MEMBER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGExpelGuildMember;
//
//////////////////////////////////////////////////////////////////////

class CGExpelGuildMember : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_EXPEL_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szGuildID + szBYTE + m_Name.size(); }

	// get packet name
	string getPacketName() const throw() { return "CGExpelGuildMember"; }

	// get packet's debug string
	string toString() const throw();

	// get/set GuildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set name
	const string& getName() const throw() { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }


private :

	// GuildID
	GuildID_t m_GuildID;

	// name
	string m_Name;

};


//////////////////////////////////////////////////////////////////////
//
// class CGExpelGuildMemberFactory;
//
// Factory for CGExpelGuildMember
//
//////////////////////////////////////////////////////////////////////

class CGExpelGuildMemberFactory : public PacketFactory {

public:
	
	// constructor
	CGExpelGuildMemberFactory() throw() {}
	
	// destructor
	virtual ~CGExpelGuildMemberFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGExpelGuildMember(); }

	// get packet name
	string getPacketName() const throw() { return "CGExpelGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_EXPEL_GUILD_MEMBER; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szGuildID + szBYTE + 20; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGExpelGuildMemberHandler;
//
//////////////////////////////////////////////////////////////////////

class CGExpelGuildMemberHandler {

public:

	// execute packet's handler
	static void execute(CGExpelGuildMember* pCGExpelGuildMember, Player* pPlayer) throw(Error);

};

#endif
