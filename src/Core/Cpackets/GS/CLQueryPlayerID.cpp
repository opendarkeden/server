//////////////////////////////////////////////////////////////////////////////
// Filename    : CLQueryPlayerID.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLQueryPlayerID.h"

void CLQueryPlayerID::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// read player id
	BYTE szPlayerID;

	iStream.read(szPlayerID);

	if (szPlayerID == 0)
		throw InvalidProtocolException("szPlayerID == 0");

	if (szPlayerID > 20)
		throw InvalidProtocolException("too long PlayerID length");

	iStream.read(m_PlayerID , szPlayerID);

	__END_CATCH
}
		    
void CLQueryPlayerID::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// write player id
	BYTE szPlayerID = m_PlayerID.size();

	if (szPlayerID == 0)
		throw InvalidProtocolException("empty PlayerID");

	if (szPlayerID > 20)
		throw InvalidProtocolException("too long PlayerID length");

	oStream.write(szPlayerID);

	oStream.write(m_PlayerID);

	__END_CATCH
}

void CLQueryPlayerID::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CLQueryPlayerIDHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CLQueryPlayerID::toString () const
	throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CLQueryPlayerID("
		<< "PlayerID:" << m_PlayerID 
		<< ")";
	return msg.toString();
		
	__END_CATCH
}

