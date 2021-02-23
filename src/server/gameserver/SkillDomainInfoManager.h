//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillDomainInfoManager.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOMAIN_INFO_MANAGER_H__
#define __SKILL_DOMAIN_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class DomainInfo
//////////////////////////////////////////////////////////////////////////////

class DomainInfo 
{
public:
	DomainInfo() throw();
	~DomainInfo() throw();

public:
	SkillDomainType_t getType() const throw() { return m_Type; }
	void setType(SkillDomainType_t type) throw() { m_Type = type; }

	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t level) throw() { m_Level = level; }

	uint getGoalExp() const throw() { return m_GoalExp; }
	void setGoalExp(Exp_t exp) throw() { m_GoalExp = exp ; }

	uint getAccumExp() const throw() { return m_AccumExp; }
	void setAccumExp(Exp_t exp) throw() { m_AccumExp = exp ; }

	ItemType_t getBestItemType() const throw() { return m_BestItemType; }
	void setBestItemType(ItemType_t it) throw() { m_BestItemType = it; }
	
	string toString() const throw();

private:

	// 스킬 도메인의 타입
	SkillDomainType_t m_Type;

	// 단계(스킬 트리에서 이 기술의 depth)
	Level_t m_Level;

	// 목표 경험치
	Exp_t m_GoalExp;

	// 누적 경험치
	Exp_t m_AccumExp;

	// 적절한 무기 단계
	ItemType_t m_BestItemType;
};

//--------------------------------------------------------------------
//
// Class DomainInfoManager
//
//--------------------------------------------------------------------
/*
class DomainInfoManager {

public:

	// constructor
	DomainInfoManager() throw();

	// destructor
	~DomainInfoManager() throw();

	// initialize manager
	void init() throw(Error);

	// get sub info class manager
	DomainInfoManager* getInfoManager(Domain DomainType) const throw(Error);

	// get item info
	SkillDomainInfo* getSkillDomainInfo(Level_t Level) const throw(Error);

	uint getDomainCount() const throw(Error);

	// toString for debug
	string toString() const throw();

private:

	DomainInfo ** m_DomainInfoLists;

};
*/

//////////////////////////////////////////////////////////////////////////////
// Class SkillDomainInfoManager
//////////////////////////////////////////////////////////////////////////////

class SkillDomainInfoManager 
{
public:
	SkillDomainInfoManager() throw();
	~SkillDomainInfoManager() throw();

public:
	// initialize manager
	void init() throw(Error);

	// get item info
	DomainInfo* getDomainInfo(SkillDomain DomainType, Level_t Level) const throw(Error);

	// addDomainInfo
	void addDomainInfo(DomainInfo* pDomainInfo) const throw(Error);

	// toString for debug
	string toString() const throw();

private:
	DomainInfo ** m_DomainInfoLists[SKILL_DOMAIN_MAX];
};

extern SkillDomainInfoManager* g_pSkillDomainInfoManager;

#endif
