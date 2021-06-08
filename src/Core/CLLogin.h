//--------------------------------------------------------------------------------
// 
// Filename    : CLLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_LOGIN_H__
#define __CL_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLLogin;
//
// 클라이언트가 로그인 서버에게 최초에 전송하는 패킷이다.
// 아이디와 패스워드가 암호화되어 있다.
//
//--------------------------------------------------------------------------------

// 최대 MAC ADDRESS 길이
#define	MAX_LENGTH_MAC	6	


class CLLogin : public Packet {
public:
	CLLogin() : m_LoginMode (LOGIN_MODE_NORMAL ) {
	  m_strMacAddress = "";
	}
    virtual ~CLLogin() {};

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CL_LOGIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;

	// get packet name
	string getPacketName() const  { return "CLLogin"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set player's id
	string getID() const  { return m_ID; }
	void setID(string id)  { m_ID = id; }

	// get/set player's password
	string getPassword() const  { return m_Password; }
	void setPassword(string password)  { m_Password = password; }

	// get/set Cpsso imformation
	bool isNetmarble() const  { return m_bNetmarble; }
	void setNetmarble(bool netmarble)  { m_bNetmarble = netmarble; }

	bool isAdult() const  { return m_bAdult; }
	void setAdult(bool adult)  { m_bAdult = adult; }

	// add - inthesky
	bool checkMacAddress(string currentMac) const ;
	string getMacAddress() const  { return m_strMacAddress; }

	const BYTE* getRareMacAddress() const { return m_cMacAddress; }

	void setWebLogin() { m_LoginMode = LOGIN_MODE_WEBLOGIN; }
	bool isWebLogin() const { return m_LoginMode == LOGIN_MODE_WEBLOGIN; }

private :

	// 플레이어 아이디
	string m_ID;

	// 플레이어 패스워드
	string m_Password;

	// 보내고 받는 건 아니지만 정보를 가지고 있을 필요가 있어서 멤버 변수 추가
	// Size 계산은 하지 않는다. (넷마블의 Cpsso 방식의 인증 정보에 들어 있는 내용 보관)
	bool m_bNetmarble;
	bool m_bAdult;

	BYTE m_cMacAddress[6];
	string m_strMacAddress;

	BYTE m_LoginMode;
};


//--------------------------------------------------------------------------------
//
// class CLLoginFactory;
//
// Factory for CLLogin
//
//--------------------------------------------------------------------------------

class CLLoginFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLLogin(); }

	// get packet name
	string getPacketName() const  { return "CLLogin"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_LOGIN; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szint + 2048 + szBYTE + 30 + 6 + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class CLLoginHandler;
//
//--------------------------------------------------------------------------------

class CLLoginHandler {

public:

	// execute packet's handler
	static void execute(CLLogin* pPacket, Player* pPlayer) ;

private :
	static bool checkFreePass(CLLogin* pPacket, Player* pPlayer) ;
	static bool	checkNetMarbleClient (CLLogin* pPacket , Player* pPlayer) ;
	static bool checkWebLogin(CLLogin* pPacket, Player* pPlayer ) ;
#ifdef __THAILAND_SERVER__
	static bool onChildGuardTimeArea(int pm, int am, string enable);
#endif
};

#endif
