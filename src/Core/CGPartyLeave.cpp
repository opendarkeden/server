//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyLeave.cpp 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyLeave.h"

void CGPartyLeave::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	BYTE name_length = 0;
	iStream.read(name_length);
	if (name_length > 0)
	{
		iStream.read(m_TargetName, name_length);
	}

	__END_CATCH
}
		    
void CGPartyLeave::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	BYTE name_length = m_TargetName.size();
	oStream.write(name_length);
	if (name_length > 0)
	{
		oStream.write(m_TargetName);
	}

	__END_CATCH
}

void CGPartyLeave::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGPartyLeaveHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPartyLeave::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGPartyLeave(" 
		<< "TargetName:" << m_TargetName
		<< ")";
	return msg.toString();

	__END_CATCH
}
