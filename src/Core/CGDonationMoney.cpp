//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDonationMoney.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDonationMoney.h"

void CGDonationMoney::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_Gold);
	iStream.read(m_DonationType);

	__END_CATCH
}

void CGDonationMoney::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Gold);
	oStream.write(m_DonationType);

	__END_CATCH
}

void CGDonationMoney::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGDonationMoneyHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGDonationMoney::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGDonationMoney(Gold:" << (int)m_Gold
		<< ",DonationType:" << (int)m_DonationType
		<< ")";
	return msg.toString();

	__END_CATCH
}
