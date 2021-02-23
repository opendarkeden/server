//--------------------------------------------------------------------------------
// 
// Filename    : CUBeginUpdate.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CUBeginUpdate.h"
#include "Properties.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CUBeginUpdate::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	static WORD GuildVersion = atoi( g_pConfig->getProperty("GuildVersion").c_str() );
	static WORD KeyVersion = atoi( g_pConfig->getProperty("KeyVersion").c_str() );
	static WORD InfoVersion = atoi( g_pConfig->getProperty("InfoVersion").c_str() );

	iStream.read( m_Version );

	if ( m_Version >= GuildVersion )
	{
		iStream.read( m_GuildVersion );
		m_Type = TWO_VERSION_KEY_FRONT;
	}
	else if ( m_Version >= KeyVersion )
	{
		m_Type = ONE_VERSION_KEY_BACK;
	}
	else m_Type = OLD_UPDATE;

	if ( m_Version >= InfoVersion )
	{
		iStream.read( m_InfoVersion );
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// 소켓으로부터 직접 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CUBeginUpdate::read ( Socket * pSocket ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	static WORD GuildVersion = atoi( g_pConfig->getProperty("GuildVersion").c_str() );
	static WORD KeyVersion = atoi( g_pConfig->getProperty("KeyVersion").c_str() );
	static WORD InfoVersion = atoi( g_pConfig->getProperty("InfoVersion").c_str() );

	pSocket->receive( &m_Version , szWORD );

	if ( m_Version >= GuildVersion )
	{
		pSocket->receive( &m_GuildVersion, szWORD );
		m_Type = TWO_VERSION_KEY_FRONT;
	}
	else if ( m_Version >= KeyVersion )
	{
		m_Type = ONE_VERSION_KEY_BACK;
	}
	else m_Type = OLD_UPDATE;

	if ( m_Version >= InfoVersion )
	{
		pSocket->receive( &m_InfoVersion, szWORD );
	}

	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void CUBeginUpdate::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_Version );
	if ( m_Version >= atoi( g_pConfig->getProperty("GuildVersion").c_str() ) ) oStream.write( m_GuildVersion );
	if ( m_Version >= atoi( g_pConfig->getProperty("InfoVersion").c_str() ) ) oStream.write( m_InfoVersion );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CUBeginUpdate::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CUBeginUpdateHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CUBeginUpdate::toString () const
	throw ()
{
	StringStream msg;

	msg << "CUBeginUpdate("
		<< "Version:" << m_Version
		<< "GuildVersion:" << m_GuildVersion
		<< "InfoVersion:" << m_InfoVersion
		<< ")";

	return msg.toString();
}
