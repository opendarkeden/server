////////////////////////////////////////////////////////////////////////////////
// Filename    : VampEXPInfo.h
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VAMP_EXP_INFO_H__
#define __VAMP_EXP_INFO_H__

#include "Exception.h"
#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
// Class VampEXPInfo
////////////////////////////////////////////////////////////////////////////////

class VampEXPInfo 
{
public:
	VampEXPInfo() ;
	~VampEXPInfo() ;

public:
	void setLevel(uint lev)  { m_Level = lev; }
	uint getLevel() const  { return m_Level; }

	void setGoalExp(Exp_t sum)  { m_GoalExp = sum; }
	uint getGoalExp() const  { return m_GoalExp; }

	void setAccumExp(Exp_t accum)  { m_AccumExp = accum ; }
	uint getAccumExp() const  { return m_AccumExp; }

	string toString() const ;

private:
	Level_t m_Level;		// 레벨
	Exp_t m_GoalExp;   	// 목표 경험치
	Exp_t m_AccumExp;		// 누적 경험치
};


////////////////////////////////////////////////////////////////////////////////
// Class VampEXPInfoManager
////////////////////////////////////////////////////////////////////////////////

class VampEXPInfoManager 
{
public:
	VampEXPInfoManager() ;
	~VampEXPInfoManager() ;

public:
	void init() ;
	void load() ;

	VampEXPInfo* getVampEXPInfo(uint VampEXPType) const ;
	void addVampEXPInfo(VampEXPInfo* pVampEXPInfo) ;

	string toString() const ;

private:
	uint          m_VampEXPCount;
	VampEXPInfo** m_VampEXPInfoList;
		
};

// Global Variable Definition
extern VampEXPInfoManager* g_pVampEXPInfoManager;

#endif	

