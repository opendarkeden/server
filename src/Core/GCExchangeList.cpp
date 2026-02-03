//////////////////////////////////////////////////////////////////////////////
// Filename    : GCExchangeList.cpp
// Written By  : Exchange System
// Description : Server sends listing list to client
//////////////////////////////////////////////////////////////////////////////

#include "GCExchangeList.h"

#include <string>

using namespace std;

// Stub execute() for server side (GC packets don't execute on server)
void GCExchangeList::execute(Player* pPlayer) {
    __BEGIN_TRY
    // Server doesn't execute GC packets
    __END_CATCH
}

void GCExchangeList::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    // Read page info
    iStream.read(m_Page);
    iStream.read(m_PageSize);
    iStream.read(m_Total);

    // Read listing count
    uint16_t count;
    iStream.read(count);

    // Read listings
    for (uint16_t i = 0; i < count; i++) {
        ExchangeListing listing;

        int64_t listingID;
        uint16_t serverID;
        uint8_t sellerRace, itemClass, currency, status, taxRate;
        uint16_t itemType;
        int pricePoint, taxAmount, objectID, version;

        iStream.read(listingID);
        iStream.read(serverID);

        // Strings need special handling
        char buf[256];
        uint8_t len;

        // SellerAccount
        iStream.read(len);
        iStream.read(buf, len);
        buf[len] = '\0';
        listing.sellerAccount = string(buf);

        // SellerPlayer
        iStream.read(len);
        iStream.read(buf, len);
        buf[len] = '\0';
        listing.sellerPlayer = string(buf);

        iStream.read(sellerRace);
        iStream.read(itemClass);
        iStream.read(itemType);
        iStream.read(listingID); // itemID
        iStream.read(objectID);
        iStream.read(pricePoint);
        iStream.read(currency);
        iStream.read(status);

        // BuyerAccount
        iStream.read(len);
        if (len > 0) {
            iStream.read(buf, len);
            buf[len] = '\0';
            listing.buyerAccount = string(buf);
        }

        // BuyerPlayer
        iStream.read(len);
        if (len > 0) {
            iStream.read(buf, len);
            buf[len] = '\0';
            listing.buyerPlayer = string(buf);
        }

        iStream.read(taxRate);
        iStream.read(taxAmount);

        // Timestamp strings
        iStream.read(len);
        if (len > 0) {
            iStream.read(buf, len);
            buf[len] = '\0';
            listing.createdAt = string(buf);
        }

        iStream.read(len);
        if (len > 0) {
            iStream.read(buf, len);
            buf[len] = '\0';
            listing.expireAt = string(buf);
        }

        iStream.read(version);

        // Snapshot fields
        // ItemName
        iStream.read(len);
        if (len > 0) {
            iStream.read(buf, len);
            buf[len] = '\0';
            listing.itemName = string(buf);
        }

        iStream.read(listing.enchantLevel);
        iStream.read(listing.grade);
        iStream.read(listing.durability);
        iStream.read(listing.silver);
        iStream.read(listing.optionType1);
        iStream.read(listing.optionType2);
        iStream.read(listing.optionType3);
        iStream.read(listing.optionValue1);
        iStream.read(listing.optionValue2);
        iStream.read(listing.optionValue3);
        iStream.read(listing.stackCount);

        m_Listings.push_back(listing);
    }

    __END_CATCH
}

void GCExchangeList::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    // Write page info
    oStream.write(m_Page);
    oStream.write(m_PageSize);
    oStream.write(m_Total);

    // Write listing count
    uint16_t count = (uint16_t)m_Listings.size();
    oStream.write(count);

    // Write listings
    for (const auto& listing : m_Listings) {
        // Write basic fields
        oStream.write((uint64_t)listing.listingID);
        oStream.write((uint16_t)listing.serverID);

        // Write strings with length prefix
        // SellerAccount
        uint8_t len = (uint8_t)listing.sellerAccount.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.sellerAccount.c_str(), len);

        // SellerPlayer
        len = (uint8_t)listing.sellerPlayer.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.sellerPlayer.c_str(), len);

        oStream.write(listing.sellerRace);
        oStream.write(listing.itemClass);
        oStream.write(listing.itemType);
        oStream.write((uint64_t)listing.itemID);
        oStream.write(listing.objectID);
        oStream.write(listing.pricePoint);
        oStream.write(listing.currency);
        oStream.write(listing.status);

        // BuyerAccount
        len = (uint8_t)listing.buyerAccount.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.buyerAccount.c_str(), len);

        // BuyerPlayer
        len = (uint8_t)listing.buyerPlayer.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.buyerPlayer.c_str(), len);

        oStream.write(listing.taxRate);
        oStream.write(listing.taxAmount);

        // Timestamp strings
        len = (uint8_t)listing.createdAt.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.createdAt.c_str(), len);

        len = (uint8_t)listing.expireAt.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.expireAt.c_str(), len);

        oStream.write(listing.version);

        // Snapshot fields
        len = (uint8_t)listing.itemName.length();
        oStream.write(len);
        if (len > 0) oStream.write(listing.itemName.c_str(), len);

        oStream.write(listing.enchantLevel);
        oStream.write(listing.grade);
        oStream.write(listing.durability);
        oStream.write(listing.silver);
        oStream.write(listing.optionType1);
        oStream.write(listing.optionType2);
        oStream.write(listing.optionType3);
        oStream.write(listing.optionValue1);
        oStream.write(listing.optionValue2);
        oStream.write(listing.optionValue3);
        oStream.write(listing.stackCount);
    }

    __END_CATCH
}

PacketSize_t GCExchangeList::getPacketSize() const {
    PacketSize_t size = 0;
    size += sizeof(m_Page);
    size += sizeof(m_PageSize);
    size += sizeof(m_Total);
    size += sizeof(uint16_t); // count

    for (const auto& listing : m_Listings) {
        size += sizeof(uint64_t); // listingID
        size += sizeof(uint16_t); // serverID
        size += sizeof(uint8_t) + listing.sellerAccount.length();
        size += sizeof(uint8_t) + listing.sellerPlayer.length();
        size += sizeof(listing.sellerRace);
        size += sizeof(listing.itemClass);
        size += sizeof(listing.itemType);
        size += sizeof(uint64_t); // itemID
        size += sizeof(listing.objectID);
        size += sizeof(listing.pricePoint);
        size += sizeof(listing.currency);
        size += sizeof(listing.status);
        size += sizeof(uint8_t) + listing.buyerAccount.length();
        size += sizeof(uint8_t) + listing.buyerPlayer.length();
        size += sizeof(listing.taxRate);
        size += sizeof(listing.taxAmount);
        size += sizeof(uint8_t) + listing.createdAt.length();
        size += sizeof(uint8_t) + listing.expireAt.length();
        size += sizeof(listing.version);
        size += sizeof(uint8_t) + listing.itemName.length();
        size += sizeof(listing.enchantLevel);
        size += sizeof(listing.grade);
        size += sizeof(listing.durability);
        size += sizeof(listing.silver);
        size += sizeof(listing.optionType1);
        size += sizeof(listing.optionType2);
        size += sizeof(listing.optionType3);
        size += sizeof(listing.optionValue1);
        size += sizeof(listing.optionValue2);
        size += sizeof(listing.optionValue3);
        size += sizeof(listing.stackCount);
    }

    return size;
}

string GCExchangeList::toString() const {
    StringStream msg;
    msg << "GCExchangeList("
        << "Page:" << m_Page
        << ",PageSize:" << m_PageSize
        << ",Total:" << m_Total
        << ",Count:" << m_Listings.size()
        << ")";
    return msg.toString();
}

void GCExchangeList::setListings(const vector<ExchangeListing>& listings) {
    m_Listings = listings;
}
