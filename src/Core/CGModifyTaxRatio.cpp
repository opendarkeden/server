//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyTaxRatio.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyTaxRatio.h"

void CGModifyTaxRatio::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Ratio);

	__END_CATCH
}

void CGModifyTaxRatio::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Ratio);
	
	__END_CATCH
}

void CGModifyTaxRatio::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGModifyTaxRatioHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGModifyTaxRatio::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGModifyTaxRatio("
		<< "Ratio : " << (int)m_Ratio
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
