//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGQuestAcceptHandler.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGGQuestAccept.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "GQuestManager.h"
#endif	

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGGQuestAcceptHandler::execute (CGGQuestAccept* pPacket , Player* pPlayer)
	 throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	cout << pPC->getName() << " Accept : " << pPacket->getQuestID() << endl;

	GQuestManager* pQM = pPC->getGQuestManager();
	pQM->accept(pPacket->getQuestID());

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

