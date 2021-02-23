/////////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayerManager.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PLAYER_MANAGER__
#define __CBILLING_PLAYER_MANAGER__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Socket.h"
#include "Mutex.h"
#include "CBillingInfo.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
#elif defined(__GAME_SERVER__)
	#include "GamePlayer.h"
#endif

class CBillingPlayer;

/////////////////////////////////////////////////////
// class CBillingPlayerManager
//
// 중국 빌링 서버와 통신을 전담하는 쓰레드
/////////////////////////////////////////////////////
class CBillingPlayerManager : public Thread
{
public:
	CBillingPlayerManager() throw ( Error );
	~CBillingPlayerManager() throw ( Error );

public:
	void init() throw ( Error ) {}
	void stop() throw ( Error );
	void run() throw ();

	// 빌링 관련 패킷 보내기 함수
#ifdef __LOGIN_SERVER__
	void sendLogin( LoginPlayer* pLoginPlayer ) throw ( ProtocolException, Error );
#elif defined(__GAME_SERVER__)
	bool sendLogin( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
	void sendIntervalValidation() throw ( ProtocolException, Error );
	bool sendMinusPoint( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
	void sendMinusMinute( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
	void sendLogout( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
#endif

	void setForceDisconnect( bool bForceDisconnect = true ) { m_bForceDisconnect = bForceDisconnect; }

	int getVersionNumber() const throw();
	int getMinusIntervalInt() const throw ();
	string getMinusInterval() const throw ();

private:
	CBillingPlayer*		m_pCBillingPlayer;
	mutable Mutex		m_Mutex;
	mutable Mutex		m_SendMutex;
	bool				m_bForceDisconnect;
};

// global variable declaration
extern CBillingPlayerManager* g_pCBillingPlayerManager;

#endif

