
//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitUnionDenyHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitUnionDeny.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "GuildUnion.h"
	#include "GCGuildResponse.h"
	#include "GCSystemMessage.h"
    #include "DB.h"
    #include "StringPool.h"
    #include "Guild.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGQuitUnionDenyHandler::execute (CGQuitUnionDeny* pPacket , Player* pPlayer)
	 
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

	uint result = GuildUnionOfferManager::Instance().denyQuit( pPacket->getGuildID() );

	gcGuildResponse.setCode(result);
	pPlayer->sendPacket(&gcGuildResponse);

////////////////////

	Guild*  pGuild  = g_pGuildManager->getGuild( pPacket->getGuildID() );

    if(pGuild == NULL)
    {
        return;
    }
    string  TargetGuildMaster = pGuild->getMaster();

    //cout << "Ż�� �źεǾ���. �뺸���� ������ : " << TargetGuildMaster.c_str() << endl;


    Statement* pStmt = NULL;

    BEGIN_DB
    {
        pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
        pStmt->executeQuery( "INSERT INTO Messages (Receiver, Message) values('%s','%s')", TargetGuildMaster.c_str(),  g_pStringPool->c_str( 376 ));
        SAFE_DELETE( pStmt );
    }
    END_DB(pStmt)

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

