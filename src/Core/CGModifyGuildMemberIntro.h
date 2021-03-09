//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyGuildMemberIntro.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_GUILD_MEMBER_INTRO_H__
#define __CG_MODIFY_GUILD_MEMBER_INTRO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberIntro;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberIntro : public Packet
{
public:
	CGModifyGuildMemberIntro() {};
    ~CGModifyGuildMemberIntro() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_MODIFY_GUILDMEMBER_INTRO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const 
	{ 
		return szGuildID + szBYTE + m_GuildMemberIntro.size();
	}

	// get packet name
	string getPacketName() const  { return "CGModifyGuildMemberIntro"; }

	// get packet's debug string
	string toString() const ;

	// get/set GuildID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set intro
	const string& getGuildMemberIntro() const  { return m_GuildMemberIntro; }
	void setGuildMemberIntro(const string& intro )  { m_GuildMemberIntro = intro; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild Member Intro
	string m_GuildMemberIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberIntroFactory;
//
// Factory for CGModifyGuildMemberIntro
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberIntroFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyGuildMemberIntroFactory()  {}
	
	// destructor
	virtual ~CGModifyGuildMemberIntroFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGModifyGuildMemberIntro(); }

	// get packet name
	string getPacketName() const  { return "CGModifyGuildMemberIntro"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_MODIFY_GUILDMEMBER_INTRO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szGuildID + szBYTE + 255; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberIntroHandler;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberIntroHandler {

public:

	// execute packet's handler
	static void execute(CGModifyGuildMemberIntro* pCGModifyGuildMemberIntro, Player* pPlayer) ;

};

#endif
