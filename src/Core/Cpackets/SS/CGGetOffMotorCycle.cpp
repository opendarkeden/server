//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGetOffMotorCycle.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGGetOffMotorCycle.h"

CGGetOffMotorCycle::CGGetOffMotorCycle () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGGetOffMotorCycle::~CGGetOffMotorCycle () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGGetOffMotorCycle::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);

	__END_CATCH
}

void CGGetOffMotorCycle::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGGetOffMotorCycle::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGGetOffMotorCycleHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGGetOffMotorCycle::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGGetOffMotorCycle(ObjectID :" << (int)m_ObjectID << ")" ;
	return msg.toString();

	__END_CATCH
}
