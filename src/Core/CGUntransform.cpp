//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUntransform.cpp 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUntransform.h"

void CGUntransform::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	__END_CATCH
}

void CGUntransform::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	__END_CATCH
}

void CGUntransform::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGUntransformHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGUntransform::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUntransform()";
	return msg.toString();

	__END_CATCH
}
