//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradePrepare.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradePrepare.h"

void CGTradePrepare::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_TargetObjectID);
	iStream.read(m_Code);

	__END_CATCH
}

void CGTradePrepare::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_TargetObjectID);
	oStream.write(m_Code);

	__END_CATCH
}

void CGTradePrepare::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGTradePrepareHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTradePrepare::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGTradePrepare(" 
		<< "TargetObjectID:" << (int)m_TargetObjectID
		<< ",CODE:"          << (int)m_Code 
		<< ")";
	return msg.toString();

	__END_CATCH
}
