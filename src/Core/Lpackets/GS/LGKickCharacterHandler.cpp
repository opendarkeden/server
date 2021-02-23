//----------------------------------------------------------------------
//
// Filename    : LGKickCharacterHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "LGKickCharacter.h"

#ifdef __GAME_SERVER__

	#include "GamePlayer.h"
	#include "LoginServerManager.h"
	#include "Creature.h"
	#include "PCFinder.h"
	#include "LogDef.h"

	#include "Gpackets/GLKickVerify.h"

#endif

//----------------------------------------------------------------------
// 
// LGKickCharacterHander::execute()
// 
// 게임 서버가 로그인 서버로부터 LGKickCharacter 패킷을 받게 되면,
// ConnectionInfo를 새로 추가하게 된다.
// 
//----------------------------------------------------------------------
void LGKickCharacterHandler::execute ( LGKickCharacter * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 냐햐햐
	/*
	if (!g_pPCFinder->setKickCharacter( pPacket->getPCName(), pPacket->getHost(), pPacket->getPort() ))
	{
		GLKickVerify glKickVerify;
		glKickVerify.setKicked(false);
		glKickVerify.setID(pPacket->getID());
		glKickVerify.setPCName(pPacket->getPCName());

		g_pLoginServerManager->sendPacket( pPacket->getHost() , pPacket->getPort() , &glKickVerify );

		//cout << "LGKickVerify Send Packet to ServerIP : " << pPacket->getHost() << endl;
		//cout << "LGKickVerify Send Packet to ServerPort : " << pPacket->getPort() << endl;
	
		return;
	}
	*/

	try {

		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		// 이름으로 사용자를 찾아온다.
		Creature* pCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPCName());

		// 캐릭터가 없는 경우에는 GLKickVerify(false)를 보낸다.
		if (pCreature == NULL)
		{
			GLKickVerify glKickVerify;
			glKickVerify.setKicked(false);
			glKickVerify.setID(pPacket->getID());
			glKickVerify.setPCName(pPacket->getPCName());

			g_pLoginServerManager->sendPacket( pPacket->getHost() , pPacket->getPort() , &glKickVerify );

			//cout << "LGKickVerify Send Packet to ServerIP : " << pPacket->getHost() << endl;
			//cout << "LGKickVerify Send Packet to ServerPort : " << pPacket->getPort() << endl;
		
			g_pPCFinder->unlock();
			return;
		}

		//cout << "KickCharacter : " << pPacket->getPCName().c_str() << endl;

		GamePlayer* pGamePlayer = NULL;
		try {

			pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		} catch (Throwable& t) {
			// pCreature->getPlayer()안에서 Assert(m_pPlayer!=NULL)때문이다.
			//filelog("kickCharacterAssert.txt", "%s", t.toString().c_str());
			g_pPCFinder->unlock();
			return;
		}

		//Assert(pGamePlayer!=NULL);
		if (pGamePlayer==NULL)	// 어떻게 가능할까? -_-;
		{
			g_pPCFinder->unlock();
			return;
		}

		int fd = -1;
		Socket* pSocket = pGamePlayer->getSocket();
		if (pSocket!=NULL) fd = (int)pSocket->getSOCKET();

		FILELOG_INCOMING_CONNECTION("incomingDisconnect.log", "Kick FD : %d, %s",
					fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()) );



		// 강제 종료 시킨다.
		pGamePlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
		pGamePlayer->setItemRatioBonusPoint(4);
		pGamePlayer->setKickForLogin(true);

		// 접속 해제 후, 응답을 보내줄 곳..
		pGamePlayer->setKickRequestHost( pPacket->getHost() );
		pGamePlayer->setKickRequestPort( pPacket->getPort() );

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	} catch ( NoSuchElementException & ) {
	}
	
#endif
		
	__END_DEBUG_EX __END_CATCH
}
