//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAcceptUnion.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAcceptUnion.h"


void CGAcceptUnion::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read( m_GuildID );

	__END_CATCH
}

void CGAcceptUnion::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write( m_GuildID );

	__END_CATCH
}

void CGAcceptUnion::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGAcceptUnionHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGAcceptUnion::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGAcceptUnion("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
