//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectPCHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectPC.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "ZoneInfoManager.h"
	#include "ZoneGroupInfoManager.h"
	#include "GameServerInfo.h"
	#include "GameServerInfoManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "Assert1.h"
	#include "gameserver/billing/BillingInfo.h"

	#include "LCSelectPCError.h"
	#include "LCReconnect.h"
	#include "LGIncomingConnection.h"

	#include "chinabilling/CBillingInfo.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// CLSelectPCHandler::execute()
// 
// 로그인 서버는 이 패킷을 받으면, 지정된 Name + PCType 를 가진 PC 를 로딩한다.�
// 이 PC가 플레이어의 캐릭터라면 이 PC가 기존에 있던 존을 알아내서
// 그 존을 담당한 게임 서버에게 LGIncomingConnection 을 전송한다.
// 직후 클라이언트에게 LCReconnect 패킷을 보내서, 게임 서버로 연결하도록
// 해준다.
//////////////////////////////////////////////////////////////////////////////
void CLSelectPCHandler::execute (CLSelectPC* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	bool bCheckATTR = false;

	// 로그인 서버에서 billing 연결 부분을 빼기로 한다.
    // 애드빌 요청 사항. by bezz 2003.04.22
/*#ifdef __CONNECT_BILLING_SYSTEM__

	// 빌링 시스템으로부터 체크를 받는 경우
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
			// 걍 통과~
			cout << "isPayPlaying: " << pLoginPlayer->getID().c_str() << endl;

			// 그러나.. 밑에서 능력치 체크를 해야한다.
			if (pLoginPlayer->getPayType()!=PAY_TYPE_FREE)
			{
				bCheckATTR = true;
			}
		}
		else
		{
			cout <<  "CannotPlay: " << pLoginPlayer->getID().c_str() << endl;

			// 게임 할 수 없는 캐릭터(빌링 관련)
			LCSelectPCError lcSelectPCError;
			lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY);
			pLoginPlayer->sendPacket(&lcSelectPCError);	

			//throw DisconnectException("cannot playing");
			return;
		}
	}
	else 
	{
		// 아직 빌링시스템으로부터 검증이 되지 않은 상태
		// 클라이언트에서 더 기다리도록 해야한다.
		// 아니면, 일단 그냥 넘어가고.. 겜 서버에서 짤리도록 할까?
		// 아직 결제 정보가 체크되지 않았다.
		cout << "NotBillingChecked: " << pLoginPlayer->getID().c_str();

		if (pLoginPlayer->isPayPlaying()
			&& pLoginPlayer->getPayType()==PAY_TYPE_FREE)
		{
			// 완전 무료 사용자는 그냥 통과한다.
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
	if (!pLoginPlayer->isAgree() )
	{
		LCSelectPCError lcSelectPCError;
		lcSelectPCError.setCode(SELECT_PC_DIDNOT_AGREE);
		pLoginPlayer->sendPacket(&lcSelectPCError);

		return;
	}
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
	if (pLoginPlayer->isCBillingVerified() )
	{
		if (!pLoginPlayer->isPayPlayer() )
		{
			LCSelectPCError lcSelectPCError;
			lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY);
			pLoginPlayer->sendPacket(&lcSelectPCError);

			return;
		}
	}
	else
	{
		LCSelectPCError lcSelectPCError;
		lcSelectPCError.setCode(SELECT_PC_NOT_BILLING_CHECK);
		pLoginPlayer->sendPacket(&lcSelectPCError);

		return;
	}

#endif

// 애드빌 빌링은 사용하지 않아도..
// 능력치 제한 체크는 해야하는 경우
#ifdef __PAY_SYSTEM_FREE_LIMIT__
	// 유료 사용자가 아닌 경우는 ... 능력치 체크한다.
	if (!pLoginPlayer->isPayPlaying())
	{
		bCheckATTR = true;
	}
#endif


	if (pLoginPlayer->getPlayerStatus() != LPS_PC_MANAGEMENT)
		throw DisconnectException("invalid player status");

	// PC 의 정보를 데이타베이스로부터 가져 온다.
	Statement* pStmt = NULL;
	Statement* pStmt1 = NULL;	// (!)
	Result* pResult;
	WorldID_t WorldID = pLoginPlayer->getWorldID();

	try 
	{
		pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement(); // (!)
        pStmt = g_pDatabaseManager->getConnection((TID)WorldID )->createStatement();

		//----------------------------------------------------------------------
		// PC 가 마지막으로 플레이한 존의 아이디를 가져온다.
		//----------------------------------------------------------------------

		// 슬레이어 혹은 뱀파이어 테이블에서 내가 소유한 액티브 캐릭터를 찾는다.
		/*
		pResult = pStmt->executeQuery(
			"SELECT ZoneID, Slot FROM %s WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
			pPacket->getPCType() == PC_SLAYER ? "Slayer" : "Vampire" ,
			pPacket->getPCName().c_str() ,
			pLoginPlayer->getID().c_str()
		);
		*/

		bool isSlayer =  (pPacket->getPCType() == PC_SLAYER);
		bool isVampire =  (pPacket->getPCType() == PC_VAMPIRE);

		if (isSlayer)
		{
			pResult = pStmt->executeQuery(
				"SELECT ZoneID, Slot, GREATEST(SwordLevel,BladeLevel,GunLevel,EnchantLevel,HealLevel), Competence FROM Slayer WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);
		}
		else if (isVampire)
		{
			pResult = pStmt->executeQuery(
				"SELECT ZoneID, Slot, Level, Competence FROM Vampire WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);
		}
		else 
		{
			pResult = pStmt->executeQuery(
				"SELECT ZoneID, Slot, Level, Competence FROM Ousters WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);
		}
	
		// 그런 PC가 없을 경우
		if (pResult->getRowCount() != 1)
		{
			SAFE_DELETE(pStmt);
			throw InvalidProtocolException("no such PC exist.");
		}

		pResult->next();

		ZoneID_t zoneID = pResult->getWORD(1);
		string slotStr 	= pResult->getString(2);

		// 능력치 체크. by sigi. 2002.11.22
		if (bCheckATTR)
		{
		#ifdef __PAY_SYSTEM_FREE_LIMIT__
			if (isSlayer)
			{
				static int slayerSum = g_pConfig->getPropertyInt("FreePlaySlayerDomainSum");

				int DomainSUM = pResult->getInt(3);

				if (DomainSUM > slayerSum)
				{
					LCSelectPCError lcSelectPCError;
					lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY_BY_ATTR);
					pLoginPlayer->sendPacket(&lcSelectPCError);	
					SAFE_DELETE(pStmt);
					return;
				}
			}
			else
			{
				static int vampireLevel = g_pConfig->getPropertyInt("FreePlayVampireLevel");

				int Level = pResult->getInt(3);

				if (Level > vampireLevel)
				{
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
		// PK Server 체크
		//////////////////////////////////////////////////////////////////////////////////////
		bool bNonPKServer = g_pGameServerInfoManager->getGameServerInfo(1, pLoginPlayer->getServerGroupID(), pLoginPlayer->getWorldID() )->isNonPKServer();
		if (bNonPKServer )
		{
			cout << "WorldID:" << (int)(pLoginPlayer->getWorldID()) << " ServerGroupID:" << (int)(pLoginPlayer->getServerGroupID()) << endl;

			int playerLevel = pResult->getInt(3);
			int competence = pResult->getInt(4);

			// 40 레벨 보다 높은 플레이어는 들어갈 수 없다.
			// 운영자는 들어가야한다.
			if (playerLevel > 80 && competence == 3 )
			{
				LCSelectPCError lcSelectPCError;
				lcSelectPCError.setCode(SELECT_PC_CANNOT_PLAY_BY_ATTR);
				pLoginPlayer->sendPacket(&lcSelectPCError);	
				SAFE_DELETE(pStmt);
				return;
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////

		if (slotStr.size()!=5)
		{
			SAFE_DELETE(pStmt);
			throw InvalidProtocolException("no slot exist.");
		}

		int slot = slotStr.at(4) - '0';

		//----------------------------------------------------------------------
		// 이 존을 관리하는 게임 서버 정보를 가져온다.
		//----------------------------------------------------------------------
		GameServerInfo* pGameServerInfo;
		if (zoneID > 10000 && zoneID < 30000 )
		{
			// 캐릭터가 길드 아지트에 있다. 길드 아지트 존의 정보는 login server에 없으므로 대충 땜빵한다.
			pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(1, pLoginPlayer->getServerGroupID(), WorldID);
		}
		else
		{
			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(zoneID);
			ZoneGroupInfo* pZoneGroupInfo = g_pZoneGroupInfoManager->getZoneGroupInfo(pZoneInfo->getZoneGroupID());
			//cout << "ConnctServerGroup: " << (int)pLoginPlayer->getServerGroupID() << ", ServerID: " << (int)pZoneGroupInfo->getServerID();
			cout << "WorldID " << (int)WorldID << ", ServerGroupID : " << (int)pLoginPlayer->getServerGroupID() << ", ServerID : " << (int)pZoneGroupInfo->getServerID() << endl;
			pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(pZoneGroupInfo->getServerID(), pLoginPlayer->getServerGroupID(), WorldID);
		}

		//----------------------------------------------------------------------
		// 이 사용자의 현재 접속 서버 정보를 가져온다.
		//----------------------------------------------------------------------
//		GameServerInfo* pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(pPlayer->getServerID());


		//----------------------------------------------------------------------
		// 게임서버에게 incoming connection 이 올 거라고 알려준다.
		//----------------------------------------------------------------------
		LGIncomingConnection lgIncomingConnection;
		lgIncomingConnection.setClientIP(pLoginPlayer->getSocket()->getHost());
		lgIncomingConnection.setPlayerID(pLoginPlayer->getID());
		lgIncomingConnection.setPCName(pPacket->getPCName());

		//--------------------------------------------------------------------------------
		//
		// *CAUTION*
		//
		// LoginPlayer::setPlayerStatus()와 GameServerManager::sendPacket()의 순서에 주의하라.
		// 단순하게 생각하면 sendPacket()후에 setPlayerStatus()를 호출하는 것이 논리에 합당
		// 하지만, 실제로 그렇게 하면 setPlayerStatus()를 호출하기 전에 게임 서버로부터
		// GLIncomingConnectionXXX 패킷이 날아와서 그 핸들러가 실행된다. - -;
		// 따라서, 아래와 같이 상태를 먼저 지정한 후에 UDP 패킷을 전송해야 한다.
		//
		//--------------------------------------------------------------------------------
		pLoginPlayer->setPlayerStatus(LPS_AFTER_SENDING_LG_INCOMING_CONNECTION);

		// by tiancaiamao: when gameserver is behind docker, it may have a docker internal IP 172.20.0.1 and a outside IP in database GameServerInfo table.
		// The outside IP should be used.
		pLoginPlayer->setGameServerIP(pGameServerInfo->getIP());

/*
		// 어쩔 수 없이 user name 을 사용해서 하드코딩한다. -_-;
		g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , pGameServerInfo->getUDPPort() , &lgIncomingConnection);
*/
		
		if (g_pConfig->getProperty("User") == "excel96")
			//g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , pGameServerInfo->getUDPPort(), &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "beowulf")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 8886 , &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "crazydog")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 6665, &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "elcastle") {
			cout << "gameserver ip: " <<  pGameServerInfo->getIP() << ", port: "  << g_pConfig->getPropertyInt("GameServerUDPPort") << endl;
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 8885 , &lgIncomingConnection);
		} else if (g_pConfig->getProperty("User") == "elca")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 3335 , &lgIncomingConnection);

		// 마지막으로 접속한 slot 기억. by sigi. 2002.5.6
		pStmt1->executeQuery(	// (!)
		//pStmt->executeQuery(
			"UPDATE Player Set CurrentWorldID = %d, CurrentServerGroupID = %d, LastSlot = %d WHERE PlayerID = '%s'",
			WorldID,
			pLoginPlayer->getServerGroupID(),
			slot,
			pLoginPlayer->getID().c_str()
		);

		pStmt->executeQuery("UPDATE Slayer Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(), pPacket->getPCName().c_str());
		pStmt->executeQuery("UPDATE Vampire Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(), pPacket->getPCName().c_str());
		pStmt->executeQuery("UPDATE Ousters Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(), pPacket->getPCName().c_str());

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); //(!)

		//cout << "CLSelectPC SendPacket to Server IP : " << pGameServerInfo->getIP() << endl;
	} 
	catch (SQLQueryException & sqe) 
	{
		//cout << sqe.toString() << endl;

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); //(!)

		throw DisconnectException(sqe.toString());
	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;

		msg << "Critical Error : data intergrity broken at ZoneInfo - ZoneGroupInfo - GameServerInfo : " << nsee.toString();

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); //(!)

		throw Error(msg.toString());
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
