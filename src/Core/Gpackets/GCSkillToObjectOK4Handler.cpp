//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK4Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToObjectOK4.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK4Handler::execute ( GCSkillToObjectOK4 * pGCSkillToObjectOK4 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToObjectOK4->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToObjectOK4->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
