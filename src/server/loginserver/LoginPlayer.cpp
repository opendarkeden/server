//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginPlyaer.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

#include "LoginPlayer.h"
#include "Assert1.h"
#include "Packet.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "DB.h"
////#include "LogClient.h"
#include "Profile.h"
#include "PacketProfile.h"
#include "GameServerInfoManager.h"
#include "GameServerManager.h"
#include "gameserver/billing/BillingPlayerManager.h"

#include "LCLoginOK.h"
#include "LCLoginError.h"
#include "LGKickCharacter.h"
#include "LCPCList.h"

// by sigi. 2002.11.12
const int defaultLoginPlayerInputStreamSize = 1024;
const int defaultLoginPlayerOutputStreamSize = 4096;

static int maxIdleSec = 60 * 15;		// 15 분동안 입력을 하지 않으면 자동 접속 종료된당.

// '이미 접속 중'문제를 해결하기 위한.. 시간 체크
static uint maxWaitForKickCharacter = 3;			// GameServer의 응답을 5초간 기다린다.
static uint maxWaitForKickCharacterCount = 3;	// GameServer가 반응이 없으면 3회 응답을 시도한다.


// CLLoginHandler.cpp에 있는 함수다.
void addLoginPlayerData(const string& ID, const string& ip, const string& SSN, const string& zipcode);
void addLogoutPlayerData(Player* pPlayer);


//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
LoginPlayer::LoginPlayer (Socket * pSocket)
	 throw(Error )
: //Player(pSocket),
	m_PlayerStatus(LPS_NONE), m_FailureCount(0)
{
	__BEGIN_TRY

	Assert(pSocket != NULL);
	m_pSocket = pSocket;

	// create socket input stream
	m_pInputStream = new SocketInputStream(m_pSocket, defaultLoginPlayerInputStreamSize);

	Assert(m_pInputStream != NULL);

	// create socket output stream
	m_pOutputStream = new SocketOutputStream(m_pSocket, defaultLoginPlayerOutputStreamSize);
	Assert(m_pOutputStream != NULL);


	m_Mutex.setName("LoginPlayer");

	m_ID = "NONE";

	Assert(m_PacketHistory.empty());

	// 로그인 플레이어가 생성될 때, 현재 시간을 최종 입력 시간으로 간주한다.
	getCurrentTime(m_ExpireTime);
	m_ExpireTime.tv_sec += maxIdleSec;

	m_bSetWorldGroupID = false;
	m_WorldID = 1;
	m_ServerGroupID = 0;
	m_LastSlot = 0;

	m_isAdult = true;

	m_KickCharacterCount = 0;

	m_bFreePass = false;

	m_bAgree = true;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
LoginPlayer::~LoginPlayer ()
	 throw(Error )
{
	__BEGIN_TRY

	// 그 어떤 플레이어 객체가 삭제될 때에도, 그 상태는 로그아웃이어야 한다.
	// 즉 어떤 플레이어를 접속 종료 시키려면, 그 상태를 로그아웃으로 만들어야 한다.
	Assert(m_PlayerStatus == LPS_END_SESSION);

	// delete all previous packets
	while (! m_PacketHistory.empty() ) {
		Packet * pPacket = m_PacketHistory.front();
		delete pPacket;
		m_PacketHistory.pop_front();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// '이미 접속 중'인 경우. 캐릭터의 강제 접속 해제를 위해서
// 대기하는 시간 설정.
//
//////////////////////////////////////////////////////////////////////
void
LoginPlayer::setExpireTimeForKickCharacter()
	throw()
{
	getCurrentTime(m_ExpireTimeForKickCharacter);

	m_ExpireTimeForKickCharacter.tv_sec += maxWaitForKickCharacter;
}

//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void LoginPlayer::processCommand (bool Option )
     throw(IOException , Error )
{
	__BEGIN_TRY

//	static Timeval currentTime;

	// '이미 접속 중'인 경우.. 강제 접속 해제를 시킬려고 할 때.
	if (m_PlayerStatus==LPS_WAITING_FOR_GL_KICK_VERIFY)
	{
		Timeval currentTime;
		getCurrentTime(currentTime);

		// timeout 체크
		if (currentTime >= m_ExpireTimeForKickCharacter)
		{
			// 다시 KickCharcter를 보내본다.
			sendLGKickCharacter();

			// 반응이 없는 경우 여러번 시도를 해본다.
			// 한계에 도달하면.. GameServer가 죽었다고 판단하고 LoginOK를 보낸다.
			if (++ m_KickCharacterCount >= maxWaitForKickCharacterCount)
			{
				sendLCLoginOK();
			}
		}

		return;
	}

	try
	{
		// 헤더를 임시저장할 버퍼 생성
		char header[szPacketHeader];
		PacketID_t packetID;
		PacketSize_t packetSize;
		Packet * pPacket;

		// 입력버퍼에 들어있는 완전한 패킷들을 모조리 처리한다.
		while (true )
		{
			// 입력스트림에서 패킷헤더크기만큼 읽어본다.
			// 만약 지정한 크기만큼 스트림에서 읽을 수 없다면,
			// Insufficient 예외가 발생하고, 루프를 빠져나간다.
			if (!m_pInputStream->peek(header , szPacketHeader ))
			{
				// 입력이 아무 것도 없었다면, 입력제한 시간을 초과했는지 체크한다.
				Timeval currentTime;
				getCurrentTime(currentTime);
				if (currentTime >= m_ExpireTime )
					throw DisconnectException("일정 시간동안 입력하지 않으면 접속이 종료됩니다.");
				break;
			}

			// 패킷아이디 및 패킷크기를 알아낸다.
			// 이때 패킷크기는 헤더를 포함한다.
			memcpy(&packetID   , &header[0] , szPacketID);
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);


            printf("RECV PACKET from %s, %s(%d) %d/%d\n",
				m_ID.c_str(),
				g_pPacketFactoryManager->getPacketName(packetID ).c_str(),
				packetID,
				szPacketHeader + packetSize,
				m_pInputStream->length()
			);

            /*
			StringStream msg;
			msg << "RECV PACKET from " << m_ID << ", "
				<< g_pPacketFactoryManager->getPacketName(packetID ) << "(" << packetID << ") "
				<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << eos;
			cout << msg.toString() << endl;
			*/

			// 패킷 아이디가 이상하면 프로토콜 에러로 간주한다.
			if (packetID >= Packet::PACKET_MAX )
				// 디버깅을 위해서 에러를 구체적으로 표시해둔다.
				throw InvalidProtocolException("too large packet id");

			try
			{
				// 패킷의 순서가 valid 한지 체크한다.
				if (! g_pPacketValidator->isValidPacketID(getPlayerStatus() , packetID ) )
					throw InvalidProtocolException("invalid packet order");

				// 패킷 크기가 너무 크면 프로토콜 에러로 간주한다.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID ) )
					throw InvalidProtocolException("too large packet size");

				// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
				// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
				if (m_pInputStream->length() < szPacketHeader + packetSize )
				//	throw InsufficientDataException();
					break;

				// 최종입력시간을 갱신한다.
				// 최종입력시간은 패킷 하나가 완전하게 도착한 시간을 의미한다.
				getCurrentTime(m_ExpireTime);
				m_ExpireTime.tv_sec += maxIdleSec;

				// 여기까지 왔다면 입력버퍼에는 완전한 패킷 하나 이상이 들어있다는 뜻이다.
				// 패킷팩토리매니저로부터 패킷아이디를 사용해서 패킷 스트럭처를 생성하면 된다.
				// 패킷아이디가 잘못될 경우는 패킷팩토리매니저에서 처리한다.
				pPacket = g_pPacketFactoryManager->createPacket(packetID);

				// 이제 이 패킷스트럭처를 초기화한다.
				// 패킷하위클래스에 정의된 read()가 virtual 메커니즘에 의해서 호출되어
				// 자동적으로 초기화된다.
				m_pInputStream->readPacket(pPacket);

				Timeval start, end;
				getCurrentTime(start);

				// 이제 이 패킷스트럭처를 가지고 패킷핸들러를 수행하면 된다.
				// 패킷아이디가 잘못될 경우는 패킷핸들러매니저에서 처리한다.
				pPacket->execute(this);

				getCurrentTime(end);
				g_PacketProfileManager.addAccuTime(pPacket->getPacketName(), start, end);

				// 현재 패킷을 패킷 히스토리의 맨 뒤에 넣는다.
				m_PacketHistory.push_back(pPacket);

				// 패킷을 nPacketHistory 개만큼만 저장한다.
				while (m_PacketHistory.size() > nPacketHistory ) {
					Packet * oldPacket = m_PacketHistory.front();
					delete oldPacket;
					m_PacketHistory.pop_front();
				}

			}
			catch (IgnorePacketException& )
			{
                // PacketValidator 에서 패킷을 무시하라고 했으니,
                // 입력스트림에서 모두 지워버리고 실행하지 않도록 한다.

                // 패킷 크기가 너무 크면 프로토콜 에러로 간주한다.
                if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
                    throw InvalidProtocolException("too large packet size");

                // 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
                // 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 � 것이다.)
                if (m_pInputStream->length() < szPacketHeader + packetSize )
                    throw InsufficientDataException();

                // 데이타가 모두 도착했으면, 그 크기만큼 무시하고,
                // 다른 패킷을 처리하도록 한다....
                m_pInputStream->skip(szPacketHeader + packetSize);

                // 무시된 패킷은, expire 에 영향을 주지 않게 된다.
                // 즉 유효한 패킷만이 짤리지 않게 해준다.
                // 또한 히스토리에도 들어가지 않는다.

			}
		}

	} catch (InsufficientDataException & ide ) {

		// 입력이 아무 것도 없었다면, 입력제한 시간을 초과했는지 체크한다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime )
			throw DisconnectException("일정 시간동안 입력하지 않으면 접속이 종료됩니다.");

	} catch (InvalidProtocolException & ipe ) {

		// 접속을 강제종료시켜야 한다. 무슨 방법으로??
		throw;

	} catch (DisconnectException & de ) {

		// 패킷 처리에서 발생한 어떤 문제로 연결을 종료해야 한다.
		throw;
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// disconnect player
//--------------------------------------------------------------------------------
void LoginPlayer::disconnect (bool bDisconnected )
	throw(Error )
{
	__BEGIN_TRY

	if (bDisconnected == UNDISCONNECTED )
	{
		// 클라이언트에게 GCDisconnect 패킷을 전송한다.
		//GCDisconnect lcDisconnect;
		//sendPacket(lcDisconnect);

		// 출력 버퍼에 남아있는 데이타를 전송한다.
		m_pOutputStream->flush();
	}

	// 소켓 연결을 닫는다.
	m_pSocket->close();

	// '이미 접속 중'인 경우, 캐릭터 강제 접속 해제를 기다리는 상황.
	if (m_PlayerStatus==LPS_WAITING_FOR_GL_KICK_VERIFY)
	{
		m_ID = "NONE";
	}

	// 플레이어의 상태를 로그아웃으로 만든다.
	Assert(m_PlayerStatus != LPS_END_SESSION);
	m_PlayerStatus = LPS_END_SESSION;

	// 아이디가 설정되었다는 뜻은, 로그인이 이루어졌다는 뜻이다.
	// '이미 접속 중'인 경우에..
	// 캐릭 접속 해제를 기다리는 경우는 ID가 설정될 수 있으므로 아니다
	if (m_ID != "NONE" )
	{
		Statement* pStmt   = NULL;
		//Result*    pResult = NULL;

		try
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		// query해서 안 쓰길래.. 날렸땅.. by sigi. 2002.5.7
		//	pResult = pStmt->executeQuery("SELECT LogOn FROM Player WHERE PlayerID='%s'" , m_ID.c_str());

			// 로그온이어야 한다.
		//	pResult->next();
		//	string logon = pResult->getString(1);
			//cout << "logon = " << logon << endl;
			//Assert(logon == "LOGON");

			// LogOn이 'LOGON'인 경우만 'LOGOFF'로 변경한다. by sigi. 2002.5.15
			// 로그오프로 변경한다.
			pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGOFF' WHERE PlayerID='%s' AND LogOn='LOGON'" , m_ID.c_str());

#if defined(__PAY_SYSTEM_LOGIN__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
			bool bClear 		= false;	// 유료 정보 완전 제거
			bool bDecreaseTime 	= false;	// 사용 시간 감소 - loginserver에서는 무시하자.
			logoutPayPlay(m_ID, bClear, bDecreaseTime);
#endif

			//cout << m_ID << " : LOGOFF" << endl;

			SAFE_DELETE(pStmt);
		}
		catch (SQLQueryException & sqe) {
			filelog("DBError.log", "%s", sqe.toString().c_str());
			SAFE_DELETE(pStmt);
			throw Error(sqe.toString());
		}
	}

	addLogoutPlayerData(this);

	__END_CATCH
}
//--------------------------------------------------------------------------------
// disconnect player no log
// DB 에 로그를 쌓지 않게 한다.
//--------------------------------------------------------------------------------
void LoginPlayer::disconnect_nolog (bool bDisconnected )
	throw(Error )
{
	__BEGIN_TRY

	if (bDisconnected == UNDISCONNECTED )
	{
		// 클라이언트에게 GCDisconnect 패킷을 전송한다.
		//GCDisconnect lcDisconnect;
		//sendPacket(lcDisconnect);

		// 출력 버퍼에 남아있는 데이타를 전송한다.
		m_pOutputStream->flush();
	}

	// 소켓 연결을 닫는다.
	m_pSocket->close();

	// '이미 접속 중'인 경우, 캐릭터 강제 접속 해제를 기다리는 상황.
	if (m_PlayerStatus==LPS_WAITING_FOR_GL_KICK_VERIFY)
		m_ID = "NONE";

	// 플레이어의 상태를 로그아웃으로 만든다.
	Assert(m_PlayerStatus != LPS_END_SESSION);
	m_PlayerStatus = LPS_END_SESSION;

	// 아이디가 설정되었다는 뜻은, 로그인이 이루어졌다는 뜻이다.
	// '이미 접속 중'인 경우에..
	// 캐릭 접속 해제를 기다리는 경우는 ID가 설정될 수 있으므로 아니다
	if (m_ID != "NONE" ) {
		Statement* pStmt   = NULL;
		//Result*    pResult = NULL;

		try {
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		// query해서 안 쓰길래.. 날렸땅.. by sigi. 2002.5.7
		//	pResult = pStmt->executeQuery("SELECT LogOn FROM Player WHERE PlayerID='%s'" , m_ID.c_str());

			// 로그온이어야 한다.
		//	pResult->next();
		//	string logon = pResult->getString(1);
			//cout << "logon = " << logon << endl;
			//Assert(logon == "LOGON");

			// LogOn이 'LOGON'인 경우만 'LOGOFF'로 변경한다. by sigi. 2002.5.15
			// 로그오프로 변경한다.
			pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGOFF' WHERE PlayerID='%s' AND LogOn='LOGON'" , m_ID.c_str());

#if defined(__PAY_SYSTEM_LOGIN__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
			bool bClear 		= false;	// 유료 정보 완전 제거
			bool bDecreaseTime 	= false;	// 사용 시간 감소 - loginserver에서는 무시하자.
			logoutPayPlay(m_ID, bClear, bDecreaseTime);
#endif

			//cout << m_ID << " : LOGOFF" << endl;

			SAFE_DELETE(pStmt);
		}
		catch (SQLQueryException & sqe )
		{
			filelog("DBError.log", "%s", sqe.toString().c_str());
			SAFE_DELETE(pStmt);
			throw Error(sqe.toString());
		}
	}


	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// 원래는 로그인플레이어매니저 외에는 로그인플레이어에 동시에 접속하는
// 쓰레드는 존재하지 않을 계획이었지만, 게임서버매니저가 동시에 쓰레드로
// 돌아가면서 로그인 플레이어에 접근할 가능성이 생겨버렸다. - -; 그래서,
// 아래와 같이 mutex 로 보호되는 버전을 급조했다.
//
//--------------------------------------------------------------------------------
void LoginPlayer::sendPacket (Packet * pPacket )
	throw(ProtocolException , Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//LOG4("SEND PACKET to %s : %s(%d) %d /%d\n", m_ID.c_str() , pPacket->getPacketName().c_str() , pPacket->getPacketID(), pPacket->getPacketSize(), m_pOutputStream->length());
	Player::sendPacket(pPacket);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 최근 N 번째의 패킷을 리턴한다.
//
// N == 0 일 경우, 가장 최근의 패킷을 리턴하게 된다.
//
// 최대 nPacketHistory - 1 까지 지정할 수 있다.
//
//////////////////////////////////////////////////////////////////////
Packet * LoginPlayer::getOldPacket (uint prev )
	throw(OutOfBoundException , NoSuchElementException )
{
	__BEGIN_TRY

	if (prev >= nPacketHistory ) throw OutOfBoundException();
	if (prev >= m_PacketHistory.size() ) throw NoSuchElementException();
	return m_PacketHistory[ m_PacketHistory.size() - prev - 1 ];

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 특정 패킷아이디를 가진 가장 최근의 패킷을 리턴한다.
//
//////////////////////////////////////////////////////////////////////
Packet * LoginPlayer::getOldPacket (PacketID_t packetID )
	throw(NoSuchElementException )
{
	__BEGIN_TRY

	Packet * pPacket = NULL;

	deque<Packet*>::reverse_iterator ritr = m_PacketHistory.rbegin();
	for (; ritr != m_PacketHistory.rend(); ritr++ )
	{
		if ((*ritr)->getPacketID() == packetID )
		{
			pPacket = (*ritr);
			break;
		}
	}

	if (pPacket == NULL ) throw NoSuchElementException();

	return pPacket;

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
//
// send LGKickCharacter
//
// GameServer로 '이미 접속중'인 캐릭터를 제거해달라고 메세지를 보낸다.
//
//////////////////////////////////////////////////////////////////////////////
void
LoginPlayer::sendLGKickCharacter()
	throw()
{
	//cout << "send LGKickCharacter" << endl;

	// Game서버로 캐릭터를 제거해달라는 message를 보낸다.
	LGKickCharacter lgKickCharacter;

	Statement* pStmt = NULL;
	Statement* pStmt1 = NULL;

	string characterName = getLastCharacterName();
	int serverID, serverGroupID, worldID, lastSlot;

	string gameServerIP;
	uint gameServerPort;

	//----------------------------------------------------------------------
	// DB에서 이 player가 최근에 접속한
	// WorldID, ServerID, LastSlot을 얻어내자.
	//----------------------------------------------------------------------
	if (!isSetWorldGroupID())
	{
		BEGIN_DB
		{
			pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			Result * pResult = pStmt1->executeQuery("SELECT CurrentWorldID, CurrentServerGroupID, LastSlot FROM Player where PlayerID='%s'" , getID().c_str());

			if(pResult->next() ) {
				serverID 		= 1;	// 현재는 무조건 1이다.
				worldID 		= pResult->getInt(1);
				serverGroupID 	= pResult->getInt(2);
				lastSlot	 	= pResult->getInt(3);

				setWorldID(worldID);
				setGroupID(serverGroupID);
				setLastSlot(lastSlot);

				setWorldGroupID(true);	// 값이 설정됐다는 의미.
														// 다음에 다시 Query 안 할려고
			}

			SAFE_DELETE(pStmt1);

		}
		END_DB(pStmt1)
	}
	else
	{
		// 기존에 저장된 값을 그대로 쓴다.
		serverID 		= 1;	// 현재는 무조건 1이다.
		worldID 		= getWorldID();
		serverGroupID 	= getGroupID();
	}


	//----------------------------------------------------------------------
	// Slot에 대응되는 캐릭터 이름을 알아낸다.
	//----------------------------------------------------------------------
	if (characterName.size() == 0)
	{
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection(TID(m_WorldID))->createStatement();
			Result * pResult = pStmt->executeQuery("SELECT Name from Slayer where PlayerID='%s' AND Slot='SLOT%d'", getID().c_str(), lastSlot);

			if(pResult->next() ) {
				characterName = pResult->getString(1);

				setLastCharacterName(characterName);
			}
			else
			{
				//cout << "No CharacterName" << endl;
				// LoginError(이미 접속 중)
				LCLoginError lcLoginError;
				lcLoginError.setErrorID(ALREADY_CONNECTED);
				sendPacket(&lcLoginError);
				setPlayerStatus(LPS_BEGIN_SESSION);

				setID("NONE");	// disconnect에서 LOGOFF로 설정되지 않게 하기 위해서

				SAFE_DELETE(pStmt);
				return;
			}

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
	}

	//----------------------------------------------------------------------
	// GameServer의 정보를 알아낸다.
	//
	// 해당 World 에 모든 Server 에 보낸다
	//----------------------------------------------------------------------
	for (int i = 0; i < g_pGameServerInfoManager->getMaxServerGroupID(); i++)
	{
		serverGroupID = i;

		try {
			//cout << "World = " << worldID << ", Group = " << serverGroupID << ", Server = " << serverID << endl;

			GameServerInfo* pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(serverID, serverGroupID, worldID);

			if (pGameServerInfo!=NULL)
			{
				gameServerIP = pGameServerInfo->getIP();
				gameServerPort = pGameServerInfo->getUDPPort();

				//cout << "IP=" << gameServerIP.c_str() << ", Port=" << gameServerPort << endl;
			}
		} catch (NoSuchElementException&) {
			//cout << "No GameServerInfo" << endl;
			// LoginError(이미 접속 중)
	//		LCLoginError lcLoginError;
	//		lcLoginError.setErrorID(ALREADY_CONNECTED);
	//		sendPacket(&lcLoginError);
	//		setPlayerStatus(LPS_BEGIN_SESSION);

			setID("NONE");	// disconnect에서 LOGOFF로 설정되지 않게 하기 위해서

			return;
		}

		lgKickCharacter.setID(getSocket()->getSOCKET());	// SocketFD. 검색을 위해서
		lgKickCharacter.setPCName(characterName);

		//cout << "(" << gameServerIP.c_str() << ", " << gameServerPort << " )" << endl;
		g_pGameServerManager->sendPacket(gameServerIP, gameServerPort, &lgKickCharacter);
	}

	setExpireTimeForKickCharacter();
	setPlayerStatus(LPS_WAITING_FOR_GL_KICK_VERIFY);
}


//////////////////////////////////////////////////////////////////////
//
// send LCLoginOK
//
// Player table의 LogOn을 'LOGON'으로 바꾸고
// client에게 LCLoginOK를 보낸다.
// PlayerStatus는 LPS_WAITING_FOR_CL_GET_PC_LIST로 설정.
//
//////////////////////////////////////////////////////////////////////
void
LoginPlayer::sendLCLoginOK()
	throw()
{
	try {
	//cout << "Send LCLoginOK" << endl;

	Statement* pStmt = NULL;

	string connectIP = getSocket()->getHost();

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGON' WHERE PlayerID = '%s'", getID().c_str());
		if (pStmt->getAffectedRowCount() == 0 )
		{
			filelog("MultiLogin.log", "멀티 로그인 접속 시도로 예상됨 : [%s:%s]", getID().c_str(), connectIP.c_str());
			LCLoginError lcLoginError;
			//lcLoginError.setMessage("already connected");
			lcLoginError.setErrorID(ALREADY_CONNECTED);
			sendPacket(&lcLoginError);

			SAFE_DELETE(pStmt);
			setPlayerStatus(LPS_BEGIN_SESSION);

			return;
		}

		pStmt->executeQuery("UPDATE Player SET LoginIP = '%s' WHERE PlayerID = '%s'",connectIP.c_str(), getID().c_str());

		SAFE_DELETE(pStmt)
	}
	END_DB(pStmt)


	// Player table의 Login을 LOGON으로 바꾼다.
	LCLoginOK lcLoginOK;

	// 이 전에 LoginPlayer에 저장해둔다.
	lcLoginOK.setAdult(isAdult());
	lcLoginOK.setLastDays(0xffff);

	sendPacket(&lcLoginOK);

	setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);

	// 사용자 접속했다고 기록
	addLoginPlayerData(m_ID, connectIP, m_SSN, m_Zipcode);

	} catch (Throwable& t) {
		filelog("loginOKError.txt", "%s", t.toString().c_str());
		throw;
	}
}


bool    LoginPlayer::sendBillingLogin()
	throw(Error)
{
	__BEGIN_TRY

	if (!m_ID.empty() && m_ID!="NONE")
	{
		Timeval currentTime;
		getCurrentTime(currentTime);

		if (currentTime > m_BillingNextLoginRequestTime)
		{
			g_pBillingPlayerManager->sendPayLogin(this);

			// PayLogin 요청한 회수 기억
			m_BillingLoginRequestCount ++;

			// 10초 후 다시 체크한다.
			m_BillingNextLoginRequestTime.tv_sec = currentTime.tv_sec + 10;
		}

		return true;
	}

	return false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string LoginPlayer::toString () const
       throw(Error )
{
	__BEGIN_TRY

	StringStream msg;
	msg << "LoginPlayer("
		<< "ID:" << m_ID
		<< ",SocketID:" << m_pSocket->getSOCKET()
		<< ",Host:" << m_pSocket->getHost()
		<< ")" ;
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//
// add LogoutPlayerdata
//
// 접속자 통계를 위해서
// UserInfo DB의 LogoutPlayerData에 Logout한 사용자를 추가한다.
//
//////////////////////////////////////////////////////////////////////////////
void addLogoutPlayerData(Player* pPlayer)
{

	if(pPlayer->getID() != "NONE")
	{

		Statement* pStmt = NULL;

		pStmt = g_pDatabaseManager->getUserInfoConnection()->createStatement();

		// 유저 통계 관련 정보를 입력한다.
		BEGIN_DB
		{
			string ID = pPlayer->getID();
			string ip = pPlayer->getSocket()->getHost();

			// 먼저 현재 시간을 얻어낸다.
			int year, month, day, hour, minute, second;
			getCurrentTimeEx(year, month, day, hour, minute, second);
			string currentDT = VSDateTime::currentDateTime().toDateTime();

			StringStream sql;
			sql << "INSERT INTO USERINFO.LogoutPlayerData (PlayerID,IP,Date,Time) VALUES ('"
				<< ID << "','" << ip << "','"
				<< currentDT.substr(0, 10 ).c_str() << "','"
				<< currentDT.substr(11 ).c_str() << "')";

			pStmt->executeQuery(sql.toString());

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
	}
}

void LoginPlayer::makePCList(LCPCList& lcPCList )
	throw(DisconnectException )
{
	Statement* pStmt = NULL;
	Statement* pStmt2 = NULL;
	Result* pResult1 = NULL;
	Result* pResult2 = NULL;

	WorldID_t WorldID = getWorldID();

	try {
		pStmt = g_pDatabaseManager->getConnection((TID)WorldID )->createStatement();
		pStmt2 = g_pDatabaseManager->getConnection((TID)WorldID )->createStatement();

		//----------------------------------------------------------------------
		// 우선 슬레이어 테이블을 검색해서, Active 한 슬레이어 정보를 로딩한다.
		// 클라이언트로 전송해야 할 정보는 다음과 같다.
		//
		//    - 이름
		//    - 슬랏번호
		//    - 성별
		//    - 헤어스타일 : 슬레이어 전용
		//    - 머리색
		//    - 피부색
		//    - 입고있는옷정보 : 슬레이어 전용, 머리/상의/하의의 색상정보
		//    - 능력치 : STR,DEX,CON
		//    - HP/MP 의 현재 및 최대 : 뱀파이어는 MP 없음
		//    - 기술과 그 경험치 : 슬레이어전용
		//    - 갖고 있는 돈
		//    - 존의 아이디
		//
		//----------------------------------------------------------------------
		pResult1 = pStmt->executeQuery(
			"SELECT Race, Name, Slot, Sex, HairColor, SkinColor, AdvancementClass, STR, STRExp, DEX, DEXExp, INTE, INTExp, HP, CurrentHP, MP, CurrentMP, Fame, BladeLevel, SwordLevel, GunLevel, HealLevel, EnchantLevel, ETCLevel, Alignment, Shape, HelmetColor, JacketColor, PantsColor, WeaponColor, ShieldColor, Rank FROM Slayer WHERE PlayerID = '%s' AND Active = 'ACTIVE'",
			getID().c_str()
		);

		// 복장 flag. by sigi. 2002.6.18
		DWORD   shape;
		Color_t colors[PCSlayerInfo::SLAYER_COLOR_MAX];
		Color_t colorsVamp[PCVampireInfo::VAMPIRE_COLOR_MAX];

		while (pResult1->next())
		{
			uint i = 0;
			string race = pResult1->getString(++i);
			string name = pResult1->getString(++i);

			if (race == "SLAYER")
			{
				// 슬레이어 PCInfo 객체를 생성한다.
				PCSlayerInfo* pPCSlayerInfo = new PCSlayerInfo();

				// 각 필드값을 지정한다.
				pPCSlayerInfo->setName(name);
				pPCSlayerInfo->setSlot(pResult1->getString(++i));
				pPCSlayerInfo->setSex(pResult1->getString(++i));
				pPCSlayerInfo->setHairStyle(HAIR_STYLE1);
				pPCSlayerInfo->setHairColor(pResult1->getInt(++i));
				pPCSlayerInfo->setSkinColor(pResult1->getInt(++i));
				pPCSlayerInfo->setAdvancementLevel(pResult1->getInt(++i));
				pPCSlayerInfo->setSTR(pResult1->getInt(++i));
				pPCSlayerInfo->setSTRExp(pResult1->getInt(++i));
				pPCSlayerInfo->setDEX(pResult1->getInt(++i));
				pPCSlayerInfo->setDEXExp(pResult1->getInt(++i));
				pPCSlayerInfo->setINT(pResult1->getInt(++i));
				pPCSlayerInfo->setINTExp(pResult1->getInt(++i));
				pPCSlayerInfo->setHP(pResult1->getInt(++i) , pResult1->getInt(++i));
				pPCSlayerInfo->setMP(pResult1->getInt(++i) , pResult1->getInt(++i));
				pPCSlayerInfo->setFame(pResult1->getInt(++i));

				for (int j = 0; j < SKILL_DOMAIN_VAMPIRE; j++ ) {
					pPCSlayerInfo->setSkillDomainLevel((SkillDomain)j, (SkillLevel_t)pResult1->getInt(++i));
				}

				pPCSlayerInfo->setAlignment(pResult1->getInt(++i));

				// 복장 정보를 flag로 대체한다. by sigi. 2002.6.18
				shape = pResult1->getDWORD(++i);

				colors[PCSlayerInfo::SLAYER_COLOR_HAIR] = pPCSlayerInfo->getHairColor();
				colors[PCSlayerInfo::SLAYER_COLOR_SKIN] = pPCSlayerInfo->getSkinColor();
				colors[PCSlayerInfo::SLAYER_COLOR_HELMET] = pResult1->getInt(++i);
				colors[PCSlayerInfo::SLAYER_COLOR_JACKET] = pResult1->getInt(++i);
				colors[PCSlayerInfo::SLAYER_COLOR_PANTS] = pResult1->getInt(++i);
				colors[PCSlayerInfo::SLAYER_COLOR_WEAPON] = pResult1->getInt(++i);
				colors[PCSlayerInfo::SLAYER_COLOR_SHIELD] = pResult1->getInt(++i);

				pPCSlayerInfo->setShapeInfo(shape, colors);

				pPCSlayerInfo->setRank(pResult1->getInt(++i));

				lcPCList.setPCInfo(pPCSlayerInfo->getSlot() , pPCSlayerInfo);
			}
			else if (race == "VAMPIRE" )
			{
				//----------------------------------------------------------------------
				// 이제 뱀파이어 테이블을 검색해서 LCPCList 패킷에 집어넣자..
				// 클라이언트로 전송해야 할 정보는 다음과 같다.
				//
				//    - Name
				//    - Slot
				//    - Sex
				//    - BatColor
				//    - SkinColor
				//    - 상의/하의의 색상정보
				//    - 능력치 : STR,DEX,CON
				//    - CurrentHP/MaxHP
				//    - Gold
				//    - ZoneID
				//
				//----------------------------------------------------------------------

				pResult2 = pStmt2->executeQuery(
					"SELECT Name, Slot, Sex, BatColor, SkinColor, AdvancementClass, STR, DEX, INTE, HP, CurrentHP, Rank, GoalExp, Level, Bonus, Fame, Alignment, Shape, CoatColor FROM Vampire WHERE PlayerID = '%s' AND Active = 'ACTIVE' AND Name='%s'",
					getID().c_str() , name.c_str()
				);

				if (pResult2->getRowCount() == 0)
				{
					throw DisconnectException("No Vampire");
				}

				pResult2->next();

				// 뱀파이어 PCInfo 객체를 생성한다.
				PCVampireInfo* pPCVampireInfo = new PCVampireInfo();

				// 각 필드값을 지정한다.
				uint i = 0;

				pPCVampireInfo->setName(pResult2->getString(++i));
				pPCVampireInfo->setSlot(pResult2->getString(++i));

				string sex = pResult2->getString(++i);
				pPCVampireInfo->setSex(sex);
				pPCVampireInfo->setBatColor(pResult2->getInt(++i));
				pPCVampireInfo->setSkinColor(pResult2->getInt(++i));
				pPCVampireInfo->setAdvancementLevel(pResult2->getInt(++i));
				pPCVampireInfo->setSTR(pResult2->getInt(++i));
				pPCVampireInfo->setDEX(pResult2->getInt(++i));
				pPCVampireInfo->setINT(pResult2->getInt(++i));
				pPCVampireInfo->setHP(pResult2->getInt(++i) , pResult2->getInt(++i));
				pPCVampireInfo->setRank(pResult2->getInt(++i));
				pPCVampireInfo->setExp(pResult2->getInt(++i));
				pPCVampireInfo->setLevel(pResult2->getInt(++i));
				pPCVampireInfo->setBonus(pResult2->getInt(++i));
				pPCVampireInfo->setFame(pResult2->getInt(++i));
				pPCVampireInfo->setAlignment(pResult2->getInt(++i));

				// 복장 정보 읽어오기 최적화. by sigi. 2002.6.19
				shape = pResult2->getDWORD(++i);

				colorsVamp[0] = pResult2->getInt(++i);  // CoatColor
				pPCVampireInfo->setShapeInfo(shape, colorsVamp);

				lcPCList.setPCInfo(pPCVampireInfo->getSlot() , pPCVampireInfo);
			}
			else
			{
				//----------------------------------------------------------------------
				// 이제 아우스터즈 테이블을 검색해서 LCPCList 패킷에 집어넣자..
				// 클라이언트로 전송해야 할 정보는 다음과 같다.
				//
				//    - Name
				//    - Slot
				//    - Sex
				//    - HairColor
				//    - SkinColor
				//    - 상의/하의의 색상정보
				//    - 능력치 : STR,DEX,CON
				//    - CurrentHP/MaxHP
				//    - Gold
				//    - ZoneID
				//
				//----------------------------------------------------------------------

				pResult2 = pStmt2->executeQuery(
					"SELECT Name, Slot, Sex, AdvancementClass, STR, DEX, INTE, HP, CurrentHP, Rank, Exp, Level, Bonus, SkillBonus, Fame, Alignment, CoatType, ArmType, CoatColor, HairColor, ArmColor, BootsColor FROM Ousters WHERE PlayerID = '%s' AND Active = 'ACTIVE' AND Name='%s'",
					getID().c_str() , name.c_str()
				);

				if (pResult2->getRowCount() == 0)
				{
					throw DisconnectException("No Ousters");
				}

				pResult2->next();

				// 아우스터즈 PCInfo 객체를 생성한다.
				PCOustersInfo* pPCOustersInfo = new PCOustersInfo();

				// 각 필드값을 지정한다.
				uint i = 0;

				pPCOustersInfo->setName(pResult2->getString(++i));
				pPCOustersInfo->setSlot(pResult2->getString(++i));

				string sex = pResult2->getString(++i);
				pPCOustersInfo->setSex(sex);
				pPCOustersInfo->setAdvancementLevel(pResult2->getInt(++i));
				pPCOustersInfo->setSTR(pResult2->getInt(++i));
				pPCOustersInfo->setDEX(pResult2->getInt(++i));
				pPCOustersInfo->setINT(pResult2->getInt(++i));
				pPCOustersInfo->setHP(pResult2->getInt(++i) , pResult2->getInt(++i));
				pPCOustersInfo->setRank(pResult2->getInt(++i));
				pPCOustersInfo->setExp(pResult2->getInt(++i));
				pPCOustersInfo->setLevel(pResult2->getInt(++i));
				pPCOustersInfo->setBonus(pResult2->getInt(++i));
				pPCOustersInfo->setSkillBonus(pResult2->getInt(++i));
				pPCOustersInfo->setFame(pResult2->getInt(++i));
				pPCOustersInfo->setAlignment(pResult2->getInt(++i));
				pPCOustersInfo->setCoatType((OustersCoatType)pResult2->getInt(++i));
				pPCOustersInfo->setArmType((OustersArmType)pResult2->getInt(++i));
				pPCOustersInfo->setCoatColor(pResult2->getInt(++i));
				pPCOustersInfo->setHairColor(pResult2->getInt(++i));
				pPCOustersInfo->setArmColor(pResult2->getInt(++i));
				pPCOustersInfo->setBootsColor(pResult2->getInt(++i));

				lcPCList.setPCInfo(pPCOustersInfo->getSlot() , pPCOustersInfo);
			}
		}

		// 쿼리 결과 및 쿼리문 객체를 삭제한다.
		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt2);
	}
	catch (SQLQueryException & sce)
	{
		// 쿼리 결과 및 쿼리문 객체를 삭제한다.
		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt2);

		throw DisconnectException(sce.toString());
	}
}

