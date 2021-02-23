//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToObjectOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK2Handler::execute ( GCSkillToObjectOK2 * pGCSkillToObjectOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToObjectOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToObjectOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
