//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMakeItem.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGMakeItem.h"

CGMakeItem::CGMakeItem () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGMakeItem::~CGMakeItem () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGMakeItem::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ItemClass);
	iStream.read(m_ItemType);

	__END_CATCH
}

void CGMakeItem::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ItemClass);
	oStream.write(m_ItemType);

	__END_CATCH
}

void CGMakeItem::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGMakeItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGMakeItem::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGMakeItem("
		<< "ItemClass: " << (int)m_ItemClass
		<< "ItemType: " << (int)m_ItemType
		<< ")";
	return msg.toString();

	__END_CATCH
}
