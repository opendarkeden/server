//////////////////////////////////////////////////////////////////////////////
// Filename    : ConnectionInfo.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ConnectionInfo.h"
#include "StringStream.h"

ConnectionInfo::ConnectionInfo() 
	
{ 
	__BEGIN_TRY

	m_Key                = 0;
	m_ExpireTime.tv_sec  = 0; 
	m_ExpireTime.tv_usec = 0; 

	__END_CATCH
}

ConnectionInfo::~ConnectionInfo() 
	 
{
	__BEGIN_TRY
	__END_CATCH
}

string ConnectionInfo::toString() const 
	 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ConnectionInfo(ClientIP:" << m_ClientIP 
		<< ",PlayerID:" << m_PlayerID
		<< ",PCName:" << m_PCName
		<< ",ExpireTime:" << m_ExpireTime.tv_sec << "." << m_ExpireTime.tv_usec 
		<< ",KEY: " << m_Key << ")";
	return msg.toString();

	__END_CATCH
}


