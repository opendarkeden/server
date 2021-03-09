//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCRegisterPlayerOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_REGISTER_PLAYER_OK_H__
#define __LC_REGISTER_PLAYER_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOK;
//
// 로그인서버가 클라이언트에게 로그인 성공을 알려주는 패킷이다.
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOK : public Packet {

public:
    LCRegisterPlayerOK() {};
    ~LCRegisterPlayerOK() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_REGISTER_PLAYER_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCRegisterPlayerOKPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const  { return szBYTE + m_GroupName.size() + szBYTE; }
	
	// get packet's name
	string getPacketName() const  { return "LCRegisterPlayerOK"; }

    // get / set Groupname
	string getGroupName() const  { return m_GroupName; }
	void setGroupName(const string & GroupName)  { m_GroupName = GroupName; }
	
	// get / set GoreLevel
	bool isAdult() const  { return m_isAdult; }
	void setAdult(bool isAdult)  { m_isAdult = isAdult; }
	
	
	// get packet's debug string
	string toString() const  { return "LCRegisterPlayerOK"; }

private :
	// 서버 그룹 이름.
	string m_GroupName;
	
	// 고어 레벨 : 현재 플레이어가 미성년자 인가?
	// true일 경우 성인
	// false 일 경우 미성년자
	bool m_isAdult;
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOKFactory;
//
// Factory for LCRegisterPlayerOK
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCRegisterPlayerOK(); }

	// get packet name
	string getPacketName() const  { return "LCRegisterPlayerOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_REGISTER_PLAYER_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  { return szBYTE + 20 + szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOKHandler {

public:

	// execute packet's handler
	static void execute(LCRegisterPlayerOK* pPacket, Player* pPlayer) ;

};

#endif
