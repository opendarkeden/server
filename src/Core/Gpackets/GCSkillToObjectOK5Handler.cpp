//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK5Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToObjectOK5.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK5Handler::execute ( GCSkillToObjectOK5 * pGCSkillToObjectOK5 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToObjectOK5->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToObjectOK5->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
