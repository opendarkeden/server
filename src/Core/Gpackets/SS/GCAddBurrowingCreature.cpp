//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddBurrowingCreature.cc 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCAddBurrowingCreature.h"

void GCAddBurrowingCreature::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );

	BYTE szName = 0;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too large name length");
		
	iStream.read( m_Name , szName );


	iStream.read( m_X );
	iStream.read( m_Y );
	__END_CATCH
}
		    
void GCAddBurrowingCreature::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );

	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too large name length");

	oStream.write( szName );
	oStream.write( m_Name );

	oStream.write( m_X );
	oStream.write( m_Y );
	__END_CATCH
}

void GCAddBurrowingCreature::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddBurrowingCreatureHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddBurrowingCreature::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddBurrowingCreature("
		<< "ObjectID:" << m_ObjectID 
		<< ",Name:"    << m_Name 
		<< ",X:"       << (int)m_X 
		<< ",Y:"       << (int)m_Y 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}


