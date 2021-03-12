//////////////////////////////////////////////////////////////////////////////
// Filename    : SharedServerClient.h 
// Written by  : reiot@ewestsoft.com
// Description : 게임 서버용 플레이어 클래스
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHARED_SERVER_CLIENT_H
#define __SHARED_SERVER_CLIENT_H

#include "Types.h"
#include "Exception.h"
#include "Player.h"
#include "Mutex.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
// class SharedServerClient
//
// 게임 서버용 쉐어드 서버 클라이언트 플레이어
//
//////////////////////////////////////////////////////////////////////////////

class SharedServerClient : public Player
{

public:
	// 저장해 놓을 이전 패킷의 개수
	const static BYTE nPacketHistorySize = 10;

public:
	SharedServerClient(Socket* pSocket) ;
	~SharedServerClient() ;

public:
	// read socket's receive buffer and fill input buffer
	// virtual void processInput() ;
	
	// parse packet and execute handler for the packet
	virtual void processCommand() ;
	
	// flush output buffer to socket's send buffer
	virtual void processOutput() ;
	
	// send packet to player's output buffer
	virtual void sendPacket(Packet* packet) ;

	// get debug string
	virtual string toString() const ;


private:

	// mutex
	mutable Mutex m_Mutex;
};

#endif
