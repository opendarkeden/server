//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyGuildMemberIntroHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyGuildMemberIntro.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGModifyGuildMemberIntroHandler::execute (CGModifyGuildMemberIntro* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPlayerCreature != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPlayerCreature->getGuildID() );
	if (pGuild==NULL) return;

	// 길드 멤버 정보를 가져온다.
	GuildMember* pGuildMember  = pGuild->getMember( pPlayerCreature->getName() );
	if (pGuildMember==NULL) return;

	pGuildMember->saveIntro( pPacket->getGuildMemberIntro() );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

