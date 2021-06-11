//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCSayDynamic.cpp 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCNPCSayDynamic.h"

void GCNPCSayDynamic::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);

	BYTE szMessage;

	iStream.read(szMessage);

	if (szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	iStream.read(m_Message , szMessage);

	__END_CATCH
}
		    
void GCNPCSayDynamic::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);

	BYTE szMessage = m_Message.size();

	if (szMessage == 0 )
		throw InvalidProtocolException("szMessage == 0");

	oStream.write(szMessage);

	oStream.write(m_Message);

	__END_CATCH
}

void GCNPCSayDynamic::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCNPCSayDynamicHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCNPCSayDynamic::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCNPCSayDynamic("
		<< "ObjectID:" << m_ObjectID 
		<< ",Message:" << m_Message 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


