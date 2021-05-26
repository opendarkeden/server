//--------------------------------------------------------------------------------
// 
// Filename    : CGConnectSetKey.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_CONNECTSETKEY_H__
#define __CL_CONNECTSETKEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGConnectSetKey;
//
// 클라이언트가 로그인 서버에게 최초에 전송하는 패킷이다.
// 아이디와 패스워드가 암호화되어 있다.
//
//--------------------------------------------------------------------------------



class CGConnectSetKey : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID () const  { return PACKET_CG_ENCODE_KEY; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const  
	{ 
		return szWORD 						// authentication key
			+ szWORD; 						// Slayer or Vampire?
	}

	// get packet name
	string getPacketName() const  { return "CGConnectSetKey"; }
	
	// get packet's debug string
	string toString() const  { return "CGConnectSetKey"; }

public:

	// get/set key
	WORD getEncryptKey () const  { return m_EncryptKey; }

	WORD getHashKey () const  { return m_HashKey; }

	void setEncryptKey ( WORD key )  { m_EncryptKey = key; }

	void setHashKey ( WORD key )	 { m_HashKey = key; }

private :

	WORD m_EncryptKey;

	WORD m_HashKey;	
};


//--------------------------------------------------------------------------------
//
// class CLLoginFactory;
//
// Factory for CLLogin
//
//--------------------------------------------------------------------------------

class CGConnectSetKeyFactory : public PacketFactory {

public:
	
	// create packet
	Packet * createPacket ()  { return new CGConnectSetKey(); }

	// get packet name
	string getPacketName() const  { return "CGConnectSetKey"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_ENCODE_KEY; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szWORD + szWORD;  }

};


//--------------------------------------------------------------------------------
//
// class CLLoginHandler;
//
//--------------------------------------------------------------------------------

class CGConnectSetKeyHandler {

public:

	// execute packet's handler
	static void execute(CGConnectSetKey* pPacket, Player* pPlayer) ;
};

#endif
