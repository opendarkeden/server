//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddInjuriousCreatureHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddInjuriousCreature.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "PCFinder.h"

	#include "Gpackets/GCAddInjuriousCreature.h"
	#include "Gpackets/GCAddInjuriousCreatureFailed.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddInjuriousCreatureHandler::execute (CGAddInjuriousCreature* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}
