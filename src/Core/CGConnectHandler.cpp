//////////////////////////////////////////////////////////////////////////////
// Filename    : CGConnectHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGConnect.h"

#ifdef __GAME_SERVER__
	#include "PlayerCreature.h"
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Zone.h"
	#include "ZoneInfoManager.h"
	#include "ZoneUtil.h"
	#include "ZoneGroup.h"
	#include "ZoneGroupManager.h"
	#include "ZonePlayerManager.h"
	#include "IncomingPlayerManager.h"
	#include "WeatherManager.h"
	#include "PCFinder.h"
	#include "GuildManager.h"
	#include "Guild.h"
	#include "TelephoneCenter.h"
	#include "EventSave.h"
	#include "EventRegeneration.h"
	#include "EventHeadCount.h"
	#include "PCSlayerInfo2.h"
	#include "PCVampireInfo2.h"
	#include "NPCInfo.h"
	#include "PacketUtil.h"
	#include "DB.h"
	#include "Properties.h"
	//#include "LogClient.h"
	#include "Thread.h"
	#include "PacketUtil.h"
	#include "ResurrectLocationManager.h"
	#include "SharedServerManager.h"
	#include "BillingPlayerManager.h"
	#include "Encrypter.h"
	#include "LogDef.h"
	#include "EventSystemMessage.h"
	#include "CastleInfoManager.h"
	#include "PKZoneInfoManager.h"
	#include "EventZoneInfo.h"
	#include "NicknameBook.h"

	#include "EffectGhost.h"
	#include "skill/EffectGnomesWhisper.h"

	#include "mission/QuestManager.h"

	#include "CreatureUtil.h"

	#include <fstream>
	#include <list>
	#include <stdio.h>

	#include "GCDisconnect.h"
	#include "GCUpdateInfo.h"
	#include "GCSystemMessage.h"
	#include "GSGuildMemberLogOn.h"

	#include "SystemAvailabilitiesManager.h"
	#include "types/ServerType.h"
	#include "GDRLairManager.h"

	#include "chinabilling/CBillingInfo.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
	#include "chinabilling/CBillingPlayerManager.h"
	#include "EventCBilling.h"
#endif

	#include "EventAuth.h"
	#include "DynamicZoneManager.h"

#endif

bool isAdultByBirthdayDate(const string& birthday);


//////////////////////////////////////////////////////////////////////////////
// CGConnectHandler::execute()
//
// 이 패킷은 로그인서버에서 최초로 게임 서버로 연결할 때, 또는 게임 서버에서
// 다른 게임 서버로 이동할 때, 클라이언트가 서버로 전송하는 최초의 패킷이다.
// 이때 플레이어 객체는 새로 생겨난 상태이고, 이 플레이어 객체는 IPM 에서
// 관리되는 상태이다. 
//
// 당연히 최초의 패킷으로 다른 패킷이 넘어오는 경우라면, 이것은 해킹 시도라고
// 봐도 무방하므로 이 패킷이 최초인지 검사해야 한다. 이를 위해서 플레이어 객체에
// 이전 패킷을 저장하고 있으므로, 이 값이 NULL 인지만 보면 되겠다.
//
// 잘못된 패킷이라면, ban 에 등록하고 접속을 종료한다.
//////////////////////////////////////////////////////////////////////////////
void CGConnectHandler::execute (CGConnect* pPacket , Player* pPlayer)
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	// set MAC Address
	pGamePlayer->setMacAddress(pPacket->getMacAddress());

	// 이 패킷을 ConnectionInfo 객체를 갖고 온다.
	// 크래커는 키값과 캐릭터 이름을 일정 시간안에 맞춰야만 접속이 가능하다.
	try 
	{
		ConnectionInfo* pConnectionInfo = g_pConnectionInfoManager->getConnectionInfo(pGamePlayer->getSocket()->getHost());

		// 키값을 인증한다.
		if (pPacket->getKey() != pConnectionInfo->getKey())
		{
			FILELOG_INCOMING_CONNECTION("connectionError.log", "Wrong Key: [%s] %s", pConnectionInfo->getPCName().c_str(), pGamePlayer->getSocket()->getHost().c_str());
			throw InvalidProtocolException("invalid key");
		}

		// 이름을 인증한다.
		if (pPacket->getPCName() != pConnectionInfo->getPCName())
		{
			FILELOG_INCOMING_CONNECTION("connectionError.log", "Wrong PCName: [%s] %s", pConnectionInfo->getPCName().c_str(), pGamePlayer->getSocket()->getHost().c_str());
			throw InvalidProtocolException("invalid pc name");
		}

		// 일단 이름을 저장한다. 어차피 다음에 실패하면 객체를 삭제하니까 무방하다.
		pGamePlayer->setID(pConnectionInfo->getPlayerID());

		// CIM의 heartbeat가 실행되기 전에 재수좋게 접속할 가능성이 있다.
		// (타이밍이 좋으면 heartbeat 실행주기*2 안에만 접속하면 된다.)
		// 따라서, 현재 시간과 expire time 을 비교한다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (pConnectionInfo->getExpireTime() < currentTime) 
		{
			FILELOG_INCOMING_CONNECTION("connectionError.log", "Expired: [%s] %s", pConnectionInfo->getPCName().c_str(), pGamePlayer->getSocket()->getHost().c_str());

			// 일단 삭제한다.
			g_pConnectionInfoManager->deleteConnectionInfo(pConnectionInfo->getClientIP());
			throw InvalidProtocolException("session already expired");
		}

       	// by sigi. 2002.12.7
		FILELOG_INCOMING_CONNECTION("connectionInfo.log", "Login [%s:%s] %s (%u)",
										pConnectionInfo->getPlayerID().c_str(),
										pConnectionInfo->getPCName().c_str(),
										pConnectionInfo->getClientIP().c_str(),
										pConnectionInfo->getKey());

		// 인증되었으니, ConnectionInfo 를 삭제한다.
		try {
			g_pConnectionInfoManager->deleteConnectionInfo(pConnectionInfo->getClientIP());
		} catch (NoSuchElementException& nsee)
		{
			FILELOG_INCOMING_CONNECTION("connectionInfoDelete.log", "DeleteNoSuch [%s:%s] %s (%u)",
										pConnectionInfo->getPlayerID().c_str(),
										pConnectionInfo->getPCName().c_str(),
										pConnectionInfo->getClientIP().c_str(),
										pConnectionInfo->getKey());
		}
	} 
	catch (NoSuchElementException & nsee) // 그런 IP를 가진 CI 가 없을 경우
	{ 
		FILELOG_INCOMING_CONNECTION("connectionError.log", "NoSuchConnectionInfo: %s", pGamePlayer->getSocket()->getHost().c_str());

		// 흠.. 연결 이후 CGConnect 패킷을 보내는 딜레이가 너무 길 경우
		// session 이 expire 된다. 이럴 경우에도 짜르자!
		// (예를 들어서, 최초 연결에서는 성공했으나 그다음에 디버깅 상태로
		// 들어갈 경우, CGConnect 패킷을 보낼 때쯤에는 expire 된다.)
		GCDisconnect gcDisconnect;
		gcDisconnect.setMessage(nsee.toString());

		pGamePlayer->sendPacket(&gcDisconnect);

		// 이렇게 던지면 상위 IPM::processCommands()에서 disconnect 처리한다.
		throw InvalidProtocolException(nsee.toString().c_str());
	} 
	catch (InvalidProtocolException & ipe) 
	{
		FILELOG_INCOMING_CONNECTION("connectionError.log", "%s: %s", ipe.toString().c_str(), pGamePlayer->getSocket()->getHost().c_str());
		//cout << endl << "+-----------------------+" << endl << "| Level 2 Access Denied |" << endl << "+-----------------------+" << endl << endl;

		GCDisconnect gcDisconnect;
		gcDisconnect.setMessage(ipe.toString());

		pGamePlayer->sendPacket(&gcDisconnect);

		// 이렇게 던지면 상위 IPM::processCommands()에서 disconnect 처리한다.
		throw;
	}

	//----------------------------------------------------------------------
	// 로그인 체크
	//----------------------------------------------------------------------
	Statement* pStmt   = NULL;
	Result*    pResult = NULL;
 
	// 빌링~
	PayType         payType;
	string          payPlayDate;
	uint            payPlayHours;
	uint            payPlayFlag;
	int				billingUserKey = 0;	// by sigi. 2002.11.18
	string          familyPayPlayDate;


	try
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT `PlayerID` FROM `Slayer` WHERE `Name` = '%s'",pPacket->getPCName().c_str());

	

		if (pResult->getRowCount() != 1)
		{
			StringStream msg;
			msg << "Failed to load PlayerCreature data from DB. Not 1 PlayerID (" 
				<< pPacket->getPCName().c_str() << ")";

			filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

			SAFE_DELETE(pStmt);
			throw ProtocolException(msg.toString().c_str());
		}

		if (pResult->next()) 
		{
			string spID = pResult->getString(1);
			if (strcasecmp(spID.c_str(), pGamePlayer->getID().c_str()) != 0) 
			{
				StringStream msg;
				msg << "Failed to load PlayerCreature data from DB. No Character(" 
					<< spID.c_str() << "!="
					<< pGamePlayer->getID().c_str() << ")";

				filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

				SAFE_DELETE(pStmt);
				throw ProtocolException(msg.toString().c_str());
			}
		}

		SAFE_DELETE(pStmt);

		//pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

#ifdef __THAILAND_SERVER__

		pResult = pStmt->executeQuery("SELECT `PlayerID`, `CurrentServerGroupID`, `LogOn`, `SpecialEventCount`, `PayType`, `PayPlayDate`, `PayPlayHours`, `PayPlayFlag`, `BillingUserKey`, `FamilyPayPlayDate`, `Birthday` FROM `Player` WHERE `PlayerID` = '%s'", pGamePlayer->getID().c_str());

#else

		pResult = pStmt->executeQuery("SELECT `PlayerID`, `CurrentServerGroupID`, `LogOn`, `SpecialEventCount`, `PayType`, `PayPlayDate`, `PayPlayHours`, `PayPlayFlag`, `BillingUserKey`, `FamilyPayPlayDate` FROM `Player` WHERE `PlayerID` = '%s'", pGamePlayer->getID().c_str());

#endif
		if (pResult->getRowCount() != 1)
		{
			StringStream msg;
			msg << "Failed to load PlayerCreature data from DB. No Player(" 
				<< pPacket->getPCName().c_str() << ")";

			filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

			SAFE_DELETE(pStmt);
			throw ProtocolException(msg.toString().c_str());
		}

		pResult->next();

		int i = 0;

		string          playerID = pResult->getString(++i);
		ServerGroupID_t GID      = pResult->getInt(++i);
		string          logon    = pResult->getString(++i);
		uint            scount	= pResult->getDWORD(++i);

		payType      = (PayType)pResult->getInt(++i);
		payPlayDate  = pResult->getString(++i);
		payPlayHours = pResult->getInt(++i);
		payPlayFlag  = pResult->getInt(++i);
		billingUserKey  	= pResult->getInt(++i);
		familyPayPlayDate	= pResult->getString(++i);

#ifdef __THAILAND_SERVER__
		string Birthday = pResult->getString(++i);
		pGamePlayer->setPermission(isAdultByBirthdayDate(Birthday ));
#endif

		pGamePlayer->setServerGroupID(GID);
		pGamePlayer->setSpecialEventCount(scount);
		pGamePlayer->setBillingUserKey(billingUserKey);

		if (logon != "LOGOFF")
		{
			SAFE_DELETE(pStmt);
			char str[80];
			sprintf(str, "Already connected player ID: %s, %s", playerID.c_str(), logon.c_str());
			throw ProtocolException(str);
		}

		pStmt->executeQuery("UPDATE `Player` SET `LogOn`='GAME' WHERE `PlayerID` = '%s' AND `LogOn`='LOGOFF'", playerID.c_str());

		// LogOn이 LOGOFF가 아니거나.. 등등.. by sigi. 2002.5.15
		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			char str[80];
			sprintf(str, "Already connected player ID2: %s, %s", playerID.c_str(), logon.c_str());
			throw ProtocolException(str);
		}

		string connectIP = pGamePlayer->getSocket()->getHost();

		// 빌링 by sigi. 2002.5.31
#ifdef __CONNECT_BILLING_SYSTEM__
		if (payType == PAY_TYPE_FREE )
		{
			pGamePlayer->setMetroFreePlayer();
		}
#elif defined(__PAY_SYSTEM_LOGIN__)
		if (pGamePlayer->loginPayPlay(payType, 
										payPlayDate, payPlayHours, payPlayFlag,
										connectIP, playerID))
		{
			sendPayInfo(pGamePlayer);
		}
		else
		{
			SAFE_DELETE(pStmt);
			throw ProtocolException("no pay account");
		}
// by sigi. 2002.11.18. 제한적 무료 사용자. - -; 일단 login
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)
		if (pGamePlayer->loginPayPlay(payType, 
										payPlayDate, payPlayHours, payPlayFlag,
										connectIP, playerID))
		{
			sendPayInfo(pGamePlayer);
		}
#else //defined(__PAY_SYSTEM_ZONE__)
		pGamePlayer->setPayPlayValue(payType, payPlayDate, payPlayHours, payPlayFlag, familyPayPlayDate);
#endif


		SAFE_DELETE(pStmt);
	}
	catch (SQLQueryException & sqe)
	{
		SAFE_DELETE(pStmt);
		throw Error(sqe.toString());
	}

	//----------------------------------------------------------------------
	// 슬레이어 또는 뱀파이어 캐릭터를 로딩한다.
	//----------------------------------------------------------------------
	Slayer*  pSlayer  = NULL;
	Vampire* pVampire = NULL;
	Ousters* pOusters = NULL;

	bool bAlreadyConnected = false;

	//try
	//{
		if (pPacket->getPCType() == PC_SLAYER) 
		{
			pSlayer = new Slayer();
			pSlayer->setName(pPacket->getPCName());
			pSlayer->setPlayer(pGamePlayer);

			if (!pSlayer->load())
			{
				filelog("connectDB_BUG.txt", "Failed to load SLAYER(%s) data from DB", pPacket->getPCName().c_str());

				throw ProtocolException("Failed to load SLAYER data from DB");
			}

			// 유료존에서만 적용되는 아이템 때문에 밑에서 체크
			//pSlayer->loadItem();
			//Assert(pSlayer->getName() == pPacket->getPCName());
			if (pSlayer->getName() != pPacket->getPCName())
			{
				//cout << "Different Name : " << pSlayer->getName().c_str() << ", " << pPacket->getPCName().c_str() << endl;

				Assert(pSlayer->getName() == pPacket->getPCName());
			}

			pGamePlayer->setCreature(pSlayer);

			// Slayer를 TelephoneCenter에 등록한다.
			//g_pTelephoneCenter->addSlayer(pSlayer);
		
			// 주기 회복 이벤트를 플레이어 객체에 추가한다.
			// 이때 기본적으로 10초 회복을 원칙으로 한다.
			// (setDeadline의 파라미터는 0.1 초라는 데 유의할 것)
			EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
			pEventRegeneration->setDeadline(10* 10);
			pGamePlayer->addEvent(pEventRegeneration);

			// PCFinder에 추가한다.
			// PCFinder의 삭제는 ~GamePlayer()에서만 한다.
			try {
				g_pPCFinder->addCreature(pSlayer);
			} catch (DuplicatedException& de) {
				bAlreadyConnected = true;
			}

			// 이미 접속중인 경우가 아니라면.. by sigi. 2002.8.29
			if (!bAlreadyConnected)
			{
				// 길드 현재 접속 멤버 리스트에 추가한다.
				if (pSlayer->getGuildID() != 99 )
				{
					Guild* pGuild = g_pGuildManager->getGuild(pSlayer->getGuildID());
					if (pGuild != NULL )
					{
						// sharedserver로 접속을 알리고 DB 도 update 한다.
						try {
							pGuild->addCurrentMember(pSlayer->getName());

							GSGuildMemberLogOn gsGuildMemberLogOn;
							gsGuildMemberLogOn.setGuildID(pGuild->getID());
							gsGuildMemberLogOn.setName(pSlayer->getName());
							gsGuildMemberLogOn.setLogOn(true);
							gsGuildMemberLogOn.setServerID( g_pConfig->getPropertyInt("ServerID"));

							g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

							// DB 업데이트
							BEGIN_DB
							{
								pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
								pStmt->executeQuery("UPDATE `GuildMember` SET `LogOn` = 1 WHERE `Name` = '%s'", pSlayer->getName().c_str());
							}
							END_DB(pStmt )

						} catch (DuplicatedException& t) {
							// 일단 무시한다. by sigi. 2002.8.29
							filelog("guildBug.log", "%s", t.toString().c_str());
						}
					}
					else
						filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(), pSlayer->getName().c_str());
				}
			}
		} 
		else if (pPacket->getPCType() == PC_VAMPIRE) 
		{
			pVampire = new Vampire();
			pVampire->setName(pPacket->getPCName());
			pVampire->setPlayer(pGamePlayer);

			if (!pVampire->load())
			{
				filelog("connectDB_BUG.txt", "Failed to load VAMPIRE(%s) data from DB", pPacket->getPCName().c_str());
				throw ProtocolException("Failed to VAMPIRE data from DB");
			}

			// 유료존에서만 적용되는 아이템 때문에 밑에서 체크
			//pVampire->loadItem();
			Assert(pVampire->getName() == pPacket->getPCName());

			pGamePlayer->setCreature(pVampire);

			// 주기 회복 이벤트를 플레이어 객체에 추가한다.
			// 이때 기본적으로 10초 회복을 원칙으로 한다.
			// (setDeadline의 파라미터는 0.1 초라는 데 유의할 것)
			EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
			pEventRegeneration->setDeadline(10* 10);
			pGamePlayer->addEvent(pEventRegeneration);

			// PCFinder에 추가한다.
			// PCFinder의 삭제는 ~GamePlayer()에서만 한다.
			try {
				g_pPCFinder->addCreature(pVampire);
			} catch (DuplicatedException& de) {
				bAlreadyConnected = true;
			}

			// 이미 접속중인 경우가 아니라면.. by sigi. 2002.8.29
			if (!bAlreadyConnected)
			{
				// 길드 현재 접속 멤버 리스트에 추가한다.
				if (pVampire->getGuildID() != 0 )
				{
					Guild* pGuild = g_pGuildManager->getGuild(pVampire->getGuildID());
					if (pGuild != NULL )
					{
						// sharedserver 에 접속을 알리고 DB 도 update 한다.
						try {
							pGuild->addCurrentMember(pVampire->getName());

							GSGuildMemberLogOn gsGuildMemberLogOn;
							gsGuildMemberLogOn.setGuildID(pGuild->getID());
							gsGuildMemberLogOn.setName(pVampire->getName());
							gsGuildMemberLogOn.setLogOn(true);
							gsGuildMemberLogOn.setServerID( g_pConfig->getPropertyInt("ServerID"));

							g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

							// DB 업데이트
							BEGIN_DB
							{
								pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
								pStmt->executeQuery("UPDATE `GuildMember` SET `LogOn` = 1 WHERE `Name` = '%s'", pVampire->getName().c_str());
							}
							END_DB(pStmt )
						} catch (DuplicatedException& t) {
							// 일단 무시한다. by sigi. 2002.8.29
							filelog("guildBug.log", "%s", t.toString().c_str());
						}
					}
					else
						filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str());
				}
			}
		}
		else if (pPacket->getPCType() == PC_OUSTERS) 
		{
			pOusters = new Ousters();
			pOusters->setName(pPacket->getPCName());
			pOusters->setPlayer(pGamePlayer);

			if (!pOusters->load())
			{
				filelog("connectDB_BUG.txt", "Failed to load VAMPIRE(%s) data from DB", pPacket->getPCName().c_str());
				throw ProtocolException("Failed to VAMPIRE data from DB");
			}

			// 유료존에서만 적용되는 아이템 때문에 밑에서 체크
			//pVampire->loadItem();
			Assert(pOusters->getName() == pPacket->getPCName());

			pGamePlayer->setCreature(pOusters);

			// 주기 회복 이벤트를 플레이어 객체에 추가한다.
			// 이때 기본적으로 10초 회복을 원칙으로 한다.
			// (setDeadline의 파라미터는 0.1 초라는 데 유의할 것)
			EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
			pEventRegeneration->setDeadline(10* 10);
			pGamePlayer->addEvent(pEventRegeneration);

			// PCFinder에 추가한다.
			// PCFinder의 삭제는 ~GamePlayer()에서만 한다.
			try {
				g_pPCFinder->addCreature(pOusters);
			} catch (DuplicatedException& de) {
				bAlreadyConnected = true;
			}

			// 이미 접속중인 경우가 아니라면.. by sigi. 2002.8.29
			if (!bAlreadyConnected)
			{
				// 길드 현재 접속 멤버 리스트에 추가한다.
				if (pOusters->getGuildID() != 66 )
				{
					Guild* pGuild = g_pGuildManager->getGuild(pOusters->getGuildID());
					if (pGuild != NULL )
					{
						// sharedserver 에 접속을 알리고 DB 도 update 한다.
						try {
							pGuild->addCurrentMember(pOusters->getName());

							GSGuildMemberLogOn gsGuildMemberLogOn;
							gsGuildMemberLogOn.setGuildID(pGuild->getID());
							gsGuildMemberLogOn.setName(pOusters->getName());
							gsGuildMemberLogOn.setLogOn(true);
							gsGuildMemberLogOn.setServerID( g_pConfig->getPropertyInt("ServerID"));

							g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

							// DB 업데이트
							BEGIN_DB
							{
								pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
								pStmt->executeQuery("UPDATE `GuildMember` SET `LogOn` = 1 WHERE `Name` = '%s'", pOusters->getName().c_str());
							}
							END_DB(pStmt )
						} catch (DuplicatedException& t) {
							// 일단 무시한다. by sigi. 2002.8.29
							filelog("guildBug.log", "%s", t.toString().c_str());
						}
					}
					else
						filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pOusters->getGuildID(), pOusters->getName().c_str());
				}
			}
		}
	//}
	/*
	catch (DuplicatedException& de)
	{
		// PC finder에서 에러가 자꾸 뜨는데, 그냥 여기서 잡아주면 되지 않을까?
		// by 김성민
		// 여기서 크리쳐 객체를 지워버리면, 게임 플레이어가 가지고 있는 m_pCreature 포인터는
		// 가비지 값을 가르키게 된다. 그래서 GamePlayer::~GamePlayer() 에서 자신의 m_pCreature를 삭제할 때
		// 잘못된 메모리 영역을 참조하면서 죽게 된다. 그러므로 주석을 풀지 말 것.

		// GamePlayer를 지우면서 
		// m_pCreature가 있는 경우에는 PCFinder지워주는데..
		// 이것때문에 멀티 로그인이 가능하게 된다.
		// 이걸 막기 위해서 캐릭터를 여기서 지워준다.
		// by sigi. 2002.5.9

		// 혹시 PCFinder에서 안 지워주고 객체만 지우면
		// PCFinder에서 읽어온 pointer가 delete된거라서 문제가 생긴다고 생각했는데
		// 분명히 GamePlayer가 delete될때는 PCFinder에서 제거해주고
		// 여기서 지우는 캐릭터는 이미 접속된 캐릭터와는 관계없는 새로운 객체이므로
		// 상관이 없다. 2002.8.29. by sigi
		SAFE_DELETE(pSlayer);
		SAFE_DELETE(pVampire);

		pGamePlayer->setID(string(""));	// LogOn은 'LOGOFF'가 되는걸 막는다.
		pGamePlayer->setCreature(NULL);	// PCFinder에서 delete하는걸 막는다.

		char str[80];
		sprintf(str, "Already connected player ID3(Dup): %s", pPacket->getPCName().c_str());
		throw ProtocolException(str);
	}
	*/

	// 이미 접속 중인 경우의 처리. 
	// PCFinder에서의 DuplicatedException을 명확하게 처리하기 위해서
	// 변수를 둬서 체크한다. 
	// 아마 길드의 DuplicatedException때문에 
	// PCFinder에서 문제가 생긴것 같다.
	// by sigi. 2002.8.29
	if (bAlreadyConnected)
	{
		SAFE_DELETE(pSlayer);
		SAFE_DELETE(pVampire);
		SAFE_DELETE(pOusters);

		pGamePlayer->setID(string(""));	// LogOn은 'LOGOFF'가 되는걸 막는다.
		pGamePlayer->setCreature(NULL);	// PCFinder에서 delete하는걸 막는다.

		char str[80];
		sprintf(str, "Already connected player ID3(Dup): %s", pPacket->getPCName().c_str());
		throw ProtocolException(str);
	}

	//----------------------------------------------------------------------
	// PC를 PCFinder와 존에 등록한다.
	//----------------------------------------------------------------------
	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	EventHeadCount* pEventHeadCount = new EventHeadCount(pGamePlayer);
	pEventHeadCount->setDeadline(18000);
	pGamePlayer->addEvent(pEventHeadCount);

	if (pCreature->isGOD() )
	{
		EffectGhost* pEffect = new EffectGhost(pCreature);
		pCreature->getEffectManager()->addEffect(pEffect);
		pCreature->setFlag(Effect::EFFECT_CLASS_GHOST);
		pCreature->setMoveMode(Creature::MOVE_MODE_FLYING);
	}
	else
	{
#ifdef __TEST_SERVER__
		EventAuth* pAuth = new EventAuth(pGamePlayer);
		pGamePlayer->addEvent(pAuth);
		//cout << "엔프로텍트 인증 타이머 붙입니다 : " << pGamePlayer->getID() << endl;
#endif
	}

	if (pCreature->getCompetenceShape() == 0 )
	{
		EffectGnomesWhisper* pEffect = new EffectGnomesWhisper(pCreature);
		pEffect->setLevel(30);

		pCreature->addEffect(pEffect);
		pCreature->setFlag(pEffect->getEffectClass());
	}

	// 성이나 성 던전 안으로 로그인할 수 없다.
	ZoneID_t castleZoneID;
	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pCreature->getZoneID());

	bool isCastleZone = g_pCastleInfoManager->getCastleZoneID(pCreature->getZoneID(), castleZoneID);
	bool isMasterLair = pZoneInfo->isMasterLair() || GDRLairManager::Instance().isGDRLairZone(pCreature->getZoneID());
	bool isPKZone = g_pPKZoneInfoManager->isPKZone(pCreature->getZoneID());
	bool isMaze = (pCreature->getZoneID() == 3001 ) ||
					(pCreature->getZoneID() == 3002 ) ||
					(pCreature->getZoneID() == 3003);
	bool isEventZone = EventZoneInfoManager::Instance().getEventZoneInfo(pCreature->getZoneID() ) != NULL;
	bool isBeginnerZone = pCreature->getZoneID() == 1122 && !canEnterBeginnerZone(pCreature);
	bool isDynamicZone = g_pDynamicZoneManager->isDynamicZone(pCreature->getZoneID());
	
	if (pCreature->isPC() ) //&& pCreature->isPLAYER() )
	{
		ZONE_COORD zoneCoord;
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert(pPC != NULL);

		if (isCastleZone || isMasterLair || isPKZone || isMaze || isEventZone || isBeginnerZone || isDynamicZone )
		{
			if (g_pResurrectLocationManager->getPosition(pPC, zoneCoord ) )
			{
				pCreature->setZoneID(zoneCoord.id);
				pCreature->setXY(zoneCoord.x, zoneCoord.y);
			}
		}
	}

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);
	
#ifdef __PAY_SYSTEM_FREE_LIMIT__
	try {
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());
		Assert(pZoneInfo != NULL);

		Assert(pCreature->isPC());
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert(pPC != NULL);

		// 유료 존이나 프리미엄 존이 아닐 경우 30 레벨 이하의 종량제 사용자에게는 과금하지 않는다.
		if ((pGamePlayer->isPayPlaying() || pGamePlayer->isPremiumPlay() )
			&& pGamePlayer->getPayType() == PAY_TYPE_TIME
			&& pPC->canPlayFree()
			&& ! (pZoneInfo->isPayPlay() || pZone->isPremiumZone() )
		)
		{
			pGamePlayer->logoutPayPlay(pGamePlayer->getID(), false, false);
		}

		// 유료화 존이고 유료사용중이 아니면..
		// ㅜ.ㅠ 2003.03.16 일반 필드도 프리미엄존이다. 무료사용자도 필드로는 로그인 되어야 한다.
		if ((pZoneInfo->isPayPlay()) //|| pZoneInfo->isPremiumZone())
			&& !pGamePlayer->isPayPlaying() )
		{
			// 유료 서비스 사용 불가인 경우
			// 슬레이어는 에슬남동에서 부활하는 곳으로 간다.
			// 뱀파이어는 림보남동에서 부활하는 곳으로 간다.
			ZONE_COORD zoneCoord;

			if (g_pResurrectLocationManager->getRaceDefaultPosition(pPC->getRace(), zoneCoord ) )
			{
				pCreature->setZoneID(zoneCoord.id);
				pCreature->setXY(zoneCoord.x, zoneCoord.y);
			}
		}
	} catch (NoSuchElementException&) {
		throw Error("ZoneInfo에 zoneID가 없다.");
	}
#elif defined(__CONNECT_BILLING_SYSTEM__)
	if (pGamePlayer->isMetroFreePlayer() )
	{
		pGamePlayer->setBillingUserStatus("MT");
		pGamePlayer->setPremiumPlay();
	}
	else
	{
		try {
			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());
			Assert(pZoneInfo != NULL);

			Assert(pCreature->isPC());
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert(pPC != NULL);

			// 아직 빌링 서버에서 유료 사용자인지 인증 확인을 받지 않았다.
			// 유료화 존이라면 일단 유료 사용자라로 생각한다.
			// premium 을 켜 놓아야지 무료 사용일때 ZonePlayerManager 에서 무료존으로 옮겨준다.
			if (pZoneInfo->isPayPlay() )
			{
				pGamePlayer->setPremiumPlay();
			}

			} catch (NoSuchElementException&) {
				throw Error("ZoneInfo에 zoneID가 없다.");
		}

		// session 값을 정해둔다. by sigi. 2002.11.18
		pGamePlayer->setBillingSession();

		// 빌링서버에 게임 시작을 알린다.
		pGamePlayer->sendBillingLogin();
	}

#elif defined(__PAY_SYSTEM_ZONE__)
	try {
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());

		// 유료화 존이고 유료사용중이 아니면..
		if (pZoneInfo!=NULL
			&& (pZoneInfo->isPayPlay() || pZoneInfo->isPremiumZone())
			&& !pGamePlayer->isPayPlaying() )
		{
			bool bEnterZone = true;

			string connectIP = pGamePlayer->getSocket()->getHost();

			// 유료 서비스 사용이 가능한가?
			// 유료 서비스 사용이 안되고 유료 존이라면 들어갈 수 없다.
			if (!pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID())
				&& pZoneInfo->isPayPlay() )
			{
				bEnterZone = false;
			}

			if (!pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID())
				&& (pZone->getZoneID() == 1131 ||
					 pZone->getZoneID() == 1132 ||
					 pZone->getZoneID() == 1133 ||
					 pZone->getZoneID() == 1134 ) )
			{
				bEnterZone = false;
			}

			Assert(pCreature->isPC());
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert(pPC != NULL);

			if (!bEnterZone)
			{
				// 유료 서비스 사용 불가인 경우
				// 슬레이어는 에슬남동에서 부활하는 곳으로 간다.
				// 뱀파이어는 림보남동에서 부활하는 곳으로 간다.
				ZONE_COORD zoneCoord;
//				bool bFindPos = false;

				if (g_pResurrectLocationManager->getRaceDefaultPosition(pPC->getRace(), zoneCoord ) )
				{
					pCreature->setZoneID(zoneCoord.id);
					pCreature->setXY(zoneCoord.x, zoneCoord.y);
				}
			}
		}
	} catch (NoSuchElementException&) {
		throw Error("ZoneInfo에 zoneID가 없다.");
	}
#elif defined(__CONNECT_CBILLING_SYSTEM__)
	// 빌링 서버로 주기적으로 minus point/minute 패킷을 보내는 이벤트를 붙인다.
	EventCBilling* pEvent = new EventCBilling(pGamePlayer);
	pEvent->setDeadline(g_pCBillingPlayerManager->getMinusIntervalInt() * 600);
	pGamePlayer->addEvent(pEvent);

	// 중국 빌링은 전면 유료화 이므로 여기까지 왔다면 유료 사용자이다. 무료 사용자일 경우 로그인 서버에서 막힌다.
	pGamePlayer->setPayPlayer(true);
	pGamePlayer->setPremiumPlay();

	// send Login
	pGamePlayer->setCBillingVerified(g_pCBillingPlayerManager->sendLogin(pGamePlayer ));
#else
	// 아무것도 설정되어 있지 않으면
	// 걍 유료 사용자라고 해버리자
	pGamePlayer->setPremiumPlay();
#endif

	// test code
	/*
	// 로그인 하고.. 바로 뭔가 메세지를 뿌려주는 부분. by sigi. 2002.12.11
	EventSystemMessage* pESM = new EventSystemMessage(pGamePlayer);
	pESM->setDeadline(0);
	pESM->addMessage("이것은 테스트 시스템 메시지");
	pESM->addMessage("제대로 출력되길 바랄뿐.. -_-;;");
	pGamePlayer->addEvent(pESM);
	*/

	// 유료존에서만 적용되는 아이템 때문에 여기서 체크
	// 2002.8.26. by sigi
	if (pPacket->getPCType() == PC_SLAYER) 
	{
		Assert(pSlayer!=NULL);
		pSlayer->loadItem(true);
	}
	else if (pPacket->getPCType() == PC_VAMPIRE )
	{
		Assert(pVampire!=NULL);
		pVampire->loadItem(true);
	}
	else if (pPacket->getPCType() == PC_OUSTERS )
	{
		Assert(pOusters!=NULL);
		pOusters->loadItem(true);
	}


	// 슬레이어라면 길드 내부, 뱀파이어라면 레어 내부에서 
	// 시작하는 경우, HP를 만땅으로 채워준다. 
	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		switch (pZone->getZoneID())
		{
			case 2000:
			case 2001:
			case 2002:
			case 2003:
			case 2004:
			case 2010:
			case 2011:
			case 2012:
			case 2013:
			case 2014:
			case 2020:
			case 2021:
			case 2022:
			case 2023:
			case 2024:
				pSlayer->setHP(pSlayer->getHP(ATTR_MAX), ATTR_CURRENT);
				break;
			default:
				break;
		}
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		switch (pZone->getZoneID())
		{
			case 1003:
			case 1007:
				pVampire->setHP(pVampire->getHP(ATTR_MAX), ATTR_CURRENT);
				break;
			default:
				break;
		}
	}
	else if (pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		switch (pZone->getZoneID() )
		{
			case 1311:
				pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
			default:
				break;
		}
	}

	// 퀘스트 매니저를 로드한다.
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	pPC->getQuestManager()->load();

	// 크리처 자신과 소유 아이템들의 OID를 할당받는다.
	// 이미 Creature::load()에서 Zone 이 지정되어 있어야 한다.
	pCreature->registerObject();

	// 주기 저장 이벤트를 플레이어 객체에 추가한다.
	// 이때 기본적으로 10분 저장을 원칙으로 한다.
	// (setDeadline의 파라미터는 0.1 초라는 데 유의할 것)
	//EventSave* pEventSave = new EventSave(pGamePlayer);
	//pEventSave->setDeadline(600* 10);
	//pGamePlayer->addEvent(pEventSave);

#ifdef __USE_ENCRYPTER__
	// 암호화 코드 등록. 지금은 objectID로 하기 때문에.. by sigi. 2002.11.27
    pGamePlayer->setEncryptCode();
#endif

//	pGamePlayer->sendPacket(SystemAvailabilitiesManager::getInstance()->getAvailabilitiesPacket());
//	SEND_SYSTEM_AVAILABILITIES(pGamePlayer);

	//----------------------------------------------------------------------
	// GCUpdateInfo 용 PC 정보, SkillInfo 를 구성한다.
	//----------------------------------------------------------------------
	GCUpdateInfo gcUpdateInfo;
	makeGCUpdateInfo(&gcUpdateInfo, pCreature);
	pGamePlayer->sendPacket(&gcUpdateInfo);

	sendPetInfo(pGamePlayer);

	string host = pGamePlayer->getSocket()->getHost();

	IP_t IP = pGamePlayer->getSocket()->getHostIP();

	// 마지막으로 IP의 정보를 DB에 INSERT 한다.
	try 
	{

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream inputsql;

		inputsql << "INSERT INTO UserIPInfo (Name, IP, ServerID) VALUES ('"
			<< pCreature->getName().c_str() << "'," 
			<< IP << "," << g_pConfig->getPropertyInt("ServerID") 
			<< ")";
		
		pStmt->executeQuery(inputsql.toString());
		*/
		
		pStmt->executeQuery("INSERT IGNORE INTO `UserIPInfo` (`Name`, `IP`, `ServerID`) VALUES ('%s', %lu, %d)", 
								pCreature->getName().c_str(), IP, g_pConfig->getPropertyInt("ServerID"));
		SAFE_DELETE(pStmt);

		//log(LOG_CGCONNECT, pPacket->getPCName(), "", host);
	} 
	catch (SQLQueryException & se) 
	{
		// 바꾸기 시도. by sigi. 2002.6.21
		try {
			pStmt->executeQuery("UPDATE `UserIPInfo` SET `IP`=%ld, `ServerID`=%d WHERE `Name`='%s'", IP, g_pConfig->getPropertyInt("ServerID"), pCreature->getName().c_str());

			//log(LOG_CGCONNECT, pPacket->getPCName(), "", host);

			SAFE_DELETE(pStmt);

		} catch (SQLQueryException & se) {
			SAFE_DELETE(pStmt);
			throw ProtocolException("Duplicated IPInfo");
		}
	}

	//--------------------------------------------------
	// change player status
	//--------------------------------------------------
	pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_CG_READY);

#endif
		
	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}



#ifdef __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//
// YYYY-MM-DD 로 성인 판별
//
//////////////////////////////////////////////////////////////////////////////
bool
isAdultByBirthdayDate(const string& birthday)
{
    StringStream AdultSSN;

    time_t daytime = time(0);
    tm Timec;
    localtime_r(&daytime, &Timec);

    AdultSSN << Timec.tm_year - 18;
    // tm_mon - range 0 to 11
    if ((Timec.tm_mon+1) < 10 ) AdultSSN << "0";
    AdultSSN << (Timec.tm_mon+1);
    if (Timec.tm_mday < 10 ) AdultSSN << "0";
    AdultSSN << Timec.tm_mday;

    //cout << "Birthday = " << birthday.c_str() << " ADULTSSN = " << AdultSSN.toString().c_str() << endl;

    int year  = atoi(birthday.substr(0,4).c_str());
    int month = atoi(birthday.substr(5,2).c_str());
    int day   = atoi(birthday.substr(8,2).c_str());

    if (Timec.tm_year - 18 + 1900 > year )
    {
        //cout << "어른" << endl;
        return true;
    }
    else if (Timec.tm_year - 18 + 1900 == year )
    {
        if (Timec.tm_mon + 1 > month )
        {
            //cout << "어른" << endl;
            return true;
        }
        else if (Timec.tm_mon + 1 == month )
        {
            if (Timec.tm_mday >= day )
            {
                //cout << "어른" << endl;
                return true;
            }
        }
    }

    //cout << "애들" << endl;
    return false;
}

#endif

