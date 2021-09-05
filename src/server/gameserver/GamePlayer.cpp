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
// ¸ðµç packetµé¿¡ ´ëÇØ¼­ profilingÇÑ´Ù. by sigi. 2002.5.6
//
// ´Ü, ÀÌ°É »ç¿ëÇÏ±â À§ÇØ¼­´Â 
// Profile.h¿¡ MAX_PROFILE_SAMPLES += 300À» ÇØÁà¾ß ÇÑ´Ù.
//////////////////////////////////////////////////////////////////////////////
//#define __PROFILE_PACKETS__

#ifdef __PROFILE_PACKETS__
	#include "Profile.h"
#endif

// by sigi. 2002.11.12
const int defaultGamePlayerInputStreamSize = 1024;
const int defaultGamePlayerOutputStreamSize = 20480;

static int maxIdleSec         = 60* 5;		// ÎÞ¶¯×÷Ê±¼ä×î´ó±£³ÖÁ¬½ÓÊ±¼ä 60 * 5 = 300Ãë(5·Ö)
//static int maxSpeedVerifyTime = 2;  		// 0.3 ÃÊ
static int maxVerifyCount     = 3;      	// ×î´ó´íÎóÐ£Ñé´ÎÊý 3´Î
static int maxTimeGap         =	5;			// Ê±¼äÐ£ÑéÆ«²îÃëÊý º«·þÎª5´Î ÐÞ¸ÄÎª8´Î
static int SpeedCheckDelay    = 60;			// Ê±¼äÐ£Ñé¼ä¸ô60ÃëÒ»´Î

const int PCRoomLottoSec = 3600;			// 3600 ÃÊ. 1½Ã°£
const int PCRoomLottoMaxAmount = 3;			// ÇÑ¹ø¿¡ ½×ÀÏ ¼ö ÀÖ´Â ÃÖ´ë º¹±Ç¼ö
// CLLoginHandler.cpp¿¡ ÀÖ´Â ÇÔ¼ö´Ù.
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

    // ÇöÀç ½Ã°£À» ¹Þ¾Æ¿Â´Ù
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

	// °´Ã¼°¡ »ý¼ºµÈ ½ÃÁ¡À» ·Î±×ÀÎÇÑ ½Ã°£À¸·Î º»´Ù.
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

	// ±× ¾î¶² ÇÃ·¹ÀÌ¾î °´Ã¼°¡ »èÁ¦µÉ ¶§¿¡µµ, ±× »óÅÂ´Â ·Î±×¾Æ¿ôÀÌ¾î¾ß ÇÑ´Ù.
	// Áï ¾î¶² ÇÃ·¹ÀÌ¾î¸¦ Á¢¼Ó Á¾·á ½ÃÅ°·Á¸é, ±× »óÅÂ¸¦ ·Î±×¾Æ¿ôÀ¸·Î ¸¸µé¾î¾ß ÇÑ´Ù.
	Assert(m_PlayerStatus == GPS_END_SESSION);

	try
	{
		// Delete creature
		if (m_pCreature != NULL) 
		{
			// ¼º¼­ ¶³¾î¶ß¸®±â
			if ( m_pCreature->hasRelicItem() )
			{
				dropRelicToZone( m_pCreature, false );
			}

			dropFlagToZone( m_pCreature, false );
			dropSweeperToZone( m_pCreature );

			//try 
			//{
				// NoSuchÁ¦°Å. by sigi. 2002.5.2
				g_pPCFinder->deleteCreature(m_pCreature->getName());
			//} 
			//catch (NoSuchElementException & t) 
			//{
			//}

		#ifdef __CONNECT_BILLING_SYSTEM__
			// Pay Á¾·áÇÑ´Ù°í ¾Ë·ÁÁØ´Ù. by sigi. 2002.11.18
			if ( isBillingPlayAvaiable() && !m_bMetroFreePlayer )	// by sigi. 2002.11.23
			{
				g_pBillingPlayerManager->sendPayLogout( this );
			}
		#elif defined(__CONNECT_CBILLING_SYSTEM__ )
			// Áß±¹ ºô¸µ ¼­¹ö¿¡ logout ÆÐÅ¶À» º¸³½´Ù.
			g_pCBillingPlayerManager->sendLogout( this );
		#endif

			Statement* pStmt = NULL;

			// ±æµå ÇöÀç Á¢¼Ó ¸â¹ö ¸®½ºÆ®¿¡¼­ »èÁ¦ÇÑ´Ù.
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
						
						// µðºñ¿¡ ¾÷µ¥ÀÌÆ® ÇÑ´Ù.
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

						// µðºñ¿¡ ¾÷µ¥ÀÌÆ® ÇÑ´Ù.
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

						// µðºñ¿¡ ¾÷µ¥ÀÌÆ® ÇÑ´Ù.
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

	// ÆÐÅ¶À» »èÁ¦ÇÑ´Ù.
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
// Á½¸ötimeval½á¹¹Ïà¼õ
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

	// Çì´õ¸¦ ÀÓ½ÃÀúÀåÇÒ ¹öÆÛ »ý¼º
	char header[szPacketHeader];
	PacketID_t packetID;
	PacketSize_t packetSize;
	// add by Coffee Ôö¼Ó·â°üÐòÁÐ
	SequenceSize_t packetSequence;

	Packet* pPacket = NULL;

	try {

		// ÆÐ³ÎÆ¼¸¦ ¹Þ°í ÀÖ´Â »ç¿ëÀÚ ÀÏ °æ¿ì ÀÌ ºÎºÐ¿¡¼­ Ã³¸® ÇØÁØ´Ù.
		// ÆÐ³ÎÆ¼¸¦ ¹Þ´Â °æ¿ì ¾î¶² ¿¹¿Ü »óÈ²ÀÌ ¹ß»ýÇÒÁö ¸ð¸£¹Ç·Î,
		// ¾ö¶ÏÊÇ·ñÐèÒª¶Ï¿ªµ±Ç°IDÁ¬½Ó
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

		// ÀÔ·Â¹öÆÛ¿¡ µé¾îÀÖ´Â ¿ÏÀüÇÑ ÆÐÅ¶µéÀ» ¸ðÁ¶¸® Ã³¸®ÇÑ´Ù.
		while (true) 
		{
			// ÀÔ·Â½ºÆ®¸²¿¡¼­ ÆÐÅ¶Çì´õÅ©±â¸¸Å­ ÀÐ¾îº»´Ù.
			// ¸¸¾à ÁöÁ¤ÇÑ Å©±â¸¸Å­ ½ºÆ®¸²¿¡¼­ ÀÐÀ» ¼ö ¾ø´Ù¸é,
			// Insufficient ¿¹¿Ü°¡ ¹ß»ýÇÏ°í, ·çÇÁ¸¦ ºüÁ®³ª°£´Ù.
			// NoSuchÁ¦°Å. by sigi. 2002.5.4
			if (!m_pInputStream->peek(&header[0] , szPacketHeader))
			{
				Timeval currentTime;
				getCurrentTime(currentTime);
				if (currentTime >= m_ExpireTime)
				{
					filelog("GamePlayer.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

					throw DisconnectException("ÀÏÁ¤ ½Ã°£µ¿¾È ÀÔ·ÂÇÏÁö ¾ÊÀ» °æ¿ì, ¿¬°áÀ» Á¾·áÇÕ´Ï´Ù.");
				}

				break;
			}
			
			// ÆÐÅ¶¾ÆÀÌµð ¹× ÆÐÅ¶Å©±â¸¦ ¾Ë¾Æ³½´Ù.
			// ÀÌ¶§ ÆÐÅ¶Å©±â´Â Çì´õ¸¦ Æ÷ÇÔÇÑ´Ù.
			memcpy(&packetID   , &header[0] , szPacketID);	
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);
			// ¶ÁÈ¡·â°üÐòÁÐ

			memcpy( &packetSequence , &header[szPacketID+szPacketSize] , szSequenceSize );
			// ÅÐ¶Ï·â°üÐòÁÐÊÇ·ñºÏ·¨
			if ( packetSequence!= m_Sequence)
			{
				filelog("SequenceError.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
					((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
					((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
				throw DisconnectException("·â°üÐòÁÐ´íÎó");
			}
			m_Sequence++;

			// ÅÐ¶Ï·â°üIDÊÇ·ñºÏ·¨
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
				// ÆÐÅ¶ ¼ø¼­°¡ ¿Ã¹Ù¸¥Áö °ËÁõÇÑ´Ù.
				if (! g_pPacketValidator->isValidPacketID(getPlayerStatus() , packetID))
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}

//Ìø¹ýµ¼ÖÂµ±»úµÄ·Ç·¨±¨ÎÄ
				if (packetID==Packet::PACKET_GC_OTHER_STORE_INFO || packetID==Packet::PACKET_GC_MY_STORE_INFO)
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}
			
				// ÆÐÅ¶ Å©±â°¡ ³Ê¹« Å©¸é ÇÁ·ÎÅäÄÝ ¿¡·¯·Î °£ÁÖÇÑ´Ù.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size, RECV [%d],PacketSize[%d/%d],ID[%s],Host[%s]", 
						packetID, packetSize, g_pPacketFactoryManager->getPacketMaxSize(packetID),
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("too large packet size");
				}
			
				// ÅÐ¶Ï·â°üÊý¾ÝÊÇ·ñ½ÓÊÕÍê±Ï
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					//throw InsufficientDataException();
					break;

				// µ±Ç°Ê±¼ä
				getCurrentTime(m_ExpireTime);
				m_ExpireTime.tv_sec += maxIdleSec;
			
				// ¿©±â±îÁö ¿Ô´Ù¸é ÀÔ·Â¹öÆÛ¿¡´Â ¿ÏÀüÇÑ ÆÐÅ¶ ÇÏ³ª ÀÌ»óÀÌ µé¾îÀÖ´Ù´Â ¶æÀÌ´Ù.
				// ÆÐÅ¶ÆÑÅä¸®¸Å´ÏÀú·ÎºÎÅÍ ÆÐÅ¶¾ÆÀÌµð¸¦ »ç¿ëÇØ¼­ ÆÐÅ¶ ½ºÆ®·°Ã³¸¦ »ý¼ºÇÏ¸é µÈ´Ù.
				// ÆÐÅ¶¾ÆÀÌµð°¡ Àß¸øµÉ °æ¿ì´Â ÆÐÅ¶ÆÑÅä¸®¸Å´ÏÀú¿¡¼­ Ã³¸®ÇÑ´Ù.
				pPacket = g_pPacketFactoryManager->createPacket(packetID);

				// ÀÌÁ¦ ÀÌ ÆÐÅ¶½ºÆ®·°Ã³¸¦ ÃÊ±âÈ­ÇÑ´Ù.
				// ÆÐÅ¶ÇÏÀ§Å¬·¡½º¿¡ Á¤ÀÇµÈ read()°¡ virtual ¸ÞÄ¿´ÏÁò¿¡ ÀÇÇØ¼­ È£ÃâµÇ¾î
				// ÀÚµ¿ÀûÀ¸·Î ÃÊ±âÈ­µÈ´Ù.
				m_pInputStream->readPacket(pPacket);

				// ÇöÀç ÆÐÅ¶À» ÆÐÅ¶ È÷½ºÅä¸®ÀÇ ¸Ç µÚ¿¡ ³Ö´Â´Ù.
				m_PacketHistory.push_back(pPacket);

				// packet file log¸¦ ³²±ä´Ù.
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
	
				// ÀÌÁ¦ ÀÌ ÆÐÅ¶½ºÆ®·°Ã³¸¦ °¡Áö°í ÆÐÅ¶ÇÚµé·¯¸¦ ¼öÇàÇÏ¸é µÈ´Ù.
				// ÆÐÅ¶¾ÆÀÌµð°¡ Àß¸øµÉ °æ¿ì´Â ÆÐÅ¶ÇÚµé·¯¸Å´ÏÀú¿¡¼­ Ã³¸®ÇÑ´Ù.
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

				// ÆÐÅ¶À» nPacketHistorySize °³¸¸Å­¸¸ ÀúÀåÇÑ´Ù.
				while (m_PacketHistory.size() > nPacketHistorySize) 
				{
					Packet* oldPacket = m_PacketHistory.front();
					SAFE_DELETE(oldPacket);
					m_PacketHistory.pop_front();
				}
			} 
			catch (IgnorePacketException & igpe) 
			{
				// PacketValidator ¿¡¼­ ÆÐÅ¶À» ¹«½ÃÇÏ¶ó°í ÇßÀ¸´Ï,
				// ÀÔ·Â½ºÆ®¸²¿¡¼­ ¸ðµÎ Áö¿ö¹ö¸®°í ½ÇÇàÇÏÁö ¾Êµµ·Ï ÇÑ´Ù.

				// ÆÐÅ¶ Å©±â°¡ ³Ê¹« Å©¸é ÇÁ·ÎÅäÄÝ ¿¡·¯·Î °£ÁÖÇÑ´Ù.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size[Ignore], RECV [%d],PacketSize[%d],Name[%s],Host[%s]", 
																packetID, packetSize,
																((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
																((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
					throw InvalidProtocolException("too large packet sizeIgnore");
				}
			
				// ÀÔ·Â¹öÆÛ³»¿¡ ÆÐÅ¶Å©±â¸¸Å­ÀÇ µ¥ÀÌÅ¸°¡ µé¾îÀÖ´ÂÁö È®ÀÎÇÑ´Ù.
				// ÃÖÀûÈ­½Ã break ¸¦ »ç¿ëÇÏ¸é µÈ´Ù. (¿©±â¼­´Â ÀÏ´Ü exceptionÀ» ¾µ °ÍÀÌ´Ù.)
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					throw InsufficientDataException();

				// µ¥ÀÌÅ¸°¡ ¸ðµÎ µµÂøÇßÀ¸¸é, ±× Å©±â¸¸Å­ ¹«½ÃÇÏ°í,
				// ´Ù¸¥ ÆÐÅ¶À» Ã³¸®ÇÏµµ·Ï ÇÑ´Ù....
				m_pInputStream->skip(szPacketHeader + packetSize);

				// ¹«½ÃµÈ ÆÐÅ¶Àº, expire ¿¡ ¿µÇâÀ» ÁÖÁö ¾Ê°Ô µÈ´Ù.
				// Áï À¯È¿ÇÑ ÆÐÅ¶¸¸ÀÌ Â©¸®Áö ¾Ê°Ô ÇØÁØ´Ù.
				// ¶ÇÇÑ È÷½ºÅä¸®¿¡µµ µé¾î°¡Áö ¾Ê´Â´Ù.
			}
		}
	} 
	catch (InsufficientDataException & ide) 
	{
		// expire time À» ÃÊ°úÇßÀ» °æ¿ì ¿¬°áÀ» Á¾·áÇÑ´Ù.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime)
		{
			filelog("GamePlayer.txt", "Timeout Diconnect. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

			throw DisconnectException("ÀÏÁ¤ ½Ã°£µ¿¾È ÀÔ·ÂÇÏÁö ¾ÊÀ» °æ¿ì, ¿¬°áÀ» Á¾·áÇÕ´Ï´Ù.");
		}
	}
	// ÁÖ¼®Ã³¸® by sigi. 2002.5.14
	/*
	catch (InvalidProtocolException & ipe) 
	{
		// Á¢¼ÓÀ» °­Á¦Á¾·á½ÃÄÑ¾ß ÇÑ´Ù. ¹«½¼ ¹æ¹ýÀ¸·Î??
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
// flushÇÒ µ¿¾È ´Ù¸¥ ¾²·¹µå¿¡¼­ Ãâ·Â ¹öÆÛ¿¡ sendPacketÀ» È£ÃâÇØ¼­´Â ¾ÈµÈ´Ù.
// (ÀÌ·² °æ¿ì´Â ¼­¹ö°£ Åë½ÅÀ¸·Î say°¡ ³¯¾Æ¿À´Â °Í¹Û¿¡ ¾ø´Ù.)
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
		//cerr << "ÀÍ¼Á¼Ç ³µ´Âµ¥...... ¾ÆÀÌ´Â ¸îÀÎ°í?" << (int)i << endl;
		throw DisconnectException("Pipe ¿¬°áÀÇ ÆÄ±«·Î Á¢¼ÓÀ» Â¥¸¥´Ù");
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
		// packet file log¸¦ ³²±ä´Ù.
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
		//throw DisconnectException("Pipe ¿¬°áÀÇ ÆÄ±«·Î Á¢¼ÓÀ» Â¥¸¥´Ù");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// disconnect player
//
// (1) Å©¸®Ã³°¡ Á¸ÀçÇÒ °æ¿ì, Á¸¿¡¼­ »èÁ¦ÇÏ°í ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
// (2) Å©¸®Ã³¸¦ ÀúÀåÇÑ´Ù.
//
//--------------------------------------------------------------------------------
void GamePlayer::disconnect (bool bDisconnected)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//--------------------------------------------------------------------------------
	// Å©¸®Ã³¸¦ Á¸¿¡¼­ »èÁ¦ÇÑ ÈÄ, ÁÖº¯ÀÇ PCµé¿¡°Ô ºê·ÎµåÄ³½ºÆ®ÇØÁØ´Ù.
	// ±×´ÙÀ½ Å©¸®Ã³¸¦ DB¿¡ ÀúÀåÇÑ´Ù.
	//--------------------------------------------------------------------------------
	string CreatureName = "";
	if (m_pCreature != NULL) 
	{
		CreatureName = m_pCreature->getName();

		try 
		{
			// GPS_NORMAL ÀÎ °æ¿ì¿¡¸¸, Á¸¿¡ Å©¸®Ã³°¡ µé¾î°¡ ÀÖ°Ô µÈ´Ù.
			// *CAUTION*
			// È¤½Ã pushPC()°¡ È£ÃâµÈ ÈÄ¿¡ ¿¬°áÀÌ Á¾·áµÇ¸é ¾î¶»°Ô ÇÏ³ª.. ¶ó°í °ÆÁ¤ÇÒ °¡´É¼ºµµ ÀÖ´Ù.
			// ±×·¯³ª, Ã³¸® ·çÆ¾ÀÇ ¼ø¼­¸¦ Àß »ìÆìº¸¸é ±×·± °ÆÁ¤À» ÇÒ ÇÊ¿ä°¡ ¾ø´Ù.
			// ¾îÂ÷ÇÇ ¿¬°áÀÌ ²÷±â´õ¶óµµ, Á¸ÀÌ Ã³¸®µÈ ÈÄ Å©¸®Ã³°¡ ½ÇÁ¦ Å¸ÀÏ·Î ¿Ã¶ó°£ ´ÙÀ½,
			// ´Ù½Ã ÇÃ·¹ÀÌ¾îÀÇ Ã³¸®·çÇÁ°¡ µ¹¾Æ¿À±â ¶§¹®ÀÌ´Ù.
			if (getPlayerStatus() == GPS_NORMAL) 
			{
				//----------------------------------
				// Á¸¿¡¼­ »èÁ¦ÇÏ°í ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
				//----------------------------------
				Zone* pZone = m_pCreature->getZone();
				Assert(pZone != NULL);
				pZone->deleteQueuePC(m_pCreature);
				pZone->deleteCreature(m_pCreature , m_pCreature->getX() , m_pCreature->getY());
				//--------------------------------------------------------------------------------
				// Å©¸®Ã³¸¦ ÀúÀåÇÑ´Ù.
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
    // ¾ÆÀÌµð°¡ ¼³Á¤µÇ¾ú´Ù´Â ¶æÀº, ·Î±×ÀÎÀÌ ÀÌ·ç¾îÁ³´Ù´Â ¶æÀÌ´Ù.
	//--------------------------------------------------------------------------------
    if (m_ID != "")
    {
        Statement* pStmt1 = NULL;
        Statement* pStmt2 = NULL;

		BEGIN_DB
		{

//            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            // ·Î±×¿ÀÇÁ·Î º¯°æÇÑ´Ù.
	      	//pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt1 = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();

			// LogOnÀÌ GAME»óÅÂÀÎ °æ¿ì¸¸ LOGOFF·Î ¹Ù²Û´Ù. by sigi. 2002.5.15
            pStmt1->executeQuery("UPDATE Player SET LogOn='LOGOFF', LastLogoutDate=now() WHERE PlayerID = '%s' AND LogOn='GAME'" , m_ID.c_str());

			// LogoutPlayerData ¿¡ Ãß°¡ÇÑ´Ù.
		//	addLogoutPlayerData(this);

			if (pStmt1->getAffectedRowCount()==0)
			{
				// ÀÌ¹Ì LOGOFF°Å³ª
				// LOGON»óÅÂÀÎ°¡?
				// ÀÌ·² ¼ö ÀÖÀ»±î? -_-;
			}

			// ºô¸µ by sigi. 2002.5.31
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

			// IP Á¤º¸¸¦ »èÁ¦ÇØ ÁØ´Ù.
            pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            pStmt2->executeQuery("DELETE FROM UserIPInfo WHERE Name = '%s'", CreatureName.c_str());

			SAFE_DELETE(pStmt2);
        }
		END_DB(pStmt2)
    }

	// login¼­¹ö·Î °¡¶ó°í client¿¡°Ô º¸³½´Ù.
	// ¿ø·¡´Â LGIncomingConnectionOKHandler¿¡¼­ Ã³¸®Çß´Ù. by sigi. 2002.6.19
	if (m_pReconnectPacket!=NULL)
	{
		//cout << "[SendReconnect] " << m_pReconnectPacket->toString().c_str() << endl;

		try 
		{
			//sendPacket( m_pReconnectPacket );
			Player::sendPacket( m_pReconnectPacket );
			// Ãâ·Â ¹öÆÛ¿¡ ³²¾ÆÀÖ´Â µ¥ÀÌÅ¸¸¦ Àü¼ÛÇÑ´Ù.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			// ¹«½Ã
		}
		
		SAFE_DELETE(m_pReconnectPacket);
	}


	// ÇÔ¼ö À­ºÎºÐ¿¡¼­ Ã³¸®Çß´Âµ¥.. Å¸ÀÌ¹Ö ¹®Á¦(LogOnÀÌ³ª UserIPInfo µî)·Î
	// ¿©±â¼­ ²÷¾îÁÖ°í.. ÀçÁ¢ÆÐÅ¶~À» º¸³»µµ·Ï ÇÑ´Ù.
	if (bDisconnected == UNDISCONNECTED) 
	{
		try 
		{
			// Å¬¶óÀÌ¾ðÆ®¿¡°Ô GCDisconnect ÆÐÅ¶À» Àü¼ÛÇÑ´Ù.
			//GCDisconnect gcDisconnect;
			//sendPacket(gcDisconnect);

			// Ãâ·Â ¹öÆÛ¿¡ ³²¾ÆÀÖ´Â µ¥ÀÌÅ¸¸¦ Àü¼ÛÇÑ´Ù.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			//cerr << "GamePlayer::disconnect() : GamePlayer::disconnect Exception Check!!" << endl;
			//cerr << t.toString() << endl;
		}
	}

	// ¼ÒÄÏ ¿¬°áÀ» ´Ý´Â´Ù.
	m_pSocket->close();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ÃÖ±Ù N ¹øÂ°ÀÇ ÆÐÅ¶À» ¸®ÅÏÇÑ´Ù.
// 
// N == 0 ÀÏ °æ¿ì, °¡Àå ÃÖ±ÙÀÇ ÆÐÅ¶À» ¸®ÅÏÇÏ°Ô µÈ´Ù.
//
// ÃÖ´ë nPacketHistorySize - 1 ±îÁö ÁöÁ¤ÇÒ ¼ö ÀÖ´Ù. 
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
// Æ¯Á¤ ÆÐÅ¶¾ÆÀÌµð¸¦ °¡Áø °¡Àå ÃÖ±ÙÀÇ ÆÐÅ¶À» ¸®ÅÏÇÑ´Ù.
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
	// ·â°üÐÄÌø¼ì²â 
	// ¿§·È 2007-6-25  kf_168@hotmail.com
	//

	if (PacketID == Packet::PACKET_CG_VERIFY_TIME )
	{
		if( m_SpeedVerify.tv_sec == 0 )
		{
			// Èç¹ûÎ´»ñÈ¡ÐÄÌø¼ì²â³õÊ¼»¯Öµ,ÔòÈ¡µ±Ç°Ê±¼ä+SpeedCheckDelya×÷Îª³õÊ¼Öµ
			// ÉèÖÃ¼ì²âÍ¨¹ý SpeedCheck = true;
			m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;
			
			SpeedCheck = true;
		}
		else
		{
			// ÒÔÏÂ¿ªÊ¼¼ì²â
			// Èç¹ûµ±Ç°Ê±¼ä´óÓÚÉÏ´Î¼ì²âÊ±¼ä+ÉÏÆ«ÒÆÖµ,Ôò¼ì²âÍ¨¹ý
			if( CurrentTime.tv_sec > m_SpeedVerify.tv_sec - maxTimeGap )
			{
				m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

				SpeedCheck = true;
				// ×î´ó´íÎóÐ£Ñé-1,Èç¹ûµ±Ç°´íÎóÐ£Ñé³¬¹ýÔ¤ÉèÖµ,Ôò·µ»Ø¼Ù
				m_VerifyCount = max(0, m_VerifyCount-1);
			}
			else
			{
				// ¸üÐÂÏÂ´ÎÐ£ÑéÊ±¼ä,×¢ÒâÕâÀïÊÇÈ¡Ç°Ê±¼ä+ÏÂ´ÎÐ£ÑéÊ±¼ä.
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
	// ¼ì²â·â°ü·¢ËÍ¿ÉÄÜÐÔ½áÊø
	// Add by Coffee 2007-6-25 kf_168@hotmail.com
	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	// Ôö¼ÓÒÆ¶¯¼ì²â·â°ü¼ì²â
	// Add by Coffee 2007-6-25 E-mail: kf_168@hotmail.com
	if (PacketID == Packet::PACKET_CG_MOVE)
	{
		if (CurrentTime <= m_MoveSpeedVerify)
		{
			// Ê¹ÓÃ¼ÓËÙ
		}
		//Timeval UseTimer=CurrentTime-m_MoveSpeedVerify;
		tv_sub(&CurrentTime,&m_MoveSpeedVerify);
		double rtt;
		// ÒÔºÁÃëÎªµ¥Î»¼ÆËãrtt
		rtt =CurrentTime.tv_sec * 1000 + CurrentTime.tv_usec / 1000;
		
		getCurrentTime(m_MoveSpeedVerify);
		//add by viva for notice
		//filelog("MoveLog.txt", "MoveTime:=%.3f ms\n",rtt);
		//end
	}
	
	// End by Coffee 
	//////////////////////////////////////////////////////////////////////////
	
	/*
	// Å©¸®Ã³ÀÇ ½ºÇÇµå¸¦ ¹Þ¾Æ¿Â´Ù.
	if (m_pCreature == NULL || pPacket == NULL) {
		return true;
	}

	// ±ÔÁ¤ ½Ã°£ ÀÌÀü¿¡ ¶È °°Àº ÆÐÅ¶ÀÌ ¼ö½Ê¹ø ³¯¾Æ¿À¸é Á¢¼ÓÀ» Â¥¸¥´Ù.
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
			// ÀÌÀü ½Ã°£ÀÌ¶û ÇöÀç ½Ã°£ÀÌ¶û Ã¼Å©ÇØ¼­ ´õ ºü¸¥ ½Ã°£¿¡ ÆÐÅ¶ÀÌ ³¯¾Æ¿ÔÀ¸¸é ÀÌ°Ç Ä¡ÅÍ´Ù.
			if (VerifyTime <= m_MoveSpeedVerify) {
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			// ´ÙÀ½¿¡ ¹«ºê°¡ °¡Àå »¡¸® ³¯¾Æ¿Ã ¼ö ÀÖ´Â °¡´ÉÇÑ ½Ã°£À» ÀúÀåÇØ µÐ´Ù.
			// ¸ðÅä »çÀÌÅ¬À» Å¸°í ÀÖ´Ù¸é ÀÌµ¿¼Óµµ°¡ ÁÙ¾îµç´Ù.

			BYTE RealSpeed = 0;
			if (pSlayer->hasRideMotorcycle()) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // ¸ðÅä»çÀÌÅ¬ÀÌ ¾Æ´Ï´Ù.
			{
				//RealSpeed = 4;
				RealSpeed = 2;
			}

			// ´ÙÀ½ ¾µ ¼ö ÀÖ´Â ½Ã°£À» ¼ÂÆÃÇÑ´Ù.
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
			// ¹«±â¸¦ ¹«¾ùÀ» µé°í ÀÖ´ÂÁö Ã¼Å©ÇÑ´Ù.
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			Item::ItemClass IClass = Item::ITEM_CLASS_SKULL;
			if (pItem != NULL) {
				IClass = pItem->getItemClass();
			} 

			getCurrentTime(m_AttackSpeedVerify);
			getCurrentTime(m_MoveSpeedVerify);

			BYTE RealSpeed = 0;
			// ½½·Î¿ì ½ºÇÇµå
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
					// ±âº» °ø°Ý 875
					default :
						RealSpeed = 8;
						break;
				}
			} 
			else if (Speed == 1) // ³ë¸Ö ½ºÇÇµå
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
					// ±âº» °ø°Ý 875
					default :
						RealSpeed = 8;
						break;

				}
			} 
			else // ÆÐ½ºÆ® ½ºÇÇµå
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

			// ½ºÇÇµå ¿ÏÈ­ Á¤Ã¥
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
			// ÀÌÀü ½Ã°£ÀÌ¶û ÇöÀç ½Ã°£ÀÌ¶û Ã¼Å©ÇØ¼­ ´õ ºü¸¥ ½Ã°£¿¡ ÆÐÅ¶ÀÌ ³¯¾Æ¿ÔÀ¸¸é ÀÌ°Ç Ä¡ÅÍ´Ù.
			if (VerifyTime <= m_MoveSpeedVerify) 
			{
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			BYTE RealSpeed = 0;
			// ´ÙÀ½¿¡ ¹«ºê°¡ °¡Àå »¡¸® ³¯¾Æ¿Ã ¼ö ÀÖ´Â °¡´ÉÇÑ ½Ã°£À» ÀúÀåÇØ µÐ´Ù.
			// ¹ÚÁã º¯½ÅÀ» ÇÏ°í ÀÖ´Ù¸é ¼Óµµ°¡ »¡¶óÁø´Ù. ÃÊ´ç ³× Å¸ÀÏÀ» ÀÌµ¿ ÇÑ´Ù.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // ³ë¸Ö »óÅÂ¿¡¼± ÃÊ´ç µÎÅ¸ÀÏÀ» ÀÌµ¿ÇÑ´Ù.
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
			if (Speed == 0) // ½½·Î¿ì ½ºÇÇµå 875
			{
				RealSpeed = 8;
			} 
			else if (Speed == 1) // ³ë¸Ö ½ºÇÇµå 875
			{
				RealSpeed = 8;
			} 
			else // ÆÐ½ºÆ® ½ºÇÇµå 812
			{
				RealSpeed = 8;
			}

			// ½ºÇÇµå ¿ÏÈ­ Á¤Ã¥
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

			// 1ÃÊ ÀÌ»ó °É¸®¸é ·Î±× ³²±ä´Ù.
			if ( afterTime.tv_sec > currentTime.tv_sec + 1 )
			{
				filelog( "billingLoginTime.txt", "PlayerID : %s, CallTime : %d sec, Try : %d", m_ID.c_str(), (int)(afterTime.tv_sec - currentTime.tv_sec), m_BillingLoginRequestCount );
			}

			// PayLogin ¿äÃ»ÇÑ È¸¼ö ±â¾ï
			m_BillingLoginRequestCount ++;

			// 60ÃÊ ÈÄ ´Ù½Ã Ã¼Å©ÇÑ´Ù.
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

// ¾ÏÈ£È­ ÄÚµå¸¦ ¼³Á¤ÇÑ´Ù.
void GamePlayer::setEncryptCode()
{
    __BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	Assert(m_pCreature!=NULL);

	// ÀÏ´ÜÀº ObjectID¸¦ ÀÌ¿ëÇÑ´Ù.
	//ObjectID_t 	objectID 	= m_pCreature->getObjectID();

	// Á¸º°·Î °ü¸®¸¦ ÇÏµµ·Ï ¼öÁ¤ÇÑ´Ù.
//	ZoneID_t 	zoneID 		= m_pCreature->getZone()->getZoneID();
//	static int	serverID	= g_pConfig->getPropertyInt("ServerID");

//	if (objectID!=0)
//	{
		//uchar code = (uchar)(objectID / zoneID + objectID);
		//uchar code = (uchar)( ( ( zoneID >> 8 ) ^ zoneID ) ^ ( ( serverID + 1 ) << 4 ) );
		uchar code = m_pCreature->getZone()->getEncryptCode();

#ifdef __ACTIVE_SERVICE_DEADLINE__
		// ¼­¹ö ¹Ùº¸ ¸¸µé±â ÄÚµå
		VSDate date = VSDate::currentDate();
		// 2003³â 1¿ù ÀÌ»óÀÎ °æ¿ì: 2003, 0
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

	// ÀÌ¹Ì EventKick ÀÌ ÀÖ´Ù¸é ¹«½ÃÇÑ´Ù.
	if ( m_EventManager.getEvent( Event::EVENT_CLASS_KICK ) != NULL )
		return;

	EventKick* pEventKick = new EventKick( this );
	pEventKick->setDeadline( nSeconds * 10 );
	addEvent( pEventKick );

	// ¸î ÃÊÈÄ¿¡ Â©¸°´Ù..°í º¸³»ÁØ´Ù.
	GCKickMessage gcKickMessage;
	gcKickMessage.setType( KickMessageType );
	gcKickMessage.setSeconds( nSeconds );
	sendPacket( &gcKickMessage );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////
// PaySystem °ü·Ã
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
// Á¢¼ÓÀÚ Åë°è¸¦ À§ÇØ¼­ 
// UserInfo DBÀÇ LogoutPlayerData¿¡ LogoutÇÑ »ç¿ëÀÚ¸¦ Ãß°¡ÇÑ´Ù.
//
//////////////////////////////////////////////////////////////////////////////
void addLogoutPlayerData(Player* pPlayer)
{

	Statement* pStmt = NULL;

	pStmt = g_pDatabaseManager->getUserInfoConnection()->createStatement();

	// À¯Àú Åë°è °ü·Ã Á¤º¸¸¦ ÀÔ·ÂÇÑ´Ù.
	BEGIN_DB
	{
		string ID = pPlayer->getID();
		string ip = pPlayer->getSocket()->getHost();

		// ¸ÕÀú ÇöÀç ½Ã°£À» ¾ò¾î³½´Ù.
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

		// ´Ù½Ã ½Ã°£À» ÃÊ±âÈ­ÇÑ´Ù.
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
			// º¹±ÇÀÌ ¾ø¾ú´Ù. »õ·Î ³Ö¾îÁØ´Ù.
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

	// DimensionID ±¸ÇÏ±â
	uint dimensionID = g_pConfig->getPropertyInt("Dimension");
	if ( g_pConfig->getPropertyInt("IsNetMarble") == 0 )
	{
		// ³Ý¸¶ºí ÀÏ °æ¿ì¿£ 2
		dimensionID = 2;
	}

	// WorldID
	uint worldID = g_pConfig->getPropertyInt("WorldID");

	// Á¾Á· ÄÚµå
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
		// ¹ìÆÄÀÌ¾î´Â  10
		racecode = 10;

		Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
		Assert( pVampire != NULL );

		str = pVampire->getSTR();
		dex = pVampire->getDEX();
		inte = pVampire->getINT();
	}
	else if ( m_pCreature->isOusters() )
	{
		// ¾Æ¿ì½ºÅÍÁî´Â 20
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

	// ·¹º§
	uint level = (uint)m_pCreature->getLevel();

	// ·Î±×¾Æ¿ô ½Ã°£. ÇöÀç ½Ã°£
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

