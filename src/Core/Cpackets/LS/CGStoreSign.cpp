//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStoreSign.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStoreSign.h"

void CGStoreSign::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE size;
	iStream.read(size);
	iStream.read(m_Sign, size);
		
	__END_CATCH
}

void CGStoreSign::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE size = m_Sign.size();
	oStream.write(size);
	oStream.write(m_Sign);

	__END_CATCH
}

void CGStoreSign::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGStoreSignHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGStoreSign::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGStoreSign("
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
