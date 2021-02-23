//////////////////////////////////////////////////////////////////////////////
// Filename    : CGCrashReport.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGCrashReport.h"
#include "Assert.h"

CGCrashReport::CGCrashReport () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGCrashReport::~CGCrashReport () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGCrashReport::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read( m_ExecutableTime, 19 );
	iStream.read( m_Version );
	iStream.read( m_Address, 10 );
	
	WORD szSTR;

	iStream.read( szSTR );
	if ( szSTR > 100 ) throw DisconnectException("too large string size : CGCrashReport::m_OS");
	iStream.read( m_OS, szSTR );

	iStream.read( szSTR );
	if ( szSTR > 1024 ) throw DisconnectException("too large string size : CGCrashReport::m_CallStack");
	iStream.read( m_CallStack, szSTR );

	iStream.read( szSTR );
	if ( szSTR > 1024 ) throw DisconnectException("too large string size : CGCrashReport::m_Message");
	iStream.read( m_Message, szSTR );
		
	__END_CATCH
}

void CGCrashReport::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	Assert( m_ExecutableTime.size() == 19 );
	Assert( m_Address.size() == 10 );

	oStream.write( m_ExecutableTime );
	oStream.write( m_Version );
	oStream.write( m_Address );

	WORD szSTR = m_OS.size();
	oStream.write( szSTR );
	Assert( szSTR <= 100 );
	oStream.write( m_OS );

	szSTR = m_CallStack.size();
	oStream.write( szSTR );
	Assert( szSTR <= 1024 );
	oStream.write( m_CallStack );

	szSTR = m_Message.size();
	oStream.write( szSTR );
	Assert( szSTR <= 1024 );
	oStream.write( m_Message );

	__END_CATCH
}

void CGCrashReport::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGCrashReportHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGCrashReport::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGCrashReport("
		<< m_ExecutableTime << ", "
		<< m_Version << ", "
		<< m_Address << ", "
		<< m_OS << ", "
		<< m_CallStack << ", "
		<< m_Message
		<< ")";
	return msg.toString();

	__END_CATCH
}
