//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDepositPet.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDepositPet.h"

void CGDepositPet::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY 
		
	iStream.read(m_ObjectID);
	iStream.read(m_Index);

	__END_CATCH
}

void CGDepositPet::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_Index);

	__END_CATCH
}

void CGDepositPet::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGDepositPetHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGDepositPet::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGDepositPet("
		<< " ObjectID : " << (int)m_ObjectID
		<< " Index : "    << (int)m_Index
		<< ")";
	return msg.toString();

	__END_CATCH
}
