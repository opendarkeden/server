//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToTileOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK3Handler::execute ( GCSkillToTileOK3 * pGCSkillToTileOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToTileOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToTileOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
