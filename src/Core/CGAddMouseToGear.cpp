//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToGear.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToGear.h"

CGAddMouseToGear::CGAddMouseToGear () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddMouseToGear::~CGAddMouseToGear () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddMouseToGear::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGAddMouseToGear::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGAddMouseToGear::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGAddMouseToGearHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddMouseToGear::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddMouseToGear(ObjectID : " << (int)m_ObjectID 
		<< ",SlotID" << (int)m_SlotID
		<< ")";
	return msg.toString();

	__END_CATCH
}
