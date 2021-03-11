//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDeleteSMSAddress.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDeleteSMSAddress.h"

CGDeleteSMSAddress::CGDeleteSMSAddress () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGDeleteSMSAddress::~CGDeleteSMSAddress () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGDeleteSMSAddress::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_ElementID);

	__END_CATCH
}

void CGDeleteSMSAddress::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ElementID);

	__END_CATCH
}

void CGDeleteSMSAddress::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGDeleteSMSAddressHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGDeleteSMSAddress::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGDeleteSMSAddress("
		<< ")";
	return msg.toString();

	__END_CATCH
}
