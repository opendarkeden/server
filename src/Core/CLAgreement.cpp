//////////////////////////////////////////////////////////////////////////////
// Filename    : CLAgreement.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLAgreement.h"

void CLAgreement::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_Agree);

	__END_CATCH
}

void CLAgreement::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Agree);

	__END_CATCH
}

void CLAgreement::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CLAgreementHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CLAgreement::toString () const
	
{
	StringStream msg;
	msg << "CLAgreement("
		<< "Agree:" << (int)m_Agree
		<< ")";
	return msg.toString();
}

