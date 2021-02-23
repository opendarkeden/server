//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowWaitGuildInfo.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShowWaitGuildInfo.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCShowWaitGuildInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName, szGuildMaster, szGuildIntro, MemberNum, szMember;
	string Member;

	iStream.read( m_GuildID );
	iStream.read( szGuildName );

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long szGuildName length" );

	iStream.read( m_GuildName, szGuildName );
	iStream.read( m_GuildState );
	iStream.read( szGuildMaster );

	if ( szGuildMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szGuildMaster > 20 )
		throw InvalidProtocolException( "too long szGuildMaster length" );

	iStream.read( m_GuildMaster, szGuildMaster );
	iStream.read( m_GuildMemberCount );
	iStream.read( szGuildIntro );

	if ( szGuildIntro > 256 )
		throw InvalidProtocolException( "too long szGuildIntro length" );

	if ( szGuildIntro != 0 )
		iStream.read( m_GuildIntro, szGuildIntro );
	else
		m_GuildIntro = "";

	iStream.read( m_JoinFee );
	iStream.read( MemberNum );

	for ( int i = 0; i < MemberNum; i++ )
	{
		iStream.read( szMember );

		if ( szMember == 0 )
			throw InvalidProtocolException( "szMember == 0" );
		if ( szMember > 20 )
			throw InvalidProtocolException( "too long szMember length" );

		iStream.read( Member, szMember );
		
		m_MemberList.push_front( Member );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCShowWaitGuildInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName = m_GuildName.size();
	BYTE szGuildMaster = m_GuildMaster.size();
	BYTE szGuildIntro = m_GuildIntro.size();
	BYTE MemberNum = m_MemberList.size();
	BYTE szMember;

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long szGuildName length" );

	if ( szGuildMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szGuildMaster > 20 )
		throw InvalidProtocolException( "too long szGuildMaster length" );

	if ( szGuildIntro > 256 )
		throw InvalidProtocolException( "too long szGuildIntro length" );

	oStream.write( m_GuildID );
	oStream.write( szGuildName );
	oStream.write( m_GuildName );
	oStream.write( m_GuildState );
	oStream.write( szGuildMaster );
	oStream.write( m_GuildMaster );
	oStream.write( m_GuildMemberCount );
	oStream.write( szGuildIntro );

	if ( szGuildIntro != 0 )
		oStream.write( m_GuildIntro );

	oStream.write( m_JoinFee );
	oStream.write( MemberNum );

	slist<string>::const_iterator itr = m_MemberList.begin();
	for ( ; itr != m_MemberList.end(); itr++ )
	{
		szMember = (*itr).size();

		if ( szMember == 0 )
			throw InvalidProtocolException( "szMember == 0" );
		if ( szMember > 20 )
			throw InvalidProtocolException( "too long szMember length" );

		oStream.write( szMember );
		oStream.write( (*itr) );
	}

	__END_CATCH
}


// get packet's body size
PacketSize_t GCShowWaitGuildInfo::getPacketSize() const throw()
{
	PacketSize_t PacketSize = szGuildID +
							  szBYTE +
							  m_GuildName.size() +
							  szGuildState +
							  szBYTE +
							  m_GuildMaster.size() +
							  szBYTE +
							  szBYTE +
							  m_GuildIntro.size() +
							  szGold +
							  szBYTE;

	slist<string>::const_iterator itr = m_MemberList.begin();
	for ( ; itr != m_MemberList.end() ; itr++ )
	{
		PacketSize += szBYTE + (*itr).size();
	}

	return PacketSize;
}



//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCShowWaitGuildInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShowWaitGuildInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCShowWaitGuildInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShowWaitGuildInfo("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildName:" << m_GuildName
		<< "GuildState:" << (int)m_GuildState
		<< "GuildMaster:" << m_GuildMaster
		<< "GuildMemberCount:" << (int)m_GuildMemberCount
		<< "GuildIntro:" << m_GuildIntro
		<< "JoinFee:" << (int)m_JoinFee
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

