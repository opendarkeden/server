//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBibleBonusManager.h
// Written By  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BLOOD_BIBLE_BONUS_INFO_MANAGER_H__
#define __BLOOD_BIBLE_BONUS_INFO_MANAGER_H__

#include "Exception.h"
#include "Exception.h"
#include "Types.h"
#include <unordered_map>

class GCHolyLandBonusInfo;
class BloodBibleBonus;

typedef unordered_map<BloodBibleBonusType_t, BloodBibleBonus*>	BloodBibleBonusHashMap;
typedef BloodBibleBonusHashMap::iterator 					BloodBibleBonusHashMapItor;
typedef BloodBibleBonusHashMap::const_iterator 				BloodBibleBonusHashMapConstItor;

//////////////////////////////////////////////////////////////////////////////
// Class BloodBibleBonusManager
//////////////////////////////////////////////////////////////////////////////

class BloodBibleBonusManager 
{
public:
	BloodBibleBonusManager() ;
	~BloodBibleBonusManager() ;

public:

	// initialize Manager
	void init() ;

	// void load() ;
	void load() ;
	
	// clear list
	void clear() ;

	// Save to DB
	void save() ;

	// get BloodBibleBonus
	BloodBibleBonus* getBloodBibleBonus(BloodBibleBonusType_t bloodBibleBonusType) const ;
	const BloodBibleBonusHashMap& getBloodBibleBonuses() const { return m_BloodBibleBonuses; }

	// add BloodBibleBonus
	void addBloodBibleBonus(BloodBibleBonus* pBloodBibleBonus) ;

	// toString for Debug
	string toString() const ;

public:
	void setBloodBibleBonusRace( BloodBibleBonusType_t bloodBibleBonusType, Race_t race ) ;

	void makeHolyLandBonusInfo( GCHolyLandBonusInfo& gcHolyLandBonusInfo ) ;

	template <typename ITR> void getBloodBibleByRace(Race_t race, ITR oItr) const
	{
		BloodBibleBonusHashMapConstItor itr = m_BloodBibleBonuses.begin();

		for ( ; itr != m_BloodBibleBonuses.end() ; ++itr )
		{
			if ( itr->second->getRace() == race )
			{
				(*oItr) = itr->first;
				++oItr;
			}
		}
	}


private:
	uint					m_Count;
	BloodBibleBonusHashMap	m_BloodBibleBonuses;

};

// Global Variable Definition
extern BloodBibleBonusManager* g_pBloodBibleBonusManager;

#endif	// __SKILL_INFO_MANAGER_H__
