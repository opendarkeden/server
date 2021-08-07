//----------------------------------------------------------------------
//
// Filename    : LGIncomingConnectionHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "LGIncomingConnection.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "ConnectionInfo.h"
	#include "ConnectionInfoManager.h"
	#include "LoginServerManager.h"
	#include "LogDef.h"

	#include "GLIncomingConnectionError.h"
	#include "GLIncomingConnectionOK.h"

#endif

//----------------------------------------------------------------------
// 
// LGIncomingConnectionHander::execute()
// 
// ���� ������ �α��� �����κ��� LGIncomingConnection ��Ŷ�� �ް� �Ǹ�,
// ConnectionInfo�� ���� �߰��ϰ� �ȴ�.
// 
//----------------------------------------------------------------------
void LGIncomingConnectionHandler::execute (LGIncomingConnection * pPacket )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//--------------------------------------------------------------------------------
	//
	// ����Ű�� �����Ѵ�.
	//
	// *NOTE*
	//
	// ������ ����� �α��� �������� ����Ű�� �����ؼ� ���Ӽ����� ���� ��, Ŭ���̾�Ʈ��
	// �����ߴ�. �̷��� �� ��� CLSelectPCHandler::execute()���� ����Ű�� �����ϰ� 
	// GLIncomingConnectionOKHandler::execute()���� ����Ű�� Ŭ���̾�Ʈ�� ������ �Ǵµ�,
	// ó�� �޽�尡 �ٸ��Ƿ� Ű���� ��𿡼��� �����Ǿ�� �Ѵ�. ���� �ܼ��� ����� �α���
	// �÷��̾� ��ü�� �����ϸ� �Ǵµ�.. ���� �����ϴ�. �Ǵٸ� ����� ���� �������� �ٽ�
	// �α��� ������ Ű���� �ǵ����ִ� ���ε�, �̴� ��Ʈ��ũ�� Ű���� 2ȸ �պ��Ѵٴ�
	// ������ ���ʿ��ϴ�. 
	// 
	// ����, ���� �������� �����ؼ� �α��μ����� �����ִ� ���� �ξ� ��������� �ȴ�.
	//
	// *TODO*
	//
	// �־��� ���, ���ó�Ʈ��ũ�� �����۸����ؼ� Ű���� ����� �� �ִ�. (�ϱ� �� ��Ʈ
	// �н����尡 ����� ���ɼ��� �ִµ�.. - -; �̷� �ž� SSL�� ��� �ϴ°Ű�..)
	// �̸� ����ؼ� GLIncomingConnectionOK ��Ŷ�� ��ȣȭ�Ǿ�� �Ѵ�.
	//
	// ���� Ű���� �����Ұ����ؾ� �Ѵ�. (������ �ڵ带 ���� ��������������.)
	//
	//--------------------------------------------------------------------------------

    DWORD authKey = rand() << ((time(0) % 10 ) + rand()) >> (time(0)% 10);

	// CI ��ü�� �����Ѵ�.
	ConnectionInfo * pConnectionInfo = new ConnectionInfo();
	pConnectionInfo->setClientIP(pPacket->getClientIP());
	pConnectionInfo->setKey(authKey);
	pConnectionInfo->setPlayerID(pPacket->getPlayerID());
	pConnectionInfo->setPCName(pPacket->getPCName());

	//--------------------------------------------------------------------------------
	//
	// ���� �ð� + 20 �� �ĸ� expire time ���� �����Ѵ�.
	//
	// *TODO*
	//
	// expire period ���� Config ���Ͽ��� �������ָ� ���ڴ�.
	//
	//--------------------------------------------------------------------------------
	Timeval currentTime;
	getCurrentTime(currentTime);	
	currentTime.tv_sec += 30;
	pConnectionInfo->setExpireTime(currentTime);

	// debug message
	/*
	cout << "+--------------------------------+" << endl
		 << "| Incoming Connection Infomation |" << endl
		 << "+--------------------------------+" << endl
		 << "ClientIP : " << pPacket->getClientIP() << endl
		 << "Auth Key : " << authKey << endl
		 << "P C Name : " << pPacket->getPCName() << endl;
	 */

	try {

		// CIM �� �߰��Ѵ�.
		g_pConnectionInfoManager->addConnectionInfo(pConnectionInfo);

		// by sigi. 2002.12.7
		FILELOG_INCOMING_CONNECTION("connectionInfo.log", "Add [%s:%s] %s (%u)",
										pPacket->getPlayerID().c_str(),
										pPacket->getPCName().c_str(),
										pPacket->getClientIP().c_str(),
										authKey);


		// �α��� �������� �ٽ� �˷��ش�.
		GLIncomingConnectionOK glIncomingConnectionOK;
		glIncomingConnectionOK.setPlayerID(pPacket->getPlayerID());
		glIncomingConnectionOK.setTCPPort(g_pConfig->getPropertyInt("TCPPort"));
		glIncomingConnectionOK.setKey(authKey);

		g_pLoginServerManager->sendPacket(pPacket->getHost() , pPacket->getPort() , &glIncomingConnectionOK);

		cout << "LGIncomingConnectionHandler Send Packet to ServerIP : " << pPacket->getHost() << endl;
		cout << "LGIncomingConnectionHandler Send Packet to ServerPort : " << pPacket->getPort() << endl;

	} catch (DuplicatedException & de ) {

		// �������� ��� CI �� �����ϰ�, �α��� �������� GLIncomingConnectionError ��Ŷ�� �����Ѵ�.
		SAFE_DELETE(pConnectionInfo);

//		GLIncomingConnectionError glIncomingConnectionError;
//		glIncomingConnectionError.setMessage(de.toString());
//		glIncomingConnectionError.setPlayerID(pPacket->getPlayerID());

//		cout << "Step 5" << endl;
//		g_pLoginServerManager->sendPacket(pPacket->getHost() , pPacket->getPort() , &glIncomingConnectionError);
//		cout << "LGIncomingConnectionHandler Send Packet to ServerIP : " << pPacket->getHost() << endl;
	}
	
#endif
		
	__END_DEBUG_EX __END_CATCH
}
