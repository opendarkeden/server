//////////////////////////////////////////////////////////////////////
//
// Filename    : LCLoginErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "LCLoginError.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLLogin.h"
#endif
	
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void LCLoginErrorHandler::execute ( LCLoginError * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	cout << "+------------------------+" << endl
		 << "| Invalid ID or Password |" << endl
		 << "+------------------------+" << endl
		 << endl;

	CLLogin clLogin;
	char cmd[80];

	cout << endl
		 << "+----------+" << endl
		 << "| RE-LOGIN |" << endl
		 << "+----------+" << endl
		 << endl;

	cout << "I    D : ";
	cin.getline(cmd,80);
	clLogin.setID(cmd);

	cout << "Passwd : ";
	cin.getline(cmd,80);
	clLogin.setPassword(cmd);

	pClientPlayer->sendPacket( &clLogin );
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_LOGIN );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
