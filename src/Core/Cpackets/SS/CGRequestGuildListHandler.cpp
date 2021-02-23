//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestGuildListHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestGuildList.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Guild.h"
#include "GuildManager.h"
#include "GuildInfo.h"
#include "Gpackets/GCWaitGuildList.h"
#include "Gpackets/GCActiveGuildList.h"
#include "Gpackets/GCSystemMessage.h"


#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "Assert.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestGuildListHandler::execute (CGRequestGuildList* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT(SYSTEM_GUILD);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

#ifdef __OLD_GUILD_WAR__
	GCSystemMessage gcSM;
	gcSM.setMessage("还没有开放此功能.");
	pGamePlayer->sendPacket( &gcSM );
	return;
#endif

	GuildType_t	tmpGuildType	= pPacket->getGuildType();

	// 措扁辨靛 捞搁
	if ( tmpGuildType == CGRequestGuildList::GUILDTYPE_WAIT )
	{
		GCWaitGuildList gcWaitGuildList;

		GuildRace_t	race;
		if ( pCreature->isSlayer() )
			race = Guild::GUILD_RACE_SLAYER;
		else if ( pCreature->isVampire() )
			race = Guild::GUILD_RACE_VAMPIRE;
		else if ( pCreature->isOusters() )
			race = Guild::GUILD_RACE_OUSTERS;
		else
			return;

		g_pGuildManager->makeWaitGuildList( gcWaitGuildList, race );

		pPlayer->sendPacket( &gcWaitGuildList );

	}
	// 老馆辨靛 捞搁
	else if( tmpGuildType == CGRequestGuildList::GUILDTYPE_NORMAL )
	{
		GCActiveGuildList gcActiveGuildList;

		GuildRace_t race;

		if ( pCreature->isSlayer() )
			race = Guild::GUILD_RACE_SLAYER;
		else if ( pCreature->isVampire() )
			race = Guild::GUILD_RACE_VAMPIRE;
		else if ( pCreature->isOusters() )
			race = Guild::GUILD_RACE_OUSTERS;
		else
			return;

		g_pGuildManager->makeActiveGuildList( gcActiveGuildList, race );

		pPlayer->sendPacket( &gcActiveGuildList );

	}
	else
	{
		return;
	}


	
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

