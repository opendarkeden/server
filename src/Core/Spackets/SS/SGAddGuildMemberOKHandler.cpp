//----------------------------------------------------------------------
//
// Filename    : SGAddGuildMemberOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGAddGuildMemberOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "StringPool.h"
	#include "StringStream.h"
	#include "DB.h"
	#include "Properties.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCOtherModifyInfo.h"

	#include <stdio.h>

#endif

//----------------------------------------------------------------------
// 
// SGAddGuildMemberOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGAddGuildMemberOKHandler::execute ( SGAddGuildMemberOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 길드 멤버 object 를 만든다.
	GuildMember* pGuildMember = new GuildMember();
	pGuildMember->setGuildID( pPacket->getGuildID() );
	pGuildMember->setName( pPacket->getName() );
	pGuildMember->setRank( pPacket->getGuildMemberRank() );

	// 길드에 추가한다.
	Guild* pGuild = g_pGuildManager->getGuild( pGuildMember->getGuildID() );
	pGuild->addMember( pGuildMember );

	// 멤버에게 메세지를 보낸다.
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
	if ( pCreature != NULL && pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER ||
			 pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )		// 길드마스터나 서브마스터일 경우
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			Gold_t Fee;
			if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
				Fee = REQUIRE_SLAYER_MASTER_GOLD;
			else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
				Fee = REQUIRE_SLAYER_SUBMASTER_GOLD;
			else
				Fee = 0;
			
			Gold_t CurMoney = pPlayerCreature->getGold();
			if ( CurMoney < Fee )
			{
				// 큰일났군
				CurMoney = 0;
			}
			else
				CurMoney -= Fee;

			pPlayerCreature->setGoldEx( CurMoney );

			if ( Fee != 0 )
			{
				GCModifyInformation gcModifyInformation;
				gcModifyInformation.addLongData( MODIFY_GOLD, CurMoney );

				// 바뀐정보를 클라이언트에 보내준다.
				pPlayer->sendPacket( &gcModifyInformation );
			}

            // 길드 가입 메시지를 보여준다.
            GCSystemMessage gcSystemMessage;
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TEAM_JOIN_ACCEPTED ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_JOIN_ACCEPTED ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_JOIN_ACCEPTED ) );
            pPlayer->sendPacket( &gcSystemMessage );

		}
		else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
		{
			// 길드 가입 신청 메시지를 보낸다.
			GCSystemMessage gcSystemMessage;
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TEAM_JOIN_TRY ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_JOIN_TRY ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_JOIN_TRY ) );

			pPlayer->sendPacket( &gcSystemMessage );
		}
	}
	else
	{
		// 접속이 안되어 있다.

		// 마스터나 서브마스터일 경우 
		// DB 에서 돈을 까도록 한다.
		if ( ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER ||
			 	pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )		// 길드마스터나 서브마스터일 경우
			&& pPacket->getServerGroupID() == g_pConfig->getPropertyInt( "ServerID" ) )		// 이 게임 서버에서 추가한 길드원인가?
		{
			Gold_t Fee;
			if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
				Fee = REQUIRE_SLAYER_MASTER_GOLD;
			else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
				Fee = REQUIRE_SLAYER_SUBMASTER_GOLD;
			else
				Fee = 0;

			string table = "";
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				table = "Slayer";
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
			{
				table = "Vampire";
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
			{
				table = "Ousters";
			}

			if ( table != "" && Fee != 0 )
			{
				Statement* pStmt = NULL;

				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pStmt->executeQuery( "UPDATE %s SET Gold = IF ( %u > Gold , 0, Gold - %u ) WHERE Name = '%s'",
											table.c_str(), Fee, Fee, pGuildMember->getName().c_str() );
				}
				END_DB(pStmt)
			}
		}
	}

	// 길드 마스터에게 메시지를 보낸다.
	pCreature = g_pPCFinder->getCreature_LOCKED( pGuild->getMaster() );
	if ( pCreature != NULL && pCreature->isPC() && pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

        char msg[100];

        if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
        {
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_JOIN_ACCEPTED_2 ),
                                pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_ACCEPTED_2 ),
                                pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_ACCEPTED_2 ),
                                pGuildMember->getName().c_str() );
        }
        else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
        {
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_JOIN_TRY_2 ),
                                pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_TRY_2 ),
                                pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_TRY_2 ),
                                pGuildMember->getName().c_str() );
        }

        GCSystemMessage gcSystemMessage;
        gcSystemMessage.setMessage( msg );
        pPlayer->sendPacket( &gcSystemMessage );

	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

#endif
		
	__END_DEBUG_EX __END_CATCH
}
