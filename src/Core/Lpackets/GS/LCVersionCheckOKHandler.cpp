//----------------------------------------------------------------------
//
// Filename    : LCVersionCheckOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCVersionCheckOK.h"

//----------------------------------------------------------------------
//
// 로그인 서버로부터 아이디와 패스워드의 인증을 받았다는 소리다.
//
// 이제 로그인 서버에게 PC 의 리스트를 요청하는 패킷을 전송하면 된다.
//
//----------------------------------------------------------------------
void LCVersionCheckOKHandler::execute ( LCVersionCheckOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__END_DEBUG_EX __END_CATCH
}
