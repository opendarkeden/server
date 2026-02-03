//////////////////////////////////////////////////////////////////////////////
// Filename : ExchangeService.h
// Written by : Exchange System
// Description : Core business logic service for Exchange System
//////////////////////////////////////////////////////////////////////////////

#ifndef __EXCHANGE_SERVICE_H__
#define __EXCHANGE_SERVICE_H__

#include "ExchangeDB.h"
#include <string>
#include <vector>

using namespace std;

class PlayerCreature;
class Item;

//////////////////////////////////////////////////////////////////////////////
// Exchange Result Codes
//////////////////////////////////////////////////////////////////////////////

enum ExchangeResult {
    EXCHANGE_SUCCESS,
    EXCHANGE_FAIL_ITEM_NOT_FOUND,
    EXCHANGE_FAIL_ITEM_OWNERSHIP,
    EXCHANGE_FAIL_ITEM_TRADEABLE,
    EXCHANGE_FAIL_INVALID_PRICE,
    EXCHANGE_FAIL_INSUFFICIENT_POINTS,
    EXCHANGE_FAIL_LISTING_NOT_FOUND,
    EXCHANGE_FAIL_LISTING_NOT_AVAILABLE,
    EXCHANGE_FAIL_INVENTORY_FULL,
    EXCHANGE_FAIL_STORAGE_FULL,
    EXCHANGE_FAIL_NOT_SELLER,
    EXCHANGE_FAIL_NOT_BUYER,
    EXCHANGE_FAIL_ALREADY_CLAIMED,
    EXCHANGE_FAIL_DATABASE_ERROR,
    EXCHANGE_FAIL_TRANSACTION_ERROR,
    EXCHANGE_FAIL_IDEMPOTENCY_CONFLICT,
    EXCHANGE_FAIL_UNKNOWN
};

//////////////////////////////////////////////////////////////////////////////
// Exchange Claim Info
//////////////////////////////////////////////////////////////////////////////

struct ExchangeClaim {
    int64_t     id;             // OrderID for buyer, ListingID for seller
    string      itemName;       // Item name for display
    int         pricePoint;
    uint8_t     type;           // 0=buyer claim, 1=seller claim
    uint8_t     status;         // Order status or Listing status
};

//////////////////////////////////////////////////////////////////////////////
// Exchange Service
//////////////////////////////////////////////////////////////////////////////

class ExchangeService {
public:
    // Status constants
    static const uint8_t LISTING_STATUS_ACTIVE     = 0;
    static const uint8_t LISTING_STATUS_SOLD       = 1;
    static const uint8_t LISTING_STATUS_CANCELLED  = 2;
    static const uint8_t LISTING_STATUS_EXPIRED    = 3;

    static const uint8_t ORDER_STATUS_PAID         = 0;
    static const uint8_t ORDER_STATUS_DELIVERED    = 1;
    static const uint8_t ORDER_STATUS_CANCELLED    = 2;

    // Point ledger reasons
    static const uint8_t POINT_REASON_BUY          = 0;
    static const uint8_t POINT_REASON_SALE         = 1;
    static const uint8_t POINT_REASON_TAX          = 2;
    static const uint8_t POINT_REASON_REFUND       = 3;
    static const uint8_t POINT_REASON_ADJUST       = 4;

    ////////////////////////////////////////////////////////////////////
    // Browse operations
    ////////////////////////////////////////////////////////////////////

    // Get listings with pagination and filters
    static vector<ExchangeListing> getListings(
        int16_t serverID,
        int page = 1,
        int pageSize = 20,
        uint8_t itemClass = 0xFF,
        uint16_t itemType = 0xFFFF,
        int minPrice = 0,
        int maxPrice = 0,
        const string& sellerFilter = ""
    );

    // Get total count matching filters
    static int getListingsCount(
        int16_t serverID,
        uint8_t itemClass = 0xFF,
        uint16_t itemType = 0xFFFF,
        int minPrice = 0,
        int maxPrice = 0,
        const string& sellerFilter = ""
    );

    // Get specific listing
    static ExchangeListing* getListing(int64_t listingID);

    ////////////////////////////////////////////////////////////////////
    // Listing operations
    ////////////////////////////////////////////////////////////////////

    // Create a new listing
    // Returns: <success, errorMessage or listingID as string>
    static pair<bool, string> createListing(
        PlayerCreature* pSeller,
        Item* pItem,
        int pricePoint,
        int durationHours = 72
    );

    // Cancel a listing
    // Returns: <success, errorMessage>
    static pair<bool, string> cancelListing(
        PlayerCreature* pSeller,
        int64_t listingID
    );

    // Get seller's listings
    static vector<ExchangeListing> getSellerListings(
        const string& sellerAccount,
        uint8_t status = LISTING_STATUS_ACTIVE
    );

    ////////////////////////////////////////////////////////////////////
    // Buying operations
    ////////////////////////////////////////////////////////////////////

    // Buy a listing
    // Returns: <success, errorMessage or orderID as string>
    static pair<bool, string> buyListing(
        PlayerCreature* pBuyer,
        int64_t listingID,
        const string& idempotencyKey
    );

    // Get buyer's orders
    static vector<ExchangeOrder> getBuyerOrders(
        const string& buyerPlayer,
        uint8_t status = ORDER_STATUS_PAID
    );

    // Get seller's fulfilled orders
    static vector<ExchangeOrder> getSellerOrders(
        const string& sellerPlayer,
        uint8_t status = ORDER_STATUS_DELIVERED
    );

    ////////////////////////////////////////////////////////////////////
    // Claim operations
    ////////////////////////////////////////////////////////////////////

    // Prepare claim list for a player (both buyer and seller items)
    static vector<ExchangeClaim> prepareClaimList(PlayerCreature* pPlayer);

    // Claim item (for buyer: deliver order, for seller: return cancelled item)
    // Returns: <success, errorMessage>
    static pair<bool, string> claimItem(
        PlayerCreature* pPlayer,
        int64_t orderOrListingID,
        bool isBuyerClaim
    );

    ////////////////////////////////////////////////////////////////////
    // Point operations
    ////////////////////////////////////////////////////////////////////

    // Get point balance
    static int getPointBalance(const string& account);

    // Adjust points with ledger record
    // Returns: <success, newBalance or -1 if failed>
    static pair<bool, int> adjustPoints(
        const string& account,
        int delta,
        uint8_t reason,
        int64_t refListingID = 0,
        int64_t refOrderID = 0,
        const string& idempotencyKey = ""
    );

    ////////////////////////////////////////////////////////////////////
    // Maintenance operations
    ////////////////////////////////////////////////////////////////////

    // Scan and expire listings
    static void scanExpiredListings();

    ////////////////////////////////////////////////////////////////////
    // Configuration
    ////////////////////////////////////////////////////////////////////

    static void setTaxRate(uint8_t rate) { m_TaxRate = rate; }
    static uint8_t getTaxRate() { return m_TaxRate; }

    static void setListingDuration(int days) { m_ListingDurationDays = days; }
    static int getListingDuration() { return m_ListingDurationDays; }

private:
    ////////////////////////////////////////////////////////////////////
    // Helper methods
    ////////////////////////////////////////////////////////////////////

    // Calculate tax amount
    static int calculateTax(int price);

    // Get current timestamp string
    static string getCurrentTimestamp();

    // Move item to exchange storage
    static bool moveItemToExchangeStorage(PlayerCreature* pPlayer, Item* pItem);

    // Move item from exchange storage to player
    static bool moveItemFromExchangeStorage(
        PlayerCreature* pPlayer,
        int64_t listingID,
        Item* pItem
    );

    // Create item snapshot for UI display
    static void createItemSnapshot(Item* pItem, ExchangeListing& listing);

    // Generate idempotency key
    static string generateIdempotencyKey();

    // Get server ID
    static int16_t getServerID();

    // Check if inventory has space
    static bool checkInventorySpace(PlayerCreature* pPlayer);

    // Format error message
    static string formatError(ExchangeResult code, const string& detail = "");

    // Static configuration
    static uint8_t m_TaxRate;
    static int m_ListingDurationDays;
};

#endif // __EXCHANGE_SERVICE_H__
