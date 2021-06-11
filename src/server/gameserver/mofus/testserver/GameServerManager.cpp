//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServerManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "GameServerManager.h"
#include "Assert.h"
#include "SocketAPI.h"
#include "Socket.h"
#include <algorithm>
#include "Properties.h"
#include "Packet.h"


//////////////////////////////////////////////////////////////////////////////
// constructor
// 하위 매니저 및 데이타 멤버들을 생성한다.
//////////////////////////////////////////////////////////////////////////////

GameServerManager::GameServerManager () 
	throw (Error)
: m_pServerSocket(NULL), m_SocketID(INVALID_SOCKET), m_MinFD(-1), m_MaxFD(-1)
{
	__BEGIN_TRY

	m_Mutex.setName("GameServerManager");

	try 
	{
		// create  server socket
		m_pServerSocket = new ServerSocket(g_pConfig->getPropertyInt("TCPPort"));
		m_pServerSocket->setNonBlocking();

		// 서버 소켓 디스크립터를 지정한다.
		m_SocketID = m_pServerSocket->getSOCKET();
	} 
	catch (NoSuchElementException & nsee) 
	{
		// 환경 파일에 그런 element가 없을 경우
		throw Error(nsee.toString());
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

GameServerManager::~GameServerManager () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 하위 매니저 및 데이터 멤버를 초기화한다.
//////////////////////////////////////////////////////////////////////////////

void GameServerManager::init ()
	throw (Error)
{
	__BEGIN_TRY

	// fd_set 들을 0 으로 초기화한다.
	FD_ZERO(&m_ReadFDs[0]);
	FD_ZERO(&m_WriteFDs[0]);
	FD_ZERO(&m_ExceptFDs[0]);

	//  서버 소켓의 비트를 켠다. (write 는 체크할 필요가 없다.)
	FD_SET(m_SocketID , &m_ReadFDs[0]);
	FD_SET(m_SocketID , &m_ExceptFDs[0]);

	// set min/max fd
	m_MinFD = m_MaxFD = m_SocketID;

	// m_Timeout 을 초기화한다.
	// 나중에는 이 주기 역시 옵션으로 처리하도록 하자.
	m_Timeout[0].tv_sec = 0;
	m_Timeout[0].tv_usec = 0;

	__END_CATCH
}


void GameServerManager::run()
	throw ( Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try {

		while ( true )
		{
			try
			{
				usleep(100);

				select();

				processInputs();
				processCommands();
				processOutputs();
			}
			catch ( Throwable& t )
			{
				filelog( "SSGSManager.txt", "%s", t.toString().c_str() );
			}
		}

	} catch (Throwable& t) {
		filelog("cbillingserverBug.txt", "%s", t.toString().c_str());
		throw;
	}

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// call select() system call
// 상위에서 TimeoutException 을 받으면 플레이어는 처리하지 않아도 된다.
//////////////////////////////////////////////////////////////////////////////
void GameServerManager::select ()
	throw (TimeoutException , InterruptedException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	// m_Timeout[0] 을 m_Timeout[1] 으로 복사한다.
	m_Timeout[1].tv_sec  = m_Timeout[0].tv_sec;
	m_Timeout[1].tv_usec = m_Timeout[0].tv_usec;

	// m_XXXFDs[0] 을 m_XXXFDs[1] 으로 복사한다.
	m_ReadFDs[1]   = m_ReadFDs[0];
	m_WriteFDs[1]  = m_WriteFDs[0];
	m_ExceptFDs[1] = m_ExceptFDs[0];

	try 
	{
		// 이제 m_XXXFDs[1] 을 가지고 select() 를 호출한다.
		SocketAPI::select_ex(m_MaxFD + 1 , &m_ReadFDs[1] , &m_WriteFDs[1] , &m_ExceptFDs[1] , &m_Timeout[1]);
	} 
	catch (InterruptedException & ie) 
	{
		// 시그널이 올 리가 엄찌~~
		//log(LOG_GAMESERVER_ERROR, "", "", ie.toString());
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// process all players' inputs
// 서버 소켓의 read flag가 켜졌을 경우, 새로운 접속이 들어왔으므로
// 이를 처리하고, 다른 소켓의 read flag가 켜졌을 경우, 새로운 패킷이
// 들어왔으므로 그 플레이어의 processInput()을 호출하면 된다.
//////////////////////////////////////////////////////////////////////////////
void GameServerManager::processInputs () 
	throw (IOException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

    if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{ 
		//m_Mutex.unlock();
		return;
	}

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (FD_ISSET(i , &m_ReadFDs[1])) 
		{
			if (i == m_SocketID) 
			{
				//  서버 소켓일 경우 새로운 연결이 도착했다는 뜻이다.
				acceptNewConnection();
			} 
			else 
			{
				if (m_pGameServerPlayers[i] != NULL) 
				{
					GameServerPlayer* pGameServerPlayer = m_pGameServerPlayers[i];
					Assert(pGameServerPlayer != NULL);
					Assert(m_pGameServerPlayers[i] != NULL);

					if (pGameServerPlayer->getSocket()->getSockError()) 
					{
						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pGameServerPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							cerr << t.toString() << endl;
						}

						deleteGameServerPlayer(i);

						delete pGameServerPlayer;
					} 
					else 
					{
						try 
						{
							pGameServerPlayer->processInput();
						} 
						catch (ConnectException & ce) 
						{
							// Blocking 소켓이므로, ConnectException과 Error를 제외한 어떤 예외도 발생하지 않는다.
							// 연결이 끊겼을 경우, 로그하고 플레이어 정보를 저장한 후에 (로드되었다면)
							// 플레이어 객체를 삭제한다.
							try 
							{
								pGameServerPlayer->disconnect();
							} 
							catch (Throwable & t) 
							{
								cerr << t.toString() << endl;
							}

							deleteGameServerPlayer(i);

							delete pGameServerPlayer;
						}
					} // else
				} // else
			} // if
		}
	}

//	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// process all players' commands
//////////////////////////////////////////////////////////////////////////////

void GameServerManager::processCommands() 
	throw (IOException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{ 
		//m_Mutex.unlock();
		return;
	}

	//copyPlayers();

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (i != m_SocketID && m_pGameServerPlayers[i] != NULL) 
		{
			GameServerPlayer* pGameServerPlayer = m_pGameServerPlayers[i];
			Assert(pGameServerPlayer != NULL);
			Assert(m_pGameServerPlayers[i] != NULL);

			if (pGameServerPlayer->getSocket()->getSockError()) 
			{
				try 
				{
					// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
					pGameServerPlayer->disconnect();
				} 
				catch (Throwable & t) 
				{
					cerr << t.toString() << endl;
				}

				deleteGameServerPlayer(i);

				delete pGameServerPlayer;
			} 
			else 
			{
				try 
				{
					pGameServerPlayer->processCommand();
				} 
				catch (ProtocolException & pe) 
				{
					try 
					{
						pGameServerPlayer->disconnect();
						cout << pe.toString().c_str() << endl;
					} 
					catch (Throwable & t) 
					{
						cerr << t.toString() << endl;
					}

					deleteGameServerPlayer(i);

					delete pGameServerPlayer;
				}
			}
		}
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// process all players' outputs
//////////////////////////////////////////////////////////////////////////////

void GameServerManager::processOutputs () 
	throw (IOException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{ 
		//m_Mutex.unlock();
		return;
	}

	//copyPlayers();

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (FD_ISSET(i , &m_WriteFDs[1])) 
		{
			if (i == m_SocketID) throw IOException("server socket's write bit is selected.");

			if (m_pGameServerPlayers[i] != NULL) 
			{
				GameServerPlayer* pGameServerPlayer = m_pGameServerPlayers[i];

				Assert( pGameServerPlayer != NULL );
				Assert(m_pGameServerPlayers[i] != NULL);

				if (pGameServerPlayer->getSocket()->getSockError()) 
				{
					try 
					{
						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
						pGameServerPlayer->disconnect(DISCONNECTED);
					} 
					catch (Throwable & t) 
					{
						cerr << t.toString() << endl;
					}

					GameServerPlayer* pGameServerPlayer = pGameServerPlayer;

					deleteGameServerPlayer(i);

					delete pGameServerPlayer;
				} 
				else 
				{
					try 
					{
						pGameServerPlayer->processOutput();
					} 
					catch (ConnectException & ce) 
					{
						StringStream msg;
						msg << "DISCONNECT " << pGameServerPlayer->getID() 
							<< "(" << ce.toString() << ")";
						//log(LOG_GAMESERVER_ERROR, "", "", msg.toString());

						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pGameServerPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							cerr << t.toString() << endl;
						}

						deleteGameServerPlayer(i);

						delete pGameServerPlayer;
					} 
					catch (ProtocolException & cp) 
					{
						StringStream msg;
						msg << "DISCONNECT " << pGameServerPlayer->getID() 
							<< "(" << cp.toString() << ")";
						//log(LOG_GAMESERVER_ERROR, "", "", cp.toString());

						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.

						try 
						{
							pGameServerPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							cerr << t.toString() << endl;
						}

						deleteGameServerPlayer(i);

						delete pGameServerPlayer;
					}
				}
			}
		}
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// process all players' exceptions
// 현재까지는 OOB 데이타를 전송할 계획은 없다.
// 따라서, 만약 OOB가 켜져 있다면 에러로 간주하고 접속을 확 짤라 버린다.
//////////////////////////////////////////////////////////////////////////////

void GameServerManager::processExceptions () 
	throw (IOException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{ 
		//m_Mutex.unlock();
		return;
	}

	//copyPlayers();

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (FD_ISSET(i , &m_ExceptFDs[1])) 
		{
			if (i != m_SocketID) 
			{
				if (m_pGameServerPlayers[i] != NULL) 
				{
					GameServerPlayer* pGameServerPlayer = m_pGameServerPlayers[i];
					Assert(pGameServerPlayer != NULL );
					Assert(i != m_SocketID);
					Assert(m_pGameServerPlayers[i] != NULL);
					StringStream msg;
					msg << "OOB from " << pGameServerPlayer->toString();

					try 
					{
						pGameServerPlayer->disconnect();
					} 
					catch (Throwable & t) 
					{
						//cerr << t.toString() << endl;
					} 

					deleteGameServerPlayer(i);

					delete pGameServerPlayer;
				}
			} 
			else 
			{
				//cerr << "Exception in Loginserver to Gameserver" << endl;
			}
		}
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////////////
// select 기반에서는 nonblocking 소켓을 사용하지 않는다.
//////////////////////////////////////////////////////////////////////////////
void GameServerManager::acceptNewConnection ()
	throw (Error)
{
	__BEGIN_TRY

	// 블록킹 방식으로 connection을 기다릴 경우
	// 리턴되는 값은 절대 NULL이 될 수 없다.
	// 또한 NonBlockingIOException도 발생할 수 없다.
	Socket* client = NULL;

	cout << "accepted" << endl;

	try {
		client = m_pServerSocket->accept();
	} catch ( Throwable & t ) {
	}

	if (client == NULL) 
	{
		return;
	}

	try 
	{
		// 에러 처리를 위하여 넣어 두었는데 원인을 꼭 밝혀야 한다..
		// 아마도 Thread의 소켓 관리 부분에서 문제가 생기지 않을까 생각 한다
		// Thread 관련 처리를 끝내기 전까지 임시로 들어간다.
		if( client->getSockError() ) throw Error();
		client->setNonBlocking();

		// 에러 처리를 위하여 넣어 두었는데 원인을 꼭 밝혀야 한다..
		// 아마도 Thread의 소켓 관리 부분에서 문제가 생기지 않을까 생각 한다
		// Thread 관련 처리를 끝내기 전까지 임시로 들어간다.
		if( client->getSockError() ) throw Error();
		// set socket option (!NonBlocking, NoLinger)
		client->setLinger(0);

		//StringStream msg;
		//cout << "NEW CONNECTION FROM " << client->getHost() << ":" << client->getPort();

		// 클라이언트 소켓을 파라미터로 사용해서 플레이어 객체를 생성한다.
		GameServerPlayer* pGameServerPlayer = new GameServerPlayer(client);

		// IPM 에 등록한다.
		try 
		{
			addGameServerPlayer(pGameServerPlayer);
		}
		catch ( DuplicatedException& ) 
		{
			client->close();
			SAFE_DELETE(client);
			SAFE_DELETE(pGameServerPlayer);
			return;
		}
	} 
	catch (NoSuchElementException&) 
	{
		StringStream msg2;
		msg2 << "ILLEGAL ACCESS FROM " << client->getHost() << ":" <<  client->getPort();
		//log(LOG_GAMESERVER, "", "", msg2.toString());

		// 인증되지 못한 연결이므로 짜른다. -_-;
		client->send("Error : Unauthorized access",27);
		client->close();
		SAFE_DELETE(client);
	}
	catch (Throwable & t)
	{
		try
		{
			if( client != NULL ) 
			{
//				client->close();
				SAFE_DELETE(client);
			}
		}
		catch (Throwable & t)
		{
		}
		catch (...)
		{
		}
	}
	catch (exception& e)
	{
	}
	catch (...)
	{
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 새로운 연결에 관련된 플레이어 객체를 IPM에 추가한다.
//
//////////////////////////////////////////////////////////////////////
void GameServerManager::addGameServerPlayer(GameServerPlayer* pGameServerPlayer) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	SOCKET fd = pGameServerPlayer->getSocket()->getSOCKET();

	// m_MinFD , m_MaxFD 를 재조정한다.
	m_MinFD = min(fd , m_MinFD);
	m_MaxFD = max(fd , m_MaxFD);

	// 모든 fd_set 에 fd 비트를 on 시킨다.
	// m_XXXFDs[1] 은 다음번에 처리해주면 된다.
	FD_SET(fd , &m_ReadFDs[0]);
	FD_SET(fd , &m_WriteFDs[0]);
	FD_SET(fd , &m_ExceptFDs[0]);

	m_pGameServerPlayers[fd] = pGameServerPlayer;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 특정 플레이어를 IPM 에서 삭제한다.
//
//////////////////////////////////////////////////////////////////////
void GameServerManager::deleteGameServerPlayer(SOCKET fd) 
	throw (OutOfBoundException , NoSuchElementException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_pGameServerPlayers[fd] = NULL;

	// m_MinFD , m_MaxFD 를 재조정한다.
	// fd == m_MinFD && fd == m_MaxFD 인 경우는 첫번째 if 에서 처리된다.
	if (fd == m_MinFD) 
	{
		// 앞에서부터 제일 작은 fd 를 찾는다.
		// m_MinFD 자리는 현재 NULL 이 되어 있음을 유의하라.
		int i = m_MinFD;
		for (i = m_MinFD ; i <= m_MaxFD ; i ++) 
		{
			if (m_pGameServerPlayers[i] != NULL || i == m_SocketID) 
			{
				m_MinFD = i;	
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		// 이때에는 m_MinFD == m_MaxFD 인 경우이다.
		// 이때에는 둘 다 -1 로 설정해주자.
		if (i > m_MaxFD) m_MinFD = m_MaxFD = -1;
	} 
	else if (fd == m_MaxFD) 
	{
		// 뒤에서부터 가장 큰 fd 를 찾는다.
		// SocketID 에 유의할 것! (SocketID 의 경우 Player 포인터는 NULL 이다.)
		int i = m_MaxFD;
		for (i = m_MaxFD ; i >= m_MinFD ; i --) {
			if (m_pGameServerPlayers[i] != NULL || i == m_SocketID) {
				m_MaxFD = i;
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		if (i < m_MinFD) {
			throw UnknownError("m_MinFD & m_MaxFD problem.");
		}
	}

	// 모든 fd_set 에 fd 비트를 off 시킨다.
	// m_XXXFDs[1]도 고쳐야 하는 이유는, 이후 처리에서 객체가 없어졌는데도
	// 처리받을 확률이 있기 때문이다.
	FD_CLR(fd , &m_ReadFDs[0]);
	FD_CLR(fd , &m_ReadFDs[1]);
	FD_CLR(fd , &m_WriteFDs[0]);
	FD_CLR(fd , &m_WriteFDs[1]);
	FD_CLR(fd , &m_ExceptFDs[0]);
	FD_CLR(fd , &m_ExceptFDs[1]);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void GameServerManager::heartbeat()
	throw(Error) 
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	__END_CATCH
}

// external variable definition
GameServerManager* g_pGameServerManager = NULL;
