//////////////////////////////////////////////////////////////////////////////
// Filename    : CLQueryPlayerIDHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLQueryPlayerID.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"

	#include "DatabaseManager.h"
	#include "Connection.h"
	#include "Statement.h"
	#include "Result.h"
	#include "Assert.h"

	#include "Lpackets/LCQueryResultPlayerID.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// DB 로부터 특정 플레이어 아이디를 찾아서 그 여부를 클라이언트로 리턴해준다.
//////////////////////////////////////////////////////////////////////////////
void CLQueryPlayerIDHandler::execute (CLQueryPlayerID* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	Statement* pStmt;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT Name FROM Player WHERE PlayerID = '%s'" , 
			pPacket->getPlayerID().c_str() 
		); 

		LCQueryResultPlayerID lcQueryResultPlayerID;

		//cout << "Query Result : " << pPacket->getPlayerID() << " is ";

		lcQueryResultPlayerID.setPlayerID(pPacket->getPlayerID());

		if (pResult->getRowCount() == 0) {
		
			lcQueryResultPlayerID.setExist(false);

			//cout << "not ";

		} else {

			lcQueryResultPlayerID.setExist(true);

		}

		//cout << "exist..." << endl;
		
		pLoginPlayer->sendPacket(&lcQueryResultPlayerID);

		// 쿼리가 여러 번 올 수 있으므로, 여전히 LWFRP 이다.
		// 문제는 누군가가 프로그램을 짜서 DOS 공격을 할 수 있으므로,
		// 최소 시간을 둬야 한다는 점이다.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);
			
		SAFE_DELETE(pStmt);
		//delete pStmt;		// 2002.1.16 by sigi
	} 
	catch (SQLQueryException & sqe) 
	{
		SAFE_DELETE(pStmt);
		throw;
	}
	
#endif
		
	__END_DEBUG_EX __END_CATCH
}
