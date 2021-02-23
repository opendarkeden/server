//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCrossCounterOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCCrossCounterOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCrossCounterOK1Handler::execute ( GCCrossCounterOK1 * pGCCrossCounterOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCCrossCounterOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCCrossCounterOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
