//--------------------------------------------------------------------------------
//
// Filename    : UCUpdateHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "UCUpdate.h"

#ifdef __UPDATE_CLIENT__

/*
	#include <stdio.h>
	#include <sys/types.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
*/

	#include "Assert.h"
	#include "Properties.h"

	#include "Resource.h"
	#include "ResourceManager.h"
	#include "UpdateManager.h"

	#include "Upackets/CUEndUpdate.h"
	#include "Upackets/CURequest.h"
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void UCUpdateHandler::execute ( UCUpdate * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}
