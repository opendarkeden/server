//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodDrainOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCBloodDrainOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCBloodDrainOK1Handler::execute ( GCBloodDrainOK1 * pGCBloodDrainOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCBloodDrainOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCBloodDrainOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
