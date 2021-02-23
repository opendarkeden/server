//////////////////////////////////////////////////////////////////////
//
// Filename    : GCStashSellHandler.cpp
// Written By  : ±è¼º¹Î
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCStashSell.h"

void GCStashSellHandler::execute ( GCStashSell * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
