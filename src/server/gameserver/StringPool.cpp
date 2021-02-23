///////////////////////////////////////////////////////////
// Filename : StringPool.cpp
///////////////////////////////////////////////////////////

#include "StringPool.h"
#include "DB.h"

StringPool::StringPool()
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

StringPool::~StringPool()
	throw(Error)
{
	__BEGIN_TRY
	
	clear();

	__END_CATCH
}

void StringPool::clear()
	throw(Error)
{
	__BEGIN_TRY

	m_Strings.clear();

	__END_CATCH
}

void StringPool::load()
	throw(Error)
{
	__BEGIN_TRY
	
	clear();

	Statement* pStmt = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery( "SELECT ID, String FROM GSStringPool" );

		while ( pResult->next() )
		{
			int i = 0;

			uint	strID	= pResult->getInt( ++i );
			string	str		= pResult->getString( ++i );

			addString( strID, str );
		}
	}
	END_DB(pStmt)

	__END_CATCH
}

void StringPool::addString( uint strID, string sString )
	throw( DuplicatedException, Error )
{
	__BEGIN_TRY

	StringHashMapItor itr = m_Strings.find( strID );

	if ( itr != m_Strings.end() )
	{
		throw DuplicatedException("StringPool::addString()");
	}

	m_Strings[ strID ] = sString;


	__END_CATCH
}

string StringPool::getString( uint strID )
	throw( NoSuchElementException, Error )
{
	__BEGIN_TRY

	StringHashMapItor itr = m_Strings.find( strID );

	if ( itr == m_Strings.end() )
	{
		throw NoSuchElementException("StringPool::getString()");
	}

	return itr->second;

	__END_CATCH
}

const char* StringPool::c_str( uint strID )
	throw( NoSuchElementException, Error )
{
	__BEGIN_TRY

	StringHashMapItor itr = m_Strings.find( strID );

	if ( itr == m_Strings.end() )
	{
		throw NoSuchElementException("StringPool::getString()");
	}

	return itr->second.c_str();

	__END_CATCH
}

StringPool* g_pStringPool = NULL;
