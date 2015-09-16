//////////////////////////////////////////////////////////////////////////////
// Filename    : CLAgreementHandler.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLAgreement.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "Assert1.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 이 패킷은 클라이언트가 아이디와 패스워드를 암호화해서 
// 로그인 서버로 전송한다. 로그인 서버는 이 패킷을 받아서
// 플레이어의 아이디와 패스워드가 정확한지 DB로부터 읽어서
// 비교한 후, 로그인의 성공 여부를 전송한다.
//////////////////////////////////////////////////////////////////////////////
void CLAgreementHandler::execute (CLAgreement* pPacket , Player* pPlayer)
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__
#ifdef __NETMARBLE_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	Assert(pLoginPlayer != NULL);

	if (pPacket->isAgree() )
	{
		Statement*   pStmt        = NULL;

		BEGIN_DB
		{
			//----------------------------------------------------------------------
			// 넷마블 약관 미동의 리스트에서 삭제
			//----------------------------------------------------------------------
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("DELETE FROM PrivateAgreementRemain WHERE PlayerID = '%s'", pLoginPlayer->getID().c_str());

			// 다음 단계로 진행할 수 있게 설정
			pLoginPlayer->setAgree(true);

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
	}

#endif
#endif

	__END_DEBUG_EX __END_CATCH
}
