//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackMeleeOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackMeleeOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackMeleeOK3Handler::execute ( GCAttackMeleeOK3 * pGCAttackMeleeOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackMeleeOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackMeleeOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
