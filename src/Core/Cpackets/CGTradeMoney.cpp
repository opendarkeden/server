//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeMoney.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeMoney.h"

void CGTradeMoney::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_TargetObjectID);
	iStream.read(m_Gold);
	iStream.read(m_Code);

	__END_CATCH
}

void CGTradeMoney::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_TargetObjectID);
	oStream.write(m_Gold);
	oStream.write(m_Code);

	__END_CATCH
}

void CGTradeMoney::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGTradeMoneyHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTradeMoney::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGTradeMoney(" 
		<< "TargetObjectID:" << (int)m_TargetObjectID
		<< ",Gold:"          << (int)m_Gold
		<< ",CODE:"          << (int)m_Code
		<< ")";
	return msg.toString();

	__END_CATCH
}
