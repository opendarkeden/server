//----------------------------------------------------------------------
//
// Filename    : ReconnectLoginInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "ReconnectLoginInfoManager.h"

#include "Assert.h"
#include "StringStream.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
ReconnectLoginInfoManager::ReconnectLoginInfoManager() noexcept {
    __BEGIN_TRY

    // ���� heartbeat �ð��� �����Ѵ�.
    getCurrentTime(m_NextHeartbeat);
    m_NextHeartbeat.tv_sec += 5;

    __END_CATCH
}

//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
ReconnectLoginInfoManager::~ReconnectLoginInfoManager() noexcept {
    __BEGIN_TRY

    // ��� ReconnectLoginInfo �� �����ؾ� �Ѵ�.
    for (HashMapReconnectLoginInfo::iterator itr = m_ReconnectLoginInfos.begin(); itr != m_ReconnectLoginInfos.end();
         itr++) {
        delete itr->second;
        itr->second = NULL;
    }

    // �ؽ��ʾȿ� �ִ� ��� pair ���� �����Ѵ�.
    m_ReconnectLoginInfos.clear();

    __END_CATCH
}


//----------------------------------------------------------------------
// add connection info to connection info manager
//----------------------------------------------------------------------
void ReconnectLoginInfoManager::addReconnectLoginInfo(ReconnectLoginInfo* pReconnectLoginInfo) noexcept(false) {
    __BEGIN_TRY

    Assert(pReconnectLoginInfo != NULL);

    HashMapReconnectLoginInfo::iterator itr = m_ReconnectLoginInfos.find(pReconnectLoginInfo->getClientIP());

    if (itr != m_ReconnectLoginInfos.end())
        // �Ȱ��� ���̵� �̹� �����Ѵٴ� �Ҹ���. - -;
        throw DuplicatedException("duplicated connection info id");

    m_ReconnectLoginInfos[pReconnectLoginInfo->getClientIP()] = pReconnectLoginInfo;

    __END_CATCH
}


//----------------------------------------------------------------------
// delete connection info from connection info manager
//----------------------------------------------------------------------
void ReconnectLoginInfoManager::deleteReconnectLoginInfo(string clientIP) noexcept(false) {
    __BEGIN_TRY

    HashMapReconnectLoginInfo::iterator itr = m_ReconnectLoginInfos.find(clientIP);

    if (itr != m_ReconnectLoginInfos.end()) {
        // ReconnectLoginInfo �� �����Ѵ�.
        delete itr->second;

        // pair�� �����Ѵ�.
        m_ReconnectLoginInfos.erase(itr);

    } else {
        // not found
        throw NoSuchElementException(clientIP);
    }

    __END_CATCH
}


//----------------------------------------------------------------------
// get connection info from connection info manager
//----------------------------------------------------------------------
ReconnectLoginInfo* ReconnectLoginInfoManager::getReconnectLoginInfo(string clientIP) noexcept(false) {
    __BEGIN_TRY

    ReconnectLoginInfo* pReconnectLoginInfo = NULL;

    HashMapReconnectLoginInfo::iterator itr = m_ReconnectLoginInfos.find(clientIP);

    if (itr != m_ReconnectLoginInfos.end()) {
        pReconnectLoginInfo = itr->second;

    } else {
        // not found
        throw NoSuchElementException(clientIP);
    }

    return pReconnectLoginInfo;

    __END_CATCH
}


//----------------------------------------------------------------------
// expire �� ReconnectLogin Info ��ü�� �����Ѵ�.
//----------------------------------------------------------------------
void ReconnectLoginInfoManager::heartbeat() noexcept(false) {
    __BEGIN_TRY

    Timeval currentTime;
    getCurrentTime(currentTime);

    if (m_NextHeartbeat < currentTime) {
        m_NextHeartbeat = currentTime;
        m_NextHeartbeat.tv_sec += 5;

        HashMapReconnectLoginInfo::iterator before = m_ReconnectLoginInfos.end();
        HashMapReconnectLoginInfo::iterator current = m_ReconnectLoginInfos.begin();

        while (current != m_ReconnectLoginInfos.end()) {
            if (current->second->getExpireTime() < currentTime) {
                ReconnectLoginInfo* pReconnectLoginInfo = current->second;

                m_ReconnectLoginInfos.erase(current);

                delete pReconnectLoginInfo;

                if (before == m_ReconnectLoginInfos.end()) // case of first
                {
                    current = m_ReconnectLoginInfos.begin();
                } else // case of not first
                {
                    current = before;
                    current++;
                }
            } else {
                before = current++;
            }
        }
    }

    __END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string ReconnectLoginInfoManager::toString() const {
    StringStream msg;

    msg << "ReconnectLoginInfoManager(";

    for (unordered_map<string, ReconnectLoginInfo*>::const_iterator itr = m_ReconnectLoginInfos.begin();
         itr != m_ReconnectLoginInfos.end(); itr++) {
        Assert(itr->second != NULL);
        msg << itr->second->toString();
    }

    msg << ")";

    return msg.toString();
}


// global variable definition
ReconnectLoginInfoManager* g_pReconnectLoginInfoManager = NULL;
