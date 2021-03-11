//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNotifyWin.cpp 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCNotifyWin.h"

void GCNotifyWin::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_GiftID);

	BYTE szMessage;

	iStream.read(szMessage);

	if (szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	iStream.read(m_Name , szMessage);

	__END_CATCH
}
		    
void GCNotifyWin::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_GiftID);

	BYTE szMessage = m_Name.size();

	if (szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	oStream.write(szMessage);

	oStream.write(m_Name);

	__END_CATCH
}

void GCNotifyWin::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCNotifyWinHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCNotifyWin::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCNotifyWin("
		<< "ObjectID:" << m_GiftID 
		<< ",Message:" << m_Name 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


