//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSystemAvailabilitiesHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSystemAvailabilities.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSystemAvailabilitiesHandler::execute ( GCSystemAvailabilities * pGCSystemAvailabilities , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pGCSystemAvailabilities->toString() << endl;
	
#elif __WINDOWS__

#endif

	__END_DEBUG_EX __END_CATCH
}
