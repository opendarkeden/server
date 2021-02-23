//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCSay.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCNPCSay.h"

void GCNPCSay::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_ScriptID );
	iStream.read( m_SubjectID );

	__END_CATCH
}
		    
void GCNPCSay::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_ScriptID );
	oStream.write( m_SubjectID );

	__END_CATCH
}

void GCNPCSay::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCNPCSayHandler::execute( this , pPlayer );

	__END_CATCH
}

string GCNPCSay::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCNPCSay("
		<< "ObjectID:" << m_ObjectID 
		<< ",ScriptID:" << m_ScriptID
		<< ",SubjectID:" << (int)m_SubjectID
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}


