//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCKnocksTargetBackOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK1Handler::execute ( GCKnocksTargetBackOK1 * pGCKnocksTargetBackOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCKnocksTargetBackOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCKnocksTargetBackOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
