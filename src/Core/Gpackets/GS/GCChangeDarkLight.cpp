//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeDarkLight.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GCChangeDarkLight.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void GCChangeDarkLight::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_DarkLevel );
	iStream.read( m_LightLevel );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCChangeDarkLight::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_DarkLevel );
	oStream.write( m_LightLevel );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCChangeDarkLight::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCChangeDarkLightHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCChangeDarkLight::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCChangeDarkLight("
		<< "DarkLevel:" << (int)m_DarkLevel
		<< ",LightLevel:" << (int)m_LightLevel 
		<< ")";
	return msg.toString();

	__END_CATCH
}
