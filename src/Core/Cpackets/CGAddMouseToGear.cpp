//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToGear.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToGear.h"

CGAddMouseToGear::CGAddMouseToGear () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddMouseToGear::~CGAddMouseToGear () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddMouseToGear::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_SlotID);

	__END_CATCH
}

void CGAddMouseToGear::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_SlotID);

	__END_CATCH
}

void CGAddMouseToGear::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddMouseToGearHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddMouseToGear::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddMouseToGear(ObjectID : " << (int)m_ObjectID 
		<< ",SlotID" << (int)m_SlotID
		<< ")";
	return msg.toString();

	__END_CATCH
}
