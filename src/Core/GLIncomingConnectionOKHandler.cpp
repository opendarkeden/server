//--------------------------------------------------------------------------------
//
// Filename    : GLIncomingConnectionOKHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GLIncomingConnectionOK.h"

#ifdef __LOGIN_SERVER__

	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
	#include "Assert1.h"

	#include "LCReconnect.h"

#endif

//--------------------------------------------------------------------------------
// 
// GLIncomingConnectionOKHander::execute()
// 
// ���� �����κ��� GLIncomingConnectionOK ��Ŷ�� ���ƿ���, �α��� ������ �� �㰡�� 
// ��� �÷��̾ ���� �㰡���� ã�Ƴ��� �Ѵ�. �� ��, �� �÷��̾�� LCReconnect
// ��Ŷ�� ������� �Ѵ�.
// 
//--------------------------------------------------------------------------------
void GLIncomingConnectionOKHandler::execute (GLIncomingConnectionOK * pPacket )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	try {	

		// �÷��̾� ���̵� ����ؼ� �÷��̾� ��ü�� �����Ѵ�.
		__ENTER_CRITICAL_SECTION((*g_pLoginPlayerManager))

		LoginPlayer * pLoginPlayer = g_pLoginPlayerManager->getPlayer_NOLOCKED(pPacket->getPlayerID());

		if (pLoginPlayer->getPlayerStatus() == LPS_AFTER_SENDING_LG_INCOMING_CONNECTION ) 
		{


		  // Tell the client to reconnect the game server.
		  // by tiancaiamao: when gameserver is behind docker, it may have a docker internal IP 172.20.0.1 and a outside IP in database GameServerInfo table.
		  // The outside IP should be used.
		  // pPacket->getHost() get the internal one.
		  // pLoginPlayer->getGameServerIP() get the outside one.

			LCReconnect lcReconnect;
			// lcReconnect.setGameServerIP(pPacket->getHost());
			lcReconnect.setGameServerIP(pLoginPlayer->getGameServerIP());
			lcReconnect.setGameServerPort(pPacket->getTCPPort());
			lcReconnect.setKey(pPacket->getKey());

			// LCReconnect ��Ŷ�� �����Ѵ�.
			pLoginPlayer->sendPacket(&lcReconnect);

			//cout << "GLIncomingConnectionOKHandler Send to Client Required Reconnect ServerIP : " << pPacket->getHost() << endl;
		}
		else
		{
			//cout << "Invalid Player Status.. must be AFTER_SENDING_LG_INCOMING_CONNECTION" << endl;
		}

		// ������ �����Ѵ�.
		//pLoginPlayer->disconnect(UNDISCONNECTED);
		pLoginPlayer->disconnect_nolog(UNDISCONNECTED);

		// LPM���� �����Ѵ�.
		g_pLoginPlayerManager->deletePlayer_NOLOCKED(pLoginPlayer->getSocket()->getSOCKET());

		// LoginPlayer ��ü�� �����Ѵ�.
		SAFE_DELETE(pLoginPlayer);

		__LEAVE_CRITICAL_SECTION((*g_pLoginPlayerManager))


	} catch (NoSuchElementException & nsee ) {
		//cout << "Player not exist or already disconnected" << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
