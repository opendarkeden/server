//////////////////////////////////////////////////////////////////////////////
// Filename    : CLReconnectLogin.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLReconnectLogin.h"

void CLReconnectLogin::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	// read authentication key
	iStream.read(m_Key);
	iStream.read(m_LoginMode);

	__END_CATCH
}
		    
void CLReconnectLogin::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	// write authentication key
	oStream.write(m_Key);
	oStream.write(m_LoginMode);

	__END_CATCH
}

void CLReconnectLogin::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CLReconnectLoginHandler::execute(this , pPlayer);

	__END_CATCH
}

string CLReconnectLogin::toString () const
       
{
	StringStream msg;
	msg << "CLReconnectLogin("
		<< "KEY:" << m_Key 
		<< "LoginMode:" << m_LoginMode
		<< ")" ;
	return msg.toString();
}
