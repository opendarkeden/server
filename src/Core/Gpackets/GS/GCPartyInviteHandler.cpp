//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyInviteHandler.cpp
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPartyInvite.h"

void GCPartyInviteHandler::execute (GCPartyInvite * pPacket , Player * pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG_EX __END_CATCH
}
