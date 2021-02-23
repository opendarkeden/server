//--------------------------------------------------------------------------------
//
// Filename    : GCGuildResponseHandler.cpp
// Written By  : elca, Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "GCGuildResponse.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCGuildResponseHandler::execute ( GCGuildResponse * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
		
#ifdef __GAME_CLIENT__

#endif

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
