//--------------------------------------------------------------------------------
// 
// Filename    : CURequestLoginMode.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CURequestLoginMode.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CURequestLoginMode::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// 소켓으로부터 직접 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CURequestLoginMode::read ( Socket * pSocket ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void CURequestLoginMode::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CURequestLoginMode::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CURequestLoginModeHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CURequestLoginMode::toString () const
	throw ()
{

	return "CUReqeustLoginMode()";
}
