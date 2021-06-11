//--------------------------------------------------------------------------------
// 
// Filename    : CUEndUpdate.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CUEndUpdate.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CUEndUpdate::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// 소켓으로부터 직접 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void CUEndUpdate::read ( Socket * pSocket ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void CUEndUpdate::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CUEndUpdate::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CUEndUpdateHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CUEndUpdate::toString () const
	throw ()
{
	StringStream msg;

	msg << "CUEndUpdate("
		<< ")";

	return msg.toString();
}
