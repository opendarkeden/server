///////////////////////////////////////////////////////////////////
// FlagManager.h
//
// Global하게 1개만 돌아가야 한다.
///////////////////////////////////////////////////////////////////

#ifndef __FLAG_MANAGER_H__
#define __FLAG_MANAGER_H__

#include "Types.h"
#include "war/Work.h"
#include "war/Scheduler.h"
#include "Mutex.h"
#include "Exception.h"
#include "Assert.h"
//#include "ZoneGroupManager.h"
#include "VSDateTime.h"

#include "Gpackets/GCFlagWarStatus.h"

#include <vector>
#include <map>

class PlayerCreature;
class MonsterCorpse;
class Zone;
class Item;

class FlagManager : public Scheduler
{
	enum RACEINDEX
	{
		SLAYER,
		VAMPIRE,
		OUSTERS,
		NONE
	};

	struct PoleFieldInfo
	{
		ZoneID_t zoneID;
		ZoneCoord_t l, t, w, h;

		PoleFieldInfo() { zoneID = l = t = w = h = 0; }
		PoleFieldInfo( ZoneID_t zID, ZoneCoord_t left, ZoneCoord_t top, ZoneCoord_t width, ZoneCoord_t height )
		{ zoneID=zID; l=left; t=top; w=width; h=height; }
		bool isInField(ZONE_COORD pos) { return pos.id == zoneID && ( pos.x >= l && pos.x < l+w ) && ( pos.y >= t && pos.y < t+h ); }
	};
public:
	FlagManager();
	virtual ~FlagManager();

public:
	void init();
	bool putFlag( PlayerCreature* pPC, MonsterCorpse* pFlagPole );
	bool getFlag( PlayerCreature* pPC, MonsterCorpse* pFlagPole );

	void setNextSchedule();

	void manualStart();

public:
	bool hasFlagWar() const { return m_bHasFlagWar; }
	Race_t getWinnerRace();
	uint getFlagCount( Race_t race ) { return m_FlagCount[(RACEINDEX)race]; }

	bool startFlagWar();
	bool endFlagWar();

	bool isFlagPole( MonsterCorpse* pFlagPole ) { return m_FlagPoles.find(pFlagPole) != m_FlagPoles.end(); }
	bool isFlagAllowedZone( ZoneID_t ZoneID ) const { return m_FlagAllowMap.find(ZoneID) != m_FlagAllowMap.end(); }

	map<ZoneID_t, uint>& getAllowMap() { return m_FlagAllowMap; }

	Packet* getStatusPacket() { m_StatusPacket.setTimeRemain(remainWarTimeSecs()); return &m_StatusPacket; }
	void broadcastStatus() { if ( hasFlagWar() ) broadcastPacket(getStatusPacket()); }//g_pZoneGroupManager->broadcast(getStatusPacket());
	const map<MonsterCorpse*, Race_t>& getFlagPoleRaceMap() const { return m_FlagPoles; }

	Race_t getFlagPoleRace( MonsterCorpse* pFlagPole ) { return m_FlagPoles[pFlagPole]; }

	bool putFlag( PlayerCreature* pPC, Item* pItem, MonsterCorpse* pFlagPole );
	int remainWarTimeSecs() { return VSDateTime::currentDateTime().secsTo( m_EndTime ); }

//	VSDateTime getNextFlagWarTime();

	void resetFlagCounts();
	bool isInPoleField( ZONE_COORD zc );

	void recordPutFlag( PlayerCreature* pPC, Item* pItem ) throw(Error);
	void recordFlagWarHistory() throw(Error);

	void broadcastPacket( Packet* pPacket ) const;

public:
	void	lock() throw (Error)		{ m_Mutex.lock(); }
	void	unlock() throw (Error)		{ m_Mutex.unlock(); }

protected:
	void addPoleField( Zone* pZone, ZoneCoord_t left, ZoneCoord_t top, uint width, uint height, Race_t race, MonsterType_t type );

private:
	map<RACEINDEX,uint>	m_FlagCount;
	mutable Mutex	m_Mutex;

	// 종족 추가할 일 없겠지? -_-;
	map<MonsterCorpse*, Race_t>	m_FlagPoles;
	GCFlagWarStatus m_StatusPacket;

	map<ZoneID_t, uint> m_FlagAllowMap;

	VSDateTime m_EndTime;
	map<Race_t, VSDateTime> m_PutTime;

	list<PoleFieldInfo> m_PoleFields;

	bool	m_bHasFlagWar;
};

extern FlagManager* g_pFlagManager;

#endif
