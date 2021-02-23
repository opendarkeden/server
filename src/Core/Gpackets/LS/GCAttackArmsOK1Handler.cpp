//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackArmsOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK1Handler::execute ( GCAttackArmsOK1 * pGCAttackArmsOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackArmsOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackArmsOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
