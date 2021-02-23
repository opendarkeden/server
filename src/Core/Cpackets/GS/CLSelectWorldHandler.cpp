//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectWorldHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectWorld.h"

#ifdef __LOGIN_SERVER__
	#include "Assert.h"
	#include "LoginPlayer.h"
	#include "DatabaseManager.h"
	#include "GameServerInfoManager.h"
	#include "GameWorldInfoManager.h"
	#include "DB.h"
	#include "PCSlayerInfo.h"
	#include "PCVampireInfo.h"
	#include "GameServerGroupInfoManager.h"
	#include "ServerGroupInfo.h"
	#include "UserInfo.h"
	#include "OptionInfo.h"
	#include "UserInfoManager.h"
	#include "Shape.h"
	#include "Lpackets/LCServerList.h"

#endif

//////////////////////////////////////////////////////////////////////////////
// 월드 선택
//////////////////////////////////////////////////////////////////////////////
void CLSelectWorldHandler::execute (CLSelectWorld* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	//cout << "Start execute" << endl;

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	WorldID_t WorldID = pPacket->getWorldID();

	//Assert( WorldID <= g_pGameWorldInfoManager->getSize() );
	// by sigi. 2002.12.20
	if (WorldID > g_pGameWorldInfoManager->getSize() )
	{
		filelog("errorLogin.txt", "WorldID Over[%d/%d]", (int)WorldID, (int)g_pGameWorldInfoManager->getSize());
		throw DisconnectException("WorldID over");
	}

	// close된 상태에서 못 들어오게 막기. by sigi. 2002.1.7
	GameWorldInfo* pGameWorldInfo = g_pGameWorldInfoManager->getGameWorldInfo(WorldID);
	if (pGameWorldInfo->getStatus()==WORLD_CLOSE)
	{
		filelog("errorLogin.txt", "WorldClosed[%d]", (int)WorldID);
		throw DisconnectException("WorldClosed");
	}

	// 트랜실(2) 빼기
	//if (WorldID==2) throw DisconnectException();

	pLoginPlayer->setWorldID( WorldID );

	Statement * pStmt = NULL;

/*	BEGIN_DB
	{
		pStmt    = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		//cout << "PlayerID: " << pLoginPlayer->getID() << endl;
		pStmt->executeQuery("UPDATE Player set CurrentWorldID = %d WHERE PlayerID = '%s'", WorldID , pLoginPlayer->getID().c_str());

		SAFE_DELETE(pStmt); // by sigi
	}
	END_DB(pStmt)*/

	try 
	{
		int GroupNum = g_pGameServerGroupInfoManager->getSize(WorldID);

		//cout << "WorldNum : " << (int)GroupNum << endl;

		ServerGroupInfo* aServerGroupInfo[GroupNum];

		for(int i = 0 ; i < GroupNum; i++) 
		{
			ServerGroupInfo* pServerGroupInfo = new ServerGroupInfo();
			GameServerGroupInfo* pGameServerGroupInfo = g_pGameServerGroupInfoManager->getGameServerGroupInfo(i, WorldID );
			pServerGroupInfo->setGroupID(pGameServerGroupInfo->getGroupID());
			pServerGroupInfo->setGroupName(pGameServerGroupInfo->getGroupName());
			//pServerGroupInfo->setStat(SERVER_FREE);

			UserInfo * pUserInfo = g_pUserInfoManager->getUserInfo( pGameServerGroupInfo->getGroupID(), WorldID );
// edit by Cofee 2006-12-10
			Statement* pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
			//Statement* pStmt = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();
			Result* pResult = pStmt->executeQuery("SELECT Count(*) FROM Player where LogOn='GAME' AND CurrentWorldID='%d'",(int)WorldID);
		
			pResult->next();
		
			int GroupCount = pResult->getInt(1);
			WORD UserModify = 500;
			/*
#ifdef __CHINA_SERVER__
			WORD UserMax = 1800;
#else
			WORD UserMax = 1500;
#endif
*/
			WORD UserMax = 1010;
			if(GroupCount < 100 + UserModify )//if (pUserInfo->getUserNum() < 100 + UserModify )
			{
				pServerGroupInfo->setStat(SERVER_FREE);
			}
			else if (GroupCount < 250 + UserModify )//(pUserInfo->getUserNum() < 250 + UserModify )
			{
				pServerGroupInfo->setStat(SERVER_NORMAL);
			}
			else if (GroupCount < 400 + UserModify )//(pUserInfo->getUserNum() < 400 + UserModify )
			{
				pServerGroupInfo->setStat(SERVER_BUSY);
			}
			/*
#ifdef __CHINA_SERVER__
			else if (pUserInfo->getUserNum() < 1000 + UserModify )
#else
			else if (pUserInfo->getUserNum() < 500 + UserModify )
#endif
*/
			else if (GroupCount < 500 + UserModify )//(pUserInfo->getUserNum() < 500 + UserModify )
			{
				pServerGroupInfo->setStat(SERVER_VERY_BUSY);
			}
			else //if (pUserInfo->getUserNum() >= 500 + UserModify )
			{
				pServerGroupInfo->setStat(SERVER_FULL);
			}
			//else
			{
			//pServerGroupInfo->setStat(SERVER_DOWN);
			}

			if (GroupCount >= UserMax)//(pUserInfo->getUserNum() >= UserMax)
			{
				pServerGroupInfo->setStat(SERVER_FULL);
			}

			if ( pGameServerGroupInfo->getStat() == SERVER_DOWN )
			{
				pServerGroupInfo->setStat( SERVER_DOWN );
			}

			aServerGroupInfo[i] = pServerGroupInfo;

			//cout << "AddServer : " << pServerGroupInfo->getGroupName() << endl;
		}

		LCServerList lcServerList;

		pStmt = NULL;
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			Result * pResult = pStmt->executeQuery("SELECT CurrentServerGroupID FROM Player where PlayerID='%s'" , pLoginPlayer->getID().c_str() );

			if( pResult->next() ) {
				lcServerList.setCurrentServerGroupID( pResult->getInt(1) );
			}

			SAFE_DELETE(pStmt);	// by sigi -_-
		}
		END_DB(pStmt)	// by sigi T_T

		for(int k = 0; k < GroupNum; k++) 
		{
			lcServerList.addListElement(aServerGroupInfo[k]);
		}

		pLoginPlayer->sendPacket(&lcServerList);
	
//		pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);

	} 
	catch (Throwable & t) 
	{
		//cout << t.toString() << endl;
	}
	//cout << "End execute" << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}
