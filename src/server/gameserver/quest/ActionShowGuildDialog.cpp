////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowGuildDialog.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionShowGuildDialog.h"
#include "DB.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Guild.h"
#include "GuildManager.h"
#include "GuildInfo.h"
#include "SharedServerManager.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCWaitGuildList.h"
#include "Gpackets/GCActiveGuildList.h"
#include "Gpackets/GSQuitGuild.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionShowGuildDialog::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try
	{
		// 다이얼로그의 종류
		m_Type = (GuildDialog_t)propertyBuffer.getPropertyInt("Type");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionShowGuildDialog::execute (Creature * pCreature1, Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT(SYSTEM_GUILD);

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	if ( m_Type == GUILD_DIALOG_REGIST )
	{
		//cout << "길드 등록" << endl;
		////////////////////////////////////////////////////////////////////////////////
		// 길드 등록을 선택했을 경우
		////////////////////////////////////////////////////////////////////////////////
		Statement* pStmt;
		Result* pResult;

		BEGIN_DB
		{
			// 다른 길드 소속인지 체크
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			pResult = pStmt->executeQuery( "SELECT Rank, ExpireDate FROM GuildMember WHERE Name = '%s'", pCreature->getName().c_str() );

			if ( pResult->next() )
			{
				// 길드 등록 정보가 있다. expire date를 보고 결정한다.
				int  	Rank 		= pResult->getInt(1);
				string 	ExpireDate 	= pResult->getString(2);

				if ( ExpireDate.size() == 7 )
				{
					// 다른 길드에서 탈퇴한 경우에는 일주일 동안 길드를 만들 수 없다.
					if (Rank==GuildMember::GUILDMEMBER_RANK_LEAVE)
					{
						// 현재는 길드 소속 상태가 아니다. 하지만 expire date 에서 7일이 지나야 한다.
						time_t daytime = time(0);
						tm Time;
						Time.tm_year = atoi( ExpireDate.substr(0,3).c_str() );
						Time.tm_mon = atoi( ExpireDate.substr(3,2).c_str() );
						Time.tm_mday = atoi( ExpireDate.substr(5,2).c_str() );

						if ( difftime( daytime, mktime(&Time) ) < 604800 ) // 실시간 7일이 지났는가?
						{

							SAFE_DELETE( pStmt );

							// 시간이 일주일 ...어쩌고
							if ( pCreature->isSlayer() )
							{
								GCNPCResponse response;
								response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_QUIT_TIMEOUT );
								pPlayer->sendPacket( &response );
							}
							else if ( pCreature->isVampire() )
							{
								GCNPCResponse response;
								response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_QUIT_TIMEOUT );
								pPlayer->sendPacket( &response );
							}
							else if ( pCreature->isOusters() )
							{
								GCNPCResponse response;
								response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_QUIT_TIMEOUT );
								pPlayer->sendPacket( &response );
							}

							return;
						}
					}
				}
				else
				{
					SAFE_DELETE( pStmt );

					// 다른 길드에 가입되어있는 경우
					if ( pCreature->isSlayer() )
					{
						GCNPCResponse response;
						response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_ALREADY_JOIN );
						pPlayer->sendPacket( &response );
					}
					else if ( pCreature->isVampire() )
					{
						GCNPCResponse response;
						response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_ALREADY_JOIN );
						pPlayer->sendPacket( &response );
					}
					else if ( pCreature->isOusters() )
					{
						GCNPCResponse response;
						response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_ALREADY_JOIN );
						pPlayer->sendPacket( &response );
					}

					
					return;
				}
			}
		}
		END_DB(pStmt)

		if ( pCreature->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Assert( pSlayer != NULL );

			SkillDomainType_t highest = pSlayer->getHighestSkillDomain();

			if ( pSlayer->getSkillDomainLevel(highest) < REQUIRE_SLAYER_MASTER_SKILL_DOMAIN_LEVEL )	// 레벨 50 이상
			{
				// 레벨이 낮음
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_LEVEL );
				pPlayer->sendPacket( &response );

				return;
			}
			if ( pSlayer->getGold() < REQUIRE_SLAYER_MASTER_GOLD )				// 등록비 1억
			{
				// 등록비가 모자람
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_MONEY );
				pPlayer->sendPacket( &response );

				return;
			}
			if ( pSlayer->getFame() < REQUIRE_SLAYER_MASTER_FAME[highest] )		// 명성
			{
				// 명성이 모자람
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_TEAM_REGIST_FAIL_FAME );
				pPlayer->sendPacket( &response );

				return;
			}
			// 길드 등록 창을 띄우도록 메시지를 보낸다.
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_GUILD_SHOW_REGIST );
			response.setParameter( REQUIRE_SLAYER_MASTER_GOLD );
			pPlayer->sendPacket( &response );
		}
		else if ( pCreature->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			Assert( pVampire != NULL );

			// 등록 가능 여부 체크
			if ( pVampire->getLevel() < REQUIRE_VAMPIRE_MASTER_LEVEL )				// 레벨 50이상
			{
				// 레벨이 낮음
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_LEVEL );
				pPlayer->sendPacket( &response );

				return;
			}
			if ( pVampire->getGold() < REQUIRE_VAMPIRE_MASTER_GOLD )			// 등록비 1억
			{
				// 등록비가 모자람
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_MONEY );
				pPlayer->sendPacket( &response );

				return;
			}
//			if ( pVampire->getFame() < 500000 )				// 명성 50만
//			{
//				// 명성이 모자람
//				GCNPCResponse response;
//				response.setCode( NPC_RESPONSE_CLAN_REGIST_FAIL_FAME );
//				pPlayer->sendPacket( &response );
//
//				return;
//			}
			// 길드 등록 창을 띄우도록 메시지를 보낸다.
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_GUILD_SHOW_REGIST );

			//cout << "길드가입비 : " << REQUIRE_VAMPIRE_MASTER_GOLD << endl;
			response.setParameter( REQUIRE_VAMPIRE_MASTER_GOLD );
			//cout << "길드가입비(param) : " << response.getParameter() << endl;
			pPlayer->sendPacket( &response );
		}
		else if ( pCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			Assert( pOusters != NULL );

			// 등록 가능 여부 체크
			if ( pOusters->getLevel() < REQUIRE_OUSTERS_MASTER_LEVEL )				// 레벨 50이상
			{
				// 레벨이 낮음
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_LEVEL );
				pPlayer->sendPacket( &response );

				return;
			}
			if ( pOusters->getGold() < REQUIRE_OUSTERS_MASTER_GOLD )			// 등록비 1억
			{
				// 등록비가 모자람
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_GUILD_REGIST_FAIL_MONEY );
				pPlayer->sendPacket( &response );

				return;
			}

			// 길드 등록 창을 띄우도록 메시지를 보낸다.
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_GUILD_SHOW_REGIST );

			//cout << "길드가입비 : " << REQUIRE_VAMPIRE_MASTER_GOLD << endl;
			response.setParameter( REQUIRE_OUSTERS_MASTER_GOLD );
			//cout << "길드가입비(param) : " << response.getParameter() << endl;
			pPlayer->sendPacket( &response );
		}
	}
	else if ( m_Type == GUILD_DIALOG_WAIT_LIST )
	{
		//cout << "길드 대기 리스트" << endl;
		GCWaitGuildList gcWaitGuildList;

//		const HashMapGuild& Guilds = g_pGuildManager->getGuilds_const();
//		HashMapGuildConstItor itr = Guilds.begin();

		GuildRace_t race;
		if ( pCreature->isSlayer() )
			race = Guild::GUILD_RACE_SLAYER;
		else if ( pCreature->isVampire() )
			race = Guild::GUILD_RACE_VAMPIRE;
		else if ( pCreature->isOusters() )
			race = Guild::GUILD_RACE_OUSTERS;
		else
			return;

		g_pGuildManager->makeWaitGuildList( gcWaitGuildList, race );

		pPlayer->sendPacket( &gcWaitGuildList );
	}
	else if ( m_Type == GUILD_DIALOG_LIST )
	{
		//cout << "길드 리스트" << endl;
		GCActiveGuildList gcActiveGuildList;

		GuildRace_t race;
		if ( pCreature->isSlayer() )
			race = Guild::GUILD_RACE_SLAYER;
		else if ( pCreature->isVampire() )
			race = Guild::GUILD_RACE_VAMPIRE;
		else if ( pCreature->isOusters() )
			race = Guild::GUILD_RACE_OUSTERS;
		else
			return;

		g_pGuildManager->makeActiveGuildList( gcActiveGuildList, race );

		pPlayer->sendPacket( &gcActiveGuildList );
	}
	else if ( m_Type == GUILD_DIALOG_QUIT )
	{
		// 길드 탈퇴 창을 띄우지 않고 길드 탈퇴를 확정한 것으로 간주한다.
		Guild* pGuild = NULL;

		Statement* pStmt = NULL;
		Result* pResult = NULL;
		
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			pResult = pStmt->executeQuery( "SELECT GuildID FROM GuildMember WHERE Name = '%s'", pCreature->getName().c_str() );

			if ( pResult->next() )
			{
				pGuild = g_pGuildManager->getGuild( pResult->getInt(1) );
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
				
		// 길드 상태가 활동중이거나 대기중이어야 한다.
		if ( pGuild == NULL || 
			 ( pGuild->getState() != Guild::GUILD_STATE_ACTIVE && pGuild->getState() != Guild::GUILD_STATE_WAIT ) )
		{ 
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
			pPlayer->sendPacket( &response );

			return; 
		}

		// 플레이어가 길드의 멤버인지 확인한다.
		GuildMember* pGuildMember = pGuild->getMember( pCreature->getName() );
		if ( pGuildMember == NULL )
		{ 
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
			pPlayer->sendPacket( &response );

			return; 
		}

		// 활동 중인 길드의 마스터라면 탈퇴를 무시한다.
		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER && pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
		{
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
			pPlayer->sendPacket( &response );

			return;
		}

		GSQuitGuild gsQuitGuild;
		gsQuitGuild.setGuildID( pGuild->getID() );
		gsQuitGuild.setName( pCreature->getName() );

		g_pSharedServerManager->sendPacket( &gsQuitGuild );

		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &response );
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionShowGuildDialog::toString () const
	throw ()
{
	__BEGIN_TRY

	string str = "ActionShowGuildDialog";

	return str;

	__END_CATCH
}
