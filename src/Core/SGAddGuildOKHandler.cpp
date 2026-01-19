//----------------------------------------------------------------------
//
// Filename    : SGAddGuildOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "Properties.h"
#include "SGAddGuildOK.h"

#ifdef __GAME_SERVER__

#include "Creature.h"
#include "GCSystemMessage.h"
#include "Guild.h"
#include "GuildManager.h"
#include "PCFinder.h"
#include "Player.h"
#include "StringPool.h"

#endif

//----------------------------------------------------------------------
//
// SGAddGuildOKHandler::execute()
//
//----------------------------------------------------------------------
void SGAddGuildOKHandler::execute(SGAddGuildOK* pPacket)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

        // Allocate a new guild object
        Guild* pGuild = new Guild();
    pGuild->setID(pPacket->getGuildID());
    pGuild->setName(pPacket->getGuildName());
    pGuild->setRace(pPacket->getGuildRace());
    pGuild->setState(pPacket->getGuildState());
    pGuild->setServerGroupID(pPacket->getServerGroupID());
    pGuild->setZoneID(pPacket->getGuildZoneID());
    pGuild->setMaster(pPacket->getGuildMaster());
    pGuild->setIntro(pPacket->getGuildIntro());

    // Add to guild manager
    g_pGuildManager->addGuild(pGuild);

    // Notify guild master if online
    __ENTER_CRITICAL_SECTION((*g_pPCFinder))

    Creature* pCreature = g_pPCFinder->getCreature_LOCKED(pGuild->getMaster());
    if (pCreature != NULL && pCreature->isPC()) {
        Player* pPlayer = pCreature->getPlayer();
        Assert(pPlayer != NULL);

        GCSystemMessage gcSystemMessage;
        if (pGuild->getRace() == Guild::GUILD_RACE_SLAYER)
            gcSystemMessage.setMessage(g_pStringPool->getString(STRID_TEAM_REGISTERED));
        else if (pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE)
            gcSystemMessage.setMessage(g_pStringPool->getString(STRID_CLAN_REGISTERED));
        else if (pGuild->getRace() == Guild::GUILD_RACE_OUSTERS)
            gcSystemMessage.setMessage(g_pStringPool->getString(STRID_CLAN_REGISTERED));
        pPlayer->sendPacket(&gcSystemMessage);
    }

    __LEAVE_CRITICAL_SECTION((*g_pPCFinder))

    // cout << pGuild->toString() << endl;

#endif

    __END_DEBUG_EX __END_CATCH
}
