//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTakeOutGood.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTakeOutGood.h"
#include "Assert1.h"


CGTakeOutGood::CGTakeOutGood () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGTakeOutGood::~CGTakeOutGood () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGTakeOutGood::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);

	__END_CATCH
}

void CGTakeOutGood::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGTakeOutGood::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGTakeOutGoodHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTakeOutGood::toString () 
	const 
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGTakeOutGood(ObjectID : " << (int)m_ObjectID << ")";
	return msg.toString();

	__END_CATCH
}
