//////////////////////////////////////////////////////////////////////////////
// Filename    : GuildManager.h
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUILDMANAGER_H__
#define __GUILDMANAGER_H__

#include "Types.h"
#include "Assert1.h"
#include "Exception.h"
#include "Mutex.h"
#include "Timeval.h"
#include <map>

class Guild;

typedef map<GuildID_t, Guild*> HashMapGuild;
typedef map<GuildID_t, Guild*>::iterator HashMapGuildItor;
typedef map<GuildID_t, Guild*>::const_iterator HashMapGuildConstItor;

#ifdef __SHARED_SERVER__
class SGGuildInfo;
#endif

class GCWaitGuildList;
class GCActiveGuildList;
class PlayerCreature;

class GuildManager {
public:
    GuildManager() throw();
    ~GuildManager() throw();

    void init() throw();
    void load() throw();

    void addGuild(Guild* pGuild) throw(DuplicatedException);
    void addGuild_NOBLOCKED(Guild* pGuild) throw(DuplicatedException);
    void deleteGuild(GuildID_t id) throw(NoSuchElementException);
    Guild* getGuild(GuildID_t id) throw();
    Guild* getGuild_NOBLOCKED(GuildID_t id) throw();

    void clear() throw();
    void clear_NOBLOCKED();


    ushort getGuildSize() const throw() { return m_Guilds.size(); }
    HashMapGuild& getGuilds() throw() { return m_Guilds; }
    const HashMapGuild& getGuilds_const() const throw() { return m_Guilds; }

#ifdef __SHARED_SERVER__
    void makeSGGuildInfo(SGGuildInfo& sgGuildInfo) throw();
#endif

    void makeWaitGuildList(GCWaitGuildList& gcWaitGuildList, GuildRace_t race) throw();
    void makeActiveGuildList(GCActiveGuildList& gcWaitGuildList, GuildRace_t race) throw();

    void lock() { m_Mutex.lock(); }
    void unlock() { m_Mutex.unlock(); }

    void heartbeat() throw(Error);

    bool isGuildMaster(GuildID_t guildID, PlayerCreature* pPC) throw(Error);

    string getGuildName(GuildID_t guildID) throw(Error);

    // 길드가 성을 가졌나?
    bool hasCastle(GuildID_t guildID) throw(Error);
    bool hasCastle(GuildID_t guildID, ServerID_t& serverID, ZoneID_t& zoneID) throw(Error);

    // 길드가 전쟁신청을 했나?
    bool hasWarSchedule(GuildID_t guildID) throw(Error);

    // 현재 진행중인 전쟁이 있는가?
    bool hasActiveWar(GuildID_t guidlID) throw(Error);

    string toString(void) const throw();


protected:
    map<GuildID_t, Guild*> m_Guilds;        // 길드 포인터 맵

    Timeval m_WaitMemberClearTime;          // heartbeat 에서 Wait 중인 길드멤버 정리 시간

    mutable Mutex m_Mutex;
};

extern GuildManager* g_pGuildManager;

#endif // __GUILDINFO_H__
