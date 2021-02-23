//--------------------------------------------------------------------------------
//
// Filename    : GCReconnectLoginHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "GCReconnectLogin.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CGConnect.h"
#endif

//--------------------------------------------------------------------------------
// 로그인서버로부터 게임 서버의 주소와 포트, 그리고 인증키를 받은 즉시
// 게임 서버로 연결한 후, 인증키를 담은 CGConnect 패킷을 전송한다.
//--------------------------------------------------------------------------------
void GCReconnectLoginHandler::execute ( GCReconnectLogin * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
#ifdef __GAME_CLIENT__
#endif
	__END_DEBUG_EX __END_CATCH
}
