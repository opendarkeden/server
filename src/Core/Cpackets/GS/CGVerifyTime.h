//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGVerifyTime.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_VERIFY_TIME_H__
#define __CG_VERIFY_TIME_H__

// include files

//#ifdef __GAME_SERVER__
//#include "GamePlayer.h"
//#endif

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTime;
//
// 클라이언트가 서버에게 보내는 VerifyTime 패킷이다.
// 내부에 VerifyTime String 만을 데이타 필드로 가진다.
//
//////////////////////////////////////////////////////////////////////

class Player;
class GamePlayer;

class CGVerifyTime : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_CG_VERIFY_TIME; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return 0; }

	// get packet name
	string getPacketName () const throw () { return "CGVerifyTime"; }
	
	// get packet's debug string
	string toString () const throw ();

private :
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeFactory;
//
// Factory for CGVerifyTime
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new CGVerifyTime(); }

	// get packet name
	string getPacketName () const throw () { return "CGVerifyTime"; }
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CG_VERIFY_TIME; }

	// get packet's max body size
	// message 의 최대 크기에 대한 설정이 필요하다.
	PacketSize_t getPacketMaxSize () const throw () { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeHandler;
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeHandler {

public :

	// execute packet's handler
	static void execute ( CGVerifyTime * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

	// 스피드핵 사용자를 디비에 저장한다.
	static void saveSpeedHackPlayer( Player* pPlayer );

};

#endif
