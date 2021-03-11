//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUnburrow.cpp 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUnburrow.h"

void CGUnburrow::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_X);
	iStream.read(m_Y);
	iStream.read(m_Dir);

	__END_CATCH
}

void CGUnburrow::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_X);
	oStream.write(m_Y);
	oStream.write(m_Dir);

	__END_CATCH
}

void CGUnburrow::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGUnburrowHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGUnburrow::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUnburrow("
		<< "X:" << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",Dir:" << Dir2String[m_Dir] << ")";
	return msg.toString();

	__END_CATCH
}
