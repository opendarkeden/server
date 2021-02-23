//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCOtherGuildName.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_GUILD_NAME_H__
#define __GC_OTHER_GUILD_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildName;
//
// 게임 서버가 특정 플레이어의 OtherGuildName 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 OtherGuildName 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildName : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_OTHER_GUILD_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szGuildID + szBYTE + m_GuildName.size(); }

	// get packet name
	string getPacketName() const throw() { return "GCOtherGuildName"; }
	
	// get packet's debug string
	string toString() const throw();

	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID( ObjectID_t objectID ) throw() { m_ObjectID = objectID; }

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set Guild Name
	string getGuildName() const throw() { return m_GuildName; }
	void setGuildName(const string& guildName) throw() { m_GuildName = guildName; }

private :

	ObjectID_t m_ObjectID;

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	string m_GuildName;

};


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildNameFactory;
//
// Factory for GCOtherGuildName
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildNameFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCOtherGuildName(); }

	// get packet name
	string getPacketName() const throw() { return "GCOtherGuildName"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_OTHER_GUILD_NAME; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCOtherGuildNamePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szGuildID + szBYTE + 30; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCOtherGuildNameHandler;
//
//////////////////////////////////////////////////////////////////////

class GCOtherGuildNameHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCOtherGuildName* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
