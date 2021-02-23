//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestGuildMemberListHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestGuildMemberList.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Gpackets/GCGuildMemberList.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "Player.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Guild.h"
	#include "GuildMemberInfo.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestGuildMemberListHandler::execute (CGRequestGuildMemberList* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>( pGamePlayer->getCreature() );
	Assert( pPlayerCreature != NULL );

	// 선택한 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPlayerCreature->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL)
		return;

	GCGuildMemberList gcGuildMemberList;

	pGuild->makeMemberInfo( gcGuildMemberList );
	
	pPlayer->sendPacket( &gcGuildMemberList );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

