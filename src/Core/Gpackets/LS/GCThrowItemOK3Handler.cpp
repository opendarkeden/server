//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowItemOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCThrowItemOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowItemOK3Handler::execute ( GCThrowItemOK3 * pGCThrowItemOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __GAME_CLIENT__

	//cout << pGCThrowItemOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCThrowItemOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
