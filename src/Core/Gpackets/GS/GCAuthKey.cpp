//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAuthKey.cpp 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCAuthKey.h"

void GCAuthKey::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_Key );

	__END_CATCH
}
		    
void GCAuthKey::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_Key );

	__END_CATCH
}

void GCAuthKey::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAuthKeyHandler::execute( this , pPlayer );

	__END_CATCH
}

string GCAuthKey::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCAuthKey("
		<< "Key:" << m_Key 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


