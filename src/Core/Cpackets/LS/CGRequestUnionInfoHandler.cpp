//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestUnionInfoHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestUnionInfo.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Assert.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "GuildUnion.h"
	#include "Guild.h"
	#include "Gpackets/GCGuildResponse.h"
	#include "Gpackets/GCShowUnionInfo.h"
	#include "Gpackets/GCSystemMessage.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestUnionInfoHandler::execute (CGRequestUnionInfo* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>( pGamePlayer->getCreature() );
	Assert( pPlayerCreature != NULL );

#ifdef __OLD_GUILD_WAR__
	GCSystemMessage gcSM;
	gcSM.setMessage("뻘청唐역렴늪묘콘.");
	pGamePlayer->sendPacket( &gcSM );
	return;
#endif

	GCGuildResponse gcGuildResponse;
	
	GuildUnion	*pGuildUnion	= GuildUnionManager::Instance().getGuildUnion( pPlayerCreature->getGuildID() );
	// 자기가 속한 길드가 연합에 가입되어있는지 찾는다
	if (pGuildUnion == NULL)
	{
	
		gcGuildResponse.setCode(GuildUnionOfferManager::NOT_IN_UNION);
		pPlayer->sendPacket(&gcGuildResponse);

		return;
	}

	// Master 길드의 정보를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pGuildUnion->getMasterGuildID() );

	if (pGuild == NULL)
	{
		gcGuildResponse.setCode(GuildUnionOfferManager::NO_TARGET_UNION);
		pPlayer->sendPacket(&gcGuildResponse);
	
		return;
	}

	
	GCShowUnionInfo	gcShowUnionInfo;
	
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
	{
		
		gcShowUnionInfo.getMasterGuildInfo().setGuildID( pGuild->getID() );
		gcShowUnionInfo.getMasterGuildInfo().setGuildName( pGuild->getName() );
		gcShowUnionInfo.getMasterGuildInfo().setGuildState( pGuild->getState() );
		gcShowUnionInfo.getMasterGuildInfo().setGuildMaster( pGuild->getMaster() );
		gcShowUnionInfo.getMasterGuildInfo().setGuildMemberCount( pGuild->getActiveMemberCount() );
		gcShowUnionInfo.getMasterGuildInfo().setGuildIntro( pGuild->getIntro() );
		gcShowUnionInfo.getMasterGuildInfo().setJoinFee( 0 );
	}

	list<GuildID_t> gList = pGuildUnion->getGuildList();
	list<GuildID_t>::iterator itr = gList.begin();
	for ( ; itr != gList.end() ; ++itr )
    {

		Guild*	pGuild2	= g_pGuildManager->getGuild( *itr ); 
		if(pGuild2 != NULL)
		{
			SingleGuildInfo	*GuildInfo	= new SingleGuildInfo;
			
			GuildInfo->setGuildID( pGuild2->getID() );
			GuildInfo->setGuildName( pGuild2->getName() );
			GuildInfo->setGuildState( pGuild2->getState() );
			GuildInfo->setGuildMaster( pGuild2->getMaster() );
			GuildInfo->setGuildMemberCount( pGuild2->getActiveMemberCount() );
			GuildInfo->setGuildIntro( pGuild2->getIntro() );
			GuildInfo->setJoinFee( 0 );

			gcShowUnionInfo.addGuildInfoList(GuildInfo);
		}
    }
	
	pPlayer->sendPacket(&gcShowUnionInfo);
	
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

