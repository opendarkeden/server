//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeFinish.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeFinish.h"

void CGTradeFinish::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_TargetObjectID);
	iStream.read(m_Code);

	__END_CATCH
}

void CGTradeFinish::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_TargetObjectID);
	oStream.write(m_Code);

	__END_CATCH
}

void CGTradeFinish::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGTradeFinishHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTradeFinish::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGTradeFinish(" 
		<< "TargetObjectID:" << (int)m_TargetObjectID
		<< ",CODE:" << (int)m_Code
		<< ")";
	return msg.toString();

	__END_CATCH
}
