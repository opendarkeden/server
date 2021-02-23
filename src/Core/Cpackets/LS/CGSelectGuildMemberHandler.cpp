//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectGuildMemberHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectGuildMember.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Gpackets/GCShowGuildMemberInfo.h"
	#include "GuildManager.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Guild.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectGuildMemberHandler::execute (CGSelectGuildMember* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPlayerCreature != NULL );

	// 선택한 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPlayerCreature->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// 선택한 길드 멤버를 가져온다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	GCShowGuildMemberInfo gcShowGuildMemberInfo;
	gcShowGuildMemberInfo.setGuildID( pGuildMember->getGuildID() );
	gcShowGuildMemberInfo.setName( pGuildMember->getName() );
	gcShowGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
	gcShowGuildMemberInfo.setGuildMemberIntro( pGuildMember->getIntro() );

	pPlayer->sendPacket( &gcShowGuildMemberInfo );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

