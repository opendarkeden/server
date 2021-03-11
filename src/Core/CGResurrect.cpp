//////////////////////////////////////////////////////////////////////////////
// Filename    : CGResurrect.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGResurrect.h"

void CGResurrect::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	__END_CATCH
}
		    
void CGResurrect::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	__END_CATCH
}

void CGResurrect::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGResurrectHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGResurrect::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGResurrect()";
	return msg.toString();

	__END_CATCH
}
