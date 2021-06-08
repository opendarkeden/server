//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectBloodBibleHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectBloodBible.h"

#ifdef __GAME_SERVER__
	#include "PlayerCreature.h"
	#include "GamePlayer.h"
	#include "BloodBibleBonus.h"
	#include "BloodBibleBonusManager.h"
	#include "BloodBibleSignInfo.h"
	#include "GCBloodBibleSignInfo.h"
	#include "GCSystemMessage.h"
	#include <algorithm>
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectBloodBibleHandler::execute (CGSelectBloodBible* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	BloodBibleBonus* pBonus = NULL;

	try
	{
		pBonus = g_pBloodBibleBonusManager->getBloodBibleBonus( pPacket->getBloodBibleID() );
		if ( pBonus == NULL ) return;
	}
	catch ( NoSuchElementException& e )
	{
		return;
	}

	if ( pPC->getRace() != pBonus->getRace() )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "�޷�ʹ�õ�ʥ��.");
		pGamePlayer->sendPacket( &gcSM );
		return;
	}

	BloodBibleSignInfo* pInfo = pPC->getBloodBibleSign();
	if ( pInfo->getOpenNum() <= pInfo->getList().size() )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "û�п����." );
		pGamePlayer->sendPacket( &gcSM );
		return;
	}
	
	if ( find( pInfo->getList().begin(), pInfo->getList().end(), pPacket->getBloodBibleID() ) != pInfo->getList().end() )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( "��װ����ʥ��." );
		pGamePlayer->sendPacket( &gcSM );
		return;
	}

	GCSystemMessage gcSM;
	gcSM.setMessage( "��װ��Ѫ֮ʥ��." );
	pGamePlayer->sendPacket( &gcSM );

	pInfo->getList().push_back( pPacket->getBloodBibleID() );
	GCBloodBibleSignInfo gcInfo;
	gcInfo.setSignInfo( pInfo );
	pGamePlayer->sendPacket( &gcInfo );

	pPC->initAllStatAndSend();

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

