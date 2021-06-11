//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestGuildMemberList.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestGuildMemberList.h"


void CGRequestGuildMemberList::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_GuildID);

	__END_CATCH
}

void CGRequestGuildMemberList::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_GuildID);

	__END_CATCH
}

void CGRequestGuildMemberList::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGRequestGuildMemberListHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRequestGuildMemberList::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRequestGuildMemberList("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
