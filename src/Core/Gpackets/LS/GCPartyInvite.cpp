//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyInvite.cpp 
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPartyInvite.h"

const string GCPartyInvite2String[] =
{
	"REQUEST",
	"CANCEL",
	"ACCEPT",
	"REJECT",
	"BUSY",
	"ANOTHER_PARTY",
	"MEMBER_FULL",
	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// class GCPartyInvite member methods
//////////////////////////////////////////////////////////////////////////////

void GCPartyInvite::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	iStream.read(m_Code);
	iStream.read(m_TargetObjectID);
		
	__END_CATCH
}
		    
void GCPartyInvite::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	
	oStream.write(m_Code);
	oStream.write(m_TargetObjectID);

	__END_CATCH
}

void GCPartyInvite::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCPartyInviteHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCPartyInvite::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCPartyInvite("
		<< "CODE:" << GCPartyInvite2String[m_Code]
		<< "TOID:" << m_TargetObjectID
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


