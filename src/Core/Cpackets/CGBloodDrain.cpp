//////////////////////////////////////////////////////////////////////////////
// Filename    : CGBloodDrain.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGBloodDrain.h"

CGBloodDrain::CGBloodDrain () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGBloodDrain::~CGBloodDrain () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGBloodDrain::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read((char*)&m_ObjectID , szObjectID);

	__END_CATCH
}
		    
void CGBloodDrain::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write((char*)&m_ObjectID , szObjectID);

	__END_CATCH
}

void CGBloodDrain::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGBloodDrainHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGBloodDrain::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGBloodDrain("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
