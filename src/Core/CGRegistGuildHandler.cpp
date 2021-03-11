//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRegistGuildHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRegistGuild.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "DB.h"
	#include "Properties.h"
	#include "SharedServerManager.h"
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Guild.h"
	#include "Gpackets/GSAddGuild.h"
	#include "Gpackets/GCNPCResponse.h"
	#include "VariableManager.h"

	#include <stdio.h>

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRegistGuildHandler::execute (CGRegistGuild* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	string GuildName = pPacket->getGuildName();

	if ( GuildName.find_first_of("'\\") < GuildName.size() )
	{
		// 이미 사용 중인 길드 이름이다
		if ( pCreature->isSlayer() )
		{
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_NAME );
			pPlayer->sendPacket( &response );
		}
		else if ( pCreature->isVampire() )
		{
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_NAME );
			pPlayer->sendPacket( &response );
		}
		else if ( pCreature->isOusters() )
		{
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_NAME );
			pPlayer->sendPacket( &response );
		}

		return;
	}
	
	Statement* pStmt;
	Result* pResult;

	BEGIN_DB
	{
		// 같은 길드 이름이 있는지 체크
		pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
		pResult = pStmt->executeQuery( "SELECT GuildID FROM GuildInfo WHERE GuildName = '%s' AND GuildState IN ( 0, 1 )", pPacket->getGuildName().c_str() );

		if ( pResult->getRowCount() != 0 )
		{
			SAFE_DELETE( pStmt );

			// 이미 사용 중인 길드 이름이다
			if ( pCreature->isSlayer() )
			{
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_NAME );
				pPlayer->sendPacket( &response );
			}
			else if ( pCreature->isVampire() )
			{
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_NAME );
				pPlayer->sendPacket( &response );
			}
			else if ( pCreature->isOusters() )
			{
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_NAME );
				pPlayer->sendPacket( &response );
			}

			return;
		}
		
		// 다른 길드 소속인지 체크
		pResult = pStmt->executeQuery( "SELECT Rank, ExpireDate FROM GuildMember WHERE Name = '%s'", pCreature->getName().c_str() );

		if ( pResult->next() )
		{
			int    Rank       = pResult->getInt(1);
			string ExpireDate = pResult->getString(2);

			// 다른 길드에서 탈퇴한 경우는 길드를 생성할 수 없다.
			if ( ExpireDate.size() == 7 
				 && Rank==GuildMember::GUILDMEMBER_RANK_LEAVE)
			{
				time_t daytime = time(0);
				tm Time;
				Time.tm_year = atoi( ExpireDate.substr(0,3).c_str() );
				Time.tm_mon = atoi( ExpireDate.substr(3,2).c_str() );
				Time.tm_mday = atoi( ExpireDate.substr(5,2).c_str() );

//				if ( difftime( daytime, mktime(&Time) ) < 604800 )	// 실시간 7일이 지났는가?
				if ( difftime( daytime, mktime(&Time) ) < g_pVariableManager->getVariable(QUIT_GUILD_PENALTY_TERM)*24*3600 )	// 실시간 7일이 지났는가?
				{
					// 길드 생성할 수 없다는 메세지
					GCNPCResponse response;

					if (pCreature->isSlayer())
						response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_DENY );
					else if ( pCreature->isVampire() )
						response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_DENY );
					else if ( pCreature->isOusters() )
						response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_DENY );

					pPlayer->sendPacket( &response );

					SAFE_DELETE( pStmt );

					return;
				}
			}

			// 기존의 길드멤버 정보를 지워준다.
			pStmt->executeQuery(
					"DELETE FROM GuildMember WHERE Name='%s'",
					pCreature->getName().c_str() );

			//SAFE_DELETE( pStmt );
			//return;
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)
	

	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Assert( pSlayer != NULL );

		SkillDomainType_t highest = pSlayer->getHighestSkillDomain();

		// 등록 가능 여부 체크
		if ( ( pSlayer->getGold() >= REQUIRE_SLAYER_MASTER_GOLD ) &&			// 등록비 1억
			 ( pSlayer->getFame() >= REQUIRE_SLAYER_MASTER_FAME[highest]) &&	// 명성치
			 ( pSlayer->getSkillDomainLevel(highest) >= REQUIRE_SLAYER_MASTER_SKILL_DOMAIN_LEVEL )	// 레벨 50 이상
		   )
		{
			GSAddGuild gsAddGuild;

			gsAddGuild.setGuildName( pPacket->getGuildName() );
			gsAddGuild.setGuildMaster( pSlayer->getName() );
			gsAddGuild.setGuildIntro( pPacket->getGuildIntro() );
			gsAddGuild.setGuildState( Guild::GUILD_STATE_WAIT );
			gsAddGuild.setGuildRace( Guild::GUILD_RACE_SLAYER );
			gsAddGuild.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

			g_pSharedServerManager->sendPacket( &gsAddGuild );

			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
			pPlayer->sendPacket( &response );
		}

	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		Assert( pVampire != NULL );

		// 등록 가능 여부 체크
		if ( ( pVampire->getGold() >= REQUIRE_VAMPIRE_MASTER_GOLD ) &&		// 등록비 1억
			 ( pVampire->getLevel() >= REQUIRE_VAMPIRE_MASTER_LEVEL )
		   )
		{
			GSAddGuild gsAddGuild;

			gsAddGuild.setGuildName( pPacket->getGuildName() );
			gsAddGuild.setGuildMaster( pVampire->getName() );
			gsAddGuild.setGuildIntro( pPacket->getGuildIntro() );
			gsAddGuild.setGuildState( Guild::GUILD_STATE_WAIT );
			gsAddGuild.setGuildRace( Guild::GUILD_RACE_VAMPIRE );
			gsAddGuild.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

			g_pSharedServerManager->sendPacket( &gsAddGuild );

			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
			pPlayer->sendPacket( &response );
		}
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		Assert( pOusters != NULL );

		// 등록 가능 여부 체크
		if ( ( pOusters->getGold() >= REQUIRE_OUSTERS_MASTER_GOLD ) &&		// 등록비 1억
			 ( pOusters->getLevel() >= REQUIRE_OUSTERS_MASTER_LEVEL )
		   )
		{
			GSAddGuild gsAddGuild;

			gsAddGuild.setGuildName( pPacket->getGuildName() );
			gsAddGuild.setGuildMaster( pOusters->getName() );
			gsAddGuild.setGuildIntro( pPacket->getGuildIntro() );
			gsAddGuild.setGuildState( Guild::GUILD_STATE_WAIT );
			gsAddGuild.setGuildRace( Guild::GUILD_RACE_OUSTERS );
			gsAddGuild.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

			g_pSharedServerManager->sendPacket( &gsAddGuild );

			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
			pPlayer->sendPacket( &response );
		}
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

