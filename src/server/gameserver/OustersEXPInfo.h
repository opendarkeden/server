////////////////////////////////////////////////////////////////////////////////
// Filename    : OustersEXPInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_EXP_INFO_H__
#define __OUSTERS_EXP_INFO_H__

#include "Exception.h"
#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
// Class OustersEXPInfo
////////////////////////////////////////////////////////////////////////////////

class OustersEXPInfo 
{
public:
	OustersEXPInfo() throw();
	~OustersEXPInfo() throw();

public:
	void setLevel(uint lev) throw() { m_Level = lev; }
	uint getLevel() const throw() { return m_Level; }

	void setGoalExp(Exp_t sum) throw() { m_GoalExp = sum; }
	uint getGoalExp() const throw() { return m_GoalExp; }

	void setAccumExp(Exp_t accum) throw() { m_AccumExp = accum ; }
	uint getAccumExp() const throw() { return m_AccumExp; }

	void setSkillPointBonus(SkillBonus_t SkillBonus) throw() { m_SkillPointBonus = SkillBonus; }
	SkillBonus_t getSkillPointBonus() const throw() { return m_SkillPointBonus; }

	string toString() const throw();

private:
	Level_t m_Level;		// 레벨
	Exp_t m_GoalExp;   		// 목표 경험치
	Exp_t m_AccumExp;		// 누적 경험치
	SkillBonus_t m_SkillPointBonus;		// 레벨업시 스킬 보너스 포인트
};


////////////////////////////////////////////////////////////////////////////////
// Class OustersEXPInfoManager
////////////////////////////////////////////////////////////////////////////////

class OustersEXPInfoManager 
{
public:
	OustersEXPInfoManager() throw();
	~OustersEXPInfoManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

	OustersEXPInfo* getOustersEXPInfo(uint OustersEXPType) const throw(NoSuchElementException, OutOfBoundException, Error);
	void addOustersEXPInfo(OustersEXPInfo* pOustersEXPInfo) throw(DuplicatedException, Error);

	string toString() const throw();

private:
	uint          m_OustersEXPCount;
	OustersEXPInfo** m_OustersEXPInfoList;
		
};

// Global Variable Definition
extern OustersEXPInfoManager* g_pOustersEXPInfoManager;

#endif
