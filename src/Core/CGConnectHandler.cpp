//////////////////////////////////////////////////////////////////////////////
// Filename    : CGConnectHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGConnect.h"

#ifdef __GAME_SERVER__
#include <stdio.h>

#include <fstream>
#include <list>

#include "BillingPlayerManager.h"
#include "CastleInfoManager.h"
#include "CreatureUtil.h"
#include "DB.h"
#include "EffectGhost.h"
#include "Encrypter.h"
#include "EventHeadCount.h"
#include "EventRegeneration.h"
#include "EventSave.h"
#include "EventSystemMessage.h"
#include "EventZoneInfo.h"
#include "GCDisconnect.h"
#include "GCSystemMessage.h"
#include "GCUpdateInfo.h"
#include "GSGuildMemberLogOn.h"
#include "GamePlayer.h"
#include "Guild.h"
#include "GuildManager.h"
#include "IncomingPlayerManager.h"
#include "LogClient.h"
#include "LogDef.h"
#include "NPCInfo.h"
#include "NicknameBook.h"
#include "Ousters.h"
#include "PCFinder.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "PKZoneInfoManager.h"
#include "PacketUtil.h"
#include "PlayerCreature.h"
#include "Properties.h"
#include "ResurrectLocationManager.h"
#include "SharedServerManager.h"
#include "Slayer.h"
#include "TelephoneCenter.h"
#include "Thread.h"
#include "Vampire.h"
#include "WeatherManager.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "ZoneUtil.h"
#include "mission/QuestManager.h"
#include "skill/EffectGnomesWhisper.h"
// #include "GCLoadInventory.h"
#include "GDRLairManager.h"
#include "SystemAvailabilitiesManager.h"
#include "chinabilling/CBillingInfo.h"
#include "types/ServerType.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
#include "EventCBilling.h"
#include "chinabilling/CBillingPlayerManager.h"
#endif

#include "DynamicZoneManager.h"
#include "EventAuth.h"

#endif

bool isAdultByBirthdayDate(const string& birthday);


//////////////////////////////////////////////////////////////////////////////
// CGConnectHandler::execute()
//
// ÀÌ ÆÐÅ¶Àº ·Î±×ÀÎ¼­¹ö¿¡¼­ ÃÖÃÊ·Î °ÔÀÓ ¼­¹ö·Î ¿¬°áÇÒ ¶§, ¶Ç´Â °ÔÀÓ ¼­¹ö¿¡¼­
// ´Ù¸¥ °ÔÀÓ ¼­¹ö·Î ÀÌµ¿ÇÒ ¶§, Å¬¶óÀÌ¾ðÆ®°¡ ¼­¹ö·Î Àü¼ÛÇÏ´Â ÃÖÃÊÀÇ ÆÐÅ¶ÀÌ´Ù.
// ÀÌ¶§ ÇÃ·¹ÀÌ¾î °´Ã¼´Â »õ·Î »ý°Ü³­ »óÅÂÀÌ°í, ÀÌ ÇÃ·¹ÀÌ¾î °´Ã¼´Â IPM ¿¡¼­
// °ü¸®µÇ´Â »óÅÂÀÌ´Ù.
//
// ´ç¿¬È÷ ÃÖÃÊÀÇ ÆÐÅ¶À¸·Î ´Ù¸¥ ÆÐÅ¶ÀÌ ³Ñ¾î¿À´Â °æ¿ì¶ó¸é, ÀÌ°ÍÀº ÇØÅ· ½Ãµµ¶ó°í
// ºÁµµ ¹«¹æÇÏ¹Ç·Î ÀÌ ÆÐÅ¶ÀÌ ÃÖÃÊÀÎÁö °Ë»çÇØ¾ß ÇÑ´Ù. ÀÌ¸¦ À§ÇØ¼­ ÇÃ·¹ÀÌ¾î °´Ã¼¿¡
// ÀÌÀü ÆÐÅ¶À» ÀúÀåÇÏ°í ÀÖÀ¸¹Ç·Î, ÀÌ °ªÀÌ NULL ÀÎÁö¸¸ º¸¸é µÇ°Ú´Ù.
//
// Àß¸øµÈ ÆÐÅ¶ÀÌ¶ó¸é, ban ¿¡ µî·ÏÇÏ°í Á¢¼ÓÀ» Á¾·áÇÑ´Ù.
//////////////////////////////////////////////////////////////////////////////
void CGConnectHandler::execute(CGConnect* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX __BEGIN_DEBUG

#ifdef __GAME_SERVER__

        Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

    // set MAC Address
    pGamePlayer->setMacAddress(pPacket->getMacAddress());

    // ÀÌ ÆÐÅ¶À» ConnectionInfo °´Ã¼¸¦ °®°í ¿Â´Ù.
    // Å©·¡Ä¿´Â Å°°ª°ú Ä³¸¯ÅÍ ÀÌ¸§À» ÀÏÁ¤ ½Ã°£¾È¿¡ ¸ÂÃç¾ß¸¸ Á¢¼ÓÀÌ °¡´ÉÇÏ´Ù.
    try {
        ConnectionInfo* pConnectionInfo =
            g_pConnectionInfoManager->getConnectionInfo(pGamePlayer->getSocket()->getHost());

        // Å°°ªÀ» ÀÎÁõÇÑ´Ù.
        if (pPacket->getKey() != pConnectionInfo->getKey()) {
            FILELOG_INCOMING_CONNECTION("connectionError.log", "Wrong Key: [%s] %s",
                                        pConnectionInfo->getPCName().c_str(),
                                        pGamePlayer->getSocket()->getHost().c_str());
            throw InvalidProtocolException("invalid key");
        }

        // ÀÌ¸§À» ÀÎÁõÇÑ´Ù.
        if (pPacket->getPCName() != pConnectionInfo->getPCName()) {
            FILELOG_INCOMING_CONNECTION("connectionError.log", "Wrong PCName: [%s] %s",
                                        pConnectionInfo->getPCName().c_str(),
                                        pGamePlayer->getSocket()->getHost().c_str());
            throw InvalidProtocolException("invalid pc name");
        }

        // ÀÏ´Ü ÀÌ¸§À» ÀúÀåÇÑ´Ù. ¾îÂ÷ÇÇ ´ÙÀ½¿¡ ½ÇÆÐÇÏ¸é °´Ã¼¸¦ »èÁ¦ÇÏ´Ï±î ¹«¹æÇÏ´Ù.
        pGamePlayer->setID(pConnectionInfo->getPlayerID());

        // CIMÀÇ heartbeat°¡ ½ÇÇàµÇ±â Àü¿¡ Àç¼öÁÁ°Ô Á¢¼ÓÇÒ °¡´É¼ºÀÌ ÀÖ´Ù.
        // (Å¸ÀÌ¹ÖÀÌ ÁÁÀ¸¸é heartbeat ½ÇÇàÁÖ±â*2 ¾È¿¡¸¸ Á¢¼ÓÇÏ¸é µÈ´Ù.)
        // µû¶ó¼­, ÇöÀç ½Ã°£°ú expire time À» ºñ±³ÇÑ´Ù.
        Timeval currentTime;
        getCurrentTime(currentTime);
        if (pConnectionInfo->getExpireTime() < currentTime) {
            FILELOG_INCOMING_CONNECTION("connectionError.log", "Expired: [%s] %s", pConnectionInfo->getPCName().c_str(),
                                        pGamePlayer->getSocket()->getHost().c_str());

            // ÀÏ´Ü »èÁ¦ÇÑ´Ù.
            g_pConnectionInfoManager->deleteConnectionInfo(pConnectionInfo->getClientIP());
            throw InvalidProtocolException("session already expired");
        }

        // by sigi. 2002.12.7
        FILELOG_INCOMING_CONNECTION("connectionInfo.log", "Login [%s:%s] %s (%u)",
                                    pConnectionInfo->getPlayerID().c_str(), pConnectionInfo->getPCName().c_str(),
                                    pConnectionInfo->getClientIP().c_str(), pConnectionInfo->getKey());

        // ÀÎÁõµÇ¾úÀ¸´Ï, ConnectionInfo ¸¦ »èÁ¦ÇÑ´Ù.
        try {
            g_pConnectionInfoManager->deleteConnectionInfo(pConnectionInfo->getClientIP());
        } catch (NoSuchElementException& nsee) {
            FILELOG_INCOMING_CONNECTION("connectionInfoDelete.log", "DeleteNoSuch [%s:%s] %s (%u)",
                                        pConnectionInfo->getPlayerID().c_str(), pConnectionInfo->getPCName().c_str(),
                                        pConnectionInfo->getClientIP().c_str(), pConnectionInfo->getKey());
        }
    } catch (NoSuchElementException& nsee) // ±×·± IP¸¦ °¡Áø CI °¡ ¾øÀ» °æ¿ì
    {
        FILELOG_INCOMING_CONNECTION("connectionError.log", "NoSuchConnectionInfo: %s",
                                    pGamePlayer->getSocket()->getHost().c_str());

        // Èì.. ¿¬°á ÀÌÈÄ CGConnect ÆÐÅ¶À» º¸³»´Â µô·¹ÀÌ°¡ ³Ê¹« ±æ °æ¿ì
        // session ÀÌ expire µÈ´Ù. ÀÌ·² °æ¿ì¿¡µµ Â¥¸£ÀÚ!
        // (¿¹¸¦ µé¾î¼­, ÃÖÃÊ ¿¬°á¿¡¼­´Â ¼º°øÇßÀ¸³ª ±×´ÙÀ½¿¡ µð¹ö±ë »óÅÂ·Î
        // µé¾î°¥ °æ¿ì, CGConnect ÆÐÅ¶À» º¸³¾ ¶§Âë¿¡´Â expire µÈ´Ù.)
        GCDisconnect gcDisconnect;
        gcDisconnect.setMessage(nsee.toString());

        pGamePlayer->sendPacket(&gcDisconnect);

        // ÀÌ·¸°Ô ´øÁö¸é »óÀ§ IPM::processCommands()¿¡¼­ disconnect Ã³¸®ÇÑ´Ù.
        throw InvalidProtocolException(nsee.toString().c_str());
    } catch (InvalidProtocolException& ipe) {
        FILELOG_INCOMING_CONNECTION("connectionError.log", "%s: %s", ipe.toString().c_str(),
                                    pGamePlayer->getSocket()->getHost().c_str());
        cout << endl
             << "+-----------------------+" << endl
             << "| Level 2 Access Denied |" << endl
             << "+-----------------------+" << endl
             << endl;

        GCDisconnect gcDisconnect;
        gcDisconnect.setMessage(ipe.toString());

        pGamePlayer->sendPacket(&gcDisconnect);

        // ÀÌ·¸°Ô ´øÁö¸é »óÀ§ IPM::processCommands()¿¡¼­ disconnect Ã³¸®ÇÑ´Ù.
        throw;
    }

    //----------------------------------------------------------------------
    // ·Î±×ÀÎ Ã¼Å©
    //----------------------------------------------------------------------
    Statement* pStmt = NULL;
    Result* pResult = NULL;

    // ºô¸µ~
    PayType payType;
    string payPlayDate;
    uint payPlayHours;
    uint payPlayFlag;
    int billingUserKey = 0; // by sigi. 2002.11.18
    string familyPayPlayDate;


    try {
        // È¡½ÇÉ«ÀàÐÍ£¬²»Ê¹ÓÃ¿Í»§¶ËÉÏÀ´µÄÀàÐÍ£¬·ÀÖ¹µôÏß
        // ³Â¹â»ÔÐÞ¸Ä2006 05 31
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pResult =
            pStmt->executeQuery("SELECT PlayerID,Race FROM Slayer WHERE Name = '%s'", pPacket->getPCName().c_str());


        if (pResult->getRowCount() != 1) {
            StringStream msg;
            msg << "Failed to load PlayerCreature data from DB. Not 1 PlayerID (" << pPacket->getPCName().c_str()
                << ")";

            filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

            SAFE_DELETE(pStmt);
            throw ProtocolException(msg.toString().c_str());
        }

        if (pResult->next()) {
            string spID = pResult->getString(1);
            string spRace = pResult->getString(2);

            if (spRace == "SLAYER") {
                pPacket->setPCType(PC_SLAYER);
            } else if (spRace == "VAMPIRE") {
                pPacket->setPCType(PC_VAMPIRE);
            } else if (spRace == "OUSTERS") {
                pPacket->setPCType(PC_OUSTERS);
            } else {
                StringStream msg;
                msg << "Failed to load PlayerCreature data from DB. No Character(" << spID.c_str()
                    << "!=" << pGamePlayer->getID().c_str() << ")";

                filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

                SAFE_DELETE(pStmt);
                throw ProtocolException(msg.toString().c_str());
            }


            if (strcasecmp(spID.c_str(), pGamePlayer->getID().c_str()) != 0) {
                StringStream msg;
                msg << "Failed to load PlayerCreature data from DB. No Character(" << spID.c_str()
                    << "!=" << pGamePlayer->getID().c_str() << ")";

                filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

                SAFE_DELETE(pStmt);
                throw ProtocolException(msg.toString().c_str());
            }
        }

        SAFE_DELETE(pStmt);

        // pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

#ifdef __THAILAND_SERVER__

        pResult = pStmt->executeQuery(
            "SELECT PlayerID, CurrentServerGroupID, LogOn, SpecialEventCount, PayType, PayPlayDate, PayPlayHours, "
            "PayPlayFlag, BillingUserKey, FamilyPayPlayDate, Birthday FROM Player WHERE PlayerID = '%s'",
            pGamePlayer->getID().c_str());

#else

        pResult = pStmt->executeQuery(
            "SELECT PlayerID, CurrentServerGroupID, LogOn, SpecialEventCount, PayType, PayPlayDate, PayPlayHours, "
            "PayPlayFlag, BillingUserKey, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s'",
            pGamePlayer->getID().c_str());

#endif
        if (pResult->getRowCount() != 1) {
            StringStream msg;
            msg << "Failed to load PlayerCreature data from DB. No Player(" << pPacket->getPCName().c_str() << ")";

            filelog("connectDB_BUG.txt", "%s", msg.toString().c_str());

            SAFE_DELETE(pStmt);
            throw ProtocolException(msg.toString().c_str());
        }

        pResult->next();

        int i = 0;

        string playerID = pResult->getString(++i);
        ServerGroupID_t GID = pResult->getInt(++i);
        string logon = pResult->getString(++i);
        uint scount = pResult->getDWORD(++i);

        payType = (PayType)pResult->getInt(++i);
        payPlayDate = pResult->getString(++i);
        payPlayHours = pResult->getInt(++i);
        payPlayFlag = pResult->getInt(++i);
        billingUserKey = pResult->getInt(++i);
        familyPayPlayDate = pResult->getString(++i);

#ifdef __THAILAND_SERVER__
        string Birthday = pResult->getString(++i);
        pGamePlayer->setPermission(isAdultByBirthdayDate(Birthday));
#endif

        pGamePlayer->setServerGroupID(GID);
        pGamePlayer->setSpecialEventCount(scount);
        pGamePlayer->setBillingUserKey(billingUserKey);

        if (logon != "LOGOFF") {
            SAFE_DELETE(pStmt);
            char str[80];
            sprintf(str, "Already connected player ID: %s, %s", playerID.c_str(), logon.c_str());
            throw ProtocolException(str);
        }

        pStmt->executeQuery("UPDATE Player SET LogOn='GAME' WHERE PlayerID = '%s' AND LogOn='LOGOFF'",
                            playerID.c_str());

        // LogOnÀÌ LOGOFF°¡ ¾Æ´Ï°Å³ª.. µîµî.. by sigi. 2002.5.15
        if (pStmt->getAffectedRowCount() == 0) {
            SAFE_DELETE(pStmt);
            char str[80];
            sprintf(str, "Already connected player ID2: %s, %s", playerID.c_str(), logon.c_str());
            throw ProtocolException(str);
        }

        string connectIP = pGamePlayer->getSocket()->getHost();

        // ºô¸µ by sigi. 2002.5.31
#if defined(__CONNECT_BILLING_SYSTEM__)
        if (payType == PAY_TYPE_FREE) {
            pGamePlayer->setMetroFreePlayer();
        }
#elif defined(__PAY_SYSTEM_LOGIN__)
        if (pGamePlayer->loginPayPlay(payType, payPlayDate, payPlayHours, payPlayFlag, connectIP, playerID)) {
            sendPayInfo(pGamePlayer);
        } else {
            SAFE_DELETE(pStmt);
            throw ProtocolException("no pay account");
        }
// by sigi. 2002.11.18. Á¦ÇÑÀû ¹«·á »ç¿ëÀÚ. - -; ÀÏ´Ü login
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)
        if (pGamePlayer->loginPayPlay(payType, payPlayDate, payPlayHours, payPlayFlag, connectIP, playerID)) {
            sendPayInfo(pGamePlayer);
        }
#else // defined(__PAY_SYSTEM_ZONE__)
        pGamePlayer->setPayPlayValue(payType, payPlayDate, payPlayHours, payPlayFlag, familyPayPlayDate);
#endif


        SAFE_DELETE(pStmt);
    } catch (SQLQueryException& sqe) {
        SAFE_DELETE(pStmt);
        throw Error(sqe.toString());
    }

    //----------------------------------------------------------------------
    // ½½·¹ÀÌ¾î ¶Ç´Â ¹ìÆÄÀÌ¾î Ä³¸¯ÅÍ¸¦ ·ÎµùÇÑ´Ù.
    //----------------------------------------------------------------------
    Slayer* pSlayer = NULL;
    Vampire* pVampire = NULL;
    Ousters* pOusters = NULL;

    bool bAlreadyConnected = false;

    // try
    //{
    if (pPacket->getPCType() == PC_SLAYER) {
        pSlayer = new Slayer();
        pSlayer->setName(pPacket->getPCName());
        pSlayer->setPlayer(pGamePlayer);

        if (!pSlayer->load()) {
            filelog("connectDB_BUG.txt", "Failed to load SLAYER(%s) data from DB", pPacket->getPCName().c_str());
            cout << " ¿©±â´Â µÇ³ª¿ä" << endl;
            throw ProtocolException("Failed to load SLAYER data from DB");
        }

        // À¯·áÁ¸¿¡¼­¸¸ Àû¿ëµÇ´Â ¾ÆÀÌÅÛ ¶§¹®¿¡ ¹Ø¿¡¼­ Ã¼Å©
        // pSlayer->loadItem();
        // Assert(pSlayer->getName() == pPacket->getPCName());
        if (pSlayer->getName() != pPacket->getPCName()) {
            cout << "Different Name : " << pSlayer->getName().c_str() << ", " << pPacket->getPCName().c_str() << endl;

            Assert(pSlayer->getName() == pPacket->getPCName());
        }

        pGamePlayer->setCreature(pSlayer);

        // Slayer¸¦ TelephoneCenter¿¡ µî·ÏÇÑ´Ù.
        // g_pTelephoneCenter->addSlayer(pSlayer);

        // ÁÖ±â È¸º¹ ÀÌº¥Æ®¸¦ ÇÃ·¹ÀÌ¾î °´Ã¼¿¡ Ãß°¡ÇÑ´Ù.
        // ÀÌ¶§ ±âº»ÀûÀ¸·Î 10ÃÊ È¸º¹À» ¿øÄ¢À¸·Î ÇÑ´Ù.
        // (setDeadlineÀÇ ÆÄ¶ó¹ÌÅÍ´Â 0.1 ÃÊ¶ó´Â µ¥ À¯ÀÇÇÒ °Í)
        EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
        pEventRegeneration->setDeadline(10 * 10);
        pGamePlayer->addEvent(pEventRegeneration);

        // PCFinder¿¡ Ãß°¡ÇÑ´Ù.
        // PCFinderÀÇ »èÁ¦´Â ~GamePlayer()¿¡¼­¸¸ ÇÑ´Ù.
        try {
            g_pPCFinder->addCreature(pSlayer);
        } catch (DuplicatedException& de) {
            bAlreadyConnected = true;
        }

        // ÀÌ¹Ì Á¢¼ÓÁßÀÎ °æ¿ì°¡ ¾Æ´Ï¶ó¸é.. by sigi. 2002.8.29
        if (!bAlreadyConnected) {
            // ±æµå ÇöÀç Á¢¼Ó ¸â¹ö ¸®½ºÆ®¿¡ Ãß°¡ÇÑ´Ù.
            if (pSlayer->getGuildID() != 99) {
                Guild* pGuild = g_pGuildManager->getGuild(pSlayer->getGuildID());
                if (pGuild != NULL) {
                    // sharedserver·Î Á¢¼ÓÀ» ¾Ë¸®°í DB µµ update ÇÑ´Ù.
                    try {
                        pGuild->addCurrentMember(pSlayer->getName());

                        GSGuildMemberLogOn gsGuildMemberLogOn;
                        gsGuildMemberLogOn.setGuildID(pGuild->getID());
                        gsGuildMemberLogOn.setName(pSlayer->getName());
                        gsGuildMemberLogOn.setLogOn(true);
                        gsGuildMemberLogOn.setServerID(g_pConfig->getPropertyInt("ServerID"));

                        g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

                        // DB ¾÷µ¥ÀÌÆ®
                        BEGIN_DB {
                            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
                            pStmt->executeQuery("UPDATE GuildMember SET LogOn = 1 WHERE Name = '%s'",
                                                pSlayer->getName().c_str());
                        }
                        END_DB(pStmt)

                    } catch (DuplicatedException& t) {
                        // ÀÏ´Ü ¹«½ÃÇÑ´Ù. by sigi. 2002.8.29
                        filelog("guildBug.log", "%s", t.toString().c_str());
                    }
                } else
                    filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(),
                            pSlayer->getName().c_str());
            }
        }
    } else if (pPacket->getPCType() == PC_VAMPIRE) {
        pVampire = new Vampire();
        pVampire->setName(pPacket->getPCName());
        pVampire->setPlayer(pGamePlayer);

        if (!pVampire->load()) {
            filelog("connectDB_BUG.txt", "Failed to load VAMPIRE(%s) data from DB", pPacket->getPCName().c_str());
            throw ProtocolException("Failed to VAMPIRE data from DB");
        }

        // À¯·áÁ¸¿¡¼­¸¸ Àû¿ëµÇ´Â ¾ÆÀÌÅÛ ¶§¹®¿¡ ¹Ø¿¡¼­ Ã¼Å©
        // pVampire->loadItem();
        Assert(pVampire->getName() == pPacket->getPCName());

        pGamePlayer->setCreature(pVampire);

        // ÁÖ±â È¸º¹ ÀÌº¥Æ®¸¦ ÇÃ·¹ÀÌ¾î °´Ã¼¿¡ Ãß°¡ÇÑ´Ù.
        // ÀÌ¶§ ±âº»ÀûÀ¸·Î 10ÃÊ È¸º¹À» ¿øÄ¢À¸·Î ÇÑ´Ù.
        // (setDeadlineÀÇ ÆÄ¶ó¹ÌÅÍ´Â 0.1 ÃÊ¶ó´Â µ¥ À¯ÀÇÇÒ °Í)
        EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
        pEventRegeneration->setDeadline(10 * 10);
        pGamePlayer->addEvent(pEventRegeneration);

        // PCFinder¿¡ Ãß°¡ÇÑ´Ù.
        // PCFinderÀÇ »èÁ¦´Â ~GamePlayer()¿¡¼­¸¸ ÇÑ´Ù.
        try {
            g_pPCFinder->addCreature(pVampire);
        } catch (DuplicatedException& de) {
            bAlreadyConnected = true;
        }

        // ÀÌ¹Ì Á¢¼ÓÁßÀÎ °æ¿ì°¡ ¾Æ´Ï¶ó¸é.. by sigi. 2002.8.29
        if (!bAlreadyConnected) {
            // ±æµå ÇöÀç Á¢¼Ó ¸â¹ö ¸®½ºÆ®¿¡ Ãß°¡ÇÑ´Ù.
            if (pVampire->getGuildID() != 0) {
                Guild* pGuild = g_pGuildManager->getGuild(pVampire->getGuildID());
                if (pGuild != NULL) {
                    // sharedserver ¿¡ Á¢¼ÓÀ» ¾Ë¸®°í DB µµ update ÇÑ´Ù.
                    try {
                        pGuild->addCurrentMember(pVampire->getName());

                        GSGuildMemberLogOn gsGuildMemberLogOn;
                        gsGuildMemberLogOn.setGuildID(pGuild->getID());
                        gsGuildMemberLogOn.setName(pVampire->getName());
                        gsGuildMemberLogOn.setLogOn(true);
                        gsGuildMemberLogOn.setServerID(g_pConfig->getPropertyInt("ServerID"));

                        g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

                        // DB ¾÷µ¥ÀÌÆ®
                        BEGIN_DB {
                            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
                            pStmt->executeQuery("UPDATE GuildMember SET LogOn = 1 WHERE Name = '%s'",
                                                pVampire->getName().c_str());
                        }
                        END_DB(pStmt)
                    } catch (DuplicatedException& t) {
                        // ÀÏ´Ü ¹«½ÃÇÑ´Ù. by sigi. 2002.8.29
                        filelog("guildBug.log", "%s", t.toString().c_str());
                    }
                } else
                    filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(),
                            pVampire->getName().c_str());
            }
        }
    } else if (pPacket->getPCType() == PC_OUSTERS) {
        pOusters = new Ousters();
        pOusters->setName(pPacket->getPCName());
        pOusters->setPlayer(pGamePlayer);

        if (!pOusters->load()) {
            filelog("connectDB_BUG.txt", "Failed to load VAMPIRE(%s) data from DB", pPacket->getPCName().c_str());
            throw ProtocolException("Failed to VAMPIRE data from DB");
        }

        // À¯·áÁ¸¿¡¼­¸¸ Àû¿ëµÇ´Â ¾ÆÀÌÅÛ ¶§¹®¿¡ ¹Ø¿¡¼­ Ã¼Å©
        // pVampire->loadItem();
        Assert(pOusters->getName() == pPacket->getPCName());
        // filelog("Ousters.txt","CGConectHandler.cpp 0,HP:%d,MAXHP:%d,MP:%d,MAXMP:%d",  (int)pOusters->getHP(
        // ATTR_CURRENT), (int)pOusters->getHP(ATTR_MAX),(int)pOusters->getMP(ATTR_CURRENT),
        // (int)pOusters->getMP(ATTR_MAX));

        pGamePlayer->setCreature(pOusters);

        // ÁÖ±â È¸º¹ ÀÌº¥Æ®¸¦ ÇÃ·¹ÀÌ¾î °´Ã¼¿¡ Ãß°¡ÇÑ´Ù.
        // ÀÌ¶§ ±âº»ÀûÀ¸·Î 10ÃÊ È¸º¹À» ¿øÄ¢À¸·Î ÇÑ´Ù.
        // (setDeadlineÀÇ ÆÄ¶ó¹ÌÅÍ´Â 0.1 ÃÊ¶ó´Â µ¥ À¯ÀÇÇÒ °Í)
        EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);
        pEventRegeneration->setDeadline(10 * 10);
        pGamePlayer->addEvent(pEventRegeneration);

        // PCFinder¿¡ Ãß°¡ÇÑ´Ù.
        // PCFinderÀÇ »èÁ¦´Â ~GamePlayer()¿¡¼­¸¸ ÇÑ´Ù.
        try {
            g_pPCFinder->addCreature(pOusters);
        } catch (DuplicatedException& de) {
            bAlreadyConnected = true;
        }

        // ÀÌ¹Ì Á¢¼ÓÁßÀÎ °æ¿ì°¡ ¾Æ´Ï¶ó¸é.. by sigi. 2002.8.29
        if (!bAlreadyConnected) {
            // ±æµå ÇöÀç Á¢¼Ó ¸â¹ö ¸®½ºÆ®¿¡ Ãß°¡ÇÑ´Ù.
            if (pOusters->getGuildID() != 66) {
                Guild* pGuild = g_pGuildManager->getGuild(pOusters->getGuildID());
                if (pGuild != NULL) {
                    // sharedserver ¿¡ Á¢¼ÓÀ» ¾Ë¸®°í DB µµ update ÇÑ´Ù.
                    try {
                        pGuild->addCurrentMember(pOusters->getName());

                        GSGuildMemberLogOn gsGuildMemberLogOn;
                        gsGuildMemberLogOn.setGuildID(pGuild->getID());
                        gsGuildMemberLogOn.setName(pOusters->getName());
                        gsGuildMemberLogOn.setLogOn(true);
                        gsGuildMemberLogOn.setServerID(g_pConfig->getPropertyInt("ServerID"));

                        g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);

                        // DB ¾÷µ¥ÀÌÆ®
                        BEGIN_DB {
                            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
                            pStmt->executeQuery("UPDATE GuildMember SET LogOn = 1 WHERE Name = '%s'",
                                                pOusters->getName().c_str());
                        }
                        END_DB(pStmt)
                    } catch (DuplicatedException& t) {
                        // ÀÏ´Ü ¹«½ÃÇÑ´Ù. by sigi. 2002.8.29
                        filelog("guildBug.log", "%s", t.toString().c_str());
                    }
                } else
                    filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pOusters->getGuildID(),
                            pOusters->getName().c_str());
            }
        }
    }
    //}

    cout << " ¿©±â´Â µÇ³ª¿ä2" << endl;

    // ÀÌ??Á¢¼Ó ÁßÀÎ °æ¿ìÀÇ Ã³¸®.
    // PCFinder¿¡¼­ÀÇ DuplicatedExceptionÀ» ¸íÈ®ÇÏ°Ô Ã³¸®ÇÏ±â À§ÇØ¼­
    // º¯¼ö¸¦ µÖ¼­ Ã¼Å©ÇÑ´Ù.
    // ¾Æ¸¶ ±æµåÀÇ DuplicatedException¶§¹®¿¡
    // PCFinder¿¡¼­ ¹®Á¦°¡ »ý±ä°Í °°´Ù.
    // by sigi. 2002.8.29
    if (bAlreadyConnected) {
        SAFE_DELETE(pSlayer);
        SAFE_DELETE(pVampire);
        SAFE_DELETE(pOusters);

        pGamePlayer->setID(string("")); // LogOnÀº 'LOGOFF'°¡ µÇ´Â°É ¸·´Â´Ù.
        pGamePlayer->setCreature(NULL); // PCFinder¿¡¼­ deleteÇÏ´Â°É ¸·´Â´Ù.

        char str[80];
        sprintf(str, "Already connected player ID3(Dup): %s", pPacket->getPCName().c_str());
        throw ProtocolException(str);
    }

    //----------------------------------------------------------------------
    // PC¸¦ PCFinder¿Í Á¸¿¡ µî·ÏÇÑ´Ù.
    //----------------------------------------------------------------------
    Creature* pCreature = pGamePlayer->getCreature();
    Assert(pCreature != NULL);

    EventHeadCount* pEventHeadCount = new EventHeadCount(pGamePlayer);
    pEventHeadCount->setDeadline(18000);
    pGamePlayer->addEvent(pEventHeadCount);
    cout << " ¿©±â´Â µÇ³ª¿ä3" << endl;
    if (pCreature->isGOD()) {
        EffectGhost* pEffect = new EffectGhost(pCreature);
        pCreature->getEffectManager()->addEffect(pEffect);
        pCreature->setFlag(Effect::EFFECT_CLASS_GHOST);
        pCreature->setMoveMode(Creature::MOVE_MODE_FLYING);
    } else {
#ifdef __TEST_SERVER__
        EventAuth* pAuth = new EventAuth(pGamePlayer);
        pGamePlayer->addEvent(pAuth);
        cout << "¿£ÇÁ·ÎÅØÆ® ÀÎÁõ Å¸ÀÌ¸Ó ºÙÀÔ´Ï´Ù : " << pGamePlayer->getID() << endl;
#endif
    }

    if (pCreature->getCompetenceShape() == 0) {
        EffectGnomesWhisper* pEffect = new EffectGnomesWhisper(pCreature);
        pEffect->setLevel(30);

        pCreature->addEffect(pEffect);
        pCreature->setFlag(pEffect->getEffectClass());
    }
    cout << " ¿©±â´Â µÇ³ª¿ä4" << endl;
    // ¼ºÀÌ³ª ¼º ´øÀü ¾ÈÀ¸·Î ·Î±×ÀÎÇÒ ¼ö ¾ø´Ù.
    ZoneID_t castleZoneID;
    ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pCreature->getZoneID());

    bool isCastleZone = g_pCastleInfoManager->getCastleZoneID(pCreature->getZoneID(), castleZoneID);
    bool isMasterLair = pZoneInfo->isMasterLair() || GDRLairManager::Instance().isGDRLairZone(pCreature->getZoneID());
    bool isPKZone = g_pPKZoneInfoManager->isPKZone(pCreature->getZoneID());
    bool isMaze = (pCreature->getZoneID() == 3001) || (pCreature->getZoneID() == 3002) ||
                  (pCreature->getZoneID() == 3003) || (pCreature->getZoneID() == 1013); // add by sonic 2006.10.30
    bool isEventZone = EventZoneInfoManager::Instance().getEventZoneInfo(pCreature->getZoneID()) != NULL;
    bool isBeginnerZone = pCreature->getZoneID() == 1122 && !canEnterBeginnerZone(pCreature);
    bool isDynamicZone = g_pDynamicZoneManager->isDynamicZone(pCreature->getZoneID());

    if (pCreature->isPC()) //&& pCreature->isPLAYER() )
    {
        ZONE_COORD zoneCoord;
        PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
        Assert(pPC != NULL);

        if (isCastleZone || isMasterLair || isPKZone || isMaze || isEventZone || isBeginnerZone || isDynamicZone) {
            if (g_pResurrectLocationManager->getPosition(pPC, zoneCoord)) {
                pCreature->setZoneID(zoneCoord.id);
                pCreature->setXY(zoneCoord.x, zoneCoord.y);
            }
        }
    }
    cout << " ¿©±â´Â µÇ³ª¿ä5" << endl;
    Zone* pZone = pCreature->getZone();
    Assert(pZone != NULL);

#if defined(__PAY_SYSTEM_FREE_LIMIT__)
    try {
        ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());
        Assert(pZoneInfo != NULL);

        Assert(pCreature->isPC());
        PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
        Assert(pPC != NULL);

        // À¯·á Á¸ÀÌ³ª ÇÁ¸®¹Ì¾ö Á¸ÀÌ ¾Æ´Ò °æ¿ì 30 ·¹º§ ÀÌÇÏÀÇ Á¾·®Á¦ »ç¿ëÀÚ¿¡°Ô´Â °ú±ÝÇÏÁö ¾Ê´Â´Ù.
        if ((pGamePlayer->isPayPlaying() || pGamePlayer->isPremiumPlay()) &&
            pGamePlayer->getPayType() == PAY_TYPE_TIME && pPC->canPlayFree() &&
            !(pZoneInfo->isPayPlay() || pZone->isPremiumZone())) {
            pGamePlayer->logoutPayPlay(pGamePlayer->getID(), false, false);
        }

        // À¯·áÈ­ Á¸ÀÌ°í À¯·á»ç¿ëÁßÀÌ ¾Æ´Ï¸é..
        // ¤Ì.¤Ð 2003.03.16 ÀÏ¹Ý ÇÊµåµµ ÇÁ¸®¹Ì¾öÁ¸ÀÌ´Ù. ¹«·á»ç¿ëÀÚµµ ÇÊµå·Î´Â ·Î±×ÀÎ µÇ¾î¾ß ÇÑ´Ù.
        if ((pZoneInfo->isPayPlay()) //|| pZoneInfo->isPremiumZone())
            && !pGamePlayer->isPayPlaying()) {
            // À¯·á ¼­ºñ½º »ç¿ë ºÒ°¡ÀÎ °æ¿ì
            // ½½·¹ÀÌ¾î´Â ¿¡½½³²µ¿¿¡¼­ ºÎÈ°ÇÏ´Â °÷À¸·Î °£´Ù.
            // ¹ìÆÄÀÌ¾î´Â ¸²º¸³²µ¿¿¡¼­ ºÎÈ°ÇÏ´Â °÷À¸·Î °£´Ù.
            ZONE_COORD zoneCoord;

            if (g_pResurrectLocationManager->getRaceDefaultPosition(pPC->getRace(), zoneCoord)) {
                pCreature->setZoneID(zoneCoord.id);
                pCreature->setXY(zoneCoord.x, zoneCoord.y);
            }
        }
    } catch (NoSuchElementException&) {
        throw Error("ZoneInfo¿¡ zoneID°¡ ¾ø´Ù.");
    }
#elif defined(__CONNECT_BILLING_SYSTEM__)
    if (pGamePlayer->isMetroFreePlayer()) {
        pGamePlayer->setBillingUserStatus("MT");
        pGamePlayer->setPremiumPlay();
    } else {
        try {
            ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());
            Assert(pZoneInfo != NULL);

            Assert(pCreature->isPC());
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
            Assert(pPC != NULL);

            // ¾ÆÁ÷ ºô¸µ ¼­¹ö¿¡¼­ À¯·á »ç¿ëÀÚÀÎÁö ÀÎÁõ È®ÀÎÀ» ¹ÞÁö ¾Ê¾Ò´Ù.
            // À¯·áÈ­ Á¸ÀÌ¶ó¸é ÀÏ´Ü À¯·á »ç¿ëÀÚ¶ó·Î »ý°¢ÇÑ´Ù.
            // premium À» ÄÑ ³õ¾Æ¾ßÁö ¹«·á »ç¿ëÀÏ¶§ ZonePlayerManager ¿¡¼­ ¹«·áÁ¸À¸·Î ¿Å°ÜÁØ´Ù.
            if (pZoneInfo->isPayPlay()) {
                pGamePlayer->setPremiumPlay();
            }

        } catch (NoSuchElementException&) {
            throw Error("ZoneInfo¿¡ zoneID°¡ ¾ø´Ù.");
        }

        // session °ªÀ» Á¤ÇØµÐ´Ù. by sigi. 2002.11.18
        pGamePlayer->setBillingSession();

        // ºô¸µ¼­¹ö¿¡ °ÔÀÓ ½ÃÀÛÀ» ¾Ë¸°´Ù.
        pGamePlayer->sendBillingLogin();
    }

#elif defined(__PAY_SYSTEM_ZONE__)
    try {
        ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(pZone->getZoneID());

        // À¯·áÈ­ Á¸ÀÌ°í À¯·á»ç¿ëÁßÀÌ ¾Æ´Ï¸é..
        if (pZoneInfo != NULL && (pZoneInfo->isPayPlay() || pZoneInfo->isPremiumZone()) &&
            !pGamePlayer->isPayPlaying()) {
            bool bEnterZone = true;

            string connectIP = pGamePlayer->getSocket()->getHost();

            // À¯·á ¼­ºñ½º »ç¿ëÀÌ °¡´ÉÇÑ°¡?
            // À¯·á ¼­ºñ½º »ç¿ëÀÌ ¾ÈµÇ°í À¯·á Á¸ÀÌ¶ó¸é µé¾î°¥ ¼ö ¾ø´Ù.
            if (!pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()) && pZoneInfo->isPayPlay()) {
                bEnterZone = false;
            }

            if (!pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()) &&
                (pZone->getZoneID() == 1131 || pZone->getZoneID() == 1132 || pZone->getZoneID() == 1133 ||
                 pZone->getZoneID() == 1134)) {
                bEnterZone = false;
            }

            Assert(pCreature->isPC());
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
            Assert(pPC != NULL);

            if (!bEnterZone) {
                // À¯·á ¼­ºñ½º »ç¿ë ºÒ°¡ÀÎ °æ¿ì
                // ½½·¹ÀÌ¾î´Â ¿¡½½³²µ¿¿¡¼­ ºÎÈ°ÇÏ´Â °÷À¸·Î °£´Ù.
                // ¹ìÆÄÀÌ¾î´Â ¸²º¸³²µ¿¿¡¼­ ºÎÈ°ÇÏ´Â °÷À¸·Î °£´Ù.
                ZONE_COORD zoneCoord;
                //				bool bFindPos = false;

                if (g_pResurrectLocationManager->getRaceDefaultPosition(pPC->getRace(), zoneCoord)) {
                    pCreature->setZoneID(zoneCoord.id);
                    pCreature->setXY(zoneCoord.x, zoneCoord.y);
                }
            }
        }
    } catch (NoSuchElementException&) {
        throw Error("ZoneInfo¿¡ zoneID°¡ ¾ø´Ù.");
    }
#elif defined(__CONNECT_CBILLING_SYSTEM__)
    // ºô¸µ ¼­¹ö·Î ÁÖ±âÀûÀ¸·Î minus point/minute ÆÐÅ¶À» º¸³»´Â ÀÌº¥Æ®¸¦ ºÙÀÎ´Ù.
    EventCBilling* pEvent = new EventCBilling(pGamePlayer);
    pEvent->setDeadline(g_pCBillingPlayerManager->getMinusIntervalInt() * 600);
    pGamePlayer->addEvent(pEvent);

    // Áß±¹ ºô¸µÀº Àü¸é À¯·áÈ­ ÀÌ¹Ç·Î ¿©±â±îÁö ¿Ô´Ù¸é À¯·á »ç¿ëÀÚÀÌ´Ù. ¹«·á »ç¿ëÀÚÀÏ °æ¿ì ·Î±×ÀÎ ¼­¹ö¿¡¼­ ¸·Èù´Ù.
    pGamePlayer->setPayPlayer(true);
    pGamePlayer->setPremiumPlay();

    // send Login
    pGamePlayer->setCBillingVerified(g_pCBillingPlayerManager->sendLogin(pGamePlayer));
#else
    // ¾Æ¹«°Íµµ ¼³Á¤µÇ¾î ÀÖÁö ¾ÊÀ¸¸é
    // °Á À¯·á »ç¿ëÀÚ¶ó°í ÇØ¹ö¸®ÀÚ
    pGamePlayer->setPremiumPlay();
#endif

    // test code
    /*
    // ·Î±×ÀÎ ÇÏ°í.. ¹Ù·Î ¹º°¡ ¸Þ¼¼Áö¸¦ »Ñ·ÁÁÖ´Â ºÎºÐ. by sigi. 2002.12.11
    EventSystemMessage* pESM = new EventSystemMessage( pGamePlayer );
    pESM->setDeadline( 0 );
    pESM->addMessage("ÀÌ°ÍÀº Å×½ºÆ® ½Ã½ºÅÛ ¸Þ½ÃÁö");
    pESM->addMessage("Á¦´ë·Î Ãâ·ÂµÇ±æ ¹Ù¶ö»Ó.. -_-;;");
    pGamePlayer->addEvent( pESM );
    */

    // À¯·áÁ¸¿¡¼­¸¸ Àû¿ëµÇ´Â ¾ÆÀÌÅÛ ¶§¹®¿¡ ¿©±â¼­ Ã¼Å©
    // 2002.8.26. by sigi
    cout << " ¾ÆÀÌÅÛ ·Îµå ºÎºÐ ÀÌ ºÎºÐÀÌ ¾ÈµÇ¸é ÀÌºÎºÐÀÌ ¿À·ù´Ù." << endl;
    if (pPacket->getPCType() == PC_SLAYER) {
        Assert(pSlayer != NULL);
        pSlayer->loadItem(true);
    } else if (pPacket->getPCType() == PC_VAMPIRE) {
        Assert(pVampire != NULL);
        pVampire->loadItem(true);
    } else if (pPacket->getPCType() == PC_OUSTERS) {
        Assert(pOusters != NULL);
        pOusters->loadItem(true);
    }


    // ½½·¹ÀÌ¾î¶ó¸é ±æµå ³»ºÎ, ¹ìÆÄÀÌ¾î¶ó¸é ·¹¾î ³»ºÎ¿¡¼­
    // ½ÃÀÛÇÏ´Â °æ¿ì, HP¸¦ ¸¸¶¥À¸·Î Ã¤¿öÁØ´Ù.
    if (pCreature->isSlayer()) {
        Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

        switch (pZone->getZoneID()) {
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
    } else if (pCreature->isVampire()) {
        Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

        switch (pZone->getZoneID()) {
        case 1003:
        case 1007:
            pVampire->setHP(pVampire->getHP(ATTR_MAX), ATTR_CURRENT);
            break;
        default:
            break;
        }
    } else if (pCreature->isOusters()) {
        Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

        switch (pZone->getZoneID()) {
        case 1311:
            // filelog("Ousters.txt","CGConectHandler.cpp 1,HP:%d,MAXHP:%d,MP:%d,MAXMP:%d",  (int)pOusters->getHP(
            // ATTR_CURRENT), (int)pOusters->getHP(ATTR_MAX),(int)pOusters->getMP(ATTR_CURRENT),
            // (int)pOusters->getMP(ATTR_MAX));
            pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
            // chengh add 2005 10 02
            pOusters->setMP(pOusters->getMP(ATTR_MAX), ATTR_CURRENT);
            // filelog("Ousters.txt","CGConectHandler.cpp 2,HP:%d,MAXHP:%d,MP:%d,MAXMP:%d",  (int)pOusters->getHP(
            // ATTR_CURRENT), (int)pOusters->getHP(ATTR_MAX),(int)pOusters->getMP(ATTR_CURRENT),
            // (int)pOusters->getMP(ATTR_MAX));

        default:
            break;
        }
    }

    // Äù½ºÆ® ¸Å´ÏÀú¸¦ ·ÎµåÇÑ´Ù.
    PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
    pPC->getQuestManager()->load();

    // Å©¸®Ã³ ÀÚ½Å°ú ¼ÒÀ¯ ¾ÆÀÌÅÛµéÀÇ OID¸¦ ÇÒ´ç¹Þ´Â´Ù.
    // ÀÌ¹Ì Creature::load()¿¡¼­ Zone ÀÌ ÁöÁ¤µÇ¾î ÀÖ¾î¾ß ÇÑ´Ù.
    pCreature->registerObject();

    // ÁÖ±â ÀúÀå ÀÌº¥Æ®¸¦ ÇÃ·¹ÀÌ¾î °´Ã¼¿¡ Ãß°¡ÇÑ´Ù.
    // ÀÌ¶§ ±âº»ÀûÀ¸·Î 10ºÐ ÀúÀåÀ» ¿øÄ¢À¸·Î ÇÑ´Ù.
    // (setDeadlineÀÇ ÆÄ¶ó¹ÌÅÍ´Â 0.1 ÃÊ¶ó´Â µ¥ À¯ÀÇÇÒ °Í)
    // EventSave* pEventSave = new EventSave(pGamePlayer);
    // pEventSave->setDeadline(600* 10);
    // pGamePlayer->addEvent(pEventSave);

#ifdef __USE_ENCRYPTER__
    // ¾ÏÈ£È­ ÄÚµå µî·Ï. Áö±ÝÀº objectID·Î ÇÏ±â ¶§¹®¿¡.. by sigi. 2002.11.27
    pGamePlayer->setEncryptCode();
#endif

    //	pGamePlayer->sendPacket( SystemAvailabilitiesManager::getInstance()->getAvailabilitiesPacket() );
    SEND_SYSTEM_AVAILABILITIES(pGamePlayer);

    //----------------------------------------------------------------------
    // GCUpdateInfo ¿ë PC Á¤º¸, SkillInfo ¸¦ ±¸¼ºÇÑ´Ù.
    //----------------------------------------------------------------------

    cout << " ¿©±â´Â µÇ³ª¿ä7" << endl;

    GCUpdateInfo gcUpdateInfo;

    makeGCUpdateInfo(&gcUpdateInfo, pCreature);

    pGamePlayer->sendPacket(&gcUpdateInfo);

    sendPetInfo(pGamePlayer);

    string host = pGamePlayer->getSocket()->getHost();

    IP_t IP = pGamePlayer->getSocket()->getHostIP();

    // ¸¶Áö¸·À¸·Î IPÀÇ Á¤º¸¸¦ DB¿¡ INSERT ÇÑ´Ù.

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
// YYYY-MM-DD ·Î ¼ºÀÎ ÆÇº°
//
//////////////////////////////////////////////////////////////////////////////
bool isAdultByBirthdayDate(const string& birthday) {
    StringStream AdultSSN;

    time_t daytime = time(0);
    tm Timec;
    localtime_r(&daytime, &Timec);

    AdultSSN << Timec.tm_year - 18;
    // tm_mon - range 0 to 11
    if ((Timec.tm_mon + 1) < 10)
        AdultSSN << "0";
    AdultSSN << (Timec.tm_mon + 1);
    if (Timec.tm_mday < 10)
        AdultSSN << "0";
    AdultSSN << Timec.tm_mday;

    cout << "Birthday = " << birthday.c_str() << " ADULTSSN = " << AdultSSN.toString().c_str() << endl;

    int year = atoi(birthday.substr(0, 4).c_str());
    int month = atoi(birthday.substr(5, 2).c_str());
    int day = atoi(birthday.substr(8, 2).c_str());

    if (Timec.tm_year - 18 + 1900 > year) {
        cout << "¾î¸¥" << endl;
        return true;
    } else if (Timec.tm_year - 18 + 1900 == year) {
        if (Timec.tm_mon + 1 > month) {
            cout << "¾î¸¥" << endl;
            return true;
        } else if (Timec.tm_mon + 1 == month) {
            if (Timec.tm_mday >= day) {
                cout << "¾î¸¥" << endl;
                return true;
            }
        }
    }

    cout << "¾Öµé" << endl;
    return false;
}

#endif
