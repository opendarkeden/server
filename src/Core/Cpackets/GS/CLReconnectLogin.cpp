//////////////////////////////////////////////////////////////////////////////
// Filename    : CLReconnectLogin.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLReconnectLogin.h"

void CLReconnectLogin::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// read authentication key
	iStream.read(m_Key);
	iStream.read( m_LoginMode );

	__END_CATCH
}
		    
void CLReconnectLogin::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// write authentication key
	oStream.write(m_Key);
	oStream.write( m_LoginMode );

	__END_CATCH
}

void CLReconnectLogin::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CLReconnectLoginHandler::execute(this , pPlayer);

	__END_CATCH
}

string CLReconnectLogin::toString () const
       throw ()
{
	StringStream msg;
	msg << "CLReconnectLogin("
		<< "KEY:" << m_Key 
		<< "LoginMode:" << m_LoginMode
		<< ")" ;
	return msg.toString();
}
