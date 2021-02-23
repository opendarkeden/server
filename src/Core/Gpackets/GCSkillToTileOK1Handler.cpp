//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToTileOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1Handler::execute ( GCSkillToTileOK1 * pGCSkillToTileOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __GAME_CLIENT__

	//cout << pGCSkillToTileOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToTileOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
