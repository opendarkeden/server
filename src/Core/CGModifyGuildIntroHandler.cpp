//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyGuildIntroHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyGuildIntro.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "GSModifyGuildIntro.h"
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

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	if (pGuild==NULL) return;

	// ��� ��� ������ �����´�.
	GuildMember* pGuildMember  = pGuild->getMember( pPlayerCreature->getName() );
	if (pGuildMember==NULL) return;

	// ��� ������ �̾�� �Ѵ�.
	if ( pGuild->getMaster() != pPlayerCreature->getName() )
		return;
	if (pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER )
		return;

	// ��� Intro ���� ��Ŷ�� ����� ������ ������.
	GSModifyGuildIntro gsModifyGuildIntro;
	gsModifyGuildIntro.setGuildID( pGuild->getID() );
	gsModifyGuildIntro.setGuildIntro( pPacket->getGuildIntro() );

	g_pSharedServerManager->sendPacket( &gsModifyGuildIntro );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

