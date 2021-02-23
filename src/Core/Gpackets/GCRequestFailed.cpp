//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRequestFailed.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCRequestFailed.h"

void GCRequestFailed::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE name_length = 0;

	iStream.read(m_Code);
	iStream.read(name_length);

	if (name_length == 0) throw ProtocolException("");

	iStream.read(m_Name, name_length);

	__END_CATCH
}
		    
void GCRequestFailed::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_Code);
	
	BYTE name_length = m_Name.size();
	if (name_length == 0) throw ProtocolException("");

	oStream.write(name_length);
	oStream.write(m_Name);

	__END_CATCH
}

void GCRequestFailed::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCRequestFailedHandler::execute( this , pPlayer );
		
	__END_CATCH
}

string GCRequestFailed::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCRequestFailed(" 
	    << "Code : " << (int)m_Code 
	    << ")";
	return msg.toString();

	__END_CATCH
}


