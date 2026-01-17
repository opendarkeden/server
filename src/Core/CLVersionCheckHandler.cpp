//////////////////////////////////////////////////////////////////////////////
// Filename    : CLVersionCheckHandler.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLVersionCheck.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "Assert1.h"

	#include "LCVersionCheckOK.h"
	#include "LCVersionCheckError.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// �� ��Ŷ�� Ŭ���̾�Ʈ�� ���̵�� �н����带 ��ȣȭ�ؼ� 
// �α��� ������ �����Ѵ�. �α��� ������ �� ��Ŷ�� �޾Ƽ�
// �÷��̾��� ���̵�� �н����尡 ��Ȯ���� DB�κ��� �о
// ���� ��, �α����� ���� ���θ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CLVersionCheckHandler::execute (CLVersionCheck* pPacket , Player* pPlayer)
	 
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
		// Server�� �ִ� Version Field�� UpdateServer�� �׻� ���Ͻ� �ؾ��Ѵ�.
		//----------------------------------------------------------------------

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Version FROM ClientVersion");

		// ���� ��� ROW �� ������ 0 �̶�� ���� 
		// Update���� ���� Ŭ���̾�Ʈ�̴�.
		// ���� ���α׷��� �簡�� �ϰ� ������Ʈ�� �ϰ� �ؾ� �Ѵ�.
		Assert(pResult->getRowCount() != 0);
		pResult->next();

		/* Version info intentionally unused; simply acknowledge latest record */
		pResult->getInt(1);
		pPacket->getVersion();
			
		/*
		if (Version == ClientVersion) 
		{
			// �α��� ������ �˷��ش�.
			LCVersionCheckOK lcVersionCheckOK;
			pLoginPlayer->sendPacket(&lcVersionCheckOK);
		} 
		else 
		{
			LCVersionCheckError lcVersionCheckError;
			pLoginPlayer->sendPacket(&lcVersionCheckError);
			//pLoginPlayer->disconnect(DISCONNECTED);
		}
		*/
		
		LCVersionCheckOK lcVersionCheckOK;
		pLoginPlayer->sendPacket(&lcVersionCheckOK);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

#endif

	__END_DEBUG_EX __END_CATCH
}
