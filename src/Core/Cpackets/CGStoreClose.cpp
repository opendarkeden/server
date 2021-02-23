//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreClose.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreClose.h"

void CGStoreClose::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void CGStoreClose::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void CGStoreClose::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGStoreCloseHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGStoreClose::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGStoreClose("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
