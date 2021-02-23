//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMineExplosionOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMineExplosionOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK2Handler::execute ( GCMineExplosionOK2 * pGCMineExplosionOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCMineExplosionOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCMineExplosionOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
