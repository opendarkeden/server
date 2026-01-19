//----------------------------------------------------------------------
//
// Filename    : ReconnectLoginInfoManager.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __CONNECTION_INFO_MANAGER_H__
#define __CONNECTION_INFO_MANAGER_H__

// include files
#include <unordered_map>

#include "Exception.h"
#include "ReconnectLoginInfo.h"
#include "Types.h"

typedef unordered_map<string, ReconnectLoginInfo*> HashMapReconnectLoginInfo;

//----------------------------------------------------------------------
//
// class ReconnectLoginInfoManager;
//
// IP ��Ʈ���� Ű������ �ϴ� unordered_map �� ���ο� ������ �ִ�.
//
//----------------------------------------------------------------------

class ReconnectLoginInfoManager {
public:
    // constructor
    ReconnectLoginInfoManager() noexcept;

    // destructor
    ~ReconnectLoginInfoManager() noexcept;


public:
    // add connection info to connection info manager
    void addReconnectLoginInfo(ReconnectLoginInfo* pReconnectLoginInfo) noexcept(false);

    // delete connection info from connection info manager
    void deleteReconnectLoginInfo(string ip) noexcept(false);

    // get connection info from connection info manager
    ReconnectLoginInfo* getReconnectLoginInfo(string ip) noexcept(false);

    // heartbeat method
    // expire �� ReconnectLoginInfo �� �����Ѵ�.
    void heartbeat() noexcept(false);

    // get debug string
    string toString() const;


private:
    // hash map of ReconnectLoginInfo
    // key is ip-string
    HashMapReconnectLoginInfo m_ReconnectLoginInfos;

    Timeval m_NextHeartbeat;
};

// global variable declaration
extern ReconnectLoginInfoManager* g_pReconnectLoginInfoManager;

#endif
