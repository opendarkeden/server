//////////////////////////////////////////////////////////////////////
// 
// Filename    : GSExpelGuildMember.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GSExpelGuildMember.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GSExpelGuildMember::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szName, szSender;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	iStream.read( m_Name, szName );
	iStream.read( szSender );

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender == 0" );
	if ( szSender > 20 )
		throw InvalidProtocolException( "too long name length" );

	iStream.read( m_Sender, szSender );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GSExpelGuildMember::write ( SocketOutputStream& oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();
	BYTE szSender = m_Sender.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender= 0" );
	if ( szSender > 20 )
		throw InvalidProtocolException( "too long szSender length" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( szSender );
	oStream.write( m_Sender );


	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GSExpelGuildMember::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GSExpelGuildMemberHandler::execute(this, pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GSExpelGuildMember::toString () const
    throw ()
{
	StringStream msg;

	msg << "GSExpelGuildMember ("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< "Sender:" << m_Sender
		<< " )";

	return msg.toString();
}

