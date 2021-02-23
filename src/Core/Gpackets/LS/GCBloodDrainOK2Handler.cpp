//////////////////////////////////////////////////////////////////////
//
// Filename    : GCBloodDrainOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCBloodDrainOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCBloodDrainOK2Handler::execute ( GCBloodDrainOK2 * pGCBloodDrainOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCBloodDrainOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCBloodDrainOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
