//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildMemberInfo.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_MEMBER_INFO_H__
#define __GUILD_MEMBER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class GuildMemberInfo;
//
// 클라이언트에 길드멤버 리스트를 보낸다.
//
//////////////////////////////////////////////////////////////////////

class GuildMemberInfo {

public :
	
	// constructor
	GuildMemberInfo () throw ();
	
	// destructor
	~GuildMemberInfo () throw ();

public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return ( szBYTE + 20 + szGuildMemberRank + szbool) * 220 + szBYTE + szServerID;
	}

	// get packet's debug string
	string toString () const throw ();

	// get/set Name
	string getName() const throw() { return m_Name; }
	void setName( const string& Name ) throw() { m_Name = Name; }

	// get/set GuildMemberRank
	GuildMemberRank_t getRank() const throw() { return m_Rank; }
	void setRank( GuildMemberRank_t rank ) throw() { m_Rank = rank; }

	// get/set Guild Member LogOn
	bool getLogOn() const throw() { return m_bLogOn; }
	void setLogOn( bool logOn ) throw() { m_bLogOn = logOn; }

	// get/set Guild Member Zone(current)
	ServerID_t	getServerID()	const throw() { return m_ServerID; }
	void		setServerID( ServerID_t	ServerID)	throw() { m_ServerID = ServerID; }

private :

	// 이름
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_Rank;


	// Guild Member LogOn
	bool m_bLogOn;

	// Guild Member Zone(current)
	ServerID_t	m_ServerID;

};

#endif
