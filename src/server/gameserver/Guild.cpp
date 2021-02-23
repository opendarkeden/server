//////////////////////////////////////////////////////////////////////////////
// Filename		: Guild.cpp
// Written by	: bezz
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include <algorithm>

#include "Guild.h"
#include "StringStream.h"
#include "DB.h"

#ifdef __SHARED_SERVER__
	#include "GuildInfo2.h"
	#include "GuildMemberInfo2.h"
#endif

#include "GuildInfo.h"
#include "Gpackets/GCGuildMemberList.h"
#include "GuildMemberInfo.h"
#include "Properties.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// class GuildMember member methods
//////////////////////////////////////////////////////////////////////////////

GuildMember::GuildMember()
	throw()
{
	m_bLogOn = false;
	m_ServerID = 255;
}

void GuildMember::create()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT GuildID FROM GuildMember WHERE Name = '%s'", m_Name.c_str() );

		if ( pResult->getRowCount() != 0 )
		{
			// 이미 디비에 존재하므로 데이터만 고쳐준다.(즉, 전에 다른 길드에 속한 적이 있다)
			if ( m_Rank == GUILDMEMBER_RANK_WAIT )
			{
				pStmt->executeQuery( "UPDATE GuildMember SET GuildID = %d, Rank = %d, ExpireDate = '', RequestDateTime = '%s' WHERE Name = '%s'",
										m_GuildID, m_Rank, getRequestDateTime().c_str(), m_Name.c_str() );
			}
			else
			{
				pStmt->executeQuery( "UPDATE GuildMember SET GuildID = %d, Rank = %d, ExpireDate = '' WHERE Name = '%s'",
										m_GuildID, m_Rank, m_Name.c_str() );
			}
		}
		else
		{
			if ( m_Rank == GUILDMEMBER_RANK_WAIT )
			{
				pStmt->executeQuery( "INSERT INTO GuildMember( GuildID, Name, Rank, RequestDateTime ) VALUES ( %d, '%s', %d, '%s' )",
										m_GuildID, m_Name.c_str(),  m_Rank, getRequestDateTime().c_str() );
			}
			else
			{
				pStmt->executeQuery( "INSERT INTO GuildMember( GuildID, Name, Rank ) VALUES ( %d, '%s', %d )",
										m_GuildID, m_Name.c_str(),  m_Rank );
			}
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
	
}


bool GuildMember::load()
	throw()
{
	__BEGIN_TRY
	
	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT GuildID, Name, Rank, LogOn FROM GuildMember WHERE Name = '%s'", m_Name.c_str() );

		if ( pResult->getRowCount() != 1 )
		{
			SAFE_DELETE( pStmt );
			return false;
		}

		pResult->next();

		m_GuildID	= pResult->getInt(1);
		m_Name		= pResult->getString(2);
		m_Rank		= pResult->getInt(3);
		m_bLogOn	= pResult->getInt(4);

		m_ServerID  = g_pConfig->getPropertyInt("ServerID");

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return true;

	__END_CATCH
}


void GuildMember::save()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		
		pStmt->executeQuery( "UPDATE GuildMember SET GuildID = %d, Rank = %d WHERE Name = '%s'",
								m_GuildID, m_Rank, m_Name.c_str() );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
}


void GuildMember::destroy()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "DELETE FROM GuildMember WHERE Name = '%s'", m_Name.c_str() );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
}

void GuildMember::expire()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		// 현재 실시간 날짜를 구한다.
		time_t daytime = time(0);
		tm Timec;
		localtime_r( &daytime, &Timec );
		char ExpireDate[8];
		sprintf( ExpireDate, "%03d%02d%02d", Timec.tm_year, Timec.tm_mon, Timec.tm_mday );

		pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

		pStmt->executeQuery( "UPDATE GuildMember SET Rank = %d, ExpireDate = '%s' WHERE Name = '%s'", GUILDMEMBER_RANK_DENY, ExpireDate, m_Name.c_str() );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
}

void GuildMember::leave()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		// 현재 실시간 날짜를 구한다.
		time_t daytime = time(0);
		tm Timec;
		localtime_r( &daytime, &Timec );
		char ExpireDate[8];
		sprintf( ExpireDate, "%03d%02d%02d", Timec.tm_year, Timec.tm_mon, Timec.tm_mday );

		pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

		pStmt->executeQuery( "UPDATE GuildMember SET Rank = %d, ExpireDate = '%s' WHERE Name = '%s'", GUILDMEMBER_RANK_LEAVE, ExpireDate, m_Name.c_str() );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
}


void GuildMember::saveIntro( const string& intro )
	throw()
{
	__BEGIN_TRY

	Statement* pStmt;

	string modifyIntro = Guild::correctString( intro );

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

		pStmt->executeQuery( "UPDATE GuildMember SET Intro = '%s' WHERE Name = '%s'", modifyIntro.c_str(), m_Name.c_str() );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__END_CATCH
}


string GuildMember::getIntro() const
	throw()
{
	__BEGIN_TRY

	Statement* pStmt;
	Result* pResult;

	string intro = "";

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
		pResult = pStmt->executeQuery( "SELECT Intro FROM GuildMember WHERE Name = '%s'", m_Name.c_str() );

		if ( pResult->next() )
		{
			intro = pResult->getString(1);
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return intro;

	__END_CATCH
}


string GuildMember::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "GuildID = " << (int)m_GuildID << " Name = " << m_Name << " Rank = " << (int)m_Rank << endl;

	return msg.toString();

	__END_CATCH
}


GuildMember& GuildMember::operator=( GuildMember& Member )
{
	m_GuildID		= Member.m_GuildID;
	m_Name			= Member.m_Name;
	m_Rank			= Member.m_Rank;

	return *this;
}

string GuildMember::getRequestDateTime() const
	throw()
{
	__BEGIN_TRY

	char buf[20];

	sprintf( buf, "%4d-%02d-%02d %02d:%02d:%02d",
			m_RequestDateTime.date().year(), m_RequestDateTime.date().month(), m_RequestDateTime.date().day(),
			m_RequestDateTime.time().hour(), m_RequestDateTime.time().minute(), m_RequestDateTime.time().second() );

	cout << buf << endl;

	return string(buf);

	__END_CATCH
}


void GuildMember::setRank(GuildMemberRank_t rank)
	throw()
{
	__BEGIN_TRY

	m_Rank = rank;

	__END_CATCH
}


void GuildMember::setRequestDateTime( const string& rtime )
	throw()
{
	__BEGIN_TRY

	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if ( rtime.size() == 19 )
	{
		int year	= atoi( rtime.substr(0,4).c_str() );
		int month	= atoi( rtime.substr(5,2).c_str() );
		int day		= atoi( rtime.substr(8,2).c_str() );
		int hour	= atoi( rtime.substr(11,2).c_str() );
		int min		= atoi( rtime.substr(14,2).c_str() );
		int second	= atoi( rtime.substr(17,2).c_str() );

		m_RequestDateTime.setDate( VSDate( year, month, day ) );
		m_RequestDateTime.setTime( VSTime( hour, min, second ) );
	}
	else
	{
		m_RequestDateTime.setDate( VSDate( 2000, 1, 1 ) );
		m_RequestDateTime.setTime( VSTime( 0, 0, 0 ) );
	}

	__END_CATCH
}

bool GuildMember::isRequestDateTimeOut( const VSDateTime& currentDateTime ) const
	throw()
{
	__BEGIN_TRY

	VSDateTime limitDateTime = m_RequestDateTime.addDays(7);

	return currentDateTime > limitDateTime;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// global variable initialization
//////////////////////////////////////////////////////////////////////////////

GuildID_t Guild::m_MaxGuildID = 0;
ZoneID_t Guild::m_MaxSlayerZoneID = 10000;
ZoneID_t Guild::m_MaxVampireZoneID = 20000;
ZoneID_t Guild::m_MaxOustersZoneID = 30000;

//////////////////////////////////////////////////////////////////////////////
// class Guild member methods
//////////////////////////////////////////////////////////////////////////////

Guild::Guild()
	throw()
{
	m_ID			= 0;
	m_Name			= "";
	m_Type			= 0;
	m_State			= 0;
	m_ServerGroupID	= 0;
	m_ZoneID		= 0;
	m_Master		= "";
	m_Date			= "";
	m_Intro			= "";

	m_ActiveMemberCount = 0;
	m_WaitMemberCount = 0;

	__BEGIN_TRY
	
	m_Mutex.setName( "Guild" );

	__END_CATCH
}


Guild::~Guild()
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapGuildMemberItor itr = m_Members.begin();
	for ( ; itr != m_Members.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_Members.clear();

#ifdef __GAME_SERVER__
	m_CurrentMembers.clear();
#endif

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}


void Guild::create()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	string correctIntro = correctString( m_Intro );

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "INSERT INTO GuildInfo ( GuildID, GuildName, GuildType, GuildRace, GuildState, ServerGroupID, GuildZoneID, Master, Date, Intro ) VALUES ( %d, '%s', %d, %d, %d, %d, %d, '%s', '%s', '%s' )",
				m_ID, m_Name.c_str(), m_Type, m_Race, m_State, m_ServerGroupID, m_ZoneID, m_Master.c_str(), m_Date.c_str(), correctIntro.c_str() );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


bool Guild::load()
	throw()
{
	__BEGIN_TRY

	Statement*	pStmt	= NULL;
	Result*		pResult	= NULL;	

	__ENTER_CRITICAL_SECTION(m_Mutex)

	BEGIN_DB
	{
		pStmt	= g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult	= pStmt->executeQuery( "SELECT GuildName, GuildType, GuildRace, GuildState, ServerGroupID, GuildZoneID, Master, Date FROM GuildInfo WHERE GuildID = %d", m_ID );

		if ( pResult->getRowCount() != 1 )
		{
			SAFE_DELETE( pStmt );
			m_Mutex.unlock();

			return false;
		}

		pResult->next();

		m_Name			= pResult->getString( 1 );
		m_Type			= pResult->getInt( 2 );
		m_Race			= pResult->getInt( 3 );
		m_State			= pResult->getInt( 4 );
		m_ServerGroupID	= pResult->getInt( 5 );
		m_ZoneID		= pResult->getInt( 6 );
		m_Master		= pResult->getString( 7 );
		m_Date			= pResult->getString( 8 );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return true;

	__END_CATCH
}


void Guild::save()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE GuildInfo SET GuildName = '%s', GuildType = %d, GuildRace = %d, GuildState = %d, ServerGroupID = %d, GuildZoneID = %d, Master = '%s', Date = '%s' WHERE GuildID = %d",
								m_Name.c_str(), m_Type, m_Race, m_State, m_ServerGroupID, m_ZoneID, m_Master.c_str(), m_Date.c_str(), m_ID );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


void Guild::destroy()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "DELETE FROM GuildInfo WHERE GuildID = %d", m_ID );
		pStmt->executeQuery( "DELETE FROM GuildUnionMember WHERE OwnerGuildID = %d", m_ID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


#ifdef __SHARED_SERVER__
void Guild::saveIntro( const string& intro )
	throw()
{
	__BEGIN_TRY

	m_Intro = intro;

	Statement* pStmt = NULL;

	string modifyIntro = Guild::correctString( intro );

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE GuildInfo SET Intro = '%s' WHERE GuildID = %u", modifyIntro.c_str(), m_ID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void Guild::tinysave( const char* field ) const
	throw()
{
	__BEGIN_TRY
	
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE GuildInfo SET %s WHERE GuildID = %u", field, m_ID );

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )

	__END_CATCH
}

void Guild::saveCount() const throw()
{
	__BEGIN_TRY

//	char buffer[200];
//	sprintf(buffer, "MemberCount=%u", m_ActiveMemberCount);
//	tinysave(buffer);

	__END_CATCH
}
#endif


GuildMember* Guild::getMember( const string& name ) const
	throw()
{
	__BEGIN_TRY

	HashMapGuildMemberConstItor itr;
	GuildMember* pGuildMember = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)
	
	itr = m_Members.find( name );

	if ( itr == m_Members.end() )
	{
		//cout << "Guild::getMember() : NoSuchMember" << endl;
		m_Mutex.unlock();

		return NULL;
	}

	pGuildMember = itr->second;

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	return pGuildMember;

	__END_CATCH
}


GuildMember* Guild::getMember_NOLOCKED( const string& name ) const
	throw()
{
	__BEGIN_TRY

	HashMapGuildMemberConstItor itr;
	GuildMember* pGuildMember = NULL;

	itr = m_Members.find( name );

	if ( itr == m_Members.end() )
	{
		//cerr << "Guild::getMember() : NoSuchMember" << endl;

		return NULL;
	}

	pGuildMember = itr->second;

	return pGuildMember;

	__END_CATCH
}

void Guild::addMember( GuildMember* pMember )
	throw( DuplicatedException, Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Assert( pMember );

	HashMapGuildMemberConstItor itr;

	itr = m_Members.find( pMember->getName() );

	if ( itr != m_Members.end() )
	{
		m_Mutex.unlock();
		throw DuplicatedException();
	}

	m_Members[ pMember->getName() ] = pMember;

	GuildMemberRank_t rank = pMember->getRank();
	
	if ( rank == GuildMember::GUILDMEMBER_RANK_NORMAL ||
		 rank == GuildMember::GUILDMEMBER_RANK_MASTER ||
		 rank == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		// 일반회원이나 (서브)마스터가 추가될때 ActiverMemberCount를 증가시킨다.
		m_ActiveMemberCount++;
	}
	else if ( rank == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		// 가입 대기자가 추가될때 WaitMemberCount 를 증가 시킨다.
		m_WaitMemberCount++;
	}

#ifdef __SHARED_SERVER__
	saveCount();
#endif

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


void Guild::deleteMember( const string& name )
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	HashMapGuildMemberItor itr;

	itr = m_Members.find( name );

	if ( itr == m_Members.end() )
	{
		cerr << "Guild::deleteMember() : NoSuchElementException" << endl;
		m_Mutex.unlock();

		return;
	}

	GuildMemberRank_t rank = itr->second->getRank();

	if ( rank == GuildMember::GUILDMEMBER_RANK_NORMAL
	  || rank == GuildMember::GUILDMEMBER_RANK_MASTER
	  || rank == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		// 활동중인 회원수 카운터를 감소 시킨다
		m_ActiveMemberCount--;
	}
	else if ( rank == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		m_WaitMemberCount--;
	}

	SAFE_DELETE( itr->second );

	m_Members.erase(itr);

#ifdef __SHARED_SERVER__
	saveCount();
#endif

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


void Guild::modifyMember( GuildMember& Member )
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	HashMapGuildMemberConstItor itr;

	itr = m_Members.find( Member.getName() );

	if ( itr == m_Members.end() )
	{
		cerr << "Guild::modifyMember() : NoSuchElementException" << endl;
		m_Mutex.unlock();

		return;
	}

	*(itr->second) = Member;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


void Guild::modifyMemberRank( const string& name, GuildMemberRank_t rank )
	throw()
{
	__BEGIN_TRY
	
	GuildMember* pMember = getMember( name );
	if ( pMember == NULL ) return;

	GuildMemberRank_t oldRank = pMember->getRank();

	if ( oldRank == rank )
		return;

	if ( oldRank == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		m_WaitMemberCount--;
	}
	else if ( oldRank == GuildMember::GUILDMEMBER_RANK_NORMAL
			|| oldRank == GuildMember::GUILDMEMBER_RANK_MASTER
			|| oldRank == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		m_ActiveMemberCount--;
	}
	
	if ( rank == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		m_WaitMemberCount++;
	}
	else if ( rank == GuildMember::GUILDMEMBER_RANK_NORMAL
			|| rank == GuildMember::GUILDMEMBER_RANK_MASTER
			|| rank == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		m_ActiveMemberCount++;
	}

	pMember->setRank( rank );

#ifdef __SHARED_SERVER__
	pMember->save();
	saveCount();
#endif

	__END_CATCH
}


#ifdef __GAME_SERVER__
void Guild::addCurrentMember( const string& name )
	throw ( DuplicatedException, Error )
{
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)		// 다른 뮤텍스 써도 될 듯한데.. 귀찮아..

	if ( m_CurrentMembers.end() != find( m_CurrentMembers.begin(), m_CurrentMembers.end(), name ) )
	{
		m_Mutex.unlock();
		return;
	}

	m_CurrentMembers.push_back( name );

	// Guild Member 객체에 로그온을 세팅한다.
	GuildMember* pGuildMember = getMember_NOLOCKED( name );
	if ( pGuildMember == NULL ) 
	{
		m_Mutex.unlock();
		return;
	}

	pGuildMember->setLogOn( true );

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void Guild::deleteCurrentMember( const string& name )
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)

	list<string>::iterator itr =  find( m_CurrentMembers.begin(), m_CurrentMembers.end(), name );

	if ( m_CurrentMembers.end() == itr )
	{
		m_Mutex.unlock();
		return;
	}

	m_CurrentMembers.erase( itr );

	// Guild Member 객체에 로그오프를 세팅한다.
	GuildMember* pGuildMember = getMember_NOLOCKED( name );
	if ( pGuildMember == NULL ) 
	{
		m_Mutex.unlock();
		return;
	}

	pGuildMember->setLogOn( false );

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

list<string> Guild::getCurrentMembers()
	throw()
{
	__BEGIN_TRY
	
	list<string> cmList;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	cmList = m_CurrentMembers;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return cmList;

	__END_CATCH
}
#endif

#ifdef __SHARED_SERVER__
void Guild::makeInfo( GuildInfo2* pGuildInfo )
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	pGuildInfo->setID( m_ID );
	pGuildInfo->setName( m_Name );
	pGuildInfo->setType( m_Type );
	pGuildInfo->setRace( m_Race );
	pGuildInfo->setState( m_State );
	pGuildInfo->setServerGroupID( m_ServerGroupID );
	pGuildInfo->setZoneID( m_ZoneID );
	pGuildInfo->setMaster( m_Master );
	pGuildInfo->setDate( m_Date );
	pGuildInfo->setIntro( m_Intro );

	HashMapGuildMemberConstItor itr = m_Members.begin();
	for ( ; itr != m_Members.end(); itr++ )
	{
		GuildMemberInfo2* pGuildMemberInfo = new GuildMemberInfo2();
		pGuildMemberInfo->setGuildID( itr->second->getGuildID() );
		pGuildMemberInfo->setName( itr->second->getName() );
		pGuildMemberInfo->setRank( itr->second->getRank() );
		pGuildMemberInfo->setLogOn( itr->second->getLogOn() );

		pGuildInfo->addGuildMemberInfo( pGuildMemberInfo );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}
#endif

void Guild::makeInfo( GuildInfo* pGuildInfo )
	throw()
{
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION( m_Mutex )

	pGuildInfo->setGuildID( m_ID );
	pGuildInfo->setGuildName( m_Name );
	pGuildInfo->setGuildMaster( m_Master );
	pGuildInfo->setGuildMemberCount( m_ActiveMemberCount );

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

void Guild::makeMemberInfo( GCGuildMemberList& gcGuildMemberList )
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapGuildMember& Members = getMembers();
	HashMapGuildMemberConstItor itr = Members.begin();

	for ( ; itr != Members.end(); itr++ )
	{
		GuildMember* pGuildMember = itr->second;

		GuildMemberInfo* pGuildMemberInfo = new GuildMemberInfo();
		pGuildMemberInfo->setName( pGuildMember->getName() );
		pGuildMemberInfo->setRank( pGuildMember->getRank() );
		pGuildMemberInfo->setLogOn( pGuildMember->getLogOn() );
		pGuildMemberInfo->setServerID( pGuildMember->getServerID() );

		gcGuildMemberList.addGuildMemberInfo( pGuildMemberInfo );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}


void Guild::expireTimeOutWaitMember( VSDateTime currentDateTime, list<string>& mList )
	throw(Error)
{
	__BEGIN_TRY

#ifdef __SHARED_SERVER__

	HashMapGuildMemberItor itr = m_Members.begin();

	while ( itr != m_Members.end() )
	{
		GuildMember* pGuildMember = itr->second;

		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT
		  && pGuildMember->isRequestDateTimeOut( currentDateTime ) )
		{
			mList.push_back( pGuildMember->getName() );

			// wait member count 를 줄인다.
			m_WaitMemberCount--;

			pGuildMember->expire();

			SAFE_DELETE( pGuildMember );

			m_Members.erase( itr++ );
		}
		else
		{
			itr++;
		}
	}

#endif

	__END_CATCH
}


string Guild::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << " GuildID = " << m_ID
		<< " GuildName = " << m_Name
		<< " GuildType = " << (int)m_Type
		<< " GuildState = " << (int)m_State
		<< " ServerGroupID = " << (int)m_ServerGroupID
		<< " GuildZoneID = " << (int)m_ZoneID
		<< " Master = " << m_Master
		<< " Date = " << m_Date
		<< endl;

	return msg.toString();

	__END_CATCH
}

string Guild::correctString( const string& str )
	throw()
{
	__BEGIN_TRY

	string correct = str;

	unsigned int i = 0;
	unsigned int size = str.size();

	while( i < size )
	{
		if ( correct[i] == '\\' )
		{
			correct.replace( i, 1, "\\\\" );
			i = i + 2;
			size++;
		}
		else if ( correct[i] == '\'' )
		{
			correct.replace( i, 1, "\\'" );
			i = i + 2;
			size++;
		}
		else 
		{
			i++;
		}
	}

	return correct;

	__END_CATCH
}
