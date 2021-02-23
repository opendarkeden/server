//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTakeOutOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCTakeOutOK.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCTakeOutOKHandler::execute ( GCTakeOutOK * pGCTakeOutOK , Player * pPlayer )
	 throw ( ProtocolException, Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCTakeOutOK->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCTakeOutOK->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
