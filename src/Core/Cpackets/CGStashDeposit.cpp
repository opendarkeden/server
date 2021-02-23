//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashDeposit.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashDeposit.h"

void CGStashDeposit::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_Amount);

	__END_CATCH
}
		    
void CGStashDeposit::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_Amount);

	__END_CATCH
}

void CGStashDeposit::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGStashDepositHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGStashDeposit::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGStashDeposit("
		<< "Amount : " << (int)m_Amount
		<< ")";
	return msg.toString();

	__END_CATCH
}
