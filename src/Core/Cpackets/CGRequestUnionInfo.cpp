//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestUnionInfo.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestUnionInfo.h"


void CGRequestUnionInfo::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	__END_CATCH
}

void CGRequestUnionInfo::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	__END_CATCH
}

void CGRequestUnionInfo::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGRequestUnionInfoHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRequestUnionInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRequestUnionInfo("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
