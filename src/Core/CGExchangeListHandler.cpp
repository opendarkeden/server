//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExchangeListHandler.cpp
// Written By  : Exchange System
// Description : Handler for CGExchangeList
//////////////////////////////////////////////////////////////////////////////

#include "CGExchangeList.h"
#include "GCExchangeList.h"

#ifdef __GAME_SERVER__
#include "PlayerCreature.h"
#include "GamePlayer.h"
#endif

// Forward declaration of exchange service
#include "../server/gameserver/exchange/ExchangeService.h"

void CGExchangeListHandler::execute(CGExchangeList* pPacket, Player* pPlayer) {
    __BEGIN_TRY

    // Validate player
    if (pPlayer == NULL) return;

    PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pPlayer);
    if (pPC == NULL) return;

    // Get server ID (TODO: implement getServerID in PlayerCreature)
    int16_t serverID = 1; // Default server ID

    // Get listings from service
    vector<ExchangeListing> listings = ExchangeService::getListings(
        serverID,
        pPacket->getPage(),
        pPacket->getPageSize(),
        pPacket->getItemClass(),
        pPacket->getItemType(),
        pPacket->getMinPrice(),
        pPacket->getMaxPrice()
    );

    // Send response
    GCExchangeList gcPacket;
    gcPacket.setListings(listings);
    gcPacket.setPage(pPacket->getPage());
    gcPacket.setPageSize(pPacket->getPageSize());
    gcPacket.setTotal(listings.size());

    pPlayer->sendPacket(&gcPacket);

    __END_CATCH
}
