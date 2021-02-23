//----------------------------------------------------------------------
//
// Filename    : LCCreatePCErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCCreatePCError.h"

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
void LCCreatePCErrorHandler::execute ( LCCreatePCError * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	cout << "Fail to create PC... (" << pPacket->toString() << ")" << endl;
	throw ProtocolException("CreatePC Failed!");

#endif
		
	__END_DEBUG_EX __END_CATCH
}
