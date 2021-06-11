#include "SMSServiceThread.h"
#include "Properties.h"

#include "Assert.h"
#include "StringStream.h"
#include "Timeval.h"

#include <unistd.h>

#define KEY_SIZE 32

string SMSMessage::toString() const
{
	StringStream msg;

	msg << "SMSMessage("
		<< m_SenderName << ", "
		<< m_ReceiverNumber << ", "
		<< m_CallerNumber << ", "
		<< m_Message << ")";

	return msg.toString();
}

void operator++ (string& id)
{
	cout << "start operator++" << id << endl;

	string::iterator itr = id.end();
	--itr;

	while ( (*itr) == '9' && itr != id.begin() )
	{
		(*itr) = '0';
		--itr;
	}

	Assert( (*itr) <= '8' && (*itr) >= '0' );
	++(*itr);

	cout << "end operator++" << id << endl;
}

void SMSServiceThread::run() 
{
	__BEGIN_TRY

	if ( g_pConfig->getPropertyInt("IsNetMarble") != 0 ) return;

	string host     = g_pConfig->getProperty("SMS_DB_HOST");
	string db       = g_pConfig->getProperty("SMS_DB_DB");
	string user     = g_pConfig->getProperty("SMS_DB_USER");
	string password = g_pConfig->getProperty("SMS_DB_PASSWORD");
	uint port		= 0;
	if ( g_pConfig->hasKey("SMS_DB_PORT") )
		port = g_pConfig->getPropertyInt("SMS_DB_PORT");

	m_pConnection = new Connection( host, db, user, password, port );
	Assert( m_pConnection != NULL );

	uint Dimension	= g_pConfig->getPropertyInt("Dimension");
	uint WorldID	= g_pConfig->getPropertyInt("WorldID");
	uint ServerID	= g_pConfig->getPropertyInt("ServerID");

	Assert( Dimension<10 );
	Assert( WorldID<10 );
	Assert( ServerID<10 );

	string mid;

	{
		char buffer[KEY_SIZE+1];
		buffer[0] = Dimension + '0';
		buffer[1] = WorldID + '0';
		buffer[2] = ServerID + '0';
		for ( int i=3; i<KEY_SIZE; ++i ) buffer[i] = '0';
		buffer[KEY_SIZE] = 0;
		mid = buffer;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = m_pConnection->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT MAX(mid) FROM uds_msg WHERE mid LIKE '%c%c%c%%' AND length(mid)=%d", Dimension+'0', WorldID+'0', ServerID+'0', KEY_SIZE );

		string max;
		if ( pResult->next() ) max = pResult->getString(1);
		if ( max.size() == KEY_SIZE ) mid = max;
		++mid;
		cout << "initial mid : " << mid << endl;;

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt);

	Timeval dummyQueryTime;
	getCurrentTime( dummyQueryTime );
	
	while ( true )
	{
		__ENTER_CRITICAL_SECTION( m_QueueMutex )

		try
		{
			if ( !m_MessageQueue.empty() )
			{
				list<SMSMessage*>::const_iterator itr = m_MessageQueue.begin();
				list<SMSMessage*>::const_iterator endItr = m_MessageQueue.end();

				for ( ; itr != endItr ; ++itr )
				{
					SMSMessage* pMsg = *itr;

					if ( pMsg != NULL )
					{
						Statement* pStmt = NULL;

						BEGIN_DB
						{
							//cout << pMsg->toString() << endl;
							filelog( "SMS.log", "Send message [%s] %s", mid.c_str(), pMsg->toString().c_str() );
							pStmt = m_pConnection->createStatement();
							pStmt->executeQuery( "INSERT INTO uds_msg (mid,recvdate,target,toname,callback,body) VALUES "
									"('%s',now(),'%s','%s','%s','%s')",
									mid.c_str(),
									pMsg->m_ReceiverNumber.c_str(),
									pMsg->m_SenderName.c_str(),
									pMsg->m_CallerNumber.c_str(),
									getDBString(pMsg->m_Message).c_str() );

							if ( pStmt->getAffectedRowCount() != 0 )
							{
								pStmt->executeQuery( "INSERT INTO msg_queue (mid) VALUES ('%s')", mid.c_str() );
								filelog( "SMS.log", "insert queue %s", mid.c_str() );

	//							cout << mid << " message sent!" << endl;
								++mid;
								//mid++;
							}

							SAFE_DELETE( pStmt );
						}
						END_DB(pStmt)
					}
				}

				m_MessageQueue.clear();
			}
		} catch ( SQLQueryException& e )
		{
			filelog( "SMSThreadException.log", "SQLQueryException:%s", e.toString().c_str() );
			SAFE_DELETE( m_pConnection );

			m_pConnection = new Connection( host, db, user, password );
			Assert( m_pConnection != NULL );
		}
		catch ( Throwable& t )
		{
			filelog( "SMSThreadException.log", "Throwable:%s", t.toString().c_str() );
		}

		__LEAVE_CRITICAL_SECTION( m_QueueMutex )

		Timeval currentTime;
		getCurrentTime(currentTime);

		if (dummyQueryTime < currentTime)
		{
			g_pDatabaseManager->executeDummyQuery( m_pConnection );

			// 1시간 ~ 1시간 30분 사이에서 dummy query 시간을 설정한다.
			// timeout이 되지 않게 하기 위해서이다.
			dummyQueryTime.tv_sec += (60+rand()%30) * 60;
		}

		sleep(1); // 1초에 한번씩 큐를 체크한다.
	}

	__END_CATCH
}

string SMSServiceThread::getDBString( const string& msg ) const
{
	string ret = "";

	string::const_iterator itr = msg.begin();
	string::const_iterator endItr = msg.end();

	for ( ; itr != endItr ; ++itr )
	{
		char ch = *itr;

		if ( ch == '\'' || ch=='\\' )
		{
			ret += '\\';
		}

		ret += ch;
	}

	return ret;
}

bool SMSServiceThread::isValidNumber( const string& num ) const
{
	if ( num.size() > 11 || num.size() < 9 ) return false;

	string::const_iterator itr = num.begin();
	string::const_iterator endItr = num.end();

	if ( (*itr) != '0' ) return false;

	itr++;

	if ( (*itr) != '1' ) return false;

	for ( ; itr != endItr ; ++itr )
	{
		if ( (*itr) < '0' || (*itr) > '9' ) return false;
	}

	return true;
}

void SMSServiceThread::pushMessage( SMSMessage* pMsg )
{
	__ENTER_CRITICAL_SECTION( m_QueueMutex )

	m_MessageQueue.push_back( pMsg );

	__LEAVE_CRITICAL_SECTION( m_QueueMutex )
}
