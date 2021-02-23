//--------------------------------------------------------------------------------
//
// Filename    : GCChangeWeatherHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "GCChangeWeather.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#endif


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCChangeWeatherHandler::execute ( GCChangeWeather * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	#if __LINUX__

		//cout << pPacket->toString() << endl;

	#elif __WINDOW__

	#endif

#endif

	__END_DEBUG_EX __END_CATCH
}
