//----------------------------------------------------------------------
//
// Filename    : LCCreatePCOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCCreatePCOK.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"
#endif

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
void LCCreatePCOKHandler::execute ( LCCreatePCOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	cout << "                            " << endl;
	cout << "+--------------------------+" << endl;
	cout << "| PC created successfully! |" << endl;
	cout << "+--------------------------+" << endl;
	cout << "                            " << endl;

	// 다시 PC LIST 를 받아와야 한다.
	CLGetPCList clGetPCList;
	pClientPlayer->sendPacket( &clGetPCList );

	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );
	
#endif

	__END_DEBUG_EX __END_CATCH
}
