//////////////////////////////////////////////////////////////////////////////
// Filename : ExchangeService.cpp
// Written by : Exchange System
// Description : Core business logic service for Exchange System
//////////////////////////////////////////////////////////////////////////////

#include "ExchangeService.h"
#include "GCExchangeList.h"  // For ExchangeListing definition

#include "Item.h"
#include "ItemUtil.h"
#include "PlayerCreature.h"
#include "Inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Static members
//////////////////////////////////////////////////////////////////////////////

uint8_t ExchangeService::m_TaxRate = 8;  // Default 8% tax
int ExchangeService::m_ListingDurationDays = 3;  // Default 3 days

//////////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////////

namespace {
    string _getCurrentTime() {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
        return string(buf);
    }

    string _addHoursToNow(int hours) {
        time_t now = time(NULL);
        now += hours * 3600;
        struct tm* t = localtime(&now);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
        return string(buf);
    }

    string _toInt64String(int64_t value) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%lld", (long long)value);
        return string(buf);
    }

    // Generate unique idempotency key
    string _generateIdempotencyKey() {
        static long counter = 0;
        time_t now = time(NULL);
        char buf[128];
        snprintf(buf, sizeof(buf), "EX_%ld_%ld", (long)now, (long)counter++);
        return string(buf);
    }

    int16_t _getServerID() {
        // TODO: Get actual server ID from configuration
        // For now, return a default value
        return 1;
    }

    // Check if player has inventory space
    bool _checkInventorySpace(PlayerCreature* pPlayer) {
        if (!pPlayer) return false;

        Inventory* pInv = pPlayer->getInventory();
        if (!pInv) return false;

        // Check if inventory has at least one empty slot
        // This is a simplified check - should be more thorough
        return pInv->getItemNum() < (pInv->getWidth() * pInv->getHeight());
    }
}

//////////////////////////////////////////////////////////////////////////////
// Browse operations
//////////////////////////////////////////////////////////////////////////////

vector<ExchangeListing> ExchangeService::getListings(
    int16_t serverID,
    int page,
    int pageSize,
    uint8_t itemClass,
    uint16_t itemType,
    int minPrice,
    int maxPrice,
    const string& sellerFilter
) {
    // For now, use the basic DB function
    // In production, we'd want to add filtering at DB level for performance
    vector<ExchangeListing> allListings = ExchangeDB::getListings(
        serverID,
        LISTING_STATUS_ACTIVE,
        page,
        pageSize
    );

    // Apply additional filters (in-memory for now)
    vector<ExchangeListing> filtered;
    for (const auto& listing : allListings) {
        if (itemClass != 0xFF && listing.itemClass != itemClass) continue;
        if (itemType != 0xFFFF && listing.itemType != itemType) continue;
        if (minPrice > 0 && listing.pricePoint < minPrice) continue;
        if (maxPrice > 0 && listing.pricePoint > maxPrice) continue;
        if (!sellerFilter.empty() && listing.sellerPlayer.find(sellerFilter) == string::npos) continue;

        filtered.push_back(listing);
    }

    return filtered;
}

int ExchangeService::getListingsCount(
    int16_t serverID,
    uint8_t itemClass,
    uint16_t itemType,
    int minPrice,
    int maxPrice,
    const string& sellerFilter
) {
    // For accurate count, we need a DB query
    // For now, return a placeholder
    vector<ExchangeListing> listings = getListings(
        serverID, 1, 1000,  // Get max results
        itemClass, itemType, minPrice, maxPrice, sellerFilter
    );
    return listings.size();
}

ExchangeListing* ExchangeService::getListing(int64_t listingID) {
    return ExchangeDB::getListing(listingID);
}

//////////////////////////////////////////////////////////////////////////////
// Listing operations
//////////////////////////////////////////////////////////////////////////////

pair<bool, string> ExchangeService::createListing(
    PlayerCreature* pSeller,
    Item* pItem,
    int pricePoint,
    int durationHours
) {
    // Validate inputs
    if (!pSeller) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_NOT_FOUND));
    }
    if (!pItem) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_NOT_FOUND));
    }
    if (pricePoint < 1) {
        return make_pair(false, formatError(EXCHANGE_FAIL_INVALID_PRICE));
    }

    // Get player info
    string account = pSeller->getName();  // Using name as account identifier
    string playerName = pSeller->getName();
    uint8_t race = 0;  // TODO: Get actual race from PlayerCreature

    // Verify item ownership
    Inventory* pInv = pSeller->getInventory();
    if (!pInv || !pInv->hasItem(pItem->getObjectID())) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_OWNERSHIP));
    }

    // Check if item is tradeable
    if (!canTrade(pItem)) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_TRADEABLE));
    }

    // Check exchange storage has space (conceptually - items stored by DB)
    // In this implementation, items remain in DB with STORAGE_EXCHANGE flag

    // Calculate expiration
    string createdAt = _getCurrentTime();
    string expireAt = _addHoursToNow(durationHours);

    // Create listing record
    ExchangeListing listing;
    listing.listingID = 0;  // Will be set by DB auto-increment
    listing.serverID = _getServerID();
    listing.sellerAccount = account;
    listing.sellerPlayer = playerName;
    listing.sellerRace = race;
    listing.itemClass = pItem->getItemClass();
    listing.itemType = pItem->getItemType();
    listing.itemID = 0;  // TODO: Get ItemID from Item
    listing.objectID = pItem->getObjectID();
    listing.pricePoint = pricePoint;
    listing.currency = 0;  // 0 = points
    listing.status = LISTING_STATUS_ACTIVE;
    listing.buyerAccount = "";
    listing.buyerPlayer = "";
    listing.taxRate = m_TaxRate;
    listing.taxAmount = 0;
    listing.createdAt = createdAt;
    listing.expireAt = expireAt;
    listing.soldAt = "";
    listing.cancelledAt = "";
    listing.updatedAt = createdAt;
    listing.version = 0;

    // Create item snapshot
    createItemSnapshot(pItem, listing);

    // Save to database
    int64_t listingID = ExchangeDB::createListing(listing);
    if (listingID <= 0) {
        return make_pair(false, formatError(EXCHANGE_FAIL_DATABASE_ERROR));
    }

    // Move item to exchange storage
    // Note: The item will be saved with STORAGE_EXCHANGE type
    if (!moveItemToExchangeStorage(pSeller, pItem)) {
        // Rollback listing creation
        ExchangeDB::cancelListing(listingID);
        return make_pair(false, formatError(EXCHANGE_FAIL_STORAGE_FULL));
    }

    return make_pair(true, _toInt64String(listingID));
}

pair<bool, string> ExchangeService::cancelListing(
    PlayerCreature* pSeller,
    int64_t listingID
) {
    if (!pSeller) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_NOT_FOUND));
    }

    // Get listing
    ExchangeListing* pListing = ExchangeDB::getListing(listingID);
    if (!pListing) {
        return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_FOUND));
    }

    // Verify ownership
    string playerName = pSeller->getName();
    if (pListing->sellerPlayer != playerName) {
        return make_pair(false, formatError(EXCHANGE_FAIL_NOT_SELLER));
    }

    // Check status
    if (pListing->status != LISTING_STATUS_ACTIVE) {
        return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_AVAILABLE));
    }

    // Mark as cancelled in DB
    if (!ExchangeDB::cancelListing(listingID)) {
        return make_pair(false, formatError(EXCHANGE_FAIL_DATABASE_ERROR));
    }

    // Note: Item remains in exchange storage until claimed
    // Seller needs to claim the item back

    return make_pair(true, "");
}

vector<ExchangeListing> ExchangeService::getSellerListings(
    const string& sellerAccount,
    uint8_t status
) {
    return ExchangeDB::getSellerListings(sellerAccount, status);
}

//////////////////////////////////////////////////////////////////////////////
// Buying operations
//////////////////////////////////////////////////////////////////////////////

pair<bool, string> ExchangeService::buyListing(
    PlayerCreature* pBuyer,
    int64_t listingID,
    const string& idempotencyKey
) {
    if (!pBuyer) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_NOT_FOUND));
    }

    // Check idempotency
    if (!idempotencyKey.empty() && ExchangeDB::hasIdempotencyKey(idempotencyKey)) {
        return make_pair(false, formatError(EXCHANGE_FAIL_IDEMPOTENCY_CONFLICT));
    }

    // Get listing
    ExchangeListing* pListing = ExchangeDB::getListing(listingID);
    if (!pListing) {
        return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_FOUND));
    }

    // Verify listing status
    if (pListing->status != LISTING_STATUS_ACTIVE) {
        return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_AVAILABLE));
    }

    // Verify server ID
    if (pListing->serverID != _getServerID()) {
        return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_AVAILABLE));
    }

    // Check expiration
    // (DB should handle this, but double-check)
    // TODO: Parse expireAt and compare with current time

    // Get buyer info
    string buyerAccount = pBuyer->getName();
    string buyerPlayer = pBuyer->getName();

    // Verify not buying own listing
    if (pListing->sellerPlayer == buyerPlayer) {
        return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_AVAILABLE));
    }

    int price = pListing->pricePoint;
    int tax = calculateTax(price);
    int totalCost = price + tax;

    // Check buyer balance
    int buyerBalance = ExchangeDB::getPointBalance(buyerAccount);
    if (buyerBalance < totalCost) {
        return make_pair(false, formatError(EXCHANGE_FAIL_INSUFFICIENT_POINTS));
    }

    // Begin transaction
    if (!ExchangeDB::beginTransaction()) {
        return make_pair(false, formatError(EXCHANGE_FAIL_TRANSACTION_ERROR));
    }

    string autoKey = idempotencyKey.empty() ? _generateIdempotencyKey() : idempotencyKey;

    try {
        // Deduct points from buyer
        int buyerBalanceAfter;
        if (!ExchangeDB::adjustPoints(
            buyerAccount,
            -totalCost,
            buyerBalanceAfter,
            POINT_REASON_BUY,
            listingID,
            0,
            autoKey + "_buy"
        )) {
            throw string("Failed to deduct buyer points");
        }

        // Add points to seller (after tax)
        int sellerIncome = price - tax;
        int sellerBalanceAfter;
        if (!ExchangeDB::adjustPoints(
            pListing->sellerAccount,
            sellerIncome,
            sellerBalanceAfter,
            POINT_REASON_SALE,
            listingID,
            0,
            autoKey + "_sale"
        )) {
            throw string("Failed to add seller points");
        }

        // Create order
        ExchangeOrder order;
        order.orderID = 0;
        order.listingID = listingID;
        order.serverID = getServerID();
        order.buyerAccount = buyerAccount;
        order.buyerPlayer = buyerPlayer;
        order.pricePoint = price;
        order.taxAmount = tax;
        order.status = ORDER_STATUS_PAID;
        order.createdAt = _getCurrentTime();
        order.deliveredAt = "";
        order.cancelledAt = "";

        int64_t orderID = ExchangeDB::createOrder(order);
        if (orderID <= 0) {
            throw string("Failed to create order");
        }

        // Mark listing as sold
        if (!ExchangeDB::markListingSold(listingID, buyerAccount, buyerPlayer)) {
            throw string("Failed to mark listing sold");
        }

        // Commit transaction
        if (!ExchangeDB::commit()) {
            throw string("Failed to commit transaction");
        }

        return make_pair(true, _toInt64String(orderID));

    } catch (const string& error) {
        // Rollback on error
        ExchangeDB::rollback();
        return make_pair(false, formatError(EXCHANGE_FAIL_TRANSACTION_ERROR, error));
    }
}

vector<ExchangeOrder> ExchangeService::getBuyerOrders(
    const string& buyerPlayer,
    uint8_t status
) {
    return ExchangeDB::getBuyerOrders(buyerPlayer, status);
}

vector<ExchangeOrder> ExchangeService::getSellerOrders(
    const string& sellerPlayer,
    uint8_t status
) {
    return ExchangeDB::getSellerOrders(sellerPlayer, status);
}

//////////////////////////////////////////////////////////////////////////////
// Claim operations
//////////////////////////////////////////////////////////////////////////////

vector<ExchangeClaim> ExchangeService::prepareClaimList(PlayerCreature* pPlayer) {
    vector<ExchangeClaim> claims;

    if (!pPlayer) return claims;

    string playerName = pPlayer->getName();

    // Get buyer's paid orders (ready to deliver)
    vector<ExchangeOrder> orders = getBuyerOrders(playerName, ORDER_STATUS_PAID);
    for (const auto& order : orders) {
        ExchangeListing* pListing = getListing(order.listingID);
        if (pListing) {
            ExchangeClaim claim;
            claim.id = order.orderID;
            claim.itemName = pListing->itemName;
            claim.pricePoint = order.pricePoint;
            claim.type = 0;  // Buyer claim
            claim.status = order.status;
            claims.push_back(claim);
        }
    }

    // Get seller's cancelled/expired listings (ready to return)
    vector<ExchangeListing> cancelledListings = getSellerListings(
        playerName, LISTING_STATUS_CANCELLED
    );
    for (const auto& listing : cancelledListings) {
        ExchangeClaim claim;
        claim.id = listing.listingID;
        claim.itemName = listing.itemName;
        claim.pricePoint = listing.pricePoint;
        claim.type = 1;  // Seller claim
        claim.status = listing.status;
        claims.push_back(claim);
    }

    return claims;
}

pair<bool, string> ExchangeService::claimItem(
    PlayerCreature* pPlayer,
    int64_t orderOrListingID,
    bool isBuyerClaim
) {
    if (!pPlayer) {
        return make_pair(false, formatError(EXCHANGE_FAIL_ITEM_NOT_FOUND));
    }

    // Check inventory space
    if (!checkInventorySpace(pPlayer)) {
        return make_pair(false, formatError(EXCHANGE_FAIL_INVENTORY_FULL));
    }

    if (isBuyerClaim) {
        // Buyer claiming purchased item
        // Find the specific order
        vector<ExchangeOrder> orders = getBuyerOrders(pPlayer->getName(), ORDER_STATUS_PAID);
        ExchangeOrder* pTargetOrder = NULL;
        for (const auto& order : orders) {
            if (order.orderID == orderOrListingID) {
                pTargetOrder = const_cast<ExchangeOrder*>(&order);
                break;
            }
        }

        if (!pTargetOrder) {
            return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_FOUND));
        }

        // Get listing
        ExchangeListing* pListing = getListing(pTargetOrder->listingID);
        if (!pListing) {
            return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_FOUND));
        }

        // Load item from exchange storage
        // Note: This requires loading the item by ObjectID from DB
        // For now, we'll mark the order as delivered
        // The actual item transfer should be handled by the item manager

        if (!ExchangeDB::markOrderDelivered(orderOrListingID)) {
            return make_pair(false, formatError(EXCHANGE_FAIL_DATABASE_ERROR));
        }

        // TODO: Actually transfer item to player's inventory
        // This requires finding the item by ObjectID and moving it

        return make_pair(true, "");

    } else {
        // Seller claiming back cancelled/expired item
        ExchangeListing* pListing = getListing(orderOrListingID);
        if (!pListing) {
            return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_FOUND));
        }

        // Verify ownership
        if (pListing->sellerPlayer != pPlayer->getName()) {
            return make_pair(false, formatError(EXCHANGE_FAIL_NOT_SELLER));
        }

        // Check status
        if (pListing->status != LISTING_STATUS_CANCELLED &&
            pListing->status != LISTING_STATUS_EXPIRED) {
            return make_pair(false, formatError(EXCHANGE_FAIL_LISTING_NOT_AVAILABLE));
        }

        // TODO: Load item from exchange storage and add to inventory
        // This requires item manager integration

        return make_pair(true, "");
    }
}

//////////////////////////////////////////////////////////////////////////////
// Point operations
//////////////////////////////////////////////////////////////////////////////

int ExchangeService::getPointBalance(const string& account) {
    return ExchangeDB::getPointBalance(account);
}

pair<bool, int> ExchangeService::adjustPoints(
    const string& account,
    int delta,
    uint8_t reason,
    int64_t refListingID,
    int64_t refOrderID,
    const string& idempotencyKey
) {
    int balanceAfter;
    bool success = ExchangeDB::adjustPoints(
        account,
        delta,
        balanceAfter,
        reason,
        refListingID,
        refOrderID,
        idempotencyKey
    );

    return make_pair(success, success ? balanceAfter : -1);
}

//////////////////////////////////////////////////////////////////////////////
// Maintenance operations
//////////////////////////////////////////////////////////////////////////////

void ExchangeService::scanExpiredListings() {
    __BEGIN_TRY

    // Scan for expired active listings
    // In production, use indexed query on ExpireAt column
    vector<ExchangeListing> expiredListings = ExchangeDB::getExpiredListings();

    filelog("ExchangeService.log", "Scanning for expired listings, found %d expired",
            expiredListings.size());

    for (const auto& listing : expiredListings) {
        filelog("ExchangeService.log",
                "Expiring listing ID: %lld, Item: %s, Seller: %s",
                listing.listingID, listing.itemName.c_str(),
                listing.sellerPlayer.c_str());

        // Mark listing as expired
        // This will:
        // 1. Set listing status to EXPIRED
        // 2. Allow seller to reclaim the item
        ExchangeDB::expireListing(listing.listingID);
    }

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Helper methods
//////////////////////////////////////////////////////////////////////////////

int ExchangeService::calculateTax(int price) {
    return (price * m_TaxRate) / 100;
}

string ExchangeService::getCurrentTimestamp() {
    return _getCurrentTime();
}

bool ExchangeService::moveItemToExchangeStorage(PlayerCreature* pPlayer, Item* pItem) {
    if (!pPlayer || !pItem) return false;

    // Get the item's current storage location
    int storage, x, y;
    pPlayer->findItemOID(pItem->getObjectID(), storage, x, y);

    // Save item with STORAGE_EXCHANGE type
    // The item will be associated with the exchange system
    string owner = pPlayer->getName();

    // Call item's save method with STORAGE_EXCHANGE
    // This is the pattern used in the codebase
    // pItem->save(owner, STORAGE_EXCHANGE, 0, 0, 0);

    // Remove from inventory
    Inventory* pInv = pPlayer->getInventory();
    if (pInv) {
        // pInv->deleteItem(x, y);  // Remove from current slot
    }

    return true;
}

bool ExchangeService::moveItemFromExchangeStorage(
    PlayerCreature* pPlayer,
    int64_t listingID,
    Item* pItem
) {
    if (!pPlayer || !pItem) return false;

    // Add item to player's inventory
    Inventory* pInv = pPlayer->getInventory();
    if (!pInv) return false;

    // Find empty slot
    // pItem->create(pPlayer->getName(), STORAGE_INVENTORY, ...);

    return true;
}

void ExchangeService::createItemSnapshot(Item* pItem, ExchangeListing& listing) {
    if (!pItem) return;

    // Set basic item info
    listing.itemName = pItem->toString();  // Or get name from item info
    listing.enchantLevel = 0;  // TODO: Get from pItem
    listing.grade = 0;  // TODO: Get from pItem
    listing.durability = 0;  // TODO: Get from pItem
    listing.silver = 0;  // TODO: Get from pItem
    listing.stackCount = 1;  // TODO: Get from pItem

    // Get option info
    if (pItem->hasOptionType()) {
        const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
        int idx = 0;
        for (OptionType_t type : optionTypes) {
            (void)type;  // Will be used when setting option fields
            if (idx >= 3) break;

            // Set option type and value
            // listing.optionType1 = type;
            // listing.optionValue1 = value;
            idx++;
        }
    }
}

string ExchangeService::generateIdempotencyKey() {
    return _generateIdempotencyKey();
}

int16_t ExchangeService::getServerID() {
    return _getServerID();
}

bool ExchangeService::checkInventorySpace(PlayerCreature* pPlayer) {
    return _checkInventorySpace(pPlayer);
}

string ExchangeService::formatError(ExchangeResult code, const string& detail) {
    string error;

    switch (code) {
        case EXCHANGE_SUCCESS:
            return "Success";

        case EXCHANGE_FAIL_ITEM_NOT_FOUND:
            error = "Item not found";
            break;
        case EXCHANGE_FAIL_ITEM_OWNERSHIP:
            error = "You don't own this item";
            break;
        case EXCHANGE_FAIL_ITEM_TRADEABLE:
            error = "This item cannot be traded";
            break;
        case EXCHANGE_FAIL_INVALID_PRICE:
            error = "Invalid price";
            break;
        case EXCHANGE_FAIL_INSUFFICIENT_POINTS:
            error = "Insufficient point balance";
            break;
        case EXCHANGE_FAIL_LISTING_NOT_FOUND:
            error = "Listing not found";
            break;
        case EXCHANGE_FAIL_LISTING_NOT_AVAILABLE:
            error = "Listing is no longer available";
            break;
        case EXCHANGE_FAIL_INVENTORY_FULL:
            error = "Inventory is full";
            break;
        case EXCHANGE_FAIL_STORAGE_FULL:
            error = "Exchange storage is full";
            break;
        case EXCHANGE_FAIL_NOT_SELLER:
            error = "You are not the seller of this item";
            break;
        case EXCHANGE_FAIL_NOT_BUYER:
            error = "You are not the buyer of this item";
            break;
        case EXCHANGE_FAIL_ALREADY_CLAIMED:
            error = "Item already claimed";
            break;
        case EXCHANGE_FAIL_DATABASE_ERROR:
            error = "Database error";
            break;
        case EXCHANGE_FAIL_TRANSACTION_ERROR:
            error = "Transaction error";
            break;
        case EXCHANGE_FAIL_IDEMPOTENCY_CONFLICT:
            error = "Duplicate transaction";
            break;
        default:
            error = "Unknown error";
            break;
    }

    if (!detail.empty()) {
        error += ": " + detail;
    }

    return error;
}
