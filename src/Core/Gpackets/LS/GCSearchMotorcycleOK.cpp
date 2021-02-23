//--------------------------------------------------------------------------------
// 
// Filename    : GCSearchMotorcycleOK.cpp 
// Written By  : 김성민
// Description : 플레이어에게 서버 측의 상점 버전을 알려줄 때 쓰이는 패킷이다.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCSearchMotorcycleOK.h"
#include "Assert.h"

//--------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------
void GCSearchMotorcycleOK::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_ZoneID );
	iStream.read( m_ZoneX );
	iStream.read( m_ZoneY );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCSearchMotorcycleOK::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ZoneID );
	oStream.write( m_ZoneX );
	oStream.write( m_ZoneY );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCSearchMotorcycleOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSearchMotorcycleOKHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCSearchMotorcycleOK::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCSearchMotorcycleOK(" 
		<< "ZoneID:" << (int)m_ZoneID
		<< ",ZoneX:" << (int)m_ZoneX
		<< ",ZoneY:" << (int)m_ZoneY
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


