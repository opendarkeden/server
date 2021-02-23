//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK4Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCKnocksTargetBackOK4.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK4Handler::execute ( GCKnocksTargetBackOK4 * pGCKnocksTargetBackOK4 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCKnocksTargetBackOK4->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCKnocksTargetBackOK4->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
