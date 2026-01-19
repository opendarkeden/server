//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMoveHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGMove.h"

#ifdef __GAME_SERVER__
#include "Effect.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Timeval.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "skill/Sniping.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGMoveHandler::execute(CGMove* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

        Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

    if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) {
        // In this state the creature should already be placed and loaded, so it must not be NULL.
        // PLAYER_INGAME means the zone has finished loading.
        Creature* pCreature = pGamePlayer->getCreature();
        Assert(pCreature != NULL);

        if (pCreature->isDead())
            return;

        // If the player is moving while being searched or relocating, the zone pointer can be NULL
        // due to incomplete initialization; in that case the server may still receive CGMove.
        // Guard against it here.
        if (pCreature->getZone() == NULL)
            return;

        Zone* pZone = pCreature->getZone();
        Assert(pZone != NULL);

        if (pCreature->isSlayer() && pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) {
            g_Sniping.checkRevealRatio(pCreature, 10, 20);
        }

        // For some PCs, movement processing needs to notify other PCs nearby. CGMove includes
        // the new coordinates, so simply validate and relay them.
        pZone->movePC(pCreature, pPacket->getX(), pPacket->getY(), pPacket->getDir());
    }

#endif

    __END_DEBUG_EX __END_CATCH
}
