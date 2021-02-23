//////////////////////////////////////////////////////////////////////
// 
// Filename    : CommonBillingPacket.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __COMMON_BILLING_PACKET_H__
#define __COMMON_BILLING_PACKET_H__

// include files
#include <stdio.h>
#include "Packet.h"
#include "PacketFactory.h"
#include "BillingInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class CommonBillingPacket;
//
// GameServer와 BillingServer가 주고 받는 packet이다.
//
//////////////////////////////////////////////////////////////////////

class Player;
class Creature;
class GamePlayer;

class CommonBillingPacket : public Packet, public BillingInfo {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_COMMON_BILLING; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBillingInfo; }

	// get packet name
	string getPacketName() const throw() { return "CommonBillingPacket"; }
	
	// get packet's debug string
	string toString() const throw();

    void test();

public :
	void	setPacket_Type(BillingPacketType bpt)	{ Packet_Type = bpt; }
	void	setResult(int result) 					{ Result = result; }
	void	setUser_CC() throw (Error);
	void	setSession(const string& session) 		{ memset(Session, 0, sizeof(Session)); memcpy(Session, session.c_str(), session.length()); }
	void	setUser_ID(const string& PlayerID) 		{ strcpy(User_ID, PlayerID.c_str()); }
	void	setUser_No(int uno) 					{ sprintf(User_No, "%d", uno); }
	void	setUser_IP(const string& IP) 			{ strcpy(User_IP, IP.c_str()); }
	void	setGame_No(int gameNo) 					{ Game_No = gameNo; }
	void	setUser_Status(const string& UserStatus){ strcpy(User_Status, UserStatus.c_str()); }
	void	setExpire_Date(const string& PlayerID) throw (Error);

	string	getExpire_DateToString() const;

private :
	// 256은 BillingInfo가 196이기 때문에 일단 이렇게 잡아둔거다
	char		m_pBuffer[256];
};


//////////////////////////////////////////////////////////////////////
//
// class CommonBillingPacketFactory;
//
// Factory for CommonBillingPacket
//
//////////////////////////////////////////////////////////////////////

class CommonBillingPacketFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CommonBillingPacket(); }

	// get packet name
	string getPacketName() const throw() { return "CommonBillingPacket"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_COMMON_BILLING; }

	// get packet's max body size
	// message 의 최대 크기에 대한 설정이 필요하다.
	PacketSize_t getPacketMaxSize() const throw() { return szBillingInfo; }

};


//////////////////////////////////////////////////////////////////////
//
// class CommonBillingPacketHandler;
//
//////////////////////////////////////////////////////////////////////

class CommonBillingPacketHandler {

public:

	// execute packet's handler
	static void execute(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);

private :
	static void executeBillingLoginVerify(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeBillingRemain(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeBillingCheck(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeBillingLoginCheckVerify(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void disconnectGamePlayer(GamePlayer* pGamePlayer, Turn_t delay) throw (Error);
	static void sendBillingRemainMessage(CommonBillingPacket* pPacket, GamePlayer* pGamePlayer) throw (Error);

};

#endif
