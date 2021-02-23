//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestIP.cpp 
// Written By  :
// Description :
// 서버에 원하는 사람의 IP 요청
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestIP.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestIP member methods
//////////////////////////////////////////////////////////////////////////////

CGRequestIP::CGRequestIP () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}
	
CGRequestIP::~CGRequestIP () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGRequestIP::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE num;
	iStream.read( num );

	if (num > 0)
	{
		iStream.read( m_Name, num );
	}

	__END_CATCH
}
		    
void CGRequestIP::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE num = m_Name.size();
	oStream.write( num );

	if (num > 0)
	{
		oStream.write( m_Name );
	}

	__END_CATCH
}

void CGRequestIP::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CGRequestIPHandler::execute( this , pPlayer );
		
	__END_CATCH
}

string CGRequestIP::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGRequestIP( "
		<< ",Name: " << m_Name			
		<< ")";
	return msg.toString();

	__END_CATCH
}
