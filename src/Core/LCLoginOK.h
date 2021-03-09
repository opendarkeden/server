//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCLoginOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_LOGIN_OK_H__
#define __LC_LOGIN_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCLoginOK;
//
// 로그인서버가 클라이언트에게 로그인 성공을 알려주는 패킷이다.
//
//////////////////////////////////////////////////////////////////////

class LCLoginOK : public Packet {

public:

	LCLoginOK() : m_LastDays(0xffff) { }
    ~LCLoginOK() {};

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_LOGIN_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCLoginOKPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const  { return szBYTE + szBYTE + szBYTE + szWORD; }
	
	// get packet's name
	string getPacketName() const  { return "LCLoginOK"; }

	// get / set GoreLevel
	bool isAdult() const  { return m_isAdult; }
	void setAdult(bool isAdult)  { m_isAdult = isAdult; }

	bool isFamily() const  { return m_bFamily; }
	void setFamily(bool isFamily)  { m_bFamily = isFamily; }

	BYTE getStat() const  { return m_Stat; }
	void setStat(BYTE Stat)  { m_Stat = Stat; }

	WORD getLastDays() const  { return m_LastDays; }
	void setLastDays(WORD LastDays)  { m_LastDays = LastDays; }

	// get packet's debug string
	string toString() const  { return "LCLoginOK"; }

private :

	// 고어 레벨 : 현재 플레이어가 미성년자 인가?
	// true일 경우 성인
	// false 일 경우 미성년자
	bool m_isAdult;

	// Family 사용자인가
	bool m_bFamily;

	// 서버의 상태
	BYTE m_Stat;

	WORD m_LastDays;

};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginOKFactory;
//
// Factory for LCLoginOK
//
//////////////////////////////////////////////////////////////////////

class LCLoginOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCLoginOK(); }

	// get packet name
	string getPacketName() const  { return "LCLoginOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_LOGIN_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szBYTE + szBYTE + szWORD; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCLoginOKHandler {

public:

	// execute packet's handler
	static void execute(LCLoginOK* pPacket, Player* pPlayer) ;

};

#endif
