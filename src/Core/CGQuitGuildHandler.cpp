//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitGuildHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitGuild.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "GSQuitGuild.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "SharedServerManager.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGQuitGuildHandler::execute (CGQuitGuild* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pPlayer);
	Assert( pPlayerCreature != NULL );

	// �÷��̾ ���� ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& t ) { return; }

	// �÷��̾ ����� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPlayerCreature->getName() );
	if ( pGuildMember == NULL )
		return;

	GSQuitGuild gsQuitGuild;
	gsQuitGuild.setGuildID( pGuild->getID() );
	gsQuitGuild.setName( pPlayerCreature->getName() );

	g_pSharedServerManager->sendPacket( &gsQuitGuild );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

