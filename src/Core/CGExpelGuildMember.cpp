//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExpelGuildMember.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGExpelGuildMember.h"


void CGExpelGuildMember::read (SocketInputStream & iStream) 
	 
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

void CGExpelGuildMember::write (SocketOutputStream & oStream) const 
     
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

void CGExpelGuildMember::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGExpelGuildMemberHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGExpelGuildMember::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGExpelGuildMember("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< ")";
	return msg.toString();

	__END_CATCH
}
