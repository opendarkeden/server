//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitUnionDeny.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitUnionDeny.h"


void CGQuitUnionDeny::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read( m_GuildID );

	__END_CATCH
}

void CGQuitUnionDeny::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write( m_GuildID );

	__END_CATCH
}

void CGQuitUnionDeny::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGQuitUnionDenyHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGQuitUnionDeny::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGQuitUnionDeny("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
