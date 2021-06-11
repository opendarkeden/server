//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectGuildMember.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectGuildMember.h"


void CGSelectGuildMember::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	BYTE szName;

	iStream.read(m_GuildID);
	iStream.read(szName);

	if (szName == 0 )
		throw InvalidProtocolException("szName == 0");
	if (szName > 20 )
		throw InvalidProtocolException("too long szName length");

	iStream.read(m_Name, szName);

	__END_CATCH
}

void CGSelectGuildMember::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();

	if (szName == 0 )
		throw InvalidProtocolException("szName == 0");
	if (szName > 20 )
		throw InvalidProtocolException("too long szName length");

	oStream.write(m_GuildID);
	oStream.write(szName);
	oStream.write(m_Name);

	__END_CATCH
}

void CGSelectGuildMember::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSelectGuildMemberHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectGuildMember::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectGuildMember("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
