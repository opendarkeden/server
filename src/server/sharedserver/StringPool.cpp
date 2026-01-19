///////////////////////////////////////////////////////////
// Filename : StringPool.cpp
///////////////////////////////////////////////////////////

#include "StringPool.h"

#include "DB.h"

StringPool::StringPool() noexcept(false){__BEGIN_TRY __END_CATCH}

StringPool::~StringPool() noexcept {
    try {
        clear();
    } catch (...) {
        // destructor must not throw
    }
}

void StringPool::clear() noexcept(false) {
    __BEGIN_TRY

    m_Strings.clear();

    __END_CATCH
}

void StringPool::load() noexcept(false) {
    __BEGIN_TRY

    clear();

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT ID, String FROM SSStringPool");

        while (pResult->next()) {
            int i = 0;

            uint strID = pResult->getInt(++i);
            string str = pResult->getString(++i);

            addString(strID, str);
        }
    }
    END_DB(pStmt)

    __END_CATCH
}

void StringPool::addString(uint strID, string sString) noexcept(false) {
    __BEGIN_TRY

    StringHashMapItor itr = m_Strings.find(strID);

    if (itr != m_Strings.end()) {
        throw DuplicatedException("StringPool::addString()");
    }

    m_Strings[strID] = sString;

    __END_CATCH
}

string StringPool::getString(uint strID) noexcept(false) {
    __BEGIN_TRY

    StringHashMapItor itr = m_Strings.find(strID);

    if (itr == m_Strings.end()) {
        throw NoSuchElementException("StringPool::getStrind()");
    }

    return itr->second;

    __END_CATCH
}

const char* StringPool::c_str(uint strID) noexcept(false) {
    __BEGIN_TRY

    StringHashMapItor itr = m_Strings.find(strID);

    if (itr == m_Strings.end()) {
        throw NoSuchElementException("StringPool::getStrind()");
    }

    return itr->second.c_str();

    __END_CATCH
}

StringPool* g_pStringPool = NULL;
