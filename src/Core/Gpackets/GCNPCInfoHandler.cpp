//----------------------------------------------------------------------
//
// Filename    : GCNPCInfoHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "GCNPCInfo.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "PCSlayerInfo2.h"
	#include "PCVampireInfo2.h"
	#include "Cpackets/CGReady.h"

#endif

//----------------------------------------------------------------------
// 클라이언트가 게임 서버로부터 GCNPCInfo 패킷을 받게 되면,
// 패킷 안의 데이터들을 클라이언트에 저장한 후, 데이터 로딩이
// 끝이 나면 게임 서버로 CGReady 패킷을 보내면 된다.
//----------------------------------------------------------------------
void GCNPCInfoHandler::execute ( GCNPCInfo * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

#endif

	__END_DEBUG_EX __END_CATCH
}
