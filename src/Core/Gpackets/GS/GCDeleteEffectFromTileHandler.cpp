//////////////////////////////////////////////////////////////////////
//
// Filename    : GCDeleteEffectFromTileHandler.cc
// Written By  : crazydog
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCDeleteEffectFromTile.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCDeleteEffectFromTileHandler::execute ( GCDeleteEffectFromTile * pGCDeleteEffectFromTile , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pGCDeleteEffectFromTile->toString() << endl;
	
#elif __WINDOWS__

#endif

	__END_DEBUG_EX __END_CATCH
}
