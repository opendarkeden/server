//--------------------------------------------------------------------------------
// 
// Filename    : WarInfo.h 
// Written By  : 
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GUILD_WAR_LIST_H__
#define __GUILD_WAR_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WarInfo.h"

//--------------------------------------------------------------------------------
//
// class WarInfo;
//
// 하나의 전쟁에 대한 정보
//
//--------------------------------------------------------------------------------

class GuildWarInfo : public WarInfo {

public :
	typedef ValueList<GuildID_t>	GuildIDList;

public :
	GuildWarInfo() {}
	~GuildWarInfo() {}
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	PacketSize_t getSize() const throw() 
	{ 
		return WarInfo::getSize() 
				+ szZoneID 
				+ szBYTE + m_AttackGuildName.size() 
				+ szBYTE + m_DefenseGuildName.size() 
				+ m_GuildIDs.getPacketSize();
	}

	static PacketSize_t getMaxSize() throw() 
	{ 
		return WarInfo::getMaxSize() 
				+ szZoneID 
				+ szBYTE + 40
				+ szBYTE + 30
				+ GuildIDList::getPacketMaxSize();
	}

	// get packet's debug string
	string toString() const throw();

	void operator = (const GuildWarInfo& GWI)
	{
		m_StartTime			= GWI.m_StartTime;
		m_RemainTime 		= GWI.m_RemainTime;
		m_CastleID 			= GWI.m_CastleID;
		m_DefenseGuildName 	= GWI.m_DefenseGuildName;
		m_AttackGuildName 	= GWI.m_AttackGuildName;
		m_GuildIDs			= GWI.m_GuildIDs;
	}

public :
	WarType_t 			getWarType() const 			{ return WAR_GUILD; }

	ZoneID_t			getCastleID() const			{ return m_CastleID; }
	void 				setCastleID(ZoneID_t zid) 	{ m_CastleID = zid; }

	const string&		getAttackGuildName() const						{ return m_AttackGuildName; }
	void 				setAttackGuildName(const string& guildName) 	{ m_AttackGuildName = guildName; }

	const string&		getDefenseGuildName() const						{ return m_DefenseGuildName; }
	void 				setDefenseGuildName(const string& guildName) 	{ m_DefenseGuildName = guildName; }

	GuildIDList& 		getJoinGuilds()				{ return m_GuildIDs; }
	void 				addJoinGuild(GuildID_t gid)	{ m_GuildIDs.addValue(gid); }

private :
	ZoneID_t				m_CastleID;				// 전쟁중인 성
	string					m_DefenseGuildName;		// 방어 길드
	string					m_AttackGuildName;		// 공격 길드
	GuildIDList				m_GuildIDs;				// 참여길드들
};

#endif
