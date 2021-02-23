//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherModifyInfoHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCOtherModifyInfo.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCOtherModifyInfoHandler::execute ( GCOtherModifyInfo * pGCOtherModifyInfo , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#if __TEST_CLIENT__

	//cout << pGCOtherModifyInfo->toString() << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pGCOtherModifyInfo->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
