//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBibleBonusManager.cpp
// Written By  : beowulf
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodBibleBonus.h"
#include "BloodBibleBonusManager.h"
#include "DB.h"

#include "Gpackets/GCHolyLandBonusInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodBibleBonusManager member methods
//////////////////////////////////////////////////////////////////////////////

BloodBibleBonusManager::BloodBibleBonusManager()
	throw()
{
	__BEGIN_TRY

	m_Count = 0;

	__END_CATCH
}

BloodBibleBonusManager::~BloodBibleBonusManager()
	throw()
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void BloodBibleBonusManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void BloodBibleBonusManager::clear()
	throw()
{
	__BEGIN_TRY

	BloodBibleBonusHashMapItor itr = m_BloodBibleBonuses.begin();
	for ( ; itr != m_BloodBibleBonuses.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_BloodBibleBonuses.clear();
	
	__END_CATCH
}

void BloodBibleBonusManager::load()
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
		pResult = pStmt->executeQuery("SELECT MAX(Type) FROM BloodBibleBonusInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in BloodBibleBonusInfo Table");
		}

		pResult->next();

		m_Count = pResult->getInt(1) + 1;

		Assert (m_Count > 0);

		pResult = pStmt->executeQuery("SELECT Type, Name, OptionList FROM BloodBibleBonusInfo");

		while (pResult->next()) 
		{
			BloodBibleBonus* pBloodBibleBonus = new BloodBibleBonus();
			int i = 0;

			pBloodBibleBonus->setType( pResult->getInt(++i) );
			pBloodBibleBonus->setName( pResult->getString(++i) );
			pBloodBibleBonus->setOptionTypeList( pResult->getString(++i) );
			pBloodBibleBonus->setRace( 0 );

			addBloodBibleBonus(pBloodBibleBonus);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void BloodBibleBonusManager::save()
	throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError (__PRETTY_FUNCTION__);
	
	__END_CATCH
}

BloodBibleBonus* BloodBibleBonusManager::getBloodBibleBonus( BloodBibleBonusType_t bloodBibleBonusType ) const
	throw( NoSuchElementException, Error )
{
	__BEGIN_TRY

	BloodBibleBonusHashMapConstItor itr = m_BloodBibleBonuses.find( bloodBibleBonusType );

	if ( itr == m_BloodBibleBonuses.end() )
	{
		cerr << "BloodBibleBonusManager::getBloodBibleBonus() : no such element" << endl;
		throw NoSuchElementException();
	}

	return itr->second;

	__END_CATCH
}

void BloodBibleBonusManager::addBloodBibleBonus(BloodBibleBonus* pBloodBibleBonus)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert (pBloodBibleBonus != NULL);

	BloodBibleBonusHashMapConstItor itr = m_BloodBibleBonuses.find( pBloodBibleBonus->getType() );
	if ( itr != m_BloodBibleBonuses.end() )
	{
		throw DuplicatedException ();
	}

	m_BloodBibleBonuses[pBloodBibleBonus->getType()] = pBloodBibleBonus;

	__END_CATCH
}

void BloodBibleBonusManager::setBloodBibleBonusRace( BloodBibleBonusType_t bloodBibleBonusType, Race_t race )
	throw( Error )
{
	__BEGIN_TRY

	getBloodBibleBonus( bloodBibleBonusType )->setRace( race );

	__END_CATCH
}

void BloodBibleBonusManager::makeHolyLandBonusInfo( GCHolyLandBonusInfo& gcHolyLandBonusInfo )
	throw( Error )
{
	__BEGIN_TRY

/*	BloodBibleBonusHashMapConstItor itr = m_BloodBibleBonuses.begin();
	for ( ; itr != m_BloodBibleBonuses.end(); itr++ )
	{
		BloodBibleBonusInfo* pInfo = new BloodBibleBonusInfo();
		BloodBibleBonus* pBonus = itr->second;

		pInfo->setType( pBonus->getType() );
		pInfo->setRace( pBonus->getRace() );
		pInfo->setOptionType( pBonus->getOptionTypeList() );

		gcHolyLandBonusInfo.addBloodBibleBonusInfo( pInfo );
	}*/

	__END_CATCH
}

string BloodBibleBonusManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "BloodBibleBonusManager(\n";

	BloodBibleBonusHashMapConstItor itr = m_BloodBibleBonuses.begin();
	for ( ; itr != m_BloodBibleBonuses.end(); itr++ )
	{
		msg << itr->second->toString() << ",";
	}

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
BloodBibleBonusManager* g_pBloodBibleBonusManager = NULL;
