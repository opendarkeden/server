//////////////////////////////////////////////////////////////////////////////
// Filename		: Guild.h
// Written by	: bezz
// Description	:
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUILD_H__
#define __GUILD_H__

#include <list>

#include <unordered_map>

#include "Assert.h"
#include "Exception.h"
#include "Mutex.h"
#include "Types.h"
#include "VSDateTime.h"

#ifdef __SHARED_SERVER__
class GuildInfo2;
#endif

class GuildInfo;
class GCGuildMemberList;

//////////////////////////////////////////////////////////////////////////////
// class GuildMember
// ������� ���� ������ ������.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef __CHINA_SERVER__
const Gold_t REQUIRE_SLAYER_MASTER_GOLD = 50000000;
const Gold_t REQUIRE_VAMPIRE_MASTER_GOLD = 50000000;
const Gold_t REQUIRE_OUSTERS_MASTER_GOLD = 50000000;

const Gold_t REQUIRE_SLAYER_SUBMASTER_GOLD = 25000000;
const Gold_t REQUIRE_VAMPIRE_SUBMASTER_GOLD = 25000000;
const Gold_t REQUIRE_OUSTERS_SUBMASTER_GOLD = 25000000;

const Gold_t RETURN_SLAYER_MASTER_GOLD = 0;
const Gold_t RETURN_VAMPIRE_MASTER_GOLD = 0;
const Gold_t RETURN_OUSTERS_MASTER_GOLD = 0;

const Gold_t RETURN_SLAYER_SUBMASTER_GOLD = 0;
const Gold_t RETURN_VAMPIRE_SUBMASTER_GOLD = 0;
const Gold_t RETURN_OUSTERS_SUBMASTER_GOLD = 0;

const Fame_t REQUIRE_SLAYER_MASTER_FAME[SKILL_DOMAIN_ETC] = {
    500000, // SKILL_DOMAIN_BLADE
    500000, // SKILL_DOMAIN_SWORD
    500000, // SKILL_DOMAIN_GUN
    100000, // SKILL_DOMAIN_HEAL
    150000  // SKILL_DOMAIN_ENCHANT
};

const Fame_t REQUIRE_SLAYER_SUBMASTER_FAME[SKILL_DOMAIN_ETC] = {
    400000, // SKILL_DOMAIN_BLADE
    400000, // SKILL_DOMAIN_SWORD
    400000, // SKILL_DOMAIN_GUN
    75000,  // SKILL_DOMAIN_HEAL
    125000  // SKILL_DOMAIN_ENCHANT
};

#else
#ifndef __OLD_GUILD_WAR__
const Gold_t REQUIRE_SLAYER_MASTER_GOLD = 10000000;
const Gold_t REQUIRE_VAMPIRE_MASTER_GOLD = 10000000;
const Gold_t REQUIRE_OUSTERS_MASTER_GOLD = 10000000;

const Gold_t REQUIRE_SLAYER_SUBMASTER_GOLD = 0;
const Gold_t REQUIRE_VAMPIRE_SUBMASTER_GOLD = 0;
const Gold_t REQUIRE_OUSTERS_SUBMASTER_GOLD = 0;

const Gold_t RETURN_SLAYER_MASTER_GOLD = 9000000;
const Gold_t RETURN_VAMPIRE_MASTER_GOLD = 9000000;
const Gold_t RETURN_OUSTERS_MASTER_GOLD = 9000000;

const Gold_t RETURN_SLAYER_SUBMASTER_GOLD = 0;
const Gold_t RETURN_VAMPIRE_SUBMASTER_GOLD = 0;
const Gold_t RETURN_OUSTERS_SUBMASTER_GOLD = 0;

const Fame_t REQUIRE_SLAYER_MASTER_FAME[SKILL_DOMAIN_ETC] = {
    100000, // SKILL_DOMAIN_BLADE
    100000, // SKILL_DOMAIN_SWORD
    100000, // SKILL_DOMAIN_GUN
    20000,  // SKILL_DOMAIN_HEAL
    30000   // SKILL_DOMAIN_ENCHANT
};

const Fame_t REQUIRE_SLAYER_SUBMASTER_FAME[SKILL_DOMAIN_ETC] = {
    0, // SKILL_DOMAIN_BLADE
    0, // SKILL_DOMAIN_SWORD
    0, // SKILL_DOMAIN_GUN
    0, // SKILL_DOMAIN_HEAL
    0  // SKILL_DOMAIN_ENCHANT
};
#else
const Gold_t REQUIRE_SLAYER_MASTER_GOLD = 100000000;
const Gold_t REQUIRE_VAMPIRE_MASTER_GOLD = 100000000;
const Gold_t REQUIRE_OUSTERS_MASTER_GOLD = 100000000;

const Gold_t REQUIRE_SLAYER_SUBMASTER_GOLD = 50000000;
const Gold_t REQUIRE_VAMPIRE_SUBMASTER_GOLD = 50000000;
const Gold_t REQUIRE_OUSTERS_SUBMASTER_GOLD = 50000000;

const Gold_t RETURN_SLAYER_MASTER_GOLD = 90000000;
const Gold_t RETURN_VAMPIRE_MASTER_GOLD = 90000000;
const Gold_t RETURN_OUSTERS_MASTER_GOLD = 90000000;

const Gold_t RETURN_SLAYER_SUBMASTER_GOLD = 45000000;
const Gold_t RETURN_VAMPIRE_SUBMASTER_GOLD = 45000000;
const Gold_t RETURN_OUSTERS_SUBMASTER_GOLD = 45000000;

const Fame_t REQUIRE_SLAYER_MASTER_FAME[SKILL_DOMAIN_ETC] = {
    1000000, // SKILL_DOMAIN_BLADE
    1000000, // SKILL_DOMAIN_SWORD
    1000000, // SKILL_DOMAIN_GUN
    200000,  // SKILL_DOMAIN_HEAL
    300000   // SKILL_DOMAIN_ENCHANT
};

const Fame_t REQUIRE_SLAYER_SUBMASTER_FAME[SKILL_DOMAIN_ETC] = {
    800000, // SKILL_DOMAIN_BLADE
    800000, // SKILL_DOMAIN_SWORD
    800000, // SKILL_DOMAIN_GUN
    150000, // SKILL_DOMAIN_HEAL
    250000  // SKILL_DOMAIN_ENCHANT
};
#endif

#endif

const SkillLevel_t REQUIRE_SLAYER_MASTER_SKILL_DOMAIN_LEVEL = 50;
const Level_t REQUIRE_VAMPIRE_MASTER_LEVEL = 50;
const Level_t REQUIRE_OUSTERS_MASTER_LEVEL = 50;

#ifndef __OLD_GUILD_WAR__
const SkillLevel_t REQUIRE_SLAYER_SUBMASTER_SKILL_DOMAIN_LEVEL = 30;
#else
const SkillLevel_t REQUIRE_SLAYER_SUBMASTER_SKILL_DOMAIN_LEVEL = 40;
#endif
const Level_t REQUIRE_VAMPIRE_SUBMASTER_LEVEL = 40;
const Level_t REQUIRE_OUSTERS_SUBMASTER_LEVEL = 40;

class GuildMember {
public:
    GuildMember() noexcept;

    ///// Member constants /////

public:
    enum GuildRank {
        GUILDMEMBER_RANK_NORMAL = 0, // �Ϲ� ���
        GUILDMEMBER_RANK_MASTER,     // ��� ������
        GUILDMEMBER_RANK_SUBMASTER,  // ��� ���� ������
        GUILDMEMBER_RANK_WAIT,       // ��� ���� ���
        GUILDMEMBER_RANK_DENY,       // �߹�/�ź� ����
        GUILDMEMBER_RANK_LEAVE,      // ��� Ż��(������)

        GUILDMEMBER_RANK_MAX
    };


public: // DB methods
    void create() noexcept(false);
    bool load() noexcept(false);
    void save() noexcept(false);
    void destroy() noexcept(false);
    void expire() noexcept(false);
    void leave() noexcept(false);

    void saveIntro(const string& intro) noexcept(false);
    string getIntro() const noexcept(false);


public: // identity methods
    GuildID_t getGuildID() const noexcept {
        return m_GuildID;
    }
    void setGuildID(GuildID_t guildID) noexcept {
        m_GuildID = guildID;
    }

    string getName() const noexcept {
        return m_Name;
    }
    void setName(const string& name) noexcept {
        m_Name = name;
    }

    GuildMemberRank_t getRank() const noexcept {
        return m_Rank;
    }
    void setRank(GuildMemberRank_t rank) noexcept(false); // Guild class ���� ó���Ѵ�.

    bool getLogOn() const noexcept {
        return m_bLogOn;
    }
    void setLogOn(bool logOn) noexcept {
        m_bLogOn = logOn;
    }

    ServerID_t getServerID() const noexcept {
        return m_ServerID;
    }
    void setServerID(ServerID_t ServerID) noexcept {
        m_ServerID = ServerID;
    }

    string getRequestDateTime() const noexcept(false);
    void setRequestDateTime(const VSDateTime& vsdatetime) noexcept {
        m_RequestDateTime = vsdatetime;
    }
    void setRequestDateTime(const string& rdatetime) noexcept(false);
    bool isRequestDateTimeOut(const VSDateTime& currentDateTime) const noexcept;

public: // debug
    string toString() const noexcept;


    ///// operator overloadgin /////

public:
    GuildMember& operator=(GuildMember& Member);


    ///// Member data /////

protected:
    GuildID_t m_GuildID;          // ��� ID
    string m_Name;                // ��� �̸�
    GuildMemberRank_t m_Rank;     // ����� ���
    VSDateTime m_RequestDateTime; // ���� ��û �ð�
    bool m_bLogOn;                // ���� ����
    ServerID_t m_ServerID;        // ���� ��ġ
};


//////////////////////////////////////////////////////////////////////////////
// class Guild
// ��忡 ���� ������ ������.
//
// GuildInfo ���̺��� ����
// ----------------------------------------
// GuildID            INT
// GuildName          VARCHAR(20)
// GuildType          TINYINT
// GuildGold          INT
// ----------------------------------------
//////////////////////////////////////////////////////////////////////////////

#ifndef __OLD_GUILD_WAR__
#define MAX_GUILDMEMBER_ACTIVE_COUNT 100
#define MIN_GUILDMEMBER_COUNT 3
#else
#define MAX_GUILDMEMBER_ACTIVE_COUNT 230
#define MIN_GUILDMEMBER_COUNT 5
#endif
#define MAX_GUILDMEMBER_WAIT_COUNT 15

typedef unordered_map<string, GuildMember*> HashMapGuildMember;
typedef HashMapGuildMember::iterator HashMapGuildMemberItor;
typedef HashMapGuildMember::const_iterator HashMapGuildMemberConstItor;

class Guild {
    ///// Member constants /////

public:
    enum GuildTypes {
        GUILD_TYPE_NORMAL = 0, // �Ϲ� ���
        GUILD_TYPE_JUDGE,      // �ǰ� ���
        GUILD_TYPE_ASSASSIN,   // �ϻ��� ���

        GUILD_TYPE_MAX
    };

    enum GuildState {
        GUILD_STATE_ACTIVE = 0, // Ȱ�� ���� ���
        GUILD_STATE_WAIT,       // ��� ��� ���� ���
        GUILD_STATE_CANCEL,     // ��ҵ� ���
        GUILD_STATE_BROKEN,     // ��ü�� ���

        GUILD_STATE_MAX
    };

    enum GuildRace {
        GUILD_RACE_SLAYER = 0, // �����̾� ���
        GUILD_RACE_VAMPIRE,    // �����̾� ���
        GUILD_RACE_OUSTERS,    // �ƿ콺���� ���

        GUILD_RACE_MAX
    };

public: // constructor & destructor
    Guild() noexcept(false);
    virtual ~Guild() noexcept;


public: // DB methods
    void create() noexcept(false);
    bool load() noexcept(false);
    void save() noexcept(false);
    void destroy() noexcept(false);


public: // identity methods
    GuildID_t getID() const noexcept {
        return m_ID;
    }
    void setID(GuildID_t id) noexcept {
        m_ID = id;
    }

    string getName() const noexcept {
        return m_Name;
    }
    void setName(const string& name) noexcept {
        m_Name = name;
    }

    GuildType_t getType() const noexcept {
        return m_Type;
    }
    void setType(GuildType_t type) noexcept {
        m_Type = type;
    }

    GuildRace_t getRace() const noexcept {
        return m_Race;
    }
    void setRace(GuildRace_t race) noexcept {
        m_Race = race;
    }

    GuildState_t getState() const noexcept {
        return m_State;
    }
    void setState(GuildState_t state) noexcept {
        m_State = state;
    }

    ServerGroupID_t getServerGroupID() const noexcept {
        return m_ServerGroupID;
    }
    void setServerGroupID(ServerGroupID_t serverGroupID) noexcept {
        m_ServerGroupID = serverGroupID;
    }

    ZoneID_t getZoneID() const noexcept {
        return m_ZoneID;
    }
    void setZoneID(ZoneID_t zoneID) noexcept {
        m_ZoneID = zoneID;
    }

    string getMaster() const noexcept {
        return m_Master;
    }
    void setMaster(const string& master) noexcept {
        m_Master = master;
    }

    string getDate() const noexcept {
        return m_Date;
    }
    void setDate(const string& Date) noexcept {
        m_Date = Date;
    }

    string getIntro() const noexcept {
        return m_Intro;
    }
    void setIntro(const string& intro) noexcept {
        m_Intro = intro;
    }

#ifdef __SHARED_SERVER__
    void saveIntro(const string& intro) noexcept(false);
    void tinysave(const char* field) const noexcept(false);
    void saveCount() const noexcept(false);
#endif


    ///// GuildMember get/add/delete/modify /////
    GuildMember* getMember(const string& name) const noexcept(false);
    GuildMember* getMember_NOLOCKED(const string& name) const noexcept(false);
    void addMember(GuildMember* pMember) noexcept(false);
    void deleteMember(const string& name) noexcept(false);
    void modifyMember(GuildMember& Member) noexcept(false);

    void modifyMemberRank(const string& name, GuildMemberRank_t rank) noexcept(false);

    HashMapGuildMember& getMembers() noexcept {
        return m_Members;
    }

    int getActiveMemberCount() const noexcept {
        return m_ActiveMemberCount;
    }
    int getWaitMemberCount() const noexcept {
        return m_WaitMemberCount;
    }

#ifdef __GAME_SERVER__
    void addCurrentMember(const string& name) noexcept(false);
    void deleteCurrentMember(const string& name) noexcept(false);
    list<string> getCurrentMembers() noexcept(false);
#endif

#ifdef __SHARED_SERVER__
    void makeInfo(GuildInfo2* pGulidInfo) noexcept(false);
#endif

    void makeInfo(GuildInfo* pGuildInfo) noexcept(false);
    void makeMemberInfo(GCGuildMemberList& gcGuildMemberList) noexcept(false);


public: // static
    static GuildID_t getMaxGuildID() noexcept {
        return m_MaxGuildID;
    }
    static void setMaxGuildID(GuildID_t id) noexcept {
        m_MaxGuildID = id;
    }

    static ZoneID_t getMaxSlayerZoneID() noexcept {
        return m_MaxSlayerZoneID;
    }
    static void setMaxSlayerZoneID(ZoneID_t zoneID) noexcept {
        m_MaxSlayerZoneID = zoneID;
    }

    static ZoneID_t getMaxVampireZoneID() noexcept {
        return m_MaxVampireZoneID;
    }
    static void setMaxVampireZoneID(ZoneID_t zoneID) noexcept {
        m_MaxVampireZoneID = zoneID;
    }

    static ZoneID_t getMaxOustersZoneID() noexcept {
        return m_MaxOustersZoneID;
    }
    static void setMaxOustersZoneID(ZoneID_t zoneID) noexcept {
        m_MaxOustersZoneID = zoneID;
    }

public:
    void expireTimeOutWaitMember(VSDateTime currentDateTime, list<string>& mList) noexcept(false);

public: // debug
    string toString() const noexcept;

    static string correctString(const string& str) noexcept;


    ///// Member data /////

protected:
    GuildID_t m_ID;                  // ��� ID
    string m_Name;                   // ��� �̸�
    GuildType_t m_Type;              // ��� Ÿ��
    GuildRace_t m_Race;              // ��� ����
    GuildState_t m_State;            // ��� ����
    ServerGroupID_t m_ServerGroupID; // ��� ���� �ִ� ���� �׷� ID
    ZoneID_t m_ZoneID;               // ��� ZoneID
    string m_Master;                 // ��� ������
    string m_Date;                   // ��� Expire, Regist Date
    string m_Intro;                  // ��� �Ұ�

    HashMapGuildMember m_Members; // ��� ��� ������ ��
    int m_ActiveMemberCount;      // Active Member Count
    int m_WaitMemberCount;        // Wait Member Count

    static GuildID_t m_MaxGuildID;      // ��� ���̵� �ִ밪
    static ZoneID_t m_MaxSlayerZoneID;  // �����̾� ��� �� ID �ִ밪
    static ZoneID_t m_MaxVampireZoneID; // �����̾� ��� �� ID �ִ밪
    static ZoneID_t m_MaxOustersZoneID; // �ƿ콺���� ��� �� ID �ִ밪

    mutable Mutex m_Mutex; // Mutex for Guild

#ifdef __GAME_SERVER__
    list<string> m_CurrentMembers; // ���� ���� ���� ���
#endif
};

#endif
