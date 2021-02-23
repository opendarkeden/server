//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRealWearingInfoHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCRealWearingInfo.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRealWearingInfoHandler::execute ( GCRealWearingInfo * pGCRealWearingInfo , Player * pPlayer )
	 throw ( ProtocolException, Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCRealWearingInfo->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCRealWearingInfo->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
