//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestNewbieItem.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestNewbieItem.h"

void CGRequestNewbieItem::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ItemClass);

	__END_CATCH
}
		    
void CGRequestNewbieItem::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ItemClass);

	__END_CATCH
}

void CGRequestNewbieItem::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGRequestNewbieItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGRequestNewbieItem::toString () 
	const throw ()
{
	StringStream msg;
	msg << "CGRequestNewbieItem(" 
		<< "ItemClass : " << (int)m_ItemClass
		<< ")";
	return msg.toString();
}
