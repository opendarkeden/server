//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyError.cpp 
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPartyError.h"

const string GCPartyError2String[] = 
{
	"TARGET_NOT_EXIST",
	"RACE_DIFFER",
	"NOT_SAFE",
	"NOT_NORMAL_FORM",
	"ALREADY_INVITING",
	"NOT_INVITING",
	"NO_AUTHORITY",
	"UNKNOWN",
	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// class GCPartyError member methods
//////////////////////////////////////////////////////////////////////////////

void GCPartyError::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_Code);
	iStream.read(m_TargetObjectID);
		
	__END_CATCH
}
		    
void GCPartyError::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	
	oStream.write(m_Code);
	oStream.write(m_TargetObjectID);

	__END_CATCH
}

void GCPartyError::execute (Player * pPlayer) 
	 
{
	__BEGIN_TRY
		
	GCPartyErrorHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCPartyError::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCPartyError("
		<< "CODE:" << GCPartyError2String[m_Code]
		<< "TOID:" << m_TargetObjectID
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


