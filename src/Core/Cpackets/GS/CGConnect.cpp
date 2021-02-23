//////////////////////////////////////////////////////////////////////////////
// Filename    : CGConnect.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGConnect.h"

void CGConnect::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// read authentication key
	iStream.read(m_Key);

	// read PC type
	BYTE pcType;
	iStream.read(pcType);
	m_PCType = PCType(pcType);

	// read PC name
	BYTE szPCName;
	iStream.read(szPCName);

	if (szPCName == 0) throw InvalidProtocolException("szPCName == 0");

	if (szPCName > 20) throw InvalidProtocolException("too long pc name length");

	iStream.read(m_PCName , szPCName);
	iStream.read((char*)m_MacAddress, 6);

	__END_CATCH
}
		    
void CGConnect::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// write authentication key
	oStream.write(m_Key);

	// write PC type
	oStream.write((BYTE)m_PCType);

	// write PC name
	BYTE szPCName = m_PCName.size();

	if (szPCName == 0) throw InvalidProtocolException("szPCName == 0");

	if (szPCName > 20) throw InvalidProtocolException("too long pc name length");

	oStream.write(szPCName);
	oStream.write(m_PCName);

	oStream.write((char*)m_MacAddress, 6);

	__END_CATCH
}

void CGConnect::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGConnectHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGConnect::toString () const
       throw ()
{
	StringStream msg;
	msg << "CGConnect(" ;///modify by viva for notice
	//	<< "KEY:" << m_Key 
	//	<< ",PCType:" << PCType2String[m_PCType] 
	//	<< ",PCName:" << m_PCName 
	//	<< ")" ;
	return msg.toString();
}
