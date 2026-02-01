//////////////////////////////////////////////////////////////////////////////
// Filename    : GCExchangeBuy.cpp
// Written By  : Exchange System
// Description : Server responds to buy request
//////////////////////////////////////////////////////////////////////////////

#include "GCExchangeBuy.h"

// Stub execute() for server side (GC packets don't execute on server)
void GCExchangeBuy::execute(Player* pPlayer) {
    __BEGIN_TRY
    // Server doesn't execute GC packets
    __END_CATCH
}

void GCExchangeBuy::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    uint8_t success;
    iStream.read(success);
    m_Success = (success != 0);

    iStream.read(m_Message);

    uint64_t orderID;
    iStream.read(orderID);
    m_OrderID = (int64_t)orderID;

    __END_CATCH
}

void GCExchangeBuy::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    oStream.write((uint8_t)m_Success);
    oStream.write(m_Message);
    oStream.write((uint64_t)m_OrderID);

    __END_CATCH
}

PacketSize_t GCExchangeBuy::getPacketSize() const {
    PacketSize_t size = 0;
    size += sizeof(uint8_t);
    size += m_Message.size();
    size += sizeof(m_OrderID);
    return size;
}

string GCExchangeBuy::toString() const {
    StringStream msg;
    msg << "GCExchangeBuy("
        << "Success:" << (m_Success ? "true" : "false")
        << ",Message:" << m_Message
        << ",OrderID:" << (int)m_OrderID
        << ")";
    return msg.toString();
}
