////////////////////////////////////////////////////////////////////////////////
// Filename    : OustersEXPInfo.cpp
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "OustersEXPInfo.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

////////////////////////////////////////////////////////////////////////////////
// Global Variable definition
////////////////////////////////////////////////////////////////////////////////
OustersEXPInfoManager* g_pOustersEXPInfoManager = NULL;


////////////////////////////////////////////////////////////////////////////////
// class OustersEXPInfo member methods
////////////////////////////////////////////////////////////////////////////////

OustersEXPInfo::OustersEXPInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

OustersEXPInfo::~OustersEXPInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string OustersEXPInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "OustersEXPInfo ("
			<< " Level : "   << (int)m_Level
			<< " GoalExp : "   << (int)m_GoalExp
			<< " AccumExp : " << (int)m_AccumExp
			<< " SkillPointBonus : " << (int)m_SkillPointBonus
			<< ")";
	return msg.toString();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// class OustersEXPInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

OustersEXPInfoManager::OustersEXPInfoManager()
	throw()
{
	__BEGIN_TRY

	m_OustersEXPCount    = 0;
	m_OustersEXPInfoList = NULL;

	__END_CATCH
}

OustersEXPInfoManager::~OustersEXPInfoManager()
	throw()
{
	__BEGIN_TRY

	if (m_OustersEXPInfoList != NULL)
	{
		for (uint i=0; i<m_OustersEXPCount; i++)
			SAFE_DELETE(m_OustersEXPInfoList[i]);

		SAFE_DELETE_ARRAY(m_OustersEXPInfoList);
	}
	
	__END_CATCH
}

void OustersEXPInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void OustersEXPInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt   = NULL; // by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Level) FROM OustersEXPBalanceInfo");

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in OustersEXPInfo Table");
		}

		// 전체 갯수를 세팅한다.
		pResult->next();
		m_OustersEXPCount = pResult->getInt(1) +1;

		Assert (m_OustersEXPCount > 0);

		m_OustersEXPInfoList = new OustersEXPInfo* [m_OustersEXPCount]; 

		Assert(m_OustersEXPInfoList != NULL);

		// 배열을 초기화
		for (uint i = 0 ; i < m_OustersEXPCount ; i ++)
			m_OustersEXPInfoList[i] = NULL;
		
		pResult = pStmt->executeQuery("Select Level, GoalExp, AccumExp, SkillPointBonus from OustersEXPBalanceInfo");

		while (pResult->next()) 
		{
			OustersEXPInfo* pOustersEXPInfo = new OustersEXPInfo ();
			int          i            = 0;

			pOustersEXPInfo->setLevel (pResult->getInt(++i));
			pOustersEXPInfo->setGoalExp (pResult->getInt(++i));
			pOustersEXPInfo->setAccumExp (pResult->getInt(++i));
			pOustersEXPInfo->setSkillPointBonus((SkillBonus_t)pResult->getInt(++i));

			addOustersEXPInfo(pOustersEXPInfo);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void OustersEXPInfoManager::addOustersEXPInfo(OustersEXPInfo* pOustersEXPInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert(pOustersEXPInfo != NULL);
	Assert(m_OustersEXPInfoList[pOustersEXPInfo->getLevel()] == NULL);

	m_OustersEXPInfoList[pOustersEXPInfo->getLevel()] = pOustersEXPInfo;
	
	__END_CATCH
}

OustersEXPInfo* OustersEXPInfoManager::getOustersEXPInfo(uint  OustersEXPType)
	const throw(NoSuchElementException , OutOfBoundException, Error)
{
	__BEGIN_TRY

	Assert(OustersEXPType < m_OustersEXPCount);
	Assert(m_OustersEXPInfoList[OustersEXPType] != NULL);

	return m_OustersEXPInfoList[OustersEXPType];
	
	__END_CATCH
}

string OustersEXPInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "OustersEXPInfoManager(";

	for (uint i = 0 ; i < m_OustersEXPCount ; i ++) 
	{
		if (m_OustersEXPInfoList[i] != NULL)
		{
			msg << m_OustersEXPInfoList[i]->toString();
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

