//////////////////////////////////////////////////////////////////////////////
// Filename    : IncomingPlayerManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "IncomingPlayerManager.h"
#include "Assert1.h"
#include "SocketAPI.h"
#include "Socket.h"
#include "Player.h"
#include <algorithm>
#include "Properties.h"
#include "GamePlayer.h"
#include "LoginServerManager.h"
#include "PacketUtil.h"
#include "ZoneInfoManager.h"
#include "ZoneGroup.h"
#include "ZonePlayerManager.h"
#include "DB.h"
//#include "LogClient.h"
#include "PaySystem.h"
#include "MasterLairManager.h"
#include "Encrypter.h"
#include "LogDef.h"
#include "PlayerCreature.h"
#include "PKZoneInfoManager.h"
#include "CreatureUtil.h"

#include "GCUpdateInfo.h"
#include "GLIncomingConnection.h"
#include "GLKickVerify.h"

//#include "UserGateway.h"
#include "SystemAvailabilitiesManager.h"


//////////////////////////////////////////////////////////////////////////////
// constructor
// 하위 매니저 및 데이타 멤버들을 생성한다.
//////////////////////////////////////////////////////////////////////////////

IncomingPlayerManager::IncomingPlayerManager () 
	throw(Error)
: m_pServerSocket(NULL), m_SocketID(INVALID_SOCKET), m_MinFD(-1), m_MaxFD(-1)
{
	__BEGIN_TRY

	m_Mutex.setName("IncomingPlayerManager");
	m_MutexOut.setName("IncomingPlayerManagerOut");
	m_PlayerListQueue.clear();

	try 
	{
		// create  server socket
		while (1) {
			try {
				m_pServerSocket = new ServerSocket(g_pConfig->getPropertyInt("TCPPort"));
				break;
			}
			catch (BindException& b) {
				SAFE_DELETE(m_pServerSocket);
				cout << "[IncomingPlayerManager:" << g_pConfig->getPropertyInt("TCPPort") << "] " << b.toString() << endl;
				sleep(1);
			}
		}

		m_pServerSocket->setNonBlocking();

		// 서버 소켓 디스크립터를 지정한다.
		m_SocketID = m_pServerSocket->getSOCKET();
	} 
	catch (NoSuchElementException & nsee) 
	{
		// 환경 파일에 그런 element가 없을 경우
		throw Error(nsee.toString());
	}

	g_pConnectionInfoManager = new ConnectionInfoManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

IncomingPlayerManager::~IncomingPlayerManager () 
	throw()
{
	__BEGIN_TRY

	SAFE_DELETE(g_pConnectionInfoManager);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 하위 매니저 및 데이터 멤버를 초기화한다.
//////////////////////////////////////////////////////////////////////////////

void IncomingPlayerManager::init ()
	throw(Error)
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
	// ZonePlayerManager에 비해서 길어도 무방하다.....
	m_Timeout[0].tv_sec = 0;
	m_Timeout[0].tv_usec = 0;

	/*
	// connection info manager 를 초기화한다.
	// 원래는 로그인서버로부터 받아야 하지만..
	// 일단 210.220.188.161 ~ 180 까지 등록해둔다.
	char buf[20];
	for (int i = 0 ; i < 20 ; i ++) 
	{
		sprintf(buf,"210.220.188.%d",161+i);
		ConnectionInfo* pConnectionInfo = new ConnectionInfo();
		pConnectionInfo->setClientIP(buf);
		g_pConnectionInfoManager.addConnectionInfo(pConnectionInfo);
	}
	*/
	string dist_host     = g_pConfig->getProperty("UI_DB_HOST");
	string dist_db       = "DARKEDEN";
	string dist_user     = g_pConfig->getProperty("UI_DB_USER");
	string dist_password = g_pConfig->getProperty("UI_DB_PASSWORD");
	uint dist_port		= 0;
	if (g_pConfig->hasKey("UI_DB_PORT") )
		dist_port = g_pConfig->getPropertyInt("UI_DB_PORT");

	Connection* pDistConnection = new Connection(dist_host, dist_db, dist_user, dist_password, dist_port);
    g_pDatabaseManager->addDistConnection((Thread::self()), pDistConnection);

	/*
    // Login DB 의 PCRoomDBInfo Table 읽어서 Connection 만들기
    pStmt = pDistConnection->createStatement();
    Result * pResult = NULL;

    pResult = pStmt->executeQuery("SELECT ID, Host, DB, User, Password FROM PCRoomDBInfo");

    if (pResult->next())
    {
        WorldID_t ID = pResult->getInt(1);
        string host = pResult->getString(2);
        string db = pResult->getString(3);
        string user = pResult->getString(4);
        string password = pResult->getString(5);

        cout << "Connection: "
             << "  ID=" << (int)ID
             << ", HOST=" << host.c_str()
             << ", DB=" << db.c_str()
             << ", User=" << user.c_str() << endl;

        Connection * pConnection = new Connection(host, db, user, password);
        Assert(pConnection!=NULL);

        g_pDatabaseManager->addPCRoomConnection((int)(Thread::self()) , pConnection);
    }
	*/

	// Player.LogOn 를 정리해준다.
    Statement * pStmt = NULL;
	Statement* pStmt2 = NULL;
	BEGIN_DB {
		//pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		//pStmt = g_pDatabaseManager->getDistConnection((int)Thread::self() )->createStatement();
		//pStmt2 = g_pDatabaseManager->getDistConnection((int)Thread::self() )->createStatement();

		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB" )->createStatement();
		pStmt2 = g_pDatabaseManager->getDistConnection("PLAYER_DB" )->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT PlayerID from Player WHERE LogOn='GAME' AND CurrentWorldID=%d AND CurrentServerGroupID=%d", g_pConfig->getPropertyInt("WorldID"), g_pConfig->getPropertyInt("ServerID"));

		// 겜방에서 놀던애들 정리해준다.
		// 빌링~ by sigi 2002.5.31 
		while (pResult->next()) {
			string playerID = pResult->getString(1);

			pStmt2->executeQuery("DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'", playerID.c_str());
		}

		pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGOFF' WHERE LogOn = 'GAME' AND CurrentWorldID=%d AND CurrentServerGroupID=%d", g_pConfig->getPropertyInt("WorldID"), g_pConfig->getPropertyInt("ServerID"));

		/*
		// 두번 하는거 제거. by sigi. 2002.5.9
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM UserIPInfo WHERE ServerID = %d", g_pConfig->getPropertyInt("ServerID"));
		*/
		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt2);
	} END_DB(pStmt)

	BEGIN_DB {
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM UserIPInfo WHERE ServerID = %d", g_pConfig->getPropertyInt("ServerID"));
		SAFE_DELETE(pStmt);
	} END_DB(pStmt)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::copyPlayers()
	    throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	PlayerManager::copyPlayers();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::broadcast (Packet* pPacket)
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) {
		if (i != m_SocketID && m_pPlayers[i] != NULL)
			m_pPlayers[i]->sendPacket(pPacket);
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// call select() system call
// 상위에서 TimeoutException 을 받으면 플레이어는 처리하지 않아도 된다.
//////////////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::select ()
	throw(TimeoutException , InterruptedException , Error)
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
void IncomingPlayerManager::processInputs () 
	throw(IOException , Error)
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
		if (FD_ISSET(i , &m_ReadFDs[1])) 
		{
			if (i == m_SocketID) 
			{
				//  서버 소켓일 경우 새로운 연결이 도착했다는 뜻이다.
				// by sigi. 2002.12.8
				for (int i=0; i<50; i++)	// 50명만 받자 - -;
				{
					if (!acceptNewConnection())
						break;
				}
			} 
			else 
			{
				if (m_pPlayers[i] != NULL) 
				{
					GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
					Assert(pTempPlayer != NULL);
					Assert(m_pPlayers[i] != NULL);

					if (pTempPlayer->getSocket()->getSockError()) 
					{
						FILELOG_INCOMING_CONNECTION("ICMPISocketErr.log", "[Input] PlayerID : %s, PlayerStatus : %d", pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());

						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pTempPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							cerr << t.toString() << endl;
						}


						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_INPUT_ERROR);

						// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
						// 다른 곳에서 deletePlayer를 하는 곳은 없다.
						// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
						// ProcessCommand에서 사라졌다는 말이다.
						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						Creature* pCreature = pTempPlayer->getCreature();
						if (pCreature != NULL )
							pCreature->setValue(1);
						SAFE_DELETE(pTempPlayer);
					} 
					else 
					{
						try 
						{
							pTempPlayer->processInput();
						} 
						catch (ConnectException & ce) 
						{
							FILELOG_INCOMING_CONNECTION("ICMPIConectionErr.log", "[Input] %s, PlayerID : %s, PlayerStatus : %d", ce.toString().c_str(), pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
							// Blocking 소켓이므로, ConnectException과 Error를 제외한 어떤 예외도 발생하지 않는다.
							// 연결이 끊겼을 경우, 로그하고 플레이어 정보를 저장한 후에 (로드되었다면)
							// 플레이어 객체를 삭제한다.
							try 
							{
								pTempPlayer->disconnect();
							} 
							catch (Throwable & t) 
							{
								cerr << t.toString() << endl;
							}

							// by sigi. 2002.12.30
//							UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_INPUT_DISCONNECT);

							// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
							// 다른 곳에서 deletePlayer를 하는 곳은 없다.
							// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
							// ProcessCommand에서 사라졌다는 말이다.
							deletePlayer(i);
							deleteQueuePlayer(pTempPlayer);

							Creature* pCreature = pTempPlayer->getCreature();
							if (pCreature != NULL )
								pCreature->setValue(2);
							SAFE_DELETE(pTempPlayer);
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

void IncomingPlayerManager::processCommands() 
	throw(IOException , Error)
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
		if (i != m_SocketID && m_pPlayers[i] != NULL) 
		{
			GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
			Assert(pTempPlayer != NULL);
			Assert(m_pPlayers[i] != NULL);

			if (pTempPlayer->getSocket()->getSockError()) 
			{
				FILELOG_INCOMING_CONNECTION("ICMPCSocketErr.log", "[Command] PlayerID : %s, PlayerStatus : %d", pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
				try 
				{
					// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
					pTempPlayer->disconnect();
				} 
				catch (Throwable & t) 
				{
					cerr << t.toString() << endl;
				}

				// by sigi. 2002.12.30
//				UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_COMMAND_ERROR);

				// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
				// 다른 곳에서 deletePlayer를 하는 곳은 없다.
				// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
				// ProcessCommand에서 사라졌다는 말이다.
				deletePlayer(i);
				deleteQueuePlayer(pTempPlayer);

				Creature* pCreature = pTempPlayer->getCreature();
				if (pCreature != NULL )
					pCreature->setValue(3);
				try
				{
					SAFE_DELETE(pTempPlayer);
				}
				catch (Throwable& t)
				{
					cerr << t.toString() << endl;
					filelog("Destructor.log", "IncommingPlayerManager.cpp +509 : %s" , t.toString().c_str());
				}
			} 
			else 
			{
				try 
				{
					pTempPlayer->processCommand(false);
				} 
				catch (ProtocolException & pe) 
				{
					try 
					{
						FILELOG_INCOMING_CONNECTION("ICMPCProtocolExcpt.log", "[Command] %s, PlayerID : %s, PlayerStatus : %d", pe.toString().c_str(), pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
						pTempPlayer->disconnect();
					} 
					catch (Throwable & t) 
					{
						cerr << t.toString() << endl;
					}

					// by sigi. 2002.12.30
//					UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_COMMAND_DISCONNECT);

					// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
					// 다른 곳에서 deletePlayer를 하는 곳은 없다.
					// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
					// ProcessCommand에서 사라졌다는 말이다.
					deletePlayer(i);
					deleteQueuePlayer(pTempPlayer);

					Creature* pCreature = pTempPlayer->getCreature();
					if (pCreature != NULL )
						pCreature->setValue(4);
					try
					{
						SAFE_DELETE(pTempPlayer);
					}
					catch (Throwable& t)
					{
						cerr << t.toString() << endl;
						filelog("Destructor.log", "IncommingPlayerManager.cpp +509 : %s" , t.toString().c_str());
					}
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

void IncomingPlayerManager::processOutputs () 
	throw(IOException , Error)
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
			if (i == m_SocketID)
			{
				FILELOG_INCOMING_CONNECTION("ICMFD.txt", "[ i == m_SocketID ] FD : %d, ServerSocket : %d, MinFD : %d, MaxFD : %d, nPlayers : %d:", i, m_SocketID, m_MinFD, m_MaxFD, m_nPlayers);
				throw IOException("server socket's write bit is selected.");	
			}

			if (m_pPlayers[i] != NULL) 
			{
				GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);

				Assert(pTempPlayer != NULL);
				Assert(m_pPlayers[i] != NULL);

				if (pTempPlayer->getSocket()->getSockError()) 
				{
					FILELOG_INCOMING_CONNECTION("ICMPOSocketErr.log", "[Output] PlayerID : %s, PlayerStatus : %d", pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
					try 
					{
						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
						pTempPlayer->disconnect(DISCONNECTED);
					} 
					catch (Throwable & t) 
					{
						cerr << t.toString() << endl;
					}

					// by sigi. 2002.12.30
//					UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_OUTPUT_ERROR);

					// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
					// 다른 곳에서 deletePlayer를 하는 곳은 없다.
					// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
					// ProcessCommand에서 사라졌다는 말이다.
					deletePlayer(i);
					deleteQueuePlayer(pTempPlayer);

					Creature* pCreature = pTempPlayer->getCreature();
					if (pCreature != NULL )
						pCreature->setValue(5);
					SAFE_DELETE(pTempPlayer);
				} 
				else 
				{
					try 
					{
						pTempPlayer->processOutput();
					} 
					catch (ConnectException & ce) 
					{
						FILELOG_INCOMING_CONNECTION("ICMPOConnectExcept.log", "[Output] %s, PlayerID : %s, PlayerStatus : %d", ce.toString().c_str(), pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
						StringStream msg;
						msg << "DISCONNECT " << pTempPlayer->getID() 
							<< "(" << ce.toString() << ")";
						//log(LOG_GAMESERVER_ERROR, "", "", msg.toString());

						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pTempPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							cerr << t.toString() << endl;
						}

						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_OUTPUT_DISCONNECT);

						// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
						// 다른 곳에서 deletePlayer를 하는 곳은 없다.
						// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
						// ProcessCommand에서 사라졌다는 말이다.
						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						Creature* pCreature = pTempPlayer->getCreature();
						if (pCreature != NULL )
							pCreature->setValue(6);
						SAFE_DELETE(pTempPlayer);
					} catch (ProtocolException & cp) {
						FILELOG_INCOMING_CONNECTION("ICMPOProtocolExcept.log", "[Output] %s, PlayerID : %s, PlayerStatus : %d", cp.toString().c_str(), pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
						//StringStream msg;
						//msg << "DISCONNECT " << pTempPlayer->getID() << "(" << cp.toString() << ")";
						//log(LOG_GAMESERVER_ERROR, "", "", cp.toString());

						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.

						try {
							pTempPlayer->disconnect(DISCONNECTED);
						} catch (Throwable & t) {
							cerr << t.toString() << endl;
						}

						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_OUTPUT_DISCONNECT2);

						// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
						// 다른 곳에서 deletePlayer를 하는 곳은 없다.
						// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
						// ProcessCommand에서 사라졌다는 말이다.
						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						Creature* pCreature = pTempPlayer->getCreature();
						if (pCreature != NULL)
							pCreature->setValue(7);
						SAFE_DELETE(pTempPlayer);
					}
				}
			}
			//pTempPlayer->processOutput();
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

void IncomingPlayerManager::processExceptions () 
	throw(IOException , Error)
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
				if (m_pPlayers[i] != NULL) 
				{
					GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
					Assert(pTempPlayer != NULL);
					Assert(i != m_SocketID);
					Assert(m_pPlayers[i] != NULL);
					StringStream msg;
					msg << "OOB from " << pTempPlayer->toString();
					
					FILELOG_INCOMING_CONNECTION("ICMPEOOB.log", "PlayerID : %s, PlayerStatus : %d", pTempPlayer->getID().c_str(), (int)pTempPlayer->getPlayerStatus());
					try 
					{
						pTempPlayer->disconnect();
					} 
					catch (Throwable & t) 
					{
						//cerr << t.toString() << endl;
					} 

					// by sigi. 2002.12.30
//					UserGateway::getInstance()->passUser(UserGateway::USER_OUT_INCOMING_EXCEPTION);

					// 플레이어가 없다는 말은? 다른 곳에서 지워 졌거나,
					// 다른 곳에서 deletePlayer를 하는 곳은 없다.
					// 오로지 각 PlayerManager에서만 Player를 지울 수 있다.
					// ProcessCommand에서 사라졌다는 말이다.
					deletePlayer(i);
					deleteQueuePlayer(pTempPlayer);

					Creature* pCreature = pTempPlayer->getCreature();
					if (pCreature != NULL )
						pCreature->setValue(8);
					SAFE_DELETE(pTempPlayer);
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
bool IncomingPlayerManager::acceptNewConnection ()
	throw(Error)
{
	__BEGIN_TRY

	m_CheckValue = 0;
	
	int fd = -9999;
	int MinFD = (int)m_MinFD;
	int MaxFD = (int)m_MaxFD;

	// 블록킹 방식으로 connection을 기다릴 경우
	// 리턴되는 값은 절대 NULL이 될 수 없다.
	// 또한 NonBlockingIOException도 발생할 수 없다.
	Socket* client = NULL;

	try {
		m_CheckValue = 1;
		client = m_pServerSocket->accept();
		m_CheckValue = 2;
	} catch (Throwable & t ) {
		m_CheckValue += 10000;
	}

	if (client == NULL) 
	{
		m_CheckValue = 50;
		return false;
	}

	try 
	{

		fd = (int)client->getSOCKET();
		FILELOG_INCOMING_CONNECTION("acceptNewConnection.log", "Accept FD : %d (MinFD : %d , MaxFD : %d ) %s", fd, MinFD, MaxFD, client->getHost().c_str());

		if (fd<=0 || fd>=nMaxPlayers)
		{
			FILELOG_INCOMING_CONNECTION("acceptNewConnectionError.log", "Accept FD : %d (MinFD : %d , MaxFD : %d ) %s", fd, MinFD, MaxFD, client->getHost().c_str());

			throw Error();
		}

		// 에러 처리를 위하여 넣어 두었는데 원인을 꼭 밝혀야 한다..
		// 아마도 Thread의 소켓 관리 부분에서 문제가 생기지 않을까 생각 한다
		// Thread 관련 처리를 끝내기 전까지 임시로 들어간다.
		if(client->getSockError() ) 
		{
			m_CheckValue = 4;
			throw Error();
		}

		m_CheckValue = 5;
		client->setNonBlocking();
		m_CheckValue = 6;

		// 에러 처리를 위하여 넣어 두었는데 원인을 꼭 밝혀야 한다..
		// 아마도 Thread의 소켓 관리 부분에서 문제가 생기지 않을까 생각 한다
		// Thread 관련 처리를 끝내기 전까지 임시로 들어간다.
		if(client->getSockError() ) 
		{
			m_CheckValue = 7;
			throw Error();
		}
		// set socket option (!NonBlocking, NoLinger)
		m_CheckValue = 8;
		client->setLinger(0);
		m_CheckValue = 9;

		//StringStream msg;
		//msg << "NEW CONNECTION FROM " << client->getHost() << ":" << client->getPort();
		//log(LOG_GAMESERVER, "", "", msg.toString());
		m_CheckValue = 10;
		
		//----------------------------------------------------------------------
		// Incoming List 에 있는지 인증한다.
		//----------------------------------------------------------------------
		// toString()에서 CI == NULL 이 발생하기도 한다. -_-; 주의 요망..

		// 이 안에서 예외가 발생하면 짜른다.
		g_pConnectionInfoManager->getConnectionInfo(client->getHost());
		m_CheckValue = 11;

		// 클라이언트 소켓을 파라미터로 사용해서 플레이어 객체를 생성한다.
		GamePlayer* pGamePlayer = new GamePlayer(client);
		m_CheckValue = 12;

		// set player status to GPS_BEGIN_SESSION
		pGamePlayer->setPlayerStatus(GPS_BEGIN_SESSION);
		m_CheckValue = 13;
		
		// IPM 에 등록한다.
		//addPlayer_NOBLOCKED(pGamePlayer);
		try 
		{
			m_CheckValue = 14;
			addPlayer(pGamePlayer);
			m_CheckValue = 15;

			// by sigi. 2002.12.30
//			UserGateway::getInstance()->passUser(UserGateway::USER_IN_NORMAL);
		}
		catch (DuplicatedException & de) 
		{
			FILELOG_INCOMING_CONNECTION("ancDupExcept.log", "[Output] %s, FD : %d (MinFD : %d , MaxFD : %d ) %s", de.toString().c_str(), fd, MinFD, MaxFD, client->getHost().c_str());

			m_CheckValue += 1000;
			client->close();
			m_CheckValue += 1000;
			SAFE_DELETE(client);
			m_CheckValue += 1000;
			SAFE_DELETE(pGamePlayer);
			m_CheckValue += 1000;
			//return true;
		}
	} 
	catch (NoSuchElementException&) 
	{
		FILELOG_INCOMING_CONNECTION("ancNoSuch.log", "FD : %d (MinFD : %d , MaxFD : %d ) %s", fd, MinFD, MaxFD, client->getHost().c_str());

		m_CheckValue += 20000;
		m_CheckValue += 1000;
		//StringStream msg2;
		//msg2 << "ILLEGAL ACCESS FROM " << client->getHost() << ":" <<  client->getPort();
		//log(LOG_GAMESERVER, "", "", msg2.toString());

		m_CheckValue += 1000;

		//----------------------------------------acceptNewConnection core!!!
		// 인증되지 못한 연결이므로 짜른다. -_-;
		//client->send("Error : Unauthorized access",27);

		m_CheckValue += 1000;
		client->close();
		m_CheckValue += 1000;
		SAFE_DELETE(client);
		m_CheckValue += 1000;
	}
	catch (Throwable & t)
	{
		FILELOG_INCOMING_CONNECTION("ancThrowable.log", "FD : %d (MinFD : %d , MaxFD : %d ) %s checkValue : %d", fd, MinFD, MaxFD, client->getHost().c_str(), m_CheckValue);
		m_CheckValue += 30000;
		try
		{
			m_CheckValue = 25;
			if(client != NULL ) 
			{
				client->close();
				m_CheckValue = 26;
				SAFE_DELETE(client);
				m_CheckValue = 27;
			}
			m_CheckValue = 28;
		}
		catch (Throwable & t)
		{
			m_CheckValue += 1000;
		}
		catch (...)
		{
			m_CheckValue += 2000;
		}
	}
	catch (exception& e)
	{
		m_CheckValue += 40000;
		FILELOG_INCOMING_CONNECTION("ancException.log", "FD : %d (MinFD : %d , MaxFD : %d ) %s checkValue : %d", fd, MinFD, MaxFD, client->getHost().c_str(), m_CheckValue);
	}
	catch (...)
	{
		m_CheckValue += 50000;
		FILELOG_INCOMING_CONNECTION("ancEtc.log", "FD : %d (MinFD : %d , MaxFD : %d ) %s checkValue : %d", fd, MinFD, MaxFD, client->getHost().c_str(), m_CheckValue);
	}
	m_CheckValue = 33;

	return true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 새로운 연결에 관련된 플레이어 객체를 IPM에 추가한다.
//
//////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::addPlayer (Player* pGamePlayer) 
	throw(DuplicatedException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// call base class's method
	PlayerManager::addPlayer(pGamePlayer);

	SOCKET fd = pGamePlayer->getSocket()->getSOCKET();

	// m_MinFD , m_MaxFD 를 재조정한다.
	m_MinFD = min(fd , m_MinFD);
	m_MaxFD = max(fd , m_MaxFD);

	// 모든 fd_set 에 fd 비트를 on 시킨다.
	// m_XXXFDs[1] 은 다음번에 처리해주면 된다.
	FD_SET(fd , &m_ReadFDs[0]);
	FD_SET(fd , &m_WriteFDs[0]);
	FD_SET(fd , &m_ExceptFDs[0]);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 새로운 연결에 관련된 플레이어 객체를 IPM에 추가한다.
//
//////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::addPlayer_NOBLOCKED (Player* pGamePlayer) 
	throw(DuplicatedException , Error)
{
	__BEGIN_TRY

	// call base class's method
	PlayerManager::addPlayer(pGamePlayer);

	SOCKET fd = pGamePlayer->getSocket()->getSOCKET();

	// m_MinFD , m_MaxFD 를 재조정한다.
	m_MinFD = min(fd , m_MinFD);
	m_MaxFD = max(fd , m_MaxFD);

	// 모든 fd_set 에 fd 비트를 on 시킨다.
	// m_XXXFDs[1] 은 다음번에 처리해주면 된다.
	FD_SET(fd , &m_ReadFDs[0]);
	FD_SET(fd , &m_WriteFDs[0]);
	FD_SET(fd , &m_ExceptFDs[0]);

	__END_CATCH
}

void IncomingPlayerManager::deletePlayer_NOBLOCKED (SOCKET fd) 
	throw(OutOfBoundException , NoSuchElementException , Error)
{
	__BEGIN_TRY

	// call base class's method
	PlayerManager::deletePlayer(fd);

	Assert(m_pPlayers[fd] == NULL);

	// m_MinFD , m_MaxFD 를 재조정한다.
	// fd == m_MinFD && fd == m_MaxFD 인 경우는 첫번째 if 에서 처리된다.
	if (fd == m_MinFD) 
	{
		// 앞에서부터 제일 작은 fd 를 찾는다.
		// m_MinFD 자리는 현재 NULL 이 되어 있음을 유의하라.
		int i = m_MinFD;
		for (i = m_MinFD ; i <= m_MaxFD ; i ++) {
			if (m_pPlayers[i] != NULL || i == m_SocketID) {
				m_MinFD = i;	
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		// 이때에는 m_MinFD == m_MaxFD 인 경우이다.
		// 이때에는 둘 다 -1 로 설정해주자.
		if (i > m_MaxFD)
			m_MinFD = m_MaxFD = -1;
	} 
	else if (fd == m_MaxFD) 
	{
		// 뒤에서부터 가장 큰 fd 를 찾는다.
		// SocketID 에 유의할 것! (SocketID 의 경우 Player 포인터는 NULL 이다.)
		int i = m_MaxFD;
		for (i = m_MaxFD ; i >= m_MinFD ; i --) {
			if (m_pPlayers[i] != NULL || i == m_SocketID) {
				m_MaxFD = i;
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		if (i < m_MinFD) {
			FILELOG_INCOMING_CONNECTION("ICMFD.txt", "[ i < m_MinFD nbl] nPlayers : %d, MinFD : %d, MaxFD : %d, ServerSocket : %d", m_nPlayers, (int)m_MinFD, (int)m_MaxFD, (int)m_SocketID);
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

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 특정 플레이어를 IPM 에서 삭제한다.
//
// 플레이어가 IPM에서 삭제되는 이유는 다음과 같다.
//
//  (1) ZPM으로 객체를 옮김 --> 플레이어 객체를 삭제하면 안된다.
//  (2) 게임에 들어가기 전에 연결이 끊긴다. --> 플레이어 객체를 삭제해야 한다.
//
// 따라서, 플레이어 삭제는 외부에서 이루어져야 한다.
//
//////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::deletePlayer (SOCKET fd) 
	throw(OutOfBoundException , NoSuchElementException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// call base class's method
	PlayerManager::deletePlayer(fd);

	Assert(m_pPlayers[fd] == NULL);

	// m_MinFD , m_MaxFD 를 재조정한다.
	// fd == m_MinFD && fd == m_MaxFD 인 경우는 첫번째 if 에서 처리된다.
	if (fd == m_MinFD) 
	{
		// 앞에서부터 제일 작은 fd 를 찾는다.
		// m_MinFD 자리는 현재 NULL 이 되어 있음을 유의하라.
		int i = m_MinFD;
		for (i = m_MinFD ; i <= m_MaxFD ; i ++) 
		{
			if (m_pPlayers[i] != NULL || i == m_SocketID) 
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
			if (m_pPlayers[i] != NULL || i == m_SocketID) {
				m_MaxFD = i;
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		if (i < m_MinFD) {
			FILELOG_INCOMING_CONNECTION("ICMFD.txt", "[ i < m_MinFD ] nPlayers : %d, MinFD : %d, MaxFD : %d, ServerSocket : %d", m_nPlayers, (int)m_MinFD, (int)m_MaxFD, (int)m_SocketID);
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

GamePlayer* IncomingPlayerManager::getPlayer_NOBLOCKED (const string & id)
    throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	GamePlayer* pGamePlayer = NULL;

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (m_pPlayers[i] != NULL) 
		{
			if (m_pPlayers[i]->getID() == id) 
			{
				pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
				break;
			}
		}
	}

	if (pGamePlayer == NULL) 
		throw NoSuchElementException("Player ID not found.");

	return pGamePlayer;

	__END_CATCH

}

GamePlayer* IncomingPlayerManager::getPlayer (const string & id)
    throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	GamePlayer* pGamePlayer = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	pGamePlayer = getPlayer_NOBLOCKED(id);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return pGamePlayer;

	__END_CATCH
}

GamePlayer* IncomingPlayerManager::getReadyPlayer (const string & id)
    throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	GamePlayer* pGamePlayer = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	list<GamePlayer *>::iterator itr = find_if (m_PlayerListQueue.begin(), m_PlayerListQueue.end(), isSamePlayerbyID(id));

	if (itr == m_PlayerListQueue.end()) 
	{
		throw NoSuchElementException();
	} 
	else 
	{
		pGamePlayer = (*itr);
		Assert(pGamePlayer != NULL);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return pGamePlayer;

	__END_CATCH
}

void IncomingPlayerManager::pushPlayer(GamePlayer* pGamePlayer)
	throw(Error)
{
	__BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_Mutex)

    m_PlayerListQueue.push_back(pGamePlayer);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void IncomingPlayerManager::pushOutPlayer(GamePlayer* pGamePlayer)
	throw(Error)
{
	__BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_MutexOut)

    m_PlayerOutListQueue.push_back(pGamePlayer);

    __LEAVE_CRITICAL_SECTION(m_MutexOut)

	__END_CATCH
}

void IncomingPlayerManager::heartbeat()
	throw(Error) 
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//--------------------------------------------------
	// PlayerQueue의 Player를 메니져에 추가한다.    
	//--------------------------------------------------

	// ZPM에서 IPM으로 들어가는 경우는 Status에 따라서 처리하는 방식이 달라진다.
	// ZPM에서 IPM으로 가는 종류에는 두가지가 있다.
	// 1. 존이동을 할 경우 GPS_WAITING_FOR_CG_READY 상태.
	// 2. 로그아웃을 할 경우 GPS_AFTER_SENDING_GL_INCOMING_CONNECTION
	while(! m_PlayerListQueue.empty())
	{
		GamePlayer* pGamePlayer = m_PlayerListQueue.front();

		if (pGamePlayer == NULL)
		{
			filelog("ZoneBug.txt", "%s : %s", "Zone::heartbeat(1)", "pGamePlayer is NULL.");
			continue;
		}

		m_PlayerListQueue.pop_front();

		//-----------------------------------------------------------------------------
		// * elcastle 's Note
		//-----------------------------------------------------------------------------
		// 넘어오는 과정에서 KICKED 플레그가 걸려 있다는 말은 비정상 종료라는 말이다.
		// 이 경우는 그냥 Disconnect 해주면 되는 것이다.
		// 로그아웃을 하는 경우는 이 단계에서 KICKED가 걸려 있지 않다.
		// LGIncomingConnectionOK 단계에서 KICKED 플레그가 걸려 있으므로 헷갈리지 말자.
		// 정상적인 로그아웃의 경우 이 체크에서 걸리는 것은 정상적이지 못하다.
		// 소켓의 에러, 비정상 적인 종료의 경우 여기서 접속을 끊어 버리게 된다.
		// 여기서 끊고 접속 하고를 다 하는 이유는 소켓의 Using 자원에 대한 커널레벨의
		// 불안정한 지원이 있을지도 모르는 경우를 대비해서 이다.
		// 실제적으로도 불안정한 현상이 나타나고 있다.
		//-----------------------------------------------------------------------------
		if(pGamePlayer->isPenaltyFlag(PENALTY_TYPE_KICKED) ) {
			// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
			int fd = -1;
			Socket* pSocket = pGamePlayer->getSocket();
			if (pSocket!=NULL) fd = (int)pSocket->getSOCKET();

			FILELOG_INCOMING_CONNECTION("incomingDisconnect.log", "FD : %d, %s", fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()));

			// by sigi. 2002.12.30
			if (pGamePlayer->getReconnectPacket()!=NULL)
			{
//				UserGateway::getInstance()->passUser(UserGateway::USER_OUT_NORMAL);
			}
			else
			{
//				UserGateway::getInstance()->passUser(UserGateway::USER_OUT_KICKED);
			}

			try 
			{ 
				pGamePlayer->disconnect(DISCONNECTED);

				// Login을 하기 위해서 기존에 있던 캐릭터를 제거하는 경우이다.
				// 이 때는.. LoginServer로 결과 packet을 보내줘야 한다.
				// by sigi. 2002.5.4
				if (pGamePlayer->isKickForLogin())
				{
					// send GLKickVerify to LoginServer. 2002.5.6
					GLKickVerify glKickVerify;
					glKickVerify.setKicked(true);
					glKickVerify.setID(pGamePlayer->getSocket()->getSOCKET());
					glKickVerify.setPCName(pGamePlayer->getCreature()->getName());

					g_pLoginServerManager->sendPacket(pGamePlayer->getKickRequestHost(), 
														pGamePlayer->getKickRequestPort(), 
														&glKickVerify);
				}
			} catch (Throwable & t) {
				cerr << t.toString() << endl;
			}

			Creature* pCreature = pGamePlayer->getCreature();
			if (pCreature != NULL)
				pCreature->setValue(9);
			SAFE_DELETE(pGamePlayer);

			continue;
		}


		addPlayer_NOBLOCKED(pGamePlayer);

		//filelog("ZoneHeartbeatTrace.txt", "Added Player[%s]", pGamePlayer->getID().c_str());
	
		// 완벽히 Adding을 끝낸 다음 다음과 같은 처리를 해준다. Status에 따라서.
		// ZPM에서 IPM으로 완벽히 넘어온 경우에 그에 따른 패킷을 날린다.

		// 존이동을 하는 경우이다.
		if (pGamePlayer->getPlayerStatus() == GPS_WAITING_FOR_CG_READY) 
		{
			Creature * pCreature = pGamePlayer->getCreature();
			Assert(pCreature != NULL);

			Zone* pOldZone = pCreature->getZone();

			// by sigi. 2002.5.15
			Zone* pZone = pCreature->getNewZone();
			//Assert(pZone != NULL);

			if (pOldZone!=NULL)
			{
				// 마스터 레어에서 플레이어가 나가는 경우
				if (pOldZone->isMasterLair())
				{
					MasterLairManager* pMasterLairManager = pOldZone->getMasterLairManager();
					Assert(pMasterLairManager!=NULL);
					pMasterLairManager->leaveCreature(pCreature);
				}

				// PK 존에서 플레이어가 나가는 경우
				if (pCreature->isPLAYER() && pZone != NULL && pOldZone->getZoneID() != pZone->getZoneID())
				{
					if(g_pPKZoneInfoManager->isPKZone(pOldZone->getZoneID() )) g_pPKZoneInfoManager->leavePKZone(pOldZone->getZoneID());
				}
			}

			if (pZone==NULL)
			{
				pZone = pCreature->getZone();
				Assert(pZone != NULL);
			}
			else
			{
				pCreature->setZone(pZone);
				pCreature->setNewZone(NULL);

				pCreature->setXY(pCreature->getNewX(), pCreature->getNewY());

				// 새 Zone에 들어가게 되는 경우
				pCreature->registerObject();
			}

			// 암호화 코드 등록. 지금은 objectID로 하기 때문에.. by sigi. 2002.11.27
#ifdef __USE_ENCRYPTER__
			pGamePlayer->setEncryptCode();
#endif

			#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
				// 빌링
				// 유료존 --> 무료존으로 갈 경우 30레벨 이하의 종량제는 지불 끝이다.
				if ((pGamePlayer->isPayPlaying() || pGamePlayer->isPremiumPlay() )
					&& pGamePlayer->getPayType() == PAY_TYPE_TIME )
				{
					Assert(pCreature->isPC());
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
					Assert(pPC != NULL);

					if (pPC->canPlayFree() && !pZone->isPayPlay() && !pZone->isPremiumZone() )
						pGamePlayer->logoutPayPlay(pGamePlayer->getID());
				}
			#endif

			// System Availabilities 정보를 보내준다.
			//SEND_SYSTEM_AVAILABILITIES(pGamePlayer);

			//--------------------------------------------------------------------------------
			// GCUpdateInfo 패킷을 만들어 날린다.
			//--------------------------------------------------------------------------------
			GCUpdateInfo gcUpdateInfo;
			
			makeGCUpdateInfo(&gcUpdateInfo, pCreature);
			
			pGamePlayer->sendPacket(&gcUpdateInfo);

		// 로그아웃을 하는 경우이다.
		} else if (pGamePlayer->getPlayerStatus() == GPS_AFTER_SENDING_GL_INCOMING_CONNECTION) {

/*			Creature * pCreature = pGamePlayer->getCreature();

			// PK 존에서 플레이어가 나가는 경우
			if (pCreature != NULL && g_pPKZoneInfoManager->isPKZone(pCreature->getZoneID() ))
			{
				g_pPKZoneInfoManager->leavePKZone(pCreature->getZoneID());
			}
*/
   			// 로그인 서버로 GLIncomingConnection을 보낸다.
			// PlayerName과 ClientIP를 같이 실어서 보낸다.
			GLIncomingConnection glIncomingConnection;
			glIncomingConnection.setPlayerID(pGamePlayer->getID());
			glIncomingConnection.setClientIP(pGamePlayer->getSocket()->getHost());

			static int portNum = g_pConfig->getPropertyInt("LoginServerUDPPortNum");

			int port;
			
			if (portNum > 1)
				port = g_pConfig->getPropertyInt("LoginServerBaseUDPPort") + rand()%portNum;
			else
				port = g_pConfig->getPropertyInt("LoginServerUDPPort");
	
			/*
			if (g_pConfig->getProperty("User") == "excel96")
				g_pLoginServerManager->sendPacket(g_pConfig->getProperty("LoginServerIP") , port, &glIncomingConnection);
			else if (g_pConfig->getProperty("User") == "elcastle")
				g_pLoginServerManager->sendPacket(g_pConfig->getProperty("LoginServerIP") , port, &glIncomingConnection);
			else if (g_pConfig->getProperty("User") == "elca")
				g_pLoginServerManager->sendPacket(g_pConfig->getProperty("LoginServerIP") , port, &glIncomingConnection);
			*/

			// 그냥 보낸다. by sigi. 2002.11.26
			g_pLoginServerManager->sendPacket(g_pConfig->getProperty("LoginServerIP") , port, &glIncomingConnection);
		}
	
		//filelog("ZoneHeartbeatTrace.txt", "After pop front");

	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	// 나갈 대기열에 있는 사람을 처리 해 준다.
	// ZPM으로 가는 사람들을 처리하는 부분이다. 기냥 추가 하면 될 것이다.
	// 어느 존으로 가는지 알아기 위해선 Creatue의 Zone을 참조하므로 미리 Zone을 찾아서 셋팅해 두어야 할 것.

	// by sigi. 2002.12.10
    __ENTER_CRITICAL_SECTION(m_MutexOut)

	while(!m_PlayerOutListQueue.empty()) {

		GamePlayer* pGamePlayer = m_PlayerOutListQueue.front();

		m_PlayerOutListQueue.pop_front();

		Assert(pGamePlayer != NULL);

		Creature * pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		// getNewZone()이 새로 들어갈 Zone이다.	 by sigi. 2002.5.11
		//Zone * pZone = pCreature->getZone();
		//Assert(pZone != NULL);
		Zone * pZone = pCreature->getNewZone();
		//Assert(pZone != NULL);

		// newZone이 설정 안됐으면 기존 존으로.. -_-;
		// load()할때는 NewZone설정을 안한다.
		if (pZone==NULL)
		{
			pZone = pCreature->getZone();
			Assert(pZone != NULL);
		}

		// 들어갈 존의 PlayerManager를 찾는다.
		ZoneGroup * pZoneGroup = pZone->getZoneGroup();
		Assert(pZoneGroup != NULL);
		ZonePlayerManager * pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		Assert(pZonePlayerManager != NULL);

		// Push 한다.
		pZonePlayerManager->pushPlayer(pGamePlayer);


	}

    __LEAVE_CRITICAL_SECTION(m_MutexOut)

	__END_CATCH
}

void IncomingPlayerManager::deleteQueuePlayer(GamePlayer* pGamePlayer)
    throw(NoSuchElementException , Error)
{
	__BEGIN_TRY


	// 필요없는 lock인거 같다.
	// by sigi. 2002.5.9
	// 다른 lock사용. 2002.12.10
	__ENTER_CRITICAL_SECTION(m_MutexOut)

	Assert(pGamePlayer != NULL);

	list<GamePlayer *>::iterator itr = find_if (m_PlayerOutListQueue.begin(), m_PlayerOutListQueue.end(), isSamePlayer(pGamePlayer));

	if (itr != m_PlayerOutListQueue.end()) {

		m_PlayerOutListQueue.erase(itr);

	}

	__LEAVE_CRITICAL_SECTION(m_MutexOut)

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// IncomingPlayerManager 에 있는 모든 사용자를 정리한다.
////////////////////////////////////////////////////////////////////////
void IncomingPlayerManager::clearPlayers()
	throw(Error)
{
	__BEGIN_TRY

	// PlayerListQueue 에 있는 애들을 정리한다.
	while (!m_PlayerListQueue.empty() )
	{
		GamePlayer* pGamePlayer = m_PlayerListQueue.front();

		m_PlayerListQueue.pop_front();

		if (pGamePlayer != NULL )
		{
			try
			{
				pGamePlayer->disconnect();
			}
			catch (Throwable& t )
			{
				// 무시
			}

			SAFE_DELETE(pGamePlayer);
		}
	}

	// PlayerOutListQueue 에 있는 애들을 정리한다.
	while (!m_PlayerOutListQueue.empty() )
	{
		GamePlayer* pGamePlayer = m_PlayerOutListQueue.front();

		m_PlayerOutListQueue.pop_front();

		if (pGamePlayer != NULL )
		{
			try
			{
				pGamePlayer->disconnect();
			}
			catch (Throwable& t )
			{
				// 무시
			}

			SAFE_DELETE(pGamePlayer);
		}
	}


	if (m_MinFD == -1 && m_MaxFD == -1 )
		return;

	// 플레이어를 정리한다.
	for (int i = m_MinFD; i <= m_MaxFD; i++ )
	{
		if (i != m_SocketID && m_pPlayers[i] != NULL )
		{
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);

			if (pGamePlayer != NULL )
			{
				try
				{
					pGamePlayer->disconnect();
				}
				catch (Throwable& t )
				{
					// 무시
				}

				SAFE_DELETE(pGamePlayer);
			}
		}
	}

	__END_CATCH
}


// external variable definition
IncomingPlayerManager* g_pIncomingPlayerManager = NULL;
