//----------------------------------------------------------------------
//
// Filename    : GSQuitGuildHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSQuitGuild.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"
	#include "StringPool.h"

	#include "Spackets/SGQuitGuildOK.h"
	#include "Spackets/SGDeleteGuildOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSQuitGuildHandler::execute()
// 
//----------------------------------------------------------------------
void GSQuitGuildHandler::execute ( GSQuitGuild* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// 플레이어가 속한 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// 플레이어가 길드의 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	Statement* pStmt = NULL;

	// 길드 탈퇴 로그를 남긴다.
	GuildMemberRank_t rank = pGuildMember->getRank();
	if ( rank == GuildMember::GUILDMEMBER_RANK_NORMAL ||
		 rank == GuildMember::GUILDMEMBER_RANK_MASTER ||
		 rank == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
		filelog( "GuildExit.log", "GuildID: %d, GuildName: %s, Quit: %s", pGuild->getID(), pGuild->getName().c_str(), pPacket->getName().c_str() );

	//////////////////////////////////////////////////////////////////////////////
	// 길드가 active 라면 걍 탈퇴하는 거다
	// wait 라면 돈도 돌려주고 탈퇴하는 사람이 마스터라면 길드를 취소시킨다.
	//////////////////////////////////////////////////////////////////////////////
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
	{
		// 길드 마스터일 경우 무시
		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
			return;

		// DB 의 Slayer, Vampire, Ousters 테이블의 길드 아이디를 바꾼다.
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				pStmt->executeQuery( "UPDATE Slayer SET GuildID = 99 WHERE Name = '%s'", pGuildMember->getName().c_str() );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
			{
				pStmt->executeQuery( "UPDATE Vampire SET GuildID = 0 WHERE Name = '%s'", pGuildMember->getName().c_str() );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
			{
				pStmt->executeQuery( "UPDATE Ousters SET GuildID = 66 WHERE Name = '%s'", pGuildMember->getName().c_str() );
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)

		// Guild Member 를 leave 시킨다.
		pGuildMember->leave();

		// Guild 에서 삭제한다.
		pGuild->deleteMember( pGuildMember->getName() );

		// 게임 서버로 보낼 패킷을 만든다.
		SGQuitGuildOK sgQuitGuildOK;
		sgQuitGuildOK.setGuildID( pGuild->getID() );
		sgQuitGuildOK.setName( pPacket->getName() );

		// 게임 서버로 패킷을 보낸다.
		g_pGameServerManager->broadcast( &sgQuitGuildOK );

		// 길드 인원이 5명 미만이 될 경우
		if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE && pGuild->getActiveMemberCount() < MIN_GUILDMEMBER_COUNT )
		{
			// 기록을 남긴다.
			filelog( "GuildBroken.log", "GuildID: %d, GuildName: %s, MemberCount: %d, Quit: %s", pGuild->getID(), pGuild->getName().c_str(), pGuild->getActiveMemberCount(), pPacket->getName().c_str() );

			// 길드 멤버 expire and delete
			HashMapGuildMember& Members = pGuild->getMembers();
			HashMapGuildMemberItor itr = Members.begin();

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

				for ( ; itr != Members.end(); itr++ )
				{
					GuildMember* pGuildMember = itr->second;

					if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
					{
						pStmt->executeQuery( "UPDATE Slayer SET GuildID = 99 WHERE Name = '%s'", pGuildMember->getName().c_str() );
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_TEAM_BROKEN ) );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
					{
						pStmt->executeQuery( "UPDATE Vampire SET GuildID = 0 WHERE Name = '%s'", pGuildMember->getName().c_str() );
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_BROKEN ) );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
					{
						pStmt->executeQuery( "UPDATE Ousters SET GuildID = 0 WHERE Name = '%s'", pGuildMember->getName().c_str() );
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_BROKEN ) );
					}

					// 길드 멤버를 expire 시킨다.
					pGuildMember->expire();

					// 길드 멤버를 삭제
					SAFE_DELETE( pGuildMember );
				}
				
				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

			Members.clear();

			// 길드를 삭제한다
			pGuild->setState( Guild::GUILD_STATE_BROKEN );
			pGuild->save();

			SAFE_DELETE( pGuild );
			g_pGuildManager->deleteGuild( pPacket->getGuildID() );

			// 길드를 삭제하도록 패킷을 보낸다.
			SGDeleteGuildOK sgDeleteGuildOK;
			sgDeleteGuildOK.setGuildID( pPacket->getGuildID() );

			g_pGameServerManager->broadcast( &sgDeleteGuildOK );
		}
	}
	else if ( pGuild->getState() == Guild::GUILD_STATE_WAIT )
	{
		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
		{
			////////////////////////////////////////////////////////////
			// 길드를 취소 시킨다.
			// 길드 멤버 expire and delete
			////////////////////////////////////////////////////////////
			HashMapGuildMember& Members = pGuild->getMembers();
			HashMapGuildMemberItor itr = Members.begin();

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

				for ( ; itr != Members.end(); itr++ )
				{
					GuildMember* pGuildMember = itr->second;

					string Table = "";
					string Message = "";
					Gold_t Gold = 0;

					if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
					{
						Table = "Slayer";
						Message = g_pStringPool->getString( STRID_TEAM_CANCEL );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
					{
						Table = "Vampire";
						Message = g_pStringPool->getString( STRID_CLAN_CANCEL );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
					{
						Table = "Ousters";
						Message = g_pStringPool->getString( STRID_CLAN_CANCEL );
					}
					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
						Gold = RETURN_SLAYER_MASTER_GOLD;
					else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
						Gold = RETURN_SLAYER_SUBMASTER_GOLD;

					if ( !Table.empty() && !Message.empty() && Gold != 0 )
					{
						// 메시지를 넣는다.
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), Message.c_str() );
						
						// 등록비를 환불한다. 게임 플레이중인 캐릭터는 DB 데이타랑 gameserver에 있는 데이타랑 다를수도 있기때문에 이렇게 하면 안되는데, 다시 게임 서버에서 새로 업데이트 한다.
						pStmt->executeQuery( "UPDATE %s SET Gold = Gold + %d WHERE Name = '%s'", Table.c_str(), (int)Gold, pGuildMember->getName().c_str() );
					}

					// 길드 멤버를 expire 시킨다.
					pGuildMember->expire();

					// 길드 멤버를 삭제
					SAFE_DELETE( pGuildMember );
				}
				
				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

			Members.clear();

			// 길드를 삭제한다
			pGuild->setState( Guild::GUILD_STATE_CANCEL );
			pGuild->save();

			SAFE_DELETE( pGuild );

			g_pGuildManager->deleteGuild( pPacket->getGuildID() );

			// 길드를 삭제하도록 패킷을 보낸다.
			SGDeleteGuildOK sgDeleteGuildOK;
			sgDeleteGuildOK.setGuildID( pPacket->getGuildID() );

			g_pGameServerManager->broadcast( &sgDeleteGuildOK );
		}
		else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
		{
			//////////////////////////////////////////////////////////
			// 스타팅 멤버 가입을 취소 시킨다.
			// Guild Member 를 expire 시킨다.
			//////////////////////////////////////////////////////////
			pGuildMember->expire();

			// Guild 에서 삭제한다.
			pGuild->deleteMember( pGuildMember->getName() );

			// 게임 서버로 보낼 패킷을 만든다.
			SGQuitGuildOK sgQuitGuildOK;
			sgQuitGuildOK.setGuildID( pGuild->getID() );
			sgQuitGuildOK.setName( pPacket->getName() );

			// 게임 서버로 패킷을 보낸다.
			g_pGameServerManager->broadcast( &sgQuitGuildOK );

		}
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
