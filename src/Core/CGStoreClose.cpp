//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreClose.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreClose.h"

void CGStoreClose::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	__END_CATCH
}

void CGStoreClose::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	__END_CATCH
}

void CGStoreClose::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGStoreCloseHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGStoreClose::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGStoreClose("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
