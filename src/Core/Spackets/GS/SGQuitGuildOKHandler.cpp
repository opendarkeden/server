//----------------------------------------------------------------------
//
// Filename    : SGQuitGuildOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGQuitGuildOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "StringPool.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCOtherModifyInfo.h"

	#include <stdio.h>

#endif

//----------------------------------------------------------------------
// 
// SGQuitGuildOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGQuitGuildOKHandler::execute ( SGQuitGuildOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// 길드 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	string memberName = pGuildMember->getName();

	// 접속해 있다면 메시지를 보낸다.
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	Creature* pCreature = g_pPCFinder->getCreature_LOCKED( memberName );
	if ( pCreature != NULL && pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

		PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPlayerCreature != NULL );

		if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
		{
			////////////////////////////////////////////////////////////////////////////////
			// 활동 중인 길드 였다면 Slayer, Vampire 길드 아이디를 가입 안한 상태로 바꾼다.
			////////////////////////////////////////////////////////////////////////////////
			if ( pPlayerCreature->isSlayer() )
			{
				pPlayerCreature->setGuildID( 99 );		// 슬레이어의 가입안한 상태의 길드 ID

				// 클라이언트로 메시지를 보낸다.
				GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
				gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
				gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
				gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
				pPlayer->sendPacket( &gcModifyGuildMemberInfo );
			}
			else if ( pPlayerCreature->isVampire() )
			{
				pPlayerCreature->setGuildID( 0 );		// 뱀파이어의 가입안한 상태의 길드 ID

				// 클라이언트로 메시지를 보낸다.
				GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
				gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
				gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
				gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
				pPlayer->sendPacket( &gcModifyGuildMemberInfo );
			}
			else if ( pPlayerCreature->isOusters() )
			{
				pPlayerCreature->setGuildID( 66 );		// 아우스터즈의 가입안한 상태의 길드 ID

				// 클라이언트로 메시지를 보낸다.
				GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
				gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
				gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
				gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
				pPlayer->sendPacket( &gcModifyGuildMemberInfo );
			}
		}

		if ( pGuild->getState() == Guild::GUILD_STATE_WAIT && pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
		{
			///////////////////////////////////////////////////////////
			// 대기 중인 길드의 서브 마스터라면 등록비를 환불한다.
			///////////////////////////////////////////////////////////
			Gold_t Gold = pPlayerCreature->getGold();
			Gold = min( Gold + (uint)RETURN_SLAYER_SUBMASTER_GOLD, (long unsigned int)2000000000 );
			pPlayerCreature->setGoldEx( Gold );

			GCModifyInformation gcModifyInformation;
			gcModifyInformation.addLongData( MODIFY_GOLD, Gold );
			pPlayer->sendPacket( &gcModifyInformation );
		}

		// 길드 탈퇴 메시지를 보낸다.
		GCSystemMessage gcSystemMessage;
        if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
            gcSystemMessage.setMessage( g_pStringPool->getString( STRID_QUIT_TEAM ) );
        else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
            gcSystemMessage.setMessage( g_pStringPool->getString( STRID_QUIT_CLAN ) );
        else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
            gcSystemMessage.setMessage( g_pStringPool->getString( STRID_QUIT_CLAN ) );
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

	// 길드에서 삭제한다.
	pGuild->deleteMember( memberName );

	// 길드 마스터에게 메시지를 보낸다.
	pCreature = g_pPCFinder->getCreature_LOCKED( pGuild->getMaster() );
	if ( pCreature != NULL && pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer != NULL );

//		StringStream msg;
//		msg << memberName << "님이 길드를 탈퇴하였습니다.";

        char msg[100];
        if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
            sprintf( msg, g_pStringPool->c_str( STRID_QUIT_TEAM_2 ), memberName.c_str() );
        else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
            sprintf( msg, g_pStringPool->c_str( STRID_QUIT_CLAN_2 ), memberName.c_str() );
        else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
            sprintf( msg, g_pStringPool->c_str( STRID_QUIT_CLAN_2 ), memberName.c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg );
		pPlayer->sendPacket( &gcSystemMessage );
	}
	else
	{
		// 같은 서버에 길드 마스터가 없는 경우. how?
	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))


#endif
		
	__END_DEBUG_EX __END_CATCH
}
