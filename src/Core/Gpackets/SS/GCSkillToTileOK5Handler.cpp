//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK5Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToTileOK5.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK5Handler::execute ( GCSkillToTileOK5 * pGCSkillToTileOK5 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToTileOK5->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToTileOK5->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
