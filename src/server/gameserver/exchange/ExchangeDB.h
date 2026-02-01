//////////////////////////////////////////////////////////////////////////////
// Filename : ExchangeDB.h
// Written by : Exchange System
// Description : Database access layer for Exchange System
//////////////////////////////////////////////////////////////////////////////

#ifndef __EXCHANGE_DB_H__
#define __EXCHANGE_DB_H__

#include <string>
#include <vector>

#include "Types.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Data structures for Exchange
//////////////////////////////////////////////////////////////////////////////

// Listing status constants
const uint8_t LISTING_STATUS_ACTIVE = 0;
const uint8_t LISTING_STATUS_SOLD = 1;
const uint8_t LISTING_STATUS_CANCELLED = 2;
const uint8_t LISTING_STATUS_EXPIRED = 3;

// Order status constants
const uint8_t ORDER_STATUS_PAID = 0;
const uint8_t ORDER_STATUS_DELIVERED = 1;
const uint8_t ORDER_STATUS_CANCELLED = 2;

// Point transaction reason codes
const uint8_t POINT_REASON_BUY = 0;
const uint8_t POINT_REASON_SALE = 1;
const uint8_t POINT_REASON_TAX = 2;
const uint8_t POINT_REASON_REFUND = 3;
const uint8_t POINT_REASON_ADJUST = 4;

// Forward declaration (defined in GCExchangeList.h)
struct ExchangeListing;

struct ExchangeOrder {
    int64_t     orderID;
    int64_t     listingID;
    int16_t     serverID;
    string      buyerAccount;
    string      buyerPlayer;
    int         pricePoint;
    int         taxAmount;
    uint8_t     status;
    string      createdAt;
    string      deliveredAt;
    string      cancelledAt;
};

//////////////////////////////////////////////////////////////////////////////
// Exchange Database Access Layer
//////////////////////////////////////////////////////////////////////////////

class ExchangeDB {
public:
    //////////////////////////////////////////////////////////////////////////////
    // Listing operations
    //////////////////////////////////////////////////////////////////////////////

    // Create a new listing record
    static int64_t createListing(const ExchangeListing& listing);

    // Cancel a listing (mark as CANCELLED)
    static bool cancelListing(int64_t listingID);

    // Mark listing as expired
    static bool expireListing(int64_t listingID);

    // Mark listing as sold and set buyer info
    static bool markListingSold(int64_t listingID,
                               const string& buyerAccount,
                               const string& buyerPlayer);

    // Query listings with pagination and filters
    static vector<ExchangeListing> getListings(int16_t serverID,
                                               uint8_t status,
                                               int page,
                                               int pageSize);

    // Get a specific listing by ID
    static ExchangeListing* getListing(int64_t listingID);

    // Get seller's active listings
    static vector<ExchangeListing> getSellerListings(const string& sellerAccount,
                                                     uint8_t status);

    // Get expired listings (for maintenance scan)
    static vector<ExchangeListing> getExpiredListings();

    //////////////////////////////////////////////////////////////////////////////
    // Order operations
    //////////////////////////////////////////////////////////////////////////////

    // Create a new order
    static int64_t createOrder(const ExchangeOrder& order);

    // Mark order as delivered
    static bool markOrderDelivered(int64_t orderID);

    // Get buyer's orders
    static vector<ExchangeOrder> getBuyerOrders(const string& buyerPlayer,
                                                uint8_t status);

    // Get seller's fulfilled orders
    static vector<ExchangeOrder> getSellerOrders(const string& sellerPlayer,
                                                 uint8_t status);

    //////////////////////////////////////////////////////////////////////////////
    // Point operations (cross-database to USERINFO)
    //////////////////////////////////////////////////////////////////////////////

    // Adjust point balance with ledger record
    // Returns true on success, balanceAfter contains new balance
    static bool adjustPoints(const string& account,
                            int delta,
                            int& balanceAfter,
                            uint8_t reason,
                            int64_t refListingID,
                            int64_t refOrderID,
                            const string& idempotencyKey);

    // Get current point balance
    static int getPointBalance(const string& account);

    // Check if idempotency key exists
    static bool hasIdempotencyKey(const string& idempotencyKey);

    //////////////////////////////////////////////////////////////////////////////
    // Transaction helpers (cross-database)
    //////////////////////////////////////////////////////////////////////////////

    // Begin cross-database transaction
    static bool beginTransaction();

    // Commit transaction
    static bool commit();

    // Rollback transaction
    static bool rollback();
};

#endif // __EXCHANGE_DB_H__
