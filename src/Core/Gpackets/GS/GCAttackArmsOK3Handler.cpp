//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackArmsOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK3Handler::execute ( GCAttackArmsOK3 * pGCAttackArmsOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackArmsOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackArmsOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
