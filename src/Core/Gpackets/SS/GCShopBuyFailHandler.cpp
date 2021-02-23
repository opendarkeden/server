//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopBuyFailHandler.cpp
// Written By  : ±è¼º¹Î
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShopBuyFail.h"

void GCShopBuyFailHandler::execute ( GCShopBuyFail * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG_EX __END_CATCH
}
