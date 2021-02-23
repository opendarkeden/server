//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildInfo2.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GuildInfo2.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GuildInfo2::GuildInfo2 () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GuildInfo2::~GuildInfo2 () 
    throw ()
{
	__BEGIN_TRY
	
	clearGuildMemberInfoList();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// clear guild member info list
//////////////////////////////////////////////////////////////////////
void GuildInfo2::clearGuildMemberInfoList()
	    throw()
{
	__BEGIN_TRY

	// GuildInfoList를 삭제한다.
	while( !m_GuildMemberInfoList.empty() )
	{
		GuildMemberInfo2* pGuildMemberInfo = m_GuildMemberInfoList.front();
		m_GuildMemberInfoList.pop_front();
		SAFE_DELETE( pGuildMemberInfo );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GuildInfo2::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName, szMaster, szDate, szIntro;

	iStream.read( m_ID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szName > 30 )
		throw InvalidProtocolException( "too long szGuildName size" );

	iStream.read( m_Name, szName );
	iStream.read( m_Type );
	iStream.read( m_Race );
	iStream.read( m_State );
	iStream.read( m_ServerGroupID );
	iStream.read( m_ZoneID );
	iStream.read( szMaster );

	if ( szMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szMaster > 20 )
		throw InvalidProtocolException( "too long szGuildMaster size" );

	iStream.read( m_Master, szMaster );
	iStream.read( szDate );

	if ( szDate > 11 )
		throw InvalidProtocolException( "too long szGuildExpireDate size" );

	if ( szDate != 0 )
		iStream.read( m_Date, szDate );
	else
		m_Date = "";

	iStream.read( szIntro );

	if ( szIntro > 256 )
		throw InvalidProtocolException( "too long szIntro length" );

	if ( szIntro != 0 )
		iStream.read( m_Intro, szIntro );
	else
		m_Intro = "";

	WORD szGuildMemberInfo;
	iStream.read( szGuildMemberInfo );
	for ( int i = 0; i < szGuildMemberInfo; i++ )
	{
		GuildMemberInfo2* pGuildMemberInfo = new GuildMemberInfo2();
		pGuildMemberInfo->read( iStream );
		m_GuildMemberInfoList.push_front( pGuildMemberInfo );
	}


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GuildInfo2::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	BYTE szMaster = m_Master.size();
	BYTE szDate = m_Date.size();
	BYTE szIntro = m_Intro.size();
	
	if ( szName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szName > 30 )
		throw InvalidProtocolException( "too long szGuildName size" );

	if ( szMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szMaster > 20 )
		throw InvalidProtocolException( "too long szGuildMaster size" );

	if ( szDate > 11 )
		throw InvalidProtocolException( "too long szGuildExpireDate size" );

	if ( szIntro > 256 )
		throw InvalidProtocolException( "too long szIntro length" );

	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_Type );
	oStream.write( m_Race );
	oStream.write( m_State );
	oStream.write( m_ServerGroupID );
	oStream.write( m_ZoneID );
	oStream.write( szMaster );
	oStream.write( m_Master );

	oStream.write( szDate );
	if ( szDate != 0 )
		oStream.write( m_Date );

	oStream.write( szIntro );
	if ( szIntro != 0 )
		oStream.write( m_Intro );


	WORD szGuildMemberInfo = m_GuildMemberInfoList.size();
	oStream.write( szGuildMemberInfo );
	GuildMemberInfoListConstItor2 itr = m_GuildMemberInfoList.begin();
	for ( ; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		(*itr)->write( oStream );
	}


	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GuildInfo2::getSize()
	throw()
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();
	BYTE szMaster = m_Master.size();
	BYTE szDate = m_Date.size();
	BYTE szIntro = m_Intro.size();

	PacketSize_t PacketSize = szGuildID
							+ szBYTE + szName
							+ szGuildType
							+ szGuildRace
							+ szGuildState
							+ szServerGroupID
							+ szZoneID
							+ szBYTE + szMaster
							+ szBYTE + szDate
							+ szBYTE + szIntro;

	PacketSize += szWORD;

	GuildMemberInfoListConstItor2 itr = m_GuildMemberInfoList.begin();
	for ( ; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GuildInfo2::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GuildInfo2( "
		<< "GuildID:" << m_ID
		<< "GuildName:" << m_Name
		<< "GuildType:" << (int)m_Type
		<< "GuildRace:" << (int)m_Race
		<< "GuildState:" << (int)m_State
		<< "ServerGroupID:" << (int)m_ServerGroupID
		<< "ZoneID:" << (int)m_ZoneID
		<< "GuildMaster:" << m_Master
		<< "GuildDate:" << m_Date
		<< "GuildIntro:" << m_Intro
		<< ")";

	return msg.toString();

	__END_CATCH
}

