//----------------------------------------------------------------------
//
// Filename    : GSExpelGuildMemberHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSExpelGuildMember.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"

	#include "Spackets/SGExpelGuildMemberOK.h"
	#include "Spackets/SGDeleteGuildOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSExpelGuildMemberHandler::execute()
// 
//----------------------------------------------------------------------
void GSExpelGuildMemberHandler::execute ( GSExpelGuildMember* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__
	//cout << "GSExpelGuildMember received" << endl;

	Assert( pPacket != NULL );

	// 플레이어가 속한 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// 플레이어가 길드의 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	// 길드 탈퇴 로그를 남긴다.
	filelog( "GuildExit.log", "GuildID: %d, GuildName: %s, Expel: %s, By: %s", pGuild->getID(), pGuild->getName().c_str(), pPacket->getName().c_str(), pPacket->getSender().c_str() );

	///////////////////////////////////////////////////////////////////
	//  DB에 Slayer, Vampire, Ousters 테이블의 GuildID 를 바꾼다.
	///////////////////////////////////////////////////////////////////
	Statement* pStmt = NULL;
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

	// Guild Member 를 expire 시킨다.
	pGuildMember->expire();

	// Guild 에서 삭제한다.
	pGuild->deleteMember( pGuildMember->getName() );

	// 게임 서버로 보낼 패킷을 만든다.
	SGExpelGuildMemberOK sgExpelGuildMemberOK;
	sgExpelGuildMemberOK.setGuildID( pGuild->getID() );
	sgExpelGuildMemberOK.setName( pPacket->getName() );
	sgExpelGuildMemberOK.setSender( pPacket->getSender() );

	// 게임 서버로 패킷을 보낸다.
	g_pGameServerManager->broadcast( &sgExpelGuildMemberOK );

	// 길드 인원이 5명 미만이 될 경우 길드를 삭제한다.
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE && pGuild->getActiveMemberCount() < MIN_GUILDMEMBER_COUNT )
	{
		// 길드 삭제 로그를 남긴다.
		filelog( "GuildBroken.log", "GuildID: %d, GuildName: %s, MemberCount: %d, Expel: %s", pGuild->getID(), pGuild->getName().c_str(), pGuild->getActiveMemberCount(), pPacket->getName().c_str() );

		// 길드 멤버 expire and delete
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();
		
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

			for ( ; itr != Members.end(); itr++ )
			{
				GuildMember* pGuildMember = itr->second;

				///////////////////////////////////////////////////////////////////
				//  DB에 Slayer, Vampire, Ousters 테이블의 GuildID 를 바꾼다.
				///////////////////////////////////////////////////////////////////
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

				// 길드 멤버를 expire 시킨다.
				pGuildMember->expire();
				// 완전히 DB에서 제거한다.
				//pGuildMember->destroy();

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

#endif
		
	__END_DEBUG_EX __END_CATCH
}
