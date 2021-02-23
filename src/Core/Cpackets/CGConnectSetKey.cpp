//////////////////////////////////////////////////////////////////////////////
// Filename    : CLLogin.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "libcpsso.h"
#include "CGConnectSetKey.h"

//#include "Properties.h"

void CGConnectSetKey::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read( m_EncryptKey );
	iStream.read( m_HashKey );

	__END_CATCH
}

void CGConnectSetKey::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write( m_EncryptKey );
	oStream.write( m_HashKey );

	__END_CATCH
}

void CGConnectSetKey::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGConnectSetKeyHandler::execute( this , pPlayer );

	__END_CATCH
}

