//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItem.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeRemoveItem.h"

void CGTradeRemoveItem::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_TargetObjectID);
	iStream.read(m_ItemObjectID);

	__END_CATCH
}

void CGTradeRemoveItem::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_TargetObjectID);
	oStream.write(m_ItemObjectID );

	__END_CATCH
}

void CGTradeRemoveItem::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGTradeRemoveItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTradeRemoveItem::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGTradeRemoveItem(" 
		<< "TargetObjectID:" << (int)m_TargetObjectID
		<< ",ItemObjectID:" << (int)m_ItemObjectID
		<< ")";
	return msg.toString();

	__END_CATCH
}
