//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePotionFromQuickSlot.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUsePotionFromQuickSlot.h"

CGUsePotionFromQuickSlot::CGUsePotionFromQuickSlot () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGUsePotionFromQuickSlot::~CGUsePotionFromQuickSlot () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGUsePotionFromQuickSlot::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGUsePotionFromQuickSlot::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGUsePotionFromQuickSlot::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGUsePotionFromQuickSlotHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGUsePotionFromQuickSlot::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUsePotionFromQuickSlot("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",SlotID:" << (int)m_SlotID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
