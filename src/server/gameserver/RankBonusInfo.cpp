//////////////////////////////////////////////////////////////////////////////
// Filename    : RankBonusInfo.cpp
// Written By  : beowulf
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RankBonusInfo.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

//////////////////////////////////////////////////////////////////////////////
// class RankBonusInfo member methods
//////////////////////////////////////////////////////////////////////////////

RankBonusInfo::RankBonusInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

RankBonusInfo::~RankBonusInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

string RankBonusInfo::toString() const
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "RankBonusInfo ("
		<< "Type:"			<< (int)m_Type
		<< ",Name:"			<< m_Name
		<< ",Rank:"			<< m_Rank
		<< ",Point:"		<< m_Point
		<< ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class RankBonusInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

RankBonusInfoManager::RankBonusInfoManager()
	throw()
{
	__BEGIN_TRY

	m_Count = 0;
	m_RankBonusInfoList = NULL;

	__END_CATCH
}

RankBonusInfoManager::~RankBonusInfoManager()
	throw()
{
	__BEGIN_TRY

	SAFE_DELETE_ARRAY(m_RankBonusInfoList);

	__END_CATCH
}

void RankBonusInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void RankBonusInfoManager::clear()
	throw()
{
	__BEGIN_TRY
	
	if ( m_RankBonusInfoList != NULL )
	{
		for ( uint i = 0; i < m_Count; i++ )
		{
			if ( m_RankBonusInfoList[i] != NULL )
				SAFE_DELETE( m_RankBonusInfoList[i] );
		}
	}
	SAFE_DELETE_ARRAY( m_RankBonusInfoList );

	__END_CATCH
}

void RankBonusInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	clear();

	Statement* pStmt    = NULL;
	Result*    pResult  = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Type) FROM RankBonusInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in RankBonusInfo Table");
		}

		pResult->next();

		m_Count = pResult->getInt(1) + 1;

		Assert (m_Count > 0);

		m_RankBonusInfoList = new RankBonusInfo* [m_Count];

		for (uint i=0 ; i < m_Count; i++)
			m_RankBonusInfoList[i] = NULL;

		pResult = pStmt->executeQuery("SELECT Type, Name, Rank, Point, Race FROM RankBonusInfo");

		while (pResult->next()) 
		{
			RankBonusInfo* pRankBonusInfo = new RankBonusInfo();
			int i = 0;

			pRankBonusInfo->setType( pResult->getInt(++i) );
			pRankBonusInfo->setName( pResult->getString(++i) );
			pRankBonusInfo->setRank( pResult->getInt(++i) );
			pRankBonusInfo->setPoint( pResult->getInt(++i) );
			pRankBonusInfo->setRace( pResult->getInt(++i) );

			addRankBonusInfo(pRankBonusInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void RankBonusInfoManager::save()
	throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError (__PRETTY_FUNCTION__);
	
	__END_CATCH
}

RankBonusInfo* RankBonusInfoManager::getRankBonusInfo( DWORD rankBonusType ) const
	throw( NoSuchElementException, OutOfBoundException, Error )
{
	__BEGIN_TRY

	if ( rankBonusType >= m_Count )
	{
		cerr << "RankBonusInfoManager::getRankBonusInfo() : out of bound" << endl;
		throw OutOfBoundException();
	}

	if ( m_RankBonusInfoList[rankBonusType] == NULL )
	{
		cerr << "RankBonusInfoManager::getRankBonusInfo() : no such element" << endl;
		throw NoSuchElementException();
	}

	return m_RankBonusInfoList[rankBonusType];

	__END_CATCH
}

void RankBonusInfoManager::addRankBonusInfo(RankBonusInfo* pRankBonusInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert (pRankBonusInfo != NULL);

	if (m_RankBonusInfoList[pRankBonusInfo->getType()] != NULL)
		throw DuplicatedException ();

	m_RankBonusInfoList[pRankBonusInfo->getType()] = pRankBonusInfo;

	__END_CATCH
}

string RankBonusInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "RankBonusInfoManager(\n";

	for (int i = 0 ; i < (int)m_Count ; i ++)
	{
		msg << "RankBonusInfos[" << i << "] == ";
		msg	<< (m_RankBonusInfoList[i] == NULL ? "NULL" : m_RankBonusInfoList[i]->getName());
		msg << "\n";
		if (m_RankBonusInfoList[i] != NULL) {
			msg << m_RankBonusInfoList[i]->toString() << "\n";
		}
	}

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
RankBonusInfoManager* g_pRankBonusInfoManager = NULL;
