//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildMemberInfo.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GuildMemberInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GuildMemberInfo::GuildMemberInfo () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GuildMemberInfo::~GuildMemberInfo () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GuildMemberInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName size" );

	iStream.read( m_Name, szName );
	iStream.read( m_Rank );
	iStream.read( m_bLogOn );
	iStream.read( m_ServerID );
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GuildMemberInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	
	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName size" );

	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_Rank );
	oStream.write( m_bLogOn );
	oStream.write( m_ServerID );

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GuildMemberInfo::getSize()
	throw()
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	PacketSize_t PacketSize = szBYTE + szName + szGuildMemberRank + szbool + szServerID;

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GuildMemberInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GuildMemberInfo( "
		<< "Name:" << m_Name
		<< "GuildMemberRank:" << m_Rank
		<< "CurrentServerID :" << m_ServerID
		<< ")";

	return msg.toString();

	__END_CATCH
}

