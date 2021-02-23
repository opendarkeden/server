//////////////////////////////////////////////////////////////////////////////
// Filename    : CGResurrect.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGResurrect.h"

void CGResurrect::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}
		    
void CGResurrect::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void CGResurrect::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGResurrectHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGResurrect::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGResurrect()";
	return msg.toString();

	__END_CATCH
}
