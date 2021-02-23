//////////////////////////////////////////////////////////////////////////////
// Filename    : SweeperBonusManager.cpp
// Written By  : beowulf
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Zone.h"
#include "ZoneUtil.h"
#include "SweeperBonus.h"
#include "SweeperBonusManager.h"
#include "LevelWarManager.h"
#include "LevelWarZoneInfoManager.h"
#include "DB.h"

#include "Gpackets/GCSweeperBonusInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class SweeperBonusManager member methods
//////////////////////////////////////////////////////////////////////////////

SweeperBonusManager::SweeperBonusManager()
	throw()
{
	__BEGIN_TRY

	m_Count = 0;

	__END_CATCH
}

SweeperBonusManager::~SweeperBonusManager()
	throw()
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void SweeperBonusManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void SweeperBonusManager::clear()
	throw()
{
	__BEGIN_TRY

	SweeperBonusHashMapItor itr = m_SweeperBonuses.begin();
	for ( ; itr != m_SweeperBonuses.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_SweeperBonuses.clear();
	
	__END_CATCH
}

void SweeperBonusManager::load()
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
		pResult = pStmt->executeQuery("SELECT MAX(Type) FROM SweeperBonusInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in SweeperBonusInfo Table");
		}

		pResult->next();

		m_Count = pResult->getInt(1) + 1;

		Assert (m_Count > 0);

		pResult = pStmt->executeQuery("SELECT Type, Name, OptionList, OwnerRace, Level FROM SweeperBonusInfo");

		while (pResult->next()) 
		{
			SweeperBonus* pSweeperBonus = new SweeperBonus();
			int i = 0;

			pSweeperBonus->setType( pResult->getInt(++i) );
			pSweeperBonus->setName( pResult->getString(++i) );
			pSweeperBonus->setOptionTypeList( pResult->getString(++i) );
			pSweeperBonus->setRace( pResult->getInt(++i) );
			pSweeperBonus->setLevel( pResult->getInt(++i) );

			addSweeperBonus(pSweeperBonus);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void SweeperBonusManager::reloadOwner(int level)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt    = NULL;
	Result*    pResult  = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Type) FROM SweeperBonusInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in SweeperBonusInfo Table");
		}

		pResult->next();

		m_Count = pResult->getInt(1) + 1;

		Assert (m_Count > 0);

		pResult = pStmt->executeQuery("SELECT Type, OwnerRace FROM SweeperBonusInfo WHERE Level = %d", level);

		while (pResult->next()) 
		{
			int i = 0;
			SweeperBonusType_t type = pResult->getInt(++i);

			SweeperBonusHashMapItor itr = m_SweeperBonuses.find(type);

			if ( itr != m_SweeperBonuses.end() )
			{
				itr->second->setRace( pResult->getInt(++i) );
			}

		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void SweeperBonusManager::save()
	throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError (__PRETTY_FUNCTION__);
	
	__END_CATCH
}

SweeperBonus* SweeperBonusManager::getSweeperBonus( SweeperBonusType_t sweeperBonusType ) const
	throw( NoSuchElementException, Error )
{
	__BEGIN_TRY

	SweeperBonusHashMapConstItor itr = m_SweeperBonuses.find( sweeperBonusType );

	if ( itr == m_SweeperBonuses.end() )
	{
		cerr << "SweeperBonusManager::getSweeperBonus() : no such element" << endl;
		throw NoSuchElementException();
	}

	return itr->second;

	__END_CATCH
}

void SweeperBonusManager::addSweeperBonus(SweeperBonus* pSweeperBonus)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert (pSweeperBonus != NULL);

	SweeperBonusHashMapConstItor itr = m_SweeperBonuses.find( pSweeperBonus->getType() );
	if ( itr != m_SweeperBonuses.end() )
	{
		throw DuplicatedException ();
	}

	m_SweeperBonuses[pSweeperBonus->getType()] = pSweeperBonus;

	__END_CATCH
}


bool SweeperBonusManager::isAble(ZoneID_t zoneID) const
{
	__BEGIN_TRY

	ZoneID_t levelWarZoneID;
	if ( g_pLevelWarZoneInfoManager->getLevelWarZoneID( zoneID, levelWarZoneID ) )
	{
		Zone* pZone = getZoneByZoneID( levelWarZoneID );
		if ( pZone == NULL ) return false;

		LevelWarManager* pLevelWarManager = pZone->getLevelWarManager();
		if ( pLevelWarManager == NULL ) return false;

		return !pLevelWarManager->hasWar();
	}

	return false;

	__END_CATCH
}

void SweeperBonusManager::setSweeperBonusRace( SweeperBonusType_t sweeperBonusType, Race_t race )
	throw( Error )
{
	__BEGIN_TRY

	getSweeperBonus( sweeperBonusType )->setRace( race );

	__END_CATCH
}

void SweeperBonusManager::makeSweeperBonusInfo( GCSweeperBonusInfo& gcSweeperBonusInfo )
	throw( Error )
{
	__BEGIN_TRY

	SweeperBonusHashMapConstItor itr = m_SweeperBonuses.begin();
	for ( ; itr != m_SweeperBonuses.end(); itr++ )
	{
		SweeperBonusInfo* pInfo = new SweeperBonusInfo();
		SweeperBonus* pBonus = itr->second;

		pInfo->setType( pBonus->getType() );
		pInfo->setRace( pBonus->getRace() );
		pInfo->setOptionType( pBonus->getOptionTypeList() );

		gcSweeperBonusInfo.addSweeperBonusInfo( pInfo );
	}

	__END_CATCH
}

void SweeperBonusManager::makeVoidSweeperBonusInfo( GCSweeperBonusInfo& gcSweeperBonusInfo )
	throw( Error )
{
	__BEGIN_TRY

	SweeperBonusHashMapConstItor itr = m_SweeperBonuses.begin();
	for ( ; itr != m_SweeperBonuses.end(); itr++ )
	{
		SweeperBonusInfo* pInfo = new SweeperBonusInfo();
		SweeperBonus* pBonus = itr->second;

		pInfo->setType( pBonus->getType() );
		pInfo->setRace( 3 );
		pInfo->setOptionType( pBonus->getOptionTypeList() );

		gcSweeperBonusInfo.addSweeperBonusInfo( pInfo );
	}

	__END_CATCH
}

string SweeperBonusManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SweeperBonusManager(\n";

	SweeperBonusHashMapConstItor itr = m_SweeperBonuses.begin();
	for ( ; itr != m_SweeperBonuses.end(); itr++ )
	{
		msg << itr->second->toString() << ",";
	}

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
SweeperBonusManager* g_pSweeperBonusManager = NULL;
