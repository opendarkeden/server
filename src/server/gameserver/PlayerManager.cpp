//////////////////////////////////////////////////////////////////////
//
// Filename    : PlayerManager.cc
// Written by  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "PlayerManager.h"
#include "Assert.h"
#include "SocketAPI.h"
#include "Socket.h"
#include "Player.h"
#include "gameserver/Creature.h"
#include "gameserver/Slayer.h"
#include <algorithm>


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
PlayerManager::PlayerManager () 
	throw ()
: m_nPlayers(0)
{
	__BEGIN_TRY

	// 플레이어 포인터 배열을 NULL 로 초기화한다.
	for ( uint i = 0 ; i < nMaxPlayers ; i ++ )
		m_pPlayers[i] = NULL;

	// 플레이어 포인터 배열을 NULL 로 초기화한다.
	for ( uint i = 0 ; i < nMaxPlayers ; i ++ )
		m_pCopyPlayers[i] = NULL;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
PlayerManager::~PlayerManager () 
	throw ()
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < nMaxPlayers ; i ++ ) {

		if ( m_pPlayers[i] != NULL ) {
			// 플레이어 객체를 삭제하면, destructor에서 연결을 종료한다.
			delete m_pPlayers[i];
			m_pPlayers[i] = NULL;
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void PlayerManager::broadcastPacket ( Packet * pPacket )
	throw ( Error )
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < nMaxPlayers ; i ++ ) {
		if ( m_pPlayers[i] != NULL ) {
			try {
				m_pPlayers[i]->sendPacket(pPacket);
			} catch (Throwable& t) {
				filelog("playerManager.log", "broadcastPacket: %s", t.toString().c_str());
			}
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 특정 플레이어를 매니저에 추가한다.
//////////////////////////////////////////////////////////////////////
void PlayerManager::addPlayer ( Player * pPlayer ) 
	throw ( DuplicatedException , Error )
{
	__BEGIN_TRY

	SOCKET fd = pPlayer->getSocket()->getSOCKET();

	// bound check
	Assert( fd >= 0 && fd < (SOCKET)nMaxPlayers );

	// null check
	if ( m_pPlayers[ fd ] != NULL )
	{
		ofstream file("Socket_Error.txt", ios::out | ios::app);
		file << "socket descriptor duplicated" << endl;
		file.close();

		cout << "socket descriptor duplicated" << endl;
		throw DuplicatedException("socket descriptor duplicated");
	}

	// 괜찮으면 포인터를 대입한다.
	m_pPlayers[ fd ] = pPlayer;

	// 플레이어 숫자를 증가시킨다.
	m_nPlayers ++;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 특정 플레이어를 매니저에서 삭제한다.
// 객체는 삭제하지 않으며, 슬랏만을 NULL로 만든다.
//////////////////////////////////////////////////////////////////////
void PlayerManager::deletePlayer ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__BEGIN_TRY

	// bound check
	if ( fd < 0 || fd >= (SOCKET)nMaxPlayers )
		throw OutOfBoundException();

	// null check
	if ( m_pPlayers[ fd ] == NULL )
		throw NoSuchElementException();

	// 배열의 fd번째를 클리어한다.
	m_pPlayers[ fd ] = NULL;

	// 플레이어 숫자를 감소시킨다.
	m_nPlayers --;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 특정 플레이어 객체를 가져온다.
//////////////////////////////////////////////////////////////////////
Player * PlayerManager::getPlayer ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__BEGIN_TRY

	// bound check
	if ( fd < 0 || fd >= (SOCKET)nMaxPlayers )
		throw OutOfBoundException();

	// null check
	if ( m_pPlayers[ fd ] == NULL )
		throw NoSuchElementException();

	return m_pPlayers[ fd ];

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 플레이어를 복사한다.
//////////////////////////////////////////////////////////////////////
void PlayerManager::copyPlayers()
	throw()
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < nMaxPlayers ; i ++ ) {
		m_pCopyPlayers[i] = m_pPlayers[i];
	}

	__END_CATCH
}

