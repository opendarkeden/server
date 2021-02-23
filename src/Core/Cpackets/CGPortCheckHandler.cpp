//----------------------------------------------------------------------
//
// Filename    : CGPortCheckHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "CGPortCheck.h"
#include "Properties.h"
#include <stdio.h>

#ifdef __GAME_SERVER__
	#include "DB.h"

#endif

//----------------------------------------------------------------------
// 
// CGPortCheckHander::execute()
// 
// 게임 서버가 로그인 서버로부터 CGPortCheck 패킷을 받게 되면,
// ConnectionInfo를 새로 추가하게 된다.
// 
//----------------------------------------------------------------------
void CGPortCheckHandler::execute ( CGPortCheck * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	const string& host = pPacket->getHost();
	DWORD IP = inet_addr(host.c_str());
	uint port = pPacket->getPort();

	//cout << "CGPortCheck: [" << IP << "] " << host.c_str() << ":" << port << endl;

	Statement* pStmt = NULL;

	try 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "INSERT IGNORE INTO UserIPInfo (Name, IP, Port, ServerID) VALUES ( '%s', %lu, %u, %d )",
									pPacket->getPCName().c_str(), IP, port, g_pConfig->getPropertyInt("ServerID") );

		if (pStmt->getAffectedRowCount()==0)
		{
			// 다시 한번 시도
			pStmt->executeQuery( "UPDATE UserIPInfo Set IP=%lu, Port=%u WHERE Name='%s'",
									IP, 
									port,
									pPacket->getPCName().c_str());

			//log(LOG_CGCONNECT, pPacket->getPCName(), "", host);
		}

		SAFE_DELETE(pStmt);

	} catch (SQLQueryException & ) {

		/*
		try {
			// 다시 한번 시도
			pStmt->executeQuery( "UPDATE UserIPInfo Set IP=%ld, Port=%d WHERE Name='%s'",
									IP, 
									port,
									pPacket->getPCName().c_str());

			//log(LOG_CGCONNECT, pPacket->getPCName(), "", host);

			SAFE_DELETE(pStmt);

		} catch (SQLQueryException & sqe) {	//se) {

			SAFE_DELETE(pStmt);
			// 무시한다.
			//throw ProtocolException("Duplicated IPInfo");
		}
		*/
		SAFE_DELETE(pStmt);
	}
#else
	cout << pPacket->toString() << endl;
	
#endif
		
	__END_DEBUG_EX __END_CATCH
}
