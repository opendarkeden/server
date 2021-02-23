//////////////////////////////////////////////////////////////////////////////
// Filename    : ResurrectLocationManager.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ResurrectLocationManager.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
// global variable
//////////////////////////////////////////////////////////////////////////////

ResurrectLocationManager* g_pResurrectLocationManager = NULL;

//////////////////////////////////////////////////////////////////////////////
// class ResurrectLocationManager member methods
//////////////////////////////////////////////////////////////////////////////

ResurrectLocationManager::ResurrectLocationManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

ResurrectLocationManager::~ResurrectLocationManager()
	throw()
{
	__BEGIN_TRY

	m_SlayerPosition.clear();
	m_VampirePosition.clear();

	__END_CATCH
}

void ResurrectLocationManager::init() 
	throw ()
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void ResurrectLocationManager::load() 
	throw ()
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ZoneID, SResurrectZoneID, SResurrectX, SResurrectY, VResurrectZoneID, VResurrectX, VResurrectY FROM ZoneInfo");
		
		if (pResult->getRowCount() == 0)
		{
			cerr << "ResurrectLocationManager::load() : TABLE DOES NOT EXIST!" << endl;
			throw ("ResurrectLocationManager::load() : TABLE DOES NOT EXIST!");
		}

		while (pResult->next())
		{
			ZoneID_t   ID = 0;
			ZONE_COORD slayer_coord;
			ZONE_COORD vampire_coord;

			ID               = pResult->getInt(1);
			slayer_coord.id  = pResult->getInt(2);
			slayer_coord.x   = pResult->getInt(3);
			slayer_coord.y   = pResult->getInt(4);
			vampire_coord.id = pResult->getInt(5);
			vampire_coord.x  = pResult->getInt(6);
			vampire_coord.y  = pResult->getInt(7);

			addSlayerPosition(ID, slayer_coord);
			addVampirePosition(ID, vampire_coord);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

bool ResurrectLocationManager::getSlayerPosition(ZoneID_t id, ZONE_COORD& zoneCoord) const 
	throw ()//NoSuchElementException)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, ZONE_COORD>::const_iterator itr = m_SlayerPosition.find(id);

	if (itr == m_SlayerPosition.end())
	{
		cerr << "ResurrectLocationManager::getPosition() : No Such ZoneID" << endl;
		//throw NoSuchElementException("ResurrectLocationManager::getPosition() : No Such ZoneID");

		// NoSuch제거. by sigi. 2002.5.9
		return false;
	}

	//return itr->second;
	zoneCoord = itr->second;

	return true;

	__END_CATCH
}


void ResurrectLocationManager::addSlayerPosition(ZoneID_t id, const ZONE_COORD& coord) 
	throw (DuplicatedException, Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, ZONE_COORD>::const_iterator itr = m_SlayerPosition.find(id);

	if (itr != m_SlayerPosition.end())
	{
		cerr << "ResurrectLocationManager::addPosition() : ZoneID already exist!" << endl;
		throw NoSuchElementException("ResurrectLocationManager::addPosition() : ZoneID already exist!");
	}

	m_SlayerPosition[id] = coord;

	__END_CATCH
}

bool ResurrectLocationManager::getVampirePosition(ZoneID_t id, ZONE_COORD& zoneCoord) const 
	throw ()//NoSuchElementException)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, ZONE_COORD>::const_iterator itr = m_VampirePosition.find(id);

	if (itr == m_VampirePosition.end())
	{
		cerr << "ResurrectLocationManager::getPosition() : No Such ZoneID" << endl;
		// NoSuch제거. by sigi. 2002.5.9
		//throw NoSuchElementException("ResurrectLocationManager::getPosition() : No Such ZoneID");
		return false;
	}

	//return itr->second;

	zoneCoord = itr->second;

	return true;

	__END_CATCH
}


void ResurrectLocationManager::addVampirePosition(ZoneID_t id, const ZONE_COORD& coord) 
	throw (DuplicatedException, Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, ZONE_COORD>::const_iterator itr = m_VampirePosition.find(id);

	if (itr != m_VampirePosition.end())
	{
		cerr << "ResurrectLocationManager::addPosition() : ZoneID already exist!" << endl;
		throw NoSuchElementException("ResurrectLocationManager::addPosition() : ZoneID already exist!");
	}

	m_VampirePosition[id] = coord;

	__END_CATCH
}

