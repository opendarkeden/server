//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRelicToObject.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRelicToObject.h"

CGRelicToObject::CGRelicToObject () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGRelicToObject::~CGRelicToObject () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGRelicToObject::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ItemObjectID);
	iStream.read(m_ObjectID);
	iStream.read(m_X);
	iStream.read(m_Y);

	__END_CATCH
}

void CGRelicToObject::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ItemObjectID);
	oStream.write(m_ObjectID);
	oStream.write(m_X);
	oStream.write(m_Y);

	__END_CATCH
}

void CGRelicToObject::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGRelicToObjectHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRelicToObject::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRelicToObject("
		<< "X:"         << (int)m_X 
		<< ",Y:"        << (int)m_Y
		<< ",ItemObjectID:" << (int)m_ItemObjectID
		<< ",ObjectID:" << (int)m_ObjectID
	   	<< ")" ;
	return msg.toString();

	__END_CATCH
}
