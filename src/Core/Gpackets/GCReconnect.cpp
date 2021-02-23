//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnect.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCReconnect.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCReconnect::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName;
	
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	iStream.read( m_Name , szName );

	BYTE szServerIP;

	iStream.read( szServerIP );

	if ( szServerIP == 0 )
		throw InvalidProtocolException("szServerIP == 0");

	if ( szServerIP > 15 )
		throw InvalidProtocolException("too long IP length");

	iStream.read( m_ServerIP , szServerIP );

	iStream.read( m_Key );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCReconnect::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	
	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	oStream.write( szName );

	oStream.write( m_Name );

	BYTE szServerIP = m_ServerIP.size();

	if ( szServerIP == 0 )
		throw InvalidProtocolException("szServerIP == 0");

	if ( szServerIP > 15 )
		throw InvalidProtocolException("too long IP length");

	oStream.write( szServerIP );

	oStream.write( m_ServerIP );

	oStream.write( m_Key );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCReconnect::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCReconnectHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCReconnect::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCReconnect("
		<< "Name:" << m_Name 
		<< ",ServerIP:" << m_ServerIP 
		<< ",KEY:" << m_Key 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}


