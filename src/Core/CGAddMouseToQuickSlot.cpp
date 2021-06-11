//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToQuickSlot.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToQuickSlot.h"

CGAddMouseToQuickSlot::CGAddMouseToQuickSlot () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddMouseToQuickSlot::~CGAddMouseToQuickSlot () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddMouseToQuickSlot::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGAddMouseToQuickSlot::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGAddMouseToQuickSlot::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGAddMouseToQuickSlotHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddMouseToQuickSlot::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddMouseToQuickSlot("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",SlotID:"  << (int)m_SlotID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
