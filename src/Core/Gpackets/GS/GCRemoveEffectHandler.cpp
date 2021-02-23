//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRemoveEffectHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRemoveEffectHandler::execute ( GCRemoveEffect * pGCRemoveEffect , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __GAME_CLIENT__

	//cout << pGCRemoveEffect->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCRemoveEffect->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
