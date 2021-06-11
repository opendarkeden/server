//----------------------------------------------------------------------
// 
// Filename    : GSModifyGuildMember.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_MODIFY_GUILD_MEMBER_H__
#define __GS_MODIFY_GUILD_MEMBER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSModifyGuildMember;
//
// 팀이 추가를 쉐어드 서버에 요청한다.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSModifyGuildMember : public Packet {

public:
	GSModifyGuildMember() {};
    ~GSModifyGuildMember() {};
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream& oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GS_MODIFY_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// name length
			   m_Name.size() +			// name 
			   szGuildMemberRank +		// Guild Member Rank
			   szBYTE +					// sender length
			   m_Sender.size();			// sender
	}

	// get packet name
	string getPacketName() const  { return "GSModifyGuildMember"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set Guild ID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Name
	const string& getName() const  { return m_Name; }
	void setName(const string& name )  { m_Name = name; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank() const  { return m_GuildMemberRank; }
	void setGuildMemberRank(GuildMemberRank_t GuildMemberRank )  { m_GuildMemberRank = GuildMemberRank; }

	// get/set sender
	const string& getSender() const  { return m_Sender; }
	void setSender(const string& sender )  { m_Sender = sender; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// name
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// sender
	string m_Sender;

};


//////////////////////////////////////////////////////////////////////
//
// class GSModifyGuildMemberFactory;
//
// Factory for GSModifyGuildMember
//
//////////////////////////////////////////////////////////////////////

class GSModifyGuildMemberFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSModifyGuildMember(); }

	// get packet name
	string getPacketName() const  { return "GSModifyGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GS_MODIFY_GUILD_MEMBER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// name length
			   20 +					// name max length
			   szGuildMemberRank +	// guild member rank
			   szBYTE +				// sender length
			   20;					// sender max length
	}
};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSModifyGuildMemberHandler {
	
public:

	// execute packet's handler
	static void execute(GSModifyGuildMember* pPacket, Player* pPlayer) ;

};

#endif
