//////////////////////////////////////////////////////////////////////
//
// Filename    : ClientManager.h
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 클라이언트 매니저
//
//////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_CLIENT_MANAGER_H__
#define __LOGIN_CLIENT_MANAGER_H__

#include "Types.h"
#include "Exception.h"

class ClientManager {
public:
    ClientManager() throw(Error);
    ~ClientManager() throw(Error);

    void init() throw(Error);
    void start() throw(Error);
    void stop() throw(Error);
    void run() throw(Error);
};

extern ClientManager * g_pClientManager;
#endif
