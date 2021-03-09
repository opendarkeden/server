//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildMemberInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_MEMBER_INFO_H__
#define __GC_SHOW_GUILD_MEMBER_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildMemberInfo;
//
// 클라이언트에 길드 등록 창을 띄우도록 한다.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildMemberInfo : public Packet {

public :
	GCShowGuildMemberInfo() {};
    ~GCShowGuildMemberInfo() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOW_GUILD_MEMBER_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const 
	{ 
		return szGuildID +					// Guild ID
			   szBYTE +						// Name length
			   m_Name.size() +				// Name
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   m_GuildMemberIntro.size();	// Guild Member Intro
	}

	// get packet name
	string getPacketName() const  { return "GCShowGuildMemberInfo"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set Guild ID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t GuildID )  { m_GuildID = GuildID; }

	// get/set Name
	const string& getName() const  { return m_Name; }
	void setName(const string& name )  { m_Name = name; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank() const  { return m_GuildMemberRank; }
	void setGuildMemberRank(GuildMemberRank_t guildMemberRank )  { m_GuildMemberRank = guildMemberRank; }

	// get/set Guild Member Intro
	const string& getGuildMemberIntro() const  { return m_GuildMemberIntro; }
	void setGuildMemberIntro(const string& intro )  { m_GuildMemberIntro = intro; }

private :
	
	// Guild ID
	GuildID_t m_GuildID;

	// Name
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Guild Member Intro
	string m_GuildMemberIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildMemberInfoFactory;
//
// Factory for GCShowGuildMemberInfo
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildMemberInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCShowGuildMemberInfo(); }

	// get packet name
	string getPacketName() const  { return "GCShowGuildMemberInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOW_GUILD_MEMBER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const 
	{
		return szGuildID +					// Guild ID
			   szBYTE +						// Name length
			   20 +							// Name max size
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   256;							// Guild Member Intro max size
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildMemberInfo;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildMemberInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildMemberInfo* pPacket, Player* pPlayer) ;

};

#endif
