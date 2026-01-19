//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectPCHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectPC.h"

#ifdef __LOGIN_SERVER__
#include "Assert1.h"
#include "DB.h"
#include "GameServerInfo.h"
#include "GameServerInfoManager.h"
#include "GameServerManager.h"
#include "LCReconnect.h"
#include "LCSelectPCError.h"
#include "LGIncomingConnection.h"
#include "LoginPlayer.h"
#include "Properties.h"
#include "ZoneGroupInfoManager.h"
#include "ZoneInfoManager.h"
#include "chinabilling/CBillingInfo.h"
#include "gameserver/billing/BillingInfo.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// CLSelectPCHandler::execute()
//
// �α��� ������ �� ��Ŷ�� ������, ������ Name + PCType �� ���� PC �� �ε��Ѵ�.�
// �� PC�� �÷��̾��� ĳ���Ͷ�� �� PC�� ������ �ִ� ���� �˾Ƴ���
// �� ���� ����� ���� �������� LGIncomingConnection �� �����Ѵ�.
// ���� Ŭ���̾�Ʈ���� LCReconnect ��Ŷ�� ������, ���� ������ �����ϵ���
// ���ش�.
//////////////////////////////////////////////////////////////////////////////
void CLSelectPCHandler::execute(CLSelectPC* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

        Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

    LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

    bool bCheckATTR = false;

    // �α��� �������� billing ���� �κ��� ����� �Ѵ�.
    // �ֵ�� ��û ����. by bezz 2003.04.22
/*#ifdef __CONNECT_BILLING_SYSTEM__

    // ���� �ý������κ��� üũ�� �޴� ���
    // by sigi. 2002.11.21
    if (pLoginPlayer->isBillingLoginVerified())
    {
        if (pLoginPlayer->isBillingPlayAvaiable()
            && pLoginPlayer->getBillingUserStatus()!="XX")
        {
            cout << "isBillingPlay: " << pLoginPlayer->getID().c_str() << endl;
        }
        else if (pLoginPlayer->isPayPlaying())
        {
            // �� ���~
            cout << "isPayPlaying: " << pLoginPlayer->getID().c_str() << endl;

            // �׷���.. �ؿ��� �ɷ�ġ üũ�� �ؾ��Ѵ�.
            if (pLoginPlayer->getPayType()!=PAY_TYPE_FREE)
            {
                bCheckATTR = true;
            }
        }
        else
        {
            cout <<  "CannotPlay: " << pLoginPlayer->getID().c_str() << endl;

            // ���� �� �� ���� ĳ����(���� ����)
            LCSelectPCError lcSelectPCError;
            lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY);
            pLoginPlayer->sendPacket(&lcSelectPCError);

            //throw DisconnectException("cannot playing");
            return;
        }
    }
    else
    {
        // ���� �����ý������κ��� ������ ���� ���� ����
        // Ŭ���̾�Ʈ���� �� ��ٸ����� �ؾ��Ѵ�.
        // �ƴϸ�, �ϴ� �׳� �Ѿ��.. �� �������� ©������ �ұ�?
        // ���� ���� ������ üũ���� �ʾҴ�.
        cout << "NotBillingChecked: " << pLoginPlayer->getID().c_str();

        if (pLoginPlayer->isPayPlaying()
            && pLoginPlayer->getPayType()==PAY_TYPE_FREE)
        {
            // ���� ���� ����ڴ� �׳� ����Ѵ�.
            cout << "But PAY_TYPE_FREE" << endl;
        }
        else
        {
            cout << endl;

            LCSelectPCError lcSelectPCError;
            lcSelectPCError.setCode(SELECT_PC_NOT_BILLING_CHECK);
            pLoginPlayer->sendPacket(&lcSelectPCError);

            //throw DisconnectException("cannot playing");
            return;
        }
    }
*/
#ifdef __NETMARBLE_SERVER__
    if (!pLoginPlayer->isAgree()) {
        LCSelectPCError lcSelectPCError;
        lcSelectPCError.setCode(SELECT_PC_DIDNOT_AGREE);
        pLoginPlayer->sendPacket(&lcSelectPCError);

        return;
    }
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
    if (pLoginPlayer->isCBillingVerified()) {
        if (!pLoginPlayer->isPayPlayer()) {
            LCSelectPCError lcSelectPCError;
            lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY);
            pLoginPlayer->sendPacket(&lcSelectPCError);

            return;
        }
    } else {
        LCSelectPCError lcSelectPCError;
        lcSelectPCError.setCode(SELECT_PC_NOT_BILLING_CHECK);
        pLoginPlayer->sendPacket(&lcSelectPCError);

        return;
    }

#endif

// �ֵ�� ������ ������� �ʾƵ�..
// �ɷ�ġ ���� üũ�� �ؾ��ϴ� ���
#ifdef __PAY_SYSTEM_FREE_LIMIT__
    // ���� ����ڰ� �ƴ� ���� ... �ɷ�ġ üũ�Ѵ�.
    if (!pLoginPlayer->isPayPlaying()) {
        bCheckATTR = true;
    }
#endif


    if (pLoginPlayer->getPlayerStatus() != LPS_PC_MANAGEMENT)
        throw DisconnectException("invalid player status");

    // PC �� ������ ����Ÿ���̽��κ��� ���� �´�.
    Statement* pStmt = NULL;
    Statement* pStmt1 = NULL; // (!)
    Result* pResult;
    WorldID_t WorldID = pLoginPlayer->getWorldID();

    try {
        pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement(); // (!)
        pStmt = g_pDatabaseManager->getConnection((int)WorldID)->createStatement();

        //----------------------------------------------------------------------
        // PC �� ���������� �÷����� ���� ���̵� �����´�.
        //----------------------------------------------------------------------

        // �����̾� Ȥ�� �����̾� ���̺����� ���� ������ ��Ƽ��
        // ĳ���͸� ã�´�.
        /*
        pResult = pStmt->executeQuery(
            "SELECT ZoneID, Slot FROM %s WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'",
            pPacket->getPCType() == PC_SLAYER ? "Slayer" : "Vampire" ,
            pPacket->getPCName().c_str() ,
            pLoginPlayer->getID().c_str()
        );
        */

        bool isSlayer = (pPacket->getPCType() == PC_SLAYER);
        bool isVampire = (pPacket->getPCType() == PC_VAMPIRE);

        if (isSlayer) {
            pResult = pStmt->executeQuery(
                "SELECT ZoneID, Slot, GREATEST(SwordLevel,BladeLevel,GunLevel,EnchantLevel,HealLevel), Competence FROM "
                "Slayer WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'",
                pPacket->getPCName().c_str(), pLoginPlayer->getID().c_str());
        } else if (isVampire) {
            pResult = pStmt->executeQuery("SELECT ZoneID, Slot, Level, Competence FROM Vampire WHERE Name = '%s' AND "
                                          "PlayerID = '%s' AND Active = 'ACTIVE'",
                                          pPacket->getPCName().c_str(), pLoginPlayer->getID().c_str());
        } else {
            pResult = pStmt->executeQuery("SELECT ZoneID, Slot, Level, Competence FROM Ousters WHERE Name = '%s' AND "
                                          "PlayerID = '%s' AND Active = 'ACTIVE'",
                                          pPacket->getPCName().c_str(), pLoginPlayer->getID().c_str());
        }

        // �׷� PC�� ���� ���
        if (pResult->getRowCount() != 1) {
            SAFE_DELETE(pStmt);
            throw InvalidProtocolException("no such PC exist.");
        }

        pResult->next();

        ZoneID_t zoneID = pResult->getWORD(1);
        string slotStr = pResult->getString(2);

        // �ɷ�ġ üũ. by sigi. 2002.11.22
        if (bCheckATTR) {
#ifdef __PAY_SYSTEM_FREE_LIMIT__
            if (isSlayer) {
                static int slayerSum = g_pConfig->getPropertyInt("FreePlaySlayerDomainSum");

                int DomainSUM = pResult->getInt(3);

                if (DomainSUM > slayerSum) {
                    LCSelectPCError lcSelectPCError;
                    lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY_BY_ATTR);
                    pLoginPlayer->sendPacket(&lcSelectPCError);
                    SAFE_DELETE(pStmt);
                    return;
                }
            } else {
                static int vampireLevel = g_pConfig->getPropertyInt("FreePlayVampireLevel");

                int Level = pResult->getInt(3);

                if (Level > vampireLevel) {
                    LCSelectPCError lcSelectPCError;
                    lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY_BY_ATTR);
                    pLoginPlayer->sendPacket(&lcSelectPCError);
                    SAFE_DELETE(pStmt);
                    return;
                }
            }
#endif
        }

        //////////////////////////////////////////////////////////////////////////////////////
        // PK Server üũ
        //////////////////////////////////////////////////////////////////////////////////////
        bool bNonPKServer =
            g_pGameServerInfoManager->getGameServerInfo(1, pLoginPlayer->getServerGroupID(), pLoginPlayer->getWorldID())
                ->isNonPKServer();
        if (bNonPKServer) {
            cout << "WorldID:" << (int)(pLoginPlayer->getWorldID())
                 << " ServerGroupID:" << (int)(pLoginPlayer->getServerGroupID()) << endl;

            int playerLevel = pResult->getInt(3);
            int competence = pResult->getInt(4);

            // 40 ���� ���� ���� �÷��̾�� �� �� ����.
            // ��ڴ� �����Ѵ�.
            if (playerLevel > 80 && competence == 3) {
                LCSelectPCError lcSelectPCError;
                lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY_BY_ATTR);
                pLoginPlayer->sendPacket(&lcSelectPCError);
                SAFE_DELETE(pStmt);
                return;
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////

        if (slotStr.size() != 5) {
            SAFE_DELETE(pStmt);
            throw InvalidProtocolException("no slot exist.");
        }

        int slot = slotStr.at(4) - '0';

        //----------------------------------------------------------------------
        // �� ���� �����ϴ� ���� ���� ������ �����´�.
        //----------------------------------------------------------------------
        GameServerInfo* pGameServerInfo;
        if (zoneID > 10000 && zoneID < 30000) {
            // ĳ���Ͱ� ��� ����Ʈ�� �ִ�. ��� ����Ʈ ���� ������ login server�� �����Ƿ� ���� �����Ѵ�.
            pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(1, pLoginPlayer->getServerGroupID(), WorldID);
        } else {
            ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(zoneID);
            ZoneGroupInfo* pZoneGroupInfo = g_pZoneGroupInfoManager->getZoneGroupInfo(pZoneInfo->getZoneGroupID());
            // cout << "ConnctServerGroup: " << (int)pLoginPlayer->getServerGroupID() << ", ServerID: " <<
            // (int)pZoneGroupInfo->getServerID();
            cout << "WorldID " << (int)WorldID << ", ServerGroupID : " << (int)pLoginPlayer->getServerGroupID()
                 << ", ServerID : " << (int)pZoneGroupInfo->getServerID() << endl;
            pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(pZoneGroupInfo->getServerID(),
                                                                          pLoginPlayer->getServerGroupID(), WorldID);
        }

        //----------------------------------------------------------------------
        // �� ������� ���� ���� ���� ������ �����´�.
        //----------------------------------------------------------------------
        //		GameServerInfo* pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(pPlayer->getServerID());


        //----------------------------------------------------------------------
        // ���Ӽ������� incoming connection �� �� �Ŷ�� �˷��ش�.
        //----------------------------------------------------------------------
        LGIncomingConnection lgIncomingConnection;
        lgIncomingConnection.setClientIP(pLoginPlayer->getSocket()->getHost());
        lgIncomingConnection.setPlayerID(pLoginPlayer->getID());
        lgIncomingConnection.setPCName(pPacket->getPCName());

        //--------------------------------------------------------------------------------
        //
        // *CAUTION*
        //
        // LoginPlayer::setPlayerStatus()�� GameServerManager::sendPacket()�� ������ �����϶�.
        // �ܼ��ϰ� �����ϸ� sendPacket()�Ŀ� setPlayerStatus()�� ȣ���ϴ� ���� ������ �մ�
        // ������, ������ �׷��� �ϸ� setPlayerStatus()�� ȣ���ϱ�
        // ���� ���� �����κ��� GLIncomingConnectionXXX ��Ŷ�� ���ƿͼ� �� �ڵ鷯�� ����ȴ�. - -; ����, �Ʒ��� ���� ���¸� ����
        // ������ �Ŀ� UDP ��Ŷ�� �����ؾ� �Ѵ�.
        //
        //--------------------------------------------------------------------------------
        pLoginPlayer->setPlayerStatus(LPS_AFTER_SENDING_LG_INCOMING_CONNECTION);

        // by tiancaiamao: when gameserver is behind docker, it may have a docker internal IP 172.20.0.1 and a outside
        // IP in database GameServerInfo table. The outside IP should be used.
        pLoginPlayer->setGameServerIP(pGameServerInfo->getIP());

        /*
                // ��¿ �� ���� user name �� ����ؼ� �ϵ��ڵ��Ѵ�. -_-;
                g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , pGameServerInfo->getUDPPort() ,
           &lgIncomingConnection);
        */

        if (g_pConfig->getProperty("User") == "excel96")
            // g_pGameServerManager->sendPacket(pGameServerInfo->getIP() ,
            // g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
            g_pGameServerManager->sendPacket(pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(),
                                             &lgIncomingConnection);
        else if (g_pConfig->getProperty("User") == "beowulf")
            g_pGameServerManager->sendPacket(pGameServerInfo->getIP(), g_pConfig->getPropertyInt("GameServerUDPPort"),
                                             &lgIncomingConnection);
        //			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 8886 , &lgIncomingConnection);
        else if (g_pConfig->getProperty("User") == "crazydog")
            g_pGameServerManager->sendPacket(pGameServerInfo->getIP(), g_pConfig->getPropertyInt("GameServerUDPPort"),
                                             &lgIncomingConnection);
        //			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 6665, &lgIncomingConnection);
        else if (g_pConfig->getProperty("User") == "elcastle") {
            cout << "gameserver ip: " << pGameServerInfo->getIP()
                 << ", port: " << g_pConfig->getPropertyInt("GameServerUDPPort") << endl;
            g_pGameServerManager->sendPacket(pGameServerInfo->getIP(), g_pConfig->getPropertyInt("GameServerUDPPort"),
                                             &lgIncomingConnection);
            //			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 8885 , &lgIncomingConnection);
        } else if (g_pConfig->getProperty("User") == "elca")
            g_pGameServerManager->sendPacket(pGameServerInfo->getIP(), g_pConfig->getPropertyInt("GameServerUDPPort"),
                                             &lgIncomingConnection);
        //			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 3335 , &lgIncomingConnection);

        // ���������� ������ slot ���. by sigi. 2002.5.6
        pStmt1->executeQuery( // (!)
                              // pStmt->executeQuery(
            "UPDATE Player Set CurrentWorldID = %d, CurrentServerGroupID = %d, LastSlot = %d WHERE PlayerID = '%s'",
            WorldID, pLoginPlayer->getServerGroupID(), slot, pLoginPlayer->getID().c_str());

        pStmt->executeQuery("UPDATE Slayer Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(),
                            pPacket->getPCName().c_str());
        pStmt->executeQuery("UPDATE Vampire Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(),
                            pPacket->getPCName().c_str());
        pStmt->executeQuery("UPDATE Ousters Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(),
                            pPacket->getPCName().c_str());

        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt1); //(!)

        // cout << "CLSelectPC SendPacket to Server IP : " << pGameServerInfo->getIP() << endl;
    } catch (SQLQueryException& sqe) {
        // cout << sqe.toString() << endl;

        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt1); //(!)

        throw DisconnectException(sqe.toString());
    } catch (NoSuchElementException& nsee) {
        StringStream msg;

        msg << "Critical Error : data intergrity broken at ZoneInfo - ZoneGroupInfo - GameServerInfo : "
            << nsee.toString();

        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt1); //(!)

        throw Error(msg.toString());
    }

#endif

    __END_DEBUG_EX __END_CATCH
}
