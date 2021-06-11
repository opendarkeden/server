//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestRepair.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestRepair.h"

void CGRequestRepair::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);

	__END_CATCH
}

void CGRequestRepair::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGRequestRepair::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGRequestRepairHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGRequestRepair::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGRequestRepair("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
