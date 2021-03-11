//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestUnionInfo.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestUnionInfo.h"


void CGRequestUnionInfo::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	__END_CATCH
}

void CGRequestUnionInfo::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	__END_CATCH
}

void CGRequestUnionInfo::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGRequestUnionInfoHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRequestUnionInfo::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRequestUnionInfo("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
