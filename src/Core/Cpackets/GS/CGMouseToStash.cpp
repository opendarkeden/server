//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMouseToStash.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGMouseToStash.h"

void CGMouseToStash::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_Rack);
	iStream.read(m_Index);

	__END_CATCH
}

void CGMouseToStash::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_Rack);
	oStream.write(m_Index);

	__END_CATCH
}

void CGMouseToStash::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGMouseToStashHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGMouseToStash::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGMouseToStash("
		<< " ObjectID : " << (int)m_ObjectID 
		<< " Rack : "     << (int)m_Rack
		<< " Index : "    << (int)m_Index
		<< ")";
	return msg.toString();

	__END_CATCH
}
