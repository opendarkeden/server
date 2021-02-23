//////////////////////////////////////////////////////////////////////
//
// Filename    : GCDeleteandPickUpOKHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCDeleteandPickUpOK.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCDeleteandPickUpOKHandler::execute ( GCDeleteandPickUpOK * pGCDeleteandPickUpOK, Player * pPlayer )
	 throw ( ProtocolException,  Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCDeleteandPickUpOK->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCDeleteandPickUpOK->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
