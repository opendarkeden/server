//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCrossCounterOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCCrossCounterOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCrossCounterOK3Handler::execute ( GCCrossCounterOK3 * pGCCrossCounterOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCCrossCounterOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCCrossCounterOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
