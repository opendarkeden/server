#ifndef __LEVEL_WAR_MANAGER_H__
#define __LEVEL_WAR_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"

#include "war/Scheduler.h"
#include "war/Work.h"

#include "SweeperSet.h"
#include "VSDateTime.h"

#include "GCWarList.h"

class PlayerCreature;

extern int LevelWarTime[4][3];

class LevelWarManager : public Scheduler
{
	enum RACEINDEX
	{
		SLAYER,
		VAMPIRE,
		OUSTERS,
		NONE
	};

public:
	LevelWarManager(int level, Zone* pZone) : m_Level(level), m_pZone(pZone), m_bHasWar(false), m_bHasWarToDay(false), m_bCanEnterFreeUser(false)
	{ 
		m_pLevelWarSchedule = NULL;
		m_MutexWarList.setName("WarList");
	}
	virtual ~LevelWarManager() throw()
	{ 
		SAFE_DELETE(m_pLevelWarSchedule);
	}

	void init();

	virtual Work* heartbeat() throw(Error);
	bool hasWar() const { return m_bHasWar; }
	bool hasToDayWar() const { return m_bHasWarToDay; }
	void startWar();
	void endWar();
	void manualStart();

	bool isSafe(MonsterCorpse* pCorpse ) const { return m_SweeperSetManager.getSafeIndex(pCorpse ) != -1; }
	bool putSweeper(PlayerCreature* pPC, Item* pItem , MonsterCorpse* pCorpse);
	int getSafeIndex(MonsterCorpse* pCorpse ) const { return m_SweeperSetManager.getSafeIndex(pCorpse); }

	VSDateTime getNextLevelWarTime() const;

	void fixTimeband(uint timeband ) throw(Error);
	void resumeTimeband() throw(Error);

	void killAllMonsters() throw(Error);

	int getStartHour();

	bool makeGCWarList() throw(Error);
	void sendGCWarList(Player* pPlayer) throw(Error);
	void broadcastGCWarList() throw(Error);

	bool canEnterFreeUser() throw(Error) { return m_bCanEnterFreeUser; }
	void freeUserTimeCheck() throw(Error);

    const VSDateTime&   getLevelWarStartTime() const     { return m_StartTime; }
    void                setLevelWarStartTime(VSDateTime dt) { m_StartTime = dt; }

	void recordLevelWarStart();
	void recordLevelWarEnd();

private:
	int		m_Level;
	Zone*	m_pZone;
	SweeperSetManager m_SweeperSetManager;

	bool	m_bHasWar;
	bool	m_bHasWarToDay;

	bool 	m_bCanEnterFreeUser;

	VSDateTime          m_StartTime;            // 전쟁 시작 시간

	GCWarList		m_GCWarList;
	mutable	Mutex	m_MutexWarList;

	Schedule* 	m_pLevelWarSchedule;

};

#endif // __LEVEL_WAR_MANAGER_H__

