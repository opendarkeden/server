////////////////////////////////////////////////////////////////////////////////
// Filename    : AttrBalanceInfo.h
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTRBALANCEINFO_H__
#define __ATTRBALANCEINFO_H__

#include "Exception.h"
#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
// Class STRBalanceInfo
////////////////////////////////////////////////////////////////////////////////

class STRBalanceInfo 
{
public:
	STRBalanceInfo() ;
	~STRBalanceInfo() ;

public:
	void setLevel(uint lev)  { m_Level = lev; }
	uint getLevel() const  { return m_Level; }

	void setGoalExp(uint sum)  { m_GoalExp = sum; }
	uint getGoalExp() const  { return m_GoalExp; }

	void setAccumExp(uint accum)  { m_AccumExp = accum ; }
	uint getAccumExp() const  { return m_AccumExp; }

	string toString() const ;

private:
	uint m_Level;
	uint m_GoalExp;
	uint m_AccumExp;
};


////////////////////////////////////////////////////////////////////////////////
// Class STRBalanceInfoManager
////////////////////////////////////////////////////////////////////////////////

class STRBalanceInfoManager 
{
public:
	STRBalanceInfoManager() ;
	~STRBalanceInfoManager() ;

public:
	void init() ;
	void load() ;

	STRBalanceInfo* getSTRBalanceInfo(uint value) const ;
	void addSTRBalanceInfo(STRBalanceInfo* pSTRBalanceInfo) ;

	string toString() const ;

private:
	uint             m_STRBalanceCount;
	STRBalanceInfo** m_STRBalanceInfoList;
};


////////////////////////////////////////////////////////////////////////////////
// Class DEXBalanceInfo
////////////////////////////////////////////////////////////////////////////////

class DEXBalanceInfo 
{
public:
	DEXBalanceInfo() ;
	~DEXBalanceInfo() ;

public:
	void setLevel(uint lev)  { m_Level = lev; }
	uint getLevel() const  { return m_Level; }

	void setGoalExp(uint sum)  { m_GoalExp = sum; }
	uint getGoalExp() const  { return m_GoalExp; }

	void setAccumExp(uint accum)  { m_AccumExp = accum ; }
	uint getAccumExp() const  { return m_AccumExp; }

	string toString() const ;

private:
	uint m_Level;
	uint m_GoalExp;
	uint m_AccumExp;
};


////////////////////////////////////////////////////////////////////////////////
// Class DEXBalanceInfoManager
////////////////////////////////////////////////////////////////////////////////

class DEXBalanceInfoManager 
{
public:
	DEXBalanceInfoManager() ;
	~DEXBalanceInfoManager() ;

public:
	void init() ;
	void load() ;

	DEXBalanceInfo* getDEXBalanceInfo(uint value) const ;
	void addDEXBalanceInfo(DEXBalanceInfo* pDEXBalanceInfo) ;

	string toString() const ;

private:
	uint             m_DEXBalanceCount;
	DEXBalanceInfo** m_DEXBalanceInfoList;
		
};


////////////////////////////////////////////////////////////////////////////////
// Class INTBalanceInfo
////////////////////////////////////////////////////////////////////////////////

class INTBalanceInfo 
{
public:
	INTBalanceInfo() ;
	~INTBalanceInfo() ;

public:
	void setLevel(uint lev)  { m_Level = lev; }
	uint getLevel() const  { return m_Level; }

	void setGoalExp(uint sum)  { m_GoalExp = sum; }
	uint getGoalExp() const  { return m_GoalExp; }

	void setAccumExp(uint accum)  { m_AccumExp = accum ; }
	uint getAccumExp() const  { return m_AccumExp; }

	string toString() const ;

private:
	uint m_Level;
	uint m_GoalExp;
	uint m_AccumExp;
};


////////////////////////////////////////////////////////////////////////////////
// Class INTBalanceInfoManager
////////////////////////////////////////////////////////////////////////////////

class INTBalanceInfoManager 
{
public:
	INTBalanceInfoManager() ;
	~INTBalanceInfoManager() ;

public:
	void init() ;
	void load() ;

	INTBalanceInfo* getINTBalanceInfo(uint value) const ;
	void addINTBalanceInfo(INTBalanceInfo* pINTBalanceInfo) ;

	string toString() const ;

private:
	uint             m_INTBalanceCount;
	INTBalanceInfo** m_INTBalanceInfoList;
		
};

// global variable definition
extern STRBalanceInfoManager* g_pSTRBalanceInfoManager;
extern DEXBalanceInfoManager* g_pDEXBalanceInfoManager;
extern INTBalanceInfoManager* g_pINTBalanceInfoManager;

#endif	
