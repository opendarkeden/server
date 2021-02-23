//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackMeleeOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAttackMeleeOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackMeleeOK2Handler::execute ( GCAttackMeleeOK2 * pGCAttackMeleeOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCAttackMeleeOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCAttackMeleeOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
