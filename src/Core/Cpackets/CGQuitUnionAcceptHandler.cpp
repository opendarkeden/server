//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitUnionAcceptHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitUnionAccept.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "GuildUnion.h"
	#include "Gpackets/GCGuildResponse.h"
    #include "DB.h"
    #include "StringPool.h"
    #include "Guild.h"

	#include "Gpackets/GCModifyInformation.h"
    #include "Gpackets/GCOtherModifyInfo.h"
    #include "Gpackets/GCSystemMessage.h"
    #include "PacketUtil.h"
	#include "PCFinder.h"
	#include "Exception.h"

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGQuitUnionAcceptHandler::execute (CGQuitUnionAccept* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
    Assert( pGamePlayer != NULL );

    PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
    Assert( pPlayerCreature != NULL );

#ifdef __OLD_GUILD_WAR__
	GCSystemMessage gcSM;
	gcSM.setMessage("뻘청唐역렴늪묘콘.");
	pGamePlayer->sendPacket( &gcSM );
	return;
#endif

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GCGuildResponse gcGuildResponse;

	GuildUnion *pUnion = GuildUnionManager::Instance().getGuildUnion( pPlayerCreature->getGuildID() );
	if(pUnion == NULL)
	{
		gcGuildResponse.setCode(GuildUnionOfferManager::NOT_IN_UNION);
		pPlayer->sendPacket(&gcGuildResponse);

		return;
	}
	
	// 요청한놈이 지가 속한 길드의 마스터인가? || 연합의 마스터길드가 내 길드가 맞나?
	if( !g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature )
		|| pUnion->getMasterGuildID() != pPlayerCreature->getGuildID() 		
		)
	{
		// GC_GUILD_RESPONSE 날려준다.
		// 내용 : 길드 마스터가 아니자녀 -.-+

		gcGuildResponse.setCode(GuildUnionOfferManager::SOURCE_IS_NOT_MASTER);
		pPlayer->sendPacket(&gcGuildResponse);

		return;
	}

	uint result = GuildUnionOfferManager::Instance().acceptQuit( pPacket->getGuildID() );

	gcGuildResponse.setCode(result);
	pPlayer->sendPacket(&gcGuildResponse);
////////////////////

	if(result == GuildUnionOfferManager::OK)
	{
	
		Guild*  pGuild  = g_pGuildManager->getGuild( pPacket->getGuildID() );

		if(pGuild == NULL)
		{
			return;
		}
		string  TargetGuildMaster = pGuild->getMaster();

		//cout << "연합탈퇴가 수락되었다. 통보받을 유저는 : " << TargetGuildMaster.c_str() << endl;


		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			pStmt->executeQuery( "INSERT INTO Messages (Receiver, Message) values('%s','%s')", TargetGuildMaster.c_str(),  g_pStringPool->c_str( 375 ));

			// 탈퇴수락한뒤에 나 혼자 남아있다면?
			Result *pResult = pStmt->executeQuery("SELECT count(*) FROM GuildUnionMember WHERE UnionID='%u'", pUnion->getUnionID() );
			pResult->next();

			if(pResult->getInt(1) == 0)
			{
				//cout << "연합탈퇴가 수락된후..남아있는 멤버가 없으면..연합장이면 안되니까..지워버린다" << endl;
				pStmt->executeQuery("DELETE FROM GuildUnionInfo WHERE UnionID='%u'", pUnion->getUnionID() );
				GuildUnionManager::Instance().reload();

			}
		
			
			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
		
		// 연합탈퇴하면 연합정보가 바뀌었을 수도 있다. 갱신된 정보를 다시 보내준다.
		Creature *pCreature = NULL;
		pCreature = pGamePlayer->getCreature();

		if(pCreature == NULL)   return;

		GCModifyInformation gcModifyInformation;
		makeGCModifyInfoGuildUnion(&gcModifyInformation, pCreature);

		pPlayer->sendPacket(&gcModifyInformation);

		// 통보받을 유저에게 길드Union정보를 다시 보낸다
		Creature *pTargetCreature = NULL;
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	    pTargetCreature = g_pPCFinder->getCreature_LOCKED(TargetGuildMaster);
    	if (pTargetCreature==NULL)
	    {
    	    g_pPCFinder->unlock();
        	return;
	    }
		GCModifyInformation gcModifyInformation;
        makeGCModifyInfoGuildUnion(&gcModifyInformation, pTargetCreature);
        pTargetCreature->getPlayer()->sendPacket(&gcModifyInformation);

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	
		sendGCOtherModifyInfoGuildUnion(pTargetCreature);
		sendGCOtherModifyInfoGuildUnion(pCreature);

		// 다른 서버에 있는 놈들에게 변경사항을 알린다.
        GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pTargetCreature)->getGuildID() );
        GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pCreature)->getGuildID() );
				
			
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

