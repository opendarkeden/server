//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPetGamble.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPetGamble.h"
#include "Assert.h"


CGPetGamble::CGPetGamble () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGPetGamble::~CGPetGamble () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGPetGamble::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	__END_CATCH
}

void CGPetGamble::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void CGPetGamble::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGPetGambleHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPetGamble::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGPetGamble()";
	return msg.toString();

	__END_CATCH
}
