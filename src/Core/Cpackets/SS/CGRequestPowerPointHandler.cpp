//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestPowerPointHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestPowerPoint.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "Assert.h"
	#include "mofus/Mofus.h"

	#ifdef __MOFUS__
		#include "mofus/MPlayerManager.h"
	#endif
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestPowerPointHandler::execute (CGRequestPowerPoint* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );


    cout << "--------------------------------------------------" << endl;
    cout << "RECV RequestPowerPoint (CellNum:" << pPacket->getCellNum()
         << ",Name:" << pCreature->getName() << ")" << endl;
    cout << "--------------------------------------------------" << endl;


#ifdef __MOFUS__
	g_pMPlayerManager->addJob( pGamePlayer->getID(), pCreature->getName(), pPacket->getCellNum() );
#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}

