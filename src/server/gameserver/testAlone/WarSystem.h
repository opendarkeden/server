#ifndef __WAR_SYSTEM_H__
#define __WAR_SYSTEM_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include "Scheduler.h"
#include "Gpackets/GCWarList.h"

class War;
class WarSchedule;
class Item;
class MonsterCorpse;
class Player;
class GamePlayer;
class PlayerCreature;
class WarScheduleInfo;

class ActiveWarInfo
{
public :
	ActiveWarInfo( ZoneID_t zoneID, GuildID_t attackGuildID=0 )
		: ZoneID(zoneID), AttackGuildID(attackGuildID) {}

	bool operator == (const ActiveWarInfo& awi) const
	{
		return ZoneID==awi.ZoneID;
	}

	bool operator != (const ActiveWarInfo& awi) const
	{
		return ZoneID!=awi.ZoneID;
	}

public :
	ZoneID_t	ZoneID;
	GuildID_t	AttackGuildID;
};

class WarSystem : public Scheduler {
public :
	WarSystem() throw (Error);
	~WarSystem() throw (Error);

	void	init() throw (Error);
	void	load() throw (Error);

	bool	addWarDelayed(War* pWar) throw (Error);
	bool	isEndCondition(Item* pItem, MonsterCorpse* pMonsterCorpse) throw (Error);
	bool	endWar(PlayerCreature* pPC, ZoneID_t castleZoneID) throw (Error);
	bool	removeWar(ZoneID_t castleZoneID) throw (Error);
	bool	removeRaceWar() throw (Error);

	bool	makeGCWarList() throw (Error);
	bool	makeGCWarList_LOCKED() throw (Error);
	void	sendGCWarList(Player* pPlayer) throw (Error);
	bool	addRaceWarScheduleInfo(WarScheduleInfo* pWSI) throw (Error);

	virtual Work* heartbeat() throw(Error);

// public :
//	void	lock() throw (Error)	{ m_Mutex.lock(); }
//	void	unlock() throw (Error)	{ m_Mutex.unlock(); }

public :
	static WarID_t		getWarIDSuccessor()	{ return s_WarIDSuccessor; }
	static void			setWarIDSuccessor(WarID_t wid)	{ s_WarIDSuccessor = wid; }

protected :
	VSDateTime 		getWarEndTime(WarType_t warType) const;
	bool			addQueuedWar() throw (Error);
	bool			addWar(War* pWar) throw (Error);
	War* 			getActiveRaceWarAtSameThread() const throw(Error);
	bool 			checkStartRaceWar() throw (Error);

public :
	bool			hasCastleActiveWar( ZoneID_t zoneID ) const throw(Error);
	bool			getAttackGuildID( ZoneID_t zoneID, GuildID_t& guildID ) const throw(Error);
	War*			getActiveWar( ZoneID_t zoneID ) const throw(Error);
	WarSchedule*	getActiveWarSchedule_LOCKED( ZoneID_t zoneID ) throw (Error);
	WarSchedule*	getActiveWarSchedule( ZoneID_t zoneID ) throw (Error);
	bool			isModifyCastleOwner( ZoneID_t castleZoneID, PlayerCreature* pPC ) throw (Error);

	bool			hasActiveRaceWar() const throw(Error)	{ return m_bHasRaceWar; }
	War*			getActiveRaceWar() const throw(Error);

	bool			isWarActive() const { return !isEmpty(); }

public :
	void			broadcastWarList( GamePlayer* pGamePlayer ) const throw (Error);
	bool			startRaceWar() throw(Error);
	void 			prepareRaceWar() throw (Error);

private :
	static WarID_t 		s_WarIDSuccessor;

	mutable Mutex		m_Mutex;
	mutable Mutex		m_MutexWarQueue;
	mutable Mutex		m_MutexActiveWars;
	mutable Mutex		m_MutexWarList;

	GCWarList 			m_GCWarList;
	list<War*>			m_WarQueue;

	bool				m_bHasRaceWar;

	list<ActiveWarInfo>		m_ActiveWars;

	Schedule*			m_pRaceWarSchedule;
};

extern WarSystem* g_pWarSystem;

#endif
