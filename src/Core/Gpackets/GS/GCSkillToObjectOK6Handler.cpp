//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK6Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK6Handler::execute ( GCSkillToObjectOK6 * pGCSkillToObjectOK6 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToObjectOK6->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToObjectOK6->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
