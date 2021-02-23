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
	#include "LogClient.h"
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

	#include "Gpackets/GCDisconnect.h"
	#include "Gpackets/GCUpdateInfo.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GSGuildMemberLogOn.h"
	#include "Gpackets/GCLoadInventory.h"
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
// ¿Ã ∆–≈∂¿∫ ∑Œ±◊¿Œº≠πˆø°º≠ √÷√ ∑Œ ∞‘¿” º≠πˆ∑Œ ø¨∞·«“ ∂ß, ∂«¥¬ ∞‘¿” º≠πˆø°º≠
// ¥Ÿ∏• ∞‘¿” º≠πˆ∑Œ ¿Ãµø«“ ∂ß, ≈¨∂Û¿Ãæ∆Æ∞° º≠πˆ∑Œ ¿¸º€«œ¥¬ √÷√ ¿« ∆–≈∂¿Ã¥Ÿ.
// ¿Ã∂ß «√∑π¿ÃæÓ ∞¥√º¥¬ ªı∑Œ ª˝∞‹≥≠ ªÛ≈¬¿Ã∞Ì, ¿Ã «√∑π¿ÃæÓ ∞¥√º¥¬ IPM ø°º≠
// ∞¸∏Æµ«¥¬ ªÛ≈¬¿Ã¥Ÿ. 
//
// ¥Áø¨»˜ √÷√ ¿« ∆–≈∂¿∏∑Œ ¥Ÿ∏• ∆–≈∂¿Ã ≥—æÓø¿¥¬ ∞ÊøÏ∂Û∏È, ¿Ã∞Õ¿∫ «ÿ≈∑ Ω√µµ∂Û∞Ì
// ∫¡µµ π´πÊ«œπ«∑Œ ¿Ã ∆–≈∂¿Ã √÷√ ¿Œ¡ˆ ∞ÀªÁ«ÿæﬂ «—¥Ÿ. ¿Ã∏¶ ¿ß«ÿº≠ «√∑π¿ÃæÓ ∞¥√ºø°
// ¿Ã¿¸ ∆–≈∂¿ª ¿˙¿Â«œ∞Ì ¿÷¿∏π«∑Œ, ¿Ã ∞™¿Ã NULL ¿Œ¡ˆ∏∏ ∫∏∏È µ«∞⁄¥Ÿ.
//
// ¿ﬂ∏¯µ» ∆–≈∂¿Ã∂Û∏È, ban ø° µÓ∑œ«œ∞Ì ¡¢º”¿ª ¡æ∑·«—¥Ÿ.
//////////////////////////////////////////////////////////////////////////////
void CGConnectHandler::execute (CGConnect* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	// set MAC Address
	pGamePlayer->setMacAddress( pPacket->getMacAddress() );

	// ¿Ã ∆–≈∂¿ª ConnectionInfo ∞¥√º∏¶ ∞Æ∞Ì ø¬¥Ÿ.
	// ≈©∑°ƒø¥¬ ≈∞∞™∞˙ ƒ≥∏Ø≈Õ ¿Ã∏ß¿ª ¿œ¡§ Ω√∞£æ»ø° ∏¬√Áæﬂ∏∏ ¡¢º”¿Ã ∞°¥…«œ¥Ÿ.
	try 
	{
		ConnectionInfo* pConnectionInfo = g_pConnectionInfoManager->getConnectionInfo(pGamePlayer->getSocket()->getHost());

		// ≈∞∞™¿ª ¿Œ¡ı«—¥Ÿ.
		if (pPacket->getKey() != pConnectionInfo->getKey())
		{
			FILELOG_INCOMING_CONNECTION("connectionError.log", "Wrong Key: [%s] %s", pConnectionInfo->getPCName().c_str(), pGamePlayer->getSocket()->getHost().c_str());
			throw InvalidProtocolException("invalid key");
		}

		// ¿Ã∏ß¿ª ¿Œ¡ı«—¥Ÿ.
		if (pPacket->getPCName() != pConnectionInfo->getPCName())
		{
			FILELOG_INCOMING_CONNECTION("connectionError.log", "Wrong PCName: [%s] %s", pConnectionInfo->getPCName().c_str(), pGamePlayer->getSocket()->getHost().c_str());
			throw InvalidProtocolException("invalid pc name");
		}

		// ¿œ¥‹ ¿Ã∏ß¿ª ¿˙¿Â«—¥Ÿ. æÓ¬˜«« ¥Ÿ¿Ωø° Ω«∆–«œ∏È ∞¥√º∏¶ ªË¡¶«œ¥œ±Ó π´πÊ«œ¥Ÿ.
		pGamePlayer->setID(pConnectionInfo->getPlayerID());

		// CIM¿« heartbeat∞° Ω««‡µ«±‚ ¿¸ø° ¿Áºˆ¡¡∞‘ ¡¢º”«“ ∞°¥…º∫¿Ã ¿÷¥Ÿ.
		// (≈∏¿Ãπ÷¿Ã ¡¡¿∏∏È heartbeat Ω««‡¡÷±‚*2 æ»ø°∏∏ ¡¢º”«œ∏È µ»¥Ÿ.)
		// µ˚∂Ûº≠, «ˆ¿Á Ω√∞£∞˙ expire time ¿ª ∫Ò±≥«—¥Ÿ.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (pConnectionInfo->getExpireTime() < currentTime) 
		{
			FILELOG_INCOMING_CONNECTION("connectionError.log", "Expired: [%s] %s", pConnectionInfo->getPCName().c_str(), pGamePlayer->getSocket()->getHost().c_str());

			// ¿œ¥‹ ªË¡¶«—¥Ÿ.
			g_pConnectionInfoManager->deleteConnectionInfo(pConnectionInfo->getClientIP());
			throw InvalidProtocolException("session already expired");
		}

       	// by sigi. 2002.12.7
		FILELOG_INCOMING_CONNECTION("connectionInfo.log", "Login [%s:%s] %s (%u)",
										pConnectionInfo->getPlayerID().c_str(),
										pConnectionInfo->getPCName().c_str(),
										pConnectionInfo->getClientIP().c_str(),
										pConnectionInfo->getKey());

		// ¿Œ¡ıµ«æ˙¿∏¥œ, ConnectionInfo ∏¶ ªË¡¶«—¥Ÿ.
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
	catch (NoSuchElementException & nsee) // ±◊∑± IP∏¶ ∞°¡¯ CI ∞° æ¯¿ª ∞ÊøÏ
	{ 
		FILELOG_INCOMING_CONNECTION("connectionError.log", "NoSuchConnectionInfo: %s", pGamePlayer->getSocket()->getHost().c_str());

		// »Ï.. ø¨∞· ¿Ã»ƒ CGConnect ∆–≈∂¿ª ∫∏≥ª¥¬ µÙ∑π¿Ã∞° ≥ π´ ±Ê ∞ÊøÏ
		// session ¿Ã expire µ»¥Ÿ. ¿Ã∑≤ ∞ÊøÏø°µµ ¬•∏£¿⁄!
		// (øπ∏¶ µÈæÓº≠, √÷√  ø¨∞·ø°º≠¥¬ º∫∞¯«ﬂ¿∏≥™ ±◊¥Ÿ¿Ωø° µπˆ±Î ªÛ≈¬∑Œ
		// µÈæÓ∞• ∞ÊøÏ, CGConnect ∆–≈∂¿ª ∫∏≥æ ∂ß¬Îø°¥¬ expire µ»¥Ÿ.)
		GCDisconnect gcDisconnect;
		gcDisconnect.setMessage(nsee.toString());

		pGamePlayer->sendPacket(&gcDisconnect);

		// ¿Ã∑∏∞‘ ¥¯¡ˆ∏È ªÛ¿ß IPM::processCommands()ø°º≠ disconnect √≥∏Æ«—¥Ÿ.
		throw InvalidProtocolException(nsee.toString().c_str());
	} 
	catch (InvalidProtocolException & ipe) 
	{
		FILELOG_INCOMING_CONNECTION("connectionError.log", "%s: %s", ipe.toString().c_str(), pGamePlayer->getSocket()->getHost().c_str());
		cout << endl
			 << "+-----------------------+" << endl
			 << "| Level 2 Access Denied |" << endl
			 << "+-----------------------+" << endl
			 << endl;

		GCDisconnect gcDisconnect;
		gcDisconnect.setMessage(ipe.toString());

		pGamePlayer->sendPacket(&gcDisconnect);

		// ¿Ã∑∏∞‘ ¥¯¡ˆ∏È ªÛ¿ß IPM::processCommands()ø°º≠ disconnect √≥∏Æ«—¥Ÿ.
		throw;
	}

	//----------------------------------------------------------------------
	// ∑Œ±◊¿Œ √º≈©
	//----------------------------------------------------------------------
	Statement* pStmt   = NULL;
	Result*    pResult = NULL;
 
	// ∫Ù∏µ~
	PayType         payType;
	string          payPlayDate;
	uint            payPlayHours;
	uint            payPlayFlag;
	int				billingUserKey = 0;	// by sigi. 2002.11.18
	string          familyPayPlayDate;


	try
	{
		//»°Ω«…´¿‡–Õ£¨≤ª π”√øÕªß∂À…œ¿¥µƒ¿‡–Õ£¨∑¿÷πµÙœﬂ
		//≥¬π‚ª‘–ﬁ∏ƒ2006 05 31
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT PlayerID,Race FROM Slayer WHERE Name = '%s'",pPacket->getPCName().c_str());

	

		if (pResult->getRowCount() != 1)
		{
			StringStream msg;
			msg << "Failed to load PlayerCreature data from DB. Not 1 PlayerID (" 
				<< pPacket->getPCName().c_str() << ")";

			filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

			SAFE_DELETE(pStmt);
			throw ProtocolException( msg.toString().c_str() );
		}

		if (pResult->next()) 
		{
			string spID = pResult->getString(1);
			string spRace =pResult->getString(2);

			if (spRace=="SLAYER") 
			{
				pPacket->setPCType(PC_SLAYER);
			}
			else if (spRace=="VAMPIRE")
			{
				pPacket->setPCType(PC_VAMPIRE);
			}
			else if (spRace=="OUSTERS")
			{
				pPacket->setPCType(PC_OUSTERS);
			}
			else
			{
				StringStream msg;
				msg << "Failed to load PlayerCreature data from DB. No Character(" 
					<< spID.c_str() << "!="
					<< pGamePlayer->getID().c_str() << ")";

				filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

				SAFE_DELETE(pStmt);
				throw ProtocolException( msg.toString().c_str() );
			}
	
			
			if (strcasecmp(spID.c_str(), pGamePlayer->getID().c_str()) != 0) 
			{
				StringStream msg;
				msg << "Failed to load PlayerCreature data from DB. No Character(" 
					<< spID.c_str() << "!="
					<< pGamePlayer->getID().c_str() << ")";

				filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

				SAFE_DELETE(pStmt);
				throw ProtocolException( msg.toString().c_str() );
			}
		}

		SAFE_DELETE(pStmt);

		//pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

#ifdef __THAILAND_SERVER__

		pResult = pStmt->executeQuery("SELECT PlayerID, CurrentServerGroupID, LogOn, SpecialEventCount, PayType, PayPlayDate, PayPlayHours, PayPlayFlag, BillingUserKey, FamilyPayPlayDate, Birthday FROM Player WHERE PlayerID = '%s'", pGamePlayer->getID().c_str());

#else

		pResult = pStmt->executeQuery("SELECT PlayerID, CurrentServerGroupID, LogOn, SpecialEventCount, PayType, PayPlayDate, PayPlayHours, PayPlayFlag, BillingUserKey, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s'", pGamePlayer->getID().c_str());

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
		pGamePlayer->setPermission( isAdultByBirthdayDate( Birthday ) );
#endif

		pGamePlayer->setServerGroupID(GID);
		pGamePlayer->setSpecialEventCount(scount);
		pGamePlayer->setBillingUserKey( billingUserKey );

		if (logon != "LOGOFF")
		{
			SAFE_DELETE(pStmt);
			char str[80];
			sprintf(str, "Already connected player ID: %s, %s", playerID.c_str(), logon.c_str());
			throw ProtocolException(str);
		}

		pStmt->executeQuery("UPDATE Player SET LogOn='GAME' WHERE PlayerID = '%s' AND LogOn='LOGOFF'", playerID.c_str());

		// LogOn¿Ã LOGOFF∞° æ∆¥œ∞≈≥™.. µÓµÓ.. by sigi. 2002.5.15
		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			char str[80];
			sprintf(str, "Already connected player ID2: %s, %s", playerID.c_str(), logon.c_str());
			throw ProtocolException(str);
		}

		string connectIP = pGamePlayer->getSocket()->getHost();

		// ∫Ù∏µ by sigi. 2002.5.31
#if defined(__CONNECT_BILLING_SYSTEM__)
		if ( payType == PAY_TYPE_FREE )
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
// by sigi. 2002.11.18. ¡¶«—¿˚ π´∑· ªÁøÎ¿⁄. - -; ¿œ¥‹ login
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
	// ΩΩ∑π¿ÃæÓ ∂«¥¬ πÏ∆ƒ¿ÃæÓ ƒ≥∏Ø≈Õ∏¶ ∑Œµ˘«—¥Ÿ.
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
				cout << " ø©±‚¥¬ µ«≥™ø‰" << endl;
				throw ProtocolException("Failed to load SLAYER data from DB");
			}

			// ¿Ø∑·¡∏ø°º≠∏∏ ¿˚øÎµ«¥¬ æ∆¿Ã≈€ ∂ßπÆø° πÿø°º≠ √º≈©
			//pSlayer->loadItem();
			//Assert(pSlayer->getName() == pPacket->getPCName());
			if (pSlayer->getName() != pPacket->getPCName())
			{
				cout << "Different Name : " << pSlayer->getName().c_str()
						<< ", " << pPacket->getPCName().c_str() << endl;

				Assert(pSlayer->getName() == pPacket->getPCName());
			}

			pGamePlayer->setCreature(pSlayer);

			// Slayer∏¶ TelephoneCenterø° µÓ∑œ«—¥Ÿ.
			//g_pTelephoneCenter->addSlayer(pSlayer);
		
			// ¡÷±‚ »∏∫π ¿Ã∫•∆Æ∏¶ «√∑π¿ÃæÓ ∞¥√ºø° √ﬂ∞°«—¥Ÿ.
			// ¿Ã∂ß ±‚∫ª¿˚¿∏∑Œ 10√  »∏∫π¿ª ø¯ƒ¢¿∏∑Œ «—¥Ÿ.
			// (setDeadline¿« ∆ƒ∂ÛπÃ≈Õ¥¬ 0.1 √ ∂Û¥¬ µ• ¿Ø¿««“ ∞Õ)
			EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
			pEventRegeneration->setDeadline(10* 10);
			pGamePlayer->addEvent(pEventRegeneration);

			// PCFinderø° √ﬂ∞°«—¥Ÿ.
			// PCFinder¿« ªË¡¶¥¬ ~GamePlayer()ø°º≠∏∏ «—¥Ÿ.
			try {
				g_pPCFinder->addCreature(pSlayer);
			} catch (DuplicatedException& de) {
				bAlreadyConnected = true;
			}

			// ¿ÃπÃ ¡¢º”¡ﬂ¿Œ ∞ÊøÏ∞° æ∆¥œ∂Û∏È.. by sigi. 2002.8.29
			if (!bAlreadyConnected)
			{
				// ±ÊµÂ «ˆ¿Á ¡¢º” ∏‚πˆ ∏ÆΩ∫∆Æø° √ﬂ∞°«—¥Ÿ.
				if ( pSlayer->getGuildID() != 99 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pSlayer->getGuildID() );
					if ( pGuild != NULL )
					{
						// sharedserver∑Œ ¡¢º”¿ª æÀ∏Æ∞Ì DB µµ update «—¥Ÿ.
						try {
							pGuild->addCurrentMember( pSlayer->getName() );

							GSGuildMemberLogOn gsGuildMemberLogOn;
							gsGuildMemberLogOn.setGuildID( pGuild->getID() );
							gsGuildMemberLogOn.setName( pSlayer->getName() );
							gsGuildMemberLogOn.setLogOn( true );
							gsGuildMemberLogOn.setServerID(  g_pConfig->getPropertyInt("ServerID") );

							g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

							// DB æ˜µ•¿Ã∆Æ
							BEGIN_DB
							{
								pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
								pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 1 WHERE Name = '%s'", pSlayer->getName().c_str() );
							}
							END_DB( pStmt )

						} catch (DuplicatedException& t) {
							// ¿œ¥‹ π´Ω√«—¥Ÿ. by sigi. 2002.8.29
							filelog( "guildBug.log", "%s", t.toString().c_str());
						}
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(), pSlayer->getName().c_str() );
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

			// ¿Ø∑·¡∏ø°º≠∏∏ ¿˚øÎµ«¥¬ æ∆¿Ã≈€ ∂ßπÆø° πÿø°º≠ √º≈©
			//pVampire->loadItem();
			Assert(pVampire->getName() == pPacket->getPCName());

			pGamePlayer->setCreature(pVampire);

			// ¡÷±‚ »∏∫π ¿Ã∫•∆Æ∏¶ «√∑π¿ÃæÓ ∞¥√ºø° √ﬂ∞°«—¥Ÿ.
			// ¿Ã∂ß ±‚∫ª¿˚¿∏∑Œ 10√  »∏∫π¿ª ø¯ƒ¢¿∏∑Œ «—¥Ÿ.
			// (setDeadline¿« ∆ƒ∂ÛπÃ≈Õ¥¬ 0.1 √ ∂Û¥¬ µ• ¿Ø¿««“ ∞Õ)
			EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
			pEventRegeneration->setDeadline(10* 10);
			pGamePlayer->addEvent(pEventRegeneration);

			// PCFinderø° √ﬂ∞°«—¥Ÿ.
			// PCFinder¿« ªË¡¶¥¬ ~GamePlayer()ø°º≠∏∏ «—¥Ÿ.
			try {
				g_pPCFinder->addCreature(pVampire);
			} catch (DuplicatedException& de) {
				bAlreadyConnected = true;
			}

			// ¿ÃπÃ ¡¢º”¡ﬂ¿Œ ∞ÊøÏ∞° æ∆¥œ∂Û∏È.. by sigi. 2002.8.29
			if (!bAlreadyConnected)
			{
				// ±ÊµÂ «ˆ¿Á ¡¢º” ∏‚πˆ ∏ÆΩ∫∆Æø° √ﬂ∞°«—¥Ÿ.
				if ( pVampire->getGuildID() != 0 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pVampire->getGuildID() );
					if ( pGuild != NULL )
					{
						// sharedserver ø° ¡¢º”¿ª æÀ∏Æ∞Ì DB µµ update «—¥Ÿ.
						try {
							pGuild->addCurrentMember( pVampire->getName() );

							GSGuildMemberLogOn gsGuildMemberLogOn;
							gsGuildMemberLogOn.setGuildID( pGuild->getID() );
							gsGuildMemberLogOn.setName( pVampire->getName() );
							gsGuildMemberLogOn.setLogOn( true );
							gsGuildMemberLogOn.setServerID(  g_pConfig->getPropertyInt("ServerID") );

							g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

							// DB æ˜µ•¿Ã∆Æ
							BEGIN_DB
							{
								pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
								pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 1 WHERE Name = '%s'", pVampire->getName().c_str() );
							}
							END_DB( pStmt )
						} catch (DuplicatedException& t) {
							// ¿œ¥‹ π´Ω√«—¥Ÿ. by sigi. 2002.8.29
							filelog( "guildBug.log", "%s", t.toString().c_str());
						}
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str() );
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

			// ¿Ø∑·¡∏ø°º≠∏∏ ¿˚øÎµ«¥¬ æ∆¿Ã≈€ ∂ßπÆø° πÿø°º≠ √º≈©
			//pVampire->loadItem();
			Assert(pOusters->getName() == pPacket->getPCName());
			//filelog("Ousters.txt","CGConectHandler.cpp 0,HP:%d,MAXHP:%d,MP:%d,MAXMP:%d",  (int)pOusters->getHP( ATTR_CURRENT), (int)pOusters->getHP(ATTR_MAX),(int)pOusters->getMP(ATTR_CURRENT), (int)pOusters->getMP(ATTR_MAX));

			pGamePlayer->setCreature(pOusters);

			// ¡÷±‚ »∏∫π ¿Ã∫•∆Æ∏¶ «√∑π¿ÃæÓ ∞¥√ºø° √ﬂ∞°«—¥Ÿ.
			// ¿Ã∂ß ±‚∫ª¿˚¿∏∑Œ 10√  »∏∫π¿ª ø¯ƒ¢¿∏∑Œ «—¥Ÿ.
			// (setDeadline¿« ∆ƒ∂ÛπÃ≈Õ¥¬ 0.1 √ ∂Û¥¬ µ• ¿Ø¿««“ ∞Õ)
			EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
			pEventRegeneration->setDeadline(10* 10);
			pGamePlayer->addEvent(pEventRegeneration);

			// PCFinderø° √ﬂ∞°«—¥Ÿ.
			// PCFinder¿« ªË¡¶¥¬ ~GamePlayer()ø°º≠∏∏ «—¥Ÿ.
			try {
				g_pPCFinder->addCreature(pOusters);
			} catch (DuplicatedException& de) {
				bAlreadyConnected = true;
			}

			// ¿ÃπÃ ¡¢º”¡ﬂ¿Œ ∞ÊøÏ∞° æ∆¥œ∂Û∏È.. by sigi. 2002.8.29
			if (!bAlreadyConnected)
			{
				// ±ÊµÂ «ˆ¿Á ¡¢º” ∏‚πˆ ∏ÆΩ∫∆Æø° √ﬂ∞°«—¥Ÿ.
				if ( pOusters->getGuildID() != 66 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pOusters->getGuildID() );
					if ( pGuild != NULL )
					{
						// sharedserver ø° ¡¢º”¿ª æÀ∏Æ∞Ì DB µµ update «—¥Ÿ.
						try {
							pGuild->addCurrentMember( pOusters->getName() );

							GSGuildMemberLogOn gsGuildMemberLogOn;
							gsGuildMemberLogOn.setGuildID( pGuild->getID() );
							gsGuildMemberLogOn.setName( pOusters->getName() );
							gsGuildMemberLogOn.setLogOn( true );
							gsGuildMemberLogOn.setServerID(  g_pConfig->getPropertyInt("ServerID") );

							g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

							// DB æ˜µ•¿Ã∆Æ
							BEGIN_DB
							{
								pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
								pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 1 WHERE Name = '%s'", pOusters->getName().c_str() );
							}
							END_DB( pStmt )
						} catch (DuplicatedException& t) {
							// ¿œ¥‹ π´Ω√«—¥Ÿ. by sigi. 2002.8.29
							filelog( "guildBug.log", "%s", t.toString().c_str());
						}
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pOusters->getGuildID(), pOusters->getName().c_str() );
				}
			}
		}
	//}

				cout << " ø©±‚¥¬ µ«≥™ø‰2" << endl;

	// ¿Ã??¡¢º” ¡ﬂ¿Œ ∞ÊøÏ¿« √≥∏Æ. 
	// PCFinderø°º≠¿« DuplicatedException¿ª ∏Ì»Æ«œ∞‘ √≥∏Æ«œ±‚ ¿ß«ÿº≠
	// ∫Øºˆ∏¶ µ÷º≠ √º≈©«—¥Ÿ. 
	// æ∆∏∂ ±ÊµÂ¿« DuplicatedException∂ßπÆø° 
	// PCFinderø°º≠ πÆ¡¶∞° ª˝±‰∞Õ ∞∞¥Ÿ.
	// by sigi. 2002.8.29
	if (bAlreadyConnected)
	{
		SAFE_DELETE(pSlayer);
		SAFE_DELETE(pVampire);
		SAFE_DELETE(pOusters);

		pGamePlayer->setID( string("") );	// LogOn¿∫ 'LOGOFF'∞° µ«¥¬∞… ∏∑¥¬¥Ÿ.
		pGamePlayer->setCreature( NULL );	// PCFinderø°º≠ delete«œ¥¬∞… ∏∑¥¬¥Ÿ.

		char str[80];
		sprintf(str, "Already connected player ID3(Dup): %s", pPacket->getPCName().c_str());
		throw ProtocolException(str);
	}

	//----------------------------------------------------------------------
	// PC∏¶ PCFinderøÕ ¡∏ø° µÓ∑œ«—¥Ÿ.
	//----------------------------------------------------------------------
	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	EventHeadCount* pEventHeadCount = new EventHeadCount(pGamePlayer);
	pEventHeadCount->setDeadline(18000);
	pGamePlayer->addEvent(pEventHeadCount);
				cout << " ø©±‚¥¬ µ«≥™ø‰3" << endl;
	if ( pCreature->isGOD() )
	{
		EffectGhost* pEffect = new EffectGhost(pCreature);
		pCreature->getEffectManager()->addEffect( pEffect );
		pCreature->setFlag(Effect::EFFECT_CLASS_GHOST);
		pCreature->setMoveMode(Creature::MOVE_MODE_FLYING);
	}
	else
	{
#ifdef __TEST_SERVER__
		EventAuth* pAuth = new EventAuth( pGamePlayer );
		pGamePlayer->addEvent( pAuth );
		cout << "ø£«¡∑Œ≈ÿ∆Æ ¿Œ¡ı ≈∏¿Ã∏” ∫Ÿ¿‘¥œ¥Ÿ : " << pGamePlayer->getID() << endl;
#endif
	}

	if ( pCreature->getCompetenceShape() == 0 )
	{
		EffectGnomesWhisper* pEffect = new EffectGnomesWhisper( pCreature );
		pEffect->setLevel(30);

		pCreature->addEffect( pEffect );
		pCreature->setFlag( pEffect->getEffectClass() );
	}
				cout << " ø©±‚¥¬ µ«≥™ø‰4" << endl;
	// º∫¿Ã≥™ º∫ ¥¯¿¸ æ»¿∏∑Œ ∑Œ±◊¿Œ«“ ºˆ æ¯¥Ÿ.
	ZoneID_t castleZoneID;
	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pCreature->getZoneID());

	bool isCastleZone = g_pCastleInfoManager->getCastleZoneID( pCreature->getZoneID(), castleZoneID );
	bool isMasterLair = pZoneInfo->isMasterLair() || GDRLairManager::Instance().isGDRLairZone( pCreature->getZoneID() );
	bool isPKZone = g_pPKZoneInfoManager->isPKZone( pCreature->getZoneID() );
	bool isMaze = ( pCreature->getZoneID() == 3001 ) ||
					( pCreature->getZoneID() == 3002 ) ||
					( pCreature->getZoneID() == 3003 ) ||
					( pCreature->getZoneID() == 1013 ) ; //add by sonic 2006.10.30
	bool isEventZone = EventZoneInfoManager::Instance().getEventZoneInfo( pCreature->getZoneID() ) != NULL;
	bool isBeginnerZone = pCreature->getZoneID() == 1122 && !canEnterBeginnerZone(pCreature);
	bool isDynamicZone = g_pDynamicZoneManager->isDynamicZone( pCreature->getZoneID() );
	
	if ( pCreature->isPC() ) //&& pCreature->isPLAYER() )
	{
		ZONE_COORD zoneCoord;
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		if ( isCastleZone || isMasterLair || isPKZone || isMaze || isEventZone || isBeginnerZone || isDynamicZone )
		{
			if ( g_pResurrectLocationManager->getPosition( pPC, zoneCoord ) )
			{
				pCreature->setZoneID( zoneCoord.id );
				pCreature->setXY( zoneCoord.x, zoneCoord.y );
			}
		}
	}
				cout << " ø©±‚¥¬ µ«≥™ø‰5" << endl;
	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);
	
#if defined(__PAY_SYSTEM_FREE_LIMIT__)
	try {
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());
		Assert( pZoneInfo != NULL );

		Assert( pCreature->isPC() );
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		// ¿Ø∑· ¡∏¿Ã≥™ «¡∏ÆπÃæˆ ¡∏¿Ã æ∆¥“ ∞ÊøÏ 30 ∑π∫ß ¿Ã«œ¿« ¡æ∑Æ¡¶ ªÁøÎ¿⁄ø°∞‘¥¬ ∞˙±›«œ¡ˆ æ ¥¬¥Ÿ.
		if ( ( pGamePlayer->isPayPlaying() || pGamePlayer->isPremiumPlay() )
			&& pGamePlayer->getPayType() == PAY_TYPE_TIME
			&& pPC->canPlayFree()
			&& ! ( pZoneInfo->isPayPlay() || pZone->isPremiumZone() )
		)
		{
			pGamePlayer->logoutPayPlay( pGamePlayer->getID(), false, false );
		}

		// ¿Ø∑·»≠ ¡∏¿Ã∞Ì ¿Ø∑·ªÁøÎ¡ﬂ¿Ã æ∆¥œ∏È..
		// §Ã.§– 2003.03.16 ¿œπ› « µÂµµ «¡∏ÆπÃæˆ¡∏¿Ã¥Ÿ. π´∑·ªÁøÎ¿⁄µµ « µÂ∑Œ¥¬ ∑Œ±◊¿Œ µ«æÓæﬂ «—¥Ÿ.
		if ( (pZoneInfo->isPayPlay()) //|| pZoneInfo->isPremiumZone())
			&& !pGamePlayer->isPayPlaying() )
		{
			// ¿Ø∑· º≠∫ÒΩ∫ ªÁøÎ ∫“∞°¿Œ ∞ÊøÏ
			// ΩΩ∑π¿ÃæÓ¥¬ ø°ΩΩ≥≤µøø°º≠ ∫Œ»∞«œ¥¬ ∞˜¿∏∑Œ ∞£¥Ÿ.
			// πÏ∆ƒ¿ÃæÓ¥¬ ∏≤∫∏≥≤µøø°º≠ ∫Œ»∞«œ¥¬ ∞˜¿∏∑Œ ∞£¥Ÿ.
			ZONE_COORD zoneCoord;

			if ( g_pResurrectLocationManager->getRaceDefaultPosition( pPC->getRace(), zoneCoord ) )
			{
				pCreature->setZoneID( zoneCoord.id );
				pCreature->setXY( zoneCoord.x, zoneCoord.y );
			}
		}
	} catch (NoSuchElementException&) {
		throw Error("ZoneInfoø° zoneID∞° æ¯¥Ÿ.");
	}
#elif defined(__CONNECT_BILLING_SYSTEM__)
	if ( pGamePlayer->isMetroFreePlayer() )
	{
		pGamePlayer->setBillingUserStatus( "MT" );
		pGamePlayer->setPremiumPlay();
	}
	else
	{
		try {
			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());
			Assert( pZoneInfo != NULL );

			Assert( pCreature->isPC() );
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPC != NULL );

			// æ∆¡˜ ∫Ù∏µ º≠πˆø°º≠ ¿Ø∑· ªÁøÎ¿⁄¿Œ¡ˆ ¿Œ¡ı »Æ¿Œ¿ª πﬁ¡ˆ æ æ“¥Ÿ.
			// ¿Ø∑·»≠ ¡∏¿Ã∂Û∏È ¿œ¥‹ ¿Ø∑· ªÁøÎ¿⁄∂Û∑Œ ª˝∞¢«—¥Ÿ.
			// premium ¿ª ƒ— ≥ıæ∆æﬂ¡ˆ π´∑· ªÁøÎ¿œ∂ß ZonePlayerManager ø°º≠ π´∑·¡∏¿∏∑Œ ø≈∞‹¡ÿ¥Ÿ.
			if ( pZoneInfo->isPayPlay() )
			{
				pGamePlayer->setPremiumPlay();
			}

			} catch (NoSuchElementException&) {
				throw Error("ZoneInfoø° zoneID∞° æ¯¥Ÿ.");
		}

		// session ∞™¿ª ¡§«ÿµ–¥Ÿ. by sigi. 2002.11.18
		pGamePlayer->setBillingSession();

		// ∫Ù∏µº≠πˆø° ∞‘¿” Ω√¿€¿ª æÀ∏∞¥Ÿ.
		pGamePlayer->sendBillingLogin();
	}

#elif defined(__PAY_SYSTEM_ZONE__)
	try {
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());

		// ¿Ø∑·»≠ ¡∏¿Ã∞Ì ¿Ø∑·ªÁøÎ¡ﬂ¿Ã æ∆¥œ∏È..
		if (pZoneInfo!=NULL
			&& (pZoneInfo->isPayPlay() || pZoneInfo->isPremiumZone())
			&& !pGamePlayer->isPayPlaying() )
		{
			bool bEnterZone = true;

			string connectIP = pGamePlayer->getSocket()->getHost();

			// ¿Ø∑· º≠∫ÒΩ∫ ªÁøÎ¿Ã ∞°¥…«—∞°?
			// ¿Ø∑· º≠∫ÒΩ∫ ªÁøÎ¿Ã æ»µ«∞Ì ¿Ø∑· ¡∏¿Ã∂Û∏È µÈæÓ∞• ºˆ æ¯¥Ÿ.
			if ( !pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID())
				&& pZoneInfo->isPayPlay() )
			{
				bEnterZone = false;
			}

			if ( !pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID())
				&& ( pZone->getZoneID() == 1131 ||
					 pZone->getZoneID() == 1132 ||
					 pZone->getZoneID() == 1133 ||
					 pZone->getZoneID() == 1134 ) )
			{
				bEnterZone = false;
			}

			Assert( pCreature->isPC() );
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPC != NULL );

			if (!bEnterZone)
			{
				// ¿Ø∑· º≠∫ÒΩ∫ ªÁøÎ ∫“∞°¿Œ ∞ÊøÏ
				// ΩΩ∑π¿ÃæÓ¥¬ ø°ΩΩ≥≤µøø°º≠ ∫Œ»∞«œ¥¬ ∞˜¿∏∑Œ ∞£¥Ÿ.
				// πÏ∆ƒ¿ÃæÓ¥¬ ∏≤∫∏≥≤µøø°º≠ ∫Œ»∞«œ¥¬ ∞˜¿∏∑Œ ∞£¥Ÿ.
				ZONE_COORD zoneCoord;
//				bool bFindPos = false;

				if ( g_pResurrectLocationManager->getRaceDefaultPosition( pPC->getRace(), zoneCoord ) )
				{
					pCreature->setZoneID( zoneCoord.id );
					pCreature->setXY( zoneCoord.x, zoneCoord.y );
				}
			}
		}
	} catch (NoSuchElementException&) {
		throw Error("ZoneInfoø° zoneID∞° æ¯¥Ÿ.");
	}
#elif defined(__CONNECT_CBILLING_SYSTEM__)
	// ∫Ù∏µ º≠πˆ∑Œ ¡÷±‚¿˚¿∏∑Œ minus point/minute ∆–≈∂¿ª ∫∏≥ª¥¬ ¿Ã∫•∆Æ∏¶ ∫Ÿ¿Œ¥Ÿ.
	EventCBilling* pEvent = new EventCBilling( pGamePlayer );
	pEvent->setDeadline( g_pCBillingPlayerManager->getMinusIntervalInt() * 600 );
	pGamePlayer->addEvent( pEvent );

	// ¡ﬂ±π ∫Ù∏µ¿∫ ¿¸∏È ¿Ø∑·»≠ ¿Ãπ«∑Œ ø©±‚±Ó¡ˆ ø‘¥Ÿ∏È ¿Ø∑· ªÁøÎ¿⁄¿Ã¥Ÿ. π´∑· ªÁøÎ¿⁄¿œ ∞ÊøÏ ∑Œ±◊¿Œ º≠πˆø°º≠ ∏∑»˘¥Ÿ.
	pGamePlayer->setPayPlayer( true );
	pGamePlayer->setPremiumPlay();

	// send Login
	pGamePlayer->setCBillingVerified( g_pCBillingPlayerManager->sendLogin( pGamePlayer ) );
#else
	// æ∆π´∞Õµµ º≥¡§µ«æÓ ¿÷¡ˆ æ ¿∏∏È
	// ∞¡ ¿Ø∑· ªÁøÎ¿⁄∂Û∞Ì «ÿπˆ∏Æ¿⁄
	pGamePlayer->setPremiumPlay();
#endif

	// test code
	/*
	// ∑Œ±◊¿Œ «œ∞Ì.. πŸ∑Œ π∫∞° ∏ﬁºº¡ˆ∏¶ ª—∑¡¡÷¥¬ ∫Œ∫–. by sigi. 2002.12.11
	EventSystemMessage* pESM = new EventSystemMessage( pGamePlayer );
	pESM->setDeadline( 0 );
	pESM->addMessage("¿Ã∞Õ¿∫ ≈◊Ω∫∆Æ Ω√Ω∫≈€ ∏ﬁΩ√¡ˆ");
	pESM->addMessage("¡¶¥Î∑Œ √‚∑¬µ«±Ê πŸ∂ˆª”.. -_-;;");
	pGamePlayer->addEvent( pESM );
	*/

	// ¿Ø∑·¡∏ø°º≠∏∏ ¿˚øÎµ«¥¬ æ∆¿Ã≈€ ∂ßπÆø° ø©±‚º≠ √º≈©
	// 2002.8.26. by sigi
				cout << " æ∆¿Ã≈€ ∑ŒµÂ ∫Œ∫– ¿Ã ∫Œ∫–¿Ã æ»µ«∏È ¿Ã∫Œ∫–¿Ã ø¿∑˘¥Ÿ." << endl;
	if (pPacket->getPCType() == PC_SLAYER) 
	{
		Assert(pSlayer!=NULL);
		pSlayer->loadItem( true );
	}
	else if ( pPacket->getPCType() == PC_VAMPIRE )
	{
		Assert(pVampire!=NULL);
		pVampire->loadItem( true );
	}
	else if ( pPacket->getPCType() == PC_OUSTERS )
	{
		Assert(pOusters!=NULL);
		pOusters->loadItem( true );
	}


	// ΩΩ∑π¿ÃæÓ∂Û∏È ±ÊµÂ ≥ª∫Œ, πÏ∆ƒ¿ÃæÓ∂Û∏È ∑πæÓ ≥ª∫Œø°º≠ 
	// Ω√¿€«œ¥¬ ∞ÊøÏ, HP∏¶ ∏∏∂•¿∏∑Œ √§øˆ¡ÿ¥Ÿ. 
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
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		switch ( pZone->getZoneID() )
		{
			case 1311:
 				//filelog("Ousters.txt","CGConectHandler.cpp 1,HP:%d,MAXHP:%d,MP:%d,MAXMP:%d",  (int)pOusters->getHP( ATTR_CURRENT), (int)pOusters->getHP(ATTR_MAX),(int)pOusters->getMP(ATTR_CURRENT), (int)pOusters->getMP(ATTR_MAX));
				pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
				//chengh add 2005 10 02
				pOusters->setMP(pOusters->getMP(ATTR_MAX), ATTR_CURRENT);
				//filelog("Ousters.txt","CGConectHandler.cpp 2,HP:%d,MAXHP:%d,MP:%d,MAXMP:%d",  (int)pOusters->getHP( ATTR_CURRENT), (int)pOusters->getHP(ATTR_MAX),(int)pOusters->getMP(ATTR_CURRENT), (int)pOusters->getMP(ATTR_MAX));

			default:
				break;
		}
	}

	// ƒ˘Ω∫∆Æ ∏≈¥œ¿˙∏¶ ∑ŒµÂ«—¥Ÿ.
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	pPC->getQuestManager()->load();

	// ≈©∏Æ√≥ ¿⁄Ω≈∞˙ º“¿Ø æ∆¿Ã≈€µÈ¿« OID∏¶ «“¥Áπﬁ¥¬¥Ÿ.
	// ¿ÃπÃ Creature::load()ø°º≠ Zone ¿Ã ¡ˆ¡§µ«æÓ ¿÷æÓæﬂ «—¥Ÿ.
	pCreature->registerObject();

	// ¡÷±‚ ¿˙¿Â ¿Ã∫•∆Æ∏¶ «√∑π¿ÃæÓ ∞¥√ºø° √ﬂ∞°«—¥Ÿ.
	// ¿Ã∂ß ±‚∫ª¿˚¿∏∑Œ 10∫– ¿˙¿Â¿ª ø¯ƒ¢¿∏∑Œ «—¥Ÿ.
	// (setDeadline¿« ∆ƒ∂ÛπÃ≈Õ¥¬ 0.1 √ ∂Û¥¬ µ• ¿Ø¿««“ ∞Õ)
	//EventSave* pEventSave = new EventSave(pGamePlayer);
	//pEventSave->setDeadline(600* 10);
	//pGamePlayer->addEvent(pEventSave);

#ifdef __USE_ENCRYPTER__
	// æœ»£»≠ ƒ⁄µÂ µÓ∑œ. ¡ˆ±›¿∫ objectID∑Œ «œ±‚ ∂ßπÆø°.. by sigi. 2002.11.27
    pGamePlayer->setEncryptCode();
#endif

//	pGamePlayer->sendPacket( SystemAvailabilitiesManager::getInstance()->getAvailabilitiesPacket() );
	SEND_SYSTEM_AVAILABILITIES(pGamePlayer);

	//----------------------------------------------------------------------
	// GCUpdateInfo øÎ PC ¡§∫∏, SkillInfo ∏¶ ±∏º∫«—¥Ÿ.
	//----------------------------------------------------------------------

				cout << " ø©±‚¥¬ µ«≥™ø‰7" << endl;

	GCUpdateInfo gcUpdateInfo;
			
	makeGCUpdateInfo(&gcUpdateInfo, pCreature);
			
	pGamePlayer->sendPacket(&gcUpdateInfo);

	sendPetInfo( pGamePlayer );

	string host = pGamePlayer->getSocket()->getHost();

	IP_t IP = pGamePlayer->getSocket()->getHostIP();

	// ∏∂¡ˆ∏∑¿∏∑Œ IP¿« ¡§∫∏∏¶ DBø° INSERT «—¥Ÿ.

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
// YYYY-MM-DD ∑Œ º∫¿Œ ∆«∫∞
//
//////////////////////////////////////////////////////////////////////////////
bool
isAdultByBirthdayDate(const string& birthday)
{
    StringStream AdultSSN;

    time_t daytime = time(0);
    tm Timec;
    localtime_r( &daytime, &Timec );

    AdultSSN << Timec.tm_year - 18;
    // tm_mon - range 0 to 11
    if ( (Timec.tm_mon+1) < 10 ) AdultSSN << "0";
    AdultSSN << (Timec.tm_mon+1);
    if ( Timec.tm_mday < 10 ) AdultSSN << "0";
    AdultSSN << Timec.tm_mday;

    cout << "Birthday = " << birthday.c_str() << " ADULTSSN = " << AdultSSN.toString().c_str() << endl;

    int year  = atoi( birthday.substr(0,4).c_str() );
    int month = atoi( birthday.substr(5,2).c_str() );
    int day   = atoi( birthday.substr(8,2).c_str() );

    if ( Timec.tm_year - 18 + 1900 > year )
    {
        cout << "æÓ∏•" << endl;
        return true;
    }
    else if ( Timec.tm_year - 18 + 1900 == year )
    {
        if ( Timec.tm_mon + 1 > month )
        {
            cout << "æÓ∏•" << endl;
            return true;
        }
        else if ( Timec.tm_mon + 1 == month )
        {
            if ( Timec.tm_mday >= day )
            {
                cout << "æÓ∏•" << endl;
                return true;
            }
        }
    }

    cout << "æ÷µÈ" << endl;
    return false;
}

#endif

