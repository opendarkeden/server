//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectPC.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectPC.h"

void CLSelectPC::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// read creature's name
	BYTE szPCName;

	iStream.read(szPCName);

	if (szPCName == 0) 
		throw InvalidProtocolException("szPCName == 0");

	if (szPCName > 20) 
		throw InvalidProtocolException("too long pc name length");

	iStream.read(m_PCName , szPCName);

	// read pc type
	BYTE pcType;
	iStream.read(pcType);
	m_PCType = PCType(pcType);

	if (m_PCType != PC_SLAYER && m_PCType != PC_VAMPIRE && m_PCType != PC_OUSTERS)
		throw InvalidProtocolException("invalid pc type");

	__END_CATCH
}
		    
void CLSelectPC::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// write creature's name
	BYTE szPCName = m_PCName.size();

	if (szPCName == 0) 
		throw InvalidProtocolException("szPCName == 0");

	if (szPCName > 20) 
		throw InvalidProtocolException("too long pc name length");

	oStream.write(szPCName);

	oStream.write(m_PCName);

	// write pc type
	if (m_PCType != PC_SLAYER && m_PCType != PC_VAMPIRE && m_PCType != PC_OUSTERS)
		throw InvalidProtocolException("invalid pc type");

	oStream.write((BYTE)m_PCType);

	__END_CATCH
}

// execute packet's handler
void CLSelectPC::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CLSelectPCHandler::execute(this , pPlayer);
		
	__END_CATCH
}

// get packet's debug string
string CLSelectPC::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CLSelectPC(";	//modify by viva for notice
	//	<< "PCName:" << m_PCName 
	//	<< ",PCType:" << PCType2String[m_PCType] 
	//	<< ")" ;
	return msg.toString();

	__END_CATCH
}


