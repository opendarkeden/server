//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestInfo.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestInfo.h"

void CGRequestInfo::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Code);
	iStream.read(m_Value);

	__END_CATCH
}

void CGRequestInfo::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Code);
	oStream.write(m_Value);

	__END_CATCH
}

void CGRequestInfo::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGRequestInfoHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGRequestInfo::toString () const 
	
{
	StringStream msg;
	msg << "CGRequestInfo(" 
		<< "Code : " << (int)m_Code
		<< "Value : " << (int)m_Value
		<< ")";
	return msg.toString();
}
