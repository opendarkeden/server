//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCSelectPCError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_SELECT_PC_ERROR_H__
#define __LC_SELECT_PC_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

enum SELECT_PC_ERROR
{
	SELECT_PC_ERROR_NULL,

	SELECT_PC_CANNOT_PLAY,			// 게임 할 수 없는 캐릭터(빌링 관련)
	SELECT_PC_NOT_BILLING_CHECK,	// 아직 결제 정보가 체크되지 않았다.
	SELECT_PC_CANNOT_PLAY_BY_ATTR,	// 능력치 문제로 더 이상 무료겜 못한다.
};

//////////////////////////////////////////////////////////////////////
//
// class LCSelectPCError;
//
// 플레이어가 선택한 PC 가 존재하지 않을 경우, 또는 이전에 로그아웃했던
// 존의 게임 서버가 다운되었을 경우, 또는 DB 서버가 다운되었을 경우,
// 이 패킷에 에러 이유를 담아서 클라이언트로 전송한다.
//
//////////////////////////////////////////////////////////////////////

class LCSelectPCError : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_SELECT_PC_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE; }
	
	// get packet's name
	string getPacketName() const throw() { return "LCSelectPCError"; }
	
	// get packet's debug string
	string toString() const throw();
	
	// get/set error message
	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private : 

	// 에러 메시지
	BYTE  m_Code;

};


//////////////////////////////////////////////////////////////////////
//
// class LCSelectPCErrorFactory;
//
// Factory for LCSelectPCError
//
//////////////////////////////////////////////////////////////////////

class LCSelectPCErrorFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCSelectPCError(); }

	// get packet name
	string getPacketName() const throw() { return "LCSelectPCError"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_SELECT_PC_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCSelectPCErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCSelectPCErrorHandler {

public:

	// execute packet's handler
	static void execute(LCSelectPCError* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
