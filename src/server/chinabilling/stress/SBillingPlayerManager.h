/////////////////////////////////////////////////////////////////////////////
//
// filename		: SBillingPlayerManager.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __SBILLING_PLAYER_MANAGER__
#define __SBILLING_PLAYER_MANAGER__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Socket.h"
#include "Mutex.h"
#include "CBillingInfo.h"
#include "PayUser.h"

class SBillingPlayer;

/////////////////////////////////////////////////////
// class SBillingPlayerManager
//
// 중국 빌링 서버와 통신을 전담하는 쓰레드
/////////////////////////////////////////////////////
class SBillingPlayerManager : public Thread
{
public:
	SBillingPlayerManager() throw ( Error );
	~SBillingPlayerManager() throw ( Error );

public:
	void init() throw ( Error ) {}
	void stop() throw ( Error );
	void run() throw ();

	// 빌링 관련 패킷 보내기 함수
	bool sendLogin( PayUser* pPayUser, int i ) throw ( ProtocolException, Error );
	void sendIntervalValidation( int i ) throw ( ProtocolException, Error );
	bool sendMinusPoint( PayUser* pPayUser, int i ) throw ( ProtocolException, Error );
	void sendMinusMinute( PayUser* pPayUser, int i ) throw ( ProtocolException, Error );
	void sendLogout( PayUser* pPayUser, int i ) throw ( ProtocolException, Error );

	int getVersionNumber() const throw();
	int getMinusIntervalInt() const throw ();
	string getMinusInterval() const throw ();

private:
	SBillingPlayer**	m_pSBillingPlayer;
	int					m_SBillingPlayers;
	mutable Mutex*		m_Mutex;
};

// global variable declaration
extern SBillingPlayerManager* g_pSBillingPlayerManager;

#endif

