//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectWayPoint.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectWayPoint.h"

void CGSelectWayPoint::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ZoneID);
	iStream.read(m_X);
	iStream.read(m_Y);

	__END_CATCH
}
		    
void CGSelectWayPoint::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ZoneID);
	oStream.write(m_X);
	oStream.write(m_Y);

	__END_CATCH
}

void CGSelectWayPoint::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSelectWayPointHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectWayPoint::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectWayPoint("
		<< "ZoneID:" << (int)m_ZoneID
		<< ",X:"     << (int)m_X
		<< ",Y:"     << (int)m_Y
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
