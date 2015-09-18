//----------------------------------------------------------------------
//
// Filename    : GameServerGroupInfo.h
// Written By  : Reiot
// Description : 로그인 서버에서 갖고 있는 각 게임 서버에 대한 정보
//
//----------------------------------------------------------------------

#ifndef __GAME_SERVER_GROUP_INFO_H__
#define __GAME_SERVER_GROUP_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "StringStream.h"


class GameServerGroupInfo {
public:

    WorldID_t getWorldID() const throw() { return m_WorldID; }
    void setWorldID(WorldID_t WorldID) throw() { m_WorldID = WorldID; }

    ServerGroupID_t getGroupID() const throw() { return m_GroupID; }
    void setGroupID(ServerGroupID_t GroupID) throw() { m_GroupID = GroupID; }

    string getGroupName() const throw() { return m_GroupName; }
    void setGroupName(string GroupName) throw() { m_GroupName = GroupName; }
    
    BYTE getStat() const throw() { return m_Stat; }
    void setStat(BYTE stat) throw() { m_Stat = stat; }

    string toString() const throw() {
        StringStream msg;
        msg << "GameServerGroupInfo(WorldID: " << (int)m_WorldID << ", ServerGroupID: " << (int)m_GroupID << ", GroupName: " << m_GroupName << ")";
        return msg.toString();
    }

private:
    WorldID_t m_WorldID;

    ServerGroupID_t m_GroupID;

    string m_GroupName;

    BYTE m_Stat;
};
#endif
