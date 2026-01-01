//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildInfo.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GuildInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GuildInfo::GuildInfo () 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GuildInfo::~GuildInfo () noexcept = default;


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GuildInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	BYTE szGuildName, szGuildMaster, szGuildExpireDate;

	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_GuildID );
	iStream.read( szGuildName );

	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long szGuildName size" );

	iStream.read( m_GuildName, szGuildName );
	iStream.read( szGuildMaster );

	if ( szGuildMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szGuildMaster > 20 )
		throw InvalidProtocolException( "too long szGuildMaster size" );

	iStream.read( m_GuildMaster, szGuildMaster );
	iStream.read( m_GuildMemberCount );
	iStream.read( szGuildExpireDate );

	if ( szGuildExpireDate > 11 )
		throw InvalidProtocolException( "too long szGuildExpireDate size" );

	if ( szGuildExpireDate != 0 )
		iStream.read( m_GuildExpireDate, szGuildExpireDate );
	else
		m_GuildExpireDate = "";

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GuildInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	BYTE szGuildName = m_GuildName.size();
	BYTE szGuildMaster = m_GuildMaster.size();
	BYTE szGuildExpireDate = m_GuildExpireDate.size();
	
	if ( szGuildName == 0 )
		throw InvalidProtocolException( "szGuildName == 0" );
	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long szGuildName size" );

	if ( szGuildMaster == 0 )
		throw InvalidProtocolException( "szGuildMaster == 0" );
	if ( szGuildMaster > 20 )
		throw InvalidProtocolException( "too long szGuildMaster size" );

	if ( szGuildExpireDate > 11 )
		throw InvalidProtocolException( "too long szGuildExpireDate size" );

	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_GuildID );
	oStream.write( szGuildName );
	oStream.write( m_GuildName );
	oStream.write( szGuildMaster );
	oStream.write( m_GuildMaster );
	oStream.write( m_GuildMemberCount );

	oStream.write( szGuildExpireDate );

	if ( szGuildExpireDate != 0 )
		oStream.write( m_GuildExpireDate );

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GuildInfo::getSize()
{
	__BEGIN_TRY

	BYTE szGuildName = m_GuildName.size();
	BYTE szGuildMaster = m_GuildMaster.size();

	PacketSize_t PacketSize = szGuildID + szBYTE + szGuildName + szBYTE + szGuildMaster + szBYTE;

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GuildInfo::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GuildInfo( "
		<< "GuildID:" << m_GuildID
		<< "GuildName:" << m_GuildName
		<< "GuildMaster:" << m_GuildMaster
		<< "GuildMemberCount:" << m_GuildMemberCount
		<< "GuildExpireDate:" << m_GuildExpireDate
		<< ")";

	return msg.toString();

	__END_CATCH
}

