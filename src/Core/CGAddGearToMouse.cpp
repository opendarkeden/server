//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddGearToMouse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddGearToMouse.h"

CGAddGearToMouse::CGAddGearToMouse () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddGearToMouse::~CGAddGearToMouse () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddGearToMouse::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGAddGearToMouse::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGAddGearToMouse::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGAddGearToMouseHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddGearToMouse::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddGearToMouse("
		<< "ObjectID: " << (int)m_ObjectID 
		<< ", SlotID: " << (int)m_SlotID
		<< ")";
	return msg.toString();

	__END_CATCH
}
