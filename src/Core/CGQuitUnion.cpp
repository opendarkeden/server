//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitUnion.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitUnion.h"


void CGQuitUnion::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read (m_GuildID);
	iStream.read (m_Method);
	
	__END_CATCH
}

void CGQuitUnion::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write (m_GuildID);
	oStream.write (m_Method);
	
	__END_CATCH
}

void CGQuitUnion::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
	CGQuitUnionHandler::execute(this , pPlayer);
	__END_CATCH
}

string CGQuitUnion::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGQuitUnion("
		<< "GuildID:" << m_GuildID
		<< "Method:" << m_Method
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
