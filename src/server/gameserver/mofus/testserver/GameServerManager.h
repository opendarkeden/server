//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_MANAGER_H__
#define __GAME_SERVER_MANAGER_H__

#include "Thread.h"
#include "Types.h"
#include "Timeval.h"
#include "Exception.h"
#include "GameServerPlayer.h"
#include "ServerSocket.h"
#include "Mutex.h"


//////////////////////////////////////////////////////////////////////////////
//
// class GameServerManager;
//
//////////////////////////////////////////////////////////////////////////////

class GameServerManager : public Thread
{
public:
	GameServerManager() throw(Error);
	~GameServerManager() throw(Error);

public:

	// 쉐어드서버에서 받아들이는 최대 게임서버 수
	const static uint nMaxGameServers = 100;

	// initialize 
	void init() throw(Error);

	void run() throw (Error);

	// select 
	void select() throw(TimeoutException, InterruptedException, Error);

	// process all inputs
	void processInputs() throw(IOException, Error);

	// process all outputs
	void processOutputs() throw(IOException, Error);

	// process all exceptions
	void processExceptions() throw(IOException, Error);
	
	// process all commands
	void processCommands() throw(IOException, Error);

	// accept new connection
	void acceptNewConnection() throw(Error);

	// add/delete player
	void addGameServerPlayer(GameServerPlayer* pGameServerPlayer) throw(DuplicatedException, Error);
	void deleteGameServerPlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);

	// lock/unlock
	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }

	void heartbeat() throw(Error);

private:

	// TCP 서버 소켓과 소켓 디스크립터
	ServerSocket* m_pServerSocket;
	SOCKET m_SocketID;

	// 소속된 플레이어들의 소켓 디스크립터의 집합이다.
	// m_XXXXFDs[0]은 저장용이며, m_XXXFDs[1]이 실제로 select()의 파라미터로 사용된다.
	// 즉 select()하기 전에 [0] -> [1] 로 복사가 이루어져야 한다.
	fd_set m_ReadFDs[2];
	fd_set m_WriteFDs[2];
	fd_set m_ExceptFDs[2];

	// select에 사용되는 시간
	Timeval m_Timeout[2];

	// min_fd, max_fd
	// select()후 iterating 할 때 속도 증가를 위해서 사용한다.
	// 또한 select()의 첫번째 파라미터를 계산하기 위해서 사용한다.
	SOCKET m_MinFD;
	SOCKET m_MaxFD;

	// mutex
	mutable Mutex m_Mutex;


	// 게임서버의 포인터 배열. 소켓 디스크립터를 인덱스로 사용한다.
	GameServerPlayer* m_pGameServerPlayers[nMaxGameServers];

};

// external variable declaration
extern GameServerManager* g_pGameServerManager;

#endif
