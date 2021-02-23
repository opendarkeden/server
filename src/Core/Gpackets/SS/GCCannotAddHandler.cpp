//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCannotAddHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCCannotAdd.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCannotAddHandler::execute ( GCCannotAdd * pGCCannotAdd , Player * pPlayer )
	 throw ( ProtocolException, Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCCannotAdd->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCCannotAdd->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
