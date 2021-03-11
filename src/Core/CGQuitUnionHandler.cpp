//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitUnionHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitUnion.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Assert.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "GuildUnion.h"
	#include "Gpackets/GCGuildResponse.h"
	#include "DB.h"
    #include "Gpackets/GCModifyInformation.h"
    #include "Gpackets/GCOtherModifyInfo.h"
    #include "Gpackets/GCSystemMessage.h"
    #include "PacketUtil.h"
	#include "Guild.h"
	#include "PCFinder.h"
	#include "StringPool.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGQuitUnionHandler::execute (CGQuitUnion* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

//	//cout << "enter cgquitunionhandler::execute" << endl;
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
//		//cout << " out 1 " << endl;
		return;
	}

	uint	tempUnionID	= pUnion->getUnionID();


	// 요청한놈이 지가 속한 길드의 마스터인가? 
	if( !g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature )
		//|| pUnion->getMasterGuildID() != pPlayerCreature->getGuildID() 		
		)
	{
		// GC_GUILD_RESPONSE 날려준다.
		// 내용 : 길드 마스터가 아니자녀 -.-+

		gcGuildResponse.setCode(GuildUnionOfferManager::SOURCE_IS_NOT_MASTER);
		pPlayer->sendPacket(&gcGuildResponse);

		//cout << " out 2 " << endl;
		return;
	}

	//cout << "CGQuitUnion - Guild : " << pPacket->getGuildID() << ", Method : " << (int)pPacket->getQuitMethod() << endl;
	
	// 정상적으로 신청한다
	if( pPacket->getQuitMethod() == CGQuitUnion::QUIT_NORMAL )
	{
		uint result = GuildUnionOfferManager::Instance().offerQuit( pPlayerCreature->getGuildID() );

		gcGuildResponse.setCode(result);
		pPlayer->sendPacket(&gcGuildResponse);
		//cout << "normal send quit result : " << result << endl;
	}
	// 강제적으로 탈퇴한다
	else if( pPacket->getQuitMethod() == CGQuitUnion::QUIT_QUICK )
	{

		// 길드마스터의 마스터 아이디..
		string	TargetGuildMaster = g_pGuildManager->getGuild( pUnion->getMasterGuildID() )->getMaster();

		if( GuildUnionManager::Instance().removeGuild( pUnion->getUnionID(), pPlayerCreature->getGuildID() ) )
		{
			gcGuildResponse.setCode(GuildUnionOfferManager::OK);
			pPlayer->sendPacket(&gcGuildResponse);

			/* 10일간 다른연합에 가입하지 못하도록 패널티 처리한다. TODO
			 */
			 Statement* pStmt = NULL;
			 BEGIN_DB
			 {
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

				string escapeGuildName = g_pGuildManager->getGuildName(pPlayerCreature->getGuildID());
				string escapeGuildNotice = "[" + escapeGuildName + "] " + g_pStringPool->c_str( 378 );

					
				pStmt->executeQuery( "INSERT INTO Messages (Receiver, Message) values('%s','%s')", TargetGuildMaster.c_str(),  escapeGuildNotice.c_str());
				pStmt->executeQuery("INSERT INTO GuildUnionOffer values('%u','ESCAPE','%u',now())", tempUnionID, pPacket->getGuildID()  );

				// 연합맴버가 있는지 보자..없으면?
				Result *pResult = pStmt->executeQuery("SELECT count(*) FROM GuildUnionMember WHERE UnionID='%u'", tempUnionID );
				pResult->next();

				if(pResult->getInt(1) == 0)
				{
					//cout << "강제적으로 탈퇴를 한다..연합에 멤버가 없으므로 연합을..지워버린다 : unionid " << (int)tempUnionID << endl;
					pStmt->executeQuery("DELETE FROM GuildUnionInfo WHERE UnionID='%u'", tempUnionID );
					pStmt->executeQuery( "INSERT INTO Messages (Receiver, Message) values('%s','%s')", TargetGuildMaster.c_str(),  g_pStringPool->c_str(379));
					GuildUnionManager::Instance().reload();

					
				}

				
				SAFE_DELETE( pStmt );
			 }
			 END_DB(pStmt)

			Creature *pCreature = NULL;
			pCreature = pGamePlayer->getCreature();

			if(pCreature == NULL)   return;

			GCModifyInformation gcModifyInformation;
			makeGCModifyInfoGuildUnion(&gcModifyInformation, pCreature);

			pPlayer->sendPacket(&gcModifyInformation);
			
			
			Creature *pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))

			pTargetCreature = g_pPCFinder->getCreature_LOCKED(TargetGuildMaster);
			if (pTargetCreature==NULL)
			{
				g_pPCFinder->unlock();
				return;
			}
			GCModifyInformation gcModifyInformation2;
			makeGCModifyInfoGuildUnion(&gcModifyInformation2, pTargetCreature);
			pTargetCreature->getPlayer()->sendPacket(&gcModifyInformation2);

			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			//////////////////////////////


			sendGCOtherModifyInfoGuildUnion(pTargetCreature);
			sendGCOtherModifyInfoGuildUnion(pCreature);
		
			// 다른 서버에 있는 놈들에게 변경사항을 알린다.
    	    GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pTargetCreature)->getGuildID() );
        	GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pCreature)->getGuildID() );
	
			
			//cout << "quick send quit result : OK" << endl;
			
		}
		else
		{
			gcGuildResponse.setCode(GuildUnionOfferManager::NOT_YOUR_UNION);
			pPlayer->sendPacket(&gcGuildResponse);

			//cout << "quick quit failed " << endl;
		}
		
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

