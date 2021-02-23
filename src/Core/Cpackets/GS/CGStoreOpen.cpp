//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreOpen.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreOpen.h"

void CGStoreOpen::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void CGStoreOpen::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void CGStoreOpen::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGStoreOpenHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGStoreOpen::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGStoreOpen("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
