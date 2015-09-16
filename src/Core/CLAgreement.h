//--------------------------------------------------------------------------------
// 
// Filename    : CLAgreement.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_AGREEMENT_H__
#define __CL_AGREEMENT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLAgreement;
//
// 클라이언트가 로그인 서버에게 최초에 전송하는 패킷이다.
// 아이디와 패스워드가 암호화되어 있다.
//
//--------------------------------------------------------------------------------

class CLAgreement : public Packet {

public:
	CLAgreement() {};
    virtual ~CLAgreement() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_AGREEMENT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "CLAgreement"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set agreement 넷마블 사용자 약관 동의 여부
	bool isAgree() const { return (m_Agree ? true : false); }
	void setAgree(bool agree ) { m_Agree = agree; }

private :

	// 넷마블 사용자 약관 동의 여부
	BYTE m_Agree;
};


//--------------------------------------------------------------------------------
//
// class CLAgreementFactory;
//
// Factory for CLAgreement
//
//--------------------------------------------------------------------------------

class CLAgreementFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLAgreement(); }

	// get packet name
	string getPacketName() const throw() { return "CLAgreement"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_AGREEMENT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class CLAgreementHandler;
//
//--------------------------------------------------------------------------------

class CLAgreementHandler {

public:

	// execute packet's handler
	static void execute(CLAgreement* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
