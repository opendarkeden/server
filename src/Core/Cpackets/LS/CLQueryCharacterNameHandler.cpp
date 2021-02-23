//////////////////////////////////////////////////////////////////////////////
// Filename    : CLQueryCharacterNameHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLQueryCharacterName.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"

	#include "DatabaseManager.h"
	#include "Connection.h"
	#include "Statement.h"
	#include "Result.h"
	#include "Assert.h"
	#include "GameWorldInfoManager.h"

	#include "Lpackets/LCQueryResultCharacterName.h"
#endif

bool isAvailableID(const char* pID);

//////////////////////////////////////////////////////////////////////////////
// DB 로부터 특정 플레이어 아이디를 찾아서 그 여부를 클라이언트로 리턴해준다.
//////////////////////////////////////////////////////////////////////////////
void CLQueryCharacterNameHandler::execute (CLQueryCharacterName* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	WorldID_t WorldID = pLoginPlayer->getWorldID();

	Assert( WorldID <= g_pGameWorldInfoManager->getSize() );

	Statement* pStmt = NULL;

	try {

		pStmt = g_pDatabaseManager->getConnection( WorldID )->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT Name FROM Slayer WHERE Name = '%s'" , 
			pPacket->getCharacterName().c_str() 
		); 

		LCQueryResultCharacterName lcQueryResultCharacterName;

		//cout << "Query Result : " << pPacket->getCharacterName() << " is ";

		lcQueryResultCharacterName.setCharacterName(pPacket->getCharacterName());

		if (pResult->getRowCount() == 0) {
		
			lcQueryResultCharacterName.setExist(false);

			//cout << "not ";

		} else {

			lcQueryResultCharacterName.setExist(true);

		}

		//--------------------------------------------------------------------------------
		// 운영자와 관련된 이름은 아닌지 검증한다.
		//--------------------------------------------------------------------------------
		// by sigi
		if (!isAvailableID(pPacket->getCharacterName().c_str()))
		{
			lcQueryResultCharacterName.setExist(true);
		}

		/*
		string text = pPacket->getCharacterName();

		list<string> InvalidTokenList;
		InvalidTokenList.push_back("관리자");
		InvalidTokenList.push_back("도우미");
		InvalidTokenList.push_back("담당자");
		InvalidTokenList.push_back("운영");
		InvalidTokenList.push_back("기획자");
		InvalidTokenList.push_back("개발자");
		InvalidTokenList.push_back("테스터");
		InvalidTokenList.push_back("직원");
		list<string>::const_iterator itr = InvalidTokenList.begin();
		for (; itr != InvalidTokenList.end(); itr++)
		{
			if (text.find(*itr) != string::npos)
			{
				lcQueryResultCharacterName.setExist(false);
			}
		}
		*/

		//cout << "exist..." << endl;
		
		pLoginPlayer->sendPacket(&lcQueryResultCharacterName);

		// 쿼리가 여러 번 올 수 있으므로, 여전히 LWFRP 이다.
		// 문제는 누군가가 프로그램을 짜서 DOS 공격을 할 수 있으므로,
		// 최소 시간을 둬야 한다는 점이다.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);
			
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
