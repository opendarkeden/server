//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackArmsOK5Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackArmsOK5.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK5Handler::execute ( GCAttackArmsOK5 * pGCAttackArmsOK5 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackArmsOK5->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackArmsOK5->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
