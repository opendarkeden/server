//----------------------------------------------------------------------
//
// Filename    : GLKickVerifyHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GLKickVerify.h"

#ifdef __LOGIN_SERVER__

	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
	#include "Lpackets/LCLoginOK.h"

#endif


//----------------------------------------------------------------------
// 
// GLKickVerifyHander::execute()
// 
// 게임 서버가 로그인 서버로부터 GLKickVerify 패킷을 받게 되면,
// ReconnectLoginInfo를 새로 추가하게 된다.
// 
//----------------------------------------------------------------------
void GLKickVerifyHandler::execute ( GLKickVerify * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __LOGIN_SERVER__

	//cout << pPacket->toString().c_str() << endl;

	try {

		g_pLoginPlayerManager->lock();

		//LoginPlayer* pLoginPlayer = g_pLoginPlayerManager->getPlayer_NOLOCKED( pPacket->getPCName() );
		Player* pPlayer = ((PlayerManager*)g_pLoginPlayerManager)->getPlayer( pPacket->getID() );
		LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

		if (pLoginPlayer!=NULL)	// NoSuch 사용하기 때문에 일단은 안해도 되지만..
		{
			// 캐릭터 이름이 같아야 한다.
			const string& name1 = pLoginPlayer->getLastCharacterName();
			const string& name2 = pPacket->getPCName();

			if (name1.size()!=0 && name2.size()!=0
				&& name1==name2)
			{
//				if ( pLoginPlayer->isMultiLogin() )
//				{
//					pLoginPlayer->setMultiLogin(false);
					pLoginPlayer->sendLCLoginOK();
//				}
//				cout << "-_-" << endl;
			}
			else
			{
				// 딴 사람이다. 신경 쓸거 없다.
			}
		}	

		g_pLoginPlayerManager->unlock();

	} catch (Throwable&) { // (NoSuchException&) { // 의미없겠지.
		g_pLoginPlayerManager->unlock();
	}

#endif
		
	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
