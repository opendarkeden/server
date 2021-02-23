//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddInventoryToMouse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddInventoryToMouse.h"

CGAddInventoryToMouse::CGAddInventoryToMouse () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddInventoryToMouse::~CGAddInventoryToMouse () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddInventoryToMouse::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);

	__END_CATCH
}

void CGAddInventoryToMouse::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_InvenX );
	oStream.write(m_InvenY );

	__END_CATCH
}

void CGAddInventoryToMouse::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddInventoryToMouseHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddInventoryToMouse::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddInventoryToMouse(ObjectID : " << (int)m_ObjectID 
		<< ", InventoryX : " << (int)m_InvenX
		<< ", InventoryY : " << (int)m_InvenY 
		<< ")";
	return msg.toString();

	__END_CATCH
}
