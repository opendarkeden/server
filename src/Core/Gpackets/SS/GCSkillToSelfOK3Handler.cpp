//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToSelfOK3Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillToSelfOK3.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToSelfOK3Handler::execute ( GCSkillToSelfOK3 * pGCSkillToSelfOK3 , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCSkillToSelfOK3->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCSkillToSelfOK3->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
