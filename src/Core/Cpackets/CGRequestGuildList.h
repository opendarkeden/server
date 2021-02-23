
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestGuildList.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUER_GUILD_LIST_H__
#define __CG_REQUER_GUILD_LIST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

typedef BYTE GuildType_t;


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildList;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildList : public Packet
{
public:
	enum
	{
		GUILDTYPE_WAIT,             		// 등록대기중 길드.
		GUILDTYPE_NORMAL,                   // 등록된 길드(일반길드).
		GUILDTYPE_MAX
	};

	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_REQUEST_GUILD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return sizeof(GuildType_t); }

	// get packet name
	string getPacketName() const throw() { return "CGRequestGuildList"; }

	// get packet's debug string
	string toString() const throw();

	// get/set GuildType
	GuildType_t	getGuildType()	const throw() {	return m_GuildType; }
	void		setGuildType( GuildType_t GuildType )	throw()	{ m_GuildType = GuildType; }
	
	GuildType_t	m_GuildType;
	

};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildListFactory;
//
// Factory for CGRequestGuildList
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildListFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestGuildListFactory() throw() {}
	
	// destructor
	virtual ~CGRequestGuildListFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestGuildList(); }

	// get packet name
	string getPacketName() const throw() { return "CGRequestGuildList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_REQUEST_GUILD_LIST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return sizeof(GuildType_t); }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildListHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildListHandler {

public:

	// execute packet's handler
	static void execute(CGRequestGuildList* pCGRequestGuildList, Player* pPlayer) throw(Error);

};

#endif
