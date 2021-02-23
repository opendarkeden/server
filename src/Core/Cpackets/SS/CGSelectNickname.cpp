//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectNickname.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectNickname.h"


void CGSelectNickname::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read( m_NicknameID );

	__END_CATCH
}

void CGSelectNickname::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write( m_NicknameID );

	__END_CATCH
}

void CGSelectNickname::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSelectNicknameHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectNickname::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectNickname("
		<< "NicknameID:" << m_NicknameID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
