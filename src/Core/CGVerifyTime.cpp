//////////////////////////////////////////////////////////////////////////////
// Filename    : CGVerifyTime.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGVerifyTime.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
#endif

void CGVerifyTime::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	__END_CATCH
}
		    
void CGVerifyTime::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	__END_CATCH
}

void CGVerifyTime::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGVerifyTimeHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGVerifyTime::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGVerifyTime()" ;
	return msg.toString();

	__END_CATCH
}
