//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK4Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackArmsOK4.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK4Handler::execute ( GCAttackArmsOK4 * pGCAttackArmsOK4 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackArmsOK4->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackArmsOK4->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
