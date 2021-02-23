//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyInvite.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyInvite.h"

void CGPartyInvite::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_TargetObjectID);
	iStream.read(m_Code);

	__END_CATCH
}
		    
void CGPartyInvite::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_TargetObjectID);
	oStream.write(m_Code);

	__END_CATCH
}

void CGPartyInvite::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGPartyInviteHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPartyInvite::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGPartyInvite(" 
		<< "TargetObjectID : " << (int)m_TargetObjectID
		<< ",CODE : "          << (int)m_Code 
		<< ")";
	return msg.toString();

	__END_CATCH
}
