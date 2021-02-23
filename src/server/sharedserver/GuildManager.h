//////////////////////////////////////////////////////////////////////////////
// Filename    : GuildManager.h
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUILDMANAGER_H__
#define __GUILDMANAGER_H__

#include "Types.h"
#include "Assert.h"
#include "Exception.h"
#include "Mutex.h"
#include "Timeval.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class GuildManager
// 현재 활동중인 길드와 등록 대기중인 길드를 메모리에 map 형태로 가지고 있고,
// 새로운 길드의 등록/삭제를 담당한다.
//
//////////////////////////////////////////////////////////////////////////////

class Guild;

typedef hash_map<GuildID_t, Guild*> HashMapGuild;
typedef hash_map<GuildID_t, Guild*>::iterator HashMapGuildItor;
typedef hash_map<GuildID_t, Guild*>::const_iterator HashMapGuildConstItor;

#ifdef __SHARED_SERVER__
class SGGuildInfo;
#endif

class GCWaitGuildList;
class GCActiveGuildList;
class PlayerCreature;

class GuildManager
{

///// Member methods /////
	
public: // constructor & destructor 
	GuildManager() throw();
	~GuildManager() throw();


public: // initializing related methods
	void init() throw();
	void load() throw();


public: // memory related methods
	void addGuild(Guild* pGuild) throw(DuplicatedException);
	void addGuild_NOBLOCKED(Guild* pGuild) throw(DuplicatedException);
	void deleteGuild(GuildID_t id) throw(NoSuchElementException);
	Guild* getGuild(GuildID_t id) throw();
	Guild* getGuild_NOBLOCKED(GuildID_t id) throw();

	void clear() throw();
	void clear_NOBLOCKED();


public: // misc methods
	ushort getGuildSize() const throw() { return m_Guilds.size(); }
	HashMapGuild& getGuilds() throw() { return m_Guilds; }
	const HashMapGuild& getGuilds_const() const throw() { return m_Guilds; }

#ifdef __SHARED_SERVER__
public:
	void makeSGGuildInfo( SGGuildInfo& sgGuildInfo ) throw();
#endif

	void makeWaitGuildList( GCWaitGuildList& gcWaitGuildList, GuildRace_t race ) throw();
	void makeActiveGuildList( GCActiveGuildList& gcWaitGuildList, GuildRace_t race ) throw();

public:
	void lock() { m_Mutex.lock(); }
	void unlock() { m_Mutex.unlock(); }


public:
	void heartbeat() throw(Error);

public:
	bool isGuildMaster( GuildID_t guildID, PlayerCreature* pPC ) throw(Error);

	string getGuildName( GuildID_t guildID ) throw (Error);

	// 길드가 성을 가졌나?
	bool hasCastle( GuildID_t guildID ) throw(Error);
	bool hasCastle( GuildID_t guildID, ServerID_t& serverID, ZoneID_t& zoneID ) throw(Error);

	// 길드가 전쟁신청을 했나?
	bool hasWarSchedule( GuildID_t guildID ) throw(Error);

	// 현재 진행중인 전쟁이 있는가?
	bool hasActiveWar( GuildID_t guidlID ) throw(Error);

public: // debug
	string toString(void) const throw();


///// Member data /////
	
protected:
	hash_map<GuildID_t, Guild*> m_Guilds;		// 길드 포인터 맵

	Timeval m_WaitMemberClearTime;				// heartbeat 에서 Wait 중인 길드멤버 정리 시간

	// mutex
	mutable Mutex m_Mutex;
};

extern GuildManager* g_pGuildManager;

#endif // __GUILDINFO_H__
