//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK6Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToTileOK6.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK6Handler::execute ( GCSkillToTileOK6 * pGCSkillToTileOK6 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToTileOK6->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToTileOK6->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
