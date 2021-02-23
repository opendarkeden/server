//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeWeather.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GCChangeWeather.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void GCChangeWeather::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE weather;
	iStream.read( weather );
	m_Weather = (Weather)weather;

	iStream.read( m_WeatherLevel );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCChangeWeather::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( (BYTE)m_Weather );
	oStream.write( m_WeatherLevel );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCChangeWeather::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCChangeWeatherHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCChangeWeather::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCChangeWeather("
		<< "Weather:" << Weather2String[m_Weather]
		<< ",WeatherLevel:" << (int)m_WeatherLevel 
		<< ")";
	return msg.toString();

	__END_CATCH
}
