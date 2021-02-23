//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestUnionHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestUnion.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "GuildUnion.h"
	#include "Gpackets/GCGuildResponse.h"
	#include "PCFinder.h"
	#include "Exception.h"
	#include "Guild.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "PacketUtil.h"

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestUnionHandler::execute (CGRequestUnion* pPacket , Player* pPlayer)
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

	GCGuildResponse	gcGuildResponse;

	// 요청한놈이 지가 속한 길드의 마스터인가?
	if( !g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature ) )
	{
		// GC_GUILD_RESPONSE 날려준다. 
		// 내용 : 길드 마스터가 아니자녀 -.-+ 

		gcGuildResponse.setCode(GuildUnionOfferManager::SOURCE_IS_NOT_MASTER);	
		pPlayer->sendPacket(&gcGuildResponse);
		return;
	}

	uint result = GuildUnionOfferManager::Instance().offerJoin( pPlayerCreature->getGuildID(), pPacket->getGuildID() );

	gcGuildResponse.setCode(result);
	pPlayer->sendPacket(&gcGuildResponse);

    if(result == GuildUnionOfferManager::OK)
    {

		// 상대길드의 장이름을 구해서..찾아야 겠다.
		Guild *pGuild = g_pGuildManager->getGuild(pPacket->getGuildID());
		
		if(pGuild != NULL)
		{

			string targetGuildMaster = pGuild->getMaster();	
			
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			
			Creature *pCreature = g_pPCFinder->getCreature_LOCKED( targetGuildMaster );
			if(pCreature != NULL)
			{

				GCModifyInformation gcModifyInformation;
				makeGCModifyInfoGuildUnion(&gcModifyInformation, pCreature);
				pCreature->getPlayer()->sendPacket(&gcModifyInformation);

			}

			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
		}
	}
					
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

