//----------------------------------------------------------------------
//
// Filename    : SGDeleteGuildOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGDeleteGuildOK.h"

#ifdef __GAME_SERVER__

	#include "Assert.h"
	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Properties.h"
	#include "Zone.h"
	#include "ResurrectLocationManager.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"

	#include "GuildUnion.h"
#endif

//----------------------------------------------------------------------
// 
// SGDeleteGuildOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGDeleteGuildOKHandler::execute ( SGDeleteGuildOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	// 길드 아지트에 있는 멤버를 warp 시킨다.
	// 길드 아지트를 삭제한다.
	// 멤버 warp와 길드 아지트 삭제 시 다른 쓰레드에서 ZoneGroup Thread 내부에서 일어나게 해야 별탈이 없을 듯 하다.
	// 일단은 걍 둔다. Portal 이 막히므로 다시 들어갈 수 없을 것이다.
	
	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }


	// 길드 활동 중인 상태에서의 해체인지 대기 중인 상태에서의 해체인지 구별한다.
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
	{
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();

		for ( ; itr != Members.end(); itr++ )
		{
			GuildMember* pGuildMember = itr->second;

			// 접속해 있으면
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))

			Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
			if ( pCreature != NULL && pCreature->isPC() )
			{
				Player* pPlayer = pCreature->getPlayer();
				Assert( pPlayer != NULL );

				PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPlayerCreature != NULL );

				// Slayer, Vampire 의 길드 아이디를 바꾼다.
				if ( pPlayerCreature->isSlayer() )
				{
					pPlayerCreature->setGuildID( 99 );		// 슬레이어 가입안한 상태의 길드 ID

					// 클라이언트에 길드 아이디가 바꼈음을 알린다.
					GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
					gcModifyGuildMemberInfo.setGuildID( pPlayerCreature->getGuildID() );
					gcModifyGuildMemberInfo.setGuildName( "" );
					gcModifyGuildMemberInfo.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
					pPlayer->sendPacket( &gcModifyGuildMemberInfo );
				}
				else if ( pPlayerCreature->isVampire() )
				{
					pPlayerCreature->setGuildID( 0 );		// 뱀파이어 가입안한 상태의 길드 ID

					// 클라이언트에 길드 아이디가 바꼈음을 알린다.
					GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
					gcModifyGuildMemberInfo.setGuildID( pPlayerCreature->getGuildID() );
					gcModifyGuildMemberInfo.setGuildName( "" );
					gcModifyGuildMemberInfo.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
					pPlayer->sendPacket( &gcModifyGuildMemberInfo );
				}
				else if ( pPlayerCreature->isOusters() )
				{
					pPlayerCreature->setGuildID( 66 );		// 아우스터즈 가입안한 상태의 길드 ID

					// 클라이언트에 길드 아이디가 바꼈음을 알린다.
					GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
					gcModifyGuildMemberInfo.setGuildID( pPlayerCreature->getGuildID() );
					gcModifyGuildMemberInfo.setGuildName( "" );
					gcModifyGuildMemberInfo.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
					pPlayer->sendPacket( &gcModifyGuildMemberInfo );
				}

				// 주위에 클라이언트에 길드 아이디가 바꼈음을 알린다.
				GCOtherModifyInfo gcOtherModifyInfo;
				gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
				gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pPlayerCreature->getGuildID() );

				Zone* pZone = pCreature->getZone();
				Assert( pZone != NULL );

				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo, pCreature );
			}

			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			// Guild Member 객체를 삭제한다.
			SAFE_DELETE( pGuildMember );
		}

		// 길드 멤버 맵을 삭제한다.
		Members.clear();

		// 길드 매니저에서 길드를 삭제한다.
		g_pGuildManager->deleteGuild( pGuild->getID() );

		// 길드 객체를 삭제한다.
		SAFE_DELETE( pGuild );
	}
	else if ( pGuild->getState() == Guild::GUILD_STATE_WAIT )
	{
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();

		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			for ( ; itr != Members.end(); itr++ )
			{
				GuildMember* pGuildMember = itr->second;

				// 접속해 있으면
				__ENTER_CRITICAL_SECTION((*g_pPCFinder))

				Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
				if ( pCreature != NULL && pCreature->isPC() )
				{
					Player* pPlayer = pCreature->getPlayer();
					Assert( pPlayer != NULL );

					PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
					Assert( pPlayerCreature != NULL );

					// 등록비를 환불한다.
					Gold_t Gold = pPlayerCreature->getGold();
					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
					{
						Gold = min( Gold + (uint)RETURN_SLAYER_MASTER_GOLD, (long unsigned int)2000000000 );
					}
					else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
					{
						Gold = min( Gold + (uint)RETURN_SLAYER_SUBMASTER_GOLD, (long unsigned int)2000000000 );
					}

					pPlayerCreature->setGoldEx( Gold );

					GCModifyInformation gcModifyInformation;
					gcModifyInformation.addLongData( MODIFY_GOLD, Gold );
					pPlayer->sendPacket( &gcModifyInformation );

					// 메시지를 보낸다.
					pResult = pStmt->executeQuery( "SELECT Message FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str() );

					while ( pResult->next() )
					{
						GCSystemMessage message;
						message.setMessage( pResult->getString(1) );
						pPlayer->sendPacket( &message );
					}

					pStmt->executeQuery( "DELETE FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str() );
				}

				__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

				// 길드 멤버 객체를 삭제한다.
				SAFE_DELETE( pGuildMember );
			}

			// 길드 멤버 해쉬 맵을 지운다.
			Members.clear();

			// 길드 매니저에서 길드를 삭제한다.
			g_pGuildManager->deleteGuild( pGuild->getID() );
			GuildUnionManager::Instance().removeMasterGuild( pGuild->getID());

			// 길드 객체를 삭제한다.
			SAFE_DELETE( pGuild );

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}

#endif
		
	__END_CATCH
}
