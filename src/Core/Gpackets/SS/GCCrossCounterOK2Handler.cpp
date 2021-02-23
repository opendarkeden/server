//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCrossCounterOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCCrossCounterOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCrossCounterOK2Handler::execute ( GCCrossCounterOK2 * pGCCrossCounterOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCCrossCounterOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCCrossCounterOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
