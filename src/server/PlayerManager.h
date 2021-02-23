//--------------------------------------------------------------------------------
//
// Filename    : PlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//--------------------------------------------------------------------------------

#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "SocketAPI.h"
#include "Mutex.h"

// forward declaration
class Player;
class Packet;

//--------------------------------------------------------------------------------
//
// class PlayerManager;
//
// 플레이어를 관리하는 객체이다. 빠른 속도를 위해서 socket descriptor
// 를 인덱스로 하는 배열을 사용한다. 이 배열의 크기는 게임 서버에서 
// 처리할 수 있는 최대 플레이어의 숫자(소켓의 최대 숫자)이다.
// 비록 메모리 낭비가 있긴 하지만.. 감당할 수 있을 정도이다.
//
// 한 존그룹에 평균 100명의 플레이어가 있다면, 
//
// 		900 x 4(byte) x 10(#ZoneGroup) = 36k 
//
// 정도의 낭비가 있다.
//
//--------------------------------------------------------------------------------

class PlayerManager {

public :

	// 내부 플레이어 배열의 크기
	const static uint nMaxPlayers = 2000;

public :

	// constructor
	PlayerManager () throw ();

	// destructor
	virtual ~PlayerManager () throw ();

	// broadcast message
	virtual void broadcastPacket ( Packet * pPacket ) throw ( Error );

	// 특정 플레이어를 매니저에 추가한다.
	virtual void addPlayer ( Player * pPlayer ) throw ( DuplicatedException , Error );

	// 특정 플레이어를 매니저에서 삭제한다.
	virtual void deletePlayer ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );

	// 특정 플레이어 객체를 가져온다.
	virtual Player * getPlayer ( SOCKET fd ) throw ( OutOfBoundException , NoSuchElementException , Error );

	// 특정 폰을 가진 플레이어의 객체를 가져온다.
	virtual Player * getPlayerByPhoneNumber( PhoneNumber_t PhoneNumber ) throw( OutOfBoundException, NoSuchElementException, Error ) { return NULL; }

	// 현재 관리중인 플레이어 숫자를 리턴한다.
	uint size () const throw () { return m_nPlayers; }

	// Copy Player
	void copyPlayers() throw();

protected :

	// 플레이어의 포인터의 배열이다. 소켓 디스크립터를 인덱스로 사용한다.
	Player * m_pPlayers[nMaxPlayers];

	// number of Players
	uint m_nPlayers;

	// Player의 복사본을 저장하는 곳이다.
	Player * m_pCopyPlayers[nMaxPlayers];

};

#endif
