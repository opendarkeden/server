//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashList.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashList.h"

void CGStashList::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	
	iStream.read(m_ObjectID);

	__END_CATCH
}
		    
void CGStashList::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);

	__END_CATCH
}

void CGStashList::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	CGStashListHandler::execute (this , pPlayer);
		
	__END_DEBUG
	__END_CATCH
}

string CGStashList::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGStashList(" 
		<< "ObjectID : " << m_ObjectID
		<< ")";
	return msg.toString();

	__END_CATCH
}
