//////////////////////////////////////////////////////////////////////////////
// Filename    : CGVisible.cpp 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGVisible.h"

void CGVisible::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	__END_CATCH
}
		    
void CGVisible::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	__END_CATCH
}

void CGVisible::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGVisibleHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGVisible::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGVisible()";
	return msg.toString();

	__END_CATCH
}
