//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToSelfOK2Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToSelfOK2.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK2Handler::execute ( GCSkillToSelfOK2 * pGCSkillToSelfOK2 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToSelfOK2->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToSelfOK2->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
