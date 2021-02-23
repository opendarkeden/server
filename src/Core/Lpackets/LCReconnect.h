//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCReconnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_RECONNECT_H__
#define __LC_RECONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCReconnect;
//
// 로그인 서버에서 인증을 받고, 캐릭터를 선택한 클라이언트의 경우,
// 캐릭터가 이전 연결에 존재했던 존을 알아내서, 그 존을 관리하는
// 게임 서버로 재접속하라는 패킷이다.
//
//////////////////////////////////////////////////////////////////////

class LCReconnect : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_RECONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_GameServerIP.size() 	// 게임 서버 아이피
			+ szuint							// 게임 서버 포트
			+ szDWORD; 							// 인증 키
	}

	// get packet name
	string getPacketName() const throw() { return "LCReconnect"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set game server's ip
	string getGameServerIP() const throw() { return m_GameServerIP; }
	void setGameServerIP(const string & ip) throw() { m_GameServerIP = ip; }

	// get/set game server's port
	uint getGameServerPort() const throw() { return m_GameServerPort; }
	void setGameServerPort(uint port) throw() { m_GameServerPort = port; }

	// get/set key
	DWORD getKey() const throw() { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private :
	
	// New GameServer's IP
	string m_GameServerIP;

	// New GameServer's TCP Port
	uint m_GameServerPort;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class LCReconnectFactory;
//
// Factory for LCReconnect
//
//////////////////////////////////////////////////////////////////////

class LCReconnectFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCReconnect(); }

	// get packet name
	string getPacketName() const throw() { return "LCReconnect"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_RECONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LCReconnectPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + 15 	// 게임 서버 아이피
			+ szuint		// 게임 서버 포트
			+ szDWORD; 		// 인증 키
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCReconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class LCReconnectHandler {

public:

	// execute packet's handler
	static void execute(LCReconnect* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
