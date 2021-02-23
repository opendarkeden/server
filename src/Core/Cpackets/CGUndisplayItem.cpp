//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUndisplayItem.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUndisplayItem.h"

void CGUndisplayItem::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_ItemObjectID );
	iStream.read( m_Index );

	__END_CATCH
}

void CGUndisplayItem::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_ItemObjectID );
	oStream.write( m_Index );
	
	__END_CATCH
}

void CGUndisplayItem::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGUndisplayItemHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGUndisplayItem::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGUndisplayItem("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
