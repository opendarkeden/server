//////////////////////////////////////////////////////////////////////////////
// Filename : ExchangeDB.cpp
// Written by : Exchange System
// Description : Database access layer implementation for Exchange System
//////////////////////////////////////////////////////////////////////////////

#include "ExchangeDB.h"
#include "GCExchangeList.h"  // For ExchangeListing definition

#include <sstream>
#include <iomanip>
#include <cstdlib>

#include "DatabaseManager.h"
#include "DB.h"
#include "StringStream.h"

//////////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////////

namespace {

// Get current timestamp in MySQL format
string getCurrentTime() {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);
    return string(buffer);
}

// Escape string for SQL
string escapeSQL(const string& input) {
    string result = input;
    size_t pos = 0;
    while ((pos = result.find("'", pos)) != string::npos) {
        result.replace(pos, 1, "''");
        pos += 2;
    }
    return result;
}

// Convert string to int64_t
int64_t toInt64(const string& str) {
    return strtoll(str.c_str(), NULL, 10);
}

} // anonymous namespace

//////////////////////////////////////////////////////////////////////////////
// Listing operations
//////////////////////////////////////////////////////////////////////////////

// Create a new listing record
int64_t ExchangeDB::createListing(const ExchangeListing& listing) {
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        // Build INSERT query - using printf-style format
        pStmt->executeQuery(
            "INSERT INTO ExchangeListing ("
            "ServerID, SellerAccount, SellerPlayer, SellerRace, "
            "ItemClass, ItemType, ItemID, ObjectID, "
            "PricePoint, Currency, Status, "
            "TaxRate, TaxAmount, "
            "CreatedAt, ExpireAt, UpdatedAt, Version, "
            "ItemName, EnchantLevel, Grade, Durability, Silver, "
            "OptionType1, OptionType2, OptionType3, "
            "OptionValue1, OptionValue2, OptionValue3, StackCount"
            ") VALUES (%d, '%s', '%s', %d, %d, %d, %lld, %d, %d, %d, %d, %d, %d, '%s', '%s', '%s', %d, '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
            listing.serverID,
            escapeSQL(listing.sellerAccount).c_str(),
            escapeSQL(listing.sellerPlayer).c_str(),
            (int)listing.sellerRace,
            (int)listing.itemClass,
            listing.itemType,
            (long long)listing.itemID,
            listing.objectID,
            listing.pricePoint,
            (int)listing.currency,
            (int)listing.status,
            (int)listing.taxRate,
            listing.taxAmount,
            getCurrentTime().c_str(),
            listing.expireAt.c_str(),
            getCurrentTime().c_str(),
            listing.version,
            escapeSQL(listing.itemName).c_str(),
            (int)listing.enchantLevel,
            listing.grade,
            listing.durability,
            listing.silver,
            (int)listing.optionType1,
            (int)listing.optionType2,
            (int)listing.optionType3,
            listing.optionValue1,
            listing.optionValue2,
            listing.optionValue3,
            listing.stackCount
        );

        // Get the auto-generated listing ID
        pResult = pStmt->executeQuery("SELECT LAST_INSERT_ID()");
        if (pResult->next()) {
            int64_t listingID = toInt64(pResult->getString(1));
            SAFE_DELETE(pStmt);
            return listingID;
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    return 0;

    __END_CATCH
}

// Cancel a listing (mark as CANCELLED)
bool ExchangeDB::cancelListing(int64_t listingID) {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pStmt->executeQuery(
            "UPDATE ExchangeListing SET "
            "Status = 2, "  // CANCELLED
            "CancelledAt = '%s', "
            "UpdatedAt = '%s' "
            "WHERE ListingID = %lld "
            "AND Status = 0",  // Only ACTIVE listings
            getCurrentTime().c_str(),
            getCurrentTime().c_str(),
            (long long)listingID
        );

        SAFE_DELETE(pStmt);
        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Mark listing as expired
bool ExchangeDB::expireListing(int64_t listingID) {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pStmt->executeQuery(
            "UPDATE ExchangeListing SET "
            "Status = 3, "  // EXPIRED
            "UpdatedAt = '%s' "
            "WHERE ListingID = %lld "
            "AND Status = 0",  // Only ACTIVE listings
            getCurrentTime().c_str(),
            (long long)listingID
        );

        SAFE_DELETE(pStmt);
        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Mark listing as sold and set buyer info
bool ExchangeDB::markListingSold(int64_t listingID,
                                const string& buyerAccount,
                                const string& buyerPlayer) {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pStmt->executeQuery(
            "UPDATE ExchangeListing SET "
            "Status = 1, "  // SOLD
            "BuyerAccount = '%s', "
            "BuyerPlayer = '%s', "
            "SoldAt = '%s', "
            "UpdatedAt = '%s' "
            "WHERE ListingID = %lld "
            "AND Status = 0",  // Only ACTIVE listings
            escapeSQL(buyerAccount).c_str(),
            escapeSQL(buyerPlayer).c_str(),
            getCurrentTime().c_str(),
            getCurrentTime().c_str(),
            (long long)listingID
        );

        SAFE_DELETE(pStmt);
        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Query listings with pagination and filters
vector<ExchangeListing> ExchangeDB::getListings(int16_t serverID,
                                               uint8_t status,
                                               int page,
                                               int pageSize) {
    vector<ExchangeListing> listings;

    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        int offset = (page - 1) * pageSize;

        pResult = pStmt->executeQuery(
            "SELECT * FROM ExchangeListing "
            "WHERE ServerID = %d "
            "AND Status = %d "
            "ORDER BY CreatedAt DESC "
            "LIMIT %d OFFSET %d",
            serverID,
            (int)status,
            pageSize,
            offset
        );

        while (pResult->next()) {
            ExchangeListing listing;
            int idx = 1;

            listing.listingID = toInt64(pResult->getString(idx++));
            listing.serverID = pResult->getInt(idx++);
            listing.sellerAccount = pResult->getString(idx++);
            listing.sellerPlayer = pResult->getString(idx++);
            listing.sellerRace = pResult->getBYTE(idx++);
            listing.itemClass = pResult->getBYTE(idx++);
            listing.itemType = pResult->getWORD(idx++);
            listing.itemID = toInt64(pResult->getString(idx++));
            listing.objectID = pResult->getInt(idx++);
            listing.pricePoint = pResult->getInt(idx++);
            listing.currency = pResult->getBYTE(idx++);
            listing.status = pResult->getBYTE(idx++);
            listing.buyerAccount = pResult->getString(idx++);
            listing.buyerPlayer = pResult->getString(idx++);
            listing.taxRate = pResult->getBYTE(idx++);
            listing.taxAmount = pResult->getInt(idx++);
            listing.createdAt = pResult->getString(idx++);
            listing.expireAt = pResult->getString(idx++);
            listing.soldAt = pResult->getString(idx++);
            listing.cancelledAt = pResult->getString(idx++);
            listing.updatedAt = pResult->getString(idx++);
            listing.version = pResult->getInt(idx++);

            // Snapshot fields
            listing.itemName = pResult->getString(idx++);
            listing.enchantLevel = pResult->getBYTE(idx++);
            listing.grade = pResult->getWORD(idx++);
            listing.durability = pResult->getInt(idx++);
            listing.silver = pResult->getWORD(idx++);
            listing.optionType1 = pResult->getBYTE(idx++);
            listing.optionType2 = pResult->getBYTE(idx++);
            listing.optionType3 = pResult->getBYTE(idx++);
            listing.optionValue1 = pResult->getWORD(idx++);
            listing.optionValue2 = pResult->getWORD(idx++);
            listing.optionValue3 = pResult->getWORD(idx++);
            listing.stackCount = pResult->getInt(idx++);

            listings.push_back(listing);
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return listings;
}

// Get a specific listing by ID
ExchangeListing* ExchangeDB::getListing(int64_t listingID) {
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pResult = pStmt->executeQuery(
            "SELECT * FROM ExchangeListing "
            "WHERE ListingID = %lld",
            (long long)listingID
        );

        if (pResult->next()) {
            ExchangeListing* listing = new ExchangeListing();
            int idx = 1;

            listing->listingID = toInt64(pResult->getString(idx++));
            listing->serverID = pResult->getInt(idx++);
            listing->sellerAccount = pResult->getString(idx++);
            listing->sellerPlayer = pResult->getString(idx++);
            listing->sellerRace = pResult->getBYTE(idx++);
            listing->itemClass = pResult->getBYTE(idx++);
            listing->itemType = pResult->getWORD(idx++);
            listing->itemID = toInt64(pResult->getString(idx++));
            listing->objectID = pResult->getInt(idx++);
            listing->pricePoint = pResult->getInt(idx++);
            listing->currency = pResult->getBYTE(idx++);
            listing->status = pResult->getBYTE(idx++);
            listing->buyerAccount = pResult->getString(idx++);
            listing->buyerPlayer = pResult->getString(idx++);
            listing->taxRate = pResult->getBYTE(idx++);
            listing->taxAmount = pResult->getInt(idx++);
            listing->createdAt = pResult->getString(idx++);
            listing->expireAt = pResult->getString(idx++);
            listing->soldAt = pResult->getString(idx++);
            listing->cancelledAt = pResult->getString(idx++);
            listing->updatedAt = pResult->getString(idx++);
            listing->version = pResult->getInt(idx++);

            // Snapshot fields
            listing->itemName = pResult->getString(idx++);
            listing->enchantLevel = pResult->getBYTE(idx++);
            listing->grade = pResult->getWORD(idx++);
            listing->durability = pResult->getInt(idx++);
            listing->silver = pResult->getWORD(idx++);
            listing->optionType1 = pResult->getBYTE(idx++);
            listing->optionType2 = pResult->getBYTE(idx++);
            listing->optionType3 = pResult->getBYTE(idx++);
            listing->optionValue1 = pResult->getWORD(idx++);
            listing->optionValue2 = pResult->getWORD(idx++);
            listing->optionValue3 = pResult->getWORD(idx++);
            listing->stackCount = pResult->getInt(idx++);

            SAFE_DELETE(pStmt);
            return listing;
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return NULL;
}

// Get seller's listings
vector<ExchangeListing> ExchangeDB::getSellerListings(const string& sellerAccount,
                                                      uint8_t status) {
    vector<ExchangeListing> listings;

    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pResult = pStmt->executeQuery(
            "SELECT * FROM ExchangeListing "
            "WHERE SellerAccount = '%s' "
            "AND Status = %d "
            "ORDER BY CreatedAt DESC",
            escapeSQL(sellerAccount).c_str(),
            (int)status
        );

        while (pResult->next()) {
            ExchangeListing listing;
            int idx = 1;

            listing.listingID = toInt64(pResult->getString(idx++));
            listing.serverID = pResult->getInt(idx++);
            listing.sellerAccount = pResult->getString(idx++);
            listing.sellerPlayer = pResult->getString(idx++);
            listing.sellerRace = pResult->getBYTE(idx++);
            listing.itemClass = pResult->getBYTE(idx++);
            listing.itemType = pResult->getWORD(idx++);
            listing.itemID = toInt64(pResult->getString(idx++));
            listing.objectID = pResult->getInt(idx++);
            listing.pricePoint = pResult->getInt(idx++);
            listing.currency = pResult->getBYTE(idx++);
            listing.status = pResult->getBYTE(idx++);
            listing.buyerAccount = pResult->getString(idx++);
            listing.buyerPlayer = pResult->getString(idx++);
            listing.taxRate = pResult->getBYTE(idx++);
            listing.taxAmount = pResult->getInt(idx++);
            listing.createdAt = pResult->getString(idx++);
            listing.expireAt = pResult->getString(idx++);
            listing.soldAt = pResult->getString(idx++);
            listing.cancelledAt = pResult->getString(idx++);
            listing.updatedAt = pResult->getString(idx++);
            listing.version = pResult->getInt(idx++);

            // Snapshot fields
            listing.itemName = pResult->getString(idx++);
            listing.enchantLevel = pResult->getBYTE(idx++);
            listing.grade = pResult->getWORD(idx++);
            listing.durability = pResult->getInt(idx++);
            listing.silver = pResult->getWORD(idx++);
            listing.optionType1 = pResult->getBYTE(idx++);
            listing.optionType2 = pResult->getBYTE(idx++);
            listing.optionType3 = pResult->getBYTE(idx++);
            listing.optionValue1 = pResult->getWORD(idx++);
            listing.optionValue2 = pResult->getWORD(idx++);
            listing.optionValue3 = pResult->getWORD(idx++);
            listing.stackCount = pResult->getInt(idx++);

            listings.push_back(listing);
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return listings;
}

// Get expired listings for maintenance scan
vector<ExchangeListing> ExchangeDB::getExpiredListings() {
    vector<ExchangeListing> listings;

    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        // Query active listings that have expired
        // Use NOW() to compare with ExpireAt
        pResult = pStmt->executeQuery(
            "SELECT * FROM ExchangeListing "
            "WHERE Status = %d "  // LISTING_STATUS_ACTIVE = 0
            "AND ExpireAt < NOW() "
            "ORDER BY ExpireAt ASC "
            "LIMIT 1000",  // Process in batches to avoid long transactions
            (int)LISTING_STATUS_ACTIVE
        );

        while (pResult->next()) {
            ExchangeListing listing;
            int idx = 1;

            listing.listingID = toInt64(pResult->getString(idx++));
            listing.serverID = pResult->getInt(idx++);
            listing.sellerAccount = pResult->getString(idx++);
            listing.sellerPlayer = pResult->getString(idx++);
            listing.sellerRace = pResult->getBYTE(idx++);
            listing.itemClass = pResult->getBYTE(idx++);
            listing.itemType = pResult->getWORD(idx++);
            listing.itemID = toInt64(pResult->getString(idx++));
            listing.objectID = pResult->getInt(idx++);
            listing.pricePoint = pResult->getInt(idx++);
            listing.currency = pResult->getBYTE(idx++);
            listing.status = pResult->getBYTE(idx++);
            listing.buyerAccount = pResult->getString(idx++);
            listing.buyerPlayer = pResult->getString(idx++);
            listing.taxRate = pResult->getBYTE(idx++);
            listing.taxAmount = pResult->getInt(idx++);
            listing.createdAt = pResult->getString(idx++);
            listing.expireAt = pResult->getString(idx++);
            listing.soldAt = pResult->getString(idx++);
            listing.cancelledAt = pResult->getString(idx++);
            listing.updatedAt = pResult->getString(idx++);
            listing.version = pResult->getInt(idx++);

            // Snapshot fields
            listing.itemName = pResult->getString(idx++);
            listing.enchantLevel = pResult->getBYTE(idx++);
            listing.grade = pResult->getWORD(idx++);
            listing.durability = pResult->getInt(idx++);
            listing.silver = pResult->getWORD(idx++);
            listing.optionType1 = pResult->getBYTE(idx++);
            listing.optionType2 = pResult->getBYTE(idx++);
            listing.optionType3 = pResult->getBYTE(idx++);
            listing.optionValue1 = pResult->getWORD(idx++);
            listing.optionValue2 = pResult->getWORD(idx++);
            listing.optionValue3 = pResult->getWORD(idx++);
            listing.stackCount = pResult->getInt(idx++);

            listings.push_back(listing);
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return listings;
}

//////////////////////////////////////////////////////////////////////////////
// Order operations
//////////////////////////////////////////////////////////////////////////////

// Create a new order
int64_t ExchangeDB::createOrder(const ExchangeOrder& order) {
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pStmt->executeQuery(
            "INSERT INTO ExchangeOrder ("
            "ListingID, ServerID, BuyerAccount, BuyerPlayer, "
            "PricePoint, TaxAmount, Status, CreatedAt"
            ") VALUES (%lld, %d, '%s', '%s', %d, %d, %d, '%s')",
            (long long)order.listingID,
            order.serverID,
            escapeSQL(order.buyerAccount).c_str(),
            escapeSQL(order.buyerPlayer).c_str(),
            order.pricePoint,
            order.taxAmount,
            (int)order.status,
            getCurrentTime().c_str()
        );

        // Get the auto-generated order ID
        pResult = pStmt->executeQuery("SELECT LAST_INSERT_ID()");
        if (pResult->next()) {
            int64_t orderID = toInt64(pResult->getString(1));
            SAFE_DELETE(pStmt);
            return orderID;
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    return 0;

    __END_CATCH
}

// Mark order as delivered
bool ExchangeDB::markOrderDelivered(int64_t orderID) {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pStmt->executeQuery(
            "UPDATE ExchangeOrder SET "
            "Status = 1, "  // DELIVERED
            "DeliveredAt = '%s' "
            "WHERE OrderID = %lld "
            "AND Status = 0",  // Only PAID orders
            getCurrentTime().c_str(),
            (long long)orderID
        );

        SAFE_DELETE(pStmt);
        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Get buyer's orders
vector<ExchangeOrder> ExchangeDB::getBuyerOrders(const string& buyerPlayer,
                                               uint8_t status) {
    vector<ExchangeOrder> orders;

    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pResult = pStmt->executeQuery(
            "SELECT * FROM ExchangeOrder "
            "WHERE BuyerPlayer = '%s' "
            "AND Status = %d "
            "ORDER BY CreatedAt DESC",
            escapeSQL(buyerPlayer).c_str(),
            (int)status
        );

        while (pResult->next()) {
            ExchangeOrder order;
            int idx = 1;

            order.orderID = toInt64(pResult->getString(idx++));
            order.listingID = toInt64(pResult->getString(idx++));
            order.serverID = pResult->getInt(idx++);
            order.buyerAccount = pResult->getString(idx++);
            order.buyerPlayer = pResult->getString(idx++);
            order.pricePoint = pResult->getInt(idx++);
            order.taxAmount = pResult->getInt(idx++);
            order.status = pResult->getBYTE(idx++);
            order.createdAt = pResult->getString(idx++);
            order.deliveredAt = pResult->getString(idx++);
            order.cancelledAt = pResult->getString(idx++);

            orders.push_back(order);
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return orders;
}

// Get seller's fulfilled orders
vector<ExchangeOrder> ExchangeDB::getSellerOrders(const string& sellerPlayer,
                                                 uint8_t status) {
    vector<ExchangeOrder> orders;

    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        pResult = pStmt->executeQuery(
            "SELECT o.* FROM ExchangeOrder o "
            "INNER JOIN ExchangeListing l ON o.ListingID = l.ListingID "
            "WHERE l.SellerPlayer = '%s' "
            "AND o.Status = %d "
            "ORDER BY o.CreatedAt DESC",
            escapeSQL(sellerPlayer).c_str(),
            (int)status
        );

        while (pResult->next()) {
            ExchangeOrder order;
            int idx = 1;

            order.orderID = toInt64(pResult->getString(idx++));
            order.listingID = toInt64(pResult->getString(idx++));
            order.serverID = pResult->getInt(idx++);
            order.buyerAccount = pResult->getString(idx++);
            order.buyerPlayer = pResult->getString(idx++);
            order.pricePoint = pResult->getInt(idx++);
            order.taxAmount = pResult->getInt(idx++);
            order.status = pResult->getBYTE(idx++);
            order.createdAt = pResult->getString(idx++);
            order.deliveredAt = pResult->getString(idx++);
            order.cancelledAt = pResult->getString(idx++);

            orders.push_back(order);
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return orders;
}

//////////////////////////////////////////////////////////////////////////////
// Point operations (cross-database to USERINFO)
//////////////////////////////////////////////////////////////////////////////

// Adjust point balance with ledger record
bool ExchangeDB::adjustPoints(const string& account,
                             int delta,
                             int& balanceAfter,
                             uint8_t reason,
                             int64_t refListingID,
                             int64_t refOrderID,
                             const string& idempotencyKey) {
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        Connection* pConn = g_pDatabaseManager->getConnection("USERINFO");

        // Check idempotency if key provided
        if (!idempotencyKey.empty()) {
            pStmt = pConn->createStatement();
            pResult = pStmt->executeQuery(
                "SELECT COUNT(*) FROM PointLedger WHERE IdempotencyKey = '%s'",
                escapeSQL(idempotencyKey).c_str()
            );

            if (pResult->next() && pResult->getInt(1) > 0) {
                // Idempotency key exists - already processed
                SAFE_DELETE(pStmt);
                return false;
            }
            SAFE_DELETE(pStmt);
        }

        // Get current balance
        pStmt = pConn->createStatement();
        pResult = pStmt->executeQuery(
            "SELECT PointBalance FROM AccountPoint WHERE Account = '%s'",
            escapeSQL(account).c_str()
        );

        int currentBalance = 0;
        if (pResult->next()) {
            currentBalance = pResult->getInt(1);
        }
        SAFE_DELETE(pStmt);

        // Calculate new balance
        int newBalance = currentBalance + delta;
        if (newBalance < 0) {
            // Insufficient balance
            return false;
        }

        // Update or insert balance using REPLACE
        pStmt = pConn->createStatement();
        pStmt->executeQuery(
            "REPLACE INTO AccountPoint (Account, PointBalance, UpdatedAt) "
            "VALUES ('%s', %d, '%s')",
            escapeSQL(account).c_str(),
            newBalance,
            getCurrentTime().c_str()
        );
        SAFE_DELETE(pStmt);

        // Insert ledger record
        pStmt = pConn->createStatement();
        if (idempotencyKey.empty()) {
            pStmt->executeQuery(
                "INSERT INTO PointLedger "
                "(Account, Delta, BalanceAfter, Reason, RefListingID, RefOrderID, CreatedAt) "
                "VALUES ('%s', %d, %d, %d, %lld, %lld, '%s')",
                escapeSQL(account).c_str(),
                delta,
                newBalance,
                (int)reason,
                (long long)refListingID,
                (long long)refOrderID,
                getCurrentTime().c_str()
            );
        } else {
            pStmt->executeQuery(
                "INSERT INTO PointLedger "
                "(Account, Delta, BalanceAfter, Reason, RefListingID, RefOrderID, IdempotencyKey, CreatedAt) "
                "VALUES ('%s', %d, %d, %d, %lld, %lld, '%s', '%s')",
                escapeSQL(account).c_str(),
                delta,
                newBalance,
                (int)reason,
                (long long)refListingID,
                (long long)refOrderID,
                escapeSQL(idempotencyKey).c_str(),
                getCurrentTime().c_str()
            );
        }
        SAFE_DELETE(pStmt);

        balanceAfter = newBalance;
        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Get current point balance
int ExchangeDB::getPointBalance(const string& account) {
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("USERINFO")->createStatement();

        pResult = pStmt->executeQuery(
            "SELECT PointBalance FROM AccountPoint WHERE Account = '%s'",
            escapeSQL(account).c_str()
        );

        if (pResult->next()) {
            int balance = pResult->getInt(1);
            SAFE_DELETE(pStmt);
            return balance;
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return 0;
}

// Check if idempotency key exists
bool ExchangeDB::hasIdempotencyKey(const string& idempotencyKey) {
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("USERINFO")->createStatement();

        pResult = pStmt->executeQuery(
            "SELECT COUNT(*) FROM PointLedger WHERE IdempotencyKey = '%s'",
            escapeSQL(idempotencyKey).c_str()
        );

        if (pResult->next()) {
            int count = pResult->getInt(1);
            SAFE_DELETE(pStmt);
            return (count > 0);
        }

        SAFE_DELETE(pStmt);
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

//////////////////////////////////////////////////////////////////////////////
// Transaction helpers (cross-database)
//////////////////////////////////////////////////////////////////////////////

// Begin cross-database transaction
bool ExchangeDB::beginTransaction() {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        // Start transaction on DARKEDEN database
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQuery("START TRANSACTION");
        SAFE_DELETE(pStmt);

        // Start transaction on USERINFO database
        pStmt = g_pDatabaseManager->getConnection("USERINFO")->createStatement();
        pStmt->executeQuery("START TRANSACTION");
        SAFE_DELETE(pStmt);

        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Commit transaction
bool ExchangeDB::commit() {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        // Commit DARKEDEN database
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQuery("COMMIT");
        SAFE_DELETE(pStmt);

        // Commit USERINFO database
        pStmt = g_pDatabaseManager->getConnection("USERINFO")->createStatement();
        pStmt->executeQuery("COMMIT");
        SAFE_DELETE(pStmt);

        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}

// Rollback transaction
bool ExchangeDB::rollback() {
    __BEGIN_TRY

    Statement* pStmt = NULL;

    BEGIN_DB {
        // Rollback DARKEDEN database
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQuery("ROLLBACK");
        SAFE_DELETE(pStmt);

        // Rollback USERINFO database
        pStmt = g_pDatabaseManager->getConnection("USERINFO")->createStatement();
        pStmt->executeQuery("ROLLBACK");
        SAFE_DELETE(pStmt);

        return true;
    } END_DB(pStmt)

    __END_CATCH

    return false;
}
