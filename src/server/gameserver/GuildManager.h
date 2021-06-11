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
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////////
// class GuildManager
// 현재 활동중인 길드와 등록 대기중인 길드를 메모리에 map 형태로 가지고 있고,
// 새로운 길드의 등록/삭제를 담당한다.
//
//////////////////////////////////////////////////////////////////////////////

class Guild;

typedef unordered_map<GuildID_t, Guild*> HashMapGuild;
typedef unordered_map<GuildID_t, Guild*>::iterator HashMapGuildItor;
typedef unordered_map<GuildID_t, Guild*>::const_iterator HashMapGuildConstItor;

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
	GuildManager() ;
	~GuildManager() ;


public: // initializing related methods
	void init() ;
	void load() ;


public: // memory related methods
	void addGuild(Guild* pGuild) ;
	void addGuild_NOBLOCKED(Guild* pGuild) ;
	void deleteGuild(GuildID_t id) ;
	Guild* getGuild(GuildID_t id) ;
	Guild* getGuild_NOBLOCKED(GuildID_t id) ;

	void clear() ;
	void clear_NOBLOCKED();


public: // misc methods
	ushort getGuildSize() const  { return m_Guilds.size(); }
	HashMapGuild& getGuilds()  { return m_Guilds; }
	const HashMapGuild& getGuilds_const() const  { return m_Guilds; }

#ifdef __SHARED_SERVER__
public:
	void makeSGGuildInfo( SGGuildInfo& sgGuildInfo ) ;
#endif

	void makeWaitGuildList( GCWaitGuildList& gcWaitGuildList, GuildRace_t race ) ;
	void makeActiveGuildList( GCActiveGuildList& gcWaitGuildList, GuildRace_t race ) ;

public:
	void lock() { m_Mutex.lock(); }
	void unlock() { m_Mutex.unlock(); }


public:
	void heartbeat() ;

public:
	bool isGuildMaster( GuildID_t guildID, PlayerCreature* pPC ) ;

	string getGuildName( GuildID_t guildID ) ;

	// 길드가 성을 가졌나?
	bool hasCastle( GuildID_t guildID ) ;
	bool hasCastle( GuildID_t guildID, ServerID_t& serverID, ZoneID_t& zoneID ) ;

	// 길드가 전쟁신청을 했나?
	bool hasWarSchedule( GuildID_t guildID ) ;

	// 현재 진행중인 전쟁이 있는가?
	bool hasActiveWar( GuildID_t guidlID ) ;

public: // debug
	string toString(void) const ;


///// Member data /////
	
protected:
	unordered_map<GuildID_t, Guild*> m_Guilds;		// 길드 포인터 맵

	Timeval m_WaitMemberClearTime;				// heartbeat 에서 Wait 중인 길드멤버 정리 시간

	// mutex
	mutable Mutex m_Mutex;
};

extern GuildManager* g_pGuildManager;

#endif // __GUILDINFO_H__
