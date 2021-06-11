//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestNewbieItem.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestNewbieItem.h"

void CGRequestNewbieItem::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ItemClass);

	__END_CATCH
}
		    
void CGRequestNewbieItem::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ItemClass);

	__END_CATCH
}

void CGRequestNewbieItem::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGRequestNewbieItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGRequestNewbieItem::toString () 
	const 
{
	StringStream msg;
	msg << "CGRequestNewbieItem(" 
		<< "ItemClass : " << (int)m_ItemClass
		<< ")";
	return msg.toString();
}
