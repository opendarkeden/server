//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectServerHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectServer.h"

#ifdef __LOGIN_SERVER__
	#include "Assert.h"
	#include "LoginPlayer.h"
	#include "DatabaseManager.h"
	#include "GameServerInfoManager.h"
	#include "DB.h"
	#include "GameServerGroupInfoManager.h"
	#include "GameWorldInfoManager.h"
	#include "OptionInfo.h"

	#include "Lpackets/LCPCList.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 클라이언트가 PC 의 리스트를 달라고 요청해오면, 로그인 서버는 DB로부터
// PC들의 정보를 로딩해서 LCPCList 패킷에 담아서 전송한다.
//////////////////////////////////////////////////////////////////////////////
void CLSelectServerHandler::execute (CLSelectServer* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	ServerGroupID_t CurrentServerGroupID = pPacket->getServerGroupID();

	WorldID_t WorldID = pLoginPlayer->getWorldID();

	//Assert ( WorldID <= g_pGameWorldInfoManager->getSize() );
	int MaxWorldID = g_pGameWorldInfoManager->getSize();
	if (WorldID>MaxWorldID)
	{
		WorldID = MaxWorldID;
	}

	//Assert ( CurrentServerGroupID <= g_pGameServerGroupInfoManager->getSize( WorldID ) );
	int MaxServerGroupID = g_pGameServerGroupInfoManager->getSize( WorldID );
	if  (CurrentServerGroupID>MaxServerGroupID)
	{
		CurrentServerGroupID = MaxServerGroupID;
	}


	// by sigi. 2003.1.7
	GameServerGroupInfo* pGameServerGroupInfo 
		= g_pGameServerGroupInfoManager->getGameServerGroupInfo( CurrentServerGroupID, WorldID );

	Assert(pGameServerGroupInfo!=NULL);
	if (pGameServerGroupInfo->getStat() == SERVER_DOWN)
	{
		filelog("errorLogin.txt", "Server Closed: %d", CurrentServerGroupID);
		throw DisconnectException("ServerClosed");
	}


	pLoginPlayer->setServerGroupID(CurrentServerGroupID);

	Statement* pStmt = NULL;

	//----------------------------------------------------------------------
	// 이제 LCPCList 패킷을 만들어 보내자
	//----------------------------------------------------------------------
	LCPCList lcPCList;
	pLoginPlayer->makePCList( lcPCList );
	pLoginPlayer->sendPacket(&lcPCList);
	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);

/*	try
	{
		pStmt    = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();	

		pStmt->executeQuery("UPDATE Player set CurrentServerGroupID = %d WHERE PlayerID = '%s'", (int)pPacket->getServerGroupID(), pLoginPlayer->getID().c_str());

		// 쿼리 결과 및 쿼리문 객체를 삭제한다.
		SAFE_DELETE(pStmt);
	}
	catch (SQLQueryException & sce) 
	{
		//cout << sce.toString() << endl;

		// 쿼리 결과 및 쿼리문 객체를 삭제한다.
		SAFE_DELETE(pStmt);

		throw DisconnectException(sce.toString());
	}*/

#endif

	__END_DEBUG_EX __END_CATCH
}
