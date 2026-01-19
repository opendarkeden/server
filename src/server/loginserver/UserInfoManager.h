//----------------------------------------------------------------------
//
// Filename    : UserInfoManager.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __USER_INFO_MANAGER_H__
#define __USER_INFO_MANAGER_H__

// include files
#include <unordered_map>

#include "Exception.h"
#include "Types.h"
#include "UserInfo.h"

typedef unordered_map<ZoneGroupID_t, UserInfo*> HashMapUserInfo;

//----------------------------------------------------------------------
//
// class UserInfoManager;
//
// ���׷� ���̵� Ű������ �ϴ� �� ������ unordered_map ��
// ������ �ִ�.
//
//----------------------------------------------------------------------

class UserInfoManager {
public:
    // constructor
    UserInfoManager() noexcept;

    // destructor
    ~UserInfoManager() noexcept;

    // initialize manager
    void init() noexcept(false);

    // add info
    void addUserInfo(UserInfo* pUserInfo) noexcept(false);

    // delete info
    void deleteUserInfo(ZoneGroupID_t ServerGroupID, WorldID_t WorldID) noexcept(false);

    // get info
    UserInfo* getUserInfo(ZoneGroupID_t ServerGroupID, WorldID_t WorldID) const noexcept(false);

    // get count of info
    uint getSize(WorldID_t WorldID) const noexcept {
        return m_UserInfos[WorldID].size();
    }

    // get debug string
    string toString() const noexcept(false);

    // load from database
    void load() noexcept(false);

private:
    // hash map of UserInfo
    // key   : UserID_t
    // value : UserInfo *
    HashMapUserInfo* m_UserInfos;

    WorldID_t m_MaxWorldID;
};


// global variable declaration
extern UserInfoManager* g_pUserInfoManager;

#endif
