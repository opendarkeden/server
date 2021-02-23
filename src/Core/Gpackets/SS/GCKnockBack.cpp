//////////////////////////////////////////////////////////////////////////////
// Filename    : GCKnockBack.cpp 
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCKnockBack.h"



void GCKnockBack::read ( SocketInputStream & iStream )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_OriginX );
	iStream.read( m_OriginY );
	iStream.read( m_TargetX );
	iStream.read( m_TargetY );

	__END_CATCH
}
		    
void GCKnockBack::write ( SocketOutputStream & oStream )
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_OriginX );
	oStream.write( m_OriginY );
	oStream.write( m_TargetX );
	oStream.write( m_TargetY );

	__END_CATCH
}

void GCKnockBack::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCKnockBackHandler::execute( this , pPlayer );
		
	__END_CATCH
}

string GCKnockBack::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCKnockBack("
		<< "ObjectID:"    << (int)m_ObjectID 
		<< "Origin(X,Y):" << (int)m_OriginX << "," << (int)m_OriginY
		<< "Target(X,Y):" << (int)m_TargetX << "," << (int)m_TargetY
		<< ")";
	return msg.toString();

	__END_CATCH
}
