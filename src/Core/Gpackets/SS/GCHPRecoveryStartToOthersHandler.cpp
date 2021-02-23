//////////////////////////////////////////////////////////////////////
//
// Filename    : GCHPRecoveryStartToOthersHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCHPRecoveryStartToOthers.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthersHandler::execute ( GCHPRecoveryStartToOthers * pGCHPRecoveryStartToOthers , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCHPRecoveryStartToOthers->toString() << endl;
	
#elif __WINDOWS__
#endif

	__END_DEBUG_EX __END_CATCH
}
