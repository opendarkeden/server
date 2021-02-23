//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToTileOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToTileOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK2Handler::execute ( GCSkillToTileOK2 * pGCSkillToTileOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToTileOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToTileOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
