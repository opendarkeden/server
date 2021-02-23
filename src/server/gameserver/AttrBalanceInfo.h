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
	STRBalanceInfo() throw();
	~STRBalanceInfo() throw();

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
// Class STRBalanceInfoManager
////////////////////////////////////////////////////////////////////////////////

class STRBalanceInfoManager 
{
public:
	STRBalanceInfoManager() throw();
	~STRBalanceInfoManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

	STRBalanceInfo* getSTRBalanceInfo(uint value) const throw (InvalidProtocolException);
	void addSTRBalanceInfo(STRBalanceInfo* pSTRBalanceInfo) throw();

	string toString() const throw();

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
	DEXBalanceInfo() throw();
	~DEXBalanceInfo() throw();

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
// Class DEXBalanceInfoManager
////////////////////////////////////////////////////////////////////////////////

class DEXBalanceInfoManager 
{
public:
	DEXBalanceInfoManager() throw();
	~DEXBalanceInfoManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

	DEXBalanceInfo* getDEXBalanceInfo(uint value) const throw (InvalidProtocolException);
	void addDEXBalanceInfo(DEXBalanceInfo* pDEXBalanceInfo) throw();

	string toString() const throw();

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
	INTBalanceInfo() throw();
	~INTBalanceInfo() throw();

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
// Class INTBalanceInfoManager
////////////////////////////////////////////////////////////////////////////////

class INTBalanceInfoManager 
{
public:
	INTBalanceInfoManager() throw();
	~INTBalanceInfoManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

	INTBalanceInfo* getINTBalanceInfo(uint value) const throw (InvalidProtocolException);
	void addINTBalanceInfo(INTBalanceInfo* pINTBalanceInfo) throw();

	string toString() const throw();

private:
	uint             m_INTBalanceCount;
	INTBalanceInfo** m_INTBalanceInfoList;
		
};

// global variable definition
extern STRBalanceInfoManager* g_pSTRBalanceInfoManager;
extern DEXBalanceInfoManager* g_pDEXBalanceInfoManager;
extern INTBalanceInfoManager* g_pINTBalanceInfoManager;

#endif	
