//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExchangeBuy.cpp
// Written By  : Exchange System
// Description : Client requests to buy an item
//////////////////////////////////////////////////////////////////////////////

#include "CGExchangeBuy.h"
#include "GCExchangeBuy.h"

#include "PlayerCreature.h"
#include "../server/gameserver/exchange/ExchangeService.h"

void CGExchangeBuy::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    uint64_t listingID;
    iStream.read(listingID);
    m_ListingID = (int64_t)listingID;

    iStream.read(m_IdempotencyKey);

    __END_CATCH
}

void CGExchangeBuy::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    oStream.write((uint64_t)m_ListingID);
    oStream.write(m_IdempotencyKey);

    __END_CATCH
}

PacketSize_t CGExchangeBuy::getPacketSize() const {
    PacketSize_t size = 0;
    size += sizeof(m_ListingID);
    size += m_IdempotencyKey.size();
    return size;
}

string CGExchangeBuy::toString() const {
    StringStream msg;
    msg << "CGExchangeBuy("
        << "ListingID:" << (int)m_ListingID
        << ",IdempotencyKey:" << m_IdempotencyKey
        << ")";
    return msg.toString();
}

void CGExchangeBuy::execute(Player* pPlayer) {
    __BEGIN_TRY

    CGExchangeBuyHandler::execute(this, pPlayer);

    __END_CATCH
}
