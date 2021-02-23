//----------------------------------------------------------------------
// 
// Filename    : SGGuildMemberLogOnOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_GUILDMEMBER_LOGON_OK_H__
#define __SG_GUILDMEMBER_LOGON_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGGuildMemberLogOnOK;
//
// 팀이 추가 되었음을 게임서버에 알린다.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGGuildMemberLogOnOK : public Packet {

public:
	
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_SG_GUILDMEMBER_LOGON_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// name length
			   m_Name.size() +		// name size
			   szbool +				// log on
			   szServerID;			// server id
	}

	// get packet name
	string getPacketName() const throw() { return "SGGuildMemberLogOnOK"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set guildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set guild name
	const string& getName() const throw() { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

	// get/set logon
	bool getLogOn() const throw() { return m_bLogOn; }
	void setLogOn( bool logOn ) throw() { m_bLogOn = logOn; }

	// get/set serverid
	ServerID_t	getServerID() const throw() { return m_ServerID; }
	void		setServerID( ServerID_t ServerID ) throw() { m_ServerID = ServerID; }
	
private :

	// GuildID
	GuildID_t m_GuildID;

	// name
	string m_Name;

	// logon
	bool m_bLogOn;

	// serverid
	ServerID_t	m_ServerID;

};


//////////////////////////////////////////////////////////////////////
//
// class SGGuildMemberLogOnOKFactory;
//
// Factory for SGGuildMemberLogOnOK
//
//////////////////////////////////////////////////////////////////////

class SGGuildMemberLogOnOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGGuildMemberLogOnOK(); }

	// get packet name
	string getPacketName() const throw() { return "SGGuildMemberLogOnOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_SG_GUILDMEMBER_LOGON_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szGuildID +				// guild ID
			   szBYTE +					// name length
			   20 + 					// name max size
			   szbool +					// logon
			   szServerID;				// serverid
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGGuildMemberLogOnOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGGuildMemberLogOnOK* pPacket) throw(ProtocolException, Error);

};

#endif
