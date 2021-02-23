//--------------------------------------------------------------------------------
//
// Filename    : LCReconnectHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "LCReconnect.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CGConnect.h"
#endif

//--------------------------------------------------------------------------------
// 로그인서버로부터 게임 서버의 주소와 포트, 그리고 인증키를 받은 즉시
// 게임 서버로 연결한 후, 인증키를 담은 CGConnect 패킷을 전송한다.
//--------------------------------------------------------------------------------
void LCReconnectHandler::execute ( LCReconnect * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	// 로그인 서버와의 연결을 종료한다
	// 이때 로그인 서버는 LCReconnect 패킷을 보내면서 연결을 종료한다는 사실에 유의하라.
	cout << "Disconnecting from login server" << endl;
	pClientPlayer->disconnect();

	// LCReconnect 패킷에 들어있는 정보를 사용해서, 게임 서버로 연결한다.
	cout << "Reconnecting to " << pPacket->getGameServerIP() << ":" << pPacket->getGameServerPort() << endl;

	try {

		pClientPlayer->getSocket()->reconnect( pPacket->getGameServerIP() , pPacket->getGameServerPort() );

		// reconnect하게 되면 소켓이 새로 만들어지게 된다.
		// 따라서, 이 소켓 역시 옵션을 새로 지정해줘야 한다.
		pClientPlayer->getSocket()->setNonBlocking();
		pClientPlayer->getSocket()->setLinger(0);

	} catch ( ConnectException & ce ) {
		throw Error(ce.toString());
	}

	// 연결이 이루어지면, 바로 CGConnect 패킷을 전송한다.
	// 이전에 Select 한 PC의 타입과 이름을 클라이언트 플레이어 객체에 저장해둔다.
	cout << "Sending CGConnect with Key(" << pPacket->getKey() << ")" << endl;

	CGConnect cgConnect;
	cgConnect.setKey( pPacket->getKey() );
	cgConnect.setPCType( pClientPlayer->getPCType() );
	cgConnect.setPCName( pClientPlayer->getPCName() );

	pClientPlayer->sendPacket( &cgConnect );
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CG_CONNECT );

#endif

	__END_DEBUG_EX __END_CATCH
}
