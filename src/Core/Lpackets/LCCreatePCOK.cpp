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
void LCCreatePCOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCCreatePCOKHandler::execute( this , pPlayer );
		
	__END_CATCH
}


