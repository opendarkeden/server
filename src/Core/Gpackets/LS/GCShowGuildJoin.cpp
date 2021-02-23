//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildJoin.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShowGuildJoin.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCShowGuildJoin::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName;

	iStream.read( m_GuildID );
	iStream.read( szGuildName );

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 );
		throw InvalidProtocolException( "too long szGuildName length" );

	iStream.read( m_GuildName, szGuildName );
	iStream.read( m_GuildMemberRank );
	iStream.read( m_JoinFee );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCShowGuildJoin::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName = m_GuildName.size();

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long szGuildName length" );

	oStream.write( m_GuildID );
	oStream.write( szGuildName );
	oStream.write( m_GuildName );
	oStream.write( m_GuildMemberRank );
	oStream.write( m_JoinFee );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCShowGuildJoin::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShowGuildJoinHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCShowGuildJoin::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShowGuildJoin("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildName:" << m_GuildName
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< "JoinFee:" << (int)m_JoinFee
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

