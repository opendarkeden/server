//////////////////////////////////////////////////////////////////////
//
// Filename    : GuildMemberInfo.h
// Written By  :
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_MEMBER_INFO_H__
#define __GUILD_MEMBER_INFO_H__

// include files
#include "Exception.h"
#include "Packet.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////
//
// class GuildMemberInfo;
//
// Ŭ���̾�Ʈ�� ����� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GuildMemberInfo {
public:
    // constructor
    GuildMemberInfo();

    // destructor
    ~GuildMemberInfo() noexcept;

public:
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ��
    // �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream);

    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const;

    // get packet's body size
    // ����ȭ��, �̸� ���� ������ ����Ѵ�.
    PacketSize_t getSize();

    static uint getMaxSize() {
        return (szBYTE + 20 + szGuildMemberRank + szbool) * 220 + szBYTE + szServerID;
    }

    // get packet's debug string
    string toString() const;

    // get/set Name
    string getName() const {
        return m_Name;
    }
    void setName(const string& Name) {
        m_Name = Name;
    }

    // get/set GuildMemberRank
    GuildMemberRank_t getRank() const {
        return m_Rank;
    }
    void setRank(GuildMemberRank_t rank) {
        m_Rank = rank;
    }

    // get/set Guild Member LogOn
    bool getLogOn() const {
        return m_bLogOn;
    }
    void setLogOn(bool logOn) {
        m_bLogOn = logOn;
    }

    // get/set Guild Member Zone(current)
    ServerID_t getServerID() const {
        return m_ServerID;
    }
    void setServerID(ServerID_t ServerID) {
        m_ServerID = ServerID;
    }

private:
    // �̸�
    string m_Name;

    // Guild Member Rank
    GuildMemberRank_t m_Rank;


    // Guild Member LogOn
    bool m_bLogOn;

    // Guild Member Zone(current)
    ServerID_t m_ServerID;
};

#endif
