//--------------------------------------------------------------------------------
//
// Filename    : CUEndUpdateHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "CUEndUpdate.h"

#ifdef __UPDATE_SERVER__
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void CUEndUpdateHandler::execute ( CUEndUpdate * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	throw DisconnectException();

#endif
		
	__END_CATCH
}
