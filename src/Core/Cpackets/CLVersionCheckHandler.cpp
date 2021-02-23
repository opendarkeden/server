//////////////////////////////////////////////////////////////////////////////
// Filename    : CLVersionCheckHandler.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLVersionCheck.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "Assert.h"

	#include "Lpackets/LCVersionCheckOK.h"
	#include "Lpackets/LCVersionCheckError.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 이 패킷은 클라이언트가 아이디와 패스워드를 암호화해서 
// 로그인 서버로 전송한다. 로그인 서버는 이 패킷을 받아서
// 플레이어의 아이디와 패스워드가 정확한지 DB로부터 읽어서
// 비교한 후, 로그인의 성공 여부를 전송한다.
//////////////////////////////////////////////////////////////////////////////
void CLVersionCheckHandler::execute (CLVersionCheck* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	Statement*   pStmt        = NULL;
	Result*      pResult      = NULL;

	BEGIN_DB
	{
		//----------------------------------------------------------------------
		// *CAUTION*
		// Server상에 있는 Version Field는 UpdateServer와 항상 동일시 해야한다.
		//----------------------------------------------------------------------

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Version FROM ClientVersion");

		// 쿼리 결과 ROW 의 개수가 0 이라는 뜻은 
		// Update하지 않은 클라이언트이다.
		// 따라서 프로그램을 재가동 하고 업데이트를 하게 해야 한다.
		Assert(pResult->getRowCount() != 0);
		pResult->next();

		DWORD Version       = pResult->getInt(1);
		DWORD ClientVersion = pPacket->getVersion();
	
		if (Version == ClientVersion) 
		{
			// 로그인 성공을 알려준다.
			LCVersionCheckOK lcVersionCheckOK;
			pLoginPlayer->sendPacket(&lcVersionCheckOK);
		} 
		else 
		{
			LCVersionCheckError lcVersionCheckError;
			pLoginPlayer->sendPacket(&lcVersionCheckError);
			//pLoginPlayer->disconnect(DISCONNECTED);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

#endif

	__END_DEBUG_EX __END_CATCH
}
