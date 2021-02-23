//////////////////////////////////////////////////////////////////////
// 
// Filename    : ScriptParameter.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ScriptParameter.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ScriptParameter::ScriptParameter()
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ScriptParameter::~ScriptParameter() 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void ScriptParameter::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szName, szValue;

	iStream.read( szName );
	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );

	iStream.read( m_Name, szName );

	iStream.read( szValue );
	if ( szValue == 0 )
		throw InvalidProtocolException( "szValue == 0" );

	iStream.read( m_Value, szValue );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void ScriptParameter::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	BYTE szValue = m_Value.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szValue == 0 )
		throw InvalidProtocolException( "szValue == 0" );

	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( szValue );
	oStream.write( m_Value );

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t ScriptParameter::getSize()
	throw()
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();
	BYTE szValue = m_Value.size();

	PacketSize_t PacketSize = szBYTE + szName + szBYTE + szValue;

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ScriptParameter::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ScriptParameter( "
		<< "Name:" << m_Name
		<< ",Value:" << m_Value
		<< ")";

	return msg.toString();

	__END_CATCH
}

