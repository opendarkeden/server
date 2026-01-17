//////////////////////////////////////////////////////////////////////////////
// Filename    : GuildManager.h
// Written By  : �輺��
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
// ���� Ȱ������ ���� ��� ������� ��带 �޸𸮿� map ���·� ������ �ְ�,
// ���ο� ����� ���/������ ����Ѵ�.
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
	GuildManager() noexcept;
	~GuildManager() noexcept;


public: // initializing related methods
	void init() noexcept(false);
	void load() noexcept(false);


public: // memory related methods
	void addGuild(Guild* pGuild) noexcept(false);
	void addGuild_NOBLOCKED(Guild* pGuild) noexcept(false);
	void deleteGuild(GuildID_t id) noexcept(false);
	Guild* getGuild(GuildID_t id) noexcept(false);
	Guild* getGuild_NOBLOCKED(GuildID_t id) noexcept(false);

	void clear() noexcept(false);
	void clear_NOBLOCKED();


public: // misc methods
	ushort getGuildSize() const noexcept { return m_Guilds.size(); }
	HashMapGuild& getGuilds() noexcept { return m_Guilds; }
	const HashMapGuild& getGuilds_const() const noexcept { return m_Guilds; }

#ifdef __SHARED_SERVER__
public:
	void makeSGGuildInfo( SGGuildInfo& sgGuildInfo ) noexcept(false);
#endif

	void makeWaitGuildList( GCWaitGuildList& gcWaitGuildList, GuildRace_t race ) noexcept(false);
	void makeActiveGuildList( GCActiveGuildList& gcWaitGuildList, GuildRace_t race ) noexcept(false);

public:
	void lock() { m_Mutex.lock(); }
	void unlock() { m_Mutex.unlock(); }


public:
	void heartbeat() noexcept(false);

public:
	bool isGuildMaster( GuildID_t guildID, PlayerCreature* pPC ) noexcept(false);

	string getGuildName( GuildID_t guildID ) noexcept(false);

	// ��尡 ���� ������?
	bool hasCastle( GuildID_t guildID ) noexcept(false);
	bool hasCastle( GuildID_t guildID, ServerID_t& serverID, ZoneID_t& zoneID ) noexcept(false);

	// ��尡 �����û�� �߳�?
	bool hasWarSchedule( GuildID_t guildID ) noexcept(false);

	// ���� �������� ������ �ִ°�?
	bool hasActiveWar( GuildID_t guidlID ) noexcept(false);

public: // debug
	string toString(void) const noexcept;


///// Member data /////
	
protected:
	unordered_map<GuildID_t, Guild*> m_Guilds;		// ��� ������ ��

	Timeval m_WaitMemberClearTime;				// heartbeat ���� Wait ���� ����� ���� �ð�

	// mutex
	mutable Mutex m_Mutex;
};

extern GuildManager* g_pGuildManager;

#endif // __GUILDINFO_H__
