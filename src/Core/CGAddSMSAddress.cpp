//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddSMSAddress.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddSMSAddress.h"

CGAddSMSAddress::CGAddSMSAddress () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddSMSAddress::~CGAddSMSAddress () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddSMSAddress::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	BYTE szSTR;

	iStream.read(szSTR);
	iStream.read(m_CharacterName, szSTR);

	iStream.read(szSTR);
	iStream.read(m_CustomName, szSTR);

	iStream.read(szSTR);
	iStream.read(m_Number, szSTR);

	__END_CATCH
}

void CGAddSMSAddress::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	BYTE szSTR;

	szSTR = m_CharacterName.size();
	oStream.write(szSTR);
	oStream.write(m_CharacterName);

	szSTR = m_CustomName.size();
	oStream.write(szSTR);
	oStream.write(m_CustomName);

	szSTR = m_Number.size();
	oStream.write(szSTR);
	oStream.write(m_Number);

	__END_CATCH
}

void CGAddSMSAddress::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGAddSMSAddressHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddSMSAddress::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddSMSAddress("
		<< ")";
	return msg.toString();

	__END_CATCH
}
