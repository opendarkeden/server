//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDisplayItem.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDisplayItem.h"

void CGDisplayItem::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_X);
	iStream.read(m_Y);
	iStream.read(m_ItemObjectID);
	iStream.read(m_Price);
	iStream.read(m_Index);

	__END_CATCH
}

void CGDisplayItem::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_X);
	oStream.write(m_Y);
	oStream.write(m_ItemObjectID);
	oStream.write(m_Price);
	oStream.write(m_Index);
	
	__END_CATCH
}

void CGDisplayItem::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGDisplayItemHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGDisplayItem::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGDisplayItem("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
