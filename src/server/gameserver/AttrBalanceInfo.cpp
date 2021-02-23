////////////////////////////////////////////////////////////////////////////////
// Filename    : AttrBalanceInfo.cpp
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "AttrBalanceInfo.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

////////////////////////////////////////////////////////////////////////////////
// Global Variable initialization
////////////////////////////////////////////////////////////////////////////////
STRBalanceInfoManager * g_pSTRBalanceInfoManager = NULL;
DEXBalanceInfoManager * g_pDEXBalanceInfoManager = NULL;
INTBalanceInfoManager * g_pINTBalanceInfoManager = NULL;


////////////////////////////////////////////////////////////////////////////////
// class STRBalanceInfo member methods
////////////////////////////////////////////////////////////////////////////////

STRBalanceInfo::STRBalanceInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

STRBalanceInfo::~STRBalanceInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string STRBalanceInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;

	msg << "STRBalanceInfo ("
		<< " Level : "   << (int)m_Level
		<< " GoalExp : "   << (int)m_GoalExp
		<< " AccumExp : " << (int)m_AccumExp 
		<< ")";
	
	return msg.toString();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class STRBalanceInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

STRBalanceInfoManager::STRBalanceInfoManager()
	throw()
{
	__BEGIN_TRY

	m_STRBalanceCount    = 0;
	m_STRBalanceInfoList = NULL;

	__END_CATCH
}

STRBalanceInfoManager::~STRBalanceInfoManager()
	throw()
{
	__BEGIN_TRY

	if (m_STRBalanceInfoList != NULL)
	{
		for (uint i=0; i<m_STRBalanceCount; i++)
			SAFE_DELETE(m_STRBalanceInfoList[i]);

		SAFE_DELETE_ARRAY(m_STRBalanceInfoList);
	}
	
	__END_CATCH
}

void STRBalanceInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void STRBalanceInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;	// by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Level) FROM STRBalanceInfo");

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in STRBalanceInfo Table");
		}

		// 전체 갯수를 세팅한다.
		pResult->next();
		m_STRBalanceCount = pResult->getInt(1) +1;

		Assert(m_STRBalanceCount > 0);

		m_STRBalanceInfoList = new STRBalanceInfo * [m_STRBalanceCount];
		Assert(m_STRBalanceInfoList != NULL);

		// 배열을 초기화
		for (uint i = 0 ; i < m_STRBalanceCount ; i ++)
			m_STRBalanceInfoList[i] = NULL;
		
		// 데이터를 집어넣는다.
		pResult = pStmt->executeQuery("Select Level, GoalExp, AccumExp from STRBalanceInfo ");
		while (pResult->next()) 
		{
			STRBalanceInfo * pSTRBalanceInfo = new STRBalanceInfo ();
			Assert(pSTRBalanceInfo != NULL);

			int i = 0;

			pSTRBalanceInfo->setLevel (pResult->getInt(++i));
			pSTRBalanceInfo->setGoalExp (pResult->getInt(++i));
			pSTRBalanceInfo->setAccumExp (pResult->getInt(++i));

			addSTRBalanceInfo(pSTRBalanceInfo);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void STRBalanceInfoManager::addSTRBalanceInfo(STRBalanceInfo * pSTRBalanceInfo)
	throw()
{
	__BEGIN_TRY

  	Assert(pSTRBalanceInfo != NULL);
	Assert(m_STRBalanceInfoList[pSTRBalanceInfo->getLevel()] == NULL);

	m_STRBalanceInfoList[pSTRBalanceInfo->getLevel()] = pSTRBalanceInfo;
	
	__END_CATCH
}

STRBalanceInfo * STRBalanceInfoManager::getSTRBalanceInfo(uint value) const 
	throw (InvalidProtocolException)
{
	__BEGIN_TRY

	if (value >= m_STRBalanceCount || m_STRBalanceInfoList[value] == NULL)
	{
		filelog("AttrError.log", "STR 능력치 초과 또는 미만");
		throw InvalidProtocolException();
	}

	return m_STRBalanceInfoList[value];
	
	__END_CATCH
}

string STRBalanceInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "STRBalanceInfoManager(";

	for (uint i = 0 ; i < m_STRBalanceCount ; i ++) 
	{
		if (m_STRBalanceInfoList[i] != NULL)
		{
			msg << m_STRBalanceInfoList[i]->toString();
		}
		else 
		{
			msg << "NULL" ;
		}
	}
	
	msg << ")";

	return msg.toString();

	__END_CATCH
}

















////////////////////////////////////////////////////////////////////////////////
// class DEXBalanceInfo member methods
////////////////////////////////////////////////////////////////////////////////

DEXBalanceInfo::DEXBalanceInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

DEXBalanceInfo::~DEXBalanceInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string DEXBalanceInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;

	msg << "DEXBalanceInfo ("
		<< " Level : "   << (int)m_Level
		<< " GoalExp : "   << (int)m_GoalExp
		<< " AccumExp : " << (int)m_AccumExp 
		<< ")";
	
	return msg.toString();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class DEXBalanceInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

DEXBalanceInfoManager::DEXBalanceInfoManager()
	throw()
{
	__BEGIN_TRY

	m_DEXBalanceCount    = 0;
	m_DEXBalanceInfoList = NULL;

	__END_CATCH
}

DEXBalanceInfoManager::~DEXBalanceInfoManager()
	throw()
{
	__BEGIN_TRY

	if (m_DEXBalanceInfoList != NULL)
	{
		for (uint i=0; i<m_DEXBalanceCount; i++)
			SAFE_DELETE(m_DEXBalanceInfoList[i]);

		SAFE_DELETE_ARRAY(m_DEXBalanceInfoList);
	}
	
	__END_CATCH
}

void DEXBalanceInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void DEXBalanceInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;	// by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Level) FROM DEXBalanceInfo");

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in DEXBalanceInfo Table");
		}

		// 전체 갯수를 세팅한다.
		pResult->next();
		m_DEXBalanceCount = pResult->getInt(1) +1;

		Assert(m_DEXBalanceCount > 0);

		m_DEXBalanceInfoList = new DEXBalanceInfo * [m_DEXBalanceCount];
		Assert(m_DEXBalanceInfoList != NULL);

		// 배열을 초기화
		for (uint i = 0 ; i < m_DEXBalanceCount ; i ++)
			m_DEXBalanceInfoList[i] = NULL;
		
		// 데이터를 집어넣는다.
		pResult = pStmt->executeQuery("Select Level, GoalExp, AccumExp from DEXBalanceInfo ");
		while (pResult->next()) 
		{
			DEXBalanceInfo * pDEXBalanceInfo = new DEXBalanceInfo ();
			Assert(pDEXBalanceInfo != NULL);

			int i = 0;

			pDEXBalanceInfo->setLevel (pResult->getInt(++i));
			pDEXBalanceInfo->setGoalExp (pResult->getInt(++i));
			pDEXBalanceInfo->setAccumExp (pResult->getInt(++i));

			addDEXBalanceInfo(pDEXBalanceInfo);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void DEXBalanceInfoManager::addDEXBalanceInfo(DEXBalanceInfo * pDEXBalanceInfo)
	throw()
{
	__BEGIN_TRY

  	Assert(pDEXBalanceInfo != NULL);
	Assert(m_DEXBalanceInfoList[pDEXBalanceInfo->getLevel()] == NULL);

	m_DEXBalanceInfoList[pDEXBalanceInfo->getLevel()] = pDEXBalanceInfo;
	
	__END_CATCH
}

DEXBalanceInfo * DEXBalanceInfoManager::getDEXBalanceInfo(uint value) const 
	throw (InvalidProtocolException)
{
	__BEGIN_TRY

	if (value >= m_DEXBalanceCount || m_DEXBalanceInfoList[value] == NULL)
	{
		filelog("AttrError.log", "DEX 능력치 초과 또는 미만");
		throw InvalidProtocolException();
	}

	return m_DEXBalanceInfoList[value];
	
	__END_CATCH
}

string DEXBalanceInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "DEXBalanceInfoManager(";

	for (uint i = 0 ; i < m_DEXBalanceCount ; i ++) 
	{
		if (m_DEXBalanceInfoList[i] != NULL)
		{
			msg << m_DEXBalanceInfoList[i]->toString();
		}
		else 
		{
			msg << "NULL" ;
		}
	}
	
	msg << ")";

	return msg.toString();

	__END_CATCH
}

















////////////////////////////////////////////////////////////////////////////////
// class INTBalanceInfo member methods
////////////////////////////////////////////////////////////////////////////////

INTBalanceInfo::INTBalanceInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

INTBalanceInfo::~INTBalanceInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string INTBalanceInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;

	msg << "INTBalanceInfo ("
		<< " Level : "   << (int)m_Level
		<< " GoalExp : "   << (int)m_GoalExp
		<< " AccumExp : " << (int)m_AccumExp 
		<< ")";
	
	return msg.toString();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class INTBalanceInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

INTBalanceInfoManager::INTBalanceInfoManager()
	throw()
{
	__BEGIN_TRY

	m_INTBalanceCount    = 0;
	m_INTBalanceInfoList = NULL;

	__END_CATCH
}

INTBalanceInfoManager::~INTBalanceInfoManager()
	throw()
{
	__BEGIN_TRY

	if (m_INTBalanceInfoList != NULL)
	{
		for (uint i=0; i<m_INTBalanceCount; i++)
			SAFE_DELETE(m_INTBalanceInfoList[i]);

		SAFE_DELETE_ARRAY(m_INTBalanceInfoList);
	}
	
	__END_CATCH
}

void INTBalanceInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void INTBalanceInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;	// by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Level) FROM INTBalanceInfo");

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in INTBalanceInfo Table");
		}

		// 전체 갯수를 세팅한다.
		pResult->next();
		m_INTBalanceCount = pResult->getInt(1) +1;

		Assert(m_INTBalanceCount > 0);

		m_INTBalanceInfoList = new INTBalanceInfo * [m_INTBalanceCount];
		
		Assert(m_INTBalanceInfoList != NULL);

		// 배열을 초기화
		for (uint i = 0 ; i < m_INTBalanceCount ; i ++)
			m_INTBalanceInfoList[i] = NULL;
		
		// 데이터를 집어넣는다.
		pResult = pStmt->executeQuery("Select Level, GoalExp, AccumExp from INTBalanceInfo ");
		while (pResult->next()) 
		{
			INTBalanceInfo * pINTBalanceInfo = new INTBalanceInfo ();
			Assert(pINTBalanceInfo != NULL);

			int i = 0;

			pINTBalanceInfo->setLevel (pResult->getInt(++i));
			pINTBalanceInfo->setGoalExp (pResult->getInt(++i));
			pINTBalanceInfo->setAccumExp (pResult->getInt(++i));

			addINTBalanceInfo(pINTBalanceInfo);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void INTBalanceInfoManager::addINTBalanceInfo(INTBalanceInfo * pINTBalanceInfo)
	throw()
{
	__BEGIN_TRY

  	Assert(pINTBalanceInfo != NULL);

	if (m_INTBalanceInfoList[pINTBalanceInfo->getLevel()] != NULL)
		throw DuplicatedException ();

	m_INTBalanceInfoList[pINTBalanceInfo->getLevel()] = pINTBalanceInfo;
	
	__END_CATCH
}

INTBalanceInfo * INTBalanceInfoManager::getINTBalanceInfo(uint value) const 
	throw (InvalidProtocolException)
{
	__BEGIN_TRY

	if (value >= m_INTBalanceCount || m_INTBalanceInfoList[value] == NULL)
	{
		filelog("AttrError.log", "INT 능력치 초과 또는 미만");
		throw InvalidProtocolException();
	}


	return m_INTBalanceInfoList[value];
	
	__END_CATCH
}

string INTBalanceInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "INTBalanceInfoManager(";

	for (uint i = 0 ; i < m_INTBalanceCount ; i ++) 
	{
		if (m_INTBalanceInfoList[i] != NULL)
		{
			msg << m_INTBalanceInfoList[i]->toString();
		}
		else 
		{
			msg << "NULL" ;
		}
	}
	
	msg << ")";

	return msg.toString();

	__END_CATCH
}

