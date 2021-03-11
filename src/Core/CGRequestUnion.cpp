//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestUnion.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestUnion.h"


void CGRequestUnion::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_GuildID);

	__END_CATCH
}

void CGRequestUnion::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_GuildID);

	__END_CATCH
}

void CGRequestUnion::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGRequestUnionHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRequestUnion::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRequestUnion("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
