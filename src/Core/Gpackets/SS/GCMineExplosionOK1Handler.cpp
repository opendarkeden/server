//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMineExplosionOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMineExplosionOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCMineExplosionOK1Handler::execute ( GCMineExplosionOK1 * pGCMineExplosionOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCMineExplosionOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCMineExplosionOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
