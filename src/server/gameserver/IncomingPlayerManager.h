//////////////////////////////////////////////////////////////////////////////
// Filename    : IncomingPlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INCOMING_PLAYER_MANAGER_H__
#define __INCOMING_PLAYER_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "PlayerManager.h"
#include "GamePlayer.h"
#include "ServerSocket.h"
#include "DatagramSocket.h"
#include "ConnectionInfoManager.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class IncomingPlayerManager;
//
// PlayerManager는 게임 서버에 접속한 전체 플레이어를 담당하며,
// ZonePlayerManager는 각 존그룹에 종속된 플레이어들을 담당하는 반면,
// IncomingPlayerManager는 게임 서버와 연결은 이루어졌으나 아직 크리처를
// 로딩하지 않은 임시적인 상태의 플레이어들을 관리한다.
//
// 새로운 접속을 인증한 후, 크리처를 로딩해서 플레이어와 연관시킨다.
// 크리처가 로딩되면 플레이어 및 크리처를 다른 존그룹으로 넘겨준다.
//////////////////////////////////////////////////////////////////////////////

class IncomingPlayerManager : public PlayerManager 
{
public:
	IncomingPlayerManager() ;
	~IncomingPlayerManager() ;

public:
	// initialize 
	void init() ;

	// broadcast packet to all players
	void broadcast(Packet* pPacket) ;

	// 다음의 메쏘드들은 ZoneThread에 의해서 호출된다.

	// select 
	void select() ;

	// process all players' inputs
	void processInputs() ;

	// process all players' outputs
	void processOutputs() ;

	// process all players' exceptions
	void processExceptions() ;
	
	// process all players' commands
	void processCommands() ;

	// accept new connection
	bool acceptNewConnection() ;

	void copyPlayers() ;

	// add/delete player
	void addPlayer(Player* pGamePlayer) ;
	void addPlayer_NOBLOCKED(Player* pGamePlayer) ;
	void deletePlayer(SOCKET fd) ;
	void deletePlayer_NOBLOCKED(SOCKET fd) ;

	// get Player by string
	GamePlayer* getPlayer_NOBLOCKED(const string & id) ;
	GamePlayer* getPlayer(const string & id) ;
	GamePlayer* getReadyPlayer(const string & id) ;

	// lock/unlock
	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }

    // push Player to queue
    void pushPlayer(GamePlayer* pGamePlayer) ;

    void pushOutPlayer(GamePlayer* pGamePlayer) ;

    // Queue's Player Add Manager
	void heartbeat() ;

    void deleteQueuePlayer(GamePlayer* pGamePlayer) ;

	// 모든 플레이어를 정리한다.
	void clearPlayers() ;

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

    list< GamePlayer* > m_PlayerListQueue;
	list< GamePlayer* > m_PlayerOutListQueue;

	int m_CheckValue;	// by sigi. for debugging. 2002.11.11

	mutable Mutex 	m_MutexOut;
};

// external variable declaration
extern IncomingPlayerManager* g_pIncomingPlayerManager;

#endif
