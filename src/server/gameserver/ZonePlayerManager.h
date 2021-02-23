//////////////////////////////////////////////////////////////////////
//
// Filename    : ZonePlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZONE_PLAYER_MANAGER_H__
#define __ZONE_PLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Socket.h"
#include "Mutex.h"
#include "Effect.h"

class GamePlayer;
class BroadcastFilter;

//////////////////////////////////////////////////////////////////////
//
// class ZonePlayerManager;
//
// 현재 ZoneGroup에 소속된 플레이어를 관리하는 매니저 객체이다.
//
//////////////////////////////////////////////////////////////////////

class ZonePlayerManager : public PlayerManager {
public:
	typedef pair<BroadcastFilter*,SocketOutputStream*> PairFilterStream;

public:

	// constructor
	ZonePlayerManager() throw();

	// destructor
	~ZonePlayerManager() throw();

	// select 
	void select() throw(TimeoutException, InterruptedException, Error);

	// process all players' inputs
	void processInputs() throw(IOException, Error);

	// process all players' outputs
	void processOutputs() throw(IOException, Error);

	// process all players' exceptions
	void processExceptions() throw(IOException, Error);
	
	// process all players' commands
	void processCommands() throw(IOException, Error);

	// broadcast packet
	void broadcastPacket(Packet* pPacket) throw(Error);
	void broadcastPacket_NOBLOCKED(Packet* pPacket) throw(Error);
	void pushBroadcastPacket(Packet* pPacket, BroadcastFilter* pFilter=NULL) throw(Error);
	void flushBroadcastPacket() throw(Error);
	
	// add player to zone player manager
	void addPlayer(GamePlayer* pGamePlayer) throw(DuplicatedException, Error);
	void addPlayer_NOBLOCKED(GamePlayer* pGamePlayer) throw(DuplicatedException, Error);

	// delete player from zone player manager
	void deletePlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);
	void deletePlayer_NOBLOCKED(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);
	void deletePlayer(Player* pPlayer) throw(OutOfBoundException, NoSuchElementException, Error)
	{
		deletePlayer(pPlayer->getSocket()->getSOCKET());
	}

	// get player
	Player* getPlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error) ;

	// get Player by PhoneNumber
	Player* getPlayerByPhoneNumber(PhoneNumber_t PhoneNumber) throw(OutOfBoundException, NoSuchElementException, Error);

	// All Member Save
	void save() throw(Error);

	void copyPlayers() throw();

    // push Player to queue
    void pushPlayer(GamePlayer* pGamePlayer) throw(Error);
    void pushOutPlayer(GamePlayer* pGamePlayer) throw(Error);
	void processPlayerListQueue() throw (Error);

	// Queue's Player Add Manager
    void heartbeat() throw(Error);

	// delete Queue Player
	void deleteQueuePlayer(GamePlayer* pGamePlayer) throw(NoSuchElementException, Error);

	void    removeFlag (Effect::EffectClass EC) throw(Error);

	void lock() throw (Error) { m_Mutex.lock(); }	
	void unlock() throw (Error) { m_Mutex.unlock(); }	

	// 모든 플레이어를 정리한다.
	void clearPlayers() throw (Error);

	void setZGID( ZoneGroupID_t id ) { m_ZGID = id; }
	ZoneGroupID_t getZGID() const { return m_ZGID; }

#if defined(__THAILAND_SERVER__) 
	// add by inthesky for THAILAND ChildGuard rule
	bool onChildGuardTimeArea(int pm, int am, bool bSwitch);
#endif

private:

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
	mutable Mutex m_Mutex2;
	mutable Mutex m_MutexBroadcast;

	list< GamePlayer* > m_PlayerListQueue;
	list< GamePlayer* > m_PlayerOutListQueue;
	list< PairFilterStream > m_BroadcastQueue;

	ZoneGroupID_t m_ZGID;

#if defined(__THAILAND_SERVER__) 
	//add by inthesky for THAILAND ChildGuard Rule
	bool    m_bChildGuard;
	int     m_nChildGuardStartTime;
	int     m_nChildGuardEndTime;
	int     m_nChildGuardKickTime;
	int     m_nChildGuardCheckTerm;
	Timeval m_tmChildGuardCheckTerm;
#endif
};

// external variable declaration
extern ZonePlayerManager* g_pZonePlayerManager;

#endif
