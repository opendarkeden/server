//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToItem.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddItemToItem.h"

void CGAddItemToItem::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_X);
	iStream.read(m_Y);

	__END_CATCH
}

void CGAddItemToItem::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);
	oStream.write(m_X);
	oStream.write(m_Y);

	__END_CATCH
}

void CGAddItemToItem::execute (Player* pPlayer) 
	
{
	__BEGIN_TRY
		
	CGAddItemToItemHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGAddItemToItem::toString () const
	
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddItemToItem("
		<< ",ObjectID:"  << (int)m_ObjectID 
		<< ",X:"         << (int)m_X 
		<< ",Y:"         << (int)m_Y 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
