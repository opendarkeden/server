//////////////////////////////////////////////////////////////////////
//
// Filename    : GameServerManager.h
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_MANANGER_H__
#define __GAME_SERVER_MANANGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "DatagramSocket.h"

class Datagram;
class DatagramPacket;

//////////////////////////////////////////////////////////////////////
//
// class GameServerManager;
//
// 게임 서버와의 통신을 전담하는 쓰레드이다.
//
// 내부에 데이터그램 서버소켓을 하나 가지고 블로킹 기반으로 동작한다.
//
//////////////////////////////////////////////////////////////////////

class GameServerManager : public Thread {

public :

	// constructor
	GameServerManager () throw ( Error );

	// destructor
	~GameServerManager () throw ( Error );

	//
	void init () throw ( Error ) {}

	// stop thread
	void stop () throw ( Error );

	// main method
	void run () throw ();

	void sendDatagram ( Datagram * pDatagram ) throw ( ConnectException , Error );
	void sendPacket ( string host , uint port , DatagramPacket * pPacket ) throw ( ConnectException , Error );

private :

	// UDP 서버 소켓
	DatagramSocket * m_pDatagramSocket;

};

// global variable declaration
extern GameServerManager * g_pGameServerManager;

#endif
