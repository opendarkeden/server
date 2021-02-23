//----------------------------------------------------------------------
//
// Filename    : SGExpelGuildMemberOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGExpelGuildMemberOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "StringPool.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"

	#include <stdio.h>

#endif

//----------------------------------------------------------------------
// 
// SGExpelGuildMemberOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGExpelGuildMemberOKHandler::execute ( SGExpelGuildMemberOK* pPacket)
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << "SGExpelGuildMember received" << endl;

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }

	// 길드 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		//////////////////////////////////////////////////////////
		// 가입 취소
		//////////////////////////////////////////////////////////
		
		// 길드에서 삭제한다.
		pGuild->deleteMember( pGuildMember->getName() );

		// 접속해 있다면 메시지를 보낸다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuild->getName() << " 길드 가입신청이 취소되었습니다.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_JOIN_DENY ), pGuild->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY ), pGuild->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY ), pGuild->getName().c_str() );
			// 길드 가입신청취소 메시지를 보낸다.
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		// 취소시킨 사람에게 메시지를 보낸다.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pPacket->getName() << "님의 길드가입을 취소하였습니다.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_JOIN_DENY_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY_2 ), pPacket->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}
	else
	{
		///////////////////////////////////////////////////////////
		// 길드에서 추방한다.
		///////////////////////////////////////////////////////////

		// 길드에서 삭제한다.
		pGuild->deleteMember( pGuildMember->getName() );

		// 접속해 있다면 메시지를 보낸다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			if ( pPlayerCreature->isSlayer() )
			{
				pPlayerCreature->setGuildID( 99 );		// 슬레이어의 가입안한 상태의 길드 ID

				// 클라이언트에 길드 추방을 알린다.
				GCModifyGuildMemberInfo gcModifyGuildMember;
				gcModifyGuildMember.setGuildID( pPlayerCreature->getGuildID() );
				gcModifyGuildMember.setGuildName( "" );
				gcModifyGuildMember.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
				pPlayer->sendPacket( &gcModifyGuildMember );
			}
			else if ( pPlayerCreature->isVampire() )
			{
				pPlayerCreature->setGuildID( 0 );		// 뱀파이어의 가입안한 상태의 길드 ID

				// 클라이언트에 길드 추방을 알린다.
				GCModifyGuildMemberInfo gcModifyGuildMember;
				gcModifyGuildMember.setGuildID( pPlayerCreature->getGuildID() );
				gcModifyGuildMember.setGuildName( "" );
				gcModifyGuildMember.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
				pPlayer->sendPacket( &gcModifyGuildMember );
			}
			else if ( pPlayerCreature->isOusters() )
			{
				pPlayerCreature->setGuildID( 66 );		// 아우스터즈 가입안한 상태의 길드 ID

				// 클라이언트에 길드 추방을 알린다.
				GCModifyGuildMemberInfo gcModifyGuildMember;
				gcModifyGuildMember.setGuildID( pPlayerCreature->getGuildID() );
				gcModifyGuildMember.setGuildName( "" );
				gcModifyGuildMember.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
				pPlayer->sendPacket( &gcModifyGuildMember );
			}

			// 길드 추방 메시지를 보낸다.
			GCSystemMessage gcSystemMessage;
//			gcSystemMessage.setMessage( "길드에서 추방당했습니다." );

            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPEL_TEAM_MEMBER ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPEL_CLAN_MEMBER ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPEL_CLAN_MEMBER ) );

			pPlayer->sendPacket( &gcSystemMessage );

			if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
			{
				// 주위에 알린다.
				Zone* pZone = pCreature->getZone();
				Assert( pZone != NULL );

				GCOtherModifyInfo gcOtherModifyInfo;
				gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
				gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pPlayerCreature->getGuildID() );

				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo, pCreature );
			}
		}

		// 추방시킨 사람에게 메시지를 보낸다.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pPacket->getName() << "님을 길드에서 추방하였습니다.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_EXPEL_TEAM_MEMBER_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_EXPEL_CLAN_MEMBER_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_EXPEL_CLAN_MEMBER_2 ), pPacket->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
