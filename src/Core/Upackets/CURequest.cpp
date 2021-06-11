//--------------------------------------------------------------------------------
// 
// Filename    : CURequest.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CURequest.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CURequest::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_Resource.read( iStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// 소켓으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CURequest::read ( Socket * pSocket ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_Resource.read( pSocket );

	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void CURequest::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_Resource.write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CURequest::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CURequestHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CURequest::toString () const
	throw ()
{
	StringStream msg;

	msg << "CURequest("
		<< m_Resource.toString()
		<< ")";

	return msg.toString();
}
