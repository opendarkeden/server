//////////////////////////////////////////////////////////////////////
//
// Filename    : LCSelectPCErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "LCSelectPCError.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void LCSelectPCErrorHandler::execute ( LCSelectPCError * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	cout << "Access Denied... (" << pPacket->toString() << ")" << endl;
	throw ProtocolException("SelectPC Failed!");

#endif
		
	__END_DEBUG_EX __END_CATCH
}
