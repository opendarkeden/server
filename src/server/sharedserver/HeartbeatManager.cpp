//////////////////////////////////////////////////////////////////////
//
// Filename    : HeartbeatManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 클라이언트 매니저
//
//////////////////////////////////////////////////////////////////////

#include "HeartbeatManager.h"
#include "Assert1.h"
#include <unistd.h>

HeartbeatManager::HeartbeatManager() throw(Error) {
    __BEGIN_TRY
    __END_CATCH
}


HeartbeatManager::~HeartbeatManager() throw(Error) {
    __BEGIN_TRY
    __END_CATCH
}


void HeartbeatManager::init() throw(Error) {
    __BEGIN_TRY
    __END_CATCH
}


void HeartbeatManager::start() throw(Error) {
    __BEGIN_TRY

    run();        // 바로 run() 메쏘드를 호출한다. ^^;

    __END_CATCH
}


void HeartbeatManager::stop() throw(Error) {
    __BEGIN_TRY

    throw UnsupportedError("[HeartbeatManager] Stopping manager is not supported.");

    __END_CATCH
}


void HeartbeatManager::run() throw(Error) {
    __BEGIN_TRY

    while (true) {
        // *TODO
        // 각종 HeartBeat들을 여기서 처리하면 된다.

        usleep(100);
    }

    __END_CATCH
}

HeartbeatManager * g_pHeartbeatManager = NULL;
