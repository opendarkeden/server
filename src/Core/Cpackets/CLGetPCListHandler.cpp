//////////////////////////////////////////////////////////////////////////////
// Filename    : CLGetPCListHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLGetPCList.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
	#include "GameServerInfoManager.h"
	#include "OptionInfo.h"

	#include "Lpackets/LCPCList.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 클라이언트가 PC 의 리스트를 달라고 요청해오면, 로그인 서버는 DB로부터
// PC들의 정보를 로딩해서 LCPCList 패킷에 담아서 전송한다.
//////////////////////////////////////////////////////////////////////////////
void CLGetPCListHandler::execute (CLGetPCList* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);


	//----------------------------------------------------------------------
	// 이제 LCPCList 패킷을 만들어 보낸다
	//----------------------------------------------------------------------
	LCPCList lcPCList;
	pLoginPlayer->makePCList( lcPCList );
	pLoginPlayer->sendPacket(&lcPCList);
	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);


#endif

	__END_DEBUG_EX __END_CATCH
}
