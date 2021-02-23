////////////////////////////////////////////////////////////////////////////////
// Filename    : FameLimitInfo.cpp
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "FameLimitInfo.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

////////////////////////////////////////////////////////////////////////////////
// class FameLimitInfo member methods
////////////////////////////////////////////////////////////////////////////////

FameLimitInfo::FameLimitInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

FameLimitInfo::~FameLimitInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string FameLimitInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;

	msg << "FameLimitInfo ("
		<< " Level : "   << (int)m_Level
		<< " Fame : "   << (int)m_Fame
		<< ")";
	
	return msg.toString();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class FameLimitInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

FameLimitInfoManager::FameLimitInfoManager()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}

FameLimitInfoManager::~FameLimitInfoManager()
	throw()
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void FameLimitInfoManager::clear()
	throw ( Error )
{
	__BEGIN_TRY
	
	if ( m_FameLimitInfoList != NULL )
	{
		for ( int i = 0; i < SKILL_DOMAIN_MAX; i++ )
		{
			for ( int j = 0; j <= 150; j++ )
				SAFE_DELETE( m_FameLimitInfoList[i][j] );
			SAFE_DELETE_ARRAY( m_FameLimitInfoList[i] );
		}
	}

	__END_CATCH
}

void FameLimitInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void FameLimitInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;	// by sigi
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		for ( int i = 0; i < SKILL_DOMAIN_MAX; i++ )
		{
			pResult = pStmt->executeQuery("SELECT MAX(Level) FROM FameLimitInfo WHERE DomainType=%d", i);

			if ( pResult->getRowCount() == 0 )
			{
				SAFE_DELETE(pStmt);
				throw Error ("There is no data in FameLimitInfo Table");
			}

			// 전체 갯수를 세팅한다.
			pResult->next();

			int count = pResult->getInt(1) + 1;

			Assert( count > 0 );
			Assert( count <= 151 );

			m_FameLimitInfoList[i] = new FameLimitInfo * [count];

			for ( int j = 0; j < count; j++ )
				m_FameLimitInfoList[i][j] = NULL;

			pResult = pStmt->executeQuery( "SELECT DomainType, Level, Fame FROM FameLimitInfo WHERE DomainType = %d", i );
			while (pResult->next()) 
			{
				FameLimitInfo * pFameLimitInfo = new FameLimitInfo ();
				int i = 0;

				pFameLimitInfo->setDomainType( pResult->getInt(++i));
				pFameLimitInfo->setLevel(pResult->getInt(++i));
				pFameLimitInfo->setFame(pResult->getInt(++i));

				addFameLimitInfo(pFameLimitInfo);
			}

		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void FameLimitInfoManager::addFameLimitInfo(FameLimitInfo * pFameLimitInfo)
	throw()
{
	__BEGIN_TRY

  	Assert( pFameLimitInfo != NULL );

	SkillDomainType_t DomainType = pFameLimitInfo->getDomainType();
	uint Level = pFameLimitInfo->getLevel();

	Assert( DomainType < SKILL_DOMAIN_MAX );
	Assert( Level < 151 );
	Assert( m_FameLimitInfoList[DomainType][Level] == NULL);

	m_FameLimitInfoList[DomainType][Level] = pFameLimitInfo;
	
	__END_CATCH
}

FameLimitInfo * FameLimitInfoManager::getFameLimitInfo( SkillDomainType_t DomainType, uint Level ) const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(DomainType < SKILL_DOMAIN_MAX);
	Assert(Level < 151);
	Assert(m_FameLimitInfoList[DomainType] != NULL);
	Assert(m_FameLimitInfoList[DomainType][Level] != NULL);

	return m_FameLimitInfoList[DomainType][Level];

	__END_CATCH
}

string FameLimitInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "FameLimitInfoManager(";

	for ( int i = 0; i < SKILL_DOMAIN_MAX; i ++) 
	{
		for ( int j = 0; j <= 150; j++ )
		{
			if ( m_FameLimitInfoList[i][j] == NULL )
			{
				msg << "NULL" ;
			}
			else
			{
				msg << "FameLimitInfo[" << i << "][" << j << "]("
					<< m_FameLimitInfoList[i][j]->toString();
			}
		}
	}
	
	msg << ")";

	return msg.toString();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// Global Variable initialization
////////////////////////////////////////////////////////////////////////////////
FameLimitInfoManager* g_pFameLimitInfoManager = NULL;
