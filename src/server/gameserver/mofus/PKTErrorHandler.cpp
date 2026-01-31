/////////////////////////////////////////////////////////////////////////////
// Filename : PKTErrorHandler.cpp
// Desc		:
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTErrorHandler.h"

#include "Assert.h"
#include "MJob.h"
#include "MPlayer.h"
#include "Mofus.h"
#include "PKTError.h"


// 실행 함수
void PKTErrorHandler::execute(MPlayer* pPlayer, MPacket* pPacket) {
    PKTError* pError = dynamic_cast<PKTError*>(pPacket);
    Assert(pError != NULL);

    cout << "--------------------------------------------------" << endl;
    cout << "RECV [" << pPlayer->getJob()->getName() << "] Error : " << pError->nError << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "RECV [%s] Error : %d", pPlayer->getJob()->getName().c_str(), pError->nError);
    filelog(MOFUS_PACKET_FILE, "RECV : [%s] %s", pPlayer->getJob()->getName().c_str(), pPacket->toString().c_str());

    // 에러 코드를 세팅
    pPlayer->setErrorCode(pError->getErrorCode());

    // 로그아웃 보내기
    pPlayer->sendLogout();

    // 작업 끝
    pPlayer->setEnd();
}
