////////////////////////////////////////////////////////////////////////////////
// Filename    : VampEXPInfo.cpp
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "VampEXPInfo.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

////////////////////////////////////////////////////////////////////////////////
// Global Variable definition
////////////////////////////////////////////////////////////////////////////////
VampEXPInfoManager* g_pVampEXPInfoManager = NULL;


////////////////////////////////////////////////////////////////////////////////
// class VampEXPInfo member methods
////////////////////////////////////////////////////////////////////////////////

VampEXPInfo::VampEXPInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

VampEXPInfo::~VampEXPInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string VampEXPInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "VampEXPInfo ("
			<< " Level : "   << (int)m_Level
			<< " GoalExp : "   << (int)m_GoalExp
			<< " AccumExp : " << (int)m_AccumExp
			<< ")";
	return msg.toString();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// class VampEXPInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

VampEXPInfoManager::VampEXPInfoManager()
	throw()
{
	__BEGIN_TRY

	m_VampEXPCount    = 0;
	m_VampEXPInfoList = NULL;

	__END_CATCH
}

VampEXPInfoManager::~VampEXPInfoManager()
	throw()
{
	__BEGIN_TRY

	if (m_VampEXPInfoList != NULL)
	{
		for (uint i=0; i<m_VampEXPCount; i++)
			SAFE_DELETE(m_VampEXPInfoList[i]);

		SAFE_DELETE_ARRAY(m_VampEXPInfoList);
	}
	
	__END_CATCH
}

void VampEXPInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void VampEXPInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt   = NULL; // by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Level) FROM VampEXPBalanceInfo");

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in VampEXPInfo Table");
		}

		// 전체 갯수를 세팅한다.
		pResult->next();
		m_VampEXPCount = pResult->getInt(1) +1;

		Assert (m_VampEXPCount > 0);

		m_VampEXPInfoList = new VampEXPInfo* [m_VampEXPCount]; 

		Assert(m_VampEXPInfoList != NULL);

		// 배열을 초기화
		for (uint i = 0 ; i < m_VampEXPCount ; i ++)
			m_VampEXPInfoList[i] = NULL;
		
		pResult = pStmt->executeQuery("Select Level, GoalExp, AccumExp from VampEXPBalanceInfo");

		while (pResult->next()) 
		{
			VampEXPInfo* pVampEXPInfo = new VampEXPInfo ();
			int          i            = 0;

			pVampEXPInfo->setLevel (pResult->getInt(++i));
			pVampEXPInfo->setGoalExp (pResult->getInt(++i));
			pVampEXPInfo->setAccumExp (pResult->getInt(++i));

			addVampEXPInfo(pVampEXPInfo);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void VampEXPInfoManager::addVampEXPInfo(VampEXPInfo* pVampEXPInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert(pVampEXPInfo != NULL);
	Assert(m_VampEXPInfoList[pVampEXPInfo->getLevel()] == NULL);

	m_VampEXPInfoList[pVampEXPInfo->getLevel()] = pVampEXPInfo;
	
	__END_CATCH
}

VampEXPInfo* VampEXPInfoManager::getVampEXPInfo(uint  VampEXPType)
	const throw(NoSuchElementException , OutOfBoundException, Error)
{
	__BEGIN_TRY

	Assert(VampEXPType < m_VampEXPCount);
	Assert(m_VampEXPInfoList[VampEXPType] != NULL);

	return m_VampEXPInfoList[VampEXPType];
	
	__END_CATCH
}

string VampEXPInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "VampEXPInfoManager(";

	for (uint i = 0 ; i < m_VampEXPCount ; i ++) 
	{
		if (m_VampEXPInfoList[i] != NULL)
		{
			msg << m_VampEXPInfoList[i]->toString();
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

