//////////////////////////////////////////////////////////////////////
//
// Filename    : GCKnocksTargetBackOK5Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCKnocksTargetBackOK5.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5Handler::execute ( GCKnocksTargetBackOK5 * pGCKnocksTargetBackOK5 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCKnocksTargetBackOK5->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCKnocksTargetBackOK5->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
