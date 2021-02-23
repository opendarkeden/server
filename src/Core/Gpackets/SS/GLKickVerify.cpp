//////////////////////////////////////////////////////////////////////
// 
// Filename    : GLKickVerify.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GLKickVerify.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GLKickVerify::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE bKicked;
	iDatagram.read( bKicked );
	m_bKicked = bKicked;

	iDatagram.read( m_ID );

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


	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GLKickVerify::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE bKicked = (bool)m_bKicked;
	oDatagram.write( bKicked );

	oDatagram.write( m_ID );

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

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GLKickVerify::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GLKickVerifyHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GLKickVerify::toString () const
    throw ()
{
	StringStream msg;

	msg << "GLKickVerify("
		<< "bKicked:" << (int)m_bKicked
		<< ",ID:" << (int)m_ID
		<< ",Name:" << m_PCName
		<< ")";

	return msg.toString();
}

