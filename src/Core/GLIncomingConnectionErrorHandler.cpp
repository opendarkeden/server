//--------------------------------------------------------------------------------
//
// Filename    : GLIncomingConnectionErrorHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GLIncomingConnectionError.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
	#include "Assert1.h"
#endif

//--------------------------------------------------------------------------------
// 
// GLIncomingConnectionErrorHander::execute()
// 
//--------------------------------------------------------------------------------
void GLIncomingConnectionErrorHandler::execute (GLIncomingConnectionError * pPacket )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	// Handle login player connection failure.
	//
	// *CAUTION*
	//
	// Rare case: the login player may disappear before being processed because the
	// login server is heavily loaded. In that situation setPlayerStatus() could be
	// called on an invalid player. This should not happen under normal conditions
	// since the incoming connection is not a user-triggered input.
	//
	// In short, this indicates the login server could not accept the incoming
	// request. The most likely reason is a timeout while reading the handshake.
	try 
	{
		LoginPlayer * pLoginPlayer = g_pLoginPlayerManager->getPlayer(pPacket->getPlayerID());
	
		Assert(pLoginPlayer->getPlayerStatus() == LPS_AFTER_SENDING_LG_INCOMING_CONNECTION);

		// �� �÷��̾��� �α����� ���������Ƿ� ������ �����Ѵ�.
		//cout << "Fail to join game server...(" << pPacket->getPlayerID() << ")" << endl;

		// ������ �����Ѵ�.
		pLoginPlayer->disconnect(UNDISCONNECTED);

		// LPM���� �����Ѵ�.
		g_pLoginPlayerManager->deletePlayer(pLoginPlayer->getSocket()->getSOCKET());

		// LoginPlayer ��ü�� �����Ѵ�.
		SAFE_DELETE(pLoginPlayer);
	} 
	catch (NoSuchElementException & nsee ) 
	{
		//cout << "Player not exist or already disconnected." << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
