//----------------------------------------------------------------------
// 
// Filename    : GSAddGuildMember.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_ADD_GUILD_MEMBER_H__
#define __GS_ADD_GUILD_MEMBER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSAddGuildMember;
//
// 길드 멤버 추가를 쉐어드 서버에 요청한다.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSAddGuildMember : public Packet {

public:
	GSAddGuildMember() {};
    ~GSAddGuildMember() {};
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream& oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GS_ADD_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szGuildID +					// guild id
			   szBYTE +						// member name length
			   m_Name.size() +				// member name
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   m_GuildMemberIntro.size() +	// Guild Member Intro
			   szServerGroupID;				// server group ID
	}

	// get packet name
	string getPacketName() const  { return "GSAddGuildMember"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set guild ID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t id )  { m_GuildID = id; }

	// get/set name
	const string& getName() const  { return m_Name; }
	void setName(const string& name )  { m_Name = name; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank() const  { return m_GuildMemberRank; }
	void setGuildMemberRank(GuildMemberRank_t GuildMemberRank )  { m_GuildMemberRank = GuildMemberRank; }

	// get/set Guild Member Intro
	const string& getGuildMemberIntro() const  { return m_GuildMemberIntro; }
	void setGuildMemberIntro(const string& GuildMemberIntro )  { m_GuildMemberIntro = GuildMemberIntro; }

	// get/set server group ID
	ServerGroupID_t getServerGroupID() const  { return m_ServerGroupID; }
	void setServerGroupID(ServerGroupID_t serverGroupID )  { m_ServerGroupID = serverGroupID; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// 멤버 이름
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Guild Member Intro
	string m_GuildMemberIntro;

	// Server Group ID
	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class GSAddGuildFactory;
//
// Factory for GSAddGuild
//
//////////////////////////////////////////////////////////////////////

class GSAddGuildMemberFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSAddGuildMember(); }

	// get packet name
	string getPacketName() const  { return "GSAddGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GS_ADD_GUILD_MEMBER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szGuildID +					// guild id
			   szBYTE +						// member name length
			   20 +							// member name max size
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   256 +						// Guild Member Intro max size
			   szServerGroupID;				// server group ID
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSAddGuildMemberHandler {
	
public:

	// execute packet's handler
	static void execute(GSAddGuildMember* pPacket, Player* pPlayer) ;

};

#endif
