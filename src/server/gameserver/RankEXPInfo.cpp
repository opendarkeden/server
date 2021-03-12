////////////////////////////////////////////////////////////////////////////////
// Filename    : RankEXPInfo.cpp
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "RankEXPInfo.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

////////////////////////////////////////////////////////////////////////////////
// Global Variable initialization
////////////////////////////////////////////////////////////////////////////////
RankEXPInfoManager * g_pRankEXPInfoManager[RANK_TYPE_MAX] = { NULL, };


////////////////////////////////////////////////////////////////////////////////
// class RankEXPInfo member methods
////////////////////////////////////////////////////////////////////////////////

RankEXPInfo::RankEXPInfo()
	
{
	__BEGIN_TRY
	__END_CATCH
}

RankEXPInfo::~RankEXPInfo()
	
{
	__BEGIN_TRY
	__END_CATCH
}

string RankEXPInfo::toString() const
	
{
	__BEGIN_TRY
	
	StringStream msg;

	msg << "RankEXPInfo ("
		<< " Level : "   << (int)m_Level
		<< " GoalExp : "   << (int)m_GoalExp
		<< " AccumExp : " << (int)m_AccumExp 
		<< ")";
	
	return msg.toString();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class RankEXPInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

RankEXPInfoManager::RankEXPInfoManager()
	
{
	__BEGIN_TRY

	m_RankEXPCount    = 0;
	m_RankEXPInfoList = NULL;

	__END_CATCH
}

RankEXPInfoManager::~RankEXPInfoManager()
	
{
	__BEGIN_TRY

	if (m_RankEXPInfoList != NULL)
	{
		for (uint i=0; i<m_RankEXPCount; i++)
			SAFE_DELETE(m_RankEXPInfoList[i]);

		SAFE_DELETE_ARRAY(m_RankEXPInfoList);
	}
	
	__END_CATCH
}

void RankEXPInfoManager::init(RankType rankType)
	
{
	__BEGIN_TRY

	load(rankType);

	__END_CATCH
}

void RankEXPInfoManager::load(RankType rankType)
	
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;	// by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Level) FROM RankEXPInfo WHERE RankType=%d", (int)rankType);

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in RankEXPInfo Table");
		}

		// 전체 갯수를 세팅한다.
		pResult->next();
		m_RankEXPCount = pResult->getInt(1) +1;

		Assert(m_RankEXPCount > 0);

		m_RankEXPInfoList = new RankEXPInfo * [m_RankEXPCount];
		Assert(m_RankEXPInfoList != NULL);

		// 배열을 초기화
		for (uint i = 0 ; i < m_RankEXPCount ; i ++)
			m_RankEXPInfoList[i] = NULL;
		
		// 데이터를 집어넣는다.
		pResult = pStmt->executeQuery("Select Level, GoalExp, AccumExp from RankEXPInfo WHERE RankType=%d", (int)rankType);
		while (pResult->next()) 
		{
			RankEXPInfo * pRankEXPInfo = new RankEXPInfo ();
			Assert(pRankEXPInfo != NULL);

			int i = 0;

			pRankEXPInfo->setLevel (pResult->getInt(++i));
			pRankEXPInfo->setGoalExp (pResult->getInt(++i));
			pRankEXPInfo->setAccumExp (pResult->getInt(++i));

			addRankEXPInfo(pRankEXPInfo);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void RankEXPInfoManager::addRankEXPInfo(RankEXPInfo * pRankEXPInfo)
	
{
	__BEGIN_TRY

  	Assert(pRankEXPInfo != NULL);
	Assert(m_RankEXPInfoList[pRankEXPInfo->getLevel()] == NULL);

	m_RankEXPInfoList[pRankEXPInfo->getLevel()] = pRankEXPInfo;
	
	__END_CATCH
}

RankEXPInfo * RankEXPInfoManager::getRankEXPInfo(uint value) const 
	
{
	__BEGIN_TRY

	if (value >= m_RankEXPCount || m_RankEXPInfoList[value] == NULL)
	{
		filelog("RankEXPError.log", "RankEXP 능력치 초과 또는 미만");
		throw InvalidProtocolException();
	}

	return m_RankEXPInfoList[value];
	
	__END_CATCH
}

string RankEXPInfoManager::toString() const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "RankEXPInfoManager(";

	for (uint i = 0 ; i < m_RankEXPCount ; i ++) 
	{
		if (m_RankEXPInfoList[i] != NULL)
		{
			msg << m_RankEXPInfoList[i]->toString();
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

