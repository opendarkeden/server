//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK4Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToTileOK4.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK4Handler::execute ( GCSkillToTileOK4 * pGCSkillToTileOK4 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToTileOK4->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToTileOK4->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
