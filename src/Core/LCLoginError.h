//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCLoginError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_LOGIN_ERROR_H__
#define __LC_LOGIN_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCLoginError;
//
//
//////////////////////////////////////////////////////////////////////

class LCLoginError : public Packet {

public:
	LCLoginError() {};
    ~LCLoginError() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_LOGIN_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szBYTE; }
	
	// get packet's name
	string getPacketName() const  { return "LCLoginError"; }
	
	// get packet's debug string
	string toString() const ;
	
//	string getMessage() const  { return m_Message; }
//	void setMessage(string message)  { m_Message = message; }
	BYTE getErrorID() const  { return m_ErrorID; }
	void setErrorID(BYTE ErrorID)  { m_ErrorID = ErrorID; }

private : 

	// 에러 ID
	BYTE m_ErrorID;

//	string m_Message;

};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginErrorFactory;
//
// Factory for LCLoginError
//
//////////////////////////////////////////////////////////////////////

class LCLoginErrorFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCLoginError(); }

	// get packet name
	string getPacketName() const  { return "LCLoginError"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_LOGIN_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCLoginErrorHandler {

public:

	// execute packet's handler
	static void execute(LCLoginError* pPacket, Player* pPlayer) ;

};

#endif
