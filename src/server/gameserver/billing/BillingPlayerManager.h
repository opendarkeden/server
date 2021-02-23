//////////////////////////////////////////////////////////////////////////////
// Filename    : BillingPlayerManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __BILLING_PLAYER_MANANGER_H__
#define __BILLING_PLAYER_MANANGER_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Socket.h"
#include "Packet.h"
#include "Mutex.h"
#include "BillingInfo.h"	// for #define __CONNECT_BILLING_SYSTEM__

class BillingPlayer;
class CommonBillingPacket;

//////////////////////////////////////////////////////////////////////////////
// class BillingPlayerManager;
//
// 쉐어드 서버와의 통신을 전담하는 쓰레드이다.
// 연결 끊기면 다시 연결해야 된다. 될 때까지~~
//////////////////////////////////////////////////////////////////////////////

class BillingPlayerManager : public Thread 
{
public:
	BillingPlayerManager() throw(Error);
	~BillingPlayerManager() throw(Error);

public:
	void init() throw(Error) {}

	void stop() throw(Error);

	void run() throw();

	void sendPacket( Packet* pPacket ) throw( ProtocolException, Error );

	// Pay Login/Logout
	void sendPayInit() throw( ProtocolException, Error );
	void sendPayCheck( CommonBillingPacket* pPacket ) throw( ProtocolException, Error );
	void sendPayLogin( Player* pPlayer ) throw( ProtocolException, Error );
	void sendPayLogout( Player* pPlayer ) throw( ProtocolException, Error );

	void setForceDisconnect( bool bForceDisconnect = true ) { m_bForceDisconnect = bForceDisconnect; }

private:

	BillingPlayer* m_pBillingPlayer;

	mutable Mutex	m_Mutex;

	bool m_bForceDisconnect;

};

// global variable declaration
extern BillingPlayerManager* g_pBillingPlayerManager;

#endif
