//////////////////////////////////////////////////////////////////////////////
// Filename    : GamePlyaer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GamePlayer.h"
#include "Assert.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "LogClient.h"
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

#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////
// ��� packet�鿡 ���ؼ� profiling�Ѵ�. by sigi. 2002.5.6
//
// ��, �̰� ����ϱ� ���ؼ��� 
// Profile.h�� MAX_PROFILE_SAMPLES += 300�� ����� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
//#define __PROFILE_PACKETS__

#ifdef __PROFILE_PACKETS__
	#include "Profile.h"
#endif

// by sigi. 2002.11.12
const int defaultGamePlayerInputStreamSize = 1024;
const int defaultGamePlayerOutputStreamSize = 20480;

static int maxIdleSec         = 60* 5;		// �޶���ʱ����󱣳�����ʱ�� 60 * 5 = 300��(5��)
//static int maxSpeedVerifyTime = 2;  		// 0.3 ��
static int maxVerifyCount     = 3;      	// ������У����� 3��
static int maxTimeGap         =	5;			// ʱ��У��ƫ������ ����Ϊ5�� �޸�Ϊ8��
static int SpeedCheckDelay    = 60;			// ʱ��У����60��һ��

const int PCRoomLottoSec = 3600;			// 3600 ��. 1�ð�
const int PCRoomLottoMaxAmount = 3;			// �ѹ��� ���� �� �ִ� �ִ� ���Ǽ�
// CLLoginHandler.cpp�� �ִ� �Լ���.
void addLogoutPlayerData(Player* pPlayer);


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GamePlayer::GamePlayer (Socket* pSocket)
: //Player(pSocket), 	// by sigi. 2002.11.12
	m_pCreature(NULL), m_PlayerStatus(GPS_NONE), m_pReconnectPacket(NULL),m_Sequence(0)
{
	__BEGIN_TRY

	Assert( pSocket != NULL );
	m_pSocket = pSocket;

#ifdef __USE_ENCRYPTER__
	// create socket input stream
	m_pInputStream = new SocketEncryptInputStream( m_pSocket, defaultGamePlayerInputStreamSize );
	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketEncryptOutputStream( m_pSocket, defaultGamePlayerOutputStreamSize );
	Assert( m_pOutputStream != NULL );
#else
	// create socket input stream
	m_pInputStream = new SockettInputStream( m_pSocket, defaultGamePlayerInputStreamSize );
	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SockettOutputStream( m_pSocket, defaultGamePlayerOutputStreamSize );
	Assert( m_pOutputStream != NULL );
#endif

	m_Mutex.setName("GamePlayer");
		
	getCurrentTime(m_ExpireTime);
	m_ExpireTime.tv_sec += maxIdleSec;

    // ���� �ð��� �޾ƿ´�
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

//	if ( m_bPCRoomPlay )
//		m_ItemRatioBonusPoint = g_pVariableManager->getPCRoomItemRatioBonusPercent();
//	else
		m_ItemRatioBonusPoint = 0;

	m_PCRoomLottoStartTime.tv_sec = 0;
	m_PCRoomLottoStartTime.tv_usec = 0;
	m_PCRoomLottoSumTime = 0;

	m_bPacketLog = false;

	// ��ü�� ������ ������ �α����� �ð����� ����.
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
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	// �� � �÷��̾� ��ü�� ������ ������, �� ���´� �α׾ƿ��̾�� �Ѵ�.
	// �� � �÷��̾ ���� ���� ��Ű����, �� ���¸� �α׾ƿ����� ������ �Ѵ�.
	Assert(m_PlayerStatus == GPS_END_SESSION);

	try
	{
		// Delete creature
		if (m_pCreature != NULL) 
		{
			// ���� ����߸���
			if ( m_pCreature->hasRelicItem() )
			{
				dropRelicToZone( m_pCreature, false );
			}

			dropFlagToZone( m_pCreature, false );
			dropSweeperToZone( m_pCreature );

			//try 
			//{
				// NoSuch����. by sigi. 2002.5.2
				g_pPCFinder->deleteCreature(m_pCreature->getName());
			//} 
			//catch (NoSuchElementException & t) 
			//{
			//}

		#ifdef __CONNECT_BILLING_SYSTEM__
			// Pay �����Ѵٰ� �˷��ش�. by sigi. 2002.11.18
			if ( isBillingPlayAvaiable() && !m_bMetroFreePlayer )	// by sigi. 2002.11.23
			{
				g_pBillingPlayerManager->sendPayLogout( this );
			}
		#elif defined(__CONNECT_CBILLING_SYSTEM__ )
			// �߱� ���� ������ logout ��Ŷ�� ������.
			g_pCBillingPlayerManager->sendLogout( this );
		#endif

			Statement* pStmt = NULL;

			// ��� ���� ���� ��� ����Ʈ���� �����Ѵ�.
			if ( m_pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
				if ( pSlayer->getGuildID() != 99 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pSlayer->getGuildID() );
					if ( pGuild != NULL )
					{
						pGuild->deleteCurrentMember( pSlayer->getName() );

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID( pGuild->getID() );
						gsGuildMemberLogOn.setName( pSlayer->getName() );
						gsGuildMemberLogOn.setLogOn( false );

						g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );
						
						// ��� ������Ʈ �Ѵ�.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pSlayer->getName().c_str() );
						}
						END_DB(pStmt)
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(), pSlayer->getName().c_str() );
				}
			}
			else if ( m_pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
				if ( pVampire->getGuildID() != 0 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pVampire->getGuildID() );
					if ( pGuild != NULL )
					{
						pGuild->deleteCurrentMember( pVampire->getName() );

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID( pGuild->getID() );
						gsGuildMemberLogOn.setName( pVampire->getName() );
						gsGuildMemberLogOn.setLogOn( false );

						g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

						// ��� ������Ʈ �Ѵ�.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pVampire->getName().c_str() );
						}
						END_DB(pStmt)
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str() );
				}
			}
			else if ( m_pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(m_pCreature);
				if ( pOusters->getGuildID() != 66 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pOusters->getGuildID() );
					if ( pGuild != NULL )
					{
						pGuild->deleteCurrentMember( pOusters->getName() );

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID( pGuild->getID() );
						gsGuildMemberLogOn.setName( pOusters->getName() );
						gsGuildMemberLogOn.setLogOn( false );

						g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

						// ��� ������Ʈ �Ѵ�.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pOusters->getName().c_str() );
						}
						END_DB(pStmt)
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pOusters->getGuildID(), pOusters->getName().c_str() );
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
			//m_pCreature->setPlayer( NULL );
		}
	}
	catch (NoSuchElementException& nsee)
	{
		cerr << "GamePlayer::~GamePlayer() : " << nsee.toString() << endl;
		throw ("GamePlayer::~GamePlayer() : NoSuchElementException");
	}
	catch (Throwable& t )
	{
		t.addStack( __PRETTY_FUNCTION__ );
		throw;
	}

	// ��Ŷ�� �����Ѵ�.
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
//////////////////////////////////////////////////////////////////////////
//
// ����timeval�ṹ���
//
//////////////////////////////////////////////////////////////////////////
void GamePlayer::tv_sub(struct timeval *out,struct timeval *in) 
{ 
	if( (out->tv_usec-=in->tv_usec)<0) 
	{ 
		--out->tv_sec; 
		out->tv_usec +=1000000; 
	} 
	out->tv_sec-=in->tv_sec; 
} 
/*------------- The End -----------*/
//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::processCommand (bool Option) 
{
	__BEGIN_TRY

	// ����� �ӽ������� ���� ����
	char header[szPacketHeader];
	PacketID_t packetID;
	PacketSize_t packetSize;
	// add by Coffee ���ӷ������
	SequenceSize_t packetSequence;

	Packet* pPacket = NULL;

	try {

		// �г�Ƽ�� �ް� �ִ� ����� �� ��� �� �κп��� ó�� ���ش�.
		// �г�Ƽ�� �޴� ��� � ���� ��Ȳ�� �߻����� �𸣹Ƿ�,
		// �����Ƿ���Ҫ�Ͽ���ǰID����
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

		// �Է¹��ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while (true) 
		{
			// �Է½�Ʈ������ ��Ŷ���ũ�⸸ŭ �о��.
			// ���� ������ ũ�⸸ŭ ��Ʈ������ ���� �� ���ٸ�,
			// Insufficient ���ܰ� �߻��ϰ�, ������ ����������.
			// NoSuch����. by sigi. 2002.5.4
			if (!m_pInputStream->peek(&header[0] , szPacketHeader))
			{
				Timeval currentTime;
				getCurrentTime(currentTime);
				if (currentTime >= m_ExpireTime)
				{
					filelog("GamePlayer.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

					throw DisconnectException("���� �ð����� �Է����� ���� ���, ������ �����մϴ�.");
				}

				break;
			}
			
			// ��Ŷ���̵� �� ��Ŷũ�⸦ �˾Ƴ���.
			// �̶� ��Ŷũ��� ����� �����Ѵ�.
			memcpy(&packetID   , &header[0] , szPacketID);	
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);
			// ��ȡ�������

			memcpy( &packetSequence , &header[szPacketID+szPacketSize] , szSequenceSize );
			// �жϷ�������Ƿ�Ϸ�
			if ( packetSequence!= m_Sequence)
			{
				filelog("SequenceError.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
					((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
					((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
				throw DisconnectException("������д���");
			}
			m_Sequence++;

			// �жϷ��ID�Ƿ�Ϸ�
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
				// ��Ŷ ������ �ùٸ��� �����Ѵ�.
				if (! g_pPacketValidator->isValidPacketID(getPlayerStatus() , packetID))
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}

//�������µ����ķǷ�����
				if (packetID==Packet::PACKET_GC_OTHER_STORE_INFO || packetID==Packet::PACKET_GC_MY_STORE_INFO)
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}
			
				// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size, RECV [%d],PacketSize[%d/%d],ID[%s],Host[%s]", 
						packetID, packetSize, g_pPacketFactoryManager->getPacketMaxSize(packetID),
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("too large packet size");
				}
			
				// �жϷ�������Ƿ�������
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					//throw InsufficientDataException();
					break;

				// ��ǰʱ��
				getCurrentTime(m_ExpireTime);
				m_ExpireTime.tv_sec += maxIdleSec;
			
				// ������� �Դٸ� �Է¹��ۿ��� ������ ��Ŷ �ϳ� �̻��� ����ִٴ� ���̴�.
				// ��Ŷ���丮�Ŵ����κ��� ��Ŷ���̵� ����ؼ� ��Ŷ ��Ʈ��ó�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ���丮�Ŵ������� ó���Ѵ�.
				pPacket = g_pPacketFactoryManager->createPacket(packetID);

				// ���� �� ��Ŷ��Ʈ��ó�� �ʱ�ȭ�Ѵ�.
				// ��Ŷ����Ŭ������ ���ǵ� read()�� virtual ��Ŀ���� ���ؼ� ȣ��Ǿ�
				// �ڵ������� �ʱ�ȭ�ȴ�.
				m_pInputStream->readPacket(pPacket);

				// ���� ��Ŷ�� ��Ŷ �����丮�� �� �ڿ� �ִ´�.
				m_PacketHistory.push_back(pPacket);

				// packet file log�� �����.
				if ( m_bPacketLog )
				{
					Timeval currentTime;
					getCurrentTime( currentTime );

					if ( currentTime >= m_PacketLogEndTime )
					{
						m_bPacketLog = false;
					}
					else
					{
						filelog( m_PacketLogFileName.c_str(), "%s", pPacket->toString().c_str() );
					}
				}

				//cout << "[" << (int)Thread::self() << "] execute before : " << pPacket->getPacketName().c_str() << endl;
	
				// ���� �� ��Ŷ��Ʈ��ó�� ������ ��Ŷ�ڵ鷯�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ�ڵ鷯�Ŵ������� ó���Ѵ�.
				try
				{
				#ifdef __PROFILE_PACKETS__
					
					beginProfileEx(	pPacket->getPacketName().c_str() );
					pPacket->execute(this);
					endProfileEx( pPacket->getPacketName().c_str() );

				#else
					verifySpeed(pPacket);
					pPacket->execute(this);
				#endif
				}  /*catch ( Throwable& t )
				{
					filelog( "GPPC.txt", "%s PacketID : %d", t.toString().c_str(), packetID );
					throw DisconnectException("GamePlayer Error 1!");
				}*/catch(...)
					{
						filelog("GamePlayerError.txt","Player:[%s], IP:[%s],MAC:[%02x%02x%02x%02x%02x%02x],Packet is:%s",m_ID.c_str(),getSocket()->getHost().c_str(),
							m_MacAddress[0],m_MacAddress[1],m_MacAddress[2],m_MacAddress[3],m_MacAddress[4],m_MacAddress[5],
							pPacket->toString().c_str());
						throw DisconnectException("GamePlayer Error 2!");
					}
				//cout << "[" << (int)Thread::self() << "] execute after : " << pPacket->getPacketName().c_str() << endl;

				// ��Ŷ�� nPacketHistorySize ����ŭ�� �����Ѵ�.
				while (m_PacketHistory.size() > nPacketHistorySize) 
				{
					Packet* oldPacket = m_PacketHistory.front();
					SAFE_DELETE(oldPacket);
					m_PacketHistory.pop_front();
				}
			} 
			catch (IgnorePacketException & igpe) 
			{
				// PacketValidator ���� ��Ŷ�� �����϶�� ������,
				// �Է½�Ʈ������ ��� ���������� �������� �ʵ��� �Ѵ�.

				// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size[Ignore], RECV [%d],PacketSize[%d],Name[%s],Host[%s]", 
																packetID, packetSize,
																((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
																((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
					throw InvalidProtocolException("too large packet sizeIgnore");
				}
			
				// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
				// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					throw InsufficientDataException();

				// ����Ÿ�� ��� ����������, �� ũ�⸸ŭ �����ϰ�,
				// �ٸ� ��Ŷ�� ó���ϵ��� �Ѵ�....
				m_pInputStream->skip(szPacketHeader + packetSize);

				// ���õ� ��Ŷ��, expire �� ������ ���� �ʰ� �ȴ�.
				// �� ��ȿ�� ��Ŷ���� ©���� �ʰ� ���ش�.
				// ���� �����丮���� ���� �ʴ´�.
			}
		}
	} 
	catch (InsufficientDataException & ide) 
	{
		// expire time �� �ʰ����� ��� ������ �����Ѵ�.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime)
		{
			filelog("GamePlayer.txt", "Timeout Diconnect. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

			throw DisconnectException("���� �ð����� �Է����� ���� ���, ������ �����մϴ�.");
		}
	}
	// �ּ�ó�� by sigi. 2002.5.14
	/*
	catch (InvalidProtocolException & ipe) 
	{
		// ������ ����������Ѿ� �Ѵ�. ���� �������??
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
// flush�� ���� �ٸ� �����忡�� ��� ���ۿ� sendPacket�� ȣ���ؼ��� �ȵȴ�.
// (�̷� ���� ������ ������� say�� ���ƿ��� �͹ۿ� ����.)
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::processOutput () 
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
		//cerr << "�ͼ��� ���µ�...... ���̴� ���ΰ�?" << (int)i << endl;
		throw DisconnectException("Pipe ������ �ı��� ������ ¥����");
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
{	
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		// packet file log�� �����.
		if ( m_bPacketLog )
		{
			Timeval currentTime;
			getCurrentTime( currentTime );

			if ( currentTime >= m_PacketLogEndTime )
			{
				m_bPacketLog = false;
			}
			else
			{
				filelog( m_PacketLogFileName.c_str(), "%s", pPacket->toString().c_str() );
			}
		}

		Player::sendPacket(pPacket);

		//cout << "GamePlayer::sendPacket() : " << pPacket->toString() << endl;
		//cout << "GamePlayer::sendPacket() PACKET SIZE : " << pPacket->getPacketSize() << endl;

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
		//throw DisconnectException("Pipe ������ �ı��� ������ ¥����");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// disconnect player
//
// (1) ũ��ó�� ������ ���, ������ �����ϰ� ��ε�ĳ��Ʈ�Ѵ�.
// (2) ũ��ó�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
void GamePlayer::disconnect (bool bDisconnected)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//--------------------------------------------------------------------------------
	// ũ��ó�� ������ ������ ��, �ֺ��� PC�鿡�� ��ε�ĳ��Ʈ���ش�.
	// �״��� ũ��ó�� DB�� �����Ѵ�.
	//--------------------------------------------------------------------------------
	string CreatureName = "";
	if (m_pCreature != NULL) 
	{
		CreatureName = m_pCreature->getName();

		try 
		{
			// GPS_NORMAL �� ��쿡��, ���� ũ��ó�� �� �ְ� �ȴ�.
			// *CAUTION*
			// Ȥ�� pushPC()�� ȣ��� �Ŀ� ������ ����Ǹ� ��� �ϳ�.. ��� ������ ���ɼ��� �ִ�.
			// �׷���, ó�� ��ƾ�� ������ �� ���캸�� �׷� ������ �� �ʿ䰡 ����.
			// ������ ������ �������, ���� ó���� �� ũ��ó�� ���� Ÿ�Ϸ� �ö� ����,
			// �ٽ� �÷��̾��� ó�������� ���ƿ��� �����̴�.
			if (getPlayerStatus() == GPS_NORMAL) 
			{
				//----------------------------------
				// ������ �����ϰ� ��ε�ĳ��Ʈ�Ѵ�.
				//----------------------------------
				Zone* pZone = m_pCreature->getZone();
				Assert(pZone != NULL);
				pZone->deleteQueuePC(m_pCreature);
				pZone->deleteCreature(m_pCreature , m_pCreature->getX() , m_pCreature->getY());
				//--------------------------------------------------------------------------------
				// ũ��ó�� �����Ѵ�.
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
    // ���̵� �����Ǿ��ٴ� ����, �α����� �̷�����ٴ� ���̴�.
	//--------------------------------------------------------------------------------
    if (m_ID != "")
    {
        Statement* pStmt1 = NULL;
        Statement* pStmt2 = NULL;

		BEGIN_DB
		{

//            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            // �α׿����� �����Ѵ�.
	      	//pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt1 = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();

			// LogOn�� GAME������ ��츸 LOGOFF�� �ٲ۴�. by sigi. 2002.5.15
            pStmt1->executeQuery("UPDATE Player SET LogOn='LOGOFF', LastLogoutDate=now() WHERE PlayerID = '%s' AND LogOn='GAME'" , m_ID.c_str());

			// LogoutPlayerData �� �߰��Ѵ�.
		//	addLogoutPlayerData(this);

			if (pStmt1->getAffectedRowCount()==0)
			{
				// �̹� LOGOFF�ų�
				// LOGON�����ΰ�?
				// �̷� �� ������? -_-;
			}

			// ���� by sigi. 2002.5.31
#if defined(__PAY_SYSTEM_LOGIN__) || defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
			if (isPayPlaying() || isPremiumPlay())
			{
				logoutPayPlay( m_ID );
			}
#endif


			SAFE_DELETE(pStmt1);

		}
		END_DB(pStmt1)
		BEGIN_DB
        {

			// IP ������ ������ �ش�.
            pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            pStmt2->executeQuery("DELETE FROM UserIPInfo WHERE Name = '%s'", CreatureName.c_str());

			SAFE_DELETE(pStmt2);
        }
		END_DB(pStmt2)
    }

	// login������ ����� client���� ������.
	// ������ LGIncomingConnectionOKHandler���� ó���ߴ�. by sigi. 2002.6.19
	if (m_pReconnectPacket!=NULL)
	{
		//cout << "[SendReconnect] " << m_pReconnectPacket->toString().c_str() << endl;

		try 
		{
			//sendPacket( m_pReconnectPacket );
			Player::sendPacket( m_pReconnectPacket );
			// ��� ���ۿ� �����ִ� ����Ÿ�� �����Ѵ�.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			// ����
		}
		
		SAFE_DELETE(m_pReconnectPacket);
	}


	// �Լ� ���κп��� ó���ߴµ�.. Ÿ�̹� ����(LogOn�̳� UserIPInfo ��)��
	// ���⼭ �����ְ�.. ������Ŷ~�� �������� �Ѵ�.
	if (bDisconnected == UNDISCONNECTED) 
	{
		try 
		{
			// Ŭ���̾�Ʈ���� GCDisconnect ��Ŷ�� �����Ѵ�.
			//GCDisconnect gcDisconnect;
			//sendPacket(gcDisconnect);

			// ��� ���ۿ� �����ִ� ����Ÿ�� �����Ѵ�.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			//cerr << "GamePlayer::disconnect() : GamePlayer::disconnect Exception Check!!" << endl;
			//cerr << t.toString() << endl;
		}
	}

	// ���� ������ �ݴ´�.
	m_pSocket->close();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// �ֱ� N ��°�� ��Ŷ�� �����Ѵ�.
// 
// N == 0 �� ���, ���� �ֱ��� ��Ŷ�� �����ϰ� �ȴ�.
//
// �ִ� nPacketHistorySize - 1 ���� ������ �� �ִ�. 
//
//////////////////////////////////////////////////////////////////////
Packet* GamePlayer::getOldPacket (uint prev)
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
// Ư�� ��Ŷ���̵� ���� ���� �ֱ��� ��Ŷ�� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
Packet* GamePlayer::getOldPacket (PacketID_t packetID)
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
{
	__BEGIN_TRY

	m_EventManager.addEvent(pEvent);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void GamePlayer::deleteEvent (Event::EventClass EClass)
{
	__BEGIN_TRY

	m_EventManager.deleteEvent(EClass);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
Event* GamePlayer::getEvent (Event::EventClass EClass)
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
{
	__BEGIN_TRY
	PacketID_t PacketID = pPacket->getPacketID();

	bool SpeedCheck = false;

	Timeval CurrentTime;
	getCurrentTime( CurrentTime );

	//////////////////////////////////////////////////////////////////////////
	// ���������� 
	// ���� 2007-6-25  kf_168@hotmail.com
	//

	if (PacketID == Packet::PACKET_CG_VERIFY_TIME )
	{
		if( m_SpeedVerify.tv_sec == 0 )
		{
			// ���δ��ȡ��������ʼ��ֵ,��ȡ��ǰʱ��+SpeedCheckDelya��Ϊ��ʼֵ
			// ���ü��ͨ�� SpeedCheck = true;
			m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;
			
			SpeedCheck = true;
		}
		else
		{
			// ���¿�ʼ���
			// �����ǰʱ������ϴμ��ʱ��+��ƫ��ֵ,����ͨ��
			if( CurrentTime.tv_sec > m_SpeedVerify.tv_sec - maxTimeGap )
			{
				m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

				SpeedCheck = true;
				// ������У��-1,�����ǰ����У�鳬��Ԥ��ֵ,�򷵻ؼ�
				m_VerifyCount = max(0, m_VerifyCount-1);
			}
			else
			{
				// �����´�У��ʱ��,ע��������ȡǰʱ��+�´�У��ʱ��.
				m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

				if( m_VerifyCount > maxVerifyCount )
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
	}
	//
	// ��������Ϳ����Խ���
	// Add by Coffee 2007-6-25 kf_168@hotmail.com
	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	// �����ƶ���������
	// Add by Coffee 2007-6-25 E-mail: kf_168@hotmail.com
	if (PacketID == Packet::PACKET_CG_MOVE)
	{
		if (CurrentTime <= m_MoveSpeedVerify)
		{
			// ʹ�ü���
		}
		//Timeval UseTimer=CurrentTime-m_MoveSpeedVerify;
		tv_sub(&CurrentTime,&m_MoveSpeedVerify);
		double rtt;
		// �Ժ���Ϊ��λ����rtt
		rtt =CurrentTime.tv_sec * 1000 + CurrentTime.tv_usec / 1000;
		
		getCurrentTime(m_MoveSpeedVerify);
		//add by viva for notice
		//filelog("MoveLog.txt", "MoveTime:=%.3f ms\n",rtt);
		//end
	}
	
	// End by Coffee 
	//////////////////////////////////////////////////////////////////////////
	
	/*
	// ũ��ó�� ���ǵ带 �޾ƿ´�.
	if (m_pCreature == NULL || pPacket == NULL) {
		return true;
	}

	// ���� �ð� ������ �� ���� ��Ŷ�� ���ʹ� ���ƿ��� ������ ¥����.
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
			// ���� �ð��̶� ���� �ð��̶� üũ�ؼ� �� ���� �ð��� ��Ŷ�� ���ƿ����� �̰� ġ�ʹ�.
			if (VerifyTime <= m_MoveSpeedVerify) {
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			// ������ ���갡 ���� ���� ���ƿ� �� �ִ� ������ �ð��� ������ �д�.
			// ���� ����Ŭ�� Ÿ�� �ִٸ� �̵��ӵ��� �پ���.

			BYTE RealSpeed = 0;
			if (pSlayer->hasRideMotorcycle()) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // �������Ŭ�� �ƴϴ�.
			{
				//RealSpeed = 4;
				RealSpeed = 2;
			}

			// ���� �� �� �ִ� �ð��� �����Ѵ�.
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
			// ���⸦ ������ ��� �ִ��� üũ�Ѵ�.
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			Item::ItemClass IClass = Item::ITEM_CLASS_SKULL;
			if (pItem != NULL) {
				IClass = pItem->getItemClass();
			} 

			getCurrentTime(m_AttackSpeedVerify);
			getCurrentTime(m_MoveSpeedVerify);

			BYTE RealSpeed = 0;
			// ���ο� ���ǵ�
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
					// �⺻ ���� 875
					default :
						RealSpeed = 8;
						break;
				}
			} 
			else if (Speed == 1) // ��� ���ǵ�
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
					// �⺻ ���� 875
					default :
						RealSpeed = 8;
						break;

				}
			} 
			else // �н�Ʈ ���ǵ�
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

			// ���ǵ� ��ȭ ��å
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
			// ���� �ð��̶� ���� �ð��̶� üũ�ؼ� �� ���� �ð��� ��Ŷ�� ���ƿ����� �̰� ġ�ʹ�.
			if (VerifyTime <= m_MoveSpeedVerify) 
			{
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			BYTE RealSpeed = 0;
			// ������ ���갡 ���� ���� ���ƿ� �� �ִ� ������ �ð��� ������ �д�.
			// ���� ������ �ϰ� �ִٸ� �ӵ��� ��������. �ʴ� �� Ÿ���� �̵� �Ѵ�.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // ��� ���¿��� �ʴ� ��Ÿ���� �̵��Ѵ�.
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
			if (Speed == 0) // ���ο� ���ǵ� 875
			{
				RealSpeed = 8;
			} 
			else if (Speed == 1) // ��� ���ǵ� 875
			{
				RealSpeed = 8;
			} 
			else // �н�Ʈ ���ǵ� 812
			{
				RealSpeed = 8;
			}

			// ���ǵ� ��ȭ ��å
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
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
//		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt   = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();

		pResult = pStmt->executeQuery("SELECT SpecialEventCount FROM Player WHERE PlayerID='%s'", m_ID.c_str());

		if (pResult->getRowCount() != 0)
		{
			pResult->next();
			m_SpecialEventCount = pResult->getDWORD(1);
		}
		else
		{
			SAFE_DELETE(pStmt);
			throw ("GamePlayer::loadSpecialEventCount() : unable to dispatch data");
			return;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

void GamePlayer::saveSpecialEventCount(void)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
//		pStmt = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();

		pStmt->executeQuery("UPDATE Player SET SpecialEventCount=%d WHERE PlayerID='%s'", m_SpecialEventCount, m_ID.c_str());
		SAFE_DELETE(pStmt);	
	}
	END_DB(pStmt);

	__END_CATCH
}

bool    GamePlayer::sendBillingLogin() 
{
	__BEGIN_TRY

	if (!m_ID.empty() && m_ID!="NONE")
	{
		Timeval currentTime;
		getCurrentTime(currentTime);

		if (currentTime > m_BillingNextLoginRequestTime)
		{
			g_pBillingPlayerManager->sendPayLogin( this );

			Timeval afterTime;
			getCurrentTime( afterTime );

			// 1�� �̻� �ɸ��� �α� �����.
			if ( afterTime.tv_sec > currentTime.tv_sec + 1 )
			{
				filelog( "billingLoginTime.txt", "PlayerID : %s, CallTime : %d sec, Try : %d", m_ID.c_str(), (int)(afterTime.tv_sec - currentTime.tv_sec), m_BillingLoginRequestCount );
			}

			// PayLogin ��û�� ȸ�� ���
			m_BillingLoginRequestCount ++;

			// 60�� �� �ٽ� üũ�Ѵ�.
			m_BillingNextLoginRequestTime.tv_sec = currentTime.tv_sec + 60;
		}

		return true;
	}

	return false;

	__END_CATCH
}

void GamePlayer::sendCBillingPayInfo()
{
	__BEGIN_TRY

	char m[200];
	if ( m_CBPlayerType == CBILLING_PLAYER_TYPE_MONTHLY )
	{
		VSDate currentDate;
		currentDate = VSDate::currentDate();

		sprintf( m, g_pStringPool->c_str( STRID_CB_MONTHLY_PLAYER ),
						m_CBEndDateTime.date().year(),
						m_CBEndDateTime.date().month(),
						m_CBEndDateTime.date().day(),
						currentDate.year(),
						currentDate.month(),
						currentDate.day() );

		GCSystemMessage msg;
		msg.setMessage( m );

		sendPacket( &msg );
	}
	else if ( m_CBPlayerType == CBILLING_PLAYER_TYPE_POINT )
	{
		sprintf( m, g_pStringPool->c_str( STRID_CB_POINT_PLAYER ), m_CBLeftTime / 10 );

		GCSystemMessage msg;
		msg.setMessage( m );

		sendPacket( &msg );
	}

	__END_CATCH
}

// ��ȣȭ �ڵ带 �����Ѵ�.
void GamePlayer::setEncryptCode()
{
    __BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	Assert(m_pCreature!=NULL);

	// �ϴ��� ObjectID�� �̿��Ѵ�.
	//ObjectID_t 	objectID 	= m_pCreature->getObjectID();

	// ������ ������ �ϵ��� �����Ѵ�.
//	ZoneID_t 	zoneID 		= m_pCreature->getZone()->getZoneID();
//	static int	serverID	= g_pConfig->getPropertyInt("ServerID");

//	if (objectID!=0)
//	{
		//uchar code = (uchar)(objectID / zoneID + objectID);
		//uchar code = (uchar)( ( ( zoneID >> 8 ) ^ zoneID ) ^ ( ( serverID + 1 ) << 4 ) );
		uchar code = m_pCreature->getZone()->getEncryptCode();

#ifdef __ACTIVE_SERVICE_DEADLINE__
		// ���� �ٺ� ����� �ڵ�
		VSDate date = VSDate::currentDate();
		// 2003�� 1�� �̻��� ���: 2003, 0
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

void GamePlayer::kickPlayer( uint nSeconds, uint KickMessageType )
{
	__BEGIN_TRY

	// �̹� EventKick �� �ִٸ� �����Ѵ�.
	if ( m_EventManager.getEvent( Event::EVENT_CLASS_KICK ) != NULL )
		return;

	EventKick* pEventKick = new EventKick( this );
	pEventKick->setDeadline( nSeconds * 10 );
	addEvent( pEventKick );

	// �� ���Ŀ� ©����..�� �����ش�.
	GCKickMessage gcKickMessage;
	gcKickMessage.setType( KickMessageType );
	gcKickMessage.setSeconds( nSeconds );
	sendPacket( &gcKickMessage );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////
// PaySystem ����
//////////////////////////////////////////////////////////////////
bool GamePlayer::loginPayPlay( PayType payType, const string& PayPlayDate, int PayPlayHours, uint payPlayFlag, const string& ip, const string& playerID )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	return PaySystem::loginPayPlay( payType, PayPlayDate, PayPlayHours, payPlayFlag, ip, playerID );
#endif
	__END_CATCH
}

bool GamePlayer::loginPayPlay( const string& ip, const string& playerID )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	bool bRet = PaySystem::loginPayPlay( ip, playerID );

	if ( bRet )
		setPCRoomLottoStartTime();

	return bRet;
#endif
	__END_CATCH
}

bool GamePlayer::updatePayPlayTime( const string& playerID, const VSDateTime& currentDateTime, const Timeval& currentTime )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	checkPCRoomLotto( currentTime );

	return PaySystem::updatePayPlayTime( playerID, currentDateTime, currentTime );
#endif
	__END_CATCH
}

void GamePlayer::logoutPayPlay( const string& playerID, bool bClear, bool bDecreaseTime )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	if ( !BillingPlayerInfo::isBillingPlayAvaiable() )
		setPremiumPlay( false );
#else
	savePCRoomLottoTime();

	PaySystem::logoutPayPlay( playerID, bClear, bDecreaseTime );
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
// ������ ��踦 ���ؼ� 
// UserInfo DB�� LogoutPlayerData�� Logout�� ����ڸ� �߰��Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////
void addLogoutPlayerData(Player* pPlayer)
{

	Statement* pStmt = NULL;

	pStmt = g_pDatabaseManager->getUserInfoConnection()->createStatement();

	// ���� ��� ���� ������ �Է��Ѵ�.
	BEGIN_DB
	{
		string ID = pPlayer->getID();
		string ip = pPlayer->getSocket()->getHost();

		// ���� ���� �ð��� ����.
		int year, month, day, hour, minute, second;
		getCurrentTimeEx(year, month, day, hour, minute, second);
		string currentDT = VSDateTime::currentDateTime().toDateTime();

		StringStream sql;
		sql << "INSERT INTO USERINFO.LogoutPlayerData (PlayerID,IP,Date,Time) VALUES ('"
			<< ID << "','" << ip << "','"
			<< currentDT.substr( 0, 10 ).c_str() << "','"
			<< currentDT.substr( 11 ).c_str() << "')";

		pStmt->executeQueryString(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
}

void GamePlayer::setPCRoomLottoStartTime()
{
	if ( !g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if ( !m_bPCRoomPlay )
		return;

	m_PCRoomLottoStartTime.tv_sec = m_PayPlayStartTime.tv_sec - m_PCRoomLottoSumTime;
}

void GamePlayer::savePCRoomLottoTime()
{
	if ( !g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if ( !m_bPCRoomPlay )
		return;

	Timeval currentTime;
	getCurrentTime( currentTime );

	m_PCRoomLottoSumTime = currentTime.tv_sec - m_PCRoomLottoStartTime.tv_sec;
	m_PCRoomLottoStartTime.tv_sec = 0;
}

void GamePlayer::checkPCRoomLotto( const Timeval& currentTime )
{
	if ( !g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if ( !m_bPCRoomPlay )
		return;

	if ( m_PCRoomLottoStartTime.tv_sec == 0 )
	{
		m_PCRoomLottoStartTime.tv_sec = currentTime.tv_sec - m_PCRoomLottoSumTime;
	}

	int time = currentTime.tv_sec - m_PCRoomLottoStartTime.tv_sec;	

	if ( time >= PCRoomLottoSec )
	{
		giveLotto();

		// �ٽ� �ð��� �ʱ�ȭ�Ѵ�.
		m_PCRoomLottoStartTime.tv_sec = currentTime.tv_sec;
		m_PCRoomLottoSumTime = 0;
	}
}

void GamePlayer::giveLotto()
{
	if ( m_pCreature == NULL )
		return;

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		static uint DimensionID	= g_pConfig->getPropertyInt( "Dimension" );
		static uint WorldID		= g_pConfig->getPropertyInt( "WorldID" );
		string PlayerID		= getID();
		string Name			= m_pCreature->getName();
		Race_t Race			= m_pCreature->getRace();
		int Amount			= 0;
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		pResult = pStmt->executeQuery( "SELECT Amount FROM PCRoomLottoObject WHERE PlayerID = '%s' AND Name = '%s' AND DimensionID = %u AND WorldID = %u",
										PlayerID.c_str(), Name.c_str(), DimensionID, WorldID );

		if ( pResult->next() )
		{
			Amount = pResult->getInt( 1 );

			if ( Amount < PCRoomLottoMaxAmount )
			{
				pStmt->executeQuery( "UPDATE PCRoomLottoObject SET Amount = %d WHERE PlayerID = '%s' AND Name = '%s' AND DimensionID = %u AND WorldID = %u",
										Amount + 1, PlayerID.c_str(), Name.c_str(), DimensionID, WorldID );
			}
		}
		else
		{
			// ������ ������. ���� �־��ش�.
			pStmt->executeQuery( "INSERT INTO PCRoomLottoObject VALUES ( 0, %u, '%s', %u, %u, '%s', %u, 1 )",
									m_PCRoomID, PlayerID.c_str(), DimensionID, WorldID, Name.c_str(), Race );
		}

		if ( Amount < PCRoomLottoMaxAmount )
		{
			char msg[100];
			sprintf( msg, g_pStringPool->c_str( STRID_GIVE_LOTTO ), Amount + 1 ); 

			GCSystemMessage gcMsg;
			gcMsg.setMessage( msg );
			sendPacket( &gcMsg );

			if ( Amount >= PCRoomLottoMaxAmount - 1 )
			{
				gcMsg.setMessage( g_pStringPool->getString( STRID_CANNOT_GIVE_LOTTO ) );
				sendPacket( &gcMsg );
			}
		}
	}
	END_DB( pStmt )
}

bool GamePlayer::startPacketLog( uint sec )
{
	if ( m_pCreature == NULL )
		return false;

	m_bPacketLog = true;
	getCurrentTime( m_PacketLogEndTime );
	m_PacketLogEndTime.tv_sec += sec;

	char filename[100];
	sprintf( filename, "log/%s.log", m_pCreature->getName().c_str() );
	m_PacketLogFileName = filename;

	return true;
}

void GamePlayer::logLoginoutDateTime()
{
	if ( m_pCreature == NULL )
		return;

	// DimensionID ���ϱ�
	uint dimensionID = g_pConfig->getPropertyInt("Dimension");
	if ( g_pConfig->getPropertyInt("IsNetMarble") == 0 )
	{
		// �ݸ��� �� ��쿣 2
		dimensionID = 2;
	}

	// WorldID
	uint worldID = g_pConfig->getPropertyInt("WorldID");

	// ���� �ڵ�
	uint racecode;
	uint str,dex,inte;
	if ( m_pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
		Assert( pSlayer != NULL );

		racecode = (uint)pSlayer->getHighestSkillDomain();

		str = pSlayer->getSTR();
		dex = pSlayer->getDEX();
		inte = pSlayer->getINT();
	}
	else if ( m_pCreature->isVampire() )
	{
		// �����̾��  10
		racecode = 10;

		Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
		Assert( pVampire != NULL );

		str = pVampire->getSTR();
		dex = pVampire->getDEX();
		inte = pVampire->getINT();
	}
	else if ( m_pCreature->isOusters() )
	{
		// �ƿ콺����� 20
		racecode = 20;

		Ousters* pOusters = dynamic_cast<Ousters*>(m_pCreature);
		Assert( pOusters != NULL );

		str = pOusters->getSTR();
		dex = pOusters->getDEX();
		inte = pOusters->getINT();
	}
	else
	{
		return;
	}

	// ����
	uint level = (uint)m_pCreature->getLevel();

	// �α׾ƿ� �ð�. ���� �ð�
	VSDateTime logoutDateTime = VSDateTime::currentDateTime();

	// filename
	char filename[20];
	sprintf( filename, "log/%s.txt", logoutDateTime.toStringforWeb().c_str() );

	try
	{
		ofstream file( filename, ios::out | ios::app );
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

