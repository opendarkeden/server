//////////////////////////////////////////////////////////////////////////////
// Filename    : MasterLairInfoManager.cpp
// Written By  : reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "MasterLairInfoManager.h"
#include "MonsterInfo.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "DB.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
MasterLairInfo::MasterLairInfo()
{
	m_ZoneID = 0;
	m_MasterMonsterType = 0;
	m_MasterNotReadyMonsterType = 0;
	m_MasterRemainNotReady = false;
	m_MasterX = 0;
	m_MasterY = 0;
	m_MasterDir = 0;
	m_MaxPassPlayer = 0;
	//m_MaxSummonMonster = 0;
	m_SummonX = 0;
	m_SummonY = 0;
	m_FirstRegenDelay = 0;
	m_RegenDelay = 0;
	m_StartDelay = 0;
	m_EndDelay = 0;
	m_KickOutDelay = 0;
	m_KickZoneID = 0;
	m_KickZoneX = 0;
	m_KickZoneY = 0;
	m_LairAttackTick = 0;
	m_LairAttackMinNumber = 0;
	m_LairAttackMaxNumber = 0;
}

MasterLairInfo::~MasterLairInfo()
{
}

// a      bc
// "hihihi", "dsfsdfsd sdfds, sfd", "anfdsf"
void MasterLairInfo::setSayText(vector<string>& sayWords, const string& text) 
	throw()
{
	sayWords.clear();

	if (text.empty()) return;

	uint a=0, b=0, c=0;
	while (c < text.size())
	{
		a = text.find_first_of('\"', c);
		b = text.find_first_of('\"', a+1);
		c = text.find_first_of(',', b+1);

		if (a==string::npos || b==string::npos)
			break;

		string words = text.substr(a+1, b-a-1);

		sayWords.push_back( words );

//		cout << "SayWord: " << words.c_str() << endl;
	}
}

void MasterLairInfo::setMasterSummonSay(const string& text) 
	throw()
{
	setSayText(m_MasterSummonSay, text);
}

void MasterLairInfo::setMasterDeadSlayerSay(const string& text) 
	throw()
{
	setSayText(m_MasterDeadSlayerSay, text);
}

void MasterLairInfo::setMasterDeadVampireSay(const string& text) 
	throw()
{
	setSayText(m_MasterDeadVampireSay, text);
}

void MasterLairInfo::setMasterNotDeadSay(const string& text) 
	throw()
{
	setSayText(m_MasterNotDeadSay, text);
}

const string& MasterLairInfo::getRandomMasterSummonSay() const 
	throw()
{
	static string stringNULL = "";

	if (m_MasterSummonSay.empty()) return stringNULL;

	return m_MasterSummonSay[rand()%m_MasterSummonSay.size()];
}


const string& MasterLairInfo::getRandomMasterDeadSlayerSay() const 
	throw()
{
	static string stringNULL = "";

	if (m_MasterDeadSlayerSay.empty()) return stringNULL;

	return m_MasterDeadSlayerSay[rand()%m_MasterDeadSlayerSay.size()];
}

const string& MasterLairInfo::getRandomMasterDeadVampireSay() const 
	throw()
{
	static string stringNULL = "";

	if (m_MasterDeadVampireSay.empty()) return stringNULL;

	return m_MasterDeadVampireSay[rand()%m_MasterDeadVampireSay.size()];
}

const string& MasterLairInfo::getRandomMasterNotDeadSay() const 
	throw()
{
	static string stringNULL = "";

	if (m_MasterNotDeadSay.empty()) return stringNULL;

	return m_MasterNotDeadSay[rand()%m_MasterNotDeadSay.size()];
}

string
MasterLairInfo::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MasterLairInfo("
		<< "ZoneID:" << (int)m_ZoneID
		<< ",MasterNotReadyMonsterType:" << (int)m_MasterNotReadyMonsterType
		<< ",MasterMonsterType:" << (int)m_MasterMonsterType
		<< ",MasterRemainNotReady:" << (int)m_MasterRemainNotReady
		<< ",MasterX:" << (int)m_MasterX
		<< ",MasterY:" << (int)m_MasterY
		<< ",MasterDir:" << (int)m_MasterDir
		<< ",MaxPassPlayer:" << (int)m_MaxPassPlayer
		//<< ",MaxSummonMonster:" << (int)m_MaxSummonMonster
		<< ",SummonX:" << (int)m_SummonX
		<< ",SummonY:" << (int)m_SummonY
		<< ",FirstRegenDelay:" << (int)m_FirstRegenDelay
		<< ",RegenDelay:" << (int)m_RegenDelay
		<< ",StartDelay:" << (int)m_StartDelay
		<< ",EndDelay:" << (int)m_EndDelay
		<< ",KickOutDelay:" << (int)m_KickOutDelay
		<< ",KickZoneID:" << (int)m_KickZoneID
		<< ",KickZoneX:" << (int)m_KickZoneX
		<< ",KickZoneY:" << (int)m_KickZoneY
		<< ",LairAttackTick:" << (int)m_LairAttackTick
		<< ",LairAttackMinNumber:" << (int)m_LairAttackMinNumber
		<< ",LairAttackMaxNumber:" << (int)m_LairAttackMaxNumber
		<< ")";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
MasterLairInfoManager::MasterLairInfoManager () 
	throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
MasterLairInfoManager::~MasterLairInfoManager () 
	throw ()
{
	__BEGIN_TRY

	hash_map< ZoneID_t , MasterLairInfo *>::iterator itr = m_MasterLairInfos.begin();
	for (; itr != m_MasterLairInfos.end(); itr++)
	{
		MasterLairInfo* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	// 해쉬맵안에 있는 모든 pair 들을 삭제한다.
	m_MasterLairInfos.clear();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////////////
// initialize zone info manager
//////////////////////////////////////////////////////////////////////////////
void MasterLairInfoManager::init () 
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
void MasterLairInfoManager::load ()
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{

		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT ZoneID, MasterNotReadyMonsterType, MasterMonsterType, MasterRemainNotReady, MasterX, MasterY, MasterDir, MaxPassPlayer, SummonX, SummonY, FirstRegenDelay, RegenDelay, StartDelay, EndDelay, KickOutDelay, KickZoneID, KickZoneX, KickZoneY, LairAttackTick, LairAttackMinNumber, LairAttackMaxNumber, MasterSummonSay, MasterDeadSlayerSay, MasterDeadVampireSay, MasterNotDeadSay FROM MasterLairInfo");

		while (pResult->next()) 
		{
			uint i = 0;

			ZoneID_t zoneID = pResult->getInt(++i);

			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( zoneID );
			Assert( pZoneInfo!=NULL );

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
			
			if(pZoneInfo->isAvailable())
			{

				cout << "LOAD MASTER LAIR : ZoneID(" << (int)zoneID << ") , Enable " << endl;
			
#endif
			
				pZoneInfo->setMasterLair();

				MasterLairInfo* pMasterLairInfo = new MasterLairInfo();
				//cout << "new OK" << endl;

				pMasterLairInfo->setZoneID( zoneID );
				pMasterLairInfo->setMasterNotReadyMonsterType( pResult->getInt(++i) );
				pMasterLairInfo->setMasterMonsterType( pResult->getInt(++i) );
				pMasterLairInfo->setMasterRemainNotReady( pResult->getInt(++i)!=0 );
				pMasterLairInfo->setMasterX( pResult->getInt(++i) );
				pMasterLairInfo->setMasterY( pResult->getInt(++i) );
				pMasterLairInfo->setMasterDir( pResult->getInt(++i) );
				pMasterLairInfo->setMaxPassPlayer( pResult->getInt(++i) );
				//pMasterLairInfo->setMaxSummonMonster( pResult->getInt(++i) );
				pMasterLairInfo->setSummonX( pResult->getInt(++i) );
				pMasterLairInfo->setSummonY( pResult->getInt(++i) );
				pMasterLairInfo->setFirstRegenDelay( pResult->getInt(++i) );
				pMasterLairInfo->setRegenDelay( pResult->getInt(++i) );
				pMasterLairInfo->setStartDelay( pResult->getInt(++i) );
				pMasterLairInfo->setEndDelay( pResult->getInt(++i) );
				pMasterLairInfo->setKickOutDelay( pResult->getInt(++i) );
				pMasterLairInfo->setKickZoneID( pResult->getInt(++i) );
				pMasterLairInfo->setKickZoneX( pResult->getInt(++i) );
				pMasterLairInfo->setKickZoneY( pResult->getInt(++i) );
				pMasterLairInfo->setLairAttackTick( pResult->getInt(++i) );
				pMasterLairInfo->setLairAttackMinNumber( pResult->getInt(++i) );
				pMasterLairInfo->setLairAttackMaxNumber( pResult->getInt(++i) );
				pMasterLairInfo->setMasterSummonSay( pResult->getString(++i) );
				pMasterLairInfo->setMasterDeadSlayerSay( pResult->getString(++i) );
				pMasterLairInfo->setMasterDeadVampireSay( pResult->getString(++i) );
				pMasterLairInfo->setMasterNotDeadSay( pResult->getString(++i) );

				addMasterLairInfo(pMasterLairInfo);

				//cout << pMasterLairInfo->toString().c_str() << endl;

				// 체크 코드
				// 마스터의 몬스터 정보가 있는지 체크한다.
				try {
					const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pMasterLairInfo->getMasterMonsterType() );

					if (pMonsterInfo==NULL)	// 나중을 위해서. -_-;
					{
						throw Error("마스터의 몬스터 정보가 없당.");
					}

					if (!pMonsterInfo->isMaster())
					{
						StringStream msg;
						msg << "몬스터 타잎[" 
							<< (int)pMasterLairInfo->getMasterMonsterType() 
							<< "]은 마스터가 아니다.";

						throw Error(msg.toString());
					}

				} catch (Throwable& t) {
					cout << t.toString().c_str() << endl;
					throw Error("마스터의 몬스터 정보가 없당.");
				}

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
			}//isAvailable
			else
			{
				cout << "LOAD MASTER LAIR : ZoneID(" << (int)zoneID << "), Disable " << endl;
			}
#endif
		}
			
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// reload from database
//////////////////////////////////////////////////////////////////////////////
void MasterLairInfoManager::reload ()
	throw (Error)
{
	__BEGIN_TRY
	
	//cout << "MasterLairInfoManager::reload()" << endl;

	Statement* pStmt = NULL;

	BEGIN_DB
	{

		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT ZoneID, MasterNotReadyMonsterType, MasterMonsterType, MasterRemainNotReady, MasterX, MasterY, MasterDir, MaxPassPlayer, SummonX, SummonY, FirstRegenDelay, RegenDelay, StartDelay, EndDelay, KickOutDelay, KickZoneID, KickZoneX, KickZoneY, LairAttackTick, LairAttackMinNumber, LairAttackMaxNumber, MasterSummonSay, MasterDeadSlayerSay, MasterDeadVampireSay, MasterNotDeadSay FROM MasterLairInfo");

		while (pResult->next()) 
		{
			uint i = 0;

			ZoneID_t zoneID = pResult->getInt(++i);

			MasterLairInfo* pMasterLairInfo = getMasterLairInfo( zoneID );
			//cout << "new OK" << endl;

			if (pMasterLairInfo!=NULL)
			{
				//cout << "Reload: " << zoneID << endl;
				pMasterLairInfo->setZoneID( zoneID );
				pMasterLairInfo->setMasterNotReadyMonsterType( pResult->getInt(++i) );
				pMasterLairInfo->setMasterMonsterType( pResult->getInt(++i) );
				pMasterLairInfo->setMasterRemainNotReady( pResult->getInt(++i)!=0 );
				pMasterLairInfo->setMasterX( pResult->getInt(++i) );
				pMasterLairInfo->setMasterY( pResult->getInt(++i) );
				pMasterLairInfo->setMasterDir( pResult->getInt(++i) );
				pMasterLairInfo->setMaxPassPlayer( pResult->getInt(++i) );
				//pMasterLairInfo->setMaxSummonMonster( pResult->getInt(++i) );
				pMasterLairInfo->setSummonX( pResult->getInt(++i) );
				pMasterLairInfo->setSummonY( pResult->getInt(++i) );
				pMasterLairInfo->setFirstRegenDelay( pResult->getInt(++i) );
				pMasterLairInfo->setRegenDelay( pResult->getInt(++i) );
				pMasterLairInfo->setStartDelay( pResult->getInt(++i) );
				pMasterLairInfo->setEndDelay( pResult->getInt(++i) );
				pMasterLairInfo->setKickOutDelay( pResult->getInt(++i) );
				pMasterLairInfo->setKickZoneID( pResult->getInt(++i) );
				pMasterLairInfo->setKickZoneX( pResult->getInt(++i) );
				pMasterLairInfo->setKickZoneY( pResult->getInt(++i) );
				pMasterLairInfo->setLairAttackTick( pResult->getInt(++i) );
				pMasterLairInfo->setLairAttackMinNumber( pResult->getInt(++i) );
				pMasterLairInfo->setLairAttackMaxNumber( pResult->getInt(++i) );
				pMasterLairInfo->setMasterSummonSay( pResult->getString(++i) );
				pMasterLairInfo->setMasterDeadSlayerSay( pResult->getString(++i) );
				pMasterLairInfo->setMasterDeadVampireSay( pResult->getString(++i) );
				pMasterLairInfo->setMasterNotDeadSay( pResult->getString(++i) );

				// 체크 코드
				// 마스터의 몬스터 정보가 있는지 체크한다.
				try {
					const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pMasterLairInfo->getMasterMonsterType() );

					if (pMonsterInfo==NULL)	// 나중을 위해서. -_-;
					{
						throw Error("마스터의 몬스터 정보가 없당.");
					}

					if (!pMonsterInfo->isMaster())
					{
						StringStream msg;
						msg << "몬스터 타잎[" 
							<< (int)pMasterLairInfo->getMasterMonsterType() 
							<< "]은 마스터가 아니다.";

						throw Error(msg.toString());
					}

				} catch (Throwable& t) {
					cout << t.toString().c_str() << endl;
					throw Error("마스터의 몬스터 정보가 없당.");
				}
			}
		}
			
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// add zone info to zone info manager
//////////////////////////////////////////////////////////////////////////////
void MasterLairInfoManager::addMasterLairInfo (MasterLairInfo* pMasterLairInfo) 
	throw (Error)
{
	__BEGIN_TRY

	// 일단 같은 아이디의 존이 있는지 체크해본다.
	hash_map< ZoneID_t , MasterLairInfo *>::iterator itr = m_MasterLairInfos.find(pMasterLairInfo->getZoneID());
	
	if (itr != m_MasterLairInfos.end())
		// 똑같은 아이디가 이미 존재한다는 소리다. - -;
		throw Error("duplicated zone id");

	m_MasterLairInfos[ pMasterLairInfo->getZoneID() ] = pMasterLairInfo;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// Delete zone info from zone info manager
//////////////////////////////////////////////////////////////////////////////
void MasterLairInfoManager::deleteMasterLairInfo (ZoneID_t zoneID) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY
		
	hash_map< ZoneID_t , MasterLairInfo *>::iterator itr = m_MasterLairInfos.find(zoneID);
	
	if (itr != m_MasterLairInfos.end()) 
	{
		// 존을 삭제한다.
		SAFE_DELETE(itr->second);

		// pair를 삭제한다.
		m_MasterLairInfos.erase(itr);
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
MasterLairInfo* MasterLairInfoManager::getMasterLairInfo (ZoneID_t zoneID) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY
		
	MasterLairInfo* pMasterLairInfo = NULL;

	hash_map< ZoneID_t , MasterLairInfo *>::iterator itr = m_MasterLairInfos.find(zoneID);
	
	if (itr != m_MasterLairInfos.end()) {

		pMasterLairInfo = itr->second;

	} else {

		// 그런 존 아이디를 찾을 수 없었을 때
		/*
		StringStream msg;
		msg << "ZoneID : " << zoneID; 
		throw NoSuchElementException(msg.toString());
		*/

		return NULL;

	}

	return pMasterLairInfo;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string MasterLairInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "MasterLairInfoManager(";

	if (m_MasterLairInfos.empty()) msg << "EMPTY";
	else 
	{
		for (hash_map< ZoneID_t , MasterLairInfo* >::const_iterator itr = m_MasterLairInfos.begin() ; itr != m_MasterLairInfos.end() ; itr ++) 
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}


// global variable definition
MasterLairInfoManager* g_pMasterLairInfoManager = NULL;
