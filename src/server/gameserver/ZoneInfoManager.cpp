//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneInfoManager.cpp
// Written By  : reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ZoneInfoManager.h"
#include "ZoneUtil.h"
#include "DB.h"

#include "SystemAvailabilitiesManager.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
ZoneInfoManager::ZoneInfoManager () 
	throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
ZoneInfoManager::~ZoneInfoManager () 
	throw ()
{
	__BEGIN_TRY

	hash_map< ZoneID_t , ZoneInfo *>::iterator itr = m_ZoneInfos.begin();
	for (; itr != m_ZoneInfos.end(); itr++)
	{
		ZoneInfo* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	// 해쉬맵안에 있는 모든 pair 들을 삭제한다.
	m_ZoneInfos.clear();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////////////
// initialize zone info manager
//////////////////////////////////////////////////////////////////////////////
void ZoneInfoManager::init () 
	throw (Error)
{
	__BEGIN_TRY

	// init == load
	load();
			
	__END_CATCH
}

	
//void testMaxMemory();

//////////////////////////////////////////////////////////////////////////////
// load from database
//////////////////////////////////////////////////////////////////////////////
void ZoneInfoManager::load ()
	throw (Error)
{
	__BEGIN_TRY

	bool bReload = !m_ZoneInfos.empty();

	Statement* pStmt = NULL;

	BEGIN_DB
	{

		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT ZoneID, ZoneGroupID, Type, Level, AccessMode, OwnerID, PayPlayZone, PremiumZone, PKZone, NoPortalZone, HolyLand, Available, OpenLevel, SMPFilename, SSIFilename, FullName, ShortName FROM ZoneInfo");

		while (pResult->next()) 
		{
			uint i = 0;

			ZoneID_t zoneID = pResult->getInt(++i);

//			cout << "load ZoneInfo = " << zoneID << endl;

			ZoneInfo* pZoneInfo = NULL;
			bool bExistInfo = false;
			
			if (bReload)
			{
				hash_map< ZoneID_t , ZoneInfo *>::iterator itr = m_ZoneInfos.find(zoneID);
				
				if (itr != m_ZoneInfos.end()) 
				{
					pZoneInfo = itr->second;
					bExistInfo = true;
				}
				else
				{
					pZoneInfo = new ZoneInfo();
				}
			}
			else
			{
				pZoneInfo = new ZoneInfo();
			}
			//cout << "new OK" << endl;

			//if (zoneID!=31 && zoneID!=21)
			{
				pZoneInfo->setZoneID(zoneID);
				pZoneInfo->setZoneGroupID(pResult->getInt(++i));
				pZoneInfo->setZoneType(pResult->getString(++i));
				pZoneInfo->setZoneLevel(pResult->getInt(++i));
				pZoneInfo->setZoneAccessMode(pResult->getString(++i));
				pZoneInfo->setZoneOwnerID(pResult->getString(++i));
				pZoneInfo->setPayPlay(pResult->getInt(++i)!=0);
				pZoneInfo->setPremiumZone(pResult->getInt(++i)!=0);
				pZoneInfo->setPKZone(pResult->getInt(++i)!=0);
				pZoneInfo->setNoPortalZone(pResult->getInt(++i)!=0);
				pZoneInfo->setHolyLand(pResult->getInt(++i)!=0);
				pZoneInfo->setAvailable(pResult->getInt(++i)!=0);
				pZoneInfo->setOpenLevel(pResult->getInt(++i));
				pZoneInfo->setSMPFilename(pResult->getString(++i));
				pZoneInfo->setSSIFilename(pResult->getString(++i));
				pZoneInfo->setFullName(pResult->getString(++i));
				pZoneInfo->setShortName(pResult->getString(++i));

				pZoneInfo->setAvailable(
					pZoneInfo->isAvailable()
					&& pZoneInfo->getOpenLevel() < SystemAvailabilitiesManager::getInstance()->getZoneOpenDegree()
				);

				if (!bExistInfo)
				{
					addZoneInfo(pZoneInfo);
				}

				/*
				if (zoneID==22)
				{
					testMaxMemory();
				}
				*/
			
				//cout << "load ZoneInfo = " << zoneID << endl;
				//cout << "ZoneInfo = " << pZoneInfo->toString().c_str() << endl << endl;
			}
			/*
			else
			{
				cout << "skip load ZoneID = " << i << endl << endl;
			}
			*/

		}
			
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// add zone info to zone info manager
//////////////////////////////////////////////////////////////////////////////
void ZoneInfoManager::addZoneInfo (ZoneInfo* pZoneInfo) 
	throw (Error)
{
	__BEGIN_TRY

	// 일단 같은 아이디의 존이 있는지 체크해본다.
	hash_map< ZoneID_t , ZoneInfo *>::iterator itr = m_ZoneInfos.find(pZoneInfo->getZoneID());
	
	if (itr != m_ZoneInfos.end())
		// 똑같은 아이디가 이미 존재한다는 소리다. - -;
		throw Error("duplicated zone id");

	m_ZoneInfos[ pZoneInfo->getZoneID() ] = pZoneInfo;

	// Zone full name 맵에다 존 ID를 집어넣어둔다.
	// 운영자 명령어를 위한 기능이다.
	hash_map<string, ZoneInfo*>::iterator fitr = m_FullNameMap.find(pZoneInfo->getFullName());
	if (fitr != m_FullNameMap.end())
	{
		cerr << "Duplicated Zone Full Name" << endl;
		throw Error("Duplicated Zone Full Name");
	}

	m_FullNameMap[pZoneInfo->getFullName()] = pZoneInfo;

	// Zone short name 맵에다 존 ID를 집어넣어둔다.
	// 운영자 명령어를 위한 기능이다.
	hash_map<string, ZoneInfo*>::iterator sitr = m_ShortNameMap.find(pZoneInfo->getShortName());
	if (sitr != m_ShortNameMap.end())
	{
		cerr << "Duplicated Zone Short Name" << endl;
		throw Error("Duplicated Zone Short Name");
	}

	m_ShortNameMap[pZoneInfo->getShortName()] = pZoneInfo;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// Delete zone info from zone info manager
//////////////////////////////////////////////////////////////////////////////
void ZoneInfoManager::deleteZoneInfo (ZoneID_t zoneID) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY
		
	hash_map< ZoneID_t , ZoneInfo *>::iterator itr = m_ZoneInfos.find(zoneID);
	
	if (itr != m_ZoneInfos.end()) 
	{
		// 존을 삭제한다.
		SAFE_DELETE(itr->second);

		// pair를 삭제한다.
		m_ZoneInfos.erase(itr);
	} 
	else 
	{
		// 그런 존 아이디를 찾을 수 없었을 때
		StringStream msg;
		msg << "ZoneID : " << zoneID;
		throw NoSuchElementException(msg.toString());
	}

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////////////
// get zone from zone info manager
//////////////////////////////////////////////////////////////////////////////
ZoneInfo* ZoneInfoManager::getZoneInfo (ZoneID_t zoneID) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY
		
	ZoneInfo* pZoneInfo = NULL;

	hash_map< ZoneID_t , ZoneInfo *>::iterator itr = m_ZoneInfos.find(zoneID);
	
	if (itr != m_ZoneInfos.end()) {

		pZoneInfo = itr->second;

	} else {

		// 그런 존 아이디를 찾을 수 없었을 때
		StringStream msg;
		msg << "ZoneID : " << zoneID; 
		throw NoSuchElementException(msg.toString());

	}

	return pZoneInfo;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get zone from zone info manager
//////////////////////////////////////////////////////////////////////////////
ZoneInfo* ZoneInfoManager::getZoneInfoByName(const string & ZoneName)
{
	// 먼저 short name map을 검색한다.
	hash_map<string, ZoneInfo*>::const_iterator short_itr = m_ShortNameMap.find(ZoneName);
	if (short_itr != m_ShortNameMap.end())
	{
		return short_itr->second;
	}

	// 없다면 full name map을 검색한다.
	hash_map<string, ZoneInfo*>::const_iterator full_itr = m_FullNameMap.find(ZoneName);
	if (full_itr != m_FullNameMap.end())
	{
		return full_itr->second;
	}

	// 아무 곳에도 없었다면 그냥 NULL을 리턴한다.
	return NULL;
}

vector<Zone*> ZoneInfoManager::getNormalFields() const
{
	vector<Zone*> ret;

//	hash_map< ZoneID_t , ZoneInfo *>::const_iterator itr = m_ZoneInfos.begin();
//	hash_map< ZoneID_t , ZoneInfo *>::const_iterator endItr = m_ZoneInfos.end();
//	
//	for ( ; itr != endItr ; ++itr )
//	{
//		if ( itr->second->getZoneType() == ZONE_NORMAL_FIELD ) ret.push_back( getZoneByZoneID( itr->first ) );
//	}

	ret.push_back( getZoneByZoneID(13) );

	return ret;
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string ZoneInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ZoneInfoManager(";

	if (m_ZoneInfos.empty()) msg << "EMPTY";
	else 
	{
		for (hash_map< ZoneID_t , ZoneInfo* >::const_iterator itr = m_ZoneInfos.begin() ; itr != m_ZoneInfos.end() ; itr ++) 
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}


// global variable definition
ZoneInfoManager* g_pZoneInfoManager = NULL;
