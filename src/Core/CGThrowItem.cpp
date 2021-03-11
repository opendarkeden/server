//////////////////////////////////////////////////////////////////////////////
// Filename    : CGThrowItem.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGThrowItem.h"

CGThrowItem::CGThrowItem () 
     
{
	__BEGIN_TRY
	__END_CATCH
}
	
CGThrowItem::~CGThrowItem () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGThrowItem::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_TargetObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);

	__END_CATCH
}
		    
void CGThrowItem::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);
	oStream.write(m_TargetObjectID);
	oStream.write(m_InvenX);
	oStream.write(m_InvenY);

	__END_CATCH
}

void CGThrowItem::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGThrowItemHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGThrowItem::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGThrowItem("
		<< "ObjectID:" << (int)m_ObjectID 
    	<< ",TargetObjectID:" << (int)m_TargetObjectID 
		<< ",InvenX" << (int)m_InvenX
		<< ",InvenY" << (int)m_InvenY
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
