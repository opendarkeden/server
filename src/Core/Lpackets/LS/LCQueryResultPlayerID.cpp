//--------------------------------------------------------------------------------
// 
// Filename    : LCQueryResultPlayerID.cpp 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "LCQueryResultPlayerID.h"


//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void LCQueryResultPlayerID::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read player id
	//--------------------------------------------------
	BYTE szPlayerID;

	iStream.read( szPlayerID );

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too large PlayerID length");

	iStream.read( m_PlayerID , szPlayerID );

	//--------------------------------------------------
	// read id existence
	//--------------------------------------------------
	iStream.read( m_bExist );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void LCQueryResultPlayerID::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write player id
	//--------------------------------------------------
	BYTE szPlayerID = m_PlayerID.size();

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("empty PlayerID");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too large PlayerID length");

	oStream.write( szPlayerID );

	oStream.write( m_PlayerID );

	//--------------------------------------------------
	// write id existence
	//--------------------------------------------------
	oStream.write( m_bExist );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void LCQueryResultPlayerID::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCQueryResultPlayerIDHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string LCQueryResultPlayerID::toString () const
	throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "LCQueryResultPlayerID("
		<< "PlayerID:" << m_PlayerID 
		<< ",Exist:" << m_bExist 
		<< ")";
	return msg.toString();
		
	__END_CATCH
}

