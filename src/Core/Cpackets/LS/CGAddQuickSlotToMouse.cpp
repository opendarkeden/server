//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddQuickSlotToMouse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddQuickSlotToMouse.h"

CGAddQuickSlotToMouse::CGAddQuickSlotToMouse () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddQuickSlotToMouse::~CGAddQuickSlotToMouse () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddQuickSlotToMouse::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGAddQuickSlotToMouse::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGAddQuickSlotToMouse::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddQuickSlotToMouseHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddQuickSlotToMouse::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddQuickSlotToMouse("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ",SlotID : " << (int)m_SlotID
		<< ")";
	return msg.toString();

	__END_CATCH
}
