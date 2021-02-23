//----------------------------------------------------------------------
//
// Filename    : ZoneGroupInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "ZoneGroupInfoManager.h"
#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
ZoneGroupInfoManager::ZoneGroupInfoManager () 
	throw ()
{
}
	
//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
ZoneGroupInfoManager::~ZoneGroupInfoManager () 
	throw ()
{
	// hashmap 안의 각 pair 의 second, 즉 ZoneGroupInfo 객체만을 삭제하고
	// pair 자체는 그대로 둔다. (ZoneGroupInfo가 힙에 생성되어 있다는 것에
	// 유의하라. 즉 필살삭제를 해야 한다. 하긴, ZGIM이 destruct 된다는 것은
	// 로그인 서버가 셧다운된다는 것을 의미하니깐.. - -; )
	for ( HashMapZoneGroupInfo::iterator itr = m_ZoneGroupInfos.begin() ; 
		  itr != m_ZoneGroupInfos.end() ; 
		  itr ++ ) {
		delete itr->second;
		itr->second = NULL;
	}

	// 이제 해쉬맵안에 있는 모든 pair 들을 삭제한다.
	m_ZoneGroupInfos.clear();
}
	

//----------------------------------------------------------------------
// initialize GSIM
//----------------------------------------------------------------------
void ZoneGroupInfoManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	// just load data from ZoneGroupInfo table
	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// load data from database
//----------------------------------------------------------------------
void ZoneGroupInfoManager::load ()
	throw ( Error )
{
	__BEGIN_TRY

	Statement * pStmt;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result * pResult = pStmt->executeQuery(
			"SELECT ZoneGroupID , ServerID FROM ZoneGroupInfo"
		);

		while ( pResult->next() ) {
			ZoneGroupInfo * pZoneGroupInfo = new ZoneGroupInfo();
			pZoneGroupInfo->setZoneGroupID( pResult->getWORD(1) );
			pZoneGroupInfo->setServerID( pResult->getWORD(2) );
			addZoneGroupInfo( pZoneGroupInfo );
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
void ZoneGroupInfoManager::addZoneGroupInfo ( ZoneGroupInfo * pZoneGroupInfo ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	HashMapZoneGroupInfo::iterator itr = m_ZoneGroupInfos.find( pZoneGroupInfo->getZoneGroupID() );
	
	if ( itr != m_ZoneGroupInfos.end() )
		throw DuplicatedException("duplicated zone id");

	m_ZoneGroupInfos[ pZoneGroupInfo->getZoneGroupID() ] = pZoneGroupInfo;

	__END_CATCH
}
	
//----------------------------------------------------------------------
// delete info
//----------------------------------------------------------------------
void ZoneGroupInfoManager::deleteZoneGroupInfo ( ZoneGroupID_t zoneGroupID )
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	HashMapZoneGroupInfo::iterator itr = m_ZoneGroupInfos.find( zoneGroupID );
	
	if ( itr != m_ZoneGroupInfos.end() ) {

		// ZoneGroupInfo 를 삭제한다.
		delete itr->second;

		// pair를 삭제한다.
		m_ZoneGroupInfos.erase( itr );

	} else { // not found

		StringStream msg;
		msg << "ZoneGroupID : " << zoneGroupID;
		throw NoSuchElementException(msg.toString());

	}

	__END_CATCH
}
	
//----------------------------------------------------------------------
// get info
//----------------------------------------------------------------------
ZoneGroupInfo * ZoneGroupInfoManager::getZoneGroupInfo ( ZoneGroupID_t zoneGroupID ) const
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	ZoneGroupInfo * pZoneGroupInfo = NULL;

	HashMapZoneGroupInfo::const_iterator itr = m_ZoneGroupInfos.find( zoneGroupID );
	
	if ( itr != m_ZoneGroupInfos.end() ) {

		pZoneGroupInfo = itr->second;

	} else { // not found

		StringStream msg;
		msg << "ZoneGroupID : " << zoneGroupID;
		throw NoSuchElementException( msg.toString() );

	}

	return pZoneGroupInfo;

	__END_CATCH
}


//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string ZoneGroupInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ZoneGroupInfoManager(";

	if ( m_ZoneGroupInfos.empty() ) {

		msg << "EMPTY";

	} else {

		//--------------------------------------------------
		// *OPTIMIZATION*
		//
		// for_each()를 사용할 것
		//--------------------------------------------------
		for ( HashMapZoneGroupInfo::const_iterator itr = m_ZoneGroupInfos.begin() ; 
			  itr != m_ZoneGroupInfos.end() ; 
			  itr ++ )
			msg << itr->second->toString();
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
ZoneGroupInfoManager * g_pZoneGroupInfoManager = NULL;
