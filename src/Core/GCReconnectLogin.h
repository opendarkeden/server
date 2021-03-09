//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnectLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RECONNECT_LOGIN_H__
#define __GC_RECONNECT_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLogin;
//
// 로그인 서버에서 인증을 받고, 캐릭터를 선택한 클라이언트의 경우,
// 캐릭터가 이전 연결에 존재했던 존을 알아내서, 그 존을 관리하는
// 게임 서버로 재접속하라는 패킷이다.
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLogin : public Packet {

public :
	GCReconnectLogin() {};
    ~GCReconnectLogin() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_RECONNECT_LOGIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szBYTE + m_LoginServerIP.size() 	// 게임 서버 아이피
			+ szuint							// 게임 서버 포트
			+ szDWORD; 							// 인증 키
	}

	// get packet name
	string getPacketName() const  { return "GCReconnectLogin"; }
	
	// get packet's debug string
	string toString() const ;

public :

	// get/set game server's ip
	string getLoginServerIP() const  { return m_LoginServerIP; }
	void setLoginServerIP(const string & ip)  { m_LoginServerIP = ip; }

	// get/set game server's port
	uint getLoginServerPort() const  { return m_LoginServerPort; }
	void setLoginServerPort(uint port)  { m_LoginServerPort = port; }

	// get/set key
	DWORD getKey() const  { return m_Key; }
	void setKey(DWORD key)  { m_Key = key; }

private :
	
	// New LoginServer's IP
	string m_LoginServerIP;

	// New LoginServer's TCP Port
	uint m_LoginServerPort;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLoginFactory;
//
// Factory for GCReconnectLogin
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLoginFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCReconnectLogin(); }

	// get packet name
	string getPacketName() const  { return "GCReconnectLogin"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_RECONNECT_LOGIN; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReconnectLoginPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szBYTE + 15 	// 게임 서버 아이피
			+ szuint		// 게임 서버 포트
			+ szDWORD; 		// 인증 키
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLoginHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLoginHandler {

public :

	// execute packet's handler
	static void execute(GCReconnectLogin* pPacket, Player* pPlayer) ;

};

#endif
