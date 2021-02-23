//////////////////////////////////////////////////////////////////////
// 
// Filename    : SGModifyGuildIntroOK.cpp 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SGModifyGuildIntroOK.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void SGModifyGuildIntroOK::read ( SocketInputStream& iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szGuildIntro;

	iStream.read( m_GuildID );
	iStream.read( szGuildIntro );

	if ( szGuildIntro > 255 )
		throw InvalidProtocolException( "too long szGuildIntro length" );

	if ( szGuildIntro > 0 )
		iStream.read( m_GuildIntro, szGuildIntro );
	else
		m_GuildIntro = "";

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void SGModifyGuildIntroOK::write ( SocketOutputStream& oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szGuildIntro = m_GuildIntro.size();

	if ( szGuildIntro > 255 )
		throw InvalidProtocolException( "too long szGuildIntro length" );

	oStream.write( m_GuildID );
	oStream.write( szGuildIntro );

	if ( szGuildIntro > 0 )
		oStream.write( m_GuildIntro );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void SGModifyGuildIntroOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	SGModifyGuildIntroOKHandler::execute(this);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string SGModifyGuildIntroOK::toString () const
    throw ()
{
	StringStream msg;

	msg << "SGModifyGuildIntroOK("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildIntro:" << m_GuildIntro
		<< ")";

	return msg.toString();
}

