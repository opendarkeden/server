//----------------------------------------------------------------------
//
// Filename    : GSRequestGuildInfoHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSRequestGuildInfo.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerPlayer.h"
	#include "GameServerManager.h"
	#include "Properties.h"

	#include "Spackets/SGGuildInfo.h"

#endif

//----------------------------------------------------------------------
// 
// GSRequestGuildInfoHandler::execute()
// 
//----------------------------------------------------------------------
void GSRequestGuildInfoHandler::execute ( GSRequestGuildInfo* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	GameServerPlayer* pGSPlayer = dynamic_cast<GameServerPlayer*>(pPlayer);
	Assert( pGSPlayer != NULL );

	SGGuildInfo sgGuildInfo;

	g_pGuildManager->makeSGGuildInfo( sgGuildInfo );

	// 게임 서버로 패킷을 보낸다.
	pGSPlayer->sendPacket( &sgGuildInfo );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
