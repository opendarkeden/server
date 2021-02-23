//----------------------------------------------------------------------
//
// Filename    : GCUpdateInfoHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "GCUpdateInfo.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "PCSlayerInfo2.h"
	#include "PCVampireInfo2.h"
	#include "Cpackets/CGReady.h"

#endif

//----------------------------------------------------------------------
// 클라이언트가 게임 서버로부터 GCUpdateInfo 패킷을 받게 되면,
// 패킷 안의 데이터들을 클라이언트에 저장한 후, 데이터 로딩이
// 끝이 나면 게임 서버로 CGReady 패킷을 보내면 된다.
//----------------------------------------------------------------------
void GCUpdateInfoHandler::execute ( GCUpdateInfo * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	//cout << pPacket->toString() << endl;

	//--------------------------------------------------
	// 데이터 로딩을 시작한다.
	//--------------------------------------------------
	pClientPlayer->setPlayerStatus( CPS_WAITING_FOR_LOADING );

		// ... 로딩 로딩 ... 

	//--------------------------------------------------
	// 게임 서버로 CGReady 패킷을 보낸다.
	//--------------------------------------------------
	CGReady cgReady;
	pClientPlayer->sendPacket( &cgReady );
	pClientPlayer->setPlayerStatus( CPS_WAITING_FOR_GC_SET_POSITION );

#endif

	__END_DEBUG_EX __END_CATCH
}
