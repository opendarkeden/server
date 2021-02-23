#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "ZoneUtil.h"
#include "LevelWarZoneInfoManager.h"

LevelWarZoneInfo::LevelWarZoneInfo()
{
}

LevelWarZoneInfo::~LevelWarZoneInfo()
{
}

void LevelWarZoneInfo::setZoneIDList( const string& zoneIDs )	
	throw()
{
	__BEGIN_TRY

	makeZoneIDList( zoneIDs, m_LevelWarBonusZoneIDList );

	__END_CATCH
}

bool LevelWarZoneInfo::isBonusZone(ZoneID_t targetZoneID) const
	throw (Error)
{
	__BEGIN_TRY

	list<ZoneID_t>::const_iterator itr = m_LevelWarBonusZoneIDList.begin();
	list<ZoneID_t>::const_iterator endItr = m_LevelWarBonusZoneIDList.end();

	for ( ; itr != endItr ; itr++)
	{
		ZoneID_t zoneID = *itr;

		if (zoneID==targetZoneID)
		return true;
	}

	return false;

	__END_CATCH
}

bool LevelWarZoneInfo::isCreatureThisLevel(Creature* pCreature) const 
	throw()
{
	__BEGIN_TRY

	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		
		return (pSlayer->getTotalAttr( ATTR_BASIC ) >= getMinSlayerSum() && pSlayer->getTotalAttr( ATTR_BASIC ) <= getMaxSlayerSum());
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		return (pVampire->getLevel() >= getMinVampireLevel() && pVampire->getLevel() <= getMaxVampireLevel());
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		return (pOusters->getLevel() >= getMinOustersLevel() && pOusters->getLevel() <= getMaxOustersLevel());
	}

	return false;

	__END_CATCH
}

bool LevelWarZoneInfo::isZoneThisLevel(ZoneID_t zoneID) const
	throw()
{
	__BEGIN_TRY

	list<ZoneID_t>::const_iterator itr = m_LevelWarBonusZoneIDList.begin();
	list<ZoneID_t>::const_iterator endItr = m_LevelWarBonusZoneIDList.end();

	for (; itr != endItr ; itr++)
	{
		if (*itr == zoneID)
			return true;
	}

	return false;

	__END_CATCH
}

string LevelWarZoneInfo::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "LevelWarZoneInfo("
		<< "Grade : " << m_LevelWarGrade
		<< ", ZoneID : " << m_ZoneID
		<< ", SweeperTypeMin : " << m_SweeperTypeMin
		<< ", SweeperTypeMax : " << m_SweeperTypeMax
		<< ", SlayerSumMin : " << m_SlayerSumMin
		<< ", SlayerSumMax : " << m_SlayerSumMax
		<< ", VampireLevelMin : " << m_VampireLevelMin
		<< ", VampireLevelMax : " << m_VampireLevelMax
		<< ", OustersLevelMin : " << m_OustersLevelMin
		<< ", OustersLevelMax : " << m_OustersLevelMax
		<< ")";

	return msg.toString();

	__END_CATCH
}

LevelWarZoneInfoManager::LevelWarZoneInfoManager()
{
}

LevelWarZoneInfoManager::~LevelWarZoneInfoManager()
{
	__BEGIN_TRY

	hash_map< ZoneID_t , LevelWarZoneInfo* >::iterator itr = m_LevelWarZoneInfos.begin();
	hash_map< ZoneID_t , LevelWarZoneInfo* >::iterator endItr = m_LevelWarZoneInfos.end();
	for (; itr != endItr ; itr++)
	{
		LevelWarZoneInfo* pLevelWarZoneInfo = itr->second;
		SAFE_DELETE(pLevelWarZoneInfo);
	}

	m_LevelWarZoneInfos.clear();

	__END_CATCH
}

void LevelWarZoneInfoManager::init() 
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void LevelWarZoneInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	m_LevelWarZoneInfos.clear();
	clearLevelWarZoneIDs();

	Statement* pStmt = NULL;

	BEGIN_DB
	{

		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
				"SELECT ID, ZoneID, SweeperTypeMin, SweeperTypeMax, SlayerMin, SlayerMax, VampireMin, VampireMax, OustersMin, OustersMax, ZoneIDList FROM LevelWarZoneInfo");

		while (pResult->next())
		{
			uint i = 0;

			LevelWarZoneInfo* pLevelWarZoneInfo = new LevelWarZoneInfo();

			pLevelWarZoneInfo->setGrade( pResult->getInt(++i) );
			pLevelWarZoneInfo->setZoneID( pResult->getInt(++i) );

			pLevelWarZoneInfo->setMinSweeperBonusType( pResult->getInt(++i) );
			pLevelWarZoneInfo->setMaxSweeperBonusType( pResult->getInt(++i) );

			pLevelWarZoneInfo->setMinSlayerSum( pResult->getInt(++i) );
			pLevelWarZoneInfo->setMaxSlayerSum( pResult->getInt(++i) );

			pLevelWarZoneInfo->setMinVampireLevel( pResult->getInt(++i) );
			pLevelWarZoneInfo->setMaxVampireLevel( pResult->getInt(++i) );

			pLevelWarZoneInfo->setMinOustersLevel( pResult->getInt(++i) );
			pLevelWarZoneInfo->setMaxOustersLevel( pResult->getInt(++i) );

			pLevelWarZoneInfo->setZoneIDList( pResult->getString(++i) );

			addLevelWarZoneInfo( pLevelWarZoneInfo );

		}
		
	}
	END_DB(pStmt)

	__END_CATCH
}

void LevelWarZoneInfoManager::addLevelWarZoneInfo( LevelWarZoneInfo* pLevelWarZoneInfo ) 
	throw(Error)
{
	__BEGIN_TRY

	hash_map< ZoneID_t , LevelWarZoneInfo*>::iterator itr = m_LevelWarZoneInfos.find(pLevelWarZoneInfo->getZoneID());

	if (itr != m_LevelWarZoneInfos.end())
		throw Error("duplicated zone id");

	m_LevelWarZoneInfos[ pLevelWarZoneInfo->getZoneID() ] = pLevelWarZoneInfo;

	const list<ZoneID_t>& zoneIDs = pLevelWarZoneInfo->getZoneIDList();

	list<ZoneID_t>::const_iterator zitr = zoneIDs.begin();
	list<ZoneID_t>::const_iterator zendItr = zoneIDs.end();

	for ( ; zitr != zendItr ; zitr++ )
	{
		ZoneID_t zoneID = *zitr;
		setLevelWarZoneID( zoneID, pLevelWarZoneInfo->getZoneID() );
	}

	__END_CATCH
}

int LevelWarZoneInfoManager::getCreatureLevelGrade( Creature* pCreature )
	throw(Error)
{
	hash_map< ZoneID_t , LevelWarZoneInfo*>::iterator itr = m_LevelWarZoneInfos.begin();
	hash_map< ZoneID_t , LevelWarZoneInfo*>::iterator endItr = m_LevelWarZoneInfos.end();

	for ( ; itr != endItr ; itr++ )
	{
		if ( itr->second->isCreatureThisLevel( pCreature ) )
			return itr->second->getGrade();
	}
	
	return -1;
}

ZoneID_t LevelWarZoneInfoManager::getCreatureZoneID( Creature* pCreature )
	throw(Error)
{
	hash_map< ZoneID_t , LevelWarZoneInfo*>::iterator itr = m_LevelWarZoneInfos.begin();
	hash_map< ZoneID_t , LevelWarZoneInfo*>::iterator endItr = m_LevelWarZoneInfos.end();

	for ( ; itr != endItr ; itr++ )
	{
		if ( itr->second->isCreatureThisLevel( pCreature ) )
			return itr->second->getZoneID();
	}
	
	return 1;
}

bool LevelWarZoneInfoManager::isCreatureBonusZone( Creature* pCreature, ZoneID_t zoneID ) const
	throw(Error)
{
	hash_map< ZoneID_t , LevelWarZoneInfo*>::const_iterator itr = m_LevelWarZoneInfos.begin();
	hash_map< ZoneID_t , LevelWarZoneInfo*>::const_iterator endItr = m_LevelWarZoneInfos.end();

	for ( ; itr != endItr ; itr++ )
	{
		LevelWarZoneInfo* pLevelWarZoneInfo = itr->second;

		if (pLevelWarZoneInfo->isCreatureThisLevel( pCreature )
			&& pLevelWarZoneInfo->isZoneThisLevel( zoneID ) )
		{
			return true;
		}
	}

	return false;
}

LevelWarZoneInfo* LevelWarZoneInfoManager::getLevelWarZoneInfo( ZoneID_t zoneID ) const 
	throw(Error)
{
	__BEGIN_TRY

	hash_map< ZoneID_t , LevelWarZoneInfo*>::const_iterator itr = m_LevelWarZoneInfos.find(zoneID);

	if (itr != m_LevelWarZoneInfos.end())
		return NULL;
	else
		return itr->second;


	__END_CATCH
}

/*
void LevelWarZoneInfoManager::refreshSweeperBonusZonePlayer()
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	hash_map< ZoneID_t , LevelWarZoneInfo* >::const_iterator itr = m_LevelWarZoneInfos.begin();
	hash_map< ZoneID_t , LevelWarZoneInfo* >::const_iterator endItr = m_LevelWarZoneInfos.end();

	for (; itr != endItr ;itr++)
	{
		LevelWarZoneInfo* pLevelWarZoneInfo = itr->second;
		list<ZoneID_t>::const_iterator zitr = pLevelWarZoneInfo->getZoneIDList().begin();
		list<ZoneID_t>::const_iterator zendItr = pLevelWarZoneInfo->getZoneIDList().end();

		for ( ; zitr != zendItr ; zitr++ )
		{
			Zone* pZone = getZoneByZoneID( *zitr );
			pZone->setRefreshLevelWarBonusZonePlayer( true );
		}
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH


}
*/

void LevelWarZoneInfoManager::broadcast( ZoneID_t zoneID, Packet* pPacket ) const
    throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	hash_map< ZoneID_t , LevelWarZoneInfo* >::const_iterator itr = m_LevelWarZoneInfos.find(zoneID);

//	cout << VSDateTime::currentDateTime().toString() << endl;
	if (itr != m_LevelWarZoneInfos.end())
	{
		LevelWarZoneInfo* pLevelWarZoneInfo = itr->second;
		list<ZoneID_t>::const_iterator zitr = pLevelWarZoneInfo->getZoneIDList().begin();
		list<ZoneID_t>::const_iterator zendItr = pLevelWarZoneInfo->getZoneIDList().end();

		for ( ; zitr != zendItr ; zitr++ )
		{
//			cout << *zitr << endl;
			Zone* pZone = getZoneByZoneID( *zitr );
			pZone->broadcastLevelWarBonusPacket( pPacket );
		}
	}
//	cout << VSDateTime::currentDateTime().toString() << endl;

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

void LevelWarZoneInfoManager::clearLevelWarZoneIDs() 
	throw(Error)
{
	__BEGIN_TRY

	m_LevelWarZoneIDs.clear();
	
	__END_CATCH
}

bool LevelWarZoneInfoManager::getLevelWarZoneID( ZoneID_t zoneID, ZoneID_t &levelWarZoneID ) const 
	throw(Error)
{

	__BEGIN_TRY

	hash_map< ZoneID_t , ZoneID_t >::const_iterator itr = m_LevelWarZoneIDs.find( zoneID );
	
	if ( itr != m_LevelWarZoneIDs.end() )
	{
		levelWarZoneID = itr->second;
		return true;
	}
	
	return false;

	__END_CATCH
}
void LevelWarZoneInfoManager::setLevelWarZoneID( ZoneID_t zoneID, ZoneID_t levelWarZoneID )
	throw (Error)
{
	__BEGIN_TRY

	m_LevelWarZoneIDs[zoneID] = levelWarZoneID;
	
	__END_CATCH
}

string LevelWarZoneInfoManager::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "LevelWarZoneInfoManager(";

	if (m_LevelWarZoneInfos.empty()) msg << "EMPTY";
	else
	{
		hash_map< ZoneID_t , LevelWarZoneInfo* >::const_iterator itr = m_LevelWarZoneInfos.begin();
		hash_map< ZoneID_t , LevelWarZoneInfo* >::const_iterator endItr = m_LevelWarZoneInfos.end();
		for (; itr != endItr ;itr++)
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
LevelWarZoneInfoManager* g_pLevelWarZoneInfoManager = NULL;
