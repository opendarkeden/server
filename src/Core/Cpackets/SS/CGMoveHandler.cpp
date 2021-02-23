//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMoveHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGMove.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "ZoneUtil.h"
	#include "Slayer.h"
	#include "Effect.h"
	#include "Timeval.h"

	#include "skill/Sniping.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGMoveHandler::execute (CGMove* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		// 이 상태에서는 크리처가 옳게 로딩되었어야 하므로, NULL 이 아니어야 한다.
		// PLAYER_INGAME 자체가 크리처 로딩이 성공되었음을 의미한다.
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		if (pCreature->isDead()) return;

		// 포탈 이동을 했음에도 불구하고, 클라이언트 길찾기의 맹점으로 인해서
		// 서버상에서 크리처가 존에서 IPM 으로 옮겨진 상태에서 CGMove 가 날아올
		// 가능성이 있다. 헥헥..
		if (pCreature->getZone() == NULL) return;
	
		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		if (pCreature->isSlayer() && pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
		{
			g_Sniping.checkRevealRatio(pCreature, 10, 20);
		}

		// 특정 PC의 이동이 존레벨로 처리되는 이유는, PC의 이동을 보고 있는 다른 PC들에게
		// 브로드캐스트해야 하기 때문이다. 이때, CGMove 패킷에 방향뿐만 아니라 현재 좌표가
		// 포함된 이유는, 점프 체크를 하기 위해서이다.
		pZone->movePC(pCreature , pPacket->getX() , pPacket->getY() , pPacket->getDir());
	}

#endif
	
	__END_DEBUG_EX __END_CATCH
}
