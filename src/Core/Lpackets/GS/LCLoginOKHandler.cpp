//----------------------------------------------------------------------
//
// Filename    : LCLoginOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCLoginOK.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"

#endif

//----------------------------------------------------------------------
//
// 로그인 서버로부터 아이디와 패스워드의 인증을 받았다는 소리다.
//
// 이제 로그인 서버에게 PC 의 리스트를 요청하는 패킷을 전송하면 된다.
//
//----------------------------------------------------------------------
void LCLoginOKHandler::execute ( LCLoginOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	CLGetPCList clGetPCList;

	pClientPlayer->sendPacket( &clGetPCList );
	
	// 플레이어의 상태를 바꾼다.
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

#endif

	__END_DEBUG_EX __END_CATCH
}
