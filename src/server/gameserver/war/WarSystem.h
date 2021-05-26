#ifndef __WAR_SYSTEM_H__
#define __WAR_SYSTEM_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include "Scheduler.h"
#include "GCWarList.h"

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
	WarSystem() ;
	~WarSystem() ;

	void	init() ;
	void	load() ;

	bool	addWarDelayed(War* pWar) ;
	bool	isEndCondition(Item* pItem, MonsterCorpse* pMonsterCorpse) ;
	bool	endWar(PlayerCreature* pPC, ZoneID_t castleZoneID) ;
	bool	removeWar(ZoneID_t castleZoneID) ;
	bool	removeRaceWar() ;

	bool	makeGCWarList() ;
	bool	makeGCWarList_LOCKED() ;
	void	sendGCWarList(Player* pPlayer) ;
	bool	addRaceWarScheduleInfo(WarScheduleInfo* pWSI) ;

	virtual Work* heartbeat() ;

// public :
//	void	lock() 	{ m_Mutex.lock(); }
//	void	unlock() 	{ m_Mutex.unlock(); }

public :
	static WarID_t		getWarIDSuccessor()	{ return s_WarIDSuccessor; }
	static void			setWarIDSuccessor(WarID_t wid)	{ s_WarIDSuccessor = wid; }

protected :
	VSDateTime 		getWarEndTime(WarType_t warType) const;
	bool			addQueuedWar() ;
	bool			addWar(War* pWar) ;
	War* 			getActiveRaceWarAtSameThread() const ;
	bool 			checkStartRaceWar() ;

public :
	bool			hasCastleActiveWar( ZoneID_t zoneID ) const ;
	bool			getAttackGuildID( ZoneID_t zoneID, GuildID_t& guildID ) const ;
	War*			getActiveWar( ZoneID_t zoneID ) const ;
	WarSchedule*	getActiveWarSchedule_LOCKED( ZoneID_t zoneID ) ;
	WarSchedule*	getActiveWarSchedule( ZoneID_t zoneID ) ;
	bool			isModifyCastleOwner( ZoneID_t castleZoneID, PlayerCreature* pPC ) ;

	bool			hasActiveRaceWar() const 	{ return m_bHasRaceWar; }
	War*			getActiveRaceWar() const ;

	bool			isWarActive() const { return !isEmpty(); }
	bool			isRaceWarToday() const { return m_bRaceWarToday; }
	DWORD			getRaceWarTimeParam() const { return m_RaceWarTimeParam; }

public :
	void			broadcastWarList( GamePlayer* pGamePlayer ) const ;
	bool			startRaceWar() ;
	void 			prepareRaceWar() ;

	bool			canApplyBloodBibleSign() const { return !m_b20Minutes; }
	bool			isSkyBlack() const { return m_b5Minutes; }

private :
	static WarID_t 		s_WarIDSuccessor;

	mutable Mutex		m_Mutex;
	mutable Mutex		m_MutexWarQueue;
	mutable Mutex		m_MutexActiveWars;
	mutable Mutex		m_MutexWarList;

	GCWarList 			m_GCWarList;
	list<War*>			m_WarQueue;

	bool				m_bHasRaceWar;
	bool				m_bRaceWarToday;
	DWORD				m_RaceWarTimeParam;

	list<ActiveWarInfo>		m_ActiveWars;

	Schedule*			m_pRaceWarSchedule;

	bool				m_b20Minutes;
	bool				m_b5Minutes;
};

extern WarSystem* g_pWarSystem;

#endif
