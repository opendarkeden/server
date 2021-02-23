//////////////////////////////////////////////////////////////////////////////
// Filename    : SweeperBonusManager.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SWEEPER_BONUS_INFO_MANAGER_H__
#define __SWEEPER_BONUS_INFO_MANAGER_H__

#include "Exception.h"
#include "Types.h"
#include <hash_map>

class GCSweeperBonusInfo;
class SweeperBonus;

typedef hash_map<SweeperBonusType_t, SweeperBonus*>		SweeperBonusHashMap;
typedef SweeperBonusHashMap::iterator 					SweeperBonusHashMapItor;
typedef SweeperBonusHashMap::const_iterator 			SweeperBonusHashMapConstItor;

//////////////////////////////////////////////////////////////////////////////
// Class SweeperBonusManager
//////////////////////////////////////////////////////////////////////////////

class SweeperBonusManager 
{
public:
	SweeperBonusManager() throw();
	~SweeperBonusManager() throw();

public:

	// initialize Manager
	void init() throw(Error);

	// void load() throw();
	void load() throw(Error);

	void reloadOwner(int level) throw(Error);

	// clear list
	void clear() throw();

	// Save to DB
	void save() throw(Error);

	// get SweeperBonus
	SweeperBonus* getSweeperBonus(SweeperBonusType_t sweeperBonusType) const throw(NoSuchElementException, Error);
	const SweeperBonusHashMap& getSweeperBonuses() const { return m_SweeperBonuses; }

	// add SweeperBonus
	void addSweeperBonus(SweeperBonus* pSweeperBonus) throw(DuplicatedException, Error);

	bool isAble(ZoneID_t zoneID) const; 

	// toString for Debug
	string toString() const throw();

public:
	void setSweeperBonusRace( SweeperBonusType_t sweeperBonusType, Race_t race ) throw( Error );

	void makeSweeperBonusInfo( GCSweeperBonusInfo& gcSweeperBonusInfo ) throw( Error );
	void makeVoidSweeperBonusInfo( GCSweeperBonusInfo& gcSweeperBonusInfo ) throw( Error );


private:
	uint					m_Count;
	SweeperBonusHashMap		m_SweeperBonuses;
};

// Global Variable Definition
extern SweeperBonusManager* g_pSweeperBonusManager;

#endif	// __SKILL_INFO_MANAGER_H__
