//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackArmsOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK2Handler::execute ( GCAttackArmsOK2 * pGCAttackArmsOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackArmsOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackArmsOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
