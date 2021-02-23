//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestRepair.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestRepair.h"

void CGRequestRepair::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);

	__END_CATCH
}

void CGRequestRepair::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGRequestRepair::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGRequestRepairHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGRequestRepair::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGRequestRepair("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
