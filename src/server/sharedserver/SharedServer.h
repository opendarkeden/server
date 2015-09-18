//////////////////////////////////////////////////////////////////////
// 
// Filename    : SharedServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SHARED_SERVER_H__
#define __SHARED_SERVER_H__

#ifndef __SHARED_SERVER__
#define __SHARED_SERVER__
#endif

#include "Types.h"
#include "Exception.h"

class SharedServer {
public:
    SharedServer() throw(Error);
    ~SharedServer() throw(Error);

    void init() throw(Error);
    void start() throw(Error);
    void stop() throw(Error);
};

extern SharedServer * g_pSharedServer;
#endif
