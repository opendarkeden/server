//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyPosition.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyPosition.h"

CGPartyPosition::CGPartyPosition () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGPartyPosition::~CGPartyPosition () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGPartyPosition::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_ZoneID);
	iStream.read(m_X);
	iStream.read(m_Y);
	iStream.read(m_MaxHP);
	iStream.read(m_HP);
		
	__END_CATCH
}
		    
void CGPartyPosition::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ZoneID);
	oStream.write(m_X);
	oStream.write(m_Y);
	oStream.write(m_MaxHP);
	oStream.write(m_HP);

	__END_CATCH
}

void CGPartyPosition::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGPartyPositionHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPartyPosition::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGPartyPosition("
		<< "ZoneID : " << m_ZoneID
		<< "ZoneX :" << (int)m_X
		<< "ZoneY :" << (int)m_Y
		<< "MaxHP : " << m_MaxHP
		<< "HP : " << m_HP
		<< ")";
	return msg.toString();

	__END_CATCH
}
