//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyGuildMemberHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyGuildMember.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Gpackets/GSModifyGuildMember.h"
	#include "Gpackets/GSExpelGuildMember.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "StringPool.h"
	#include "SharedServerManager.h"
	#include "Gpackets/GCSystemMessage.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGModifyGuildMemberHandler::execute (CGModifyGuildMember* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	//cout << "CGModifyGuildMember received." << endl;

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
	//try { Assert( pGuild != NULL ); } catch ( Throwable& t ) { return; }
	if (pGuild==NULL) return;

	// 길드 멤버 정보를 가져온다.
	GuildMember* pGuildMember  = pGuild->getMember( pPlayerCreature->getName() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& t ) { return; }
	if (pGuildMember==NULL) return;

	//cout << "get guild" << endl;

	if ( pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_DENY )
	{
		////////////////////////////////////////////////////////
		// 길드 멤버를 추방한다.
		////////////////////////////////////////////////////////

		// 마스터가 아니면 추방할 수 없다.
		if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER )
			return;

		if ( g_pGuildManager->hasActiveWar( pGuild->getID() ) )
		{
			GCSystemMessage msg;
			msg.setMessage( g_pStringPool->getString( STRID_CANNOT_KICK_DURING_WAR ) );
			pPlayer->sendPacket( &msg );

			return;
		}

		GSExpelGuildMember gsExpelGuildMember;
		gsExpelGuildMember.setGuildID( pGuild->getID() );
		gsExpelGuildMember.setName( pPacket->getName() );
		gsExpelGuildMember.setSender( pPlayerCreature->getName() );

		//cout << "send GSExpelGuildMember" << endl;
		g_pSharedServerManager->sendPacket( &gsExpelGuildMember );
	}
	else
	{
		if (pGuild->getActiveMemberCount() >= MAX_GUILDMEMBER_ACTIVE_COUNT )
		{
			GCSystemMessage msg;
			msg.setMessage( g_pStringPool->getString( STRID_CANNOT_ACCEPT_MORE_JOIN ) );
			pPlayer->sendPacket( &msg );

			return;
		}
		///////////////////////////////////////////////////////
		// 길드 가입을 승인한다.
		///////////////////////////////////////////////////////

		// 마스터나 서브마스터 이어야 한다.
		if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER
		  && pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_SUBMASTER )
			return;

		if ( g_pGuildManager->hasActiveWar( pGuild->getID() ) )
		{
			GCSystemMessage msg;
			msg.setMessage( g_pStringPool->getString( STRID_CANNOT_ACCEPT_DURING_WAR ) );
			pPlayer->sendPacket( &msg );

			return;
		}

		GSModifyGuildMember gsModifyGuildMember;
		gsModifyGuildMember.setGuildID( pGuild->getID() );
		gsModifyGuildMember.setName( pPacket->getName() );
		gsModifyGuildMember.setGuildMemberRank( pPacket->getGuildMemberRank() );
		gsModifyGuildMember.setSender( pPlayerCreature->getName() );

		//cout << "send GSModifyGuildMember" << endl;
		g_pSharedServerManager->sendPacket( &gsModifyGuildMember );
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

