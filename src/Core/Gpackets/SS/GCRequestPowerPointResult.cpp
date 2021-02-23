//-------------------------------------------------------------------------------- // 
// Filename    : GCRequestPowerPointResult.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GCRequestPowerPointResult.h"


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCRequestPowerPointResult::GCRequestPowerPointResult ()
	throw ()
	: m_ErrorCode(0), m_SumPowerPoint(0), m_RequestPowerPoint(0)
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCRequestPowerPointResult::~GCRequestPowerPointResult ()
	throw ()
{
}

//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void GCRequestPowerPointResult::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	// Error code
	iStream.read( m_ErrorCode );

	// 현재 누적된 파워짱 포인트
	iStream.read( m_SumPowerPoint );

	// 요청으로 가져온 파워짱 포인트
	iStream.read( m_RequestPowerPoint );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCRequestPowerPointResult::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	// Error code
	oStream.write( m_ErrorCode );

	// 현재 누적된 파워짱 포인트
	oStream.write( m_SumPowerPoint );

	// 요청으로 가져온 파워짱 포인트
	oStream.write( m_RequestPowerPoint );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCRequestPowerPointResult::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCRequestPowerPointResultHandler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCRequestPowerPointResult::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCRequestPowerPointResult("
		<< "ErrorCode:" << (int)m_ErrorCode
		<< ",SumPowerPoint:" << m_SumPowerPoint
		<< ",RequestPowerPoint:" << m_RequestPowerPoint
		<< ")";

	return msg.toString();

	__END_CATCH
}

