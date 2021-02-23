//////////////////////////////////////////////////////////////////////////////
// Filename    : RankBonusInfo.h
// Written By  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __RANK_BONUS_INFO_H__
#define __RANK_BONUS_INFO_H__

#include "Exception.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// Class RankBonusInfo
//////////////////////////////////////////////////////////////////////////////

class RankBonusInfo 
{
public:
	RankBonusInfo();
	~RankBonusInfo();

public:
	DWORD getType() const { return m_Type; }
	void setType(DWORD type) { m_Type = type; }

	string getName() const { return m_Name ; }
	void setName(string name) { m_Name = name ; }

	Rank_t getRank() const { return m_Rank; }
	void setRank(Rank_t rank) { m_Rank = rank; }

	DWORD getPoint() const { return m_Point; }
	void setPoint( DWORD point ) { m_Point = point; }

	int getRace() const { return m_Race; }
	void setRace( int race ) { m_Race = race; }

	// toString
	string toString() const ;

private:
	DWORD	m_Type;			// Type
	string	m_Name;			// Name
	Rank_t	m_Rank;			// Rank
	DWORD	m_Point;		// Point
	int		m_Race;			// Race
	
};

//////////////////////////////////////////////////////////////////////////////
// Class RankBonusInfoManager
//////////////////////////////////////////////////////////////////////////////

class RankBonusInfoManager 
{
public:
	RankBonusInfoManager() throw();
	~RankBonusInfoManager() throw();

public:

	// initialize Manager
	void init() throw(Error);

	// void load() throw();
	void load() throw(Error);
	
	// clear list
	void clear() throw();

	// Save to DB
	void save() throw(Error);

	// get RankBonusInfo
	RankBonusInfo* getRankBonusInfo(DWORD rankBonusType) const throw(NoSuchElementException, OutOfBoundException, Error);

	// add RankBonusInfo
	void addRankBonusInfo(RankBonusInfo* pRankBonusInfo) throw(DuplicatedException, Error);

	// toString for Debug
	string toString() const throw();

private:
	uint				m_Count;
	RankBonusInfo**		m_RankBonusInfoList;

};

// Global Variable Definition
extern RankBonusInfoManager* g_pRankBonusInfoManager;

#endif	// __SKILL_INFO_MANAGER_H__
