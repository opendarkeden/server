//--------------------------------------------------------------------------------
//
// Filename    : LGIncomingConnectionOKHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "LGIncomingConnectionOK.h"

#ifdef __GAME_SERVER__

	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "Assert.h"
	#include "Statement.h"
	#include "DatabaseManager.h"
	#include "LogDef.h"

	#include "Gpackets/GCReconnectLogin.h"

#endif

//--------------------------------------------------------------------------------
// 
// LGIncomingConnectionOKHander::execute()
// 
// 로그인 서버로부터 LGIncomingConnectionOK 패킷이 날아오면, 게임 서버는 이 허가가 
// 어느 플레이어에 대한 허가인지 찾아내야 한다. 그 후, 이 플레이어에게 LCReconnectLogin
// 패킷을 던져줘야 한다.
// 
//--------------------------------------------------------------------------------
void LGIncomingConnectionOKHandler::execute ( LGIncomingConnectionOK * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	try {	

		// 플레이어 아이디를 사용해서 플레이어 객체에 접근한다.
//		__ENTER_CRITICAL_SECTION((*g_pIncomingPlayerManager))
		GamePlayer * pGamePlayer = NULL;

		try {

			pGamePlayer = g_pIncomingPlayerManager->getPlayer( pPacket->getPlayerID() );

		} catch ( NoSuchElementException ) {

			pGamePlayer = g_pIncomingPlayerManager->getReadyPlayer( pPacket->getPlayerID() );

		} 

		int fd = -1;
		Socket* pSocket = pGamePlayer->getSocket();
		if (pSocket!=NULL) fd = (int)pSocket->getSOCKET();



		if ( pGamePlayer->getPlayerStatus() == GPS_AFTER_SENDING_GL_INCOMING_CONNECTION ) 
		{
			FILELOG_INCOMING_CONNECTION("incomingDisconnect.log", "OK FD : %d, %s",
							fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()) );

			/*
	        // 클라이언트에게 게임 서버로 재접속하라고 알려준다.
			GCReconnectLogin gcReconnectLogin;
			gcReconnectLogin.setLoginServerIP( pPacket->getHost() );
			gcReconnectLogin.setLoginServerPort( pPacket->getTCPPort() );
			gcReconnectLogin.setKey( pPacket->getKey() );

			// LCReconnectLogin 패킷을 전송한다.
			pGamePlayer->sendPacket( &gcReconnectLogin );

			cout << "LGIncomingConnectionOKHandler Send Packet to Client Required Reconnect ServerIP : " << pPacket->getHost() << endl;
			*/

			// 원래는 그냥 이 타이밍에 패킷을 보냈는데..
			// 타이밍 문제로 접속해제가 제대로 안됐는데 client에서 접속요청을 해오기 때문에
			// 짤려서..
			// GamePlayer에 저장해두고.. IncomingPlayerManager에서 disconnect()될때
			// 저장해둔 packet을 client로 보낸다.
			GCReconnectLogin* gcReconnectLogin = new GCReconnectLogin;
			gcReconnectLogin->setLoginServerIP( pPacket->getHost() );
			gcReconnectLogin->setLoginServerPort( pPacket->getTCPPort() );
			gcReconnectLogin->setKey( pPacket->getKey() );

			pGamePlayer->setReconnectPacket( gcReconnectLogin );

			//cout << "LGIncomingConnectionOKHandler Store Packet : " << gcReconnectLogin->toString().c_str() << endl;
			//cout << "LGIncomingConnectionOKHandler Store Packet" << endl;
		}
		else
		{
			FILELOG_INCOMING_CONNECTION("incomingDisconnect.log", "Invalid FD : %d, %s, ps=%d",
							fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()), 
							(int)pGamePlayer->getPlayerStatus());

			cout << "Invalid Player Status("
				<< (int)pGamePlayer->getPlayerStatus()
				<< ") must be AFTER_SENDING_LG_INCOMING_CONNECTION" << endl;
		}


		
		// 이렇게 해 두면, 
		// GamePlayer->processCommand()에서 isPenaltyFlag()체크에서 걸려서
		// 다음 턴의 IncomingPlayer->processCommands()에서 잘리게 된다.
		pGamePlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
		pGamePlayer->setItemRatioBonusPoint(3);

		// 연결을 종료한다.
		//pGamePlayer->disconnect( UNDISCONNECTED );

		// LPM에서 삭제한다.
		//g_pIncomingPlayerManager->deletePlayer_NOBLOCKED( pGamePlayer->getSocket()->getSOCKET());

		// GamePlayer 객체를 삭제한다.
		//SAFE_DELETE(pGamePlayer);

		//__LEAVE_CRITICAL_SECTION((*g_pIncomingPlayerManager))
	} 
	catch ( NoSuchElementException & nsee ) 
	{
		cout << "Player not exist or already disconnected" << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
