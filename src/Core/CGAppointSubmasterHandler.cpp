//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAppointSubmasterHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAppointSubmaster.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Assert1.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Guild.h"
	#include "GuildUnion.h"
	#include "GuildManager.h"
	#include "GCGuildResponse.h"
	#include "GCSystemMessage.h"
	#include "GSModifyGuildMember.h"
	#include "SharedServerManager.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAppointSubmasterHandler::execute (CGAppointSubmaster* pPacket , Player* pPlayer)
	 throw(Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
    Assert(pGamePlayer != NULL);

    PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
    Assert(pPlayerCreature != NULL);

#ifdef __OLD_GUILD_WAR__
	GCSystemMessage gcSM;
	gcSM.setMessage("아직 지원되지 않는 기능입니다.");
	pGamePlayer->sendPacket(&gcSM);
	return;
#endif

	SYSTEM_ASSERT(SYSTEM_GUILD);

	if(!g_pGuildManager->isGuildMaster (pPacket->getGuildID(), pPlayerCreature ) )
	{
		// GC_GUILD_RESPONSE 날려준다. 
		// 내용 : 길드 마스터가 아니자녀 -.-+ 
		GCGuildResponse gcGR;
		gcGR.setCode(GuildUnionOfferManager::SOURCE_IS_NOT_MASTER);
		pPlayer->sendPacket(&gcGR);
		return;
	}

	GSModifyGuildMember gsMGM;

	gsMGM.setGuildID(pPacket->getGuildID());
	gsMGM.setName(pPacket->getName());
	gsMGM.setGuildMemberRank(GuildMember::GUILDMEMBER_RANK_SUBMASTER);
	gsMGM.setSender(pPlayerCreature->getName());

	g_pSharedServerManager->sendPacket(&gsMGM);

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

