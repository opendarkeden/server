//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashList.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashList.h"

void CGStashList::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	
	iStream.read(m_ObjectID);

	__END_CATCH
}
		    
void CGStashList::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGStashList::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	CGStashListHandler::execute (this , pPlayer);
		
	__END_DEBUG
	__END_CATCH
}

string CGStashList::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGStashList(" 
		<< "ObjectID : " << m_ObjectID
		<< ")";
	return msg.toString();

	__END_CATCH
}
