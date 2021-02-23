//////////////////////////////////////////////////////////////////////
// 
// Filename    : GSAddGuild.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GSAddGuild.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GSAddGuild::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szGuildName, szGuildMaster, szGuildIntro;

	iStream.read( szGuildName );

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long guild name length" );

	iStream.read( m_GuildName, szGuildName );

	iStream.read( szGuildMaster );

	if ( szGuildMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szGuildMaster > 20 )
		throw InvalidProtocolException( "too long guild master length" );

	iStream.read( m_GuildMaster, szGuildMaster );

	iStream.read( szGuildIntro );

	if ( szGuildIntro > 256 )
		throw InvalidProtocolException( "too long guild intro length" );

	if ( szGuildIntro != 0 )
		iStream.read( m_GuildIntro, szGuildIntro );
	else
		m_GuildIntro = "";

	iStream.read( m_GuildState );
	iStream.read( m_GuildRace );
	iStream.read( m_ServerGroupID );
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GSAddGuild::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szGuildName = m_GuildName.size();
	BYTE szGuildMaster = m_GuildMaster.size();
	BYTE szGuildIntro = m_GuildIntro.size();

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long guild name length" );

	if ( szGuildMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szGuildMaster > 20 )
		throw InvalidProtocolException( "too long guild master length" );

	if ( szGuildIntro > 256 )
		throw InvalidProtocolException( "too long guild intro length" );

	oStream.write( szGuildName );
	oStream.write( m_GuildName );
	oStream.write( szGuildMaster );
	oStream.write( m_GuildMaster );
	oStream.write( szGuildIntro );

	if ( szGuildIntro != 0 )
		oStream.write( m_GuildIntro );

	oStream.write( m_GuildState );
	oStream.write( m_GuildRace );
	oStream.write( m_ServerGroupID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GSAddGuild::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GSAddGuildHandler::execute(this, pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GSAddGuild::toString () const
    throw ()
{
	StringStream msg;

	msg << "GSAddGuild ("
		<< "GuildName:" << m_GuildName
		<< "GuildMaster:" << m_GuildMaster
		<< "GuildIntro:" << m_GuildIntro
		<< "GuildState:" << (int)m_GuildState
		<< "GuildRace:" << (int)m_GuildRace
		<< "ServerGroupID:" << (int)m_ServerGroupID
		<< " )";

	return msg.toString();
}

