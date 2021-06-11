//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDenyUnion.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDenyUnion.h"


void CGDenyUnion::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_GuildID);

	__END_CATCH
}

void CGDenyUnion::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_GuildID);

	__END_CATCH
}

void CGDenyUnion::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGDenyUnionHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGDenyUnion::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGDenyUnion("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
