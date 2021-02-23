//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToObjectOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3Handler::execute ( GCSkillToObjectOK3 * pGCSkillToObjectOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToObjectOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToObjectOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
