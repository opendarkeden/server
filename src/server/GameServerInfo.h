//----------------------------------------------------------------------
//
// Filename    : GameServerInfo.h
// Written By  : Reiot
// Description : 로그인 서버에서 갖고 있는 각 게임 서버에 대한 정보
//
//----------------------------------------------------------------------

#ifndef __GAME_SERVER_INFO_H__
#define __GAME_SERVER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "StringStream.h"


//----------------------------------------------------------------------
//
// class GameServerInfo;
//
// GAME DB의 GameServerInfo 테이블에서 읽어들인 각 게임 서버의 정보를
// 담은 클래스이다.
//
//----------------------------------------------------------------------

class GameServerInfo
{
public:
	// constructor
	GameServerInfo() : m_bNonPKServer( false ) {}

public :

	// get/set GameServerID
	ServerID_t getServerID() const throw() { return m_ServerID; }
	void setServerID( ServerID_t ServerID ) throw() { m_ServerID = ServerID; }

	// get/set host name
	const string& getNickname () const throw () { return m_Nickname; }
	void setNickname ( const string &nickname ) throw () { m_Nickname = nickname; }
	
	// get/set ip address
	const string& getIP () const throw () { return m_IP; }
	void setIP ( const string &ip ) throw () { m_IP = ip; }

	// get/set port
	uint getTCPPort () const throw () { return m_TCPPort; }
	void setTCPPort ( uint port ) throw () { m_TCPPort = port; }

	// get/set UDP port
	uint getUDPPort () const throw () { return m_UDPPort; }
	void setUDPPort ( uint port ) throw () { m_UDPPort = port; }

	// get/set GameServerGroupID
	ServerGroupID_t getGroupID() const throw() { return m_GroupID; }
	void setGroupID( ServerGroupID_t GroupID ) { m_GroupID = GroupID; }

	// get/set GameWorldID
	WorldID_t getWorldID() const throw() { return m_WorldID; }
	void setWorldID( WorldID_t WorldID ) { m_WorldID= WorldID; }

	// get/set ServerStat
	ServerStatus getServerStat() const throw() { return m_ServerStat; }
	void setServerStat( ServerStatus Stat ) throw() { m_ServerStat = Stat; }

	// PK Server
	bool isNonPKServer() const { return m_bNonPKServer; }
	void setNonPKServer() { m_bNonPKServer = true; }

	ServerID_t getCastleFollowingServerID() const { return m_CastleFollowingServerID; }
	void setCastleFollowingServerID( ServerID_t sID ) { m_CastleFollowingServerID = sID; }

	// get debug string
	string toString () const throw () 
	{
		StringStream msg;
		msg << "GameServerInfo("
			<< "ServerID: " << (int)m_ServerID
			<< ",Nickname:" << m_Nickname 
			<< ",IP: " << m_IP
			<< ",TCPPort:" << m_TCPPort
			<< ",UDPPort:" << m_UDPPort
			<< ",GroupID:" << (int)m_GroupID
			<< ",WorldID:" << (int)m_WorldID
			<< ",ServerStat:" << (int)m_GroupID
			<< ")";
		return msg.toString();
	}


private :

	// GameServer ID
	ServerID_t m_ServerID;

	// GameServer Process's nick name
	string m_Nickname;

	// Host's IP address
	string m_IP;

	// GameServer's port
	uint m_TCPPort;
	uint m_UDPPort;

	// GameServerGroupID
	ServerGroupID_t m_GroupID;

	// GameServerWorld
	WorldID_t m_WorldID;

	// Server Stat
	ServerStatus m_ServerStat;

	// is PK Server
	bool m_bNonPKServer;

	ServerID_t m_CastleFollowingServerID;

};

#endif
