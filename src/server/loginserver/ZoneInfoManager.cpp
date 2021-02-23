//----------------------------------------------------------------------
//
// Filename    : ZoneInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "ZoneInfoManager.h"
#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
ZoneInfoManager::ZoneInfoManager () 
	throw ()
{
}
	
//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
ZoneInfoManager::~ZoneInfoManager () 
	throw ()
{
	// hashmap 안의 각 pair 의 second, 즉 ZoneInfo 객체만을 삭제하고
	// pair 자체는 그대로 둔다. (ZoneInfo가 힙에 생성되어 있다는 것에
	// 유의하라. 즉 필살삭제를 해야 한다. 하긴, ZIM이 destruct 된다는 것은
	// 로그인 서버가 셧다운된다는 것을 의미하니깐.. - -; )
	for ( HashMapZoneInfo::iterator itr = m_ZoneInfos.begin() ; 
		  itr != m_ZoneInfos.end() ; 
		  itr ++ ) {
		delete itr->second;
		itr->second = NULL;
	}

	// 이제 해쉬맵안에 있는 모든 pair 들을 삭제한다.
	m_ZoneInfos.clear();
}
	

//----------------------------------------------------------------------
// initialize GSIM
//----------------------------------------------------------------------
void ZoneInfoManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	// just load data from ZoneInfo table
	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// load data from database
//----------------------------------------------------------------------
void ZoneInfoManager::load ()
	throw ( Error )
{
	__BEGIN_TRY

	Statement * pStmt;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result * pResult = pStmt->executeQuery(
			"SELECT ZoneID , ZoneGroupID FROM ZoneInfo"
		);

		while ( pResult->next() ) {
			ZoneInfo * pZoneInfo = new ZoneInfo();
			pZoneInfo->setZoneID( pResult->getWORD(1) );
			pZoneInfo->setZoneGroupID( pResult->getWORD(2) );
			addZoneInfo( pZoneInfo );
		}

	} catch ( SQLQueryException & sqe ) {

		// 필살 삭제!
		delete pStmt;

		throw Error(sqe.toString());
	}

	// 필살 삭제!
	delete pStmt;

	__END_CATCH
}

//----------------------------------------------------------------------
// add info 
//----------------------------------------------------------------------
void ZoneInfoManager::addZoneInfo ( ZoneInfo * pZoneInfo ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	HashMapZoneInfo::iterator itr = m_ZoneInfos.find( pZoneInfo->getZoneID() );
	
	if ( itr != m_ZoneInfos.end() )
		throw DuplicatedException("duplicated zone id");

	m_ZoneInfos[ pZoneInfo->getZoneID() ] = pZoneInfo;

	__END_CATCH
}
	
//----------------------------------------------------------------------
// delete info
//----------------------------------------------------------------------
void ZoneInfoManager::deleteZoneInfo ( ZoneID_t zoneID )
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	HashMapZoneInfo::iterator itr = m_ZoneInfos.find( zoneID );
	
	if ( itr != m_ZoneInfos.end() ) {

		// ZoneInfo 를 삭제한다.
		delete itr->second;

		// pair를 삭제한다.
		m_ZoneInfos.erase( itr );

	} else { // not found

		StringStream msg;
		msg << "ZoneID : " << zoneID;
		throw NoSuchElementException(msg.toString());

	}

	__END_CATCH
}
	
//----------------------------------------------------------------------
// get info
//----------------------------------------------------------------------
ZoneInfo * ZoneInfoManager::getZoneInfo ( ZoneID_t zoneID ) const
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	ZoneInfo * pZoneInfo = NULL;

	HashMapZoneInfo::const_iterator itr = m_ZoneInfos.find( zoneID );
	
	if ( itr != m_ZoneInfos.end() ) {

		pZoneInfo = itr->second;

	} else { // not found

		StringStream msg;
		msg << "ZoneID : " << zoneID;
		throw NoSuchElementException( msg.toString() );

	}

	return pZoneInfo;

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string ZoneInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ZoneInfoManager(\n";

	if ( m_ZoneInfos.empty() ) {

		msg << "EMPTY";

	} else {

		//--------------------------------------------------
		// *OPTIMIZATION*
		//
		// for_each()를 사용할 것
		//--------------------------------------------------
		for ( HashMapZoneInfo::const_iterator itr = m_ZoneInfos.begin() ; 
			  itr != m_ZoneInfos.end() ; 
			  itr ++ )
			msg << itr->second->toString() << '\n';
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
ZoneInfoManager * g_pZoneInfoManager = NULL;
