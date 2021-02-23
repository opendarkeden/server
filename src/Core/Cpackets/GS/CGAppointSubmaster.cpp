//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAppointSubmaster.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAppointSubmaster.h"


void CGAppointSubmaster::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szName;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName length" );

	iStream.read( m_Name, szName );

	__END_CATCH
}

void CGAppointSubmaster::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName length" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );

	__END_CATCH
}

void CGAppointSubmaster::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGAppointSubmasterHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGAppointSubmaster::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGAppointSubmaster("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< ")";
	return msg.toString();

	__END_CATCH
}
