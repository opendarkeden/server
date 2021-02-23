//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK1Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToObjectOK1.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK1Handler::execute ( GCSkillToObjectOK1 * pGCSkillToObjectOK1 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __GAME_CLIENT__

	//cout << pGCSkillToObjectOK1->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToObjectOK1->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
