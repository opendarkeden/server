//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginPlayerManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 클라이언트 매니저
//
//////////////////////////////////////////////////////////////////////

// include files
#include <stdio.h>
#include "LoginPlayerManager.h"
#include "Assert.h"
#include "SocketAPI.h"
#include "Socket.h"
#include "LoginPlayer.h"
#include "LogClient.h"
#include <algorithm>
#include "Properties.h"
#include "ReconnectLoginInfoManager.h"
#include "gameserver/billing/BillingInfo.h"
#include "DB.h"


//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 하위 매니저 객체를 생성하는 곳이다. (그런데, 없다. - -;)
//
//////////////////////////////////////////////////////////////////////
LoginPlayerManager::LoginPlayerManager () 
	throw ( Error )
: m_pServerSocket(NULL), m_ServerFD(INVALID_SOCKET), m_MinFD(-1), m_MaxFD(-1)
{
	__BEGIN_TRY

	m_Mutex.setName("LoginPlayerManager");

	g_pReconnectLoginInfoManager = new ReconnectLoginInfoManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 하위 매니저 객체를 삭제하는 곳이다. (그런데, 없다. - -;)
//
//////////////////////////////////////////////////////////////////////
LoginPlayerManager::~LoginPlayerManager () 
	throw ( Error )
{
	__BEGIN_TRY

	if ( m_pServerSocket != NULL ) {
		m_pServerSocket->close();
		delete m_pServerSocket;
		m_pServerSocket = NULL;
	}

	// base class인 PlayerManager의 destructor에서 접속한 모든 플레이어들의
	// 연결을 끊고, 객체를 삭제하므로 신경쓰지 않아도 된다.
	//
    if ( g_pReconnectLoginInfoManager!= NULL ) {
		delete g_pReconnectLoginInfoManager;
		g_pReconnectLoginInfoManager = NULL;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 하위 매니저 객체를 초기화하고, 자신을 초기화한다.
//
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	// 바인드될때까지 재시도
	while ( 1 )
	{
		try {
			// 서버 소켓을 생성한다.
			m_pServerSocket = new ServerSocket( g_pConfig->getPropertyInt("LoginServerPort") );
			// 정상적으로 바인드되면 나간다.
			break;
		} catch ( BindException & be ) {

			SAFE_DELETE( m_pServerSocket );
			cout << be.toString() << endl;
			usleep(1000);
		}
	}

	// 서버 소켓 디스크립터를 지정한다.
	m_ServerFD = m_pServerSocket->getSOCKET();

	// fd_set 들을 0 으로 초기화한다.
	FD_ZERO( &m_ReadFDs[0] );
	FD_ZERO( &m_WriteFDs[0] );
	FD_ZERO( &m_ExceptFDs[0] );

	// 서버 소켓을 켠다.
	FD_SET( m_ServerFD , &m_ReadFDs[0] );

	// set min/max fd
	m_MaxFD = m_MinFD = m_ServerFD;

	// m_Timeout 을 초기화한다.
	// 나중에는 이 주기 역시 옵션으로 처리하도록 하자.
	// ZonePlayerManager에 비해서 길어도 무방하다.....
	m_Timeout[0].tv_sec = 0;
	m_Timeout[0].tv_usec = 0;

    //--------------------------------------------------------------------------------
    // Player.LogOn 를 정리해준다.
    //--------------------------------------------------------------------------------
    Statement* pStmt = NULL;
    Statement* pStmt2 = NULL;
    try
    {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT PlayerID from Player WHERE LogOn = 'LOGON' AND CurrentLoginServerID=%d", g_pConfig->getPropertyInt("LoginServerID"));

		// 겜방에서 놀던애들 정리해준다.
		// 빌링~ by sigi 2002.5.31
		while (pResult->next())
		{
			string playerID = pResult->getString(1);

			//cout << "delete from PCRoomUserInfo " << playerID.c_str() << endl;

			pStmt2->executeQuery( "DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
										playerID.c_str());

			//cout << "delete ok" << endl;
		}

        pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGOFF' WHERE LogOn = 'LOGON' AND CurrentLoginServerID=%d", g_pConfig->getPropertyInt("LoginServerID"));

        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt2);
    }
    catch ( SQLQueryException & sqe )
    {
        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt2);
        throw Error(sqe.toString());
    }

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// select()를 사용해서 I/O Multiplexing 을 한다.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::select ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// m_Timeout[0] 을 m_Timeout[1] 으로 복사한다.
	m_Timeout[1].tv_sec  = m_Timeout[0].tv_sec;
	m_Timeout[1].tv_usec = m_Timeout[0].tv_usec;

	// m_XXXFDs[0] 을 m_XXXFDs[1] 으로 복사한다.
	m_ReadFDs[1]   = m_ReadFDs[0];
	m_WriteFDs[1]  = m_WriteFDs[0];
	m_ExceptFDs[1] = m_ExceptFDs[0];

	try {

		// 이제 m_XXXFDs[1] 을 가지고 select() 를 호출한다.
		SocketAPI::select_ex( m_MaxFD + 1 , &m_ReadFDs[1] , &m_WriteFDs[1] , &m_ExceptFDs[1] , &m_Timeout[1] );

	} catch ( TimeoutException ) {
		// do nothing
	} catch ( InterruptedException & ie ) 
	{
		// 시그널이 올 리가 엄찌~~
		log(LOG_LOGINSERVER, "", "", ie.toString());
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 혹시모를 OOB 데이타를 처리한다.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processExceptions ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {

		if ( FD_ISSET( i , &m_ExceptFDs[1] ) && i != m_ServerFD ) {

			Assert( m_pPlayers[i] != NULL );

			StringStream msg;
			msg << "OOB from " << m_pPlayers[i]->toString();
			log(LOG_LOGINSERVER_ERROR, "", "", msg.toString());
			cout << msg.toString() << endl;

			// 출력 버퍼를 플러시한다.
			m_pPlayers[i]->disconnect(UNDISCONNECTED);

			// 플레이어 객체를 삭제한다.
			delete m_pPlayers[i];	

			// 플레이어 매니저에서 플레이어를 삭제한다.
			deletePlayer_NOLOCKED( i );		
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 접속한 모든 플레이어들의 입력을 각자의 입력 버퍼에 복사한다.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processInputs ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {

		if ( FD_ISSET( i , &m_ReadFDs[1] ) ) {

			if ( i == m_ServerFD ) {

				// 서버 소켓일 경우, 새로운 접속이 들어왔다는 뜻이다.
				acceptNewConnection();

			} else {

				Assert( m_pPlayers[i] != NULL );

				try {

					if (m_pPlayers[i]->getSocket()->getSockError())
					{
						// 이미 연결이 끊긴 상태이므로, 출력 버퍼를 플러시하지 않아야 한다.
						m_pPlayers[i]->disconnect(DISCONNECTED);

						// 플레이어 객체를 삭제한다.
						delete m_pPlayers[i];	

						// 플레이어 매니저에서 플레이어를 삭제한다.
						deletePlayer_NOLOCKED( i );
					}
					else
					{
						m_pPlayers[i]->processInput();
					}

				} catch ( ConnectException & ce ) {

					// Blocking 소켓이므로 ConnectException 과 Error를 제외한 어떤 예외도 발생하지 않는다.

					cout << ce.toString() << endl;
					log(LOG_LOGINSERVER_ERROR, "", ce.toString());

					// 이미 연결이 끊긴 상태이므로, 출력 버퍼를 플러시하지 않아야 한다.
					m_pPlayers[i]->disconnect(DISCONNECTED);

					// 플레이어 객체를 삭제한다.
					delete m_pPlayers[i];	

					// 플레이어 매니저에서 플레이어를 삭제한다.
					deletePlayer_NOLOCKED( i );

				} 
			}
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 접속한 모든 플레이어들의 입력 패킷을 처리한다.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processCommands ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// m_pPlayers[i] != NULL 의 확률이 i != m_ServerFD 보다 높으므로
	// 이 조건을 앞에다가 둔다. 

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) 
	{
		if ( m_pPlayers[i] != NULL && i != m_ServerFD ) 
		{
			try 
			{

#ifdef __CONNECT_BILLING_SYSTEM__

				//LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(m_pPlayers[i]);

				// 아직 빌링 시스템에서 검증되지 않았다면..
				// 한번만 보내고 게기는 걸로 수정. 애드빌(박정수) 요청. by bezz. 2003.04.21
				//if (!pLoginPlayer->isBillingLoginVerified())
				//{
					//pLoginPlayer->sendBillingLogin();
				//}
#endif

				m_pPlayers[i]->processCommand();
			} 
			catch ( ProtocolException & pe ) 
			{
				//--------------------------------------------------
				// ProtocolException의 종류에는 3 가지가 있다.
				//
				// - InvalidProtocolException : 프로토콜 에러
				// - DisconnectException : 연결을 종료시킴
				// - InsufficiendDataException : 패킷이 부분적으로만 도착했음
				//
				// 이 모두 클라이언트와의 연결이 지속되어 있는 상태
				// 이므로, disconnect시 UNDISCONNECTED 파라미터를 사용해서 
				// 출력 버퍼를 플러시해줘야 한다. 
				//
				//--------------------------------------------------
			
				cout << pe.toString() << endl;
				log(LOG_LOGINSERVER_ERROR, "", "", pe.toString());

				m_pPlayers[i]->disconnect(UNDISCONNECTED);

				// 플레이어 객체를 삭제한다.
				delete m_pPlayers[i];

				// 플레이어 매니저에서 플레이어를 삭제한다.
				deletePlayer_NOLOCKED(i);
			}
			// 김성민에 의해 추가...
			catch (ConnectException &ce)
			{
				cout << ce.toString() << endl;
				log(LOG_LOGINSERVER_ERROR, "", "", ce.toString());

				m_pPlayers[i]->disconnect(DISCONNECTED);

				// 플레이어 객체를 삭제한다.
				delete m_pPlayers[i];

				// 플레이어 매니저에서 플레이어를 삭제한다.
				deletePlayer_NOLOCKED(i);
			}
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 접속한 모든 플레이어들의 출력을 클라이언트로 전송한다.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processOutputs ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {

		if ( FD_ISSET( i , &m_WriteFDs[1] ) && i != m_ServerFD ) {

			Assert( m_pPlayers[i] != NULL );

			try {

				m_pPlayers[i]->processOutput();

			} catch ( ConnectException & ce ) {	

				cout << ce.toString() << endl;
				log(LOG_LOGINSERVER_ERROR, "", "", ce.toString());

				// 이미 연결이 끊긴 상태이므로, 출력 버퍼를 플러시하지 않아야 한다.
				m_pPlayers[i]->disconnect(DISCONNECTED);

				// 플레이어 객체를 삭제한다.
				delete m_pPlayers[i];	

				// 플레이어 매니저에서 플레이어를 삭제한다.
				deletePlayer_NOLOCKED( i );

			} catch ( ProtocolException & pe ) {
				cout << pe.toString() << endl;
				log(LOG_LOGINSERVER_ERROR, "", "", pe.toString());

				// 이미 연결이 끊긴 상태이므로, 출력 버퍼를 플러시하지 않아야 한다.
				m_pPlayers[i]->disconnect(DISCONNECTED);

				// 플레이어 객체를 삭제한다.
				delete m_pPlayers[i];	

				// 플레이어 매니저에서 플레이어를 삭제한다.
				deletePlayer_NOLOCKED( i );
			}

		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
//
// accept new connection
//
// select 기반에서는 nonblocking 소켓을 사용하지 않는다.
//
// 로그인 서버는 기본적으로 모든 연결시도를 받아들인다. 
// 단 BAN DB에 등록된 IP로부터의 연결은 받아들이지 않는다.
//
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::acceptNewConnection ()
	throw ( Error )
{
	__BEGIN_TRY

	// 블록킹 방식으로 connection을 기다릴 경우
	// 리턴되는 값은 절대 NULL이 될 수 없다.
	// 또한 NonBlockingIOException도 발생할 수 없다.
	Socket * client = NULL;
	
	try {
		client = m_pServerSocket->accept();
	} catch (Throwable& t) {
	}
		
	// ConnectException 이 발생할 가능성이 있다. (실제로 발생했다.)	
	// 현재 내부에서 CE 가 발새할 경우, NULL 을 리턴하기 때문에..
	// NULL 을 체크해서, 무시해줘야 한다.
	if ( client == NULL )
		return;
		

	if (client->getSockError())
	{
		delete client;
		return;
	}

	client->setNonBlocking();

	if (client->getSockError())
	{
		delete client;
		return;
	}

	StringStream msg;
	msg << "NEW CONNECTION FROM [" << client->getHost().c_str() << ":" << client->getPort() << "]";
	log(LOG_LOGINSERVER, "", "", msg.toString());
	//cout << "NEW CONNECTION FROM " << client->getHost() << ":" << client->getPort() << endl;

	//--------------------------------------------------
	// BAN DB에 쿼리해서 현재 IP가 올바른지 확인해본다.
	//--------------------------------------------------
	/*
	if ( g_pBanManager->isBanned( client->getHost() ) ) {
		client->send("You are banned. Bye~\n",23);
		client->close();
		delete client;
	}

	*/

	// set socket option ( !NonBlocking, NoLinger )
	client->setLinger(0);
		
	// 클라이언트 소켓을 파라미터로 사용해서 플레이어 객체를 생성한다.
	LoginPlayer * pPlayer = new LoginPlayer( client );

	// set player status to PLAYER_LOGON
	Assert( pPlayer->getPlayerStatus() == LPS_NONE );
	pPlayer->setPlayerStatus( LPS_BEGIN_SESSION );
		
	// LoginPlayerManager에 등록한다.
	addPlayer_NOLOCKED(pPlayer);
				
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 특정 플레이어를 매니저에 추가한다.
//
// 로그인 서버에서는 플레이어 배열에 대해서 따로 쓰레드가 돌지 않으므로
// locking 을 할 필요가 없다.
//
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::addPlayer_NOLOCKED ( Player * pPlayer ) 
	throw ( DuplicatedException , Error )
{
	__BEGIN_TRY

	PlayerManager::addPlayer(pPlayer);

	SOCKET fd = pPlayer->getSocket()->getSOCKET();

	// m_MinFD , m_MaxFD 를 재조정한다.
	m_MinFD = min( fd , m_MinFD );
	m_MaxFD = max( fd , m_MaxFD );

	// 모든 fd_set 에 fd 비트를 on 시킨다.
	// m_XXXFDs[1] 은 다음번에 처리해주면 된다.
	FD_SET( fd , &m_ReadFDs[0] );
	FD_SET( fd , &m_WriteFDs[0] );
	FD_SET( fd , &m_ExceptFDs[0] );

	__END_CATCH
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void LoginPlayerManager::addPlayer ( Player * pPlayer ) 
	throw ( DuplicatedException , Error )
{
	__ENTER_CRITICAL_SECTION(m_Mutex)

		addPlayer_NOLOCKED(pPlayer);

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}


//--------------------------------------------------------------------------------
//
// 특정 플레이어를 매니저에서 삭제한다.
//
// 로그인 서버에서는 플레이어 배열에 대해서 따로 쓰레드가 돌지 않으므로
// locking 을 할 필요가 없다.
//
//--------------------------------------------------------------------------------
void LoginPlayerManager::deletePlayer_NOLOCKED ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__BEGIN_TRY

	PlayerManager::deletePlayer(fd);

	Assert( m_pPlayers[fd] == NULL );

	// m_MinFD , m_MaxFD 를 재조정한다.
	// fd == m_MinFD && fd == m_MaxFD 인 경우는 첫번째 if 에서 처리된다.
	if ( fd == m_MinFD ) {

		// 앞에서부터 제일 작은 fd 를 찾는다.
		// m_MinFD 자리는 현재 NULL 이 되어 있음을 유의하라.
		int i = m_MinFD;
		for ( ; i <= m_MaxFD ; i ++ ) {
			if ( m_pPlayers[i] != NULL || i == m_ServerFD ) {
				m_MinFD = i;	
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		// 이때에는 m_MinFD == m_MaxFD 인 경우이다.
		// 이때에는 둘 다 -1 로 설정해주자.
		if ( i > m_MaxFD )
			m_MinFD = m_MaxFD = -1;

	} else if ( fd == m_MaxFD ) {

		// 뒤에서부터 가장 큰 fd 를 찾는다.
		// ServerFD 에 유의할 것! ( ServerFD 의 경우 Player 포인터는 NULL 이다. )
		int i = m_MaxFD;
		for ( ; i >= m_MinFD ; i -- ) {
			if ( m_pPlayers[i] != NULL || i == m_ServerFD ) {
				m_MaxFD = i;
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		if ( i < m_MinFD ) {
			throw UnknownError("m_MinFD & m_MaxFD problem.");
		}
	}

	// 모든 fd_set 에 fd 비트를 off 시킨다.
	// m_XXXFDs[1]도 고쳐야 하는 이유는, 이후 처리에서 객체가 없어졌는데도
	// 처리받을 확률이 있기 때문이다.
	FD_CLR( fd , &m_ReadFDs[0] );
	FD_CLR( fd , &m_ReadFDs[1] );
	FD_CLR( fd , &m_WriteFDs[0] );
	FD_CLR( fd , &m_WriteFDs[1] );
	FD_CLR( fd , &m_ExceptFDs[0] );
	FD_CLR( fd , &m_ExceptFDs[1] );

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void LoginPlayerManager::deletePlayer ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__ENTER_CRITICAL_SECTION(m_Mutex)

		deletePlayer_NOLOCKED(fd);

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}


//----------------------------------------------------------------------
// 로그인 서버에 접속한 특정 플레이어를 검색한다.
//----------------------------------------------------------------------
LoginPlayer * LoginPlayerManager::getPlayer_NOLOCKED ( const string & id ) const
	throw ( NoSuchElementException , Error )
{
	__BEGIN_TRY

	LoginPlayer * pLoginPlayer = NULL;

	//cout << "m_MinFD : " << m_MinFD << endl;
	//cout << "m_MaxFD : " << m_MaxFD << endl;

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) 
	{
		if ( m_pPlayers[i] != NULL ) 
		{
			//cout << "[" << i << "] : " << m_pPlayers[i]->toString() << endl;
			//cout << "[" << i << "] : " << m_pPlayers[i]->getID().c_str() << endl;

			if ( m_pPlayers[i]->getID() == id ) 
			{
				pLoginPlayer = dynamic_cast<LoginPlayer*>(m_pPlayers[i]);
				//cout << "Found OK" << endl;
				break;
			}
		}
	}

	if ( pLoginPlayer == NULL ) throw NoSuchElementException("그런 아이디를 가진 플레이어는 존재하지 않습니다.");

	return pLoginPlayer;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
LoginPlayer * LoginPlayerManager::getPlayer ( const string & id ) const
	throw ( NoSuchElementException , Error )
{

	LoginPlayer * pPlayer;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	pPlayer = getPlayer_NOLOCKED(id);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return pPlayer;
}


//--------------------------------------------------------------------------------
// 로그인 서버에 접속한 모든 플레이어들에게 특정 패킷을 전송한다.
//--------------------------------------------------------------------------------
void LoginPlayerManager::broadcastPacket ( Packet * pPacket )
	throw ( Error )
{
	__BEGIN_TRY

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {
		if ( m_pPlayers[i] != NULL ) {
			m_pPlayers[i]->sendPacket(pPacket);
		}
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// 로그인 서버에 접속한 특정 플레이어에게 특정 패킷을 보낸다.
//--------------------------------------------------------------------------------
void LoginPlayerManager::sendPacket ( const string & id , Packet * pPacket )
	throw ( Error )
{
	__BEGIN_TRY

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) 
	{
		if ( m_pPlayers[i] != NULL ) 
		{
			//cout << "[" << i << "] ID : " << m_pPlayers[i]->getID() << endl;
			if ( m_pPlayers[i]->getID() == id ) 
			{
				m_pPlayers[i]->sendPacket(pPacket);
				break;
			}
		}
	}

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string LoginPlayerManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "LoginPlayerManager(nPlayers:" << size() << ")";
	return msg.toString();

	__END_CATCH
}



// global variable definition
LoginPlayerManager * g_pLoginPlayerManager = NULL;
