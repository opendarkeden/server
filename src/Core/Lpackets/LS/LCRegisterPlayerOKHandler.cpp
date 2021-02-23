//--------------------------------------------------------------------------------
//
// Filename    : LCRegisterPlayerOKHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "LCRegisterPlayerOK.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"
#endif


//--------------------------------------------------------------------------------
//
// 플레이어 등록이 성공적으로 끝났으면, 로그인 서버에게 PC LIST 를 요청한다.
//
//--------------------------------------------------------------------------------
void LCRegisterPlayerOKHandler::execute ( LCRegisterPlayerOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	cout << "Player Registeration Successfull." << endl;

	CLGetPCList clGetPCList;

	pClientPlayer->sendPacket( &clGetPCList );

	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

#endif

	__END_DEBUG_EX __END_CATCH
}
