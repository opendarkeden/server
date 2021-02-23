//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCKnocksTargetBackOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK2Handler::execute ( GCKnocksTargetBackOK2 * pGCKnocksTargetBackOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCKnocksTargetBackOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCKnocksTargetBackOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
