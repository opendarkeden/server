//////////////////////////////////////////////////////////////////////
//
// Filename    : GCThrowBombOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCThrowBombOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCThrowBombOK3Handler::execute ( GCThrowBombOK3 * pGCThrowBombOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __GAME_CLIENT__

	//cout << pGCThrowBombOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCThrowBombOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
