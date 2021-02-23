//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyTaxRatioHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyTaxRatio.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "CastleInfoManager.h"
	#include "Gpackets/GCNPCResponse.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCSystemMessage.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGModifyTaxRatioHandler::execute (CGModifyTaxRatio* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

#ifdef __OLD_GUILD_WAR__
	GCSystemMessage gcSM;
	gcSM.setMessage("뻘청唐역렴늪묘콘.");
	pGamePlayer->sendPacket( &gcSM );
	return;
#endif

	GuildID_t guildID = pPC->getGuildID();

	list<CastleInfo*> pCastleInfoList = g_pCastleInfoManager->getGuildCastleInfos( guildID );
	if ( pCastleInfoList.empty() )
	{
		GCNPCResponse fail;
		fail.setCode( NPC_RESPONSE_MODIFY_TAX_RATIO_FAIL );

		pGamePlayer->sendPacket( &fail );
		return;
	}

	bool bOwner = false;
	list<CastleInfo*>::iterator itr = pCastleInfoList.begin();
	CastleInfo* pCastleInfo = NULL;
	for ( ; itr != pCastleInfoList.end() ; itr++ )
	{
		if ( (*itr)->getZoneID() == pPC->getZoneID() )
		{
			pCastleInfo = (*itr);
			bOwner = true;
			break;
		}
	}

	if ( !g_pGuildManager->isGuildMaster( guildID, pPC )	// 길드 마스터가 아니다.
		|| !bOwner											// 이 플레이어의 길드가 점령한 성이 아니다.
		|| pPacket->getRatio() > 10
	)
	{
		GCNPCResponse fail;
		fail.setCode( NPC_RESPONSE_MODIFY_TAX_RATIO_FAIL );

		pGamePlayer->sendPacket( &fail );
		return;
	}

	g_pCastleInfoManager->setItemTaxRatio( pPC->getZone(), pPacket->getRatio()+100 );
	GCNPCResponse ok;
	ok.setCode( NPC_RESPONSE_MODIFY_TAX_RATIO_OK );
	pGamePlayer->sendPacket( &ok );
	
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

