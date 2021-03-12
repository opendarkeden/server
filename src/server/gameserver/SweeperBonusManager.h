//////////////////////////////////////////////////////////////////////////////
// Filename    : SweeperBonusManager.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SWEEPER_BONUS_INFO_MANAGER_H__
#define __SWEEPER_BONUS_INFO_MANAGER_H__

#include "Exception.h"
#include "Types.h"
#include <unordered_map>

class GCSweeperBonusInfo;
class SweeperBonus;

typedef unordered_map<SweeperBonusType_t, SweeperBonus*>		SweeperBonusHashMap;
typedef SweeperBonusHashMap::iterator 					SweeperBonusHashMapItor;
typedef SweeperBonusHashMap::const_iterator 			SweeperBonusHashMapConstItor;

//////////////////////////////////////////////////////////////////////////////
// Class SweeperBonusManager
//////////////////////////////////////////////////////////////////////////////

class SweeperBonusManager 
{
public:
	SweeperBonusManager() ;
	~SweeperBonusManager() ;

public:

	// initialize Manager
	void init() ;

	// void load() ;
	void load() ;

	void reloadOwner(int level) ;

	// clear list
	void clear() ;

	// Save to DB
	void save() ;

	// get SweeperBonus
	SweeperBonus* getSweeperBonus(SweeperBonusType_t sweeperBonusType) const ;
	const SweeperBonusHashMap& getSweeperBonuses() const { return m_SweeperBonuses; }

	// add SweeperBonus
	void addSweeperBonus(SweeperBonus* pSweeperBonus) ;

	bool isAble(ZoneID_t zoneID) const; 

	// toString for Debug
	string toString() const ;

public:
	void setSweeperBonusRace( SweeperBonusType_t sweeperBonusType, Race_t race ) ;

	void makeSweeperBonusInfo( GCSweeperBonusInfo& gcSweeperBonusInfo ) ;
	void makeVoidSweeperBonusInfo( GCSweeperBonusInfo& gcSweeperBonusInfo ) ;


private:
	uint					m_Count;
	SweeperBonusHashMap		m_SweeperBonuses;
};

// Global Variable Definition
extern SweeperBonusManager* g_pSweeperBonusManager;

#endif	// __SKILL_INFO_MANAGER_H__
