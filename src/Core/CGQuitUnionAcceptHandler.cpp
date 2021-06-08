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
	#include "GCGuildResponse.h"
    #include "DB.h"
    #include "StringPool.h"
    #include "Guild.h"

	#include "GCModifyInformation.h"
    #include "GCOtherModifyInfo.h"
    #include "GCSystemMessage.h"
    #include "PacketUtil.h"
	#include "PCFinder.h"
	#include "Exception.h"

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGQuitUnionAcceptHandler::execute (CGQuitUnionAccept* pPacket , Player* pPlayer)
	 
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
	gcSM.setMessage("��û�п��Ŵ˹���.");
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
	
	// ��û�ѳ��� ���� ���� ����� �������ΰ�? || ������ �����ͱ�尡 �� ��尡 �³�?
	if( !g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature )
		|| pUnion->getMasterGuildID() != pPlayerCreature->getGuildID() 		
		)
	{
		// GC_GUILD_RESPONSE �����ش�.
		// ���� : ��� �����Ͱ� �ƴ��ڳ� -.-+

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

		//cout << "����Ż�� �����Ǿ���. �뺸���� ������ : " << TargetGuildMaster.c_str() << endl;


		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			pStmt->executeQuery( "INSERT INTO Messages (Receiver, Message) values('%s','%s')", TargetGuildMaster.c_str(),  g_pStringPool->c_str( 375 ));

			// Ż������ѵڿ� �� ȥ�� �����ִٸ�?
			Result *pResult = pStmt->executeQuery("SELECT count(*) FROM GuildUnionMember WHERE UnionID='%u'", pUnion->getUnionID() );
			pResult->next();

			if(pResult->getInt(1) == 0)
			{
				//cout << "����Ż�� ��������..�����ִ� ����� ������..�������̸� �ȵǴϱ�..����������" << endl;
				pStmt->executeQuery("DELETE FROM GuildUnionInfo WHERE UnionID='%u'", pUnion->getUnionID() );
				GuildUnionManager::Instance().reload();

			}
		
			
			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
		
		// ����Ż���ϸ� ���������� �ٲ���� ���� �ִ�. ���ŵ� ������ �ٽ� �����ش�.
		Creature *pCreature = NULL;
		pCreature = pGamePlayer->getCreature();

		if(pCreature == NULL)   return;

		GCModifyInformation gcModifyInformation;
		makeGCModifyInfoGuildUnion(&gcModifyInformation, pCreature);

		pPlayer->sendPacket(&gcModifyInformation);

		// �뺸���� �������� ���Union������ �ٽ� ������
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

		// �ٸ� ������ �ִ� ��鿡�� ��������� �˸���.
        GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pTargetCreature)->getGuildID() );
        GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pCreature)->getGuildID() );
				
			
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

