//--------------------------------------------------------------------------------
//
// Filename    : LGIncomingConnectionErrorHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "LGIncomingConnectionError.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "Assert.h"
	#include "LogDef.h"
#endif

//--------------------------------------------------------------------------------
// 
// LGIncomingConnectionErrorHander::execute()
// 
//--------------------------------------------------------------------------------
void LGIncomingConnectionErrorHandler::execute ( LGIncomingConnectionError * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 로그인 플레이어에 접근한다.
	//
	// *CAUTION*
	//
	// 이런 접근 방식은 문제가 있다. 로그인 플레이어 매니저가 이 플레이어를 처리하고 있을
	// 경우, 아래와 같이 접속을 종료해 버리면.. - -; 흐흠.. 이렇게 되면 setPlayerStatus()
	// 역시 락킹 버전으로 만들어야 하는가..  일단은 이렇게 하장.. (대충 입력이 없을 것이므로
	// 처리받지는 않는다..)
	//
	// 주의할 점은, 입력으로 리다이렉션하는 것이 불가능하다는 것이다. 왜냐하면, 리다이렉션
	// 시점에서 입력 버퍼에 패킷이 딱 끊겨서 들어왔다는 것을 알 수 없기 때문이다. 
	try 
	{
		GamePlayer * pGamePlayer = g_pIncomingPlayerManager->getPlayer( pPacket->getPlayerID() );
	
		Assert( pGamePlayer->getPlayerStatus() == GPS_AFTER_SENDING_GL_INCOMING_CONNECTION );

		// 이 플레이어의 로그인이 실패했으므로 접속을 종료한다.
		cout << "Fail to join game server...(" << pPacket->getPlayerID() << ")" << endl;

		int fd = -1;
		Socket* pSocket = pGamePlayer->getSocket();
		if (pSocket!=NULL) fd = (int)pSocket->getSOCKET();

		FILELOG_INCOMING_CONNECTION("incomingPenalty.log", "Error FD : %d, %s",
							fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()) );


		pGamePlayer->setPenaltyFlag( PENALTY_TYPE_KICKED );
		pGamePlayer->setItemRatioBonusPoint(2);
	} 
	catch ( NoSuchElementException & nsee ) 
	{
		cout << "Player not exist or already disconnected." << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
