//////////////////////////////////////////////////////////////////////////////
// Filename    : CGVisible.cpp 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGVisible.h"

void CGVisible::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	__END_CATCH
}
		    
void CGVisible::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void CGVisible::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGVisibleHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGVisible::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGVisible()";
	return msg.toString();

	__END_CATCH
}
