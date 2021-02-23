//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSMSAddressList.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSMSAddressList.h"

void CGSMSAddressList::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	__END_CATCH
}
		    
void CGSMSAddressList::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	__END_CATCH
}

void CGSMSAddressList::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSMSAddressListHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSMSAddressList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSMSAddressList("
	    << ")";
	
	return msg.toString();

	__END_CATCH
}
