//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddInjuriousCreature.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddInjuriousCreature.h"

void CGAddInjuriousCreature::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// 이름 읽기
	BYTE szName;

	iStream.read(szName);

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 10)
		throw InvalidProtocolException("too large name length");

	iStream.read(m_Name , szName);

	__END_CATCH
}
		    
void CGAddInjuriousCreature::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// 이름 쓰기
	BYTE szName = m_Name.size();

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 10)
		throw InvalidProtocolException("too large name length");

	oStream.write(szName);

	oStream.write(m_Name);

	__END_CATCH
}

void CGAddInjuriousCreature::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGAddInjuriousCreatureHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGAddInjuriousCreature::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddInjuriousCreature(Name :" << m_Name 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
