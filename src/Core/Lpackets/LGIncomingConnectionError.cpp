//////////////////////////////////////////////////////////////////////
// 
// Filename    : LGIncomingConnectionError.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LGIncomingConnectionError.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void LGIncomingConnectionError::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	//--------------------------------------------------
	BYTE szMessage;

	iDatagram.read( szMessage );

	if ( szMessage == 0 ) 
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage >= 128 )
		throw InvalidProtocolException("too large message length");

	iDatagram.read( m_Message , szMessage );


	//--------------------------------------------------
	//--------------------------------------------------
	BYTE szPlayerID;

	iDatagram.read( szPlayerID );

	if ( szPlayerID == 0 ) 
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID >= 128 )
		throw InvalidProtocolException("too large playerID length");

	iDatagram.read( m_PlayerID , szPlayerID );


	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void LGIncomingConnectionError::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//--------------------------------------------------
	//--------------------------------------------------
	BYTE szMessage = m_Message.size();

	if ( szMessage == 0 ) 
		throw InvalidProtocolException("szMessage == 0");

	if ( szMessage >= 128 )
		throw InvalidProtocolException("too large message length");

	oDatagram.write( szMessage );

	oDatagram.write( m_Message );


	//--------------------------------------------------
	//--------------------------------------------------
	BYTE szPlayerID = m_PlayerID.size();

	if ( szPlayerID == 0 ) 
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID >= 128 )
		throw InvalidProtocolException("too large playerID length");

	oDatagram.write( szPlayerID );

	oDatagram.write( m_PlayerID );

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LGIncomingConnectionError::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	cout << "LGIncomingConnectionError::execute() called." << endl;

	LGIncomingConnectionErrorHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string LGIncomingConnectionError::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "LGIncomingConnectionError("
		<< "Message:" << m_Message 
		<< "PlayerID:" << m_PlayerID
		<< ")";
	return msg.toString();

	__END_CATCH
}

