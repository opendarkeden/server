//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCModifyGuildMemberInfo.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCModifyGuildMemberInfo.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName;
	
	iStream.read( m_GuildID );

	//if ( szGuildName == 0 )
	//	throw InvalidProtocolException("szGuildName == 0");

	if ( szGuildName > 30 )
		throw InvalidProtocolException("too long GuildName length");

	if ( szGuildName!=0 )
		iStream.read( szGuildName );

	iStream.read( m_GuildName, szGuildName );
	iStream.read( m_GuildMemberRank );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName = m_GuildName.size();

	//if ( szGuildName == 0 )
	//	throw InvalidProtocolException("szGuildName == 0");

	if ( szGuildName > 256 )
		throw InvalidProtocolException("too long GuildName length");

	oStream.write( m_GuildID );
	oStream.write( szGuildName );

	if ( szGuildName != 0 )
		oStream.write( m_GuildName );

	oStream.write( m_GuildMemberRank );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCModifyGuildMemberInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCModifyGuildMemberInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCModifyGuildMemberInfo("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildName:" << m_GuildName
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}


