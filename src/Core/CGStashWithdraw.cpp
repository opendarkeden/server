//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashWithdraw.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashWithdraw.h"

void CGStashWithdraw::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Amount);

	__END_CATCH
}

void CGStashWithdraw::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Amount);

	__END_CATCH
}

void CGStashWithdraw::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGStashWithdrawHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGStashWithdraw::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGStashWithdraw("
		<< "Amount : " << (int)m_Amount
		<< ")";
	return msg.toString();

	__END_CATCH
}
