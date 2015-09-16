
//////////////////////////////////////////////////////////////////////
//
// Filename    : CGAuthKeyHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "CGAuthKey.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "EventKick.h"
//#include "gameguard/CSAuth.h"
#include "GCSystemMessage.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// 클라이언트에서 서버로부터 메시지를 받았을때 실행되는 메쏘드이다.
//
//////////////////////////////////////////////////////////////////////
void CGAuthKeyHandler::execute (CGAuthKey * pPacket , Player * pPlayer )
	 throw(ProtocolException , Error )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
/*
	Assert(pPacket != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	DWORD key = pPacket->getKey();
	if (!pGamePlayer->getCSAuth().CheckAuthDword(key) )
	{
		filelog("CSAuth.log", "[%s] 인증 값이 잘못되었습니다.", pGamePlayer->getID().c_str());

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage("nProtect GameGuard 인증에 실패했습니다. 실행 파일이 변조되거나 GameGuard 파일이 손상되었습니다.");
		pGamePlayer->sendPacket(&gcSystemMessage);

		EventKick* pKick = new EventKick(pGamePlayer);
		pKick->setDeadline(100);
//		pKick->setMessage("GameGuard 인증 코드가 잘못되었습니다. 10초 뒤에 연결이 종료됩니다.");
		pKick->sendMessage();

		pGamePlayer->addEvent(pKick);
	}
*/
#endif
	
	__END_CATCH
}
