//--------------------------------------------------------------------------------
//
// Filename    : PlayerManager.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//--------------------------------------------------------------------------------

#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "SocketAPI.h"
#include "Mutex.h"

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
//         900 x 4(byte) x 10(#ZoneGroup) = 36k 
//
// 정도의 낭비가 있다.
//
//--------------------------------------------------------------------------------

class PlayerManager {
public:
    const static uint nMaxPlayers = 2000;

    PlayerManager() throw();
    virtual ~PlayerManager() throw();

    virtual void broadcastPacket(Packet * pPacket) throw(Error);

    virtual void addPlayer(Player * pPlayer) throw(DuplicatedException, Error);

    virtual void deletePlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);

    virtual Player * getPlayer(SOCKET fd) throw(OutOfBoundException, NoSuchElementException, Error);

    virtual Player * getPlayerByPhoneNumber(PhoneNumber_t PhoneNumber ) throw(OutOfBoundException, NoSuchElementException, Error) { return NULL; }

    uint size() const throw() { return m_nPlayers; }

    void copyPlayers() throw();

protected:
    Player * m_pPlayers[nMaxPlayers];
    uint m_nPlayers;
    Player * m_pCopyPlayers[nMaxPlayers];
};

#endif
