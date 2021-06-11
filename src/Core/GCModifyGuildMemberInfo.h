//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCModifyGuildMemberInfo.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_GUILD_MEMBER_INFO_H__
#define __GC_MODIFY_GUILD_MEMBER_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfo;
//
// 게임 서버가 특정 플레이어의 ModifyGuildMemberInfo 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 ModifyGuildMemberInfo 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfo : public Packet {

public :
	GCModifyGuildMemberInfo() {};
    ~GCModifyGuildMemberInfo() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_MODIFY_GUILD_MEMBER_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szGuildID + szBYTE + m_GuildName.size() + szGuildMemberRank; }

	// get packet name
	string getPacketName() const  { return "GCModifyGuildMemberInfo"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set Guild ID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Guild Name
	string getGuildName() const  { return m_GuildName; }
	void setGuildName(const string& guildName)  { m_GuildName = guildName; }

	// get/set Guild ID
	GuildMemberRank_t getGuildMemberRank() const  { return m_GuildMemberRank; }
	void setGuildMemberRank(GuildMemberRank_t guildMemberRank )  { m_GuildMemberRank = guildMemberRank; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	string m_GuildName;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfoFactory;
//
// Factory for GCModifyGuildMemberInfo
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCModifyGuildMemberInfo(); }

	// get packet name
	string getPacketName() const  { return "GCModifyGuildMemberInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MODIFY_GUILD_MEMBER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCModifyGuildMemberInfoPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szGuildID + szBYTE + 30 + szGuildMemberRank; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCModifyGuildMemberInfo* pPacket, Player* pPlayer) ;

};

#endif
