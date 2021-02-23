//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildInfo2.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_INFO2_H__
#define __GUILD_INFO2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "GuildMemberInfo2.h"

#include <slist>

typedef slist<GuildMemberInfo2*> GuildMemberInfoList2;
typedef slist<GuildMemberInfo2*>::const_iterator GuildMemberInfoListConstItor2;

//////////////////////////////////////////////////////////////////////
//
// class GuildInfo2;
//
//////////////////////////////////////////////////////////////////////

class GuildInfo2 {

public :
	
	// constructor
	GuildInfo2 () throw ();
	
	// destructor
	~GuildInfo2 () throw ();

public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return ( szGuildID
			   + szBYTE + 30
			   + szGuildType
			   + szGuildRace
			   + szGuildState
			   + szServerGroupID
			   + szZoneID
			   + szBYTE + 20
			   + szBYTE + 11
			   + szBYTE + 256 ) + szWORD
			   + GuildMemberInfo2::getMaxSize() * 220 + szWORD;
	}

	// get packet's debug string
	string toString () const throw ();

	// get/set GuildID
	GuildID_t getID() const throw() { return m_ID; }
	void setID( GuildID_t GuildID ) throw() { m_ID = GuildID; }

	// get/set Guild Name
	string getName() const throw() { return m_Name; }
	void setName( const string& GuildName ) throw() { m_Name = GuildName; }

	// get/set GuildType
	GuildType_t getType() const throw() { return m_Type; }
	void setType( GuildType_t type ) throw() { m_Type = type; }

	// get/set Race
	GuildRace_t getRace() const throw() { return m_Race; }
	void setRace( GuildRace_t race ) throw() { m_Race = race; }

	// get/set state
	GuildState_t getState() const throw() { return m_State; }
	void setState( GuildState_t state ) throw() { m_State = state; }

	// get/set server group ID
	ServerGroupID_t getServerGroupID() const throw() { return m_ServerGroupID; }
	void setServerGroupID( ServerGroupID_t serverGroupID ) throw() { m_ServerGroupID = serverGroupID; }

	// get/set Zone ID
	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID( ZoneID_t zoneID ) throw() { m_ZoneID = zoneID; }

	// get/set Guild Master
	string getMaster() const throw() { return m_Master; }
	void setMaster( const string& master ) throw() { m_Master = master; }

	// get/set Guild Expire Date
	string getDate() const throw() { return m_Date; }
	void setDate( const string& date ) throw() { m_Date = date; }

	// get/set guild intro
	string getIntro() const throw() { return m_Intro; }
	void setIntro( const string& intro ) throw() { m_Intro = intro; }

	// get guild member info list num
	WORD getGuildMemberInfoListNum() const throw() { return m_GuildMemberInfoList.size(); }

	// add GuildMemberInfo
	void addGuildMemberInfo( GuildMemberInfo2* pGuildMemberInfo ) throw() { m_GuildMemberInfoList.push_front( pGuildMemberInfo ); }

	// clear GuildMemberInfoList
	void clearGuildMemberInfoList() throw();

	// pop front element in GuildMemberInfoList
	GuildMemberInfo2* popFrontGuildMemberInfoList() throw()
	{
		if ( m_GuildMemberInfoList.empty() )
		return NULL;

		GuildMemberInfo2* pGuildMemberInfo = m_GuildMemberInfoList.front();
		m_GuildMemberInfoList.pop_front();
		return pGuildMemberInfo;
	}

private :

	// 길드 아이디
	GuildID_t m_ID;

	// 길드 이름
	string m_Name;

	// guild type
	GuildType_t m_Type;

	// guild race
	GuildRace_t m_Race;

	// guild state
	GuildState_t m_State;

	// guild server group ID
	ServerGroupID_t m_ServerGroupID;

	// guild zone ID
	ZoneID_t m_ZoneID;

	// 길드 마스터
	string m_Master;

	// 길드 Expire Date
	string m_Date;

	// guild intro
	string m_Intro;

	// guild member list
	GuildMemberInfoList2 m_GuildMemberInfoList;

};

#endif
