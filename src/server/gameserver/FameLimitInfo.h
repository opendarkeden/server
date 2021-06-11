////////////////////////////////////////////////////////////////////////////////
// Filename    : FameLimitInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __FAME_LIMIT_INFO_H__
#define __FAME_LIMIT_INFO_H__

#include "Exception.h"
#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
// Class FameLimitInfo
////////////////////////////////////////////////////////////////////////////////

class FameLimitInfo 
{
public:
	FameLimitInfo() ;
	~FameLimitInfo() ;

public:
	void setDomainType( SkillDomainType_t domainType ) { m_DomainType = domainType; }
	SkillDomainType_t getDomainType() const { return m_DomainType; }

	void setLevel( uint level ) { m_Level = level; }
	uint getLevel() const { return m_Level; }

	void setFame( Fame_t fame ) { m_Fame = fame; }
	Fame_t getFame() const { return m_Fame; }

	string toString() const ;

private:
	SkillDomainType_t m_DomainType;
	uint m_Level;
	Fame_t m_Fame;
};


////////////////////////////////////////////////////////////////////////////////
// Class FameLimitInfoManager
////////////////////////////////////////////////////////////////////////////////

class FameLimitInfoManager 
{
public:
	FameLimitInfoManager() ;
	~FameLimitInfoManager() ;

public:
	void init() ;
	void load() ;
	void clear() ;

	FameLimitInfo* getFameLimitInfo(SkillDomainType_t domainType, uint level) const ;
	void addFameLimitInfo(FameLimitInfo* pFameLimitInfo) ;

	string toString() const ;

private:
	FameLimitInfo** m_FameLimitInfoList[SKILL_DOMAIN_MAX];
};

// global variable definition
extern FameLimitInfoManager* g_pFameLimitInfoManager;

#endif	
