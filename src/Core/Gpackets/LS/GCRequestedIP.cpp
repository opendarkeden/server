//////////////////////////////////////////////////////////////////////
// Filename    : GCRequestedIP.cpp 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////

#include "GCRequestedIP.h"

//////////////////////////////////////////////////////////////////////
// class GCRequestedIP member methods
//////////////////////////////////////////////////////////////////////

GCRequestedIP::GCRequestedIP () 
     throw ()
{
	__BEGIN_TRY

	m_IP = 0;

	__END_CATCH
}

GCRequestedIP::~GCRequestedIP () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void GCRequestedIP::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE num;
	iStream.read(num);

	if (num==0)
		throw InvalidProtocolException("szName==0");

	iStream.read(m_Name, num);

	iStream.read(m_IP);
	iStream.read(m_Port);

	__END_CATCH
}
		    
void GCRequestedIP::write (SocketOutputStream & oStream) 
     const throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	BYTE num = m_Name.size();
	oStream.write(num);

	if (num==0)
		throw InvalidProtocolException("szName==0");

	oStream.write(m_Name);

	oStream.write(m_IP);
	oStream.write(m_Port);

	__END_CATCH
}

void GCRequestedIP::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCRequestedIPHandler::execute(this , pPlayer);
		
	__END_CATCH
}

string GCRequestedIP::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCRequestedIP("
		<< "Name: "		<< m_Name
		<< "IP: "		<< m_IP
		<< "Port: "		<< m_Port
		<< ")";
	return msg.toString();

	__END_CATCH
}

