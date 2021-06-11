//----------------------------------------------------------------------
// 
// Filename    : SGModifyGuildOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_MODIFY_GUILD_OK_H__
#define __SG_MODIFY_GUILD_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGModifyGuildOK;
//
// 팀이 추가 되었음을 게임서버에 알린다.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGModifyGuildOK : public Packet {

public:
	SGModifyGuildOK() {};
    ~SGModifyGuildOK() {};
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream& oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_SG_MODIFY_GUILD_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szGuildID +  				// guild ID
			   szGuildState;				// guild state
	}

	// get packet name
	string getPacketName() const  { return "SGModifyGuildOK"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set guildID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set GuildState
	GuildState_t getGuildState() const  { return m_GuildState; }
	void setGuildState(GuildState_t guildState )  { m_GuildState = guildState; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild State
	GuildState_t m_GuildState;

};


//////////////////////////////////////////////////////////////////////
//
// class SGModifyGuildOKFactory;
//
// Factory for SGModifyGuildOK
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new SGModifyGuildOK(); }

	// get packet name
	string getPacketName() const  { return "SGModifyGuildOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_SG_MODIFY_GUILD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szGuildID +				// guild ID
			   szGuildState;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGModifyGuildOK* pPacket) ;

};

#endif
