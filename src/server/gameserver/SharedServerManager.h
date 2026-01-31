//////////////////////////////////////////////////////////////////////////////
// Filename    : SharedServerManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHARED_SERVER_MANANGER_H__
#define __SHARED_SERVER_MANANGER_H__

#include "Exception.h"
#include "Mutex.h"
#include "Packet.h"
#include "Socket.h"
#include "Thread.h"
#include "Types.h"

class SharedServerClient;

//////////////////////////////////////////////////////////////////////////////
// class SharedServerManager;
//
// 쉐어드 서버와의 통신을 전담하는 쓰레드이다.
// 연결 끊기면 다시 연결해야 된다. 될 때까지~~
//////////////////////////////////////////////////////////////////////////////

class SharedServerManager : public Thread {
public:
    SharedServerManager();
    ~SharedServerManager();

public:
    void init() {}

    void stop();

    void run();

    void sendPacket(Packet* pPacket);

private:
    SharedServerClient* m_pSharedServerClient;

    mutable Mutex m_Mutex;
};

// global variable declaration
extern SharedServerManager* g_pSharedServerManager;

#endif
