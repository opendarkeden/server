//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodDrainOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCBloodDrainOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCBloodDrainOK3Handler::execute ( GCBloodDrainOK3 * pGCBloodDrainOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCBloodDrainOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCBloodDrainOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
