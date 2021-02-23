//////////////////////////////////////////////////////////////////////
// 
// Filename    : GGCommand.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GGCommand.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GGCommand::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read command
	//--------------------------------------------------
	BYTE szCommand;

	iDatagram.read( szCommand );

	if ( szCommand == 0 )
		throw InvalidProtocolException("szCommand == 0");

	if ( szCommand > 80 )
		throw InvalidProtocolException("too long Command length");

	iDatagram.read( m_Command , szCommand );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GGCommand::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write client IP
	//--------------------------------------------------
	BYTE szCommand = m_Command.size();

	if ( szCommand == 0 )
		throw InvalidProtocolException("szCommand == 0");

	if ( szCommand > 80 )
		throw InvalidProtocolException("too long Command length");

	oDatagram.write( szCommand );

	oDatagram.write( m_Command );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GGCommand::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GGCommandHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GGCommand::toString () const
    throw ()
{
	StringStream msg;

	msg << "GGCommand("
		<< m_Command 
		<< ")";

	return msg.toString();
}

