//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToInventory.h"

CGAddMouseToInventory::CGAddMouseToInventory () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddMouseToInventory::~CGAddMouseToInventory () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddMouseToInventory::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);

	__END_CATCH
}

void CGAddMouseToInventory::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_InvenX);
	oStream.write(m_InvenY);

	__END_CATCH
}

void CGAddMouseToInventory::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddMouseToInventoryHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddMouseToInventory::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddMouseToInventory("
		<< "ObjectID:"    << (int)m_ObjectID 
		<< ",InventoryX:" << (int)m_InvenX 
		<< ",InventoryY:" << (int)m_InvenY 
		<< ")";
	return msg.toString();

	__END_CATCH
}
