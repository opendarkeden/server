//////////////////////////////////////////////////////////////////////////////
// Filename    : GamePlyaer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GamePlayer.h"
#include "Assert1.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
//#include "LogClient.h"
#include "Zone.h"
#include "RelicUtil.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "IncomingPlayerManager.h"
#include "PCFinder.h"
#include "TelephoneCenter.h"
#include "DB.h"
#include "VSDateTime.h"
#include "Thread.h"
#include "GuildManager.h"
#include "Guild.h"
#include "VariableManager.h"
#include "SharedServerManager.h"
#include "BillingInfo.h"
#include "BillingPlayerManager.h"
#include <fstream>
#include "Properties.h"
#include "EventKick.h"
#include "StringPool.h"

#include "CGConnect.h"
#include "GSGuildMemberLogOn.h"
#include "GCKickMessage.h"
#include "GCSystemMessage.h"

#include "ServiceDeadline.h"

#include "chinabilling/CBillingInfo.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
	#include "chinabilling/CBillingPlayerManager.h"
#endif

#include "zlog.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////
// 모든 packet들에 대해서 profiling한다. by sigi. 2002.5.6
//
// 단, 이걸 사용하기 위해서는 
// Profile.h에 MAX_PROFILE_SAMPLES += 300을 해줘야 한다.
//////////////////////////////////////////////////////////////////////////////
//#define __PROFILE_PACKETS__

#ifdef __PROFILE_PACKETS__
	#include "Profile.h"
#endif

// by sigi. 2002.11.12
const int defaultGamePlayerInputStreamSize = 1024;
const int defaultGamePlayerOutputStreamSize = 20480;

static int maxIdleSec         = 60* 5;		// 5분
//static int maxSpeedVerifyTime = 2;  		// 0.3 초
static int maxVerifyCount     = 3;      	// 3 번.
static int maxTimeGap         =	5;			// 5초
static int SpeedCheckDelay    = 60;			// 1분

const int PCRoomLottoSec = 3600;			// 3600 초. 1시간
const int PCRoomLottoMaxAmount = 3;			// 한번에 쌓일 수 있는 최대 복권수
// CLLoginHandler.cpp에 있는 함수다.
void addLogoutPlayerData(Player* pPlayer);


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GamePlayer::GamePlayer (Socket* pSocket)
	 throw(Error)
: //Player(pSocket), 	// by sigi. 2002.11.12
	m_pCreature(NULL), m_PlayerStatus(GPS_NONE), m_pReconnectPacket(NULL)
{
	__BEGIN_TRY

	Assert(pSocket != NULL);
	m_pSocket = pSocket;

#ifdef __USE_ENCRYPTER__
	// create socket input stream
	m_pInputStream = new SocketEncryptInputStream(m_pSocket, defaultGamePlayerInputStreamSize);
	Assert(m_pInputStream != NULL);
	
	// create socket output stream
	m_pOutputStream = new SocketEncryptOutputStream(m_pSocket, defaultGamePlayerOutputStreamSize);
	Assert(m_pOutputStream != NULL);
#else
	// create socket input stream
	m_pInputStream = new SockettInputStream(m_pSocket, defaultGamePlayerInputStreamSize);
	Assert(m_pInputStream != NULL);
	
	// create socket output stream
	m_pOutputStream = new SockettOutputStream(m_pSocket, defaultGamePlayerOutputStreamSize);
	Assert(m_pOutputStream != NULL);
#endif

	m_Mutex.setName("GamePlayer");
		
	getCurrentTime(m_ExpireTime);
	m_ExpireTime.tv_sec += maxIdleSec;

    // 현재 시간을 받아온다
	//getCurrentTime(m_SpeedVerify);
	m_SpeedVerify.tv_sec = 0;;
	m_SpeedVerify.tv_usec = 0;;
	getCurrentTime(m_MoveSpeedVerify);
	getCurrentTime(m_AttackSpeedVerify);

	m_VerifyCount = 0;
	
	m_SpecialEventCount = 0;

	m_bKickForLogin = false;
	
	m_bFreePass = false;

	m_bMetroFreePlayer = false;

//	if (m_bPCRoomPlay )
//		m_ItemRatioBonusPoint = g_pVariableManager->getPCRoomItemRatioBonusPercent();
//	else
		m_ItemRatioBonusPoint = 0;

	m_PCRoomLottoStartTime.tv_sec = 0;
	m_PCRoomLottoStartTime.tv_usec = 0;
	m_PCRoomLottoSumTime = 0;

	m_bPacketLog = false;

	// 객체가 생성된 시점을 로그인한 시간으로 본다.
	m_LoginDateTime = VSDateTime::currentDateTime();

#ifdef	__THAILAND_SERVER__
	m_bPermission = false;
#endif
	
//	m_NProtectCSAuth.Init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

GamePlayer::~GamePlayer ()
	 throw(Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	// 그 어떤 플레이어 객체가 삭제될 때에도, 그 상태는 로그아웃이어야 한다.
	// 즉 어떤 플레이어를 접속 종료 시키려면, 그 상태를 로그아웃으로 만들어야 한다.
	Assert(m_PlayerStatus == GPS_END_SESSION);

	try
	{
		// Delete creature
		if (m_pCreature != NULL) 
		{
			// 성서 떨어뜨리기
			if (m_pCreature->hasRelicItem() )
			{
				dropRelicToZone(m_pCreature, false);
			}

			dropFlagToZone(m_pCreature, false);
			dropSweeperToZone(m_pCreature);

			//try 
			//{
				// NoSuch제거. by sigi. 2002.5.2
				g_pPCFinder->deleteCreature(m_pCreature->getName());
			//} 
			//catch (NoSuchElementException & t) 
			//{
			//}

		#ifdef __CONNECT_BILLING_SYSTEM__
			// Pay 종료한다고 알려준다. by sigi. 2002.11.18
			if (isBillingPlayAvaiable() && !m_bMetroFreePlayer )	// by sigi. 2002.11.23
			{
				g_pBillingPlayerManager->sendPayLogout(this);
			}
		#elif defined(__CONNECT_CBILLING_SYSTEM__ )
			// 중국 빌링 서버에 logout 패킷을 보낸다.
			g_pCBillingPlayerManager->sendLogout(this);
		#endif

			Statement* pStmt = NULL;

			// 길드 현재 접속 멤버 리스트에서 삭제한다.
			if (m_pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
				if (pSlayer->getGuildID() != 99 )
				{
					Guild* pGuild = g_pGuildManager->getGuild(pSlayer->getGuildID());
					if (pGuild != NULL )
					{
						pGuild->deleteCurrentMember(pSlayer->getName());

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID(pGuild->getID());
						gsGuildMemberLogOn.setName(pSlayer->getName());
						gsGuildMemberLogOn.setLogOn(false);

						g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);
						
						// 디비에 업데이트 한다.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery("UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pSlayer->getName().c_str());
						}
						END_DB(pStmt)
					}
					else
						filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(), pSlayer->getName().c_str());
				}
			}
			else if (m_pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
				if (pVampire->getGuildID() != 0 )
				{
					Guild* pGuild = g_pGuildManager->getGuild(pVampire->getGuildID());
					if (pGuild != NULL )
					{
						pGuild->deleteCurrentMember(pVampire->getName());

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID(pGuild->getID());
						gsGuildMemberLogOn.setName(pVampire->getName());
						gsGuildMemberLogOn.setLogOn(false);

						g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

						// 디비에 업데이트 한다.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery("UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pVampire->getName().c_str());
						}
						END_DB(pStmt)
					}
					else
						filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str());
				}
			}
			else if (m_pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(m_pCreature);
				if (pOusters->getGuildID() != 66 )
				{
					Guild* pGuild = g_pGuildManager->getGuild(pOusters->getGuildID());
					if (pGuild != NULL )
					{
						pGuild->deleteCurrentMember(pOusters->getName());

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID(pGuild->getID());
						gsGuildMemberLogOn.setName(pOusters->getName());
						gsGuildMemberLogOn.setLogOn(false);

						g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

						// 디비에 업데이트 한다.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery("UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pOusters->getName().c_str());
						}
						END_DB(pStmt)
					}
					else
						filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pOusters->getGuildID(), pOusters->getName().c_str());
				}
			}

			int PartyID = m_pCreature->getPartyID();

			if (PartyID != 0)
			{
				Zone* pZone = m_pCreature->getZone();
				if (pZone != NULL)
				{
					LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
					pLocalPartyManager->deletePartyMember(PartyID, m_pCreature);
				}
			}

			SAFE_DELETE(m_pCreature);
			//m_pCreature->setPlayer(NULL);
		}
	}
	catch (NoSuchElementException& nsee)
	{
		cerr << "GamePlayer::~GamePlayer() : " << nsee.toString() << endl;
		throw("GamePlayer::~GamePlayer() : NoSuchElementException");
	}
	catch (Throwable& t )
	{
		t.addStack(__PRETTY_FUNCTION__);
		throw;
	}

	// 패킷을 삭제한다.
	while (!m_PacketHistory.empty()) 
	{
		Packet* pPacket = m_PacketHistory.front();
		SAFE_DELETE(pPacket);
		m_PacketHistory.pop_front();
	}

	SAFE_DELETE(m_pReconnectPacket);

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::processCommand (bool Option) 
     throw(IOException , Error)
{
	__BEGIN_TRY

	// 헤더를 임시저장할 버퍼 생성
	char header[szPacketHeader];
	PacketID_t packetID;
	PacketSize_t packetSize;
	Packet* pPacket = NULL;

	try {

		// 패널티를 받고 있는 사용자 일 경우 이 부분에서 처리 해준다.
		// 패널티를 받는 경우 어떤 예외 상황이 발생할지 모르므로,
		// 정상적인 처리를 다 한다음 패널티를 처리하도록 한다.
		if (isPenaltyFlag(PENALTY_TYPE_KICKED))
		{
			filelog("GamePlayer.txt", "Penalty Kicked. Name[%s],Host[%s],Type[%d]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()),
												m_ItemRatioBonusPoint);

			throw DisconnectException("He is had penalty");
		}

		if (Option) 
		{
			m_EventManager.heartbeat();
		}

		// 입력버퍼에 들어있는 완전한 패킷들을 모조리 처리한다.
		while (true) 
		{
			// 입력스트림에서 패킷헤더크기만큼 읽어본다.
			// 만약 지정한 크기만큼 스트림에서 읽을 수 없다면,
			// Insufficient 예외가 발생하고, 루프를 빠져나간다.
			// NoSuch제거. by sigi. 2002.5.4
			if (!m_pInputStream->peek(&header[0] , szPacketHeader))
			{
				Timeval currentTime;
				getCurrentTime(currentTime);
				if (currentTime >= m_ExpireTime)
				{
					filelog("GamePlayer.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

					throw DisconnectException("일정 시간동안 입력하지 않을 경우, 연결을 종료합니다.");
				}

				break;
			}
			
			// 패킷아이디 및 패킷크기를 알아낸다.
			// 이때 패킷크기는 헤더를 포함한다.
			memcpy(&packetID   , &header[0] , szPacketID);	
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);

			// 패킷 아이디가 이상하면 프로토콜 에러로 간주한다.
			if (packetID >= (int)Packet::PACKET_MAX)
			{
				filelog("GamePlayer.txt", "Packet ID exceed MAX, RECV [%d/%d],ID[%s],Host[%s]", 
					packetID, 
					Packet::PACKET_MAX,
					m_ID.c_str(),
//					getCreature()->getName().c_str(), 
					getSocket()->getHost().c_str());

				throw InvalidProtocolException("too large packet id");
			}

			try 
			{
				// 패킷 순서가 올바른지 검증한다.
				if (! g_pPacketValidator->isValidPacketID(getPlayerStatus() , packetID))
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}
			
				// 패킷 크기가 너무 크면 프로토콜 에러로 간주한다.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size, RECV [%d],PacketSize[%d/%d],ID[%s],Host[%s]", 
						packetID, packetSize, g_pPacketFactoryManager->getPacketMaxSize(packetID),
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("too large packet size");
				}
			
				// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
				// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					//throw InsufficientDataException();
					break;

				// 패킷 하나를 읽었으니, expire time 을 연기한다.
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

				// 현재 패킷을 패킷 히스토리의 맨 뒤에 넣는다.
				m_PacketHistory.push_back(pPacket);

                dzlog_debug("%s\n", pPacket->toString().c_str());
				// packet file log를 남긴다.
				if (m_bPacketLog )
				{
					Timeval currentTime;
					getCurrentTime(currentTime);

					if (currentTime >= m_PacketLogEndTime )
					{
						m_bPacketLog = false;
					}
					else
					{
						filelog(m_PacketLogFileName.c_str(), "%s", pPacket->toString().c_str());
					}
				}

				// 이제 이 패킷스트럭처를 가지고 패킷핸들러를 수행하면 된다.
				// 패킷아이디가 잘못될 경우는 패킷핸들러매니저에서 처리한다.
				try
				{
				#ifdef __PROFILE_PACKETS__
					
					beginProfileEx(	pPacket->getPacketName().c_str());
					pPacket->execute(this);
					endProfileEx(pPacket->getPacketName().c_str());

				#else
					pPacket->execute(this);
				#endif
				} catch (Throwable& t )
				{
                    dzlog_error("%s PacketID : %d", t.toString().c_str(), packetID);
					throw;
				}

				// 패킷을 nPacketHistorySize 개만큼만 저장한다.
				while (m_PacketHistory.size() > nPacketHistorySize) 
				{
					Packet* oldPacket = m_PacketHistory.front();
					SAFE_DELETE(oldPacket);
					m_PacketHistory.pop_front();
				}
			} 
			catch (IgnorePacketException & igpe) 
			{
				// PacketValidator 에서 패킷을 무시하라고 했으니,
				// 입력스트림에서 모두 지워버리고 실행하지 않도록 한다.

				// 패킷 크기가 너무 크면 프로토콜 에러로 간주한다.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size[Ignore], RECV [%d],PacketSize[%d],Name[%s],Host[%s]", 
																packetID, packetSize,
																((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
																((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
					throw InvalidProtocolException("too large packet sizeIgnore");
				}
			
				// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
				// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					throw InsufficientDataException();

				// 데이타가 모두 도착했으면, 그 크기만큼 무시하고,
				// 다른 패킷을 처리하도록 한다....
				m_pInputStream->skip(szPacketHeader + packetSize);

				// 무시된 패킷은, expire 에 영향을 주지 않게 된다.
				// 즉 유효한 패킷만이 짤리지 않게 해준다.
				// 또한 히스토리에도 들어가지 않는다.
			}
		}
	} 
	catch (InsufficientDataException & ide) 
	{
		// expire time 을 초과했을 경우 연결을 종료한다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime)
		{
			filelog("GamePlayer.txt", "Timeout Diconnect. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

			throw DisconnectException("일정 시간동안 입력하지 않을 경우, 연결을 종료합니다.");
		}
	}
	// 주석처리 by sigi. 2002.5.14
	/*
	catch (InvalidProtocolException & ipe) 
	{
		// 접속을 강제종료시켜야 한다. 무슨 방법으로??
		throw;
	} 
	catch (Throwable & t) 
	{
		//cerr << t.toString() << endl;
		//cerr << "GamePlayer Throwable Exception Check!" << endl;
		throw;
	}
	*/

	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// flush output buffer to socket's send buffer
//
// flush할 동안 다른 쓰레드에서 출력 버퍼에 sendPacket을 호출해서는 안된다.
// (이럴 경우는 서버간 통신으로 say가 날아오는 것밖에 없다.)
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::processOutput () 
     throw(IOException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	int i = 0;
		
	try 
	{
		Player::processOutput();

		i = 100000;
	} 
	catch (InvalidProtocolException & It) 
	{
		//cerr << "GamePlayer::processOutput Exception Check!!" << endl;
		//cerr << It.toString() << endl;
		//cerr << "익셉션 났는데...... 아이는 몇인고?" << (int)i << endl;
		throw DisconnectException("Pipe 연결의 파괴로 접속을 짜른다");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::sendPacket (Packet* pPacket) 
	 throw(ProtocolException , Error)
{	
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		// packet file log를 남긴다.
		if (m_bPacketLog )
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			if (currentTime >= m_PacketLogEndTime )
			{
				m_bPacketLog = false;
			}
			else
			{
				filelog(m_PacketLogFileName.c_str(), "%s", pPacket->toString().c_str());
			}
		}
        dzlog_debug("sendPacket:%s\n", pPacket->toString().c_str());
		Player::sendPacket(pPacket);

		/*
		if (getCreature() != NULL)
		{
			PacketID_t packetID = pPacket->getPacketID();
			switch (packetID)
			{
				case Packet::PACKET_GC_UPDATE_INFO:
				case Packet::PACKET_GC_MOVE_OK:
				case Packet::PACKET_GC_SET_POSITION:
					filelog("GamePlayer.txt", "SEND [%s],Name[%s],Host[%s]", 
							pPacket->getPacketName().c_str(), 
							getCreature()->getName().c_str(), 
							getSocket()->getHost().c_str());
					break;
				default:
					break;
			}
		}
		else
		{
			PacketID_t packetID = pPacket->getPacketID();
			switch (packetID)
			{
				case Packet::PACKET_GC_UPDATE_INFO:
				case Packet::PACKET_GC_MOVE_OK:
				case Packet::PACKET_GC_SET_POSITION:
					filelog("GamePlayer.txt", "SEND [%s],Name[NULL],Host[%s]", 
							pPacket->getPacketName().c_str(), 
							getSocket()->getHost().c_str());
					break;
				default:
					break;
			}
		}
		*/
	} 
	catch (InvalidProtocolException & It) 
	{
		//cout << "GamePlayer::sendPacket Exception Check!!" << endl;
		//cout << It.toString() << endl;
		//throw DisconnectException("Pipe 연결의 파괴로 접속을 짜른다");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// disconnect player
//
// (1) 크리처가 존재할 경우, 존에서 삭제하고 브로드캐스트한다.
// (2) 크리처를 저장한다.
//
//--------------------------------------------------------------------------------
void GamePlayer::disconnect (bool bDisconnected)
	throw(InvalidProtocolException, Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//--------------------------------------------------------------------------------
	// 크리처를 존에서 삭제한 후, 주변의 PC들에게 브로드캐스트해준다.
	// 그다음 크리처를 DB에 저장한다.
	//--------------------------------------------------------------------------------
	string CreatureName = "";
	if (m_pCreature != NULL) 
	{
		CreatureName = m_pCreature->getName();

		try 
		{
			// GPS_NORMAL 인 경우에만, 존에 크리처가 들어가 있게 된다.
			// *CAUTION*
			// 혹시 pushPC()가 호출된 후에 연결이 종료되면 어떻게 하나.. 라고 걱정할 가능성도 있다.
			// 그러나, 처리 루틴의 순서를 잘 살펴보면 그런 걱정을 할 필요가 없다.
			// 어차피 연결이 끊기더라도, 존이 처리된 후 크리처가 실제 타일로 올라간 다음,
			// 다시 플레이어의 처리루프가 돌아오기 때문이다.
			if (getPlayerStatus() == GPS_NORMAL) 
			{
				//----------------------------------
				// 존에서 삭제하고 브로드캐스트한다.
				//----------------------------------
				Zone* pZone = m_pCreature->getZone();
				Assert(pZone != NULL);
				pZone->deleteQueuePC(m_pCreature);
				pZone->deleteCreature(m_pCreature , m_pCreature->getX() , m_pCreature->getY());
				//--------------------------------------------------------------------------------
				// 크리처를 저장한다.
				//--------------------------------------------------------------------------------
				m_pCreature->save();
			} 
		} 
		catch (Throwable & t) 
		{
		}
	}

	setPlayerStatus(GPS_END_SESSION);

	//--------------------------------------------------------------------------------
    // 아이디가 설정되었다는 뜻은, 로그인이 이루어졌다는 뜻이다.
	//--------------------------------------------------------------------------------
    if (m_ID != "")
    {
        Statement* pStmt1 = NULL;
        Statement* pStmt2 = NULL;

		BEGIN_DB
		{

//            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            // 로그오프로 변경한다.
	      	//pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt1 = g_pDatabaseManager->getDistConnection("PLAYER_DB" )->createStatement();

			// LogOn이 GAME상태인 경우만 LOGOFF로 바꾼다. by sigi. 2002.5.15
            pStmt1->executeQuery("UPDATE Player SET LogOn='LOGOFF', LastLogoutDate=now() WHERE PlayerID = '%s' AND LogOn='GAME'" , m_ID.c_str());

			// LogoutPlayerData 에 추가한다.
		//	addLogoutPlayerData(this);

			if (pStmt1->getAffectedRowCount()==0)
			{
				// 이미 LOGOFF거나
				// LOGON상태인가?
				// 이럴 수 있을까? -_-;
			}

			// 빌링 by sigi. 2002.5.31
#if defined(__PAY_SYSTEM_LOGIN__) || defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
			if (isPayPlaying() || isPremiumPlay())
			{
				logoutPayPlay(m_ID);
			}
#endif


			SAFE_DELETE(pStmt1);

		}
		END_DB(pStmt1)
		BEGIN_DB
        {

			// IP 정보를 삭제해 준다.
            pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            pStmt2->executeQuery("DELETE FROM UserIPInfo WHERE Name = '%s'", CreatureName.c_str());

			SAFE_DELETE(pStmt2);
        }
		END_DB(pStmt2)
    }

	// login서버로 가라고 client에게 보낸다.
	// 원래는 LGIncomingConnectionOKHandler에서 처리했다. by sigi. 2002.6.19
	if (m_pReconnectPacket!=NULL)
	{
		try 
		{
			//sendPacket(m_pReconnectPacket);
			Player::sendPacket(m_pReconnectPacket);
			// 출력 버퍼에 남아있는 데이타를 전송한다.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			// 무시
		}
		
		SAFE_DELETE(m_pReconnectPacket);
	}


	// 함수 윗부분에서 처리했는데.. 타이밍 문제(LogOn이나 UserIPInfo 등)로
	// 여기서 끊어주고.. 재접패킷~을 보내도록 한다.
	if (bDisconnected == UNDISCONNECTED) 
	{
		try 
		{
			// 클라이언트에게 GCDisconnect 패킷을 전송한다.
			//GCDisconnect gcDisconnect;
			//sendPacket(gcDisconnect);

			// 출력 버퍼에 남아있는 데이타를 전송한다.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			//cerr << "GamePlayer::disconnect() : GamePlayer::disconnect Exception Check!!" << endl;
			//cerr << t.toString() << endl;
		}
	}

	// 소켓 연결을 닫는다.
	m_pSocket->close();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 최근 N 번째의 패킷을 리턴한다.
// 
// N == 0 일 경우, 가장 최근의 패킷을 리턴하게 된다.
//
// 최대 nPacketHistorySize - 1 까지 지정할 수 있다. 
//
//////////////////////////////////////////////////////////////////////
Packet* GamePlayer::getOldPacket (uint prev)
	throw(OutOfBoundException , NoSuchElementException)
{
	__BEGIN_TRY

	if (prev >= nPacketHistorySize)
		throw OutOfBoundException();

	// if prev == 0 , return m_PacketHistory[9]
	// if prev == 9 , return m_PacketHistory[0]
	Packet* pPacket = m_PacketHistory[ nPacketHistorySize - prev - 1 ];

	if (pPacket == NULL)
		throw NoSuchElementException("packet history is empty");

	return pPacket;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 특정 패킷아이디를 가진 가장 최근의 패킷을 리턴한다.
//
//////////////////////////////////////////////////////////////////////
Packet* GamePlayer::getOldPacket (PacketID_t packetID)
	throw(NoSuchElementException)
{
	__BEGIN_TRY

	Packet* pPacket = NULL;
	deque<Packet*>::reverse_iterator ritr = m_PacketHistory.rbegin();

	for (; ritr != m_PacketHistory.rend(); ritr++) 
	{
		if ((*ritr)->getPacketID() == packetID) {
			pPacket = (*ritr);
			break;
		}	
	}

	if (pPacket == NULL)
		throw NoSuchElementException("packet history is empty");

	return pPacket;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void GamePlayer::addEvent (Event* pEvent)
	throw(Error)
{
	__BEGIN_TRY

	m_EventManager.addEvent(pEvent);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void GamePlayer::deleteEvent (Event::EventClass EClass)
	throw(Error)
{
	__BEGIN_TRY

	m_EventManager.deleteEvent(EClass);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
Event* GamePlayer::getEvent (Event::EventClass EClass)
	throw(Error)
{
	__BEGIN_TRY

	return m_EventManager.getEvent(EClass);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string GamePlayer::toString () const
       throw(Error)
{
	__BEGIN_TRY
		
	StringStream msg;
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	__ENTER_CRITICAL_SECTION(m_Mutex)
	
	msg << "GamePlayer(SocketID:" << m_pSocket->getSOCKET() << ",Host:" << m_pSocket->getHost() << ")" ;

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// verifySpeed
//
//////////////////////////////////////////////////////////////////////
bool GamePlayer::verifySpeed(Packet* pPacket)
	throw(Error)
{
	__BEGIN_TRY

	bool SpeedCheck = false;

	Timeval CurrentTime;
	getCurrentTime(CurrentTime);

	if(m_SpeedVerify.tv_sec == 0 )
	{
//		getCurrentTime(m_SpeedVerify);
//		m_SpeedVerify.tv_sec += SpeedCheckDelay;
		// m_SpeedVerify 를 현재 시간으로 굳이 받아올 필요없이
		// 함수 첫 부분에서 받아 놓은 걸 걍 쓴다.
		// 2002.1.7 by bezz
		m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

		SpeedCheck = true;
	}
	else
	{
		// 원래 날아와야될 약정 시간에서 5초 빨리 날아오면 스피드핵이다.
		if(CurrentTime.tv_sec > m_SpeedVerify.tv_sec - maxTimeGap )
		{
			// 스피드 핵 통과를 했다면 다음 날아올 약정 시간을 셋팅 해야 한다.
//			getCurrentTime(m_SpeedVerify);
//			m_SpeedVerify.tv_sec += SpeedCheckDelay;
			// m_SpeedVerify 를 현재 시간으로 굳이 받아올 필요없이
			// 함수 첫 부분에서 받아 놓은 걸 걍 쓴다.
			// 2002.1.7 by bezz
			m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

			SpeedCheck = true;
			m_VerifyCount = max(0, m_VerifyCount-1);
		}
		else
		{
//			getCurrentTime(m_SpeedVerify);
//			m_SpeedVerify.tv_sec += SpeedCheckDelay;
			// m_SpeedVerify 를 현재 시간으로 굳이 받아올 필요없이
			// 함수 첫 부분에서 받아 놓은 걸 걍 쓴다.
			// 2002.1.7 by bezz
			m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

			if(m_VerifyCount > maxVerifyCount )
			{
				SpeedCheck = false;
			}
			else
			{
				SpeedCheck = true;
			}
			m_VerifyCount++;
		}
	}

	/*
	// 크리처의 스피드를 받아온다.
	if (m_pCreature == NULL || pPacket == NULL) {
		return true;
	}

	// 규정 시간 이전에 똑 같은 패킷이 수십번 날아오면 접속을 짜른다.
	Timeval VerifyTime;
	getCurrentTime(VerifyTime);

	PacketID_t PacketID = pPacket->getPacketID();

	bool SpeedCheck = true;

	if (m_pCreature->isSlayer()) {

		Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
		Speed_t AttackSpeed = pSlayer->getAttackSpeed();
		BYTE Speed = 0;
		if (AttackSpeed < 33) {
			Speed = 0;
		} else if (AttackSpeed < 67) {
			Speed = 1;
		} else {
			Speed = 2;
		}

		if (PacketID == Packet::PACKET_CG_MOVE) {
			// 이전 시간이랑 현재 시간이랑 체크해서 더 빠른 시간에 패킷이 날아왔으면 이건 치터다.
			if (VerifyTime <= m_MoveSpeedVerify) {
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			// 다음에 무브가 가장 빨리 날아올 수 있는 가능한 시간을 저장해 둔다.
			// 모토 사이클을 타고 있다면 이동속도가 줄어든다.

			BYTE RealSpeed = 0;
			if (pSlayer->hasRideMotorcycle()) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // 모토사이클이 아니다.
			{
				//RealSpeed = 4;
				RealSpeed = 2;
			}

			// 다음 쓸 수 있는 시간을 셋팅한다.
			m_MoveSpeedVerify.tv_sec += RealSpeed / 10;
			m_MoveSpeedVerify.tv_usec += RealSpeed* 100000;

			m_AttackSpeedVerify.tv_sec += RealSpeed / 10;
			m_AttackSpeedVerify.tv_usec += RealSpeed* 100000;
		} 
		else if (PacketID == Packet::PACKET_CG_ATTACK) 
		{
			if (VerifyTime <= m_AttackSpeedVerify) 
			{
				SpeedCheck = false;
			}
			// 무기를 무엇을 들고 있는지 체크한다.
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			Item::ItemClass IClass = Item::ITEM_CLASS_SKULL;
			if (pItem != NULL) {
				IClass = pItem->getItemClass();
			} 

			getCurrentTime(m_AttackSpeedVerify);
			getCurrentTime(m_MoveSpeedVerify);

			BYTE RealSpeed = 0;
			// 슬로우 스피드
			if (Speed == 0) 
			{
				switch (IClass) 
				{
					// 937
					case Item::ITEM_CLASS_SWORD :
						RealSpeed = 9;
						break;
					// 1187
					case Item::ITEM_CLASS_BLADE :
					case Item::ITEM_CLASS_CROSS :
					case Item::ITEM_CLASS_MACE :
						RealSpeed = 11;
						break;
					// 1250
					case Item::ITEM_CLASS_AR :
						RealSpeed = 12;
						break;
					// 1000
					case Item::ITEM_CLASS_SG :
						RealSpeed = 10;
						break;
					// 1375
					case Item::ITEM_CLASS_SR :
						RealSpeed = 13;
						break;
					// 1000
					case Item::ITEM_CLASS_SMG :
						RealSpeed = 10;
						break;
					// 기본 공격 875
					default :
						RealSpeed = 8;
						break;
				}
			} 
			else if (Speed == 1) // 노멀 스피드
			{
				switch (IClass) 
				{
					// 812
					case Item::ITEM_CLASS_SWORD :
						RealSpeed = 8;
						break;
					// 1062
					case Item::ITEM_CLASS_BLADE :
					case Item::ITEM_CLASS_CROSS :
					case Item::ITEM_CLASS_MACE :
						RealSpeed = 10;
						break;
					// 875
					case Item::ITEM_CLASS_AR :
						RealSpeed = 8;
						break;
					// 1125
					case Item::ITEM_CLASS_SG :
						RealSpeed = 11;
						break;
					// 1250
					case Item::ITEM_CLASS_SR :
						RealSpeed = 12;
						break;
					// 875
					case Item::ITEM_CLASS_SMG :
						RealSpeed = 8;
						break;
					// 기본 공격 875
					default :
						RealSpeed = 8;
						break;

				}
			} 
			else // 패스트 스피드
			{
				switch (IClass) 
				{
					// 687
					case Item::ITEM_CLASS_SWORD :
						RealSpeed = 6;
						break;
					// 938
					case Item::ITEM_CLASS_BLADE :
					case Item::ITEM_CLASS_CROSS :
					case Item::ITEM_CLASS_MACE :
						RealSpeed = 9;
						break;
					// 750
					case Item::ITEM_CLASS_AR :
						RealSpeed = 7;
						break;
					// 1000
					case Item::ITEM_CLASS_SG :
						RealSpeed = 10;
						break;
					// 1125
					case Item::ITEM_CLASS_SR :
						RealSpeed = 11;
						break;
					// 750
					case Item::ITEM_CLASS_SMG :
						RealSpeed = 7;
						break;
					// 875
					default :
						RealSpeed = 8;
						break;
				}
			}

			// 스피드 완화 정책
			RealSpeed -= 2;

			m_AttackSpeedVerify.tv_sec += RealSpeed / 10;
			m_AttackSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);

			m_MoveSpeedVerify.tv_sec += RealSpeed / 10;
			m_MoveSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);

		} else if (PacketID == Packet::PACKET_CG_SKILL_TO_OBJECT || PacketID == Packet::PACKET_CG_SKILL_TO_SELF || PacketID == Packet::PACKET_CG_SKILL_TO_TILE) {

		} else {
			SpeedCheck = true;
		}
	} 
	else if (m_pCreature->isVampire()) 
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
		Speed_t AttackSpeed = pVampire->getAttackSpeed();

		BYTE Speed = 0;
		if (AttackSpeed < 33) 
		{
			Speed = 0;
		} 
		else if (AttackSpeed < 67) 
		{
			Speed = 1;
		} 
		else 
		{
			Speed = 2;
		}

		if (PacketID == Packet::PACKET_CG_MOVE) 
		{
			// 이전 시간이랑 현재 시간이랑 체크해서 더 빠른 시간에 패킷이 날아왔으면 이건 치터다.
			if (VerifyTime <= m_MoveSpeedVerify) 
			{
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			BYTE RealSpeed = 0;
			// 다음에 무브가 가장 빨리 날아올 수 있는 가능한 시간을 저장해 둔다.
			// 박쥐 변신을 하고 있다면 속도가 빨라진다. 초당 네 타일을 이동 한다.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // 노멀 상태에선 초당 두타일을 이동한다.
			{
				//RealSpeed = 4;
				RealSpeed = 2;
			}

			m_MoveSpeedVerify.tv_sec += (RealSpeed / 10);
			m_AttackSpeedVerify.tv_sec += (RealSpeed / 10);

			m_MoveSpeedVerify.tv_usec += (RealSpeed* 100000);
			m_AttackSpeedVerify.tv_usec += (RealSpeed* 100000);
		} 
		else if (PacketID == Packet::PACKET_CG_ATTACK) 
		{
			if (VerifyTime <= m_AttackSpeedVerify) 
			{
				SpeedCheck = false;
			}

			getCurrentTime(m_AttackSpeedVerify);
			getCurrentTime(m_MoveSpeedVerify);

			BYTE RealSpeed = 0;
			if (Speed == 0) // 슬로우 스피드 875
			{
				RealSpeed = 8;
			} 
			else if (Speed == 1) // 노멀 스피드 875
			{
				RealSpeed = 8;
			} 
			else // 패스트 스피드 812
			{
				RealSpeed = 8;
			}

			// 스피드 완화 정책
			RealSpeed -= 2;

			m_AttackSpeedVerify.tv_sec += RealSpeed / 10;
			m_AttackSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);

			m_MoveSpeedVerify.tv_sec += RealSpeed / 10;
			m_MoveSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);
		} 
		else if (PacketID == Packet::PACKET_CG_SKILL_TO_OBJECT || 
				  PacketID == Packet::PACKET_CG_SKILL_TO_SELF   || 
				  PacketID == Packet::PACKET_CG_SKILL_TO_TILE) 
		{
		} 
		else 
		{
			SpeedCheck = true;
		}
	} 
	else 
	{
	}
	*/

	return SpeedCheck;

	__END_CATCH
}

void GamePlayer::loadSpecialEventCount(void)
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
//		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt   = g_pDatabaseManager->getDistConnection("PLAYER_DB" )->createStatement();

		pResult = pStmt->executeQuery("SELECT SpecialEventCount FROM Player WHERE PlayerID='%s'", m_ID.c_str());

		if (pResult->getRowCount() != 0)
		{
			pResult->next();
			m_SpecialEventCount = pResult->getDWORD(1);
		}
		else
		{
			SAFE_DELETE(pStmt);
			throw("GamePlayer::loadSpecialEventCount() : unable to dispatch data");
			return;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

void GamePlayer::saveSpecialEventCount(void)
	throw()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
//		pStmt = g_pDatabaseManager->getConnection((int)Thread::self() )->createStatement();

		pStmt->executeQuery("UPDATE Player SET SpecialEventCount=%d WHERE PlayerID='%s'", m_SpecialEventCount, m_ID.c_str());
		SAFE_DELETE(pStmt);	
	}
	END_DB(pStmt);

	__END_CATCH
}

bool    GamePlayer::sendBillingLogin() 
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

			Timeval afterTime;
			getCurrentTime(afterTime);

			// 1초 이상 걸리면 로그 남긴다.
			if (afterTime.tv_sec > currentTime.tv_sec + 1 )
			{
				filelog("billingLoginTime.txt", "PlayerID : %s, CallTime : %d sec, Try : %d", m_ID.c_str(), (int)(afterTime.tv_sec - currentTime.tv_sec), m_BillingLoginRequestCount);
			}

			// PayLogin 요청한 회수 기억
			m_BillingLoginRequestCount ++;

			// 60초 후 다시 체크한다.
			m_BillingNextLoginRequestTime.tv_sec = currentTime.tv_sec + 60;
		}

		return true;
	}

	return false;

	__END_CATCH
}

void GamePlayer::sendCBillingPayInfo()
	throw(Error )
{
	__BEGIN_TRY

	char m[200];
	if (m_CBPlayerType == CBILLING_PLAYER_TYPE_MONTHLY )
	{
		VSDate currentDate;
		currentDate = VSDate::currentDate();

		sprintf(m, g_pStringPool->c_str(STRID_CB_MONTHLY_PLAYER ),
						m_CBEndDateTime.date().year(),
						m_CBEndDateTime.date().month(),
						m_CBEndDateTime.date().day(),
						currentDate.year(),
						currentDate.month(),
						currentDate.day());

		GCSystemMessage msg;
		msg.setMessage(m);

		sendPacket(&msg);
	}
	else if (m_CBPlayerType == CBILLING_PLAYER_TYPE_POINT )
	{
		sprintf(m, g_pStringPool->c_str(STRID_CB_POINT_PLAYER ), m_CBLeftTime / 10);

		GCSystemMessage msg;
		msg.setMessage(m);

		sendPacket(&msg);
	}

	__END_CATCH
}

// 암호화 코드를 설정한다.
void GamePlayer::setEncryptCode()
    throw(Error)
{
    __BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	Assert(m_pCreature!=NULL);

	// 일단은 ObjectID를 이용한다.
	//ObjectID_t 	objectID 	= m_pCreature->getObjectID();

	// 존별로 관리를 하도록 수정한다.
//	ZoneID_t 	zoneID 		= m_pCreature->getZone()->getZoneID();
//	static int	serverID	= g_pConfig->getPropertyInt("ServerID");

//	if (objectID!=0)
//	{
		//uchar code = (uchar)(objectID / zoneID + objectID);
		//uchar code = (uchar)(((zoneID >> 8 ) ^ zoneID ) ^ ((serverID + 1 ) << 4 ));
		uchar code = m_pCreature->getZone()->getEncryptCode();

#ifdef __ACTIVE_SERVICE_DEADLINE__
		// 서버 바보 만들기 코드
		VSDate date = VSDate::currentDate();
		// 2003년 1월 이상인 경우: 2003, 0
		if (date.year()>=DEADLINE_YEAR && date.month()>DEADLINE_MONTH)
			code += (date.year()+date.month())/11;
#endif

		SocketEncryptOutputStream* pEOS = dynamic_cast<SocketEncryptOutputStream*>(m_pOutputStream);
		Assert(pEOS!=NULL);

		SocketEncryptInputStream* pEIS = dynamic_cast<SocketEncryptInputStream*>(m_pInputStream);
		Assert(pEIS!=NULL);

		pEOS->setEncryptCode(code);
		pEIS->setEncryptCode(code);
//	}
#endif

	__END_CATCH
}

void GamePlayer::kickPlayer(uint nSeconds, uint KickMessageType )
	throw(Error)
{
	__BEGIN_TRY

	// 이미 EventKick 이 있다면 무시한다.
	if (m_EventManager.getEvent(Event::EVENT_CLASS_KICK ) != NULL )
		return;

	EventKick* pEventKick = new EventKick(this);
	pEventKick->setDeadline(nSeconds * 10);
	addEvent(pEventKick);

	// 몇 초후에 짤린다..고 보내준다.
	GCKickMessage gcKickMessage;
	gcKickMessage.setType(KickMessageType);
	gcKickMessage.setSeconds(nSeconds);
	sendPacket(&gcKickMessage);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////
// PaySystem 관련
//////////////////////////////////////////////////////////////////
bool GamePlayer::loginPayPlay(PayType payType, const string& PayPlayDate, int PayPlayHours, uint payPlayFlag, const string& ip, const string& playerID )
	throw(Error)
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	return PaySystem::loginPayPlay(payType, PayPlayDate, PayPlayHours, payPlayFlag, ip, playerID);
#endif
	__END_CATCH
}

bool GamePlayer::loginPayPlay(const string& ip, const string& playerID )
    throw(Error)
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	bool bRet = PaySystem::loginPayPlay(ip, playerID);

	if (bRet )
		setPCRoomLottoStartTime();

	return bRet;
#endif
	__END_CATCH
}

bool GamePlayer::updatePayPlayTime(const string& playerID, const VSDateTime& currentDateTime, const Timeval& currentTime )
    throw(ProtocolException, Error )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	checkPCRoomLotto(currentTime);

	return PaySystem::updatePayPlayTime(playerID, currentDateTime, currentTime);
#endif
	__END_CATCH
}

void GamePlayer::logoutPayPlay(const string& playerID, bool bClear, bool bDecreaseTime )
    throw(Error)
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	if (!BillingPlayerInfo::isBillingPlayAvaiable() )
		setPremiumPlay(false);
#else
	savePCRoomLottoTime();

	PaySystem::logoutPayPlay(playerID, bClear, bDecreaseTime);
#endif
	__END_CATCH
}

bool GamePlayer::isPayPlaying() const
{
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#elif defined(__CONNECT_CBILLING_SYSTEM__)
	return CBillingPlayerInfo::isPayPlayer();
#elif !defined(__PAY_SYSTEM_ZONE__) && !defined(__PAY_SYSTEM_LOGIN__) && !defined(__PAY_SYSTEM_FREE_LIMIT__)
	// if there is no Pay defines, all users are pay player
	return true;
#else
	return PaySystem::isPayPlaying();
#endif
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

void GamePlayer::setPCRoomLottoStartTime()
{
	if (!g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if (!m_bPCRoomPlay )
		return;

	m_PCRoomLottoStartTime.tv_sec = m_PayPlayStartTime.tv_sec - m_PCRoomLottoSumTime;
}

void GamePlayer::savePCRoomLottoTime()
{
	if (!g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if (!m_bPCRoomPlay )
		return;

	Timeval currentTime;
	getCurrentTime(currentTime);

	m_PCRoomLottoSumTime = currentTime.tv_sec - m_PCRoomLottoStartTime.tv_sec;
	m_PCRoomLottoStartTime.tv_sec = 0;
}

void GamePlayer::checkPCRoomLotto(const Timeval& currentTime )
{
	if (!g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if (!m_bPCRoomPlay )
		return;

	if (m_PCRoomLottoStartTime.tv_sec == 0 )
	{
		m_PCRoomLottoStartTime.tv_sec = currentTime.tv_sec - m_PCRoomLottoSumTime;
	}

	int time = currentTime.tv_sec - m_PCRoomLottoStartTime.tv_sec;	

	if (time >= PCRoomLottoSec )
	{
		giveLotto();

		// 다시 시간을 초기화한다.
		m_PCRoomLottoStartTime.tv_sec = currentTime.tv_sec;
		m_PCRoomLottoSumTime = 0;
	}
}

void GamePlayer::giveLotto()
{
	if (m_pCreature == NULL )
		return;

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		static uint DimensionID	= g_pConfig->getPropertyInt("Dimension");
		static uint WorldID		= g_pConfig->getPropertyInt("WorldID");
		string PlayerID		= getID();
		string Name			= m_pCreature->getName();
		Race_t Race			= m_pCreature->getRace();
		int Amount			= 0;
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		pResult = pStmt->executeQuery("SELECT Amount FROM PCRoomLottoObject WHERE PlayerID = '%s' AND Name = '%s' AND DimensionID = %u AND WorldID = %u",
										PlayerID.c_str(), Name.c_str(), DimensionID, WorldID);

		if (pResult->next() )
		{
			Amount = pResult->getInt(1);

			if (Amount < PCRoomLottoMaxAmount )
			{
				pStmt->executeQuery("UPDATE PCRoomLottoObject SET Amount = %d WHERE PlayerID = '%s' AND Name = '%s' AND DimensionID = %u AND WorldID = %u",
										Amount + 1, PlayerID.c_str(), Name.c_str(), DimensionID, WorldID);
			}
		}
		else
		{
			// 복권이 없었다. 새로 넣어준다.
			pStmt->executeQuery("INSERT INTO PCRoomLottoObject VALUES (0, %u, '%s', %u, %u, '%s', %u, 1 )",
									m_PCRoomID, PlayerID.c_str(), DimensionID, WorldID, Name.c_str(), Race);
		}

		if (Amount < PCRoomLottoMaxAmount )
		{
			char msg[100];
			sprintf(msg, g_pStringPool->c_str(STRID_GIVE_LOTTO ), Amount + 1); 

			GCSystemMessage gcMsg;
			gcMsg.setMessage(msg);
			sendPacket(&gcMsg);

			if (Amount >= PCRoomLottoMaxAmount - 1 )
			{
				gcMsg.setMessage(g_pStringPool->getString(STRID_CANNOT_GIVE_LOTTO ));
				sendPacket(&gcMsg);
			}
		}
	}
	END_DB(pStmt )
}

bool GamePlayer::startPacketLog(uint sec )
{
	if (m_pCreature == NULL )
		return false;

	m_bPacketLog = true;
	getCurrentTime(m_PacketLogEndTime);
	m_PacketLogEndTime.tv_sec += sec;

	char filename[100];
	sprintf(filename, "log/%s.log", m_pCreature->getName().c_str());
	m_PacketLogFileName = filename;

	return true;
}

void GamePlayer::logLoginoutDateTime()
{
	if (m_pCreature == NULL )
		return;

	// DimensionID 구하기
	uint dimensionID = g_pConfig->getPropertyInt("Dimension");
	if (g_pConfig->getPropertyInt("IsNetMarble") == 0 )
	{
		// 넷마블 일 경우엔 2
		dimensionID = 2;
	}

	// WorldID
	uint worldID = g_pConfig->getPropertyInt("WorldID");

	// 종족 코드
	uint racecode;
	uint str,dex,inte;
	if (m_pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
		Assert(pSlayer != NULL);

		racecode = (uint)pSlayer->getHighestSkillDomain();

		str = pSlayer->getSTR();
		dex = pSlayer->getDEX();
		inte = pSlayer->getINT();
	}
	else if (m_pCreature->isVampire() )
	{
		// 뱀파이어는  10
		racecode = 10;

		Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
		Assert(pVampire != NULL);

		str = pVampire->getSTR();
		dex = pVampire->getDEX();
		inte = pVampire->getINT();
	}
	else if (m_pCreature->isOusters() )
	{
		// 아우스터즈는 20
		racecode = 20;

		Ousters* pOusters = dynamic_cast<Ousters*>(m_pCreature);
		Assert(pOusters != NULL);

		str = pOusters->getSTR();
		dex = pOusters->getDEX();
		inte = pOusters->getINT();
	}
	else
	{
		return;
	}

	// 레벨
	uint level = (uint)m_pCreature->getLevel();

	// 로그아웃 시간. 현재 시간
	VSDateTime logoutDateTime = VSDateTime::currentDateTime();

	// filename
	char filename[20];
	sprintf(filename, "log/%s.txt", logoutDateTime.toStringforWeb().c_str());

	try
	{
		ofstream file(filename, ios::out | ios::app);
		file << dimensionID << "\t" << worldID << "\t" << m_ID << "\t"
			 << m_pCreature->getName() << "\t" << racecode << "\t"
			 << level << "\t" << str << "\t" << dex << "\t" << inte << "\t"
			 << m_LoginDateTime.toDateTime() << "\t"
			 << logoutDateTime.toDateTime() << endl;
		file.close();
	}
	catch (...)
	{
	}
}

