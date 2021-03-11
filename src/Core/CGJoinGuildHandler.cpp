////////////////////////////////////////////////////////////////////////////// // Filename    : CGJoinGuildHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGJoinGuild.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "DB.h"
	#include "SharedServerManager.h"
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "GuildManager.h"
	#include "Guild.h"
	#include "Properties.h"
	#include "Gpackets/GSAddGuildMember.h"
	#include "Gpackets/GCNPCResponse.h"
	#include "VariableManager.h"

	#include <stdio.h>

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGJoinGuildHandler::execute (CGJoinGuild* pPacket , Player* pPlayer)
	 
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

	Player* pPlayer = pCreature->getPlayer();
	Assert( pPlayer != NULL );
	
	Statement* pStmt;
	Result* pResult;

	//cout << pPacket->toString() << endl;

	BEGIN_DB
	{
		// 정상적인 과정을 거쳤다면 여기서 체크할때 걸리면 안된다.
		// 그런 이유로 에러메시지를 클라이언트로 보내지 않는다.
		// 다른 길드 소속인지 체크
		pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
		pResult = pStmt->executeQuery( "SELECT GuildID, Rank, ExpireDate FROM GuildMember WHERE Name = '%s'", pCreature->getName().c_str() );

		if ( pResult->next() )
		{
			
			GuildID_t   GuildID    = pResult->getInt(1);
			int    		Rank       = pResult->getInt(2);
			string 		ExpireDate = pResult->getString(3);

			if ( ExpireDate.size() == 7 )
			{
				time_t daytime = time(0);

				tm Time;

				Time.tm_year = atoi( ExpireDate.substr(0,3).c_str() );
				Time.tm_mon = atoi( ExpireDate.substr(3,2).c_str() );
				Time.tm_mday = atoi( ExpireDate.substr(5,2).c_str() );
				Time.tm_hour = 0;
				Time.tm_min = 0;
				Time.tm_sec = 0;

//				if ( difftime( daytime, mktime(&Time) ) < 604800 )	// 실시간 7일이 지났는가?
				if ( difftime( daytime, mktime(&Time) ) < g_pVariableManager->getVariable(QUIT_GUILD_PENALTY_TERM)*24*3600 )	// 실시간 7일이 지났는가?
				{
/*					if (Rank==GuildMember::GUILDMEMBER_RANK_DENY
						&& GuildID != pPacket->getGuildID())
					{
						// rank4==추방/거부..인 애들은 다른 길드에는 들어갈 수 있다.
						// 기존에 있던 GuildMember에서 제거한다.
						pStmt->executeQuery( "DELETE FROM GuildMember WHERE Name = '%s'",
												pCreature->getName().c_str() );
					}
					else
					{
						SAFE_DELETE( pStmt );

						return;
					}*/

					// 실시간 7일이 지나지 않으면 가입할 수 없다. 무조건
					// 2003. 6. 25 by bezz
					SAFE_DELETE( pStmt );

					return;
				}
			}
			else
			{
				// 이미 다른 길드에 소속되어 있음
				SAFE_DELETE( pStmt );

				return;
			}
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)


	// 스타팅 멤버로 가입할 경우
	if ( pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		// 길드가 이미 정식 길드로 등록되었는지 확인한다.
		Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
		if ( pGuild == NULL ) return;

		if ( pGuild->getState() != Guild::GUILD_STATE_WAIT )
			return;

		if ( pCreature->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Assert( pSlayer != NULL );

			SkillDomainType_t highest = pSlayer->getHighestSkillDomain();

			// 등록 가능 여부 체크
			if ( ( pSlayer->getGold() >= REQUIRE_SLAYER_SUBMASTER_GOLD ) &&				// 등록비 5천만
				 ( pSlayer->getFame() >= REQUIRE_SLAYER_SUBMASTER_FAME[highest]) &&		// 명성치
				 ( pSlayer->getSkillDomainLevel(highest) >= REQUIRE_SLAYER_SUBMASTER_SKILL_DOMAIN_LEVEL )	// 레벨 40 이상
			   )
			{
				GSAddGuildMember gsAddGuildMember;

				gsAddGuildMember.setGuildID( pPacket->getGuildID() );
				gsAddGuildMember.setName( pSlayer->getName() );
				gsAddGuildMember.setGuildMemberRank( pPacket->getGuildMemberRank() );
				gsAddGuildMember.setGuildMemberIntro( pPacket->getGuildMemberIntro() );
				gsAddGuildMember.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

				g_pSharedServerManager->sendPacket( &gsAddGuildMember );
			}

		}
		else if ( pCreature->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			Assert( pVampire != NULL );

			// 등록 가능 여부 체크
			if ( ( pVampire->getGold() >= REQUIRE_VAMPIRE_SUBMASTER_GOLD ) &&		// 등록비 5천만
				 ( pVampire->getLevel() >= REQUIRE_VAMPIRE_SUBMASTER_LEVEL )		// 레벨 40 이상
			   )
			{
				GSAddGuildMember gsAddGuildMember;

				gsAddGuildMember.setGuildID( pPacket->getGuildID() );
				gsAddGuildMember.setName( pVampire->getName() );
				gsAddGuildMember.setGuildMemberRank( pPacket->getGuildMemberRank() );
				gsAddGuildMember.setGuildMemberIntro( pPacket->getGuildMemberIntro() );
				gsAddGuildMember.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

				g_pSharedServerManager->sendPacket( &gsAddGuildMember );

			}
		}
		else if ( pCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			Assert( pOusters != NULL );

			// 등록 가능 여부 체크
			if ( ( pOusters->getGold() >= REQUIRE_OUSTERS_SUBMASTER_GOLD ) &&		// 등록비 5천만
				 ( pOusters->getLevel() >= REQUIRE_OUSTERS_SUBMASTER_LEVEL )		// 레벨 40 이상
			   )
			{
				GSAddGuildMember gsAddGuildMember;

				gsAddGuildMember.setGuildID( pPacket->getGuildID() );
				gsAddGuildMember.setName( pOusters->getName() );
				gsAddGuildMember.setGuildMemberRank( pPacket->getGuildMemberRank() );
				gsAddGuildMember.setGuildMemberIntro( pPacket->getGuildMemberIntro() );
				gsAddGuildMember.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

				g_pSharedServerManager->sendPacket( &gsAddGuildMember );

			}
		}
	}
	else if ( pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		// 길드 가입 신청, 대기 상태
		GSAddGuildMember gsAddGuildMember;

		gsAddGuildMember.setGuildID( pPacket->getGuildID() );
		gsAddGuildMember.setName( pCreature->getName() );
		gsAddGuildMember.setGuildMemberRank( pPacket->getGuildMemberRank() );
		gsAddGuildMember.setGuildMemberIntro( pPacket->getGuildMemberIntro() );
		gsAddGuildMember.setServerGroupID( g_pConfig->getPropertyInt( "ServerID" ) );

		g_pSharedServerManager->sendPacket( &gsAddGuildMember );
	}

	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &response );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

