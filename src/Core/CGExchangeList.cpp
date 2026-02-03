//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExchangeList.cpp
// Written By  : Exchange System
// Description : Client requests to browse exchange listings
//////////////////////////////////////////////////////////////////////////////

#include "CGExchangeList.h"
#include "GCExchangeList.h"

#include "PlayerCreature.h"

// Forward declaration of exchange service
#include "../server/gameserver/exchange/ExchangeService.h"

void CGExchangeList::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    iStream.read(m_Page);
    iStream.read(m_PageSize);
    iStream.read(m_ItemClass);
    iStream.read(m_ItemType);
    iStream.read(m_MinPrice);
    iStream.read(m_MaxPrice);

    // Read seller filter string
    uint8_t len;
    iStream.read(len);
    if (len > 0) {
        char buf[256];
        iStream.read(buf, len);
        buf[len] = '\0';
        m_SellerFilter = string(buf);
    }

    __END_CATCH
}

void CGExchangeList::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    oStream.write(m_Page);
    oStream.write(m_PageSize);
    oStream.write(m_ItemClass);
    oStream.write(m_ItemType);
    oStream.write(m_MinPrice);
    oStream.write(m_MaxPrice);

    // Write seller filter string
    uint8_t len = (uint8_t)m_SellerFilter.length();
    oStream.write(len);
    if (len > 0) oStream.write(m_SellerFilter.c_str(), len);

    __END_CATCH
}

PacketSize_t CGExchangeList::getPacketSize() const {
    PacketSize_t size = 0;
    size += sizeof(m_Page);
    size += sizeof(m_PageSize);
    size += sizeof(m_ItemClass);
    size += sizeof(m_ItemType);
    size += sizeof(m_MinPrice);
    size += sizeof(m_MaxPrice);
    size += sizeof(uint8_t); // seller filter length
    size += m_SellerFilter.length();
    return size;
}

string CGExchangeList::toString() const {
    StringStream msg;
    msg << "CGExchangeList("
        << "Page:" << (int)m_Page
        << ",PageSize:" << (int)m_PageSize
        << ",ItemClass:" << (int)m_ItemClass
        << ",ItemType:" << (int)m_ItemType
        << ",MinPrice:" << m_MinPrice
        << ",MaxPrice:" << m_MaxPrice
        << ",SellerFilter:" << m_SellerFilter
        << ")";
    return msg.toString();
}

void CGExchangeList::execute(Player* pPlayer) {
    __BEGIN_TRY

    CGExchangeListHandler::execute(this, pPlayer);

    __END_CATCH
}

