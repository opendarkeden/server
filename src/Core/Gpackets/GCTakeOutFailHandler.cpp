//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTakeOutFailHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCTakeOutFail.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCTakeOutFailHandler::execute ( GCTakeOutFail * pGCTakeOutFail , Player * pPlayer )
	 throw ( ProtocolException, Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCTakeOutFail->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCTakeOutFail->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
