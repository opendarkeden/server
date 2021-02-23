//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyLeave.cpp 
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPartyLeave.h"

//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeave member methods
//////////////////////////////////////////////////////////////////////////////

void GCPartyLeave::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE name_length = 0;

	iStream.read(name_length);
	if (name_length > 0)
		iStream.read(m_Expeller, name_length);

	iStream.read(name_length);
	if (name_length > 0)
		iStream.read(m_Expellee, name_length);
		
	__END_CATCH
}
		    
void GCPartyLeave::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	
	BYTE name_length = 0;

	name_length = m_Expeller.size();
	oStream.write(name_length);
	if (name_length > 0)
		oStream.write(m_Expeller);

	name_length = m_Expellee.size();
	oStream.write(name_length);
	if (name_length > 0)
		oStream.write(m_Expellee);

	__END_CATCH
}

void GCPartyLeave::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCPartyLeaveHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCPartyLeave::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCPartyLeave("
		<< "Expeller:" << m_Expeller
		<< "Expellee:" << m_Expellee
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


