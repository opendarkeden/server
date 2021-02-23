//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAbsorbSoul.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAbsorbSoul.h"

CGAbsorbSoul::CGAbsorbSoul () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAbsorbSoul::~CGAbsorbSoul () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAbsorbSoul::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_TargetZoneX);
	iStream.read(m_TargetZoneY);
	iStream.read(m_InvenObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);
	iStream.read(m_TargetInvenX);
	iStream.read(m_TargetInvenY);

	__END_CATCH
}
		    
void CGAbsorbSoul::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_TargetZoneX);
	oStream.write(m_TargetZoneY);
	oStream.write(m_InvenObjectID);
	oStream.write(m_InvenX);
	oStream.write(m_InvenY);
	oStream.write(m_TargetInvenX);
	oStream.write(m_TargetInvenY);

	__END_CATCH
}

void CGAbsorbSoul::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAbsorbSoulHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAbsorbSoul::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAbsorbSoul("
		<< "ObjectID:" << (int)m_ObjectID 
		<< "InvenObjectID:" << (int)m_InvenObjectID 
		<< "InvenX :" << (int)m_InvenX
		<< "InvenY :" << (int)m_InvenY
		<< ")";
	return msg.toString();

	__END_CATCH
}
