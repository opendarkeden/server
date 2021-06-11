//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReloadFromInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGReloadFromInventory.h"

CGReloadFromInventory::CGReloadFromInventory () 
     
{
	__BEGIN_TRY
	__END_CATCH
}
	
CGReloadFromInventory::~CGReloadFromInventory () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGReloadFromInventory::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);

	__END_CATCH
}

void CGReloadFromInventory::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_InvenX);
	oStream.write(m_InvenY);

	__END_CATCH
}

void CGReloadFromInventory::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGReloadFromInventoryHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGReloadFromInventory::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGReloadFromInventory("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ",InvenX: "   << (int)m_InvenX
		<< ",InvenY: "   << (int)m_InvenY
		<< ")";
	return msg.toString();

	__END_CATCH
}
