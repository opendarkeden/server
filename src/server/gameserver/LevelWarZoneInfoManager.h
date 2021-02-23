#ifndef __LEVEL_WAR_ZONE_INFO_MANAGER_H__
#define __LEVEL_WAR_ZONE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Mutex.h"

class Packet;

class LevelWarZoneInfo
{

public:
	LevelWarZoneInfo();
	~LevelWarZoneInfo();

public:

	int						getGrade() const	{ return m_LevelWarGrade; }
	void					setGrade( int grade ) 	{ m_LevelWarGrade = grade; }

	ZoneID_t				getZoneID() const	{ return m_ZoneID; }
	void					setZoneID(const ZoneID_t zoneID)	{ m_ZoneID = zoneID; }

	SweeperBonusType_t 		getMinSweeperBonusType() const	{ return m_SweeperTypeMin; }
	void	 				setMinSweeperBonusType(const SweeperBonusType_t sweeperBonusType)	{ m_SweeperTypeMin = sweeperBonusType; }

	SweeperBonusType_t 		getMaxSweeperBonusType() const	{ return m_SweeperTypeMin; }
	void	 				setMaxSweeperBonusType(const SweeperBonusType_t sweeperBonusType)	{ m_SweeperTypeMin = sweeperBonusType; }

	Attr_t					getMinSlayerSum() const	{ return m_SlayerSumMin; }		
	void					setMinSlayerSum(const Attr_t attr)	{ m_SlayerSumMin= attr; }

	Attr_t					getMaxSlayerSum() const	{ return m_SlayerSumMax; }		
	void					setMaxSlayerSum(const Attr_t attr)	{ m_SlayerSumMax= attr; }

	Level_t					getMinVampireLevel() const	{ return m_VampireLevelMin; }
	void					setMinVampireLevel(const Level_t level)	{ m_VampireLevelMin = level; }

	Level_t					getMaxVampireLevel() const	{ return m_VampireLevelMax; }
	void					setMaxVampireLevel(const Level_t level)	{ m_VampireLevelMax = level; }

	Level_t					getMinOustersLevel() const	{ return m_OustersLevelMin; }
	void					setMinOustersLevel(const Level_t level)	{ m_OustersLevelMin = level; }

	Level_t					getMaxOustersLevel() const	{ return m_OustersLevelMax; }
	void					setMaxOustersLevel(const Level_t level)	{ m_OustersLevelMax = level; }

	const list<ZoneID_t>& 	getZoneIDList() const throw() { return m_LevelWarBonusZoneIDList; }
	void					setZoneIDList( const string& zoneIDs )	throw();

	bool 					isBonusZone(ZoneID_t targetZoneID) const throw (Error);

	bool					isCreatureThisLevel(Creature* pCreature) const throw();
	bool					isZoneThisLevel( ZoneID_t zoneID ) const throw();

	string toString() const throw();

private:

	int					m_LevelWarGrade;

	ZoneID_t			m_ZoneID;

	SweeperBonusType_t	m_SweeperTypeMin;
	SweeperBonusType_t	m_SweeperTypeMax;

	Attr_t				m_SlayerSumMin;
	Attr_t				m_SlayerSumMax;

	Level_t				m_VampireLevelMin;
	Level_t				m_VampireLevelMax;

	Level_t				m_OustersLevelMin;
	Level_t				m_OustersLevelMax;

	list<ZoneID_t>      m_LevelWarBonusZoneIDList;
};

class LevelWarZoneInfoManager
{

public:
	LevelWarZoneInfoManager();
	~LevelWarZoneInfoManager();

public:
	void init() throw(Error);
	void load() throw(Error);

	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }

	void addLevelWarZoneInfo( LevelWarZoneInfo* pLevelWarZoneInfo ) throw(Error);
	int getCreatureLevelGrade( Creature* pCreature ) throw(Error);
	ZoneID_t getCreatureZoneID( Creature* pCreature ) throw(Error);
	
	bool isCreatureBonusZone( Creature* pCreature, ZoneID_t zoneID ) const throw(Error);

	LevelWarZoneInfo* getLevelWarZoneInfo( ZoneID_t zoneID ) const throw(Error);

public:
	void clearLevelWarZoneIDs() throw(Error);
	bool getLevelWarZoneID( ZoneID_t zoneID, ZoneID_t &levelWarZoneID ) const throw(Error);
	void setLevelWarZoneID( ZoneID_t zoneID, ZoneID_t levelWarZoneID ) throw (Error);

//	void refreshSweeperBonusZonePlayer() throw(Error);
	void broadcast( ZoneID_t zoneID, Packet* pPacket ) const throw(Error);

	string toString() const throw();

private:

	hash_map<ZoneID_t, LevelWarZoneInfo*>		m_LevelWarZoneInfos;
	hash_map<ZoneID_t, ZoneID_t>				m_LevelWarZoneIDs;

	mutable Mutex 								m_Mutex;

};

extern LevelWarZoneInfoManager* g_pLevelWarZoneInfoManager;

#endif // __LEVEL_WAR_ZONE_INFO_MANAGER_H__
