//--------------------------------------------------------------------
//
// Filename    : SkillDomainInfoManager.cpp
// Written By  : Elca
//
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// include files
//--------------------------------------------------------------------
#include "Exception.h"
#include "SkillDomainInfoManager.h"
#include "StringStream.h"
#include "Assert.h"
#include "DB.h"

DomainInfo::DomainInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

DomainInfo::~DomainInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string DomainInfo::toString () const
	throw ()
{
	__BEGIN_TRY
	StringStream msg;
	
	msg << "DomainInfo("
		<< "DomainType : " << (int)m_Type
		<< "Level : " << (int)m_Level
		<< "GoalExp: " << (int)m_GoalExp
		<< "AccumExp: " << (int)m_AccumExp
		<< "BestItemType: " << (int)m_BestItemType
		<< ")";

	return msg.toString();

	__END_CATCH
}

//--------------------------------------------------------------------
//
// Constructor
//
//--------------------------------------------------------------------
SkillDomainInfoManager::SkillDomainInfoManager()
	throw()
{
	__BEGIN_TRY

	/*
	for (int i = 0 ; i < SKILL_DOMAIN_MAX; i ++) {
		for(int j = 0; j <= 100; i++) {
			m_DomainInfoLists[i][j] = NULL;
		}
	}
	*/

	__END_CATCH
}

//--------------------------------------------------------------------
//
// Destructor
//
//--------------------------------------------------------------------
SkillDomainInfoManager::~SkillDomainInfoManager()
	throw()
{
	__BEGIN_TRY

	for (int i = 0 ; i < SKILL_DOMAIN_MAX ; i ++) 
		for(int j = 0; j <= 150; j++) 
			SAFE_DELETE(m_DomainInfoLists[i][j]);

	__END_CATCH
}

//--------------------------------------------------------------------
//
// SkillDomainInfoManager::init()
//
//--------------------------------------------------------------------
void SkillDomainInfoManager::init ()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		for(int i = 0; i < SKILL_DOMAIN_MAX; i++) 
		{
			pResult = pStmt->executeQuery("SELECT MAX(Level) FROM SkillDomainInfo WHERE DomainType = %d", i);

			if (!pResult->next())
			{
				SAFE_DELETE(pStmt);
				cerr << "There is no data in DomainInfo Table" << endl;
				throw Error ("There is no data in DomainInfo Table");
			}

//			pResult->next();

			int Count = pResult->getInt(1) +1;

			Assert (Count > 0);
			Assert (Count <= 151);

			m_DomainInfoLists[i] = new DomainInfo* [Count];

			for (int j=0 ; j < Count; j++) m_DomainInfoLists[i][j] = NULL;

			pResult = pStmt->executeQuery("Select DomainType, Level, GoalExp, AccumExp, BestItemType from SkillDomainInfo WHERE DomainType = %d", i);

			while (pResult->next()) 
			{
				DomainInfo* pDomainInfo = new DomainInfo ();
				int        i          = 0;

				pDomainInfo->setType(pResult->getInt(++i));
				pDomainInfo->setLevel(pResult->getInt(++i));
				pDomainInfo->setGoalExp(pResult->getInt(++i));
				pDomainInfo->setAccumExp(pResult->getInt(++i));
				pDomainInfo->setBestItemType(pResult->getInt(++i));
				addDomainInfo(pDomainInfo);
			}
			
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get item info
//--------------------------------------------------------------------------------
DomainInfo* SkillDomainInfoManager::getDomainInfo (SkillDomain DomainType, Level_t Level)
	const throw (Error)
{
	__BEGIN_TRY

	Assert(DomainType < SKILL_DOMAIN_MAX);
	Assert(Level < 151);
	Assert(m_DomainInfoLists[DomainType] != NULL);
	Assert(m_DomainInfoLists[DomainType][Level] != NULL);

	return m_DomainInfoLists[DomainType][Level];

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get item info
//--------------------------------------------------------------------------------
void SkillDomainInfoManager::addDomainInfo(DomainInfo* pDomainInfo) const 
	throw (Error)
{
	__BEGIN_TRY

	SkillDomainType_t DomainType = pDomainInfo->getType();
	Level_t Level = pDomainInfo->getLevel();

	Assert(DomainType < SKILL_DOMAIN_MAX);
	Assert(Level < 151);
	Assert(m_DomainInfoLists[DomainType][Level] == NULL);

	m_DomainInfoLists[DomainType][Level] = pDomainInfo;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string SkillDomainInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY
	StringStream msg;
	
	msg << "SkillDomainInfoManager(";

	for (uint i = 0; i < SKILL_DOMAIN_MAX ; i ++)
	{
		for(int j = 0; j <= 150; j++) {

			if (m_DomainInfoLists[i][j] == NULL) {
				msg << "NULL";
			} else {
				msg << "DomainInfo[" << (int)i << "][" << (int)j << "](" << m_DomainInfoLists[i][j]->toString();
			}
			msg << "\n";
		}
	}

	msg << ")";

	return msg.toString();
	__END_CATCH
}

// global variable declaration
SkillDomainInfoManager* g_pSkillDomainInfoManager = NULL;
