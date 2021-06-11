//--------------------------------------------------------------------------------
//
// Filename    : UCUpdateListHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "UCUpdateList.h"

#ifdef __UPDATE_CLIENT__
	#include <stdio.h>
	#include "Properties.h"
	#include "Upackets/CURequest.h"
	#include "Upackets/CUEndUpdate.h"
#endif

//--------------------------------------------------------------------------------
//
// (1) 업데이트 매니저를 플레이어 객체에 저장한다.
// (2) 리소스 매니저를 업데이트 매니저에서 가져온다.
// (3) 리소스를 리소스 매니저에서 가져온다.
// (4) 리소스가 존재하면, 서버로 요청한다.
// (5) 리소스가 존재하지 않으면 연결을 종료한다.
//
//--------------------------------------------------------------------------------
void UCUpdateListHandler::execute ( UCUpdateList * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}
