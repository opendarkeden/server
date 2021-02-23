//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnockBackHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCKnockBack.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnockBackHandler::execute ( GCKnockBack * pGCKnockBack , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCKnockBack->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCKnockBack->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
