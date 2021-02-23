//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddSMSAddress.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddSMSAddress.h"

CGAddSMSAddress::CGAddSMSAddress () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddSMSAddress::~CGAddSMSAddress () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddSMSAddress::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szSTR;

	iStream.read( szSTR );
	iStream.read( m_CharacterName, szSTR );

	iStream.read( szSTR );
	iStream.read( m_CustomName, szSTR );

	iStream.read( szSTR );
	iStream.read( m_Number, szSTR );

	__END_CATCH
}

void CGAddSMSAddress::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szSTR;

	szSTR = m_CharacterName.size();
	oStream.write( szSTR );
	oStream.write( m_CharacterName );

	szSTR = m_CustomName.size();
	oStream.write( szSTR );
	oStream.write( m_CustomName );

	szSTR = m_Number.size();
	oStream.write( szSTR );
	oStream.write( m_Number );

	__END_CATCH
}

void CGAddSMSAddress::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddSMSAddressHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddSMSAddress::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddSMSAddress("
		<< ")";
	return msg.toString();

	__END_CATCH
}
