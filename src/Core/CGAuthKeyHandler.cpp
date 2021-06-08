
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
#include "gameguard/CSAuth.h"
#include "GCSystemMessage.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void CGAuthKeyHandler::execute ( CGAuthKey * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	DWORD key = pPacket->getKey();
// 	if ( !pGamePlayer->getCSAuth().CheckAuthDword(key) )
// 	{
// 		filelog("CSAuth.log", "[%s] ���� ���� �߸��Ǿ����ϴ�.", pGamePlayer->getID().c_str());

// 		GCSystemMessage gcSystemMessage;
// 		gcSystemMessage.setMessage("nProtect GameGuard��֤ʧ��.ִ���ļ������GameGuard�ļ���.");
// 		pGamePlayer->sendPacket( &gcSystemMessage );

// 		EventKick* pKick = new EventKick( pGamePlayer );
// 		pKick->setDeadline(100);
// //		pKick->setMessage("GameGuard ���� �ڵ尡 �߸��Ǿ����ϴ�. 10�� �ڿ� ������ ����˴ϴ�.");
// 		pKick->sendMessage();

// 		pGamePlayer->addEvent(pKick);
// 	}

#endif
	
	__END_CATCH
}
