//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyGuildIntroHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyGuildIntro.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Gpackets/GSModifyGuildIntro.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "SharedServerManager.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGModifyGuildIntroHandler::execute (CGModifyGuildIntro* pPacket , Player* pPlayer)
	 
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
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	if (pGuild==NULL) return;

	// 길드 멤버 정보를 가져온다.
	GuildMember* pGuildMember  = pGuild->getMember( pPlayerCreature->getName() );
	if (pGuildMember==NULL) return;

	// 길드 마스터 이어야 한다.
	if ( pGuild->getMaster() != pPlayerCreature->getName() )
		return;
	if (pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER )
		return;

	// 길드 Intro 수정 패킷을 쉐어드 서버로 보낸다.
	GSModifyGuildIntro gsModifyGuildIntro;
	gsModifyGuildIntro.setGuildID( pGuild->getID() );
	gsModifyGuildIntro.setGuildIntro( pPacket->getGuildIntro() );

	g_pSharedServerManager->sendPacket( &gsModifyGuildIntro );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

