//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginServerManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "LoginServerManager.h"
#include "Properties.h"
#include "LogClient.h"
#include "Assert.h"
#include "TimeChecker.h"

#include "ThreadManager.h"
#include "ThreadPool.h"

#include "Datagram.h"
#include "DatagramPacket.h"

#include <unistd.h>
#include "DB.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
LoginServerManager::LoginServerManager () 
	throw (Error)
: m_pDatagramSocket(NULL)
{
	__BEGIN_TRY

	m_Mutex.setName("LoginServerManager");

	// create datagram server socket
	while (true)
	{
		try
		{
			m_pDatagramSocket = new DatagramSocket(g_pConfig->getPropertyInt("GameServerUDPPort") );
			break;
		}
		catch ( BindException& be )
		{
			SAFE_DELETE( m_pDatagramSocket );
			cout << "LoginServerManager(" << g_pConfig->getPropertyInt("GameServerUDPPort") << ") : " << be.toString() << endl;
			sleep(1);
		}
	}

//	m_pDatagramSocket = new DatagramSocket(g_pConfig->getPropertyInt("GameServerUDPPort"));

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
LoginServerManager::~LoginServerManager () 
	throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pDatagramSocket);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// stop thread
//////////////////////////////////////////////////////////////////////
void LoginServerManager::stop () 
	throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// main method
//////////////////////////////////////////////////////////////////////
void LoginServerManager::run () 
	throw ()
{
	try 
	{
		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_DB");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");
		uint port		= 0;
		if ( g_pConfig->hasKey("DB_PORT") )
			port = g_pConfig->getPropertyInt("DB_PORT");

		Connection* pConnection = new Connection(host, db, user, password, port);
		g_pDatabaseManager->addConnection((int)Thread::self(), pConnection);
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
	    cout << "OPEN LOGIN DB" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;

		Timeval dummyQueryTime;
		getCurrentTime( dummyQueryTime );

		while (true) 
		{
	        usleep(100);

			Datagram*       pDatagram       = NULL;
			DatagramPacket* pDatagramPacket = NULL;

			try 
			{
				// 데이터그램 객체를 끄집어낸다.
				pDatagram = m_pDatagramSocket->receive();

				if (pDatagram!=NULL)	// 일부exception제거. by sigi. 2002.5.17
				{
					//cout << "[Datagram] " << pDatagram->getHost() << ":" << pDatagram->getPort() << endl;
					pDatagram->read(pDatagramPacket);

					if (pDatagramPacket!=NULL)
					{
						//cout << "[DatagramPacket] " << pDatagram->getHost() << ":" << pDatagram->getPort() << endl;
						// 끄집어낸 데이터그램 패킷 객체를 실행한다.
						__ENTER_CRITICAL_SECTION(m_Mutex)

						pDatagramPacket->execute(NULL);

						__LEAVE_CRITICAL_SECTION(m_Mutex)

						// 데이터그램 패킷 객체를 삭제한다.
						SAFE_DELETE(pDatagramPacket);
					}
			
					// 데이터그램 객체를 삭제한다.
					SAFE_DELETE(pDatagram);
				}
			} 
			catch (ProtocolException & pe) 
			{
				cerr << "----------------------------------------------------------------------" << endl;
				cerr << "GameServerManager::run Exception Check(ProtocolException)" << endl;
				cerr << pe.toString() << endl;
				cerr << "----------------------------------------------------------------------" << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);

				// 서버간 통신에서 프로토콜 에러가 발생하면, 
				// 프로그래밍 오류이거나 해킹 시도이다.
				// 일단은 전자만이 해당되므로.. 에러로 간주한다.
				//throw Error(pe.toString());

				filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 1 : %s", pe.toString().c_str());
			} 
			catch (ConnectException & ce) 
			{
				cerr << "----------------------------------------------------------------------" << endl;
				cerr << "GameServerManager::run Exception Check(ConnectException)" << endl;
				cerr << ce.toString() << endl;
				cerr << "----------------------------------------------------------------------" << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);

				// 으음.. 머지 이건..
				// 일단 에러당..
				//throw Error(ce.toString());

				filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 2 : %s", ce.toString().c_str());
			} 
			catch (Throwable & t) 
			{
				cerr << "----------------------------------------------------------------------" << endl;
				cerr << "GameServerManager::run Exception Check(Throwable)" << endl;
				cerr << t.toString() << endl;
				cerr << "----------------------------------------------------------------------" << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);

				filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 3 : %s", t.toString().c_str());
			}

			usleep(100);

			Timeval currentTime;
			getCurrentTime(currentTime);

			if (dummyQueryTime < currentTime)
			{
				g_pDatabaseManager->executeDummyQuery( pConnection );

				// 1시간 ~ 1시간 30분 사이에서 dummy query 시간을 설정한다.
				// timeout이 되지 않게 하기 위해서이다.
				dummyQueryTime.tv_sec += (60+rand()%30) * 60;
			}

			// 타임 체커 업데이트
			// ClientManager 에서는 사용자 가 ClientManager 에 들어가지 않을 경우
			// 돌지 않으므로 여기에 추가
			g_pTimeChecker->heartbeat();
		}
	} 
	catch (Throwable & t) 
	{
		filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 4 : %s", t.toString().c_str());

		cerr << t.toString() << endl;
	}
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void LoginServerManager::sendDatagram (Datagram* pDatagram)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY

    m_pDatagramSocket->send(pDatagram);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// send datagram packet to login server
//////////////////////////////////////////////////////////////////////
void LoginServerManager::sendPacket (const string& host , uint port , DatagramPacket* pPacket)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try 
	{
		// 데이터그램 객체를 하나 두고, 전송할 peer 의 호스트와 포트를 지정한다.
		Datagram datagram;

		datagram.setHost(host);
		datagram.setPort(port);

		// 데이터그램 패킷을 데이터그램에 집어넣는다.
		datagram.write(pPacket);

		// 데이터그램 소켓을 통해서 데이터그램을 전송한다.
		m_pDatagramSocket->send(&datagram);
	} 
	catch (Throwable & t) 
	{
        //cerr << "====================================================================" << endl;
		//cerr << t.toString() << endl;
		//cerr << "====================================================================" << endl;
	}

	__END_DEBUG
	__END_CATCH
}

// global variable definition
LoginServerManager* g_pLoginServerManager = NULL;
