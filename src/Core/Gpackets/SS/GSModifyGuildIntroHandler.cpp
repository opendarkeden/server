//----------------------------------------------------------------------
//
// Filename    : GSModifyGuildIntroHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSModifyGuildIntro.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"

	#include "Spackets/SGModifyGuildIntroOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSModifyGuildIntroHandler::execute()
// 
//----------------------------------------------------------------------
void GSModifyGuildIntroHandler::execute ( GSModifyGuildIntro* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	if (pGuild==NULL) return;

	pGuild->saveIntro( pPacket->getGuildIntro() );

	// 게임 서버로 보낼 패킷을 만든다.
	SGModifyGuildIntroOK sgModifyGuildIntroOK;
	sgModifyGuildIntroOK.setGuildID( pGuild->getID() );
	sgModifyGuildIntroOK.setGuildIntro( pPacket->getGuildIntro() );

	// 게임 서버로 패킷을 보낸다.
	g_pGameServerManager->broadcast( &sgModifyGuildIntroOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
