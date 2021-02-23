//----------------------------------------------------------------------
//
// Filename    : SGModifyGuildMemberOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGModifyGuildMemberOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "StringPool.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"
	#include "Gpackets/GCSystemMessage.h"

	#include <stdio.h>

#endif

//----------------------------------------------------------------------
// 
// SGModifyGuildMemberOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGModifyGuildMemberOKHandler::execute ( SGModifyGuildMemberOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << "SGModifyGuildMember received" << endl;

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }

	// 길드 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT &&
		 pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_NORMAL )
	{
		////////////////////////////////////////////////////////////////////////////
		// 길드 가입 신청을 승인한 경우이다.
		////////////////////////////////////////////////////////////////////////////

		// 길드멤버 정보를 변경한다.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );

		// 접속해 있다면 메시지를 보낸다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			// 실제 길드 ID를 등록한다.
			pPlayerCreature->setGuildID( pGuildMember->getGuildID() );

			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			Zone* pZone = pCreature->getZone();
			Assert( pZone != NULL );

			// 바뀐 길드 ID 정보를 보내준다.
			GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
			gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
			gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
			gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
			pPlayer->sendPacket( &gcModifyGuildMemberInfo );

			// 길드 가입 승인 메시지를 보낸다.
			Statement* pStmt = NULL;
			Result* pResult = NULL;
			
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
				pResult = pStmt->executeQuery( "SELECT Message FROM Messages WHERE Receiver = '%s'", pGuildMember->getName().c_str() );

				while ( pResult->next() )
				{
					GCSystemMessage gcSystemMessage;
					gcSystemMessage.setMessage( pResult->getString(1) );
					pPlayer->sendPacket( &gcSystemMessage );
				}

				pStmt->executeQuery( "DELETE FROM Messages WHERE Receiver = '%s'", pGuildMember->getName().c_str() );

				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

			// 주위에 길드 가입을 알린다.
			GCOtherModifyInfo gcOtherModifyInfo;
			gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
			gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pGuildMember->getGuildID() );

			pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo );
		}
		// 승인한 사람에게 메시지를 보낸다.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuildMember->getName() << "님의 길드 가입을 승인하였습니다.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_ACCEPT_TEAM_JOIN ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_ACCEPT_CLAN_JOIN ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_ACCEPT_CLAN_JOIN ), pGuildMember->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}
	else if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER &&
		 	pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
	{
		///////////////////////////////////////////////////////////
		// 길드 마스터를 변경한다.
		///////////////////////////////////////////////////////////

		string sMaster = pGuild->getMaster();

		// 길드마스터의 랭크를 새로 길드마스터가 되는 멤버의 원래 랭크로 바꿔준다.
		pGuild->modifyMemberRank( sMaster, pGuildMember->getRank() );
		// 새 길드마스터의 랭크를 세팅한다.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
		// 길드 오브젝트에 새 길드 마스트로 세팅한다.
		pGuild->setMaster( pGuildMember->getName() );

		// 접속해 있다면 메시지를 보낸다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		// 새 길드마스터가 게임서버에 있다면 새 정보를 보내준다.
		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			// 바뀐 길드 ID 정보를 보내준다.
			GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
			gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
			gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
			gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
			pPlayer->sendPacket( &gcModifyGuildMemberInfo );
		}

		// 원래의 길드마스터가 게임서버에 있다면 새 정보를 보내준다.
		pCreature = g_pPCFinder->getCreature_LOCKED( sMaster );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			// 바뀐 길드 ID 정보를 보내준다.
			GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
			gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
			gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
			gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
			pPlayer->sendPacket( &gcModifyGuildMemberInfo );
		}

		// 길마를 바꾼 사람에게 메시지를 보낸다.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuild->getName() << "의 마스터를 " << sMaster << " 에서 "
//				<< pGuildMember->getName() << " 으로 변경하였습니다.";

			char msg[200];
			sprintf( msg, g_pStringPool->c_str( STRID_MODIFY_GUILD_MASTER ),
							pGuild->getName().c_str(), sMaster.c_str(), pGuildMember->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}
	else
	{
		///////////////////////////////////////////////////////////
		// 길드멤버 정보를 변경한다.
		///////////////////////////////////////////////////////////
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );

		// 접속해 있다면 메시지를 보낸다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			GCSystemMessage gcSystemMessage;
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TEAM_RIGHT_CHANGED ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_RIGHT_CHANGED ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_RIGHT_CHANGED ) );

			pPlayer->sendPacket( &gcSystemMessage );
		}

		// 변경시킨 사람에게 메시지를 보낸다.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuildMember->getName() << "님의 길드 권한이 변경되었습니다.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_RIGHT_CHANGED_2 ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_RIGHT_CHANGED_2 ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_RIGHT_CHANGED_2 ), pGuildMember->getName().c_str() );


			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
