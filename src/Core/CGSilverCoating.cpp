//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSilverCoating.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSilverCoating.h"

void CGSilverCoating::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);

	__END_CATCH
}

void CGSilverCoating::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGSilverCoating::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGSilverCoatingHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGSilverCoating::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGSilverCoating()";
	return msg.toString();

	__END_CATCH
}
