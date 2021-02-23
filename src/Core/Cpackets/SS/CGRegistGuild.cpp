//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRegistGuild.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRegistGuild.h"


void CGRegistGuild::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	BYTE szGuildName, szGuildIntro;

	iStream.read( szGuildName );

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0 " );
	if ( szGuildName > 30 ) 
		throw InvalidProtocolException( "szGuildName > 30" );

	iStream.read( m_GuildName, szGuildName );

	iStream.read( szGuildIntro );

	if ( szGuildIntro > 256 )
		throw InvalidProtocolException( "szGuildIntro > 256" );

	if ( szGuildIntro != 0 )
		iStream.read( m_GuildIntro, szGuildIntro );
	else
		m_GuildIntro = "";

	__END_CATCH
}

void CGRegistGuild::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	BYTE szGuildName = m_GuildName.size();
	BYTE szGuildIntro = m_GuildIntro.size();

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0 " );
	if ( szGuildName > 30 ) 
		throw InvalidProtocolException( "szGuildName > 30" );

	if ( szGuildIntro > 256 )
		throw InvalidProtocolException( "szGuildIntro > 256" );

	oStream.write( szGuildName );
	oStream.write( m_GuildName );
	oStream.write( szGuildIntro );

	if ( szGuildIntro != 0 )
		oStream.write( m_GuildIntro ); 

	__END_CATCH
}

void CGRegistGuild::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGRegistGuildHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRegistGuild::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRegistGuild("
		<< "GuildName:" << m_GuildName
		<< "GuildIntro:" << m_GuildIntro
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
