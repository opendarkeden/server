#include "DatabaseManager.h"
#include "DB.h"
#include "PlayerCreature.h"

#include "CoupleManager.h"

bool CoupleManager::isCouple( PlayerCreature* pPC1, string name2 )
	throw(Error)
{
	__BEGIN_TRY
	
	Assert( pPC1 != NULL );

	Statement* pStmt = NULL;
	bool bRet = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM CoupleInfo where %s='%s' and %s='%s'",
					getFieldName( pPC1->getSex() ).c_str(), pPC1->getName().c_str(),
					getCounterFieldName( pPC1->getSex() ).c_str(), name2.c_str() );

		if (pResult->next()) 
		{
			int num = pResult->getInt( 1 );
			if ( num >= 1 ) bRet = true;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return bRet;

	__END_CATCH
}

bool CoupleManager::isCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 )
	throw(Error)
{
	__BEGIN_TRY
	
	Assert( pPC1 != NULL );
	Assert( pPC2 != NULL );

	if ( pPC1->getSex() == pPC2->getSex() ) return false;

	Statement* pStmt = NULL;
	bool bRet = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM CoupleInfo where %s='%s' and %s='%s'",
					getFieldName( pPC1->getSex() ).c_str(), pPC1->getName().c_str(),
					getFieldName( pPC2->getSex() ).c_str(), pPC2->getName().c_str() );

		if (pResult->next()) 
		{
			int num = pResult->getInt( 1 );
			if ( num >= 1 ) bRet = true;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return bRet;

	__END_CATCH
}

bool CoupleManager::hasCouple( PlayerCreature* pPC )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	Statement* pStmt = NULL;
	bool bRet = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM CoupleInfo where %s='%s'",
					getFieldName( pPC->getSex() ).c_str(), pPC->getName().c_str() );

		if (pResult->next()) 
		{
			int num = pResult->getInt( 1 );
			if ( num >= 1 ) bRet = true;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return bRet;

	__END_CATCH
}

bool CoupleManager::getPartnerName( PlayerCreature* pPC, string& partnerName )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	Statement* pStmt = NULL;
	bool bRet = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT %s FROM CoupleInfo where %s='%s'",
					getCounterFieldName( pPC->getSex() ).c_str(),
					getFieldName( pPC->getSex() ).c_str(), pPC->getName().c_str() );

		if (pResult->next()) 
		{
			partnerName = pResult->getString( 1 );
			bRet = true;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return bRet;

	__END_CATCH
}

void CoupleManager::makeCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC1 != NULL );
	Assert( pPC2 != NULL );

	Assert( pPC1->getRace() == pPC2->getRace() );
	Assert( pPC1->getSex() != pPC2->getSex() );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"INSERT INTO CoupleInfo (%s, %s, Race, CoupleDate ) VALUES ('%s','%s',%u, now())",
					getFieldName( pPC1->getSex() ).c_str(), getFieldName( pPC2->getSex() ).c_str(), 
					pPC1->getName().c_str(), pPC2->getName().c_str(), (uint)pPC1->getRace() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void CoupleManager::removeCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 ) 
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC1 != NULL );
	Assert( pPC2 != NULL );

	Assert( pPC1->getRace() == pPC2->getRace() );
	Assert( pPC1->getSex() != pPC2->getSex() );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"DELETE FROM CoupleInfo WHERE %s='%s' AND %s='%s' AND Race=%u",
					getFieldName( pPC1->getSex() ).c_str(), pPC1->getName().c_str(), 
					getFieldName( pPC2->getSex() ).c_str(), pPC2->getName().c_str(), 
					(uint)pPC1->getRace() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void CoupleManager::removeCoupleForce( PlayerCreature* pPC1, string strPC2 )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC1 != NULL );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "DELETE FROM CoupleInfo where %s='%s' AND %s='%s' AND Race=%u",
					getFieldName( pPC1->getSex() ).c_str(), pPC1->getName().c_str(),
					getCounterFieldName( pPC1->getSex() ).c_str(), strPC2.c_str(),
					(uint)(pPC1->getRace()) );
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void CoupleManager::removeCoupleForce( PlayerCreature* pPC1 ) throw(Error)
{
	__BEGIN_TRY

	Assert( pPC1 != NULL );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "DELETE FROM CoupleInfo where %s='%s' AND Race=%u",
					getFieldName( pPC1->getSex() ).c_str(), pPC1->getName().c_str(),
					(uint)(pPC1->getRace()) );
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

CoupleManager* g_pCoupleManager = NULL;
