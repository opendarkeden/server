//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginPlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 로그인 플레이어 매니저
//
//////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_PLAYER_MANAGER_H__
#define __LOGIN_PLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PlayerManager.h"
#include "ServerSocket.h"

class LoginPlayer;

//////////////////////////////////////////////////////////////////////
//
// class LoginPlayerManager;
//
// 로그인 서버에 접속한 모든 플레이어들을 관리한다.
//
//////////////////////////////////////////////////////////////////////

class LoginPlayerManager : public PlayerManager {

public :

	// constructor
	LoginPlayerManager () throw ( Error );

	// destructor
	~LoginPlayerManager () throw ( Error );

public :

	// 클라이언트 매니저를 초기화한다.
	void init () throw ( Error );

	// accept new connection
	void acceptNewConnection () throw ( Error );

	// select() 시스템콜을 사용해서 I/O Multiplexing을 한다.
	void select () throw ( Error );

	// 접속한 모든 사용자의 입력을 입력 버퍼로 복사한다.
	void processInputs () throw ( Error );

	// 접속한 모든 사용자의 출력을 클라이언트로 전송한다.
	void processOutputs () throw ( Error );

	// 접속한 모든 사용자의 패킷을 처리한다.
	void processCommands () throw ( Error );

	// OOB 데이타를 처리한다. ^^;
	void processExceptions () throw ( Error );

public :

	// 로그인 서버에 접속한 모든 플레이어들에게 특정 패킷을 전달한다.
	void broadcastPacket ( Packet * pPacket ) throw ( Error );

	// 특정 아이디의 플레이어에게 특정 패킷을 전달한다.
	void sendPacket ( const string & id , Packet * pPacket ) throw ( Error );

	// 플레이어 객체를 추가한다.
	void addPlayer ( Player * pPlayer ) throw ( DuplicatedException , Error );
	void addPlayer_NOLOCKED ( Player * pPlayer ) throw ( DuplicatedException , Error );

	// 플레이어 객체를 삭제한다.
	void deletePlayer ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );
	void deletePlayer_NOLOCKED ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );

	// 플레이어 객체에 접근한다.
	LoginPlayer * getPlayer ( const string & PCName ) const throw ( NoSuchElementException , Error );
	LoginPlayer * getPlayer_NOLOCKED ( const string & PCName ) const throw ( NoSuchElementException , Error );

	// lock/unlock
	void lock () throw ( Error ) { m_Mutex.lock(); }
	void unlock () throw ( Error ) { m_Mutex.unlock(); }

	// get debug string
	string toString () const throw ();

private :

	// 서버 소켓
	ServerSocket * m_pServerSocket;

	// 서버 소켓 디스크립터 ( for fast reference )
	SOCKET m_ServerFD;

	// 소속된 플레이어들의 소켓 디스크립터의 집합이다.
	// m_XXXXFDs[0]은 저장용이며, m_XXXFDs[1]이 실제로 select()의 파라미터로 사용된다.
	// 즉 select()하기 전에 [0] -> [1] 로 복사가 이루어져야 한다.
	fd_set m_ReadFDs[2];
	fd_set m_WriteFDs[2];
	fd_set m_ExceptFDs[2];

	// select에 사용되는 시간
	Timeval m_Timeout[2];

	// min_fd , max_fd
	// select()후 iterating 할 때 속도 증가를 위해서 사용한다.
	// 또한 select()의 첫번째 파라미터를 계산하기 위해서 사용한다.
	SOCKET m_MinFD;
	SOCKET m_MaxFD;

	// 로그인 서버의 메인 루프는 단일 쓰레드로 구현된다.
	// 따라서, mutex 를 사용하지 않아도 될 것처럼 보이지만.. 
	// 게임서버로부터 데이터그램을 받아서 처리하는 루틴은 
	// 독립적인 쓰레드로 구현된다. 즉, 이 쓰레드가 LPM의
	// 플레이어 배열을 manipulate할 때 경쟁조건이 발생할
	// 가능성이 높다. - -;
	mutable Mutex m_Mutex;

};

// external variable declaration
extern LoginPlayerManager * g_pLoginPlayerManager;

#endif
