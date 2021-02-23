////////////////////////////////////////////////////////////////////////////////
// Filename    : RankEXPInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __RANK_EXP_INFO_H__
#define __RANK_EXP_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "RankExpTable.h"

////////////////////////////////////////////////////////////////////////////////
// Class RankEXPInfo
////////////////////////////////////////////////////////////////////////////////

class RankEXPInfo 
{
public:
	RankEXPInfo() throw();
	~RankEXPInfo() throw();

public:
	void setLevel(uint lev) throw() { m_Level = lev; }
	uint getLevel() const throw() { return m_Level; }

	void setGoalExp(uint sum) throw() { m_GoalExp = sum; }
	uint getGoalExp() const throw() { return m_GoalExp; }

	void setAccumExp(uint accum) throw() { m_AccumExp = accum ; }
	uint getAccumExp() const throw() { return m_AccumExp; }

	string toString() const throw();

private:
	uint m_Level;
	uint m_GoalExp;
	uint m_AccumExp;
};


////////////////////////////////////////////////////////////////////////////////
// Class RankEXPInfoManager
////////////////////////////////////////////////////////////////////////////////

class RankEXPInfoManager 
{
public:
	RankEXPInfoManager() throw();
	~RankEXPInfoManager() throw();

public:
	void init(RankType rankType) throw(Error);
	void load(RankType rankType) throw(Error);

	RankEXPInfo* getRankEXPInfo(uint value) const throw (InvalidProtocolException);
	void addRankEXPInfo(RankEXPInfo* pRankEXPInfo) throw();

	string toString() const throw();

private:
	uint             m_RankEXPCount;
	RankEXPInfo** m_RankEXPInfoList;
};

// global variable definition
extern RankEXPInfoManager* g_pRankEXPInfoManager[RANK_TYPE_MAX];

#endif	
