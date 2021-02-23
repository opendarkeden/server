//////////////////////////////////////////////////////////////////////////////
// Filename    : CGJoinGuild.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGJoinGuild.h"


void CGJoinGuild::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	BYTE szGuildMemberIntro;

	iStream.read( m_GuildID );
	iStream.read( m_GuildMemberRank );
	iStream.read( szGuildMemberIntro );

	if ( szGuildMemberIntro > 256 )
		throw InvalidProtocolException( "szGuildMemberIntro > 256" );

	if ( szGuildMemberIntro != 0 )
		iStream.read( m_GuildMemberIntro, szGuildMemberIntro );
	else
		m_GuildMemberIntro = "";

	__END_CATCH
}

void CGJoinGuild::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szGuildMemberIntro = m_GuildMemberIntro.size();

	if ( szGuildMemberIntro > 256 )
		throw InvalidProtocolException( "szGuildMemberIntro > 256" );

	oStream.write( m_GuildID );
	oStream.write( m_GuildMemberRank );
	oStream.write( szGuildMemberIntro );

	if ( szGuildMemberIntro != 0 )
		oStream.write( m_GuildMemberIntro );

	__END_CATCH
}

void CGJoinGuild::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGJoinGuildHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGJoinGuild::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGJoinGuild("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< "GuildMemberIntro:" << m_GuildMemberIntro
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
