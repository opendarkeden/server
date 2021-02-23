//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestStoreInfo.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestStoreInfo.h"

void CGRequestStoreInfo::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_OwnerObjectID);

	__END_CATCH
}

void CGRequestStoreInfo::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_OwnerObjectID);

	__END_CATCH
}

void CGRequestStoreInfo::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGRequestStoreInfoHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRequestStoreInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRequestStoreInfo("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
