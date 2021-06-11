//----------------------------------------------------------------------
// 
// Filename    : LCCreatePCOK.cpp
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

// include files
#include "LCCreatePCOK.h"

//----------------------------------------------------------------------
// execute packet handler
//----------------------------------------------------------------------
void LCCreatePCOK::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	LCCreatePCOKHandler::execute(this , pPlayer);
		
	__END_CATCH
}


