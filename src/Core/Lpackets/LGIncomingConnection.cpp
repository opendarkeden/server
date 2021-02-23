//////////////////////////////////////////////////////////////////////
// 
// Filename    : LGIncomingConnection.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LGIncomingConnection.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void LGIncomingConnection::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read player id 
	//--------------------------------------------------
	BYTE szPlayerID;

	iDatagram.read( szPlayerID );

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too long name length");

	iDatagram.read( m_PlayerID , szPlayerID );

	//--------------------------------------------------
	// read creature's name
	//--------------------------------------------------
	BYTE szPCName;

	iDatagram.read( szPCName );

	if ( szPCName == 0 )
		throw InvalidProtocolException("szPCName == 0");

	if ( szPCName > 20 )
		throw InvalidProtocolException("too long name length");

	iDatagram.read( m_PCName , szPCName );

	//--------------------------------------------------
	// read client IP
	//--------------------------------------------------
	BYTE szClientIP;

	iDatagram.read( szClientIP );

	if ( szClientIP == 0 )
		throw InvalidProtocolException("szClientIP == 0");

	if ( szClientIP > 15 )
		throw InvalidProtocolException("too long IP length");

	iDatagram.read( m_ClientIP , szClientIP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void LGIncomingConnection::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write player id
	//--------------------------------------------------
	BYTE szPlayerID = m_PlayerID.size();

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too long name length");

	oDatagram.write( szPlayerID );

	oDatagram.write( m_PlayerID );

	//--------------------------------------------------
	// write PC name
	//--------------------------------------------------
	BYTE szPCName = m_PCName.size();

	if ( szPCName == 0 )
		throw InvalidProtocolException("szPCName == 0");

	if ( szPCName > 20 )
		throw InvalidProtocolException("too long name length");

	oDatagram.write( szPCName );

	oDatagram.write( m_PCName );

	//--------------------------------------------------
	// write client IP
	//--------------------------------------------------
	BYTE szClientIP = m_ClientIP.size();

	if ( szClientIP == 0 )
		throw InvalidProtocolException("szClientIP == 0");

	if ( szClientIP > 15 )
		throw InvalidProtocolException("too long IP length");

	oDatagram.write( szClientIP );

	oDatagram.write( m_ClientIP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LGIncomingConnection::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LGIncomingConnectionHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string LGIncomingConnection::toString () const
    throw ()
{
	StringStream msg;

	msg << "LGIncomingConnection("
		<< "PlayerID:" << m_PlayerID
		<< ",PCName:" << m_PCName 
		<< ",ClientIP:" << m_ClientIP 
		<< ")";

	return msg.toString();
}

